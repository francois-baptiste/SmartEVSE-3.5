#!/usr/bin/env python3
"""
Mutation testing for SmartEVSE pure C modules.

Applies single-point mutations to a C source file, recompiles, and runs the
corresponding test suite.  Survived mutants indicate test gaps.

Usage:
    python3 scripts/mutate.py --source ../../src/capacity_peak.c \
                              --test tests/test_capacity_peak.c \
                              --report reports/capacity_peak.html

Works with any gcc/clang + Unity test binary that returns 0 on pass.
Zero external dependencies — uses only the Python standard library.
"""
from __future__ import annotations

import argparse
import html
import json
import os
import re
import subprocess
import sys
import tempfile
import time
from dataclasses import dataclass, field
from pathlib import Path
from typing import List, Optional, Tuple


# ---------------------------------------------------------------------------
# Mutation operators
# ---------------------------------------------------------------------------

@dataclass
class Mutation:
    """A single mutation applied to one source line."""
    line_no: int          # 1-based
    original: str         # original line content
    mutated: str          # mutated line content
    operator: str         # e.g. "arith_add_to_sub"
    description: str      # human-readable, e.g. "Replace '+' with '-'"


# Each operator is (name, description, regex_pattern, replacement).
# The regex operates on a single line.  We skip lines that are comments or
# string literals (best-effort).

OPERATORS: List[Tuple[str, str, str, str]] = [
    # Arithmetic — space-delimited to avoid hitting pointer/struct operators
    ("arith_add_to_sub",  "Replace '+' with '-'",   r' \+ ',   ' - '),
    ("arith_sub_to_add",  "Replace '-' with '+'",   r' - ',    ' + '),
    ("arith_mul_to_div",  "Replace '*' with '/'",   r' \* ',   ' / '),
    ("arith_div_to_mul",  "Replace '/' with '*'",   r' / ',    ' * '),
    ("arith_mod_to_div",  "Replace '%' with '/'",   r' % ',    ' / '),

    # Relational — boundary mutations (off-by-one)
    ("rel_ge_to_gt",  "Replace '>=' with '>'",   r'>=',   '>' ),
    ("rel_le_to_lt",  "Replace '<=' with '<'",   r'<=',   '<' ),
    ("rel_gt_to_ge",  "Replace '>' with '>='",   r'(?<!-)(?<!>)>(?!=)',   '>='),
    ("rel_lt_to_le",  "Replace '<' with '<='",   r'(?<!<)<(?!=)',         '<='),

    # Relational — equality
    ("rel_eq_to_ne",  "Replace '==' with '!='",  r'==',  '!='),
    ("rel_ne_to_eq",  "Replace '!=' with '=='",  r'!=',  '=='),

    # Logical
    ("log_and_to_or",  "Replace '&&' with '||'",  r'&&',    '||'),
    ("log_or_to_and",  "Replace '||' with '&&'",  r'\|\|',  '&&'),

    # Increment / decrement
    ("inc_to_dec",  "Replace '++' with '--'",  r'\+\+',  '--'),
    ("dec_to_inc",  "Replace '--' with '++'",  r'(?<!>)--',  '++'),

    # Negate condition
    ("negate_return_0",  "Replace 'return 0' with 'return 1'",
     r'return\s+0\s*;',  'return 1;'),
    ("negate_return_1",  "Replace 'return 1' with 'return 0'",
     r'return\s+1\s*;',  'return 0;'),

    # Constant boundary
    ("const_zero_to_one",  "Replace literal '0' with '1' (in comparisons)",
     r'(?<==\s)0(?=\s*[;)\]}])',  '1'),
]


def is_code_line(line: str) -> bool:
    """Best-effort filter: skip blank lines, preprocessor, pure comments."""
    stripped = line.strip()
    if not stripped:
        return False
    if stripped.startswith('//'):
        return False
    if stripped.startswith('#'):
        return False
    if stripped.startswith('/*') and stripped.endswith('*/'):
        return False
    if stripped.startswith('*'):  # doc-comment continuation
        return False
    return True


def generate_mutants(source_lines: List[str]) -> List[Mutation]:
    """Generate all single-point mutants from source lines."""
    mutants: List[Mutation] = []
    in_block_comment = False

    for i, line in enumerate(source_lines):
        stripped = line.strip()

        # Track block comments
        if '/*' in stripped and '*/' not in stripped:
            in_block_comment = True
            continue
        if in_block_comment:
            if '*/' in stripped:
                in_block_comment = False
            continue

        if not is_code_line(line):
            continue

        # Skip string literals (very rough: skip lines with printf/snprintf)
        # We still apply mutations but skip inside quoted strings
        for op_name, op_desc, pattern, replacement in OPERATORS:
            # Find all non-overlapping matches
            for match in re.finditer(pattern, line):
                start, end = match.span()

                # Skip if inside a string literal (rough heuristic)
                before = line[:start]
                quote_count = before.count('"') - before.count('\\"')
                if quote_count % 2 == 1:
                    continue

                mutated = line[:start] + re.sub(pattern, replacement, line[start:], count=1)
                if mutated != line:
                    mutants.append(Mutation(
                        line_no=i + 1,
                        original=line.rstrip(),
                        mutated=mutated.rstrip(),
                        operator=op_name,
                        description=op_desc,
                    ))
    return mutants


# ---------------------------------------------------------------------------
# Compilation and test execution
# ---------------------------------------------------------------------------

@dataclass
class MutantResult:
    mutation: Mutation
    status: str           # "killed", "survived", "compile_error", "timeout"
    duration_ms: float = 0.0


def run_mutant(
    source_path: Path,
    source_lines: List[str],
    mutation: Mutation,
    compile_cmd: str,
    run_cmd: str,
    work_dir: Path,
    timeout_s: int = 10,
) -> MutantResult:
    """Apply mutation, compile, run tests, restore original."""
    # Write mutated source
    mutated_lines = list(source_lines)
    mutated_lines[mutation.line_no - 1] = mutation.mutated + '\n'

    source_path.write_text(''.join(mutated_lines))

    try:
        t0 = time.monotonic()

        # Step 1: Compile
        result = subprocess.run(
            compile_cmd, shell=True,
            capture_output=True, timeout=timeout_s,
            cwd=str(work_dir),
        )
        if result.returncode != 0:
            return MutantResult(mutation, "compile_error",
                                (time.monotonic() - t0) * 1000)

        # Step 2: Run tests
        result = subprocess.run(
            run_cmd, shell=True,
            capture_output=True, timeout=timeout_s,
            cwd=str(work_dir),
        )
        duration = (time.monotonic() - t0) * 1000

        if result.returncode == 0:
            return MutantResult(mutation, "survived", duration)
        else:
            return MutantResult(mutation, "killed", duration)

    except subprocess.TimeoutExpired:
        return MutantResult(mutation, "timeout",
                            timeout_s * 1000)
    finally:
        # Always restore original
        source_path.write_text(''.join(source_lines))


# ---------------------------------------------------------------------------
# Report generation
# ---------------------------------------------------------------------------

def print_summary(results: List[MutantResult], duration_s: float) -> dict:
    """Print text summary and return stats dict."""
    killed = sum(1 for r in results if r.status == "killed")
    survived = sum(1 for r in results if r.status == "survived")
    compile_err = sum(1 for r in results if r.status == "compile_error")
    timeout = sum(1 for r in results if r.status == "timeout")
    total = len(results)
    testable = killed + survived
    score = (killed / testable * 100) if testable > 0 else 0

    print(f"\n{'='*60}")
    print(f"  MUTATION TESTING RESULTS")
    print(f"{'='*60}")
    print(f"  Total mutants:    {total}")
    print(f"  Killed:           {killed}")
    print(f"  Survived:         {survived}")
    print(f"  Compile errors:   {compile_err} (equivalent/invalid)")
    print(f"  Timeouts:         {timeout}")
    print(f"  Mutation score:   {score:.1f}%")
    print(f"  Duration:         {duration_s:.1f}s")
    print(f"{'='*60}")

    if survived > 0:
        print(f"\n  SURVIVED MUTANTS (test gaps):\n")
        for r in results:
            if r.status == "survived":
                m = r.mutation
                print(f"  Line {m.line_no}: {m.description}")
                print(f"    - {m.original.strip()}")
                print(f"    + {m.mutated.strip()}")
                print()

    return {
        "total": total, "killed": killed, "survived": survived,
        "compile_error": compile_err, "timeout": timeout,
        "score": score, "duration_s": duration_s,
    }


def generate_html_report(
    source_path: str,
    source_lines: List[str],
    results: List[MutantResult],
    stats: dict,
    output_path: Path,
):
    """Generate an HTML mutation testing report."""
    # Build per-line annotations
    line_annotations: dict[int, List[MutantResult]] = {}
    for r in results:
        ln = r.mutation.line_no
        line_annotations.setdefault(ln, []).append(r)

    survived_lines = {r.mutation.line_no for r in results if r.status == "survived"}
    killed_lines = {r.mutation.line_no for r in results if r.status == "killed"}

    source_name = os.path.basename(source_path)

    lines_html = []
    for i, line in enumerate(source_lines, 1):
        escaped = html.escape(line.rstrip())
        css_class = "line"
        if i in survived_lines:
            css_class += " survived"
        elif i in killed_lines:
            css_class += " killed"

        tooltip = ""
        if i in line_annotations:
            tips = []
            for r in line_annotations[i]:
                icon = {"killed": "X", "survived": "!", "compile_error": "~",
                        "timeout": "T"}.get(r.status, "?")
                tips.append(f"[{icon}] {r.mutation.description} ({r.status})")
            tooltip = f' title="{html.escape(chr(10).join(tips))}"'

        lines_html.append(
            f'<tr class="{css_class}"{tooltip}>'
            f'<td class="ln">{i}</td>'
            f'<td class="code"><pre>{escaped}</pre></td></tr>'
        )

    survived_details = []
    for r in results:
        if r.status == "survived":
            m = r.mutation
            survived_details.append(f"""
            <div class="mutant survived">
                <strong>Line {m.line_no}: {html.escape(m.description)}</strong>
                <span class="badge survived">SURVIVED</span>
                <pre class="diff">- {html.escape(m.original.strip())}
+ {html.escape(m.mutated.strip())}</pre>
            </div>""")

    report_html = f"""<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="utf-8">
<title>Mutation Report: {source_name}</title>
<style>
  :root {{ --bg: #1e1e2e; --fg: #cdd6f4; --green: #a6e3a1; --red: #f38ba8;
           --yellow: #f9e2af; --surface: #313244; --overlay: #45475a; }}
  body {{ font-family: 'SF Mono', 'Fira Code', monospace; background: var(--bg);
          color: var(--fg); margin: 0; padding: 20px; }}
  h1 {{ color: var(--fg); font-size: 1.5em; }}
  .stats {{ display: flex; gap: 20px; margin: 20px 0; flex-wrap: wrap; }}
  .stat {{ background: var(--surface); padding: 16px 24px; border-radius: 8px;
           text-align: center; min-width: 120px; }}
  .stat .value {{ font-size: 2em; font-weight: bold; }}
  .stat .label {{ font-size: 0.85em; opacity: 0.7; margin-top: 4px; }}
  .stat.score .value {{ color: {"var(--green)" if stats["score"] >= 80 else
                                 "var(--yellow)" if stats["score"] >= 60 else
                                 "var(--red)"}; }}
  .stat.killed .value {{ color: var(--green); }}
  .stat.survived .value {{ color: var(--red); }}
  table {{ border-collapse: collapse; width: 100%; margin: 20px 0; }}
  .ln {{ color: #6c7086; text-align: right; padding: 0 12px 0 8px;
         user-select: none; width: 40px; }}
  .code {{ padding: 0; }}
  .code pre {{ margin: 0; padding: 2px 8px; white-space: pre; }}
  tr.killed {{ background: rgba(166, 227, 161, 0.08); }}
  tr.survived {{ background: rgba(243, 139, 168, 0.15); }}
  tr.survived td {{ border-left: 3px solid var(--red); }}
  .mutant {{ background: var(--surface); padding: 12px 16px; border-radius: 6px;
             margin: 8px 0; }}
  .mutant.survived {{ border-left: 4px solid var(--red); }}
  .badge {{ padding: 2px 8px; border-radius: 4px; font-size: 0.8em;
            font-weight: bold; margin-left: 8px; }}
  .badge.survived {{ background: var(--red); color: var(--bg); }}
  .diff {{ background: var(--overlay); padding: 8px 12px; border-radius: 4px;
           margin-top: 8px; font-size: 0.9em; }}
  h2 {{ color: var(--red); margin-top: 30px; }}
  .meta {{ opacity: 0.6; font-size: 0.85em; margin-top: 20px; }}
</style>
</head>
<body>
<h1>Mutation Report: {source_name}</h1>

<div class="stats">
  <div class="stat score">
    <div class="value">{stats["score"]:.1f}%</div>
    <div class="label">Mutation Score</div>
  </div>
  <div class="stat killed">
    <div class="value">{stats["killed"]}</div>
    <div class="label">Killed</div>
  </div>
  <div class="stat survived">
    <div class="value">{stats["survived"]}</div>
    <div class="label">Survived</div>
  </div>
  <div class="stat">
    <div class="value">{stats["total"]}</div>
    <div class="label">Total Mutants</div>
  </div>
  <div class="stat">
    <div class="value">{stats["duration_s"]:.1f}s</div>
    <div class="label">Duration</div>
  </div>
</div>

{"<h2>Survived Mutants (Test Gaps)</h2>" + chr(10).join(survived_details) if survived_details else "<h2 style='color:var(--green)'>All mutants killed!</h2>"}

<h2>Source: {source_name}</h2>
<table>
{''.join(lines_html)}
</table>

<div class="meta">
  Generated by SmartEVSE mutation testing tool &mdash;
  {stats["total"]} mutants, {stats["duration_s"]:.1f}s
</div>
</body>
</html>"""

    output_path.parent.mkdir(parents=True, exist_ok=True)
    output_path.write_text(report_html)
    print(f"\n  HTML report: {output_path}")


# ---------------------------------------------------------------------------
# Main
# ---------------------------------------------------------------------------

def main():
    parser = argparse.ArgumentParser(
        description="Mutation testing for SmartEVSE C modules")
    parser.add_argument("--source", required=True,
                        help="C source file to mutate")
    parser.add_argument("--test", nargs='+', default=None,
                        help="Test source file(s) — each compiled as separate binary")
    parser.add_argument("--extra-src", nargs='*', default=None,
                        help="Extra source files to link with each test")
    parser.add_argument("--build-cmd", default=None,
                        help="Custom build command (overrides --test/--cc/--cflags)")
    parser.add_argument("--run-cmd", default=None,
                        help="Custom run command (overrides --test)")
    parser.add_argument("--build-dir", default="build-mutate",
                        help="Build output directory")
    parser.add_argument("--cc", default="cc",
                        help="C compiler (default: cc)")
    parser.add_argument("--cflags", default="-std=c11 -Wall -O0 -g -DEVSE_TESTING",
                        help="Compiler flags")
    parser.add_argument("--includes", default="-Iinclude -I../../src",
                        help="Include paths")
    parser.add_argument("--report", default=None,
                        help="HTML report output path")
    parser.add_argument("--timeout", type=int, default=10,
                        help="Timeout per mutant (seconds)")
    parser.add_argument("--operators", default=None,
                        help="Comma-separated operator names (default: all)")
    parser.add_argument("--json", default=None,
                        help="JSON results output path")
    parser.add_argument("--threshold", type=float, default=0,
                        help="Minimum mutation score (exit 1 if below)")
    args = parser.parse_args()

    source_path = Path(args.source).resolve()

    if not source_path.exists():
        print(f"Error: source file not found: {source_path}", file=sys.stderr)
        sys.exit(1)

    # Read source
    source_lines = source_path.read_text().splitlines(keepends=True)
    print(f"Source: {source_path.name} ({len(source_lines)} lines)")

    # Generate mutants
    mutants = generate_mutants(source_lines)
    if args.operators:
        allowed = set(args.operators.split(','))
        mutants = [m for m in mutants if m.operator in allowed]

    print(f"Generated {len(mutants)} mutants")

    if not mutants:
        print("No mutants generated. Check source file and operators.")
        sys.exit(0)

    # Working directory is where the script is run from (test/native/)
    work_dir = Path.cwd()

    # Build directory (relative to work_dir)
    build_dir = work_dir / args.build_dir
    build_dir.mkdir(parents=True, exist_ok=True)

    # Build compile/run commands
    if args.build_cmd and args.run_cmd:
        # Custom commands mode
        compile_cmd = args.build_cmd
        run_cmd = args.run_cmd
    elif args.test:
        # Auto-generate compile+run for each test file, chained with &&.
        # Quote every path so that working directories with spaces (e.g.
        # "EVSE Team 2") don't get split by the shell.
        from shlex import quote as _q
        extra = ""
        if args.extra_src:
            extra = " " + " ".join(_q(str(Path(s).resolve())) for s in args.extra_src)

        compile_parts = []
        run_parts = []
        for test_file in args.test:
            test_path = Path(test_file).resolve()
            if not test_path.exists():
                print(f"Error: test file not found: {test_path}", file=sys.stderr)
                sys.exit(1)
            binary = build_dir / f"test_{test_path.stem}"
            compile_parts.append(
                f"{args.cc} {args.cflags} {args.includes} "
                f"-o {_q(str(binary))} {_q(str(test_path))} {_q(str(source_path))}{extra}"
            )
            run_parts.append(_q(str(binary)))

        compile_cmd = " && ".join(compile_parts)
        run_cmd = " && ".join(run_parts)
    else:
        print("Error: provide --test or --build-cmd/--run-cmd", file=sys.stderr)
        sys.exit(1)

    test_count = len(args.test) if args.test else 1
    if test_count > 1:
        print(f"Testing with {test_count} test suites per mutant")

    # Verify baseline passes
    print("Verifying baseline (unmodified source)... ", end="", flush=True)
    result = subprocess.run(f"{compile_cmd} && {run_cmd}", shell=True,
                            capture_output=True, timeout=60, cwd=str(work_dir))
    if result.returncode != 0:
        print("FAIL")
        print("Baseline test fails! Fix tests before running mutation testing.",
              file=sys.stderr)
        if result.stderr:
            print(result.stderr.decode(errors='replace')[-500:], file=sys.stderr)
        sys.exit(1)
    print("OK")

    # Run mutants
    results: List[MutantResult] = []
    t_start = time.monotonic()

    for i, mutation in enumerate(mutants, 1):
        status_char = {'killed': 'X', 'survived': '.', 'compile_error': 'E',
                       'timeout': 'T'}

        r = run_mutant(source_path, source_lines, mutation,
                       compile_cmd, run_cmd, work_dir, args.timeout)
        results.append(r)

        c = status_char.get(r.status, '?')
        sys.stdout.write(c)
        if i % 50 == 0:
            sys.stdout.write(f" [{i}/{len(mutants)}]\n")
        sys.stdout.flush()

    duration = time.monotonic() - t_start
    print()

    # Summary
    stats = print_summary(results, duration)

    # HTML report
    if args.report:
        generate_html_report(
            str(source_path), source_lines, results, stats,
            Path(args.report),
        )

    # JSON output
    if args.json:
        json_path = Path(args.json)
        json_path.parent.mkdir(parents=True, exist_ok=True)
        json_data = {
            "source": str(source_path),
            "stats": stats,
            "mutants": [
                {
                    "line": r.mutation.line_no,
                    "operator": r.mutation.operator,
                    "description": r.mutation.description,
                    "original": r.mutation.original.strip(),
                    "mutated": r.mutation.mutated.strip(),
                    "status": r.status,
                    "duration_ms": r.duration_ms,
                }
                for r in results
            ],
        }
        json_path.write_text(json.dumps(json_data, indent=2))
        print(f"  JSON report: {json_path}")

    # Threshold check (for CI)
    if args.threshold > 0 and stats["score"] < args.threshold:
        print(f"\n  FAIL: mutation score {stats['score']:.1f}% "
              f"< threshold {args.threshold:.1f}%")
        sys.exit(1)


if __name__ == "__main__":
    main()
