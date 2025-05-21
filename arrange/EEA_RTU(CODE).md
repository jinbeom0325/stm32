## code lora.h
- BANDWIDTH는 대역폭 클수록 빠르고 감도/거리 감소
  - SLEEP_MODE: 전력 절약
  - STNBY_MODE: 대기 상태
  - TRANSMIT_MODE: 송신
  - RXCONTIN_MODE: 지속 수신
  - RXSINGLE_MODE: 단일 패킷 수신

- CODING RATE는 부호화율 에러정정 코드 비율 클수록 내구성 증가, 데이터율 감소
- SPREADING FACTOR는 확산인자 높을수록 감도/거리 증가 속도 감소
- POWER GAIN는 전송 출력 파워 설정
- REGISTERS는 레지스터 주소
- LORA STATUS는 상태코드 lora통신 함수 실행 후 결과 코드로 사용
***
## Comprotocol.h
| 함수 이름                                                                       | 설명                              |
| --------------------------------------------------------------------------- | ------------------------------- |
| `uint8_t uchGetBLID(void);`                                                 | 장치의 고유 ID (예: Board ID)를 반환     |
| `void vUpdateTable(uint8_t _uchCommand, uint8_t _uchID, uint8_t _uchData);` | 테이블에 특정 명령에 따라 ID와 데이터로 업데이트 수행 |
| `void vSetTimerTable(void);`                                                | 타이머 관련 테이블을 설정 (예: 시간 동기화용)     |

### 패킷생성 및 처리 관련
| 함수 이름                                                                    | 설명                     |
| ------------------------------------------------------------------------ | ---------------------- |
| `bool bIsCommand(uint8_t _uchCommand);`                                  | 유효한 명령인지 검사            |
| `uint8_t uchCalChecksum(uint8_t *uchpPacket, uint8_t _uchPacketLength);` | 주어진 패킷에 대한 체크섬 계산      |
| `uint8_t uchMakePirPacket(...);`                                         | PIR 관련 명령을 담은 패킷 생성    |
| `uint8_t uchTransLoRaPacket(...);`                                       | LoRa용 전송 패킷 생성 및 전송    |
| `uint8_t uchTransUartPacket(...);`                                       | UART용 전송 패킷 생성 및 전송    |
| `void vMakeTablePacket(...);`                                            | 전체 테이블 정보 포함 패킷 구성     |
| `void vMakePacket(...);`                                                 | 단일 명령 패킷 생성 (기본 송신 패킷) |

### 수신처리
| 함수 이름                           | 설명                      |
| ------------------------------- | ----------------------- |
| `void vCheckRxLoRaPacket(...);` | 수신된 LoRa 패킷을 확인 및 분기 처리 |
| `void vCheckRxUartPacket(...);` | 수신된 UART 패킷을 확인 및 분기 처리 |
| `void vProcLoRaPacket(...);`    | LoRa 패킷을 실제로 파싱하고 동작 수행 |
| `void vProcUartPacket(...);`    | UART 패킷을 실제로 파싱하고 동작 수행 |

### 재전송 및 응답 관리
| 함수 이름                               | 설명                           |
| ----------------------------------- | ---------------------------- |
| `void vCheckRspTable(...);`         | 응답 테이블을 확인하여 재전송 여부 판단       |
| `void vCompareSaveId(...);`         | 응답 패킷에서 ID를 비교하여 저장 및 정합성 검사 |
| `int iGetCmdFlag(void);`            | 현재 명령 수행 여부 상태 반환            |
| `int iGetResendCount(void);`        | 재전송 횟수 확인                    |
| `void vSetResendCount(int _value);` | 재전송 횟수 설정                    |

### PIR ID 관리
| 함수 이름                                                       | 설명                          |
| ----------------------------------------------------------- | --------------------------- |
| `int iCheckPirIdBit(uint8_t *_uchPirList);`                 | PIR ID 목록에서 설정된 ID 비트 확인    |
| `void vCheckPirId(uint8_t _uchPirId, uint8_t *uchCheckId);` | 단일 PIR ID 체크 후 결과 저장        |
| `void vUpdatePirId(void);`                                  | 수신된 PIR ID를 기반으로 전체 ID 업데이트 |
| `void vInitPirId(void);`                                    | PIR ID 시스템 초기화              |

### 전체테이블 정보 송신
| 함수 이름                                                                         | 설명                    |
| ----------------------------------------------------------------------------- | --------------------- |
| `void vSendTxTablePacket(UART_HandleTypeDef *huart, DeviceInfo *SetDevices);` | UART를 통해 전체 테이블 정보 송신 |
***
## main.c
```c
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    if(GPIO_Pin == DIO0_Pin)
    {
        uchPacketSize = LoRa_receive(&RtuLoRa, &RxLoRaData, MAX_PACKET_SIZE);
        vTaskNotifyGiveFromISR(LoraTaskHandle, &xHigherPriorityTaskWoken);

        // ISR 내에서 더 높은 우선순위 태스크가 준비되었다면 즉시 전환
        portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
    }
}
```

```c
// task : 작업단위, RTOS : 프로세스 스케쥴링
```
