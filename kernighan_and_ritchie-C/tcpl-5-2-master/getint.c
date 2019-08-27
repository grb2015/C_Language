/********************************************************************
*	file	   :	K&R 5-2  
*	discription：	从输入中为一个整型数组赋值，只能使用getchar()函数，不能使用scanf  %d等格式化输入
*			重点是实现int getline(int *p) 函数，它从输入中提取一个数字赋值给p 
*	history	   ：	renbin.guo	2016-11-23  ceated
*
*
********************************************************************/
#include <stdio.h>
#include <ctype.h>

#define BUFSIZE 100
#define ARRAY_SIZE  20

char buf[BUFSIZE];  /*用于ungetch函数的缓冲区*/
int bufp = 0;       /*buf中下一个空闲位置*/

/*取一个字符*/
int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

/*把字符压回到输入中*/
void ungetch(int c)
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

/***********************************
*	功能：将输入中的下一个整型数赋值给*pn
*	参数： [out] *pn: 保存提取的整数
*	返回值：
*			0	:	输入的不是一个整数
			EOF :	输入了文件终止符EOF
			正数：	正确获取了一个整数
************************************/
int getint(int *pn)
{
    int c, sign;

    /*跳过空白符*/
    while (isspace(c = getch()))
        ;

    /*输入不是一个数字*/
    if (!isdigit(c) && c != EOF && c != '+' && c != '-')
    {
        ungetch(c);
        return 0;
    }

    sign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-')
        c = getch();

    for (*pn = 0; isdigit(c); c = getch())
        *pn = 10 * *pn + (c - '0');

    *pn *= sign;

    if (c != EOF)
        ungetch(c);

    return c;
}
int main()
{
	int i;
	int array[ARRAY_SIZE];
	for(i=0;i<ARRAY_SIZE && getint(&array[i])!=EOF;i++)
	{
	//	getint(&array[i]);
	}
	/* test */
	for(i = 0;i< ARRAY_SIZE;i++)
		printf("array[%d] = %d\n",i,array[i]);
}


