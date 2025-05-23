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
osSemaphoreRelease(ProcessSPHandle); //세마포어 반환  (코드 마지막)
ulTaskNotifyTake(pdTRUE, portMAX_DELAY); //다른 task가 깨울때까지 대기 (give로깨움)
xTaskNotifyGive(processTaskHandle); //프로세스 task깨우기 (코드 마지막쯤) 

```
세마포어는 공유 자원에 여러 Task가 동시에 접근하지 않도록 제어하는 장치
| 상황                           | 추천 방식                       |
| ---------------------------- | --------------------------- |
| 단일 Task 간 동기화 (ISR → Task 등) | `Task Notification`         |
| 여러 Task 간 동기화 필요             | `Semaphore`                 |
| ISR과 Task 간 자원 보호가 필요한 경우    | `Binary/Counting Semaphore` |
| 빠르고 lightweight한 통신          | `Task Notification`         |
***
### Semaphore 방식 (RTOS 자원 동기화)
- osSemaphoreWait(ProcessSPHandle, osWaitForever)
  → 이 Task는 세마포어가 주어질 때까지 대기함.

- osSemaphoreRelease(ProcessSPHandle)
→ 이걸 호출하면, 세마포어를 기다리던 Task가 깨서 작업을 시작함.
uart는 양방향이라 

ISR이나 다른 Task에서도 호출 가능.
***
### Task Notification 방식 (경량화된 Task 간 신호)
- ulTaskNotifyTake(pdTRUE, portMAX_DELAY)
  → 이 Task는 알림이 올 때까지 무기한 대기함.

- xTaskNotifyGive(processTaskHandle)
  → 해당 Task에 알림(Notification) 을 보내서 깨어나게 함.

매우 빠르고 메모리 효율적. 단일 Task에만 해당.
로라가 이 방식인 이유가 단일 이벤트 rtu쪽에만 주는거 빠른게 목적
***
### 추가설명
FreeRTOS가 systick을 쓰므로  HAL은 TIM6을 Tick Timer로 
자신의 task가 끝나면 block상태이고 모든 task가 끝나면 FreeRTOS는 **Idle Task**를 실행 (저전력모드)
***

```c
//꺼내는 위치front부터 저장위치rear 전까지 
Index:   0   1   2   3   4   5   6   7   8   9

         ↑                               ↑
         
       시작                            끝 인덱스
```
uchPacketBuffer[5 + _uchDataLen + 1] = uchCalChecksum(uchPacketBuffer, LORA_PACKET_LEN - 2); 

-2한 이유는 체크섬은 ETX랑 본인(체크섬)은 빼고 계산해야함



