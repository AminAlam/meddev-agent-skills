---
skill_id: SEC-THREAT-MODELING
version: 1.0.0
last_updated: 2026-01-04
applies_to: [Class A, Class B, Class C]
jurisdiction: [Global]
prerequisites: [REG-ISO14971]
---

# Threat Modeling for Medical Devices

## Purpose
Identify, prioritize, and mitigate security threats for medical devices, integrating with risk management and informing control selection.

## When to Apply
- New features, interfaces, protocols, or deployment models.
- Architectural changes or introduction of third-party components.
- Periodic review or after security incidents.

## Requirements (testable)
1. Scope & Assets: Define assets (PHI, credentials, control channels) and trust boundaries. Rationale: focus analysis.
2. Methodology: Apply STRIDE (or equivalent) to data flows/components; document threats and mitigations. Rationale: structured coverage.
3. Prioritization: Rate threats by likelihood/impact; align with risk criteria; focus on high/critical. Rationale: actionable output.
4. Controls Mapping: Map threats to controls (auth, crypto, logging, rate limits, updates); ensure ownership and implementation path. Rationale: closure.
5. Validation: Include verification activities (tests, pen/DAST/fuzz) for high-risk threats. Rationale: evidence of mitigation.
6. Update & Trace: Update threat model on changes; keep versioned; link to requirements and tests. Rationale: current and auditable.

## Recommended Practices
- Use DFDs to visualize flows; include physical ports and debug interfaces.
- Consider safety impacts of security failures (link to ISO 14971 hazards).
- Capture abuse cases (e.g., radio flooding, spoofing, replay).
- Keep a concise threat model summary with top risks for quick consumption.

## Patterns
Threat entry (YAML):
```yaml
# REQ-THM-01
threat_id: TH-07
component: BLE Control Service
stride: Spoofing
description: Attacker pairs via Just Works and sends control commands.
mitigations:
  - REQ-BLE-SEC-01 (LESC + MITM)
  - REQ-AUTH-RBAC-03 (role checks)
verification:
  - TEST-BLE-05 (pairing)
  - PEN-02 (spoof attempt)
```

DFD elements:
```text
External: Clinician App
Process: Device Control Task
Data Store: Config Flash (encrypted)
Boundary: BLE link (encrypted/authenticated)
```

## Anti-Patterns (risks)
- No threat model or outdated one -> risk: missed controls, audit finding.
- Listing threats without mapping to controls -> risk: no mitigation.
- Ignoring verification -> risk: unproven controls.
- Not updating after major change -> risk: stale mitigations.

## Verification Checklist
- [ ] Assets and trust boundaries defined; DFDs updated.
- [ ] STRIDE (or equivalent) applied to components/flows.
- [ ] High/critical threats prioritized with rationale.
- [ ] Threats mapped to implemented controls; owners assigned.
- [ ] Verification (tests/pen/fuzz) planned/executed for high risks.
- [ ] Threat model versioned and updated after changes.

## Traceability
- Threat IDs (`TH-###`) linked to controls (`REQ-###/RISK-CTRL-###`) and tests (`TEST-###`, `PEN-###`, `FUZZ-###`).
- Store threat model artifacts with release; reference in risk management file.

## References
- STRIDE (Microsoft), attack surface reduction concepts.
- FDA Cybersecurity Premarket Guidance (threat modeling).
- IEC 62443 threat concepts (zones/conduits).

## Changelog
- 1.0.0 (2026-01-04): Initial threat modeling skill with STRIDE application, control mapping, and verification linkage.

## Audit History
- **2026-01-04**: Audit performed. Verified:
  - STRIDE methodology correctly attributed to Microsoft
  - DFD-based threat modeling approach accurately described
  - Integration with FDA cybersecurity guidance correctly noted
