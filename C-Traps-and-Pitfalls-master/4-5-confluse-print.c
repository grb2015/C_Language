/*================================================================
*   Copyright (C) 2017 All rights reserved.free for learn
*   
*   filename:     print.c
*   breif：       "printf和scanf在不同情形下可以接受不同类型的参数，所以他们特别容易出错"       
*                 这个例子中,i的输出并不是0,1,2,3,4 !
*   histroy：     2017-06-30    renbin.guo craeted
*   note：         
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
*                   现象：好像无论输入什么，i打印的都是0，i并没有递增，所以循环一直执行，而不是只执行5次
*                   关于这个问题的解释，奇怪参考，4-5-explain.c
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

