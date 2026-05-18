from dataclasses import dataclass

from robot_dog_pcb.connections import PinConnection
from robot_dog_pcb.nets import BoardNets


@dataclass(frozen=True)
class McuBlock:
    nets: BoardNets
    name: str = "mcu"
    part: str = "STM32F103C8T6 Blue Pill"

    @property
    def connections(self) -> list[PinConnection]:
        power_connections = [
            PinConnection("J_BLUEPILL", "3V3", self.nets.mcu_3v3),
            PinConnection("J_BLUEPILL", "GND", self.nets.gnd),
        ]
        pwm_connections = [
            PinConnection("J_BLUEPILL", f"PWM{index:02d}", pwm)
            for index, pwm in enumerate(self.nets.servo_pwm_names, start=1)
        ]
        return power_connections + pwm_connections

    def connection_tuples(self) -> list[tuple[str, str, str]]:
        return [connection.as_tuple() for connection in self.connections]

    def describe(self) -> dict[str, list[str] | str]:
        return {
            "name": self.name,
            "part": self.part,
            "power": self.nets.mcu_3v3,
            "ground": self.nets.gnd,
            "pwm_inputs": self.nets.servo_pwm_names,
        }
