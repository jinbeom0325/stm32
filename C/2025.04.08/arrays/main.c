#include<stdio.h>
#include<stdint.h>


//int main(void)
//{
//	uint32_t studentsAge[100];
//	printf("Size of an array = %u\n", sizeof(studentsAge));
//	printf("Basea address of the arry = %p\n",studentsAge);
//	return 0;
//}


int main(void)
{
	uint8_t someData[10] = {0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};

	printf("contents of this array\n");

	for(uint32_t i = 0 ; i < 10 ; i++)
	{
		printf("%x\t",someData[i]);
	}



	printf("\n");

	for(uint32_t i = 0 ; i < 10 ; i++)
	{
		someData[i] = 0x33;
		printf("%x\t",someData[i]);
	}

	return 0;
}


