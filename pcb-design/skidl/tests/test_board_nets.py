from robot_dog_pcb import BoardNets


def test_board_nets_creates_power_and_twelve_pwm_names():
    nets = BoardNets()

    assert nets.vbat == "VBAT"
    assert nets.gnd == "GND"
    assert nets.servo_vcc == "SERVO_VCC"
    assert nets.mcu_3v3 == "MCU_3V3"
    assert nets.servo_pwm_names == [
        "PWM_SERVO_01",
        "PWM_SERVO_02",
        "PWM_SERVO_03",
        "PWM_SERVO_04",
        "PWM_SERVO_05",
        "PWM_SERVO_06",
        "PWM_SERVO_07",
        "PWM_SERVO_08",
        "PWM_SERVO_09",
        "PWM_SERVO_10",
        "PWM_SERVO_11",
        "PWM_SERVO_12",
    ]
