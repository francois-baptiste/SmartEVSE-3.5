# Contributing to SmartEVSE

Thank you for your interest in contributing to SmartEVSE! This document provides guidelines for contributing to the project.

## Getting Started

1. Fork the repository on GitHub
2. Clone your fork locally
3. Create a feature branch from `master`

## Development Setup

### Prerequisites

- [PlatformIO](https://platformio.org/) for firmware builds
- GCC (C11) for native tests
- Python 3.10+ for test tooling

### Building Firmware

```bash
# ESP32 v3
pio run -e release -d SmartEVSE-3/

# CH32
pio run -e ch32 -d SmartEVSE-3/
```

### Running Tests

```bash
cd SmartEVSE-3/test/native
make clean test
```

All 265 native tests must pass before submitting a PR.

## Making Changes

### Branch Naming

- `feature/short-description` for new features
- `fix/short-description` for bug fixes
- `docs/short-description` for documentation changes

### Commit Messages

Use clear, concise commit messages:

```
Add solar mode phase switching logic

Implements automatic 3P-to-1P switching when solar surplus drops
below threshold for 10 seconds.
```

- Use imperative mood ("Add", not "Added")
- First line under 72 characters
- Add a blank line and details if needed

### Code Style

- C source files: C11 standard
- Use existing code patterns as reference
- Keep functions focused and testable
- Add SbE annotations (`@feature`, `@req`, `@scenario`, `@given`, `@when`, `@then`) to new test functions

### Testing Requirements

- Add tests for new functionality
- Ensure all existing tests pass (`make clean test`)
- Safety-critical changes (state machine, contactors, current limiting) require thorough test coverage

## Submitting Changes

1. Push your branch to your fork
2. Open a Pull Request against `master`
3. Describe what your changes do and why
4. Reference any related issues
5. Ensure CI checks pass

## Reporting Bugs

Use the [bug report template](https://github.com/dingo35/SmartEVSE-3.5/issues/new?template=bug_report.md) and include:

- Your SmartEVSE hardware version (v3 or v4)
- Firmware version
- Configuration JSON (from the webserver "raw" button)
- Debug log capturing the issue

## Security Vulnerabilities

Please report security vulnerabilities privately. See [SECURITY.md](SECURITY.md) for details.

## License

By contributing, you agree that your contributions will be licensed under the [MIT License](LICENSE).
