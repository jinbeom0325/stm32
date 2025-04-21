#include "stm32f4xx_hal.h"               // STM32 HAL 드라이버 라이브러리 (핵심 HAL 기능 포함)
#include "tim.h"                         // 타이머 관련 초기화 함수 헤더

// 타이머를 1초 간격으로 설정 (즉, 1Hz 주파수로 설정)

// 시스템 기본 주파수 = 16,000,000 Hz
// 기본 PCLK1 주파수 = 16,000,000 Hz
// 기본 PCLK2 주파수 = 16,000,000 Hz

// 타이머 프리스케일러 설정: 1600 => 16,000,000 / 1600 = 10,000 (10kHz)
// 타이머 기간 (자동 리로드 값) = 10,000 => 10,000 / 10,000 = 1Hz

TIM_HandleTypeDef TimHandle;  // 타이머 핸들 구조체 선언

// 타이머 초기화 함수
void tim_timebase_init(void)
{
    _TIMx_CLK_ENABLE;  // TIM3(또는 선택한 타이머)에 대한 클럭 활성화 (타이머 동작을 위해 필요)

    // 타이머 핸들 초기화
    TimHandle.Instance = TIMx;  // 타이머 인스턴스를 TIM3로 설정
    TimHandle.Init.Prescaler = 1600 - 1;  // 프리스케일러 설정 (16,000,000 / 1600 = 10,000)
    TimHandle.Init.Period = 10000 - 1;    // 자동 리로드 값 설정 (10,000 / 10,000 = 1Hz)
    TimHandle.Init.ClockDivision = TIM_COUNTERMODE_UP;  // 카운터 증가 모드로 설정
    TimHandle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;  // 자동 리로드 프리로드 비활성화

    HAL_TIM_Base_Init(&TimHandle);  // 타이머 기본 초기화 함수 호출

    HAL_NVIC_SetPriority(TIMx_IRQn, 0, 0);  // 타이머 인터럽트 우선순위 설정 (우선순위 0, 서브 우선순위 0)
    HAL_NVIC_EnableIRQ(TIMx_IRQn);  // 타이머 인터럽트 활성화

    HAL_TIM_Base_Start_IT(&TimHandle);  // 타이머 시작 및 인터럽트 활성화 (주기적으로 인터럽트 발생)
}

// 타이머 인터럽트 핸들러 (타이머 인터럽트 발생 시 호출됨)
void TIMx_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&TimHandle);  // 타이머 인터럽트 처리 함수 호출
}
