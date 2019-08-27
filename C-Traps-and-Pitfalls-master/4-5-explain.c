/*================================================================
*   Copyright (C) 2017 All rights reserved.free for learn
*   
*   filename:     print2.c
*   breif：       对4-5-confluse-print.c的解释 
*   histroy：     2017-06-30    renbin.guo craeted
*   note：         
*   usage:         
*               [root@localhost C-Traps-and-Pitfalls]# ./explain 
*
*               p=5ec38210,*p=0
*               p+1=5ec38211,*p=1
*               p+2=5ec38212,*p=2
*               p+3=5ec38213,*p=3
*
*               a=3020100           //我们发现，a占4个字节，&a放回的是最低按个字节，栈往低地址增长嘛
*
*               c=5ec38214          
*               a=5ec38210
*               b=5ec3820f      // b的地址紧挨着a,它是下一个空闲的地址，没有问题
*
*               [root@localhost C-Traps-and-Pitfalls]# 
*
================================================================*/
int main(int argc, char *argv[])
{
    int c;
    int a;
    char b;
    char *p = &a;

    *p = 0x00;
    *(p+1) = 0x01;
    *(p+2) = 0x02;
    *(p+3) = 0x03;
    printf("p=%x,*p=%x\n",p,*p);
    printf("p+1=%x,*p=%x\n",p+1,*(p+1));
    printf("p+2=%x,*p=%x\n",p+2,*(p+2));
    printf("p+3=%x,*p=%x\n",p+3,*(p+3));

    printf("a=%x\n",a);

    printf("c=%x\n",&c);
    printf("a=%x\n",&a);
    printf("b=%x\n",&b); 
    /* ---------------------------------------------------------- */
    /*
    int main(int argc, char *argv[])
    {
        int i;
        char  c;  

        printf("i=%x\n",&i);
        printf("c=%x\n",&c);

        for (i=0; i<5; i++)
        {   
            puts("before Input c :");
            scanf("%d\n",&c);           // 问题的关键在这里，本来c只有一个字节，你把它转为%d后，就占用了4个字节，相当现在的c还占用i的底下3个字节，每次输入c，比如9，就把原来的i的最
                                        //低下的字节覆盖为0了，所以i就不会增长了。除非你输入的c大于255，这样才会是i最底下的字节不为0，i的值才会变化。
            puts("afeter Input c :");
            printf("i= %d\n",i);
        }

    }
    */

    ~          
}


