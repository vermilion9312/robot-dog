from pprint import pprint

from robot_dog_pcb import RobotDogPcbProject


def run() -> dict[str, object]:
    project = RobotDogPcbProject().build()
    return project.summary()


def main() -> None:
    pprint(run())


if __name__ == "__main__":
    main()
