## volatile
volatile 사용 안 할 경우
- 최적화 O0 실행시 값이 메모리 위치에서 r3레지스터로 로드 - 중복명령 실행
- 최적화 O1 실행시 컴파일러가 모든 명령 제거

volatile 사용할 경우
- 최적화 O1 실행시 두 변수에 대한 연산 최적화 하지 않음

결론 : volatile = "값이 언제든 바뀔 수 있다" 라고 컴파일러에게 알려주는 키워드

uint8_t volatile my_data; = volatile uint8_t my_data; = 휘발성 변수

uint32_t volatile *const 레지스터_이름 = (uint32_t *)주소;
|키워드|	의미|
|--|--|
|volatile|	값 자주 바뀜|
|const|	포인터 주소는 고정|
|*|	그 주소 안 값 사용|
***

ISR 버튼 전역 플레그 설정

While 무한 루프 안에서 전역플래그가 ISR에 의해 설정된경우 
버튼의 눌림 횟수 프린트 

버튼 플래그 재설정






