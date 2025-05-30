## volatile
volatile 사용 안 할 경우
- 최적화 O0 실행시 값이 메모리 위치에서 r3레지스터로 로드 - 중복명령 실행
- 최적화 O1 실행시 컴파일러가 모든 명령 제거

volatile 사용할 경우
- 최적화 O1 실행시 두 변수에 대한 연산 최적화 하지 않음
***
- uint8_t volatile my_data; = volatile uint8_t my_data; = 휘발성 변수
- uint32_t volatile *const 레지스터_이름 = (uint32_t *)주소;
- uint32_t const volatile *const 레지스터_이름 = (uint32_t *)주소; 형식은 읽기전용 메모리 주소에만 사용 
- const는 예기치 않은 변경으로부터 포인터를 보호하기 위해
- volatile는 "값이 언제든 바뀔 수 있다" 라고 컴파일러에게 알려주는 키워드

|키워드|	의미|
|--|--|
|volatile|	값 자주 바뀜(최적화x)|
|const|	포인터 주소는 고정(읽기전용)|
|*|	그 주소 안 값 사용|
***

ISR 버튼 전역 플레그 설정

While 무한 루프 안에서 전역플래그가 ISR에 의해 설정된경우 
버튼의 눌림 횟수 프린트 

버튼 플래그 재설정

|상황|	volatile 필요 여부|
|--|--|
|HW 레지스터 값 계속 바뀜|	필수|
|ISR 변수|	필수|
|일반 지역변수|	X 안써도 됨|
***
## pending bit
|개념|설명|
|--|--|
|Pending Bit|인터럽트 발생 알림 플래그|
|자동 Set|인터럽트 발생시 자동 1|
|Clear 방법|ISR 안에서 1 써서 지움|
|안 지우면?|	ISR 무한반복 → 시스템 먹통 가능|

예시 - Pending Bit = 초인종 불 들어온 표시
- 사람이 버튼 누름 → 불 켜짐
- 주인이 문 열어줌 (ISR 실행)
- 불 꺼줌 (Pending Bit Clear)
- 다음 손님 기다림 (다시 대기)
***
## Struct Padding
```c
#include <stdio.h>
struct test {
    char a;   // 1byte
    int b;    // 4byte
    char c;   // 1byt리















