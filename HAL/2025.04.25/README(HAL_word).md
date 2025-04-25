## HAL 함수 관련 용어 정리 진행중

### GPIO(입출력 핀 제어)
함수 | 설명
--|--
HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_SET/RESET) | 출력 핀 HIGH/LOW 설정
HAL_GPIO_ReadPin(GPIOx, GPIO_Pin) | 입력 핀 상태 읽기 (GPIO_PIN_SET or GPIO_PIN_RESET 반환)
HAL_GPIO_TogglePin(GPIOx, GPIO_Pin) | 핀 상태 토글 (HIGH ↔ LOW)
HAL_GPIO_Init(GPIOx, &GPIO_InitStruct) | 핀 모드, 속도, 풀업/다운 설정
HAL_GPIO_DeInit(GPIOx, GPIO_Pin) | 핀 설정 해제
***
### I2C(Inter-Integrated Circuit)
함수 | 설명
--|--
HAL_I2C_Master_Transmit(&hi2c, addr, pData, size, timeout) | 마스터가 슬레이브로 데이터 전송
HAL_I2C_Master_Receive(&hi2c, addr, pData, size, timeout) | 마스터가 슬레이브로부터 데이터 수신
HAL_I2C_Mem_Write(&hi2c, addr, memAddr, size, data, size, timeout) | 슬레이브의 특정 메모리 주소에 쓰기
HAL_I2C_Mem_Read(&hi2c, addr, memAddr, size, data, size, timeout) | 슬레이브의 특정 메모리 주소에서 읽기
HAL_I2C_Init(&hi2c) | I2C 초기화
HAL_I2C_DeInit(&hi2c) | I2C 해제
***


