```c
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
void ChangeNumbers(int* p1, int* p2) /*포인터 2개 인자로 받음*/ {
	int temp = *p1;  //swap
	*p1 = *p2;
	*p2 = temp;
}
int main(void) {
	int num1;
	int num2;
	printf("숫자1 : ");
	scanf("%d", &num1);
	printf("숫자2 : ");
	scanf("%d", &num2);
	printf("바꾸기 전\n 숫자1 : %d, 숫자2 : %d\n", num1, num2);
	ChangeNumbers(&num1, &num2);
	printf("바꾼 후\n 숫자1 : %d, 숫자2 : %d\n", num1, num2);
	return 0;
}
```
