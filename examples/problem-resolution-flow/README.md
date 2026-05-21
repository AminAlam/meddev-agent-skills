# Problem Resolution and Change Control Example

Illustrates IEC 62304 Clause 9 problem resolution linked to Clause 8 change control and Clause 6 maintenance feedback—using repository traceability IDs only (no standard text).

## Scenario

Field complaint: door-open stop latency exceeds 50 ms on firmware v1.2.3.

## Artifacts

| Artifact | ID | Skill |
|----------|-----|-------|
| Problem report | `PR-2026-088` | `DOC-PROBLEM-RES` |
| Change request | `CR-201` | `DOC-CHANGE-CONTROL` |
| Requirement | `REQ-62304-102` | `DOC-SW-REQ` |
| Test | `TEST-415` | `TEST-UNIT` |
| Software risk | `HZ-07`, `RISK-CTRL-19` | `REG-IEC62304-SWRM` |

## Flow

1. **Feedback** (6.2.1): Complaint logged with software version → `PR-2026-088`.
2. **Investigation** (9.2): Root cause race in `pump_control`; safety evaluation via Clause 7 → `CR-201`.
3. **Change control** (8.2): `CR-201` approved; implement fix; re-run `TEST-410`, `TEST-415`.
4. **SCM** (8.1–8.3): Baseline `v1.2.4-rc1` with updated configuration manifest.
5. **Release** (5.8): Release after `CICD-RELEASE` checklist; residual anomalies reviewed.
6. **Records** (9.8): Test record includes version, environment, tester, pass/fail.

## Sample records

See `sample-records.yaml` for minimal YAML examples agents can mirror in a QMS repo.

## Related skills

- `REG-IEC62304`, `DOC-SW-MAINT`, `REG-POSTMKT-LABEL`, `DOC-TEST-DOCS`
