from dataclasses import dataclass, field

from robot_dog_pcb.blocks import ExpansionBlock, McuBlock, PowerBlock, ServoConnectorBank
from robot_dog_pcb.connections import PinConnection
from robot_dog_pcb.nets import BoardNets


@dataclass
class RobotDogPcbProject:
    name: str = "robot-dog-controller"
    nets: BoardNets = field(default_factory=BoardNets)
    power: PowerBlock | None = None
    mcu: McuBlock | None = None
    servo_connectors: ServoConnectorBank | None = None
    expansion: ExpansionBlock | None = None

    def build(self) -> "RobotDogPcbProject":
        self.power = PowerBlock(self.nets)
        self.mcu = McuBlock(self.nets)
        self.servo_connectors = ServoConnectorBank(self.nets)
        self.expansion = ExpansionBlock(self.nets)
        return self

    @property
    def blocks(self) -> list[PowerBlock | McuBlock | ServoConnectorBank | ExpansionBlock]:
        return [
            block
            for block in [self.power, self.mcu, self.servo_connectors, self.expansion]
            if block is not None
        ]

    @property
    def connections(self) -> list[PinConnection]:
        return [
            connection
            for block in self.blocks
            for connection in block.connections
        ]

    def summary(self) -> dict[str, object]:
        servo_count = (
            len(self.servo_connectors.connectors)
            if self.servo_connectors is not None
            else 0
        )
        return {
            "name": self.name,
            "blocks": [block.name for block in self.blocks],
            "servo_count": servo_count,
            "nets": {
                "vbat": self.nets.vbat,
                "gnd": self.nets.gnd,
                "servo_vcc": self.nets.servo_vcc,
                "mcu_3v3": self.nets.mcu_3v3,
                "servo_pwm_count": len(self.nets.servo_pwm_names),
            },
            "connections": [connection.as_tuple() for connection in self.connections],
        }
