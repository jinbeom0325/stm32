1.1. 정의 및 약어

◯ 다음의 세 단계로 나누어진다. 

① M(Mandatory): 의무적으로 지켜야 함.

② R(Recommeded): 의무적으로 지켜야 하는 것은 아니지만 지킬 것을 권장함.

③ O(Optional): 지침을 참고하여 지키기로 결정되는 경우 지킴
***

2.2. Source File

◯ 프로그램 코딩 시 다음과 같은 사항을 주의하여 작성한다.

① 한 줄에 하나의 명령문을 사용한다. (if문에서 단일 State 리턴시 예외)
  
② Source Codem이 한 Line은 80글자를 초과하지 않는 것을 원칙으로한다.

③ 가능한 하나의 function을 하나의 source file로 구성한다.(여러 개의 function들이 짧고, 서로 연관성을 가질 경우에는 하나의 source file에 포함한다.)

④ 하나의 function내의 실행의 총 line의 합은 300-500 line을 넘지 않도록 한다.
***

## Naming Convention
① Name은 의미를 쉽게 파악할 수 있도록 한다.

② 각 Name은 식별이 보장되도록 한다.

③ 혼동될 문자는 가급적 사용하지 않도록 한다.

④ 발음상 혼동이 되는 Name의 사용을 피한다.

⑤ Global 변수는 등록한 후 임의 갱신을 피한다.

Variable과 Function Parameter이름은 기본적으로 Hungarian notation을 따른다. 즉, prefix(역할) base type(데이터타입) qualifier(const,static상태) 의 형태를 가진다.


### 용어
컴포넌트는 소프트웨어나 하드웨어 시스템에서 독립적으로 관리되고 재사용 가능한 기능이나 모듈

선언(Declaration)	

정의(Definition)

Abbreviation (약어)

indentation(들여쓰기)

Binary operator(이항연산자)

expression(표현식)

Conditional Compilation (조건부 컴파일) #ifdef #else #endif

FALL THROUGH(break생략)

조건부 컴파일(Conditional Compilation)과 플랫폼 특정 기능(Platform-Specific Features)은 주로 코드의 이식성(Portability)과 특정 플랫폼이나 하드웨어에서의 최적화, 디버깅을 위해 사용
