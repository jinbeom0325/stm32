### 들어가기전 정리
EXTI는 인터럽트를 발생시키는 역할 

NVIC는 인터럽트 컨트롤러 즉 CPU가 처리하게 허용해주는 것 

둘이 꼭 있어야 한다. 

DMA는 직접 메모리 접근 CPU를 거치지 않고 주변장치(ADC) <-> 메모리 사이 데이터를 주고 받는 것 

DMA는 NVIC없어도 동작은 가능하지만 다른 작업 등을 하려면 DMA완료 시점에 NVIC로 인터럽트를 받아야 한다. 

### 코드 흐름 
단계 | 함수 | 설명
--|--|--
1 | HAL_Init() | HAL 시스템 초기화
2 | uart_init() | UART 초기화
3 | adc_pa0_dma_init() | ADC + DMA 설정
4 | HAL_ADC_Start_DMA() | DMA 기반 ADC 시작
5 | while(1) | 센서값 UART 실시간 출력 (DMA가 자동으로 값 채워줌)

ADC+DMA가 자동으로 센서 값을 갱신 ,메인에 while문에서 값을 UART로 내보내는 구조 
