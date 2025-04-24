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
//콜백함수 
HAL_DMA_RegisterCallback(&DmaHandle, HAL_DMA_XFER_CPLT_CB_ID, TransferComplete);  // 전송 완료 콜백
HAL_DMA_RegisterCallback(&DmaHandle, HAL_DMA_XFER_ERROR_CB_ID, TransferError);  // 전송 오류 콜백
```
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
  - DMA_MEMORY_TO_MEMORY: 메모리 → 메모리
  - DMA_MEMORY_TO_PERIPH: 메모리 → 주변 장치 (예: 메모리에서 UART 전송)
  - DMA_PERIPH_TO_MEMORY: 주변 장치 → 메모리 (예: ADC 결과를 메모리에 저장)
***
- PeriphDataAlignment: 데이터의 정렬 방식을 설정 여기서는 32비트 워드(4바이트) 단위로 데이터를 정렬
(이름이 주변장치이지만 MEMORY_TO_MEMORY모드에서는 소스메모리 정렬)
  - DMA_PDATAALIGN_BYTE: 1바이트 (8비트)
  - DMA_PDATAALIGN_HALFWORD: 2바이트 (16비트)
  - DMA_PDATAALIGN_WORD: 4바이트 (32비트)
***
- MemDataAlignment: 메모리 측의 데이터 정렬(크기)을 설정
  - 위의 PeriphDataAlignment와 동일하게 단위 설정
  - aDST_Buffer[]도 32비트 정수 배열이므로 WORD로 설정
***
- PeriphInc: "주변 장치" 주소를 전송이 끝날 때마다 증가시킬지 여부
  - ENABLE이면, 매 전송마다 다음 주소로 자동 증가(0번째,1번째 순차접근)
  - DISABLE이면, 주소 고정 (같은 주소에 계속 데이터 덮어쓰기)
  - 메모리 간 전송에서는 이 항목이 소스 주소 증가 여부로 사용
***
- MemInc: 메모리 주소(목적지 주소)를 전송마다 증가할지 여부
  - ENABLE이면 aDST_Buffer[0], [1], [2]...에 순차적으로 저장
  - DISABLE이면 첫 주소에 계속 덮어씀
  - 배열 전체에 데이터를 저장해야 하므로 당연히 ENABLE이어야 함
***


