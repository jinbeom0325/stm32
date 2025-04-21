## SPI
- 직렬 통신 프로토콜 중 하나로 한 개의 Master(주장치)가 여러 개의 Slave(종속장치)와 양방향(Full-Duplex) 통신을 할 수 있게 하는 것 

### 마스터(Master)와 슬레이브(Slave)
- 마스터가 통신할 슬레이브의 SS 핀을 LOW로 내림 (선택)
- 마스터가 클럭을 발생시킴 (SCLK)
- 데이터가 MOSI를 통해 슬레이브로 전송됨
- 동시에 슬레이브는 MISO를 통해 마스터로 응답함
- 데이터 송수신 완료되면, 마스터는 SS 핀을 HIGH로 바꿔서 통신 종료

### SPI 통신에 필요한 4개의 라인
라인 이름 | 설명 | 별칭
--|--|--
MOSI | Master Out, Slave In → 마스터가 슬레이브에게 데이터 보낼 때 | SDIO, SI
MISO | Master In, Slave Out → 슬레이브가 마스터에게 보낼 때 | SDO
SCLK | Serial Clock → 마스터가 만들어주는 클럭 | CLK
SS or NSS | Slave Select → 어떤 슬레이브랑 통신할지 선택하는 신호 | CS (Chip Select)

### 통신 방식

1. Master가 SS 핀을 LOW로 내려서 슬레이브 선택

2. 동시에 Master와 Slave의 Shift Register에서 데이터가 한 비트씩 이동 (클럭 기준으로)

3. 한 바이트(8비트) 전송이 끝나면 둘은 데이터를 서로 교환하게 됨

4. 필요하면 다음 바이트 전송 계속

5. 통신이 끝나면 SS 핀을 HIGH로 해서 슬레이브 연결 해제

### SPI 통신 모드 
Mode | CPOL | CPHA | 의미
--|--|--|--
0 | 0 | 0 | 처음 상태 LOW, 첫 번째 상승 엣지에서 샘플링
1 | 0 | 1 | 처음 상태 LOW, 두 번째 하강 엣지에서 샘플링
2 | 1 | 0 | 처음 상태 HIGH, 첫 번째 하강 엣지에서 샘플링
3 | 1 | 1 | 처음 상태 HIGH, 두 번째 상승 엣지에서 샘플링

- CPOL은 클럭이 기본적으로 HIGH인지 LOW인지
- CPHA는 클럭의 어느 순간에 데이터 샘플링 할지
- **예) CPOL이 LOW면 처음에 HIGH로 올라가야 시작 = 첫 엣지가 상승엣지, 두번째 엣지는 하강**

### NSS모드 
- 슬레이브 선택을 의미하는 핀
- 소프트웨어 NSS: GPIO로 직접 제어
- 하드웨어 NSS: SPI 하드웨어가 자동 제어
