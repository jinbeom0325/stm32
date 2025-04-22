## 코드흐름 
***
### spi1_init(); 안에서 설정되는것

```c
// SPI 설정 구성
  hspi1.Instance = SPI1;                           // SPI1 인스턴스 지정
  hspi1.Init.Mode = SPI_MODE_MASTER;               // 마스터 모드
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;     // 양방향 (풀 듀플렉스)
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;         // 8비트 데이터
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;       // CPOL = 0 (클럭 기본상태 LOW)
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;           // CPHA = 0 (첫 번째 엣지에서 샘플링)
  hspi1.Init.NSS = SPI_NSS_SOFT;                   // 소프트웨어 NSS 관리
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8; // 클럭 분주비: 8
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;          // 최상위 비트(MSB) 먼저 전송
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;          // TI 모드 비활성화
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE; // CRC 계산 사용 안 함
```
***
### SPI 데이터 송수신
```c
HAL_SPI_TransmitReceive(&hspi1, tx_buffer, rx_buffer, 10, 100);
```
- SPI1을 통해 tx_buffer의 10바이트 데이터를 전송
- 동시에 상대방(Slave)으로부터 수신된 10바이트 데이터를 rx_buffer에 저장
- 타임아웃은 100ms
- ```c
  hspi1.Init.Direction = SPI_DIRECTION_2LINES; //이코드로  full duplex(양방향)인걸 알 수 있음
  ```


