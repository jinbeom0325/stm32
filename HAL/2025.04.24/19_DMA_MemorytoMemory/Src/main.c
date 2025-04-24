#include <stdio.h>
#include "stm32f4xx_hal.h"  // STM32 HAL 라이브러리 헤더 파일 포함
#include "uart.h"            // UART 관련 함수 선언 헤더 파일
#include "adc.h"             // ADC 관련 함수 선언 헤더 파일

#define BUFFER_SIZE				32  // 버퍼 크기 정의
#define DMA_STREAM				DMA2_Stream0  // 사용할 DMA 스트림 정의
#define DMA_STREAM_IRQ			DMA2_Stream0_IRQn  // DMA 스트림 0의 인터럽트 번호
#define DMA_STREAM_IRQHANDLER	DMA2_Stream0_IRQHandler  // DMA 스트림 0의 인터럽트 핸들러
#define DMA_CHANNEL				DMA_CHANNEL_0  // DMA 채널 0 정의

DMA_HandleTypeDef 	DmaHandle;  // DMA 핸들 구조체 정의

// 소스 버퍼 (DMA 전송을 위한 상수 데이터)
static const uint32_t aSRC_Const_Buffer[BUFFER_SIZE]= {
    0x01020304, 0x05060708, 0x090A0B0C, 0x0D0E0F10,
    0x11121314, 0x15161718, 0x191A1B1C, 0x1D1E1F20,
    0x21222324, 0x25262728, 0x292A2B2C, 0x2D2E2F30,
    0x31323334, 0x35363738, 0x393A3B3C, 0x3D3E3F40,
    0x41424344, 0x45464748, 0x494A4B4C, 0x4D4E4F50,
    0x51525354, 0x55565758, 0x595A5B5C, 0x5D5E5F60,
    0x61626364, 0x65666768, 0x696A6B6C, 0x6D6E6F70,
    0x71727374, 0x75767778, 0x797A7B7C, 0x7D7E7F80
};

// 대상 버퍼 (DMA로 전송받을 데이터 저장용)
static uint32_t aDST_Buffer[BUFFER_SIZE];

// DMA 전송 완료 콜백 함수 선언
static void TransferComplete(DMA_HandleTypeDef *DmaHandle);
// DMA 전송 오류 콜백 함수 선언
static void TransferError(DMA_HandleTypeDef *DmaHandle);
// DMA 설정 함수 선언
static void dma_config(void);

// 메인 함수
int main()
{
    HAL_Init();            // HAL 라이브러리 초기화 (STM32의 HAL API 사용을 위한 기본 설정)
    uart_init();           // UART 초기화 (UART 통신을 위한 설정)

    dma_config();          // DMA 초기화 함수 호출

    while(1)  // 무한 루프 (메인 루프)
    {
        // 여기에 다른 작업을 추가할 수 있습니다.
    }
}

// DMA 초기화 함수
static void dma_config(void)
{
    __HAL_RCC_DMA2_CLK_ENABLE();  // DMA2의 클럭을 활성화

    // DMA 핸들 설정
    DmaHandle.Instance = DMA_STREAM;  // 사용할 DMA 스트림을 설정
    DmaHandle.Init.Channel = DMA_CHANNEL;  // DMA 채널 설정
    DmaHandle.Init.Direction = DMA_MEMORY_TO_MEMORY;  // 메모리에서 메모리로 전송 설정
    DmaHandle.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;  // 주변 장치 데이터 정렬 설정 (워드 정렬)
    DmaHandle.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;  // 메모리 데이터 정렬 설정 (워드 정렬)
    DmaHandle.Init.PeriphInc = DMA_PINC_ENABLE;  // 주변 장치 주소 증가 설정
    DmaHandle.Init.MemInc = DMA_MINC_ENABLE;  // 메모리 주소 증가 설정
    DmaHandle.Init.Mode = DMA_NORMAL;  // 일반 DMA 모드 설정
    DmaHandle.Init.Priority = DMA_PRIORITY_HIGH;  // 높은 우선순위 설정
    DmaHandle.Init.FIFOMode = DMA_FIFOMODE_ENABLE;  // FIFO 모드 활성화
    DmaHandle.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_1QUARTERFULL;  // FIFO 임계값 설정
    DmaHandle.Init.MemBurst = DMA_MBURST_SINGLE;  // 메모리 버스트 설정 (단일 전송)
    DmaHandle.Init.PeriphBurst = DMA_PBURST_SINGLE;  // 주변 장치 버스트 설정 (단일 전송)

    HAL_DMA_Init(&DmaHandle);  // DMA 초기화 함수 호출

    // 콜백 함수 등록
    HAL_DMA_RegisterCallback(&DmaHandle, HAL_DMA_XFER_CPLT_CB_ID, TransferComplete);  // 전송 완료 콜백
    HAL_DMA_RegisterCallback(&DmaHandle, HAL_DMA_XFER_ERROR_CB_ID, TransferError);  // 전송 오류 콜백

    // DMA 인터럽트 우선순위 설정 및 활성화
    HAL_NVIC_SetPriority(DMA_STREAM_IRQ, 0, 0);  // DMA 인터럽트 우선순위 설정
    HAL_NVIC_EnableIRQ(DMA_STREAM_IRQ);  // DMA 인터럽트 활성화

    // DMA 전송 시작 (인터럽트 모드로 실행)
    HAL_DMA_Start_IT(&DmaHandle, (uint32_t)&aSRC_Const_Buffer, (uint32_t)&aDST_Buffer, BUFFER_SIZE);
}

// DMA 전송 완료 콜백 함수
static void TransferComplete(DMA_HandleTypeDef *DmaHandle)
{
    printf("Transfer complete!! \n\r");  // 전송 완료 메시지 출력
}

// DMA 전송 오류 콜백 함수
static void TransferError(DMA_HandleTypeDef *DmaHandle)
{
    printf("Transfer Error!! \n\r");  // 전송 오류 메시지 출력
}

// DMA 인터럽트 핸들러 (인터럽트가 발생하면 호출)
void DMA_STREAM_IRQHANDLER(void)
{
    HAL_DMA_IRQHandler(&DmaHandle);  // DMA 인터럽트 핸들링 함수 호출
}

// SysTick 인터럽트 핸들러 (타이머 기반의 시간 추적을 위한 필수 함수)
void SysTick_Handler(void)
{
    HAL_IncTick();  // HAL의 틱 타이머 증가 (타이머 기반의 시간 추적을 위해 필요)
}
