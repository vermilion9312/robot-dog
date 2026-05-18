from dataclasses import dataclass


@dataclass(frozen=True)
class PinConnection:
    component: str
    pin: str
    net: str

    def as_tuple(self) -> tuple[str, str, str]:
        return (self.component, self.pin, self.net)
