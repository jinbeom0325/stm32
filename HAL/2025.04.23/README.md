## #define DEVICE_ADDR 0x53<<1 
```c
[7비트 슬레이브 주소][1비트 R/W]  //쓰기 : 0 ,읽기 : 1
```
- 0x53은 ADXL345센서의 기본 I2C주소(데이터시트 참조)
- STM32 HAL 함수 HAL_I2C_Master_Transmit 같은 함수는 R/W 비트를 자동으로 붙이기 때문에,
슬레이브 주소를 왼쪽으로 1비트 시프트해줘야 함
- 0x53은 실제 I2C 프레임에서 0xA6 or 0xA7로 전송됨
***

```c
// HAL 라이브러리에서 I2C 메모리 방식으로 데이터를 읽을 때 사용하는 함수
HAL_I2C_Mem_Read(&hi2c1, DEVICE_ADDR, req, 1, (uint8_t *)data_rec, 6, 100);
```
인자 | 설명
--|--
&hi2c1 | 사용 중인 I2C 포트의 핸들입니다. (I2C1 사용 중)
DEVICE_ADDR | I2C 장치 주소
req | I2C 장치 내부의 레지스터 주소 또는 메모리 주소(읽고 싶은 위치)
1 | 메모리 주소 크기 (바이트 수)입니다. 보통 1 or 2 사용
(uint8_t *)data_rec | 수신 데이터를 저장할 버퍼
6 | 몇 바이트를 읽을지 (6바이트)
100 | 타임아웃 (ms 단위). 100ms 이내에 통신 완료되지 않으면 에러 발생
***

```c
// I2C 장치의 특정 레지스터(device ID 등) 값을 1바이트 읽어오는 코드
HAL_I2C_Mem_Read(&hi2c1, DEVICE_ADDR, req, 1, &device_id, 1, 100);
```
