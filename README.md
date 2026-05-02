# TRACE UAV Development

> Full-stack open-source UAV project spanning airframe aerodynamics, PCB/circuit design,
> embedded firmware, and RF data-link protocols — from airfoils to transistors to the
> data structures flying over the air.

---

## Project Scope

TRACE UAV is an end-to-end open development effort covering:

- **Airframe design** — airfoil geometry, structural layout, and aerodynamic modeling
- **Circuit/PCB design** — flight controller, ESC, power distribution, and RF front-end
- **Firmware & software** — flight control algorithms, sensor fusion, and data structures
- **RF & data-link** — over-the-air protocols, telemetry framing, and link budget design
- **Manufacturing documentation** — assembly guides, BOM, and production notes

---

## Repository Structure
TRACE-UAV/
├── firmware/          # Flight firmware and software (Apache 2.0)
├── hardware/
│   ├── pcb/           # Schematics, Gerbers, BOM (CERN-OHL-W-2.0)
│   └── airframe/      # CAD files, airfoil profiles, structural drawings (CERN-OHL-W-2.0)
└── docs/              # Specifications, guides, research notes (CC BY-SA 4.0)
---

## Licensing

This project uses three licenses applied by directory. **Read this before using any files.**

| Directory | License | SPDX Identifier |
|-----------|---------|-----------------|
| `firmware/` | Apache License 2.0 | `Apache-2.0` |
| `hardware/` | CERN Open Hardware Licence v2 Weakly Reciprocal | `CERN-OHL-W-2.0` |
| `docs/` | Creative Commons Attribution-ShareAlike 4.0 | `CC-BY-SA-4.0` |

### What This Means

**`firmware/` — Apache 2.0**
You may use, modify, and distribute the code, including in commercial products, without releasing your own modifications. You must retain copyright notices and the license file. You receive an explicit patent license from all contributors.

**`hardware/` — CERN-OHL-W-2.0**
You may use, study, modify, and manufacture hardware based on these designs. If you modify and distribute the *design files themselves*, those modifications must also be released under CERN-OHL-W-2.0. Products *built from* these designs do not trigger this requirement.

**`docs/` — CC BY-SA 4.0**
You may share and adapt the documentation for any purpose, including commercially, provided you give attribution and distribute any derivative documentation under the same license.

Full license texts are in the repository root:
- [`LICENSE-APACHE.txt`](./LICENSE-APACHE.txt)
- [`LICENSE-CERN-OHL-W.txt`](./LICENSE-CERN-OHL-W.txt)
- [`LICENSE-CC-BY-SA.txt`](./LICENSE-CC-BY-SA.txt)

### Commercial Licensing

If you require a commercial license that removes open-source obligations (e.g., for proprietary manufacturing or closed-source firmware integration), contact the project maintainer to discuss terms.

---

## Status

> 🚧 Active development — pre-release. No stable version tagged yet.

---

## Contributing

Contributions welcome. By submitting a pull request you agree your contribution will be licensed under the applicable license for the directory it modifies (Apache-2.0 for firmware, CERN-OHL-W-2.0 for hardware, CC-BY-SA-4.0 for docs).

---

## Contact

**Project Lead:** Jared Kusner
**Email:** 
**Location:** Washington, DC

---

*Copyright © 2026 Jared Kusner. All rights reserved under the licenses stated above.*
