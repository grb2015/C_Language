/*================================================================
*   Copyright (C) 2017 All rights reserved.free for learn
*   
*   filename:     print.c
*   breif��       "printf��scanf�ڲ�ͬ�����¿��Խ��ܲ�ͬ���͵Ĳ��������������ر����׳���"       
*                 ���������,i�����������0,1,2,3,4 !
*   histroy��     2017-06-30    renbin.guo craeted
*   note��         
*   usage:         
*                   [root@localhost C-Traps-and-Pitfalls]# ./4-5 
*                   i=8ad89a2c
*                   c=8ad89a2b
*                   before Input c :
*                   1
*                   2
*                   afeter Input c :
*                   i= 0
*                   before Input c :
*                   4
*                   afeter Input c :
*                   i= 0
*                   before Input c :
*                   9
*                   afeter Input c :
*                   i= 0
*                   before Input c :
*
*                   ���󣺺�����������ʲô��i��ӡ�Ķ���0��i��û�е���������ѭ��һֱִ�У�������ִֻ��5��
*                   �����������Ľ��ͣ���ֲο���4-5-explain.c
*
*
================================================================*/

int main(int argc, char *argv[])
{
    int i;
    char  c;

    printf("i=%x\n",&i);
    printf("c=%x\n",&c);

    for (i=0; i<5; i++)
    {
        puts("before Input c :");
        scanf("%d\n",&c);
        puts("afeter Input c :");
        printf("i= %d\n",i);
    }
    
}

