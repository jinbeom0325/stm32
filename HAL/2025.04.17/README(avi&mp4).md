##  AVI (Audio Video Interleave)
### 기반 포맷: RIFF (Resource Interchange File Format)
```c
//avi 구조 
RIFF Chunk (전체 파일)
├─ hdrl (Header List)
│   ├─ avih (AVI Header)
│   └─ strl (Stream List)
│       ├─ strh (Stream Header)
│       └─ strf (Stream Format)
├─ movi (Movie Data: 실제 오디오/비디오 프레임)
└─ idx1 (Optional Index Chunk - 빠른 탐색용)
```
- avih: 전체 AVI 파일의 정보 (프레임률, 해상도 등)
- strh: 각 스트림(비디오, 오디오 등)의 속성
- movi: 실제 데이터가 저장됨
- idx1: (옵션) 프레임 위치 인덱스
### 특징
- 비교적 단순한 구조
- 동기화가 정확 (오디오/비디오 싱크가 잘 맞음)
- 하지만 확장성이 떨어지고, 고급 기능(자막, 챕터 등)은 거의 없음
- 큰 파일에 비효율적이고, 스트리밍에는 적합하지 않음
***
## MP4 (MPEG-4 Part 14)
### 기반 포맷: ISO Base Media File Format (ISO/IEC 14496-12)
```c
ftyp (file type)
moov (movie metadata)
├─ mvhd (movie header)
├─ trak (track – 비디오, 오디오 등)
│   ├─ tkhd (track header)
│   └─ mdia (media information)
│       ├─ mdhd, hdlr, minf, stbl...
mdat (media data)
```조요약
| 항목 | AVI | MP4 |
|------|-----|-----|
| **구조** | **RIFF 기반**<br>→ 파일을 덩어리(chunk)로 나누는 단순한 구조. (Resource Interchange File Format) | **ISO BMFF 기반 (box 구조)**<br>→ 각 정보를 ‘박스(Box)’ 단위로 나눠 저장. 자막, 챕터도 박스로 저장 가능. (ISO Base Media File Format) |
| **오디오/비디오 코덱** | **제한적**<br>→ 주로 DivX (비디오), MP3 (오디오) 등만 사용. 최신 코덱과 호환 어려움. | **매우 다양**<br>→ H.264, H.265(HEVC), AAC 등 최신 고효율 코덱을 지원. 용량 작고 품질 좋음. |
| **자막/챕터 지원** | **거의 없음**<br>→ 자막을 따로 .srt로 넣어야 하거나 안 되는 경우도 있음. | **있음**<br>→ 자막, 챕터, 언어 선택 등 다양한 트랙을 포함 가능. |
| **스트리밍 적합성** | **낮음**<br>→ 전체 파일을 다운받아야 재생 가능. 실시간 전송엔 부적합. | **높음**<br>→ 스트리밍에 적합하도록 설계되어 있어 YouTube, Netflix 등에 많이 쓰임. |
| **사용처** | **옛날 Windows 기반 영상**<br>→ 캠코더, 윈도우 미디어 플레이어 등에서 사용. | **현재 대부분의 온라인 영상 포맷**<br>→ 스마트폰, 웹, 유튜브, OTT 서비스 등 거의 모든 플랫폼에서 사용. |
| **확장성** | **낮음**<br>→ 기능 추가가 어려움. 새 코덱이나 기능을 넣기 어려움. | **높음**<br>→ 새로운 기능(예: 360도 영상, 자막, 챕터 등)을 쉽게 추가 가능. |


## 확장자만 바꿀 시 
실제로 파일 포맷을 바꾼 게 아니기 때문에 문제가 생긴다.

### 1. 코덱 호환성 문제
- AVI에서는 흔히 MP3, PCM, AC3 같은 오디오 코덱을 사용
- MP4에서는 주로 AAC를 사용

일부 플레이어나 디바이스는 MP4 안에서 AC3 같은 코덱을 지원하지 않음

### 2. 컨테이너 포맷 차이
MP4는 ISO BMFF 기반, AVI는 RIFF 기반이라서 데이터 구조가 완전 다르기 때문에 

→ MP4로 인식하는 플레이어는 AVI 구조의 오디오 트랙을 해석하지 못할 수 있다.

### 3. 인덱스 및 메타데이터 구조 차이
- MP4는 moov 박스에 메타데이터가 있음
- AVI는 idx1 등을 써서 오디오/비디오 인덱싱

이걸 혼동하게 되면 오디오 위치를 못 찾거나 무시한다.







