## HAL 함수 관련 용어 정리

### GPIO(입출력 핀 제어)
함수명 | 설명
--|--
HAL_GPIO_Init() | GPIO 초기화
HAL_GPIO_DeInit() | GPIO 비활성화
HAL_GPIO_ReadPin() | 핀 입력값 읽기
HAL_GPIO_WritePin() | 핀 출력값 설정
HAL_GPIO_TogglePin() | 핀 출력 상태 토글
HAL_GPIO_EXTI_IRQHandler() | EXTI 인터럽트 처리 함수
HAL_GPIO_EXTI_Callback() | EXTI 발생 시 사용자 콜백 함수
***

### I2C
함수명 | 설명
--|--
HAL_I2C_Init() | I2C 초기화
HAL_I2C_DeInit() | I2C 비활성화
HAL_I2C_Master_Transmit() | I2C 마스터 송신 (Polling)
HAL_I2C_Master_Receive() | I2C 마스터 수신 (Polling)
HAL_I2C_Slave_Transmit() | I2C 슬레이브 송신 (Polling)
HAL_I2C_Slave_Receive() | I2C 슬레이브 수신 (Polling)
HAL_I2C_Master_Transmit_IT() | 마스터 송신 (Interrupt)
HAL_I2C_Master_Receive_IT() | 마스터 수신 (Interrupt)
HAL_I2C_Slave_Transmit_IT() | 슬레이브 송신 (Interrupt)
HAL_I2C_Slave_Receive_IT() | 슬레이브 수신 (Interrupt)
HAL_I2C_Master_Transmit_DMA() | 마스터 송신 (DMA)
HAL_I2C_Master_Receive_DMA() | 마스터 수신 (DMA)
HAL_I2C_Slave_Transmit_DMA() | 슬레이브 송신 (DMA)
HAL_I2C_Slave_Receive_DMA() | 슬레이브 수신 (DMA)
HAL_I2C_Mem_Write() | 메모리 쓰기 (Polling)
HAL_I2C_Mem_Read() | 메모리 읽기 (Polling)
HAL_I2C_IsDeviceReady() | 디바이스 준비 확인 (Polling)
HAL_I2C_ErrorCallback() | 에러 발생 시 호출되는 콜백 함수
***

### UART
함수명 | 설명
--|--
HAL_UART_Init() | UART 초기화
HAL_UART_DeInit() | UART 비활성화
HAL_UART_Transmit() | 데이터 송신 (Polling)
HAL_UART_Receive() | 데이터 수신 (Polling)
HAL_UART_Transmit_IT() | 데이터 송신 (Interrupt)
HAL_UART_Receive_IT() | 데이터 수신 (Interrupt)
HAL_UART_Transmit_DMA() | 데이터 송신 (DMA)
HAL_UART_Receive_DMA() | 데이터 수신 (DMA)
HAL_UART_TxCpltCallback() | 송신 완료 시 콜백 호출
HAL_UART_RxCpltCallback() | 수신 완료 시 콜백 호출
***

### ADC
함수명 | 설명
--|--
HAL_ADC_Init() | ADC 초기화
HAL_ADC_DeInit() | ADC 비활성화
HAL_ADC_Start() | 변환 시작 (Polling)
HAL_ADC_Stop() | 변환 중지
HAL_ADC_Start_IT() | 변환 시작 (Interrupt)
HAL_ADC_Start_DMA() | 변환 시작 (DMA)
HAL_ADC_GetValue() | 변환 결과 읽기
HAL_ADC_ConvCpltCallback() | 변환 완료 콜백 호출
***

### DMA
함수명 | 설명
--|--
HAL_DMA_Init() | DMA 초기화
HAL_DMA_DeInit() | DMA 비활성화
HAL_DMA_Start() | DMA 전송 시작
HAL_DMA_Abort() | DMA 전송 중단
HAL_DMA_IRQHandler() | DMA 인터럽트 처리
HAL_DMA_TxCpltCallback() | 송신 완료 콜백 호출
HAL_DMA_RxCpltCallback() | 수신 완료 콜백 호출
***

### RTC
함수명 | 설명
--|--
HAL_RTC_Init() | RTC 초기화
HAL_RTC_SetTime() | 시간 설정
HAL_RTC_SetDate() | 날짜 설정
HAL_RTC_GetTime() | 시간 읽기
HAL_RTC_GetDate() | 날짜 읽기
HAL_RTCEx_BKUPWrite() | 백업 레지스터 쓰기
HAL_RTCEx_BKUPRead() | 백업 레지스터 읽기
***

### SPI
함수명 | 설명
--|--
HAL_SPI_Init() | SPI 초기화
HAL_SPI_DeInit() | SPI 비활성화
HAL_SPI_Transmit() | 송신 (Polling)
HAL_SPI_Receive() | 수신 (Polling)
HAL_SPI_TransmitReceive() | 송수신 동시 (Polling)
HAL_SPI_Transmit_IT() | 송신 (Interrupt)
HAL_SPI_Receive_IT() | 수신 (Interrupt)
HAL_SPI_TransmitReceive_IT() | 송수신 동시 (Interrupt)
HAL_SPI_Transmit_DMA() | 송신 (DMA)
HAL_SPI_Receive_DMA() | 수신 (DMA)
HAL_SPI_TransmitReceive_DMA() | 송수신 동시 (DMA)
***

### RCC
함수명 | 설명
--|--
HAL_RCC_OscConfig() | 오실레이터(LSE, LSI 등) 설정
HAL_RCC_ClockConfig() | 시스템 클럭 설정
HAL_RCC_GetSysClockFreq() | 시스템 클럭 주파수 얻기
HAL_RCC_MCOConfig() | MCO 핀 클럭 출력 설정
HAL_RCCEx_PeriphCLKConfig() | 주변장치 클럭 소스 설정
***

### EXTI
함수명 | 설명
--|--
HAL_GPIO_EXTI_IRQHandler() | EXTI 인터럽트 핸들러
HAL_GPIO_EXTI_Callback() | EXTI 발생 시 사용자 콜백

