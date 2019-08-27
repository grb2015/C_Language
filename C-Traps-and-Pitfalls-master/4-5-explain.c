/*================================================================
*   Copyright (C) 2017 All rights reserved.free for learn
*   
*   filename:     print2.c
*   breif��       ��4-5-confluse-print.c�Ľ��� 
*   histroy��     2017-06-30    renbin.guo craeted
*   note��         
*   usage:         
*               [root@localhost C-Traps-and-Pitfalls]# ./explain 
*
*               p=5ec38210,*p=0
*               p+1=5ec38211,*p=1
*               p+2=5ec38212,*p=2
*               p+3=5ec38213,*p=3
*
*               a=3020100           //���Ƿ��֣�aռ4���ֽڣ�&a�Żص�����Ͱ����ֽڣ�ջ���͵�ַ������
*
*               c=5ec38214          
*               a=5ec38210
*               b=5ec3820f      // b�ĵ�ַ������a,������һ�����еĵ�ַ��û������
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
            scanf("%d\n",&c);           // ����Ĺؼ����������cֻ��һ���ֽڣ������תΪ%d�󣬾�ռ����4���ֽڣ��൱���ڵ�c��ռ��i�ĵ���3���ֽڣ�ÿ������c������9���Ͱ�ԭ����i����
                                        //���µ��ֽڸ���Ϊ0�ˣ�����i�Ͳ��������ˡ������������c����255�������Ż���i����µ��ֽڲ�Ϊ0��i��ֵ�Ż�仯��
            puts("afeter Input c :");
            printf("i= %d\n",i);
        }

    }
    */

    ~          
}


