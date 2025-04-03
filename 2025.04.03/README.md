# 2025.04.03

### scanf
scanf는 주소저장

scanf에서는 scanf에서는 %f와 %lf를 정확히 구분

float은 %f, double은 %lf 사용, 지수는 각각 %e , %le 사용 
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
}
```

