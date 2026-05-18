# PCB SKIDL 객체지향 설계

## 목적

이 문서는 `pcb-design/skidl/main.py`를 기준으로 SKIDL 기반 PCB 설계 자동화 구조를 정의한다. 목표는 회로를 긴 절차형 스크립트로 작성하지 않고, 전원부, MCU, 서보 커넥터, 확장 포트를 독립적인 객체 블록으로 나누어 관리하는 것이다.

## 설계 방향

`main.py`는 전체 회로를 직접 작성하지 않고 최상위 실행 진입점 역할만 한다. 실제 회로 구성은 `robot_dog_pcb` 패키지 내부의 객체들이 담당한다.

```text
pcb-design/skidl/
  main.py
  robot_dog_pcb/
    __init__.py
    project.py
    nets.py
    blocks/
      __init__.py
      power.py
      mcu.py
      servo.py
      expansion.py
```

## 주요 객체

### RobotDogPcbProject

전체 회로 생성 흐름을 관리한다.

- 공통 net 생성
- 전원 블록 생성
- MCU 블록 생성
- 서보 커넥터 블록 생성
- 확장 포트 블록 생성
- ERC 실행 진입점 제공
- netlist 생성 진입점 제공

### BoardNets

PCB 전체에서 공유하는 주요 net을 관리한다.

- `VBAT`: 외부 배터리 입력
- `GND`: 공통 접지
- `SERVO_VCC`: 서보 전원 레일
- `MCU_3V3`: MCU 전원 레일
- `PWM_SERVO_01`부터 `PWM_SERVO_12`: 서보 PWM 신호

### PowerBlock

전원 입력과 전원 레일을 담당한다.

- 배터리 입력 커넥터
- 서보 전원 레일
- MCU 전원 레일
- 보호 회로와 전원 변환 회로가 들어갈 위치

초기 구현에서는 실제 DC-DC 컨버터와 보호 회로 부품을 확정하지 않고, 객체 경계와 net 연결 구조를 먼저 만든다.

### McuBlock

STM32F103C8T6 Blue Pill 연결 영역을 담당한다.

- MCU 전원 연결
- GND 연결
- 12개 서보 PWM 신호 연결
- 디버그 또는 프로그래밍 포트 연결 여지

### ServoConnectorBank

MG996R 서보 12개용 커넥터를 반복 생성한다.

- 각 서보 커넥터는 `SERVO_VCC`, `GND`, 개별 PWM 신호를 가진다.
- 서보 번호는 1부터 12까지 사용한다.
- 커넥터 부품은 신호부 기준인 Molex 5267 계열을 우선 고려한다.

### ExpansionBlock

추후 센서, 통신, 추가 모듈을 위한 확장 포트를 담당한다.

- 전원
- GND
- 통신 신호
- 예비 GPIO

초기 구현 범위에서는 확장 포트 핀 수를 설계하지 않는다. 확장 블록은 전원, GND, 통신 신호, 예비 GPIO를 담을 수 있는 독립 객체로만 정의하고, 핀 수와 커넥터 부품은 전원 계산과 MCU 핀맵 결정 후 별도 설계 결정으로 기록한다.

## 테스트 전략

초기 테스트는 SKIDL 설치 여부와 무관하게 실행 가능한 Python 단위 테스트를 우선한다. 테스트는 객체가 올바른 설계 의도를 표현하는지 확인한다.

- `RobotDogPcbProject`가 필요한 블록을 생성하는지 확인한다.
- `BoardNets`가 12개 PWM 신호명을 생성하는지 확인한다.
- `ServoConnectorBank`가 12개 서보 채널을 구성하는지 확인한다.
- 블록 이름과 채널 번호가 일관되게 유지되는지 확인한다.

SKIDL 의존 테스트는 실제 부품 라이브러리와 footprint 후보가 정리된 뒤 추가한다.

## 제외 범위

이번 설계에서는 다음 항목을 확정하지 않는다.

- 실제 DC-DC 컨버터 부품
- 보호 회로 상세 부품
- 커넥터 footprint
- PCB 외형
- 배선 폭
- 구리 두께
- EasyEDA 회로도 파일

이 항목들은 전원 계산과 부품 선정이 끝난 뒤 별도 설계 결정으로 기록한다.
