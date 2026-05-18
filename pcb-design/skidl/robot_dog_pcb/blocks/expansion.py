from dataclasses import dataclass

from robot_dog_pcb.connections import PinConnection
from robot_dog_pcb.nets import BoardNets


@dataclass(frozen=True)
class ExpansionBlock:
    nets: BoardNets
    name: str = "expansion"

    @property
    def connections(self) -> list[PinConnection]:
        return [
            PinConnection("J_EXPANSION", "3V3", self.nets.mcu_3v3),
            PinConnection("J_EXPANSION", "GND", self.nets.gnd),
            PinConnection("J_EXPANSION", "SCL", "I2C_SCL"),
            PinConnection("J_EXPANSION", "SDA", "I2C_SDA"),
            PinConnection("J_EXPANSION", "GPIO1", "EXP_GPIO_01"),
            PinConnection("J_EXPANSION", "GPIO2", "EXP_GPIO_02"),
        ]

    def connection_tuples(self) -> list[tuple[str, str, str]]:
        return [connection.as_tuple() for connection in self.connections]

    def describe(self) -> dict[str, list[str] | str]:
        return {
            "name": self.name,
            "power": self.nets.mcu_3v3,
            "ground": self.nets.gnd,
            "available_groups": ["power", "ground", "communication", "gpio"],
        }
