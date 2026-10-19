# Medical Device Agent Skills

<p align="center">
  <img src="assets/meme.jpg" alt="Medical Device Skills Meme" width="400"/>
</p>

[![Skills](https://img.shields.io/badge/Skills-59-blue)](https://github.com)
[![License](https://img.shields.io/badge/License-MIT-green)](LICENSE)
[![IEC 62304](https://img.shields.io/badge/IEC_62304-Aligned-orange)](skills/meddev-iec-62304/)

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

## Install

Choose either the shared installer (individual skills) or a native plugin (the full collection). Avoid installing both, which can show duplicate skills.

### One command for Claude Code, Codex, and Cursor

Requires Node.js and npm. Run from the project where you want the skills:

```bash
npx skills add AminAlam/meddev-agent-skills -a claude-code -a codex -a cursor
```

Select skills interactively. Add `-g` to install across your projects. Preview available skills:

```bash
npx skills add AminAlam/meddev-agent-skills --list
```

For example, install the lifecycle hub and its risk-management prerequisite:

```bash
npx skills add AminAlam/meddev-agent-skills --skill meddev-iec-62304 --skill meddev-iso-14971 -a claude-code -a codex -a cursor
```

### Claude Code plugin

Run inside Claude Code:

```text
/plugin marketplace add AminAlam/meddev-agent-skills
/plugin install meddev-agent-skills@meddev-agent-skills
```

Restart the session if the skills do not appear. Invoke a skill with `/meddev-agent-skills:meddev-iec-62304` or describe the relevant task.

### Codex plugin

With a current Codex CLI:

```bash
codex plugin marketplace add AminAlam/meddev-agent-skills
codex plugin add meddev-agent-skills@meddev-agent-skills
```

Restart Codex after installation. In desktop versions with a Plugins directory, select **Medical Device Agent Skills** as the marketplace source and install the plugin. If your version does not provide these plugin commands, use the shared installer above. Invoke an installed skill with `$meddev-iec-62304` or describe the relevant task.

### Cursor plugin

Open **Customize → From GitHub Repository** and enter:

```text
https://github.com/AminAlam/meddev-agent-skills
```

Install **meddev-agent-skills** from the imported marketplace. The skills appear in Customize. If your Cursor version does not offer repository import, use the shared installer above.

### Use and update

Ask, for example: “Use the IEC 62304 lifecycle skill to review our software development plan.” Skills are selected by their descriptions; installing the collection does not load every skill body into each conversation.

The full plugin includes all prerequisites. When installing selected skills, also select the prerequisites listed in each skill's `metadata.prerequisites`; native tools do not automatically resolve those custom IDs. The [skill catalog](SKILLS.md) maps IDs to installable names.

Update shared-installer skills with `npx skills update`. For native plugins, refresh the marketplace and use the tool's plugin update controls. Maintainers should increment the plugin version when releasing changes.

Sources: [Skills CLI](https://github.com/vercel-labs/skills), [Claude Code marketplaces](https://code.claude.com/docs/en/plugin-marketplaces), [Codex plugins](https://developers.openai.com/plugins/build/plugins), [Cursor repository installation](https://cursor.com/docs/skills).

## Quick Start

1. Install relevant skills or the full plugin using one route above.
2. Select guidance by domain, jurisdiction, and safety class.
3. Follow the verification checklist when writing or reviewing code.
4. Maintain traceability: Requirements → Design → Code → Tests.
5. Reference `examples/` for patterns with annotations.

For custom integrations and metadata filtering, see [Agent Integration](AGENT_INTEGRATION.md). For publication and local checks, see [Distribution](DISTRIBUTION.md).

---

## Skill Index

### Regulatory
| Skill | Description |
|-------|-------------|
| [IEC 62304](skills/meddev-iec-62304/) | Software lifecycle hub by class (A/B/C); Clauses 4–9 |
| [IEC 62304 Software Risk](skills/meddev-iec-62304-software-risk/) | Clause 7 software risk management process |
| [IEC 62304 Legacy Software](skills/meddev-iec-62304-legacy-software/) | Amendment A1 legacy software pathway (4.4) |
| [ISO 14971](skills/meddev-iso-14971/) | Risk management integration, hazard controls, traceability |
| [FDA Premarket](skills/meddev-fda-premarket/) | Submission software documentation, SBOM, cybersecurity |
| [FDA 820 Design Controls](skills/meddev-fda-820-design-controls/) | 21 CFR 820.30, DHF, verification vs validation, ISO 13485 slice |
| [EU MDR](skills/meddev-eu-mdr/) | MDR-specific software expectations and Rule 11 |
| [IEC 62366 Usability](skills/meddev-iec-62366-usability/) | Formative/summative evaluation, use-related risk, UI verification |
| [SaMD Clinical Evaluation](skills/meddev-samd-clinical-evaluation/) | Intended use, IMDRF category, clinical evidence, CER linkage |
| [AI/ML Device Software](skills/meddev-ai-ml-medical-device-software/) | GMLP, data governance, PCCP, drift monitoring, model SOUP |
| [Postmarket & Labeling](skills/meddev-postmarket-labeling-ifu/) | Complaints, vigilance, recalls/FSCA, IFU and on-device labeling |
| [IEC 62443](skills/meddev-iec-62443/) | Industrial cybersecurity for connected devices |
| [21 CFR Part 11](skills/meddev-21-cfr-part-11/) | Electronic records/signatures, audit trails |

### Architecture
| Skill | Description |
|-------|-------------|
| [Safety Classification](skills/meddev-safety-classification/) | Applying class to architecture, segregation, testing |
| [Separation of Concerns](skills/meddev-separation-of-concerns/) | Partitioning safety-critical boundaries |
| [State Machines](skills/meddev-state-machines/) | Safe states, transitions, testing patterns |
| [Fault Tolerance](skills/meddev-fault-tolerance/) | Detection, degradation, watchdog, recovery |
| [Defensive Design](skills/meddev-defensive-design/) | Input/output validation, assertions, error handling |

### Firmware
| Skill | Description |
|-------|-------------|
| [Embedded C](skills/meddev-embedded-c/) | MISRA-C aligned embedded guidance and examples |
| [Embedded C++](skills/meddev-embedded-cpp/) | Controlled C++ feature set for devices |
| [RTOS Patterns](skills/meddev-rtos-patterns/) | Tasks, priorities, IPC, timing, inversion avoidance |
| [Memory Management](skills/meddev-memory-management/) | Static allocation, pools, MPU usage |
| [Power Management](skills/meddev-power-management/) | Sleep/wake, battery monitoring, graceful shutdown |
| [Interrupt Handling](skills/meddev-interrupt-handling/) | ISR structure, critical sections, testing |
| [Hardware Abstraction](skills/meddev-hardware-abstraction/) | HAL layering and testability |

### Connectivity
| Skill | Description |
|-------|-------------|
| [BLE Medical](skills/meddev-ble-medical/) | Secure BLE services for PHI-bearing devices |
| [WiFi Medical](skills/meddev-wifi-medical/) | WPA3/enterprise, cert management, coexistence |
| [USB Medical](skills/meddev-usb-medical/) | Class selection, enumeration, safety |
| [Interoperability](skills/meddev-interoperability/) | HL7 FHIR/IHE, terminology, API design |

### Security
| Skill | Description |
|-------|-------------|
| [Authentication](skills/meddev-authentication/) | User/device auth, sessions, RBAC |
| [Encryption](skills/meddev-encryption/) | Algorithms, KDFs, data at rest/in transit |
| [Secure Boot](skills/meddev-secure-boot/) | Boot chain, signatures, rollback protection |
| [Secure OTA](skills/meddev-secure-ota/) | Signed updates, atomicity, rollback, server hardening |
| [Key Management](skills/meddev-key-management/) | Generation, storage, rotation, revocation |
| [Threat Modeling](skills/meddev-threat-modeling/) | STRIDE, attack surface, control mapping |

### Testing
| Skill | Description |
|-------|-------------|
| [Unit Testing](skills/meddev-unit-testing/) | Frameworks, coverage by class, embedded mocks |
| [Integration Testing](skills/meddev-integration-testing/) | HW/SW integration, interfaces, environments |
| [Static Analysis](skills/meddev-static-analysis/) | Tools, MISRA configs, triage workflow |
| [Dynamic Analysis](skills/meddev-dynamic-analysis/) | Runtime checks, thread safety, profiling |
| [Fuzz Testing](skills/meddev-fuzz-testing/) | Inputs/protocol fuzzing, crashes, security focus |
| [Code Coverage](skills/meddev-code-coverage/) | Metrics (stmt/branch/MC/DC), CI integration |
| [Hardware-in-Loop](skills/meddev-hardware-in-loop/) | Fixtures, automation, timing, parallelism |

### Documentation
| Skill | Description |
|-------|-------------|
| [Code Comments](skills/meddev-code-comments/) | Traceability annotations, risk/test tags |
| [Design Docs](skills/meddev-design-docs/) | SAD/SDD, interfaces, SOUP docs (5.3–5.4) |
| [Software Requirements](skills/meddev-software-requirements/) | 5.2 requirements analysis and verification |
| [Test Docs](skills/meddev-test-docs/) | Plans/protocols/reports, 5.7.5 and 9.8 records |
| [Traceability](skills/meddev-traceability/) | Matrices, bidirectional links, 7.3.3 hazard chain |
| [Inline Docs](skills/meddev-inline-docs/) | Intentful inline comments, trace tags, API notes |
| [Change Control](skills/meddev-change-control/) | Change requests, impact, approvals (8.2) |
| [Software Configuration Mgmt](skills/meddev-software-configuration-management/) | Clause 8 identification, baselines, history |
| [Problem Resolution](skills/meddev-problem-resolution/) | Clause 9 problem reports, trends, closure |
| [Software Maintenance](skills/meddev-software-maintenance/) | Clause 6 post-release maintenance process |
| [AI-Assisted Dev Governance](skills/meddev-ai-assisted-development-governance/) | LLM coding policy, review, CSA-style evidence for agent output |

### Data
| Skill | Description |
|-------|-------------|
| [PHI Handling](skills/meddev-phi-handling/) | PHI identification, de-ID, encryption, retention |
| [Data Integrity](skills/meddev-data-integrity/) | CRC/ECC, validation, storage/transit integrity |
| [Audit Logging](skills/meddev-audit-logging/) | What/how to log, protection, retention |

### CI/CD
| Skill | Description |
|-------|-------------|
| [Pipeline Design](skills/meddev-pipeline-design/) | Regulated pipeline stages, artifacts, audit trail |
| [Automated Testing](skills/meddev-automated-testing/) | Strategy, hardware integration, flake handling |
| [Release Management](skills/meddev-release-management/) | Versioning, branches, verification, monitoring |

---

## Disclaimer

> These skills **supplement, not replace**, reading the actual standards and guidance. They paraphrase obligations by clause reference only and do **not** reproduce copyrighted standard text. Obtain and use your own licensed copies of IEC, ISO, FDA, and EU documents for authoritative review. Interpretations are noted; always verify with official documents and your QA/RA sign-off. Jurisdictional differences (FDA vs EU MDR) are called out where relevant.

## Contributing

See [`CONTRIBUTING.md`](CONTRIBUTING.md) for how to propose or update skills. Quality requires citations to standards, runnable code examples, and verification criteria. Regulatory/domain expert review is required for merges.

## License

MIT License — see [`LICENSE`](LICENSE).
