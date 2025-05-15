## 5.15

eea-cs : eea-m 상태 감지 모니터링하여 제어 컨트롤 및 송수신 hex value
eea-rtu : EEA-CS와 RS-232C로 연결 EEA-CS로부터 제어 데이터를 수신하거나, EEA-M의 상태 정보를 EEA-CS에 전송 EEA-RTU는 EEA-CS로부터 수신한 제어 데이터를 EEA-M에 전달하고, EEA-M의 변경상태를 수신받아 EEA-CS로 전달
eea-m : EEA-RTU로부터 제어 데이터를 수신 받아 연결된 LED전등을 켜거나 끄고, 자신의 변경된 상태를 EEA-RTU로 전송
EEA-M은 연결된 PIR 센서를 통해 객체가 감지되면 자동으로 전등을 켜고 그 정보를 EEA-RTU로 전송
led 전구 : EEA-M과 연결되어 AC220V가 입력되면 불이 켜짐

## eea-m
ssr: SSR은 전자식 릴레이로, 기계적인 접점 없이 트랜지스터, 트라이액(TRIAC), 포토커플러 등으로 전기를 스위칭 (모터,히터,plc 제어 등)

ra-02 : RA-02는 LoRa 무선 통신 모듈로, Semtech의 SX1278 칩을 기반으로 한 저전력 장거리 무선통신 모듈(spi로 mcu연결)

### 동작방식 
- PIR 센서가 사람을 감지함

- 조도 센서가 어두운 상태임

- 조건이 만족되었기 때문에, RTU 또는 LoRa 모듈이 led on 명령을 자동화 모듈에 전달함

- 이때 자동화 모듈이 SSR에 신호를 주고, SSR이 조명을 실제로 ON 시킴


