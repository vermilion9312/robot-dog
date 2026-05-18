from dataclasses import dataclass

from robot_dog_pcb.connections import PinConnection
from robot_dog_pcb.nets import BoardNets


@dataclass(frozen=True)
class PowerBlock:
    nets: BoardNets
    name: str = "power"

    @property
    def connections(self) -> list[PinConnection]:
        return [
            PinConnection("J_BAT", "1", self.nets.vbat),
            PinConnection("J_BAT", "2", self.nets.gnd),
            PinConnection("J_SERVO_RAIL", "V+", self.nets.servo_vcc),
            PinConnection("J_SERVO_RAIL", "GND", self.nets.gnd),
            PinConnection("J_MCU_RAIL", "3V3", self.nets.mcu_3v3),
            PinConnection("J_MCU_RAIL", "GND", self.nets.gnd),
        ]

    def connection_tuples(self) -> list[tuple[str, str, str]]:
        return [connection.as_tuple() for connection in self.connections]

    def describe(self) -> dict[str, list[str] | str]:
        return {
            "name": self.name,
            "battery_input": self.nets.vbat,
            "rails": [self.nets.vbat, self.nets.gnd, self.nets.servo_vcc, self.nets.mcu_3v3],
        }
