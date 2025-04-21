#ifndef TIM_H_                      // TIM_H_ 가 정의되지 않았을 경우에만 아래 코드 포함 (헤더 중복 방지)
#define TIM_H_

#define TIMx                TIM3    // 사용할 타이머를 TIM3으로 지정 (코드에서 TIMx로 TIM3을 대신 사용)
#define _TIMx_CLK_ENABLE    __HAL_RCC_TIM3_CLK_ENABLE() // TIM3의 클럭을 활성화하는 매크로
#define TIMx_IRQn           TIM3_IRQn   // TIM3 인터럽트 요청 번호 (IRQ 번호)
#define TIMx_IRQHandler     TIM3_IRQHandler // TIM3의 인터럽트 핸들러 함수 이름

void tim_timebase_init(void);      // 타이머를 시간 기준으로 초기화하는 함수 선언

#endif                              // #ifndef TIM_H_에 대한 종료 지시어
