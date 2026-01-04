# Medical Device Agent Skills

[![Skills](https://img.shields.io/badge/Skills-37-blue)](https://github.com)
[![License](https://img.shields.io/badge/License-MIT-green)](LICENSE)
[![IEC 62304](https://img.shields.io/badge/IEC_62304-Aligned-orange)](regulatory/iec-62304/)

Modular "skill" files for AI coding agents working on medical device software. Each skill captures scoped, actionable guidance (requirements, patterns, anti-patterns, verification) to help agents produce safer, more compliant code without replacing human regulatory review.

---

## What This Repo Is

- **Curated guidance** aligned to medical device standards (IEC 62304, ISO 14971, FDA, EU MDR)
- **Machine-readable** and agent-friendly (consistent schema, metadata, prerequisites)
- **Code-focused** with patterns, anti-patterns, and verification checklists

## Target Audience

- **Device Engineers** — Embedded, connectivity, cloud developers building medical software
- **QA/RA Engineers** — Quality and regulatory pros collaborating with AI-assisted development  
- **Tool Builders** — Integrating domain skills into Copilot, Claude, Cursor, or custom agents

---

## Quick Start

1. Pick relevant skills by domain and jurisdiction (e.g., `regulatory/iec-62304`, `security/secure-boot`)
2. Load skills into your agent context — start with `SKILL_SCHEMA.md`, then add specific skills
3. Follow the verification checklist when writing/reviewing code
4. Maintain traceability: Requirements -> Design -> Code -> Tests
5. Reference `examples/` for real patterns with annotations

## Using with AI Assistants

**Claude / Cursor / Copilot**: Load relevant `SKILL.md` files into context; include the schema first.

**Retrieval (RAG)**: Index by metadata (`skill_id`, `jurisdiction`, `applies_to`) for similarity search.

**Custom Agents**: Implement prerequisite chaining from YAML frontmatter; filter by class/jurisdiction.

---

## Skill Index

### Regulatory
| Skill | Description |
|-------|-------------|
| [IEC 62304](regulatory/iec-62304/) | Software lifecycle process controls by class (A/B/C) |
| [ISO 14971](regulatory/iso-14971/) | Risk management integration, hazard controls, traceability |
| [FDA Premarket](regulatory/fda-premarket/) | Submission software documentation, SBOM, cybersecurity |
| [EU MDR](regulatory/eu-mdr/) | MDR-specific software expectations and Rule 11 |
| [IEC 62443](regulatory/iec-62443/) | Industrial cybersecurity for connected devices |
| [21 CFR Part 11](regulatory/21-cfr-part-11/) | Electronic records/signatures, audit trails |

### Architecture
| Skill | Description |
|-------|-------------|
| [Safety Classification](architecture/safety-classification/) | Applying class to architecture, segregation, testing |
| [Separation of Concerns](architecture/separation-of-concerns/) | Partitioning safety-critical boundaries |
| [State Machines](architecture/state-machines/) | Safe states, transitions, testing patterns |
| [Fault Tolerance](architecture/fault-tolerance/) | Detection, degradation, watchdog, recovery |
| [Defensive Design](architecture/defensive-design/) | Input/output validation, assertions, error handling |

### Firmware
| Skill | Description |
|-------|-------------|
| [Embedded C](firmware/embedded-c/) | MISRA-C aligned embedded guidance and examples |
| [Embedded C++](firmware/embedded-cpp/) | Controlled C++ feature set for devices |
| [RTOS Patterns](firmware/rtos-patterns/) | Tasks, priorities, IPC, timing, inversion avoidance |
| [Memory Management](firmware/memory-management/) | Static allocation, pools, MPU usage |
| [Power Management](firmware/power-management/) | Sleep/wake, battery monitoring, graceful shutdown |
| [Interrupt Handling](firmware/interrupt-handling/) | ISR structure, critical sections, testing |
| [Hardware Abstraction](firmware/hardware-abstraction/) | HAL layering and testability |

### Connectivity
| Skill | Description |
|-------|-------------|
| [BLE Medical](connectivity/ble-medical/) | Secure BLE services for PHI-bearing devices |
| [WiFi Medical](connectivity/wifi-medical/) | WPA3/enterprise, cert management, coexistence |
| [USB Medical](connectivity/usb-medical/) | Class selection, enumeration, safety |
| [Interoperability](connectivity/interoperability/) | HL7 FHIR/IHE, terminology, API design |

### Security
| Skill | Description |
|-------|-------------|
| [Authentication](security/authentication/) | User/device auth, sessions, RBAC |
| [Encryption](security/encryption/) | Algorithms, KDFs, data at rest/in transit |
| [Secure Boot](security/secure-boot/) | Boot chain, signatures, rollback protection |
| [Secure OTA](security/secure-ota/) | Signed updates, atomicity, rollback, server hardening |
| [Key Management](security/key-management/) | Generation, storage, rotation, revocation |
| [Threat Modeling](security/threat-modeling/) | STRIDE, attack surface, control mapping |

### Testing
| Skill | Description |
|-------|-------------|
| [Unit Testing](testing/unit-testing/) | Frameworks, coverage by class, embedded mocks |
| [Integration Testing](testing/integration-testing/) | HW/SW integration, interfaces, environments |
| [Static Analysis](testing/static-analysis/) | Tools, MISRA configs, triage workflow |
| [Dynamic Analysis](testing/dynamic-analysis/) | Runtime checks, thread safety, profiling |
| [Fuzz Testing](testing/fuzz-testing/) | Inputs/protocol fuzzing, crashes, security focus |
| [Code Coverage](testing/code-coverage/) | Metrics (stmt/branch/MC/DC), CI integration |
| [Hardware-in-Loop](testing/hardware-in-loop/) | Fixtures, automation, timing, parallelism |

### Documentation
| Skill | Description |
|-------|-------------|
| [Code Comments](documentation/code-comments/) | Traceability annotations, risk/test tags |
| [Design Docs](documentation/design-docs/) | SAD/SDD, interfaces, SOUP docs |
| [Test Docs](documentation/test-docs/) | Plans/protocols/reports, submission formatting |
| [Traceability](documentation/traceability/) | Matrices, bidirectional links, tool integration |
| [Inline Docs](documentation/inline-docs/) | Intentful inline comments, trace tags, API notes |
| [Change Control](documentation/change-control/) | Change requests, impact, regression, config mgmt |

### Data
| Skill | Description |
|-------|-------------|
| [PHI Handling](data/phi-handling/) | PHI identification, de-ID, encryption, retention |
| [Data Integrity](data/data-integrity/) | CRC/ECC, validation, storage/transit integrity |
| [Audit Logging](data/audit-logging/) | What/how to log, protection, retention |

### CI/CD
| Skill | Description |
|-------|-------------|
| [Pipeline Design](ci-cd/pipeline-design/) | Regulated pipeline stages, artifacts, audit trail |
| [Automated Testing](ci-cd/automated-testing/) | Strategy, hardware integration, flake handling |
| [Release Management](ci-cd/release-management/) | Versioning, branches, verification, monitoring |

---

## Disclaimer

> These skills **supplement, not replace**, reading the actual standards and guidance. Interpretations are noted; always verify with official documents and your QA/RA function. Jurisdictional differences (FDA vs EU MDR) are called out where relevant.

## Contributing

See [`CONTRIBUTING.md`](CONTRIBUTING.md) for how to propose or update skills. Quality requires citations to standards, runnable code examples, and verification criteria. Regulatory/domain expert review is required for merges.

## License

MIT License — see [`LICENSE`](LICENSE).
