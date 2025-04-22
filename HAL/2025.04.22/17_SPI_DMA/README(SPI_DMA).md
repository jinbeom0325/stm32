## 코드내용

### SPI DMA 통신 시작
```c
//DMA를 통해 비동기적으로 SPI 전송시작
HAL_SPI_TransmitReceive_DMA(&hspi1, tx_buffer, rx_buffer, 10); 
```
- tx_buffer[10] → SPI로 전송됨 (MOSI)
- SPI로부터 수신된 값은 rx_buffer[10]에 저장됨 (MISO)
- 데이터 전송/수신이 비동기로 진행되므로, CPU는 블로킹되지 않고 바로 다음 작업을 수행할 수 있음
***
### 전송 완료 시 인터럽트 발생
```c
// DMA2 수신 인터럽트 핸들러
void DMA2_Stream0_IRQHandler(void)
{
    HAL_DMA_IRQHandler(&hdma_spi1_rx);
}

// DMA2 송신 인터럽트 핸들러
void DMA2_Stream3_IRQHandler(void)
{
    HAL_DMA_IRQHandler(&hdma_spi1_tx);
}
```
### 콜백함
```c
void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi)
{
	counter++; 
}

```

## DMA 구조체부분
```c
//Rx
hdma_spi1_rx.Instance = DMA2_Stream0;                // DMA2의 Stream0 사용 (Rx 전용으로 선택)
hdma_spi1_rx.Init.Channel = DMA_CHANNEL_3;           // SPI1 Rx는 DMA 채널 3에 연결됨
hdma_spi1_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;  // 데이터 방향: SPI(Rx) → 메모리
hdma_spi1_rx.Init.PeriphInc = DMA_PINC_DISABLE;      // 주변장치 주소 고정 (SPI 데이터 레지스터 주소)
hdma_spi1_rx.Init.MemInc = DMA_MINC_ENABLE;          // 메모리 주소 자동 증가 (수신 버퍼 배열)
hdma_spi1_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE; // 주변장치 데이터 정렬: 바이트 단위
hdma_spi1_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;    // 메모리 데이터 정렬: 바이트 단위
hdma_spi1_rx.Init.Mode = DMA_NORMAL;                 // 일반 모드 (한 번만 전송)
hdma_spi1_rx.Init.Priority = DMA_PRIORITY_LOW;       // 우선순위: 낮음
hdma_spi1_rx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;   // FIFO 모드 비활성화
HAL_DMA_Init(&hdma_spi1_rx);                         // DMA 초기화

__HAL_LINKDMA(&hspi1, hdmarx, hdma_spi1_rx);         // SPI1의 Rx DMA 핸들에 연결
// hspi1.hdmarx = &hdma_spi1_rx; 와 동일한 효과 (HAL 사용 권장)

//Tx
hdma_spi1_tx.Instance = DMA2_Stream3;                // DMA2의 Stream3 사용 (Tx 전용으로 선택)
hdma_spi1_tx.Init.Channel = DMA_CHANNEL_3;           // SPI1 Tx는 DMA 채널 3에 연결됨
hdma_spi1_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;  // 데이터 방향: 메모리 → SPI(Tx)
hdma_spi1_tx.Init.PeriphInc = DMA_PINC_DISABLE;      // 주변장치 주소 고정 (SPI 데이터 레지스터 주소)
hdma_spi1_tx.Init.MemInc = DMA_MINC_ENABLE;          // 메모리 주소 자동 증가 (송신 버퍼 배열)
hdma_spi1_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE; // 주변장치 데이터 정렬: 바이트 단위
hdma_spi1_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;    // 메모리 데이터 정렬: 바이트 단위
hdma_spi1_tx.Init.Mode = DMA_NORMAL;                 // 일반 모드 (한 번만 전송)
hdma_spi1_tx.Init.Priority = DMA_PRIORITY_LOW;       // 우선순위: 낮음
hdma_spi1_tx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;   // FIFO 모드 비활성화
HAL_DMA_Init(&hdma_spi1_tx);

__HAL_LINKDMA(&hspi1, hdmatx, hdma_spi1_tx);         // SPI1의 Tx DMA 핸들에 연결
```

