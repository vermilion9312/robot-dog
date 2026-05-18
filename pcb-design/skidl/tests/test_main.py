import main


def test_main_returns_project_summary():
    summary = main.run()

    assert summary["name"] == "robot-dog-controller"
    assert summary["servo_count"] == 12
    assert "servo_connectors" in summary["blocks"]
    assert ("J_SERVO_01", "PWM", "PWM_SERVO_01") in summary["connections"]
