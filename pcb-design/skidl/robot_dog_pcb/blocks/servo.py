from dataclasses import dataclass, field

from robot_dog_pcb.connections import PinConnection
from robot_dog_pcb.nets import BoardNets


@dataclass(frozen=True)
class ServoConnector:
    index: int
    power: str
    ground: str
    pwm: str

    @property
    def name(self) -> str:
        return f"SERVO_{self.index:02d}"

    @property
    def component(self) -> str:
        return f"J_{self.name}"

    @property
    def connections(self) -> list[PinConnection]:
        return [
            PinConnection(self.component, "V+", self.power),
            PinConnection(self.component, "GND", self.ground),
            PinConnection(self.component, "PWM", self.pwm),
        ]

    def connection_tuples(self) -> list[tuple[str, str, str]]:
        return [connection.as_tuple() for connection in self.connections]

    def describe(self) -> dict[str, int | str]:
        return {
            "index": self.index,
            "name": self.name,
            "power": self.power,
            "ground": self.ground,
            "pwm": self.pwm,
        }


@dataclass(frozen=True)
class ServoConnectorBank:
    nets: BoardNets
    name: str = "servo_connectors"
    connectors: list[ServoConnector] = field(init=False)

    def __post_init__(self) -> None:
        connectors = [
            ServoConnector(
                index=index,
                power=self.nets.servo_vcc,
                ground=self.nets.gnd,
                pwm=pwm,
            )
            for index, pwm in enumerate(self.nets.servo_pwm_names, start=1)
        ]
        object.__setattr__(self, "connectors", connectors)

    @property
    def connections(self) -> list[PinConnection]:
        return [
            connection
            for connector in self.connectors
            for connection in connector.connections
        ]

    def connection_tuples(self) -> list[tuple[str, str, str]]:
        return [connection.as_tuple() for connection in self.connections]

    def describe(self) -> dict[str, list[dict[str, int | str]] | str]:
        return {
            "name": self.name,
            "connectors": [connector.describe() for connector in self.connectors],
        }
