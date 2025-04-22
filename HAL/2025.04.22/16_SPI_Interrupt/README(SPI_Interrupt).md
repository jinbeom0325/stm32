## 코드부분
```c
HAL_SPI_TransmitReceive_IT(&hspi1, tx_buffer, rx_buffer, 10); //비동기 
```
- tx_buffer에서 데이터를 SPI1을 통해 송신하고, 송신과 동시에 수신된 데이터를 rx_buffer에 저장
- 인터럽트 기반으로 동작, 송수신이 완료되면 HAL_SPI_TxRxCpltCallback() 콜백 함수가 호출
***
```c
void SPI1_IRQHandler(void)
{
    HAL_SPI_IRQHandler(&hspi1);
}
```
- SPI1_IRQHandler()는 인터럽트 요청이 발생했을 때 호출되는 인터럽트 서비스 루틴
- HAL_SPI_IRQHandler()를 호출하여 SPI1의 송수신을 처리하고, 인터럽트에 대한 응답
***
```c
void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi)
{
    counter++;
}
```
- 송수신 완료되고 콜백처리 함수 
