/*exampl of K&R 5-4*/
#define ALLOCSIZE 10000 /*可用空间大小*/
static char allocbuf[ALLOCSIZE]; /*alloc使用的存储区*/
static char *allocp = allocbuf;  /*下一个空闲位置*/

/*返回指向n个字符的指针*/
char *alloc(int n)
{
    /*有足够的空闲空间*/
    if (allocbuf + ALLOCSIZE - allocp >= n)
    {
        allocp += n;
        return allocp - n;/*返回分配前的指针p*/
    }
    else /*空闲空间不够*/
    {
        return 0;
    }
}

/*释放p指向的存储区*/
void afree(char *p)
{
    if (p >= allocbuf && p < allocbuf + ALLOCSIZE)
        allocp = p;
}

