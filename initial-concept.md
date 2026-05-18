# 로봇 개 프로젝트
## 기계 설계
### 사용 프로그램
- 2d: AutoCAD
- 3d: Onshape
- 로봇 개 바디 재질: Creality Hyper PLA Black
- 회전부 NSK 베이링 사용
- 황동 인서트 사용
- MG996R 사양에 나온 최대 사양의 20%로 토크 설계할 것

## PCB 설계
- EasyEDA Pro
- Python Library SKIDL
- PCB 단일 기판으로 BEC, 컨버터 등 다른 모듈 없이 설계하여 외부 배터리만 연결하면 동작하게 설계할 것
- 전원부 단자는 KF301, 신호부는 Molex 5267 사용할 


## 펌웨어 설계
- STM32 환경
- STM32cubeMX + vscode 환경


## 정해진 사양
- MCU: STMF103C8T6 Blue Pill * 1EA
- Servo Motor: MG996R * 12EA
- 외부 배터리 전원
