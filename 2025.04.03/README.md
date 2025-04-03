# 2025.04.03

### Scanf
* scanf는 주소저장
* scanf에서는 scanf에서는 %f와 %lf를 정확히 구분해야 한다.
* float은 %f, double은 %lf 사용, 지수는 각각 %e , %le 사용 
***
```c
//샘플 예제 코드
int main(void)
{
	float number1 , number2, number3;
	float avg;
	printf("Enter the first number:");
	fflush(stdout);
	scanf("%f",&number1);

	printf("\nEnter the first number:");
	fflush(stdout);
	scanf("%f",&number2);

	printf("\nEnter the first number:");
	fflush(stdout);
	scanf("%f",&number3);

	avg = (number1+number2+number3)/3;
	printf("\nAverage is : %f\n",avg);
	getchar()
	getchar()
}
```
* 첫번째 getchar()는 줄바꿈\n 즉시 반환
* 두번째 getchar()는 입력 대기 
***
### ASCII
문자를 숫자로 변환하여 저장하고 처리할 수 있도록 만든 문자 인코딩 표준
* char를 %d로 변환하여 확인 가능 
* 총128개 7비트 사용
***
### Pointer
메모리 주소를 저장하는 변수
* 주소 연산자 & (변수의 주소 반환)
* 역참조 연산자 * (포인터가 가리키는 값)
```c
int main(void)
{

	char data = 100;
	printf("Value of data is : %d\n",data);
	printf("Address of the variable data is : %p\n", &data);
	
	//Create a pointer variable and store the address of "data" variable
	char* pAddress = &data;
	
	char value = *pAddress;
	printf("read value is : %d\n",value);
	
	*pAddress = 65;
	printf("Value of data is : %d\n",data);
	return 0;
}
```
출력

Value of data is : 100

Address of the variable data is : 0065FECA

read value is : 100

Value of data is : 65

* 포인터는 주변 레지스터에서 SRAM 메모리나 반대로 데이터를 복사하는데 많이 사용

### <stdint.h>
* 고정 크기 정수형을 제공하는 C 표준 라이브러리 헤더 파일
* uintptr_t는 포인터를 저장할 수 있는 부호 없는 정수형
### 

