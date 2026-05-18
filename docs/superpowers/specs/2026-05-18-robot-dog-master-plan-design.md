# 로봇 개 프로젝트 마스터 기획 설계

## 목적

이 문서는 로봇 개 프로젝트의 1차 마스터 기획 설계를 기록한다. 프로젝트는 단순 MVP가 아니라, 기계 설계, PCB 설계, 펌웨어 설계를 직접 수행하며 확장 가능한 완성형 학습 플랫폼을 만드는 것을 목표로 한다.

## 프로젝트 목표

- 기계, PCB, 펌웨어를 직접 설계하는 학습용 로봇 개 플랫폼을 만든다.
- MG996R 서보 12개를 기반으로 4족 보행 구조를 설계한다.
- 외부 배터리만 연결하면 동작하는 단일 PCB 전원/제어 구조를 목표로 한다.
- 약 1시간 동작 가능한 배터리를 선정하되, 서보 토크 한계와 배터리 무게를 함께 고려한다.
- 센서, 통신, 추가 모듈을 추후 확장할 수 있는 기계/PCB/펌웨어 여유를 확보한다.

## 완료 기준

프로젝트의 1차 완료 기준은 확장 플랫폼형 완성 로봇 개이다. 단순히 걷는 것만으로 완료하지 않고, 전원 안정성, 반복 동작 안정성, 설계 문서화, 확장 여유까지 검증된 상태를 목표로 한다.

## 프로젝트 구조

```text
robot-dog/
  documents/
    master-plan.md
    requirements.md
    change-log.md
    decisions.md

  mechanical-design/
    README.md
    requirements.md
    torque-and-linkage.md
    cad/
    exports/
    references/

  pcb-design/
    README.md
    requirements.md
    power-system.md
    connectors.md
    easyeda/
    skidl/
    exports/
    references/

  firmware-design/
    README.md
    requirements.md
    architecture.md
    cubemx/
    src/
    tests/
    references/
```

폴더명과 파일명은 영어로 작성하고, `.md` 문서 본문은 한국어로 작성한다.

## 분야별 범위

### 기계 설계

기계 설계는 로봇 바디, 다리 링크, 서보 배치, 베어링 적용, 황동 인서트 적용, 조립 구조를 담당한다. MG996R 최대 사양의 20% 수준을 기준으로 토크 여유를 계산하고, 배터리 무게를 포함한 전체 중량을 검토한 뒤 크기와 링크 길이를 확정한다.

### PCB 설계

PCB 설계는 외부 배터리만 연결하면 동작하는 단일 기판을 목표로 한다. BEC나 별도 컨버터 모듈 없이 전원 변환, 서보 전원 분배, MCU 연결, 커넥터 배치를 PCB에 통합한다. EasyEDA Pro를 주 설계 도구로 사용하고, SKIDL은 반복 회로나 구조화된 회로 정의에 활용한다.

### 펌웨어 설계

펌웨어 설계는 STM32F103C8T6 Blue Pill, STM32CubeMX, VS Code 환경을 기준으로 한다. 12개 서보 제어, 보행 패턴, 전원/상태 모니터링, 확장 모듈 인터페이스를 분리된 구조로 설계한다.

## 계산 후 확정할 항목

- 전체 크기
- 목표 중량
- 링크 길이
- 배터리 셀 구성 및 용량
- 평균/피크 전류 요구사항
- 전원부 회로 사양

## 변경 사양 관리

다음 항목은 변경 사양으로 본다.

- MCU, 서보, 배터리, 커넥터, 재질 등 핵심 부품 변경
- 목표 동작 시간, 중량, 크기, 토크 기준 변경
- PCB 전원 구조, 커넥터 구조, 단일 기판 원칙 변경
- 펌웨어 구조, 제어 방식, 개발 환경 변경
- 폴더 구조나 주요 문서 체계 변경

변경 사양이 생기면 관련 문서를 수정하고, `documents/change-log.md`에 변경 내용을 기록한다. 설계상 중요한 판단은 `documents/decisions.md`에 결정 이유를 남긴다. 변경 작업이 끝나면 즉시 커밋하고, 원격 저장소가 설정되어 있으면 푸시한다.
