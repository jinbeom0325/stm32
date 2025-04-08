## Arrays

```c
#include<stdio.h>
#include<stdint.h>

int main<void>
{
  int len = 10;
uint8_t someData[len];  //가능한 선언 가변길이 배열, c99도입
return 0;
}
```
***
### swap주요 정리 
|함수|	하는일|
|--|--|
|display_array|	배열 출력|
|swap_arrays|	같은 인덱스끼리 값 스왑|
|wait_for_user_input|	엔터 대기|
***
## String
RAM은 주소 0x2000~으로 시작 
***
|이름|	특징|	수정 여부|
|--|--|--|
|문자열 리터럴|	메모리 데이터 영역 저장|	수정 불가|
|문자 배열|	스택에 복사됨|	수정 가능|

char const *pmsg = "fastbitlab.com"; 처럼 문자열 리터럴(상수)일때는 **const**를 붙이기 
```c
#include <stdio.h>

int main()
{
    char name[30];
   printf("Enter your name :");
   fflush(stdout); //강제 출력 버퍼에 남아있지 않음 (Eclipse콘솔 출력)
   scanf("%s",name);

   printf("Hi,%s\n",name);
   fflush(stdout);

   return 0;
}
```
***
### scanf 다루기 
```c
scanf("%d,%d,%d",&a,&b,&c); //입력할때 공백 무시 숫자만 가져옴

char str[100];
scanf("%s", str);  //입력할때 띄워쓰기전까지 입력받음 

scanf("%[^s]s",str); //이렇게 하면 s나오기 전까지 입력 받음, [s^] -> s또는 ^ 만 입력 받음  
```
***
 





