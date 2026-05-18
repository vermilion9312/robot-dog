# PCB SKIDL OOP Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** `pcb-design/skidl/main.py`를 기준으로 SKIDL PCB 설계를 객체지향 블록 구조로 시작할 수 있게 만든다.

**Architecture:** `main.py`는 실행 진입점만 담당하고, `robot_dog_pcb` 패키지의 `RobotDogPcbProject`가 공통 net과 회로 블록을 조립한다. 초기 구현은 SKIDL 설치 없이도 단위 테스트가 가능한 순수 Python 모델을 제공하고, 실제 SKIDL 부품 연결은 이후 전원 계산과 부품 선정 뒤 확장한다.

**Tech Stack:** Python 3, pytest, SKIDL-ready package structure

---

## File Structure

- Create: `pcb-design/skidl/main.py` - 프로젝트 생성과 요약 출력 진입점
- Create: `pcb-design/skidl/robot_dog_pcb/__init__.py` - 공개 API 재노출
- Create: `pcb-design/skidl/robot_dog_pcb/connections.py` - 소자 pin과 net 연결 관계 모델
- Create: `pcb-design/skidl/robot_dog_pcb/nets.py` - `BoardNets`와 PWM net 이름 생성
- Create: `pcb-design/skidl/robot_dog_pcb/project.py` - `RobotDogPcbProject` 최상위 조립자
- Create: `pcb-design/skidl/robot_dog_pcb/blocks/__init__.py` - 블록 공개 API 재노출
- Create: `pcb-design/skidl/robot_dog_pcb/blocks/power.py` - `PowerBlock`
- Create: `pcb-design/skidl/robot_dog_pcb/blocks/mcu.py` - `McuBlock`
- Create: `pcb-design/skidl/robot_dog_pcb/blocks/servo.py` - `ServoConnector`, `ServoConnectorBank`
- Create: `pcb-design/skidl/robot_dog_pcb/blocks/expansion.py` - `ExpansionBlock`
- Create: `pcb-design/skidl/tests/test_board_nets.py` - 공통 net 테스트
- Create: `pcb-design/skidl/tests/test_project.py` - 프로젝트 조립 테스트
- Create: `pcb-design/skidl/tests/test_main.py` - `main.py` 진입점 테스트

### Task 1: BoardNets

**Files:**
- Create: `pcb-design/skidl/tests/test_board_nets.py`
- Create: `pcb-design/skidl/robot_dog_pcb/nets.py`
- Create: `pcb-design/skidl/robot_dog_pcb/__init__.py`

- [ ] **Step 1: Write the failing test**

```python
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
```

- [ ] **Step 2: Run test to verify it fails**

Run: `python -m pytest pcb-design/skidl/tests/test_board_nets.py -q`
Expected: FAIL with `ModuleNotFoundError: No module named 'robot_dog_pcb'`

- [ ] **Step 3: Write minimal implementation**

```python
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
```

- [ ] **Step 4: Run test to verify it passes**

Run: `python -m pytest pcb-design/skidl/tests/test_board_nets.py -q`
Expected: `1 passed`

### Task 2: Circuit Blocks

**Files:**
- Create: `pcb-design/skidl/tests/test_project.py`
- Create: `pcb-design/skidl/robot_dog_pcb/blocks/power.py`
- Create: `pcb-design/skidl/robot_dog_pcb/blocks/mcu.py`
- Create: `pcb-design/skidl/robot_dog_pcb/blocks/servo.py`
- Create: `pcb-design/skidl/robot_dog_pcb/blocks/expansion.py`
- Create: `pcb-design/skidl/robot_dog_pcb/blocks/__init__.py`

- [ ] **Step 1: Write the failing test**

```python
from robot_dog_pcb import BoardNets
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
    assert expansion.describe()["available_groups"] == ["power", "ground", "communication", "gpio"]
```

- [ ] **Step 2: Run test to verify it fails**

Run: `python -m pytest pcb-design/skidl/tests/test_project.py -q`
Expected: FAIL with `ModuleNotFoundError` for `robot_dog_pcb.blocks`

- [ ] **Step 3: Write minimal implementation**

Create dataclass-based block classes with `describe()`, `connections`, and `connection_tuples()` methods/properties. Each block must expose pin-to-net connectivity, not only metadata.

- [ ] **Step 4: Run test to verify it passes**

Run: `python -m pytest pcb-design/skidl/tests/test_project.py -q`
Expected: `1 passed`

### Task 3: RobotDogPcbProject

**Files:**
- Modify: `pcb-design/skidl/tests/test_project.py`
- Create: `pcb-design/skidl/robot_dog_pcb/project.py`
- Modify: `pcb-design/skidl/robot_dog_pcb/__init__.py`

- [ ] **Step 1: Write the failing test**

```python
from robot_dog_pcb import RobotDogPcbProject


def test_project_builds_named_blocks_and_summary():
    project = RobotDogPcbProject()
    summary = project.build().summary()

    assert summary["name"] == "robot-dog-controller"
    assert summary["blocks"] == ["power", "mcu", "servo_connectors", "expansion"]
    assert summary["servo_count"] == 12
    assert summary["nets"]["servo_pwm_count"] == 12
```

- [ ] **Step 2: Run test to verify it fails**

Run: `python -m pytest pcb-design/skidl/tests/test_project.py -q`
Expected: FAIL with `ImportError` for `RobotDogPcbProject`

- [ ] **Step 3: Write minimal implementation**

Create `RobotDogPcbProject` with `build()` and `summary()` methods.

- [ ] **Step 4: Run test to verify it passes**

Run: `python -m pytest pcb-design/skidl/tests/test_project.py -q`
Expected: `2 passed`

### Task 4: main.py Entrypoint

**Files:**
- Create: `pcb-design/skidl/tests/test_main.py`
- Create: `pcb-design/skidl/main.py`

- [ ] **Step 1: Write the failing test**

```python
import main


def test_main_returns_project_summary():
    summary = main.run()

    assert summary["name"] == "robot-dog-controller"
    assert summary["servo_count"] == 12
    assert "servo_connectors" in summary["blocks"]
```

- [ ] **Step 2: Run test to verify it fails**

Run: `Push-Location pcb-design/skidl; python -m pytest tests/test_main.py -q; Pop-Location`
Expected: FAIL with `ModuleNotFoundError: No module named 'main'`

- [ ] **Step 3: Write minimal implementation**

Create `main.py` with a `run()` function and command-line summary printing.

- [ ] **Step 4: Run test to verify it passes**

Run: `Push-Location pcb-design/skidl; python -m pytest tests/test_main.py -q; Pop-Location`
Expected: `1 passed`

### Task 5: Verify and Commit

**Files:**
- All files from Tasks 1-4
- Modify: `documents/change-log.md`

- [ ] **Step 1: Run all SKIDL tests**

Run: `Push-Location pcb-design/skidl; python -m pytest -q; Pop-Location`
Expected: all tests pass.

- [ ] **Step 2: Run entrypoint**

Run: `Push-Location pcb-design/skidl; python main.py; Pop-Location`
Expected: summary output includes `robot-dog-controller` and `servo_count`.

- [ ] **Step 3: Update change log**

Add a 2026-05-18 entry noting that the SKIDL OOP package skeleton, pin-to-net connection model, and tests were created.

- [ ] **Step 4: Commit and push**

```bash
git add docs/superpowers/plans/2026-05-18-pcb-skidl-oop.md pcb-design/skidl documents/change-log.md
git commit -m "Implement SKIDL PCB object skeleton"
git push
```
