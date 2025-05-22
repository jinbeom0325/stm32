## Free Real-Time Operating System
**마이크로컨트롤러(MCU)**에서 멀티태스킹을 쉽게 구현할 수 있도록 도와주는 RTOS

오픈소스 실시간 운영체제

### Free RTOS 구성요소
| 구성 요소           | 설명                                   |
| --------------- | ------------------------------------ |
| **Task**        | 실행 단위. 일반적인 함수처럼 작성하고 FreeRTOS가 스케줄링 |
| **Queue**       | 태스크 간 데이터를 주고받는 안전한 통신 수단            |
| **Semaphore**   | 리소스 보호 및 태스크 간 동기화                   |
| **Mutex**       | 뮤텍스 세마포어. 상호 배제를 보장 (특히 공유자원 보호용)    |
| **Timer**       | 소프트웨어 타이머. 지연 작업 또는 주기적 작업 처리        |
| **Event Group** | 여러 태스크가 특정 이벤트 비트 상태를 기다릴 수 있음       |
| **Tick**        | FreeRTOS의 시간 단위 (보통 1ms 단위로 설정됨)     |

```c
if (osSemaphoreWait(ProcessSPHandle, osWaitForever) == osOK) //대기하다가 osSemaphoreWait로  세마포어 획득
ulTaskNotifyTake(pdTRUE, portMAX_DELAY); //다른 task가 깨울때까지 대기 (give로깨움)
xTaskNotifyGive(processTaskHandle); //프로세스 task깨우기
osSemaphoreRelease(ProcessSPHandle); //세마포어 반환 
```
세마포어는 공유 자원에 여러 Task가 동시에 접근하지 않도록 제어하는 장치
