# Plan: contextual help links in the Web UI

Add documentation links throughout the Web UI so users can reach the
right docs page from the field or section they're looking at.

---

## UX pattern

A small **?** icon next to each section header (and selectively next to
individual fields that cause the most confusion). Clicking opens the
relevant docs page on GitHub in a new tab.

```html
<a href="https://github.com/basmeerman/SmartEVSE-3.5/blob/master/docs/<page>.md#<anchor>"
   target="_blank" rel="noopener" class="help-link" title="Documentation">?</a>
```

### CSS (add to `style.css` or inline `<style>` block)

```css
.help-link {
  display: inline-flex;
  align-items: center;
  justify-content: center;
  /* 44×44 px minimum touch target per Apple/Google guidelines, but
     visually only 1.3em circle. The outer tap area is padded. */
  min-width: 44px; min-height: 44px;
  width: 1.3em; height: 1.3em;
  border-radius: 50%;
  background: var(--bg3, #e0e0e0);
  color: var(--fg, #333);
  font-size: .7rem;
  font-weight: 600;
  text-decoration: none;
  margin-left: .3em;
  vertical-align: middle;
  opacity: .55;
  -webkit-tap-highlight-color: transparent;
}
.help-link:hover,
.help-link:active { opacity: 1; background: var(--accent, #1976d2); color: #fff; }

/* Footer help bar */
.footer-help {
  text-align: center;
  padding: 12px 8px;
  font-size: .8rem;
  color: var(--fg2, #666);
  border-top: 1px solid var(--bg3, #e0e0e0);
  margin-top: 16px;
}
.footer-help a { color: var(--accent, #1976d2); text-decoration: none; }
.footer-help a:hover { text-decoration: underline; }

/* Stack footer links vertically on narrow screens */
@media (max-width: 480px) {
  .footer-help { font-size: .75rem; line-height: 2; }
  .footer-help .sep { display: none; }
  .footer-help a { display: block; padding: 6px 0; }
}
```

Key responsive points:
- **44 px minimum touch target** on the help icon — meets Apple HIG and
  Material Design touch-target guidelines. The visual circle stays small
  (1.3 em) but the tappable area extends via `min-width`/`min-height`.
- **Footer stacks vertically** on screens narrower than 480 px (typical
  phone portrait). Each link becomes a full-width tap row.
- **`-webkit-tap-highlight-color: transparent`** removes the blue flash
  on iOS Safari when tapping a link.
- **No extra assets, no JS needed** for the responsive behaviour.

---

## Section-level links (one per collapsible card)

Each section header gets a **?** linking to the most relevant guide
section. These are the highest-value links — a user who doesn't know
what a section does can click through to an explanation.

| Section | Link target | Anchor |
|---|---|---|
| Mode selection (OFF / PAUSE / NORMAL / SOLAR / SMART) | `guide-owner.md` | `#2-the-five-modes` |
| Solar settings (Start Current, Max Import, Stop Time) | `solar-smart-stability.md` | `#new-settings` |
| Override Current + Schedule | `guide-owner.md` | `#3-starting-a-charge-session` |
| Mains phase detail | `guide-installer.md` | `#7-meter-selection` |
| EV meter | `guide-installer.md` | `#7-meter-selection` |
| Home battery | `guide-integrator.md` | `#5-feeding-mains-current-from-home-assistant-em_api` |
| Load balancing node overview | `guide-owner.md` | `#9-multi-charger-setup-masterslave` |
| Load balancing priority / scheduling | `priority-scheduling.md` | (top) |
| Capacity tariff | `guide-owner.md` | `#7-common-adjustments` |
| LCD remote | `guide-owner.md` | `#1-the-two-interfaces-youll-actually-use` |
| MQTT configuration | `guide-integrator.md` | `#3-home-assistant-via-mqtt` |
| OCPP configuration | `guide-integrator.md` | `#6-ocpp-backends` |
| Diagnostics | `troubleshooting.md` | `#11-capturing-a-debug-log` |
| Firmware update page | `guide-owner.md` | `#6-firmware-updates` |
| EV state / SoC | `mqtt-home-assistant.md` | `#soc-injection-via-mqtt` |
| Cable lock / LCD lock | `guide-owner.md` | `#8-access-control` |

---

## Field-level links (selective — only confusion-prone fields)

Not every field needs its own link. Only fields that generate repeated
questions in the Tweakers thread or issue tracker.

| Field | Link target | Why |
|---|---|---|
| `solar_start_current` | `solar-smart-stability.md#current-regulation` | "Why doesn't solar mode start?" — most common solar complaint |
| `solar_stop_time` | `solar-smart-stability.md#current-regulation` | "Why does it cycle on/off?" |
| `solar_max_import_current` | `solar-smart-stability.md#current-regulation` | "What does ImportCurrent actually do?" |
| `mode_override_current` | `guide-owner.md#3-starting-a-charge-session` | "How do I charge at a specific current?" |
| `capacity_limit_input` | `configuration.md` | Belgian capacity tariff is unfamiliar outside BE |
| `mqtt_host` | `guide-integrator.md#setup` | MQTT connection troubleshooting entry |
| `mqtt_tls` | `guide-integrator.md#tls` | TLS misconfiguration common |
| `mqtt_change_only` | `guide-integrator.md#change-only-publishing` | Users toggle this and lose data visibility |
| `ocpp_backend_url` | `guide-integrator.md#setup-1` | Provider URL format varies |
| `ocpp_auth_key` | `security.md#4-secret-redaction-in-get-settings` | "Why is my password showing bullets?" |
| `enable_ocpp` | `guide-integrator.md#6-ocpp-backends` | "Do I need OCPP?" |
| `prio_strategy` | `priority-scheduling.md` | Priority semantics not obvious |
| `rotation_interval` | `priority-scheduling.md` | Same |
| `idle_timeout` | `priority-scheduling.md` | Same |
| `diag_profile` | `troubleshooting.md#11-capturing-a-debug-log` | "Which profile should I pick?" |

---

## Footer help link

Add a persistent link in the page footer:

```html
<div class="footer-help">
  <a href="https://github.com/basmeerman/SmartEVSE-3.5/blob/master/docs/guide-owner.md"
     target="_blank" rel="noopener">📖 Documentation</a>
  ·
  <a href="https://gathering.tweakers.net/forum/list_messages/1648387"
     target="_blank" rel="noopener">💬 Community (NL)</a>
  ·
  <a href="https://github.com/basmeerman/SmartEVSE-3.5/issues"
     target="_blank" rel="noopener">🐛 Report issue</a>
</div>
```

This gives every page a "where do I go for help" fallback regardless of
which section they're looking at.

---

## Update page (`update2.html`)

Add one help link in the "CUSTOM FLASHING" section pointing to
`guide-owner.md#6-firmware-updates` and a second pointing to
`security.md#7-firmware-signature-verification` for the signed-firmware
explanation.

---

## Implementation approach

### Where the links live

All links are plain `<a>` tags in `index.html` and `update2.html`. No
JS needed. The base URL is a single constant at the top of `app.js`:

```js
var DOCS_BASE = 'https://github.com/basmeerman/SmartEVSE-3.5/blob/master/docs/';
```

Section-header links can be generated in JS from a mapping table so
adding/removing links doesn't require HTML edits:

```js
var HELP_LINKS = {
  'mqtt_config':     'guide-integrator.md#3-home-assistant-via-mqtt',
  'ocpp_config':     'guide-integrator.md#6-ocpp-backends',
  'diag_section':    'troubleshooting.md#11-capturing-a-debug-log',
  // ...
};
```

On DOMContentLoaded, walk the map and inject a `<a class="help-link">?</a>`
next to each matching element. Keeps the HTML clean and the link mapping
in one place.

### What to regenerate

After editing `index.html` / `update2.html` / `app.js`, regenerate
`packed_fs.c` via `pio run -e release`. Commit both source and packed.

---

## Scope estimate

| Work item | Files touched | Lines | Effort |
|---|---|---|---|
| CSS for `.help-link` | `index.html` | ~10 | trivial |
| `DOCS_BASE` + `HELP_LINKS` map in `app.js` | `app.js` | ~40 | small |
| JS injection loop (DOMContentLoaded) | `app.js` | ~15 | small |
| Section-header link targets in HTML (if not JS-injected) | `index.html` | ~16 ids | small |
| Field-level link targets | `index.html` or `app.js` | ~15 entries | small |
| Footer help bar | `index.html` | ~5 | trivial |
| Update page links | `update2.html` | ~3 | trivial |
| Regenerate `packed_fs.c` | auto | — | — |
| Verify no broken anchors | manual | — | 30 min |

**Total estimate: ~100 lines of JS/HTML/CSS, one PR, ~2 hours including
anchor verification.**

---

## Execution order

1. Add CSS + `DOCS_BASE` + footer help bar → visual baseline, shippable.
2. Add section-level `HELP_LINKS` map + injection loop → highest value.
3. Add field-level links for the 15 confusion-prone fields → polish.
4. Update `update2.html` → small tail.
5. Regenerate `packed_fs.c`, build, verify on device.

Steps 1–2 cover 80% of the user-facing value. Step 3 is refinement.

---

## Anchor verification

Before shipping, verify that every `#anchor` in the mapping resolves to
an actual heading in the target docs page. GitHub auto-generates anchors
from heading text (lowercase, hyphens, strip special chars). Run a
script or manual check:

```bash
for page in docs/guide-owner.md docs/guide-integrator.md ...; do
  grep '^#' "$page" | sed 's/^#* //' | tr 'A-Z ' 'a-z-' | tr -cd 'a-z0-9-\n'
done
```

Compare against the `HELP_LINKS` values. Fix any mismatches before merge.

---

## Responsive and cross-platform requirements

The existing Web UI has no `@media` queries — layout relies on
`flex-wrap` and `max-width`. That works surprisingly well on phones,
but the help links introduce new elements that need explicit mobile
consideration.

### Touch targets

Apple HIG and Material Design both specify **44 × 44 px minimum** for
tappable elements. The `?` icon is visually small (1.3 em ≈ 18 px at
default font size) but the CSS gives it a **44 × 44 px minimum
touch area** via `min-width` / `min-height`. Users can tap accurately
on iPhone SE, Android phones, tablets.

### Footer on narrow screens

The 3-link footer bar (`Documentation · Community · Report issue`)
wraps to vertical stack on screens narrower than 480 px. Each link
becomes a full-width row with 6 px padding — easy to tap without
hitting the wrong one.

### Browser compatibility

| Browser | Concern | Handled by |
|---|---|---|
| iOS Safari | Blue tap-flash on links | `-webkit-tap-highlight-color: transparent` |
| iOS Safari | viewport bounce / zoom on double-tap | `<meta name="viewport">` already present with `width=device-width, initial-scale=1` |
| Android Chrome | 300 ms tap delay (old devices) | Modern Chrome + viewport meta eliminates this by default |
| Desktop Firefox / Chrome / Edge / Safari | Hover state for `?` icon | `:hover` with accent color |
| Windows + high DPI | Crisp icon at 125/150% scaling | `em`-based sizing scales with font, not with pixels |

### Existing `title=` tooltips

The current UI uses `title=` on ~20 fields. On **desktop** these show
as browser-native hover tooltips. On **mobile** they do nothing (or
require a long-press on some browsers). The help links are the mobile
solution — a tap opens the docs page directly, replacing the
mouse-only tooltip with an always-available link.

### What to test before shipping

- [ ] iPhone SE (smallest common iOS screen, 375 px wide): all section
  headers visible, help icons tappable without accidental neighbouring
  tap, footer readable.
- [ ] Android phone (360–412 px typical): same checks.
- [ ] iPad / Android tablet (768+ px): layout should be indistinguishable
  from desktop.
- [ ] Desktop browser at 100% and 150% zoom: icons don't overflow
  section headers, footer stays in view.
- [ ] Dark mode: help icons inherit theme variables (`var(--bg3)`,
  `var(--accent)`) — verify contrast is sufficient in both themes.

---

## What this plan does NOT cover

- Inline contextual help (expandable text within the UI). That's a
  larger UX change and the docs pages already serve that role.
- Tooltips beyond what already exists. Existing `title=` attributes are
  kept; we add links, not replace tooltips.
- Localisation of help links (NL vs EN). Links point to English docs;
  the Tweakers link in the footer is the NL community resource.
- Full responsive audit of the existing UI layout (that's a larger
  scope — the existing flex-wrap approach works for most screens, but a
  dedicated responsive pass with breakpoints for 320/480/768/1024 px
  would be a separate effort).
