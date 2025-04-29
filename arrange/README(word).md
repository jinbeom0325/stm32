### 진행중

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

통신 방식 | 데이터 라인 수 | 설명
--|--|--
UART | 2개 (TX, RX) | 송신(TX), 수신(RX) 선만 사용. (추가로 GND 연결 필요)
SPI | 4개 (SCLK, MOSI, MISO, SS) | 클럭(SCLK), 마스터→슬레이브(MOSI), 슬레이브→마스터(MISO), 슬레이브 선택(SS/CS)
I2C | 2개 (SCL, SDA) | 클럭(SCL)과 데이터(SDA) 선만 사용. 여러 슬레이브 연결 가능 (주소 구분)
ADC | 1개 (Analog 입력) | 아날로그 신호를 입력받는 선 하나 필요. (내부 디지털화)
DMA | 없음 (하드웨어 내부) | CPU 대신 메모리 ↔ 주변장치 전송, 별도 외부선 필요 없음.
RTC | 없음 (내부) | 실시간 시계 기능, 외부 연결선 필요 없음. (단, 보조 배터리 연결선은 있음)
EXTI | 1개 (Interrupt 라인) | 외부 이벤트를 감지할 입력 핀 필요. (버튼, 센서 등)
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

***
### RTC관련

- RTC (Real Time Clock) : 실시간 시계 기능. MC것
- ALU : 정수계산
- FPU : 소수계산










