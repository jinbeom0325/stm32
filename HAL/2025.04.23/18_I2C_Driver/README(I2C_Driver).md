### #define DEVICE_ADDR 0x53<<1 
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
&hi2c1 | 사용 중인 I2C 포트의 핸들 (I2C1 사용 중)
DEVICE_ADDR | I2C 장치 주소
req | I2C 장치 내부의 레지스터 주소 또는 메모리 주소(읽고 싶은 위치)
1 | 메모리 주소 크기 (바이트 수) 보통 1 or 2 사용
(uint8_t *)data_rec | 수신 데이터를 저장할 버퍼
6 | 몇 바이트를 읽을지 (6바이트)
100 | 타임아웃 (ms 단위). 100ms 이내에 통신 완료되지 않으면 에러 발생
***

```c
// I2C 장치의 특정 레지스터(device ID 등) 값을 1바이트 읽어오는 코드
HAL_I2C_Mem_Read(&hi2c1, DEVICE_ADDR, req, 1, &device_id, 1, 100);
```
***

## 코드부분
### #define매크로
- DEVICE_ADDR: ADXL345의 I2C 주소 7비트 주소 0x53 → STM32 HAL에서는 8비트 주소로 사용하므로 1비트 왼쪽 시프트 (0xA6)
- DEVID_R, POWER_CTL_R 등: ADXL345 내부 레지스터 주소
- FOUR_G, RESET, SET_MEASURE_B: 레지스터에 설정할 값들
- FOUR_G_SCALE_FACT: ±4g 설정에서 1LSB가 의미하는 g 단위 값 (0.0078g)
***

### i2c1_init()
- GPIOB의 8번(SCL), 9번(SDA) 핀을 I2C1 기능에 맞게 설정
  
- I2C1 인터페이스 초기화
  - 클럭: 400kHz
  - 7비트 주소 모드, 일반 콜/듀얼 주소/노 스트레치 기능은 모두 비활성화
    
### adxl_init() ADXL345 센서 설정 함수
```c
// 디바이스 ID읽기
adxl_read_address(DEVID_R); //장치 정상연결 확인 (0xE5)
```
```c
// 데이터 포맷 설정
adxl_write(DATA_FORMAT_R, FOUR_G); //±4g 범위 설정
```
```c
//초기화 후 측정 시작
//POWER_CTL 레지스터 초기화 후 Measure bit(0x08) 설정하여 데이터 측정 시작
adxl_write(POWER_CTL_R, RESET);
adxl_write(POWER_CTL_R, SET_MEASURE_B);
```
```c
// 시작 주소 0x32부터 6바이트 읽기
// 각각 X, Y, Z 축의 LSB, MSB가 순서대로 저장됨
HAL_I2C_Mem_Read(&hi2c1, DEVICE_ADDR, req, 1, data_rec, 6, 100);
```
***
### main() 
```c
//2바이트 조합하여 16비트 정수로 변환 (Little Endian 순서)
x = ((data_rec[1] << 8) | data_rec[0]);
```
```c
//정수형 값을 g 단위 실수값으로 변환 (0.0078g/LSB)
xg = x * FOUR_G_SCALE_FACT;
```








