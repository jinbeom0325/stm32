# 2025.04.03
***
용어
- TIM핀은 타이머
- RCC는 재설정(클럭제어) 자체 주소 세트를 가지고 있다. (0x4002 3800 - 0x4002 3BFF)

***
메모리맵
|Boundary address|Peripheral|
|----|-----|
|0x4002 0C00 - 0x4002 0FFF|GPIOD|
***
GPIOD 레지스터 주소
|레지스터이름|주소(기본값)|설명
|---|---|---|
|GPIOD_MODER|0x40020C00|입출력 모드 설정|
|GPIOD_OTYPER|0x40020C04|출력 타입 설정| (Push-Pull/Open-Drain)
|GPIOD_OSPEEDR|0x40020C08|출력 속도 설정|
|GPIOD_PUPDR|0x40020C0C|풀업/풀다운 설정|
|GPIOD_IDR|0x40020C10|입력 데이터 레지스터(읽기 전용)|
|GPIOD_ODR|0x40020C14|출력 데이터 레지스터|
|GPIOD_BSRR|0x40020C18|비트 설정/리셋 레지스터(1비트 단위로 제어 가능)|
|GPIOD_LCKR|0x40020C1C|GPIO 잠금 레지스터|
|GPIOD_AFRL|0x40020C20|대체 기능 설정(0~7번)|
|GPIOD_AFRH|0x40020C24|대체 기능 설정(8~15번)|
***
GPIO 포트 모드 레지스터 
- 2개의 섹션 각 핀마다 2비트, 16개의 핀 총 32비트 
- 2비트는 (4가지 모드 입력,출력,대체기능,아날로그) 

GPIO 포트 출력 데이터 레지스터
- 상위 16비트는 예약
- 각 핀마다 1비트
***
## 004led_on
STM32F401RE 보드의 LED켜기
기본 주소 + 오프셋 = 특정 레지스터 주소

```c
#include<stdint.h>

int main(void)
{
  #기본주소 + 오프셋 
	uint32_t *pClkCtrlReg =   (uint32_t*)0x40023830; #클럭
	uint32_t *pPortDModeReg = (uint32_t*)0x40020C00; #모드
	uint32_t *pPortDOutReg =  (uint32_t*)0x40020C14; #출력

  # *pClkCtrlReg |= 0x08;와 같음
	*pClkCtrlReg |= ( 1 << 3); 

  # 비트 0인지 확인 0xFCFFFFFF;
	*pPortDModeReg &= ~( 3 << 24);
  # 0x01000000;
	*pPortDModeReg |= ( 1 << 24);

  # *pPortDOutReg |= 0x1000;
	*pPortDOutReg |= ( 1 << 12);

    while(1);
}

```



