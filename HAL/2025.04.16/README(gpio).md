GP그가 0 -> 1로 바뀔 때 인터럽트 발생
- 사용 예 : 버튼을 누르면 외부 풀다운 상태에서 3.3V로 전압 상승 -> 인터럽트 발생

### GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
- 기능: 해당 핀의 출력 신호 전환 속도를 설정
- 상세: LOW는 가장 낮은 스피드이며, 노이즈에 강하고 전력 소비가 낮음. 인터럽트 핀이나 일반 GPIO용으로 적합
- 주의: 이 설정은 출력 핀에만 실질적 영향을 주고 입력 핀에는 거의 영향 없음

### HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
- 기능: EXTI15_10_IRQn 인터럽트의 우선순위 설정
- 상세: 선점 우선순위 그룹과 서브 우선순위를 둘 다 0으로 설정하여 이 인터럽트가 가장 높은 우선순위를 갖게 해줌(선점, 서브 순서)
- 중요: 인터럽트 우선순위 충돌이 없도록 다른 IRQ들과 함께 설계해야 함 (동시발생하면 IRQ번호 낮은 거 우선 처리 (EXTI0_IRQn → IRQ 번호 6)

### HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
- 기능: NVIC(인터럽트 컨트롤러)에서 해당 IRQ를 활성화
- 상세: EXTI15_10_IRQn은 PC13을 포함한 EXTI 10~15 핀의 인터럽트 요청을 처리하는 IRQ
- 결과: 실제 인터럽트가 발생하면 EXTI15_10_IRQHandler() 함수가 호출됨

### 동작요약
버튼 누르면 low에서 high 바뀌는 순간 EXTI15_10_IRQHandler() 함수가 호출되어 인터럽트가 발생 (PC13핀에 연결된 인터럽트 요청 처리)
그다음 HAL_GPIO_EXTI_Callback(GPIO_Pin) 함수가 호출되고 LED동작


