## 용어 정리 (진행중)

용어 | 뜻
--|--
UART | Universal Asynchronous Receiver-Transmitter. 비동기 방식으로 데이터를 직렬(Serial)로 송수신하는 통신 방식.
ADC | Analog to Digital Converter. 아날로그 신호(연속된 값)를 디지털 신호(0과 1)로 변환하는 장치.
DMA | Direct Memory Access. CPU를 거치지 않고, 주변장치와 메모리 간 직접 데이터 전송을 담당하는 장치. 빠르고 효율적임.
SPI | Serial Peripheral Interface. 짧은 거리 고속 통신을 위한 동기식 직렬 통신 방식. (Master-Slave 구조)
I2C | Inter-Integrated Circuit. 2개의 선(SCL, SDA)만으로 여러 장치들을 연결하는 통신 방식. (주소로 장치 구분)
RTC | Real Time Clock. 날짜, 시간 정보를 유지하는 하드웨어 타이머. 보조 전원(VBAT)으로 리셋 후에도 동작 가능.
EXTI | External Interrupt. 외부 핀 입력(버튼 등)으로 발생하는 인터럽트. (외부 이벤트 감지)
NVIC | Nested Vectored Interrupt Controller. 인터럽트를 우선순위별로 관리하고 처리하는 ARM 코어 내부 컨트롤러.
RCC | Reset and Clock Control. MCU의 클럭 소스 관리, 리셋 기능을 담당하는 블록. 주변장치 클럭도 설정 가능.
***
### RCC관련

- RCC (Reset and Clock Control) : 클럭과 리셋 제어를 담당하는 주변장치.
MCU 내 모든 클럭 소스를 관리하며, 주변장치에 클럭을 공급하거나 차단함.
주소 범위: 0x4002 3800 ~ 0x4002 3BFF

- Oscillator (오실레이터) : 일정한 주기의 전기 신호(클럭)를 생성하는 회로.
  
  - LSI (Low-Speed Internal) : 내부 32kHz 오실레이터 (정확도 낮음)
  
  - LSE (Low-Speed External) : 외부 32.768kHz 크리스탈 (RTC용으로 정확함)
  
  - HSI, HSE : 고속 내부/외부 오실레이터 (일반적인 시스템 클럭용)

- Clock Source (클럭 소스) : 시스템 및 주변장치에 공급되는 기본 신호. 선택 가능 (LSI, LSE, HSI, PLL 등)

- PCLK (Peripheral Clock) : APB 버스를 통해 주변장치에 전달되는 클럭. PCLK1 (APB1), PCLK2 (APB2) 로 구분.

- Prescaler (분주기, PREDIV) : 클럭을 일정 비율로 나눠서 속도를 줄임. 예: 32kHz / ((127 + 1) * (249 + 1)) = 1Hz → RTC 클럭을 1초 단위로 분주

### RTC관련

- RTC (Real Time Clock) : 실시간 시계 기능. MCU가 꺼져 있어도 백업 전원이 있으면 시간 유지 가능.

- Backup Domain (백업 도메인) : RTC 및 관련 레지스터, 백업 레지스터를 포함한 영역. VDD 대신 VBAT 전원으로 유지 가능.

- Backup Registers (BKUP DRx) : 전원이 꺼져도 보존되는 레지스터 (DR0 ~ DR19, 총 20개, 주소: 0x40002850 ~ 0x4000289C) 주로 사용자 플래그나 설정값 저장 용도로 사용.

- HAL_RTC_SetTime / GetTime / SetDate / GetDate : HAL 함수로 시간/날짜를 설정하거나 읽어오는 기능.

- Synchronous (동기) : 일정한 클럭에 맞춰 동작. 모든 작업이 정해진 타이밍에 발생.
  
- Asynchronous (비동기) : 클럭 없이 동작하거나 독립적인 클럭 소스를 가짐. 타이밍이 유연함. RTC에서는 동기/비동기 프리스케일러가 존재.
  
- HAL (Hardware Abstraction Layer) : 하드웨어 추상화 계층. 레지스터 직접 접근 없이 함수로 주변장치 제어 가능.
- Peripheral (주변장치) : MCU 내의 하드웨어 기능들 (USART, ADC, RTC, SPI, I2C 등)
- Instance : 사용하려는 하드웨어의 베이스 주소 (예: RTC, USART2, ADC1 등)
- VBAT : RTC, 백업 레지스터 등에 공급되는 백업 전원
- BCD (Binary Coded Decimal) : 2진화 10진수, 4비트로 0~9까지 표현하는 방식. RTC 시간 설정 시 사용됨. (BIN은 10진수)
- VDD : MCU 주 전원
- TimeFormat(AM/PM) : 12시간제에서 오전/오후 구분
***

### 시스템 구성 및 개념
용어 | 의미
--|--
MCU (Microcontroller Unit) | 마이크로컨트롤러. CPU + 메모리 + 주변장치 포함한 칩
CMSIS | Cortex Microcontroller Software Interface Standard: ARM에서 정의한 표준 라이브러리 구조
HAL | Hardware Abstraction Layer. STM32에서 하드웨어 제어를 쉽게 하기 위한 라이브러리
LL | Low Layer. HAL보다 더 하드웨어에 가까운 API, 성능은 HAL보다 우수
BSP | Board Support Package. 특정 보드에 맞는 HAL 설정 코드 집합
IDE | 통합 개발 환경. STM32CubeIDE 등
***

### 클럭 및 전원 관련
용어 | 의미
--|--
HSI | High-Speed Internal. 내부 고속 클럭 (16MHz 등)
HSE | High-Speed External. 외부 고속 클럭 (크리스탈, 8MHz 등)
LSI | Low-Speed Internal. 저속 내부 클럭 (RTC용, 약 32kHz)
LSE | Low-Speed External. 저속 외부 클럭 (정확한 32.768kHz)
PLL | Phase Locked Loop. 클럭을 곱해 더 높은 주파수 생성
Prescaler (PREDIV) | 주파수 분주기 (클럭 나눠서 속도 낮춤)
SYSCLK | 시스템 클럭. MCU의 주 동작 클럭
AHB / APB | 버스 종류. APB는 GPIO, USART 등 주변장치 연결
VDD | MCU의 메인 전원
VSS | GND (접지)
***

### 레지스터/메모리 관련
용어 | 의미
--|--
레지스터(Register) | 주변 장치를 제어하기 위한 메모리 공간
MMIO | Memory-Mapped I/O. 주소 공간에 하드웨어 레지스터 연결
구조체 매핑 | 레지스터를 구조체로 정의해 접근하는 방식
BASE 주소 | 주변 장치의 시작 주소 (예: RCC는 0x40023800)
오프셋(Offset) | BASE 주소로부터 상대적인 위치
***

### GPIO/통신/인터럽트 관련
용어 | 의미
--|--
GPIO | General Purpose Input Output
MODE | 입력/출력/AF/아날로그 등 핀의 동작 방식
Pull-up / Pull-down | 핀의 기본 전압 상태 지정
USART / UART | 직렬 통신 장치 (Universal Synchronous/Asynchronous Receiver Transmitter)
SPI / I2C | 동기식 통신 방식
DMA | Direct Memory Access. CPU 개입 없이 메모리 ↔ 주변장치 간 데이터 이동
NVIC | Nested Vector Interrupt Controller. 인터럽트 우선순위 및 제어
EXTI | External Interrupt. 외부 핀을 통해 인터럽트 발생
***









