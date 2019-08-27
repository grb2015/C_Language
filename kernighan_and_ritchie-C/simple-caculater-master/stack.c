 #include<stdio.h>
#define MAXVAL 100

int sp = 0;
double val[MAXVAL];

void push(double f)
{
	if(sp < MAXVAL)
	{
		//printf("sp in push=%d\n",sp);     
		val[sp++] = f;
	}
	else
		printf("stack full ,can't push!\n");
}

/*pop 函数：弹出并返回栈顶的值*/
double pop()
{
	if(sp >0)
	{

		//printf("sp in pop = %d\n",sp);
		return val[--sp];
	}
	else
	{
		//printf("sp in pop = %d\n",sp);
		printf("stack empty ,can't pop!\n");
		return 0.0 ;  ///这里使用0表示栈为空，其实是不太严谨
	}
}
		
