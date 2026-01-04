from diagnostic_algorithm import run_diagnostics


# TEST-DIAG-01 covers REQ-DIAG-01
def test_ok_pressure():
    result = run_diagnostics({"pressure_kpa": 150.0})
    assert result["ok"] is True


# TEST-DIAG-02 covers REQ-DIAG-02
def test_missing_pressure():
    result = run_diagnostics({})
    assert result["ok"] is False
    assert result["reason"] == "missing_pressure"


# TEST-DIAG-03 covers REQ-DIAG-01
def test_high_pressure_flags():
    result = run_diagnostics({"pressure_kpa": 250.0})
    assert result["ok"] is False
    assert result["reason"] == "pressure_high"


if __name__ == '__main__':
    test_ok_pressure()
    test_missing_pressure()
    test_high_pressure_flags()
    print('ok')
