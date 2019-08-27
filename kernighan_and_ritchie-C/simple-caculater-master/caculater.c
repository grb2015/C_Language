/*教材4.3节 外部变量 逆波兰实现计算器*/

#include<stdio.h>
#include<stdlib.h>	/*为了使用atof()函数*/
#define MAXOP 100  /*操作数或运算符的最大长度*/
#define NUMBER '0' /*标识找到一个数*/

/*getch()函数的准备工作*/
#define BUFSIZE 100   //用于getch 和ungetch
char buf[BUFSIZE];  /*getch 和ungetch的缓冲区*/
int bufp = 0;  /*buf中下一个空闲位置*/
int getch()  /* 取一个字符(可能是压回的字符)*/
{
	return (bufp > 0)?buf[--bufp]:getchar();
}
void ungetch(int c)
{
	if(bufp >= BUFSIZE)
		printf("ungetch : too many characters \n");
	else
		buf[bufp++] = c;
}

/* getop函数，获取下一个运算符或数值操作数 */
int getop(char *s)
{
	int i,c;
	while((s[0]=c=getch()) == ' ' || c == '\t') ///是空格或制表符则一直输入，直到不是."     1 2 +"
		;
	s[1] = '\0';
	if(!(c>='0' && c<='9') && c !='.') //跳开空格后如果第一个字符不是数字或小数点(即不是数字)。能处理"  .1 2 +"
		return c;	//这里的返回值可能是'+' , '-' , '*' , '\'或者EOF 以及其它非法的字符.有个Bug就是无法处理负数。比如"  -1 2 +"
	i = 0;
	/*收集整数部分*/
	if( c >= '0' && c<= '9')  //能执行到这里，说明s[0]一定是一个数字了，所以要++i.因为c还可能是'.'，所以要if( c >= '0' && c<= '9')
		while((s[++i] = c = getch()) >='0' && c<='9')
			;
	/*收集小数部分*/
	if(c == '.')
		while((s[++i] = c = getch()) >='0' && c<='9')
			;
	s[i] = '\0';
	if(c !=EOF)
		ungetch(c);
	return NUMBER;
}

	
	
				
			
/*栈相关的方法*/	
void push(double);
double pop(void);


/*逆波兰计算器*/
/****************************************
* 注意：该程序并不能处理负数 比如输入:"   -1 2 +" 
* 原因在于getop函数,符号和减号没有分
*
*
*****************************************/
int main()
{
	int type ;
	double op2;
	char s[MAXOP];

	/*如果函数getop(s)的返回值不为EOF，则一直进行循环*/
	while((type = getop(s))!=EOF)  ///getop(s)函数将获取到的操作数或操作符存于s.返回获取到的类型
	{
		switch(type)
		{
			case NUMBER:
				push(atof(s));
				break;
			case '+':
				push(pop()+pop());
				break;
			case '-':
				op2 = pop();
				push(pop()-op2);
				break;
			case '*':
				push(pop()*pop());		
				break;
			case '/':
				op2 = pop();
				if(op2 != 0.0)
					push(pop() / op2);
				else
					printf("error : 除数为0 !");
					break;
			case '\n':
				printf("\t final result =  %f\n",pop());
				break;
			default:
				printf("error : unknown command %s\n",s);
				break;
		}
	}
	return 0;
}


