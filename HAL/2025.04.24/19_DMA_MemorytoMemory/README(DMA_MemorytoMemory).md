## 코드내용

### dma_config()함수내부 
```c
__HAL_RCC_DMA2_CLK_ENABLE();  // DMA2의 클럭을 활성화
```
***
```c
//DMA 스트림과 DMA 채널을 설정 
DmaHandle.Instance = DMA_STREAM;  // 사용할 DMA 스트림을 설정
DmaHandle.Init.Channel = DMA_CHANNEL;  // DMA 채널 설정
```
- DMA2_Stream0 스트림과 DMA_CHANNEL_0 채널을 사용
***
```c
//DMA의 데이터 전송 정의 
DmaHandle.Init.Direction = DMA_MEMORY_TO_MEMORY;  // 메모리에서 메모리로 전송 설정
DmaHandle.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;  // 주변 장치 데이터 정렬 설정 (워드 정렬)
DmaHandle.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;  // 메모리 데이터 정렬 설정 (워드 정렬)
DmaHandle.Init.PeriphInc = DMA_PINC_ENABLE;  // 주변 장치 주소 증가 설정
DmaHandle.Init.MemInc = DMA_MINC_ENABLE;  // 메모리 주소 증가 설정
```
- Direction: 전송 방향을 DMA_MEMORY_TO_MEMORY로 설정하여 메모리 간 전송을 수행
- Data Alignment: 데이터의 정렬 방식을 설정 여기서는 32비트 워드(4바이트) 단위로 데이터를 정렬
- Increment: 메모리와 주변 장치 주소를 증가시킬 것인지 설정 여기서는 두 주소 모두 증가하도록 설정(DMA_PINC_ENABLE, DMA_MINC_ENABLE).
***
```c
//콜백함수 
HAL_DMA_RegisterCallback(&DmaHandle, HAL_DMA_XFER_CPLT_CB_ID, TransferComplete);  // 전송 완료 콜백
HAL_DMA_RegisterCallback(&DmaHandle, HAL_DMA_XFER_ERROR_CB_ID, TransferError);  // 전송 오류 콜백
```

