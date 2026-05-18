from robot_dog_pcb import BoardNets
from robot_dog_pcb import RobotDogPcbProject
from robot_dog_pcb.blocks import (
    ExpansionBlock,
    McuBlock,
    PowerBlock,
    ServoConnectorBank,
)


def test_blocks_describe_expected_connections():
    nets = BoardNets()

    power = PowerBlock(nets)
    mcu = McuBlock(nets)
    servos = ServoConnectorBank(nets)
    expansion = ExpansionBlock(nets)

    assert power.describe()["rails"] == ["VBAT", "GND", "SERVO_VCC", "MCU_3V3"]
    assert mcu.describe()["pwm_inputs"] == nets.servo_pwm_names
    assert len(servos.connectors) == 12
    assert servos.connectors[0].name == "SERVO_01"
    assert servos.connectors[-1].pwm == "PWM_SERVO_12"
    assert expansion.describe()["available_groups"] == [
        "power",
        "ground",
        "communication",
        "gpio",
    ]


def test_blocks_expose_pin_to_net_connections():
    nets = BoardNets()

    power = PowerBlock(nets)
    mcu = McuBlock(nets)
    servos = ServoConnectorBank(nets)
    expansion = ExpansionBlock(nets)

    assert ("J_BAT", "1", "VBAT") in power.connection_tuples()
    assert ("J_BAT", "2", "GND") in power.connection_tuples()
    assert ("J_BLUEPILL", "3V3", "MCU_3V3") in mcu.connection_tuples()
    assert ("J_BLUEPILL", "GND", "GND") in mcu.connection_tuples()
    assert ("J_BLUEPILL", "PWM01", "PWM_SERVO_01") in mcu.connection_tuples()
    assert ("J_SERVO_01", "V+", "SERVO_VCC") in servos.connection_tuples()
    assert ("J_SERVO_01", "PWM", "PWM_SERVO_01") in servos.connection_tuples()
    assert ("J_SERVO_12", "PWM", "PWM_SERVO_12") in servos.connection_tuples()
    assert ("J_EXPANSION", "3V3", "MCU_3V3") in expansion.connection_tuples()


def test_project_builds_named_blocks_and_summary():
    project = RobotDogPcbProject()
    summary = project.build().summary()

    assert summary["name"] == "robot-dog-controller"
    assert summary["blocks"] == ["power", "mcu", "servo_connectors", "expansion"]
    assert summary["servo_count"] == 12
    assert summary["nets"]["servo_pwm_count"] == 12
    assert ("J_SERVO_12", "PWM", "PWM_SERVO_12") in summary["connections"]
