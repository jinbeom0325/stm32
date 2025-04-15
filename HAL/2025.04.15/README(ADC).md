### 단일변환모드

```c
while(1)
{
    HAL_ADC_Start(&hadc1);                        // ADC 변환 시작 요청
    HAL_ADC_PollForConversion(&hadc1, 1);         // 변환이 완료될 때까지 기다림
    sensor_value = pa0_adc_read();                // 변환된 값 읽기
    printf("The sensor value : %d\n\r", (int)sensor_value); // 시리얼로 출력
}
```
### 단일변환과 연속변환 차이
|구분|	단일 변환 (Single)|	연속 변환 (Continuous)|
|--|--|--|
|변환 시작 방식|	매번 소프트웨어로 시작해야 함 (HAL_ADC_Start)|	한 번 시작하면 자동 반복|
|값 얻는 방식|	매번 HAL_ADC_PollForConversion 호출 필요|	바로 읽거나 인터럽트/타이머로 읽으면 됨|
|코드 구조 차이|	루프 안에서 계속 Start → Poll → Read|	루프에서는 Read만 하거나, 인터럽트 이용 가능|
|CPU 점유율|	상대적으로 높음|	낮음 (자동 변환되므로 읽기만 하면 됨)|
|사용 목적| 느린 센서, 불규칙한 읽기|	빠르게 계속 값을 읽고 싶은 경우 (예: 가변 저항, 마이크 등)|
