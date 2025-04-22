#include <stdio.h>
#include "stm32f4xx_hal.h"  // STM32 HAL 라이브러리 기본 헤더
#include "uart.h"           // 사용자 정의 UART 함수 헤더
#include "adc.h"            // 사용자 정의 ADC 함수 헤더

SPI_HandleTypeDef hspi1;    // SPI1 핸들 구조체 선언

DMA_HandleTypeDef hdma_spi1_rx;
DMA_HandleTypeDef hdma_spi1_tx;

// SPI1 초기화 함수 선언
void spi1_init(void);

// 송신 및 수신 버퍼
uint8_t tx_buffer[10] = {10, 20, 20, 40, 50, 60, 70, 90, 90, 100};
uint8_t rx_buffer[10];


int counter;

void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi)
{
	counter++;
}


// 메인 함수
int main(void)
{
    HAL_Init();                 // HAL 라이브러리 초기화 (SysTick 타이머, NVIC 등 내부 설정)
    spi1_init();                // SPI1 초기화 함수 호출

    // SPI 통신: tx_buffer 데이터를 전송하며 동시에 rx_buffer에 수신된 데이터를 저장
    HAL_SPI_TransmitReceive_DMA(&hspi1, tx_buffer, rx_buffer, 10);

    while (1)                   // 무한 루프 (여기선 대기만 함)
    {
        // 여기서 데이터 처리 등의 작업을 할 수 있음
    }
}

// SPI1 초기화 함수 정의
void spi1_init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    // SPI1과 관련된 클럭 활성화
    __HAL_RCC_SPI1_CLK_ENABLE();        // SPI1 클럭 활성화
    __HAL_RCC_GPIOA_CLK_ENABLE();       // GPIOA 포트 클럭 활성화

    // SPI1 핀 설정 (PA5: SCK, PA6: MISO, PA7: MOSI)
    GPIO_InitStruct.Pin = GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7;  // 사용 핀
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;                      // 대체 기능 푸시풀 출력
    GPIO_InitStruct.Pull = GPIO_NOPULL;                          // 풀업/풀다운 없음
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;           // 속도: 매우 빠름
    GPIO_InitStruct.Alternate = GPIO_AF5_SPI1;					 // af5로 gpio -> spi기능
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);                      // GPIO 초기화

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

    HAL_SPI_Init(&hspi1);                            // SPI 초기화

    //Configure DMA
    __HAL_RCC_DMA2_CLK_ENABLE();

    //Configure Rx
    hdma_spi1_rx.Instance = DMA2_Stream0;
    hdma_spi1_rx.Init.Channel = DMA_CHANNEL_3;
    hdma_spi1_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_spi1_rx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_spi1_rx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_spi1_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_spi1_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_spi1_rx.Init.Mode = DMA_NORMAL;
    hdma_spi1_rx.Init.Priority = DMA_PRIORITY_LOW;
    hdma_spi1_rx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    HAL_DMA_Init(&hdma_spi1_rx);

    hspi1.hdmarx = &hdma_spi1_rx;


    HAL_NVIC_SetPriority(DMA2_Stream0_IRQn,0,0);
    HAL_NVIC_EnableIRQ(DMA2_Stream0_IRQn);

    //Configure Tx
    hdma_spi1_tx.Instance = DMA2_Stream3;
    hdma_spi1_tx.Init.Channel = DMA_CHANNEL_3;
    hdma_spi1_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
    hdma_spi1_tx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_spi1_tx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_spi1_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_spi1_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_spi1_tx.Init.Mode = DMA_NORMAL;
    hdma_spi1_tx.Init.Priority = DMA_PRIORITY_LOW;
    hdma_spi1_tx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    HAL_DMA_Init(&hdma_spi1_tx);

    hspi1.hdmatx = &hdma_spi1_tx;


    HAL_NVIC_SetPriority(DMA2_Stream3_IRQn,0,0);
	HAL_NVIC_EnableIRQ(DMA2_Stream3_IRQn);
}

void DMA2_Stream0_IRQHandler(void)
{
	HAL_DMA_IRQHandler(&hdma_spi1_rx);
}

void DMA2_Stream3_IRQHandler(void)
{
	HAL_DMA_IRQHandler(&hdma_spi1_tx);

}
// SysTick 인터럽트 핸들러 (주로 내부 타이머 동작에 필요)
// stm32f4xx_it.c 파일에 위치
void SysTick_Handler(void)
{
    HAL_IncTick();   // HAL 내부 틱 카운터 증가
//    HAL_SYSTICK_IRQHandler();  // HAL의 SysTick 인터럽트 처리기 호출
}
