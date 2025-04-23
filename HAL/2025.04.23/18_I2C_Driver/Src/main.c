#include <stdio.h>                         // 표준 입출력 함수 사용을 위한 헤더
#include "stm32f4xx_hal.h"                // STM32 HAL 라이브러리 헤더
#include "uart.h"                         // UART 관련 사용자 정의 헤더 (현재 사용되지 않음)
#include "adc.h"                          // ADC 관련 사용자 정의 헤더 (현재 사용되지 않음)

// ADXL345 장치의 I2C 주소 (7비트 주소를 HAL에 맞게 왼쪽 시프트)
#define DEVICE_ADDR           (0x53 << 1)   // 실제 8비트 주소는 0xA6

// ADXL345 내부 레지스터 주소 정의
#define DEVID_R               0x00    // 디바이스 ID 레지스터 주소
#define POWER_CTL_R           0x2D    // 전원 제어 레지스터
#define DATA_FORMAT_R         0x31    // 데이터 포맷 설정 레지스터
#define DATA_START_ADDR       0x32    // X, Y, Z 데이터가 저장되는 시작 주소

// 레지스터에 설정할 값들
#define FOUR_G                0x01    // ±4g 범위 설정 값
#define RESET                 0x00    // 전원 제어 레지스터 초기화 값
#define SET_MEASURE_B         0x08    // 측정 모드 활성화 비트 (Measure bit)

// ±4g 범위일 때의 스케일 팩터 (datasheet 기준 1 LSB = 0.0078g)
#define FOUR_G_SCALE_FACT     0.0078f

// I2C1 핸들 구조체 선언
I2C_HandleTypeDef hi2c1;

// 함수 프로토타입 선언
void i2c1_init(void);                      // I2C1 초기화 함수
void adxl_write(uint8_t req, uint8_t value);       // ADXL345에 데이터 쓰기
void adxl_read_values(uint8_t req);                // ADXL345로부터 가속도 데이터 읽기
void adxl_read_address(uint8_t req);               // ADXL345 레지스터에서 단일 바이트 읽기
void adxl_init(void);                              // ADXL345 초기화 함수

// 전역 변수
uint8_t data_rec[6];       // 6바이트 데이터 수신 버퍼 (X, Y, Z 각 2바이트)
uint8_t device_id;         // 디바이스 ID 저장 변수

int16_t x, y, z;           // X, Y, Z 축의 16비트 정수형 가속도 원시 값
float xg, yg, zg;          // 변환된 g 단위의 가속도 값

// 메인 함수 시작
int main()
{
    HAL_Init();                // HAL 라이브러리 초기화 (시계, NVIC 등 내부 설정)
    i2c1_init();               // I2C1 초기화
    adxl_init();               // ADXL345 센서 초기화

    while (1)                  // 무한 루프
    {
        adxl_read_values(DATA_START_ADDR);  // ADXL345에서 6바이트 데이터 읽기

        // 각 축 데이터는 2바이트이며 LSB가 먼저 옴 → 16비트 정수로 병합
        x = ((data_rec[1] << 8) | data_rec[0]);
        y = ((data_rec[3] << 8) | data_rec[2]);
        z = ((data_rec[5] << 8) | data_rec[4]);

        // 정수값을 실수(g) 단위로 변환
        xg = x * FOUR_G_SCALE_FACT;
        yg = y * FOUR_G_SCALE_FACT;
        zg = z * FOUR_G_SCALE_FACT;

        HAL_Delay(10);         // 10ms 지연 (100Hz 측정 주기)
    }
}

// ADXL345 레지스터에 값 쓰기 함수
void adxl_write(uint8_t req, uint8_t value)
{
    uint8_t data[2];
    data[0] = req;             // 레지스터 주소
    data[1] = value;           // 설정할 값

    // I2C를 통해 2바이트 전송 (주소 + 값)
    HAL_I2C_Master_Transmit(&hi2c1, DEVICE_ADDR, data, 2, 100);
}

// ADXL345의 연속 레지스터 값 읽기 함수 (주로 가속도 측정 값 읽을 때 사용)
void adxl_read_values(uint8_t req)
{
    // req 레지스터 주소부터 시작해 6바이트 연속 읽기 (X, Y, Z 각 2바이트)
    HAL_I2C_Mem_Read(&hi2c1, DEVICE_ADDR, req, 1, data_rec, 6, 100);
}

// ADXL345의 특정 레지스터에서 단일 바이트 값 읽기 (예: DEVID 확인용)
void adxl_read_address(uint8_t req)
{
    HAL_I2C_Mem_Read(&hi2c1, DEVICE_ADDR, req, 1, &device_id, 1, 100);
}

// ADXL345 초기화 함수
void adxl_init(void)
{
    adxl_read_address(DEVID_R);                 // 1. 디바이스 ID 읽기 (선택적 확인용)
    adxl_write(DATA_FORMAT_R, FOUR_G);          // 2. ±4g 모드 설정
    adxl_write(POWER_CTL_R, RESET);             // 3. 전원 제어 레지스터 초기화
    adxl_write(POWER_CTL_R, SET_MEASURE_B);     // 4. 측정 모드 활성화
}

// I2C1 초기화 함수 (PB8: SCL, PB9: SDA)
void i2c1_init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    __HAL_RCC_GPIOB_CLK_ENABLE();               // GPIOB 포트 클럭 활성화

    GPIO_InitStruct.Pin = GPIO_PIN_8 | GPIO_PIN_9;   // SCL, SDA 핀 설정
    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;          // 오픈 드레인 출력
    GPIO_InitStruct.Pull = GPIO_PULLUP;              // 내부 풀업 사용
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;  // 고속 설정
    GPIO_InitStruct.Alternate = GPIO_AF4_I2C1;         // AF4: I2C1 기능 매핑

    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);     // 설정된 구조체로 GPIO 초기화

    __HAL_RCC_I2C1_CLK_ENABLE();                // I2C1 클럭 활성화

    // I2C 설정 구조체 초기화
    hi2c1.Instance = I2C1;
    hi2c1.Init.ClockSpeed = 400000;             // 400kHz (Fast Mode)
    hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;     // 듀티 사이클 2
    hi2c1.Init.OwnAddress1 = 0;                 // 마스터는 주소 필요 없음
    hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;  // 7비트 주소 모드
    hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
    hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
    hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;

    HAL_I2C_Init(&hi2c1);                       // I2C 설정 적용
}

// SysTick 인터럽트 핸들러 함수 (1ms 주기로 호출됨)
void SysTick_Handler(void)
{
    HAL_IncTick();     // HAL 내부 Tick 카운터 증가 (Delay 함수 등에 사용됨)
}
