#include <stdio.h>
#include <unistd.h>

#define my_stack_push 335
#define my_stack_pop 336
#define loop 3

int main(void)
{
	int r;
	int n;
	int j;
	int reduce = 0;//reduce의 설명은 보고서에 있다.

	for (j = 0; j < loop; j++)//push 함수
	{
		printf("Push: ");
		scanf("%d", &n);
		r = syscall(my_stack_push, n);
		if (r == 0)//r==0则有重复的 pop次数减一
			reduce++;
	}

	j = 0;//j 초기화
	j = j + reduce;

	for (; j < loop; j++)//pop 함수
	{
		printf("Pop: ");
		r = syscall(my_stack_pop);//r = pop된 데이터
		printf("%d\n", r);
	}
	return 0;
}