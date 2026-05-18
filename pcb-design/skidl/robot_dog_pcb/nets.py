from dataclasses import dataclass, field


@dataclass(frozen=True)
class BoardNets:
    vbat: str = "VBAT"
    gnd: str = "GND"
    servo_vcc: str = "SERVO_VCC"
    mcu_3v3: str = "MCU_3V3"
    servo_pwm_names: list[str] = field(
        default_factory=lambda: [f"PWM_SERVO_{index:02d}" for index in range(1, 13)]
    )
