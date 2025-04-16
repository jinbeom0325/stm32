## STM32CubeMx 프로젝트 구조 

|번호|구간|	설명|
|-|-|-|
0|/* USER CODE BEGIN Header */|	파일 상단 헤더 (라이선스 및 파일 설명)|
1|#include "main.h"|	메인 헤더파일 포함|
2|/* USER CODE BEGIN Includes */|	사용자 헤더 추가 구간|
3|/* USER CODE BEGIN PTD/PD/PM */|사용자 typedef, define, macro 추가|
4|/* Private variables */|	전역 변수 및 핸들 정의|
5|/* USER CODE BEGIN PV */|	사용자 전역 변수 추가 구간|
6|/* Private function prototypes */|	함수 프로토타입 정의|
7|/* USER CODE BEGIN PFP */|	사용자 함수 프로토타입 정의 구간|
8|/* USER CODE BEGIN 0 */|	사용자 함수 정의, 전처리 코드 작성 구간|
9|main() 함수|	메인 루프 진입, 초기화 함수 호출|
10|/* USER CODE BEGIN 1, 2, 3 */|	main 함수 내 사용자 코드 삽입 위치|
11|주변 장치 초기화 함수들 (MX_XXX_Init)|	GPIO, UART, 타이머 등 초기화 코드|
12|SystemClock_Config()|	시스템 클럭 설정|
13|Error_Handler()|	에러 발생 시 처리 함수|
14|assert_failed()|	디버깅용 assert 실패 처리 함수|

### 각번호 상세 설명 
0. 파일 헤더
    - STM32CubeMX가 자동 생성한 파일 설명 및 저작권 정보
    - 건들 필요 없음  
1. #include "main.h"
    - 모든 핀, 핸들 선언, HAL 라이브러리 참조가 이 안에 있음
    - 이 파일은 CubeMX에서 자동 생성
 
2. /* USER CODE BEGIN Includes */
    - 사용자 헤더 파일이나 전역 배열을 넣는 곳
    ```c
    #include <stdio.h>
    char message[] = "Hello";
    ```
   
3. 사용자 정의 매크로, 타입 등
    - PTD : 사용자 typedef (구조체 정의 등)
    - PD	사용자 define
    - PM	사용자 매크로 함수
   
4. 전역 변수 & 핸들 정의
    - CubeMX에서 설정한 주변장치 핸들 생성됨
    ```c
    UART_HandleTypeDef huart2;
    TIM_HandleTypeDef htim11;
    ```
   
5. /* USER CODE BEGIN PV */
    - 사용자 전역 변수 작성
    ```c
    uint8_t rx_buffer[20];
    int adc_value = 0;
    ```
    
6. Private function prototypes
    - 함수 프로토타입 미리 선언
    ```c
    static void MX_GPIO_Init(void);
    static void MX_USART2_UART_Init(void);
    ```
7. /* USER CODE BEGIN PFP */
    - 사용자 함수 프로토타입 선언 위치
    ```c
    void PrintMessage(void);
    ```
    
8. /* USER CODE BEGIN 0 */
    - 사용자 함수 정의, 전처리 루틴 등(자주쓰는 전송코드 등) 
    ```c
    void PrintMessage(void) {
      HAL_UART_Transmit(&huart2, (uint8_t*)message, strlen(message), 100);
    }
    ```
    
9. int main(void)
    - 프로그램 진입점
    - HAL_Init() → 시스템 클럭 설정 → 주변장치 초기화 → 메인 루프(while(1))
    
10. USER CODE BEGIN 1/2/3
    - BEGIN 1 :	HAL 초기화 전에 실행할 사용자 코드
    - BEGIN 2 : 주변 장치 초기화 후, 무한 루프 전
    - BEGIN 3 : 무한 루프 내부 사용자 코드
    
11. MX_XXX_Init() 함수들
    - CubeMX 설정에 따라 자동 생성
    - GPIO, UART, ADC, Timer 등의 초기화
    
12. SystemClock_Config()
    - 클럭 소스(HSE, HSI), PLL 설정
    - CPU/버스 클럭 비율 설정 등
    
13. Error_Handler()
    - HAL 함수 실패 시 이 함수 호출됨
    - 무한 루프 돌면서 디버깅 가능
    
14. assert_failed()
    - assert 매크로 실패 시 호출 (디버깅용)
    - 일반적으로 사용 안함 (FULL_ASSERT 활성화 시만 유효)
***
### USER CODE BEGIN 0~3 차이
0 : 사용자 정의 함수 (void PrintMessage(void) 같은 것)

1 : 보통 main() 함수 내에서 초기 설정 이후에 사용자 로직을 넣는 자리, 메시지를 보내거나 타이머를 시작하는 등 초기 동작 수행 시 사용, 초기화전 사용자 코드 예를들어 HAL_Init();, MX_USART2_UART_Init();, MX_TIM11_Init();, MX_GPIO_Init();  

2 : 초기화가 완료된 이후에 사용자 기능을 실행할 수 있는 구간(타이머 시작, 인터럽트 시작, 첫 메시지 전송)

3 : 메인 반복 루프에 들어가는 사용자 코드 작성 영역(LED 토글, 센서 읽기, UART 수신 처리 등)
***
### 요약
```c
main.c
├── 헤더
├── include 및 define
├── 전역 변수
├── 함수 프로토타입
├── 사용자 함수
├── main()
│   ├── 초기화
│   ├── while(1) 루프
├── 주변장치 Init 함수들
├── SystemClock_Config()
├── Error_Handler()
```
***
