"""
Diagnostic algorithm example with simple thresholds.

REQ-DIAG-01: Flag high pressure > 200 kPa.
REQ-DIAG-02: Reject inputs missing required fields.
RISK-CTRL-55: Validate inputs to avoid misdiagnosis.
"""

from typing import Dict, Any

PRESSURE_LIMIT_KPA = 200.0


def run_diagnostics(data: Dict[str, Any]) -> Dict[str, Any]:
    """Return diagnostic result with pass/fail and reasons."""
    # Input validation (RISK-CTRL-55)
    if "pressure_kpa" not in data:
        return {"ok": False, "reason": "missing_pressure", "req": "REQ-DIAG-02"}
    try:
        pressure = float(data["pressure_kpa"])
    except (TypeError, ValueError):
        return {"ok": False, "reason": "bad_pressure_value", "req": "REQ-DIAG-02"}

    if pressure > PRESSURE_LIMIT_KPA:  # REQ-DIAG-01
        return {"ok": False, "reason": "pressure_high", "req": "REQ-DIAG-01"}

    return {"ok": True, "reason": None, "req": "REQ-DIAG-01"}


if __name__ == "__main__":
    print(run_diagnostics({"pressure_kpa": 150.0}))
