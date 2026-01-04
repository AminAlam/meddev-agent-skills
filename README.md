# medical-device-agent-skills

Modular “skill” files for AI coding agents working on medical device software. Each skill captures scoped, actionable guidance (requirements, patterns, anti-patterns, verification) to help agents produce safer, more compliant code without replacing human regulatory review.

## What this repo is
- Curated skill documents aligned to medical device standards and good practices.
- Structured to be machine-readable and agent-friendly (consistent schema, metadata, prerequisites).
- Focused on code-facing guidance: patterns, anti-patterns, checklists, traceability cues.

## Target audience
- Medical device software engineers (embedded, connectivity, cloud).
- QA/RA and safety engineers collaborating with AI-assisted coding.
- Tool builders integrating domain skills into agents (Copilot, Claude, Cursor, custom stacks).

## How to use with AI assistants
- Claude / Cursor / Copilot: load relevant `SKILL.md` files into context; start with `SKILL_SCHEMA.md` to validate structure, then include the specific domain skill (e.g., `regulatory/iec-62304/SKILL.md`).
- Retrieval pipelines: index skill files by metadata (skill_id, jurisdiction, applies_to) for similarity or rules-based selection.
- Custom agents: implement prerequisite chaining (see `prerequisites` in frontmatter) and apply class/jurisdiction filters before prompt injection.

## Skill index
Category | Skill | Description
--- | --- | ---
Regulatory | IEC 62304 | Software lifecycle process controls by class (A/B/C)
Regulatory | ISO 14971 | Risk management integration, hazard controls, traceability
Regulatory | FDA Premarket | Submission software documentation (LoC, SBOM, cybersecurity)
Regulatory | EU MDR | MDR-specific software expectations and Rule 11
Regulatory | IEC 62443 | Industrial cybersecurity for connected devices
Regulatory | 21 CFR Part 11 | Electronic records/signatures, audit trails
Architecture | Safety Classification | Applying class to architecture, segregation, testing
Architecture | Separation of Concerns | Partitioning safety-critical boundaries
Architecture | State Machines | Safe states, transitions, testing patterns
Architecture | Fault Tolerance | Detection, degradation, watchdog, recovery
Architecture | Defensive Design | Input/output validation, assertions, error handling
Firmware | Embedded C | MISRA-C aligned embedded guidance and examples
Firmware | Embedded C++ | Controlled C++ feature set for devices
Firmware | RTOS Patterns | Tasks, priorities, IPC, timing, inversion avoidance
Firmware | Memory Management | Static allocation, pools, MPU usage
Firmware | Power Management | Sleep/wake, battery monitoring, graceful shutdown
Firmware | Interrupt Handling | ISR structure, critical sections, testing
Firmware | Hardware Abstraction | HAL layering and testability
Connectivity | BLE Medical | Secure BLE services for PHI-bearing devices
Connectivity | WiFi Medical | WPA3/enterprise, cert management, coexistence
Connectivity | USB Medical | Class selection, enumeration, safety
Connectivity | Interoperability | HL7 FHIR/IHE, terminology, API design
Security | Authentication | User/device auth, sessions, RBAC
Security | Encryption | Algorithms, KDFs, data at rest/in transit
Security | Secure Boot | Boot chain, signatures, rollback protection
Security | Secure OTA | Signed updates, atomicity, rollback, server hardening
Security | Key Management | Generation, storage, rotation, revocation
Security | Threat Modeling | STRIDE, attack surface, control mapping
Testing | Unit Testing | Frameworks, coverage by class, embedded mocks
Testing | Integration Testing | HW/SW integration, interfaces, environments
Testing | Static Analysis | Tools, MISRA configs, triage workflow
Testing | Dynamic Analysis | Runtime checks, thread safety, profiling
Testing | Fuzz Testing | Inputs/protocol fuzzing, crashes, security focus
Testing | Code Coverage | Metrics (stmt/branch/MC/DC), CI integration
Testing | Hardware-in-Loop | Fixtures, automation, timing, parallelism
Documentation | Code Comments | Traceability annotations, risk/test tags
Documentation | Design Docs | SAD/SDD, interfaces, SOUP docs
Documentation | Test Docs | Plans/protocols/reports, submission formatting
Documentation | Traceability | Matrices, bidirectional links, tool integration
Documentation | Inline Docs | Intentful inline comments, trace tags, API notes
Documentation | Change Control | Change requests, impact, regression, config mgmt
Data | PHI Handling | PHI identification, de-ID, encryption, retention
Data | Data Integrity | CRC/ECC, validation, storage/transit integrity
Data | Audit Logging | What/how to log, protection, retention
CI/CD | Pipeline Design | Regulated pipeline stages, artifacts, audit trail
CI/CD | Automated Testing | Strategy, hardware integration, flake handling
CI/CD | Release Management | Versioning, branches, verification, monitoring

## Quick start
1) Pick relevant skills by domain and jurisdiction (e.g., `regulatory/iec-62304`, `security/secure-boot`, `testing/unit-testing`).  
2) Load the skills into your agent context; apply prerequisite chaining.  
3) Follow the verification checklist when writing/reviewing code.  
4) Keep traceability tags from requirements -> design -> code -> tests.  
5) Use the example projects (`examples/`) for patterns and annotations.  

## Relationship to standards (disclaimer)
These skills supplement, not replace, reading the actual standards and guidance. Interpretations are noted; always verify with official documents and your QA/RA function. Jurisdictional differences (FDA vs EU MDR) are called out where relevant.

## Contributing
See `CONTRIBUTING.md` for how to propose or update skills. Quality requires citations to standards, runnable code examples, and verification criteria. Regulatory/domain expert review is required for merges.

## License
MIT License (see `LICENSE`).
