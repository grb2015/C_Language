/* Note:Your choice is C IDE */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <conio.h>   
#define N 100

struct student
{
	char num[20];
	char name[30];
	char tel[11];
};

/* 以下是函数原型说明，被调函数的定义在主调函数后面时，要加此部分 */ 
extern getch();
void myprint();
void mycreate();
void mydisplay();
void mysearch(); 
/* sch_num与sch_name函数被mysearch调用 */
void sch_num(FILE *fp); 
void sch_name(FILE *fp);    
void mymodify();
void myadd();
void mydelete();  
/* del_num与del_name函数被mydelete调用 */
void del_num(FILE *fp);
void del_name(FILE *fp);  
void mysort();
/* sort_num与sort_name函数被mysort调用 */
void sort_num();
void sort_name();

void main()
{  
	char choose,yes_no;
	
	do
	{
		myprint();    /* 显示主菜单 */
		printf("         ");
		choose=getch(); 
		switch(choose)
		{
			case '1':	mycreate();		break;		/* 创建 */
			case '2':	mydisplay();	break;		/* 显示 */
			case '3':	mysearch();		break;		/* 查询 */
			case '4':	mymodify();		break;		/* 修改 */
			case '5':	myadd();		break;		/* 添加 */
			case '6':	mydelete();		break;		/* 删除 */
			case '7':	mysort();		break;		/* 排序 */
			case '0':	break;		
			default:printf("\n    %c为非法选项！\n",choose);
		}
		if(choose=='0')
			break;
		printf("\n        要继续选择吗(Y/N)?\n");
		do 
		{
			yes_no=getch();
		}while(yes_no!='Y'&&yes_no!='y'&&yes_no!='N'&&yes_no!='n');
	}while(yes_no!='Y'||yes_no!='y');
}

void myprint()         /* 显示菜单界面  */
{
	printf("\n\n\n\n\n\n\n\n");
	printf("			|----------------------------|\n");
	printf("			|		请输入选项编号(0-7): |\n"); 
	printf("			|----------------------------|\n");
	printf("			|	1--创建信息管理系统   	 |\n"); 
	printf("			|	2--显示信息管理系统   	 |\n");
	printf("			|	3--查询信息管理系统   	 |\n");
	printf("			|	4--修改信息管理系统   	 |\n"); 
	printf("			|	5--添加信息管理系统   	 |\n");
	printf("			|	6--删除信息管理系统   	 |\n");
	printf("			|	7--排序信息管理系统   	 |\n");
	printf("			|	0--退出				   	 |\n");  
	printf("			|----------------------------|\n");
}

/* 定义创建信息管理系统的函数 */   
void mycreate()
{
	int i=1;
	struct student temp;
	FILE *fp; 
	
	fp=fopen("./guanli.dat","w");
	if(fp==NULL)
	{
		printf("\n		打开文件失败!\n");
		return;
	}      
	
	printf("\n		请输入第1个记录:\n"); 
	printf("		学号(用#结束输入):");  
	do 
	{
		gets(temp.num);
	}while(strcmp(temp.num,"")==0);
	printf("		姓名(用#结束输入):");
	gets(temp.name);   
	printf("		电话号码(用#结束输入):");
	gets(temp.tel); 
	while(temp.num[0]!='#'&&temp.name[0]!='#'&&temp.tel[0]!='#')
	{
		fprintf(fp,"%23s%15s%15s\n",temp.num,temp.name,temp.tel);
		i++;     
		
		printf("\n		请输入第%d个记录:\n",i);  
		printf("		学号(用#结束输入):");  
		do 
		{
			gets(temp.num);
		}while(strcmp(temp.num,"")==0);
		printf("		姓名(用#结束输入):");
		gets(temp.name);   
		printf("		电话号码(用#结束输入):");
		gets(temp.tel);  
	}
	fclose(fp);
}

/* 定义显示信息管理系统的函数 */
void mydisplay()
{
	int n=0;
	struct student temp;
	FILE *fp;  
	
	fp=fopen("./guanli.dat","r+");
	if(fp==NULL)
	{
		printf("\n		打开文件失败!\n");
		return;
	}   
	
//	clrscr();
	printf("		学号		姓名		电话号码\n"); 
	while(feof(fp)==0)
	{
		fscanf(fp,"%23s%15s%15s\n",&temp.num,&temp.name,&temp.tel);
		printf("%23s%15s%15s\n",temp.num,temp.name,temp.tel);
		n++; 
	}
	if(n==0)
		printf("\n		文件中无记录!\n"); 
	else 
		printf("\n		文件中共有%d个记录!\n",n);  
	fclose(fp);
}	

/* 定义查询信息管理系统的函数 */  
void mysearch()
{
	char c;
	FILE *fp;
	
	fp=fopen("./guanli.dat","r+");
	if(fp==NULL)
	{
		printf("\n		打开文件失败!\n");
		return;
	}             
	
	printf("\n		按学号查询(h),还是按姓名查询(m)?");
	c=getch();
	printf("c=%c",c);
	if(c=='h'||c=='H')
		sch_num(fp);		/* 按学号查询 */
	else if(c=='m'||c=='M')
		sch_name(fp);		/* 按姓名查询 */
	else
		printf("\n		mysearch---非法字符! c=%c\n",c);	 
	fclose(fp);
}

/* 定义按学号查询信息管理系统的函数 */
void sch_num(FILE *fp)
{
	int flag=0,n=0;
	char tempnum[10];
	struct student temp; 
	
	printf("\n		请输入要查询记录的学号:");
	gets(tempnum);  
	while(feof(fp)==0)
	{
		fscanf(fp,"%23s%15s%15s\n",&temp.num,&temp.name,&temp.tel); 
		if(strcmp(tempnum,temp.num)==0)
		{
			if(flag==0)  
				printf("		学号		姓名		电话号码\n"); 
			printf("%23s%15s%15s\n",temp.num,temp.name,temp.tel);
			flag=1;
		} 
		n++;
	}
	if(n==0)
		printf("\n		文件中无记录!\n"); 
	else 
		if(flag==0)
			printf("\n		文件中无此人!\n");  
}	  

/* 定义按姓名查询信息管理系统的函数 */
void sch_name(FILE *fp)
{
	int flag=0,n=0;
	char tempname[10];
	struct student temp; 
	
	printf("\n		请输入要查询记录的姓名:");
	gets(tempname);  
	while(feof(fp)==0)
	{
		fscanf(fp,"%23s%15s%15s\n",&temp.num,&temp.name,&temp.tel); 
		if(strcmp(tempname,temp.name)==0)
		{
			if(flag==0)  
				printf("		学号		姓名		电话号码\n"); 
			printf("%23s%15s%15s\n",temp.num,temp.name,temp.tel);
			flag=1;
		} 
		n++;
	}
	if(n==0)
		printf("\n		文件中无记录!\n"); 
	else 
		if(flag==0)
			printf("\n		文件中无此人!\n");  
}	 

/* 定义修改信息管理系统的函数 */  
void mymodify()
{
	char c; 
	int n=0;
	struct student *find,temp,record[100],*p; /* 最多100个记录 */
	FILE *fp;
	
	fp=fopen("./guanli.dat","r+");
	if(fp==NULL)
	{
		printf("\n		打开文件失败!\n");
		return;
	}             
	
	p=record; 
	while(feof(fp)==0)
	{
		fscanf(fp,"%23s%15s%15s\n",p->num,p->name,p->tel);
		p++;
		n++; 
	} 
	fclose(fp);
	
	if(n==0) 
	{
		printf("\n		文件中无记录!\n");   
		return;
	}
	printf("\n		请输入要修改记录的学号:");
	gets(temp.num);   
	for(p=record;p<record+n;p++)
		if(strcmp(temp.num,p->num)==0)
		{
			find=p;     /* find记住修改记录的位置 */
			break;
		}  
	if(p==record+n)
	{
		printf("\n		无此人!\n");
		return;
	}
	do
	{ 
		printf("\n		请输入正确的学号:");
		do
		{ 
			gets(temp.num);
		}while(strcmp(temp.num,"")==0);
		printf("		请输入正确的姓名:");
		gets(temp.name);   
		printf("		请输入正确的电话号码:");
		gets(temp.tel);  
		for(p=record;p<record+n;p++)
			if((strcmp(temp.num,p->num)==0)&&(p!=find))
			{
				printf("\n		学号重复，要重新输入吗(Y/N)?"); 
				do 
				{
					c=getch();
				}while(c!='Y'&&c!='y'&&c!='N'&&c!='n');
				putchar('\n');
				break;			
			}      
		if(p==record+n)
		{
			*find=temp;  		/* find指向需要修改记录的位置 */
			break;
		} 
	}while(c=='Y'||c=='y'); 
	
	fp=fopen("./guanli.dat","r+");
	if(fp==NULL)
	{
		printf("\n		打开文件失败!\n");
		return;
	} 
	for(p=record;p<record+n;p++)
		fprintf(fp,"%23s%15s%15s\n",p->num,p->name,p->tel);	
	fclose(fp);		
}           

/* 定义添加信息管理系统的函数 */  
void myadd()
{
	char c; 
	int n=0;
	struct student temp,record[N],*p; 
	FILE *fp;
	
	fp=fopen("./guanli.dat","r+");
	if(fp==NULL)
	{
		printf("\n		打开文件失败!\n");
		return;
	}             
	
	p=record; 
	while(feof(fp)==0)
	{
		fscanf(fp,"%23s%15s%15s\n",p->num,p->name,p->tel);
		p++;
		n++; 
	} 
	fclose(fp);
	
	do
	{ 
		printf("\n		请输入新记录的学号:");
		do
		{ 
			gets(temp.num);
		}while(strcmp(temp.num,"")==0);
		printf("		请输入新记录的姓名:");
		gets(temp.name);   
		printf("		请输入新记录的电话号码:");
		gets(temp.tel);  
		for(p=record;p<record+n;p++)
			if(strcmp(temp.num,p->num)==0)
			{
				printf("\n		学号重复，要重新输入吗(Y/N)?"); 
				do 
				{
					c=getch();
				}while(c!='Y'&&c!='y'&&c!='N'&&c!='n');
				putchar('\n');
				break;			
			}      
		if(p==record+n)
		{
			*p=temp;  		
			break;
		} 
	}while(c=='Y'||c=='y'); 
	
	fp=fopen("./guanli.dat","r+");
	if(fp==NULL)
	{
		printf("\n		打开文件失败!\n");
		return;
	} 
	for(p=record;p<record+n+1;p++)
		fprintf(fp,"%23s%15s%15s\n",p->num,p->name,p->tel);	
	fclose(fp);		
}           

/* 定义删除信息管理系统的函数 */  
void mydelete()
{
	char c;
	FILE *fp;
	
	fp=fopen("./guanli.dat","r+");
	if(fp==NULL)
	{
		printf("\n		打开文件失败!\n");
		return;
	}   
	
	printf("\n		按学号删除(h),还是按姓名删除(m)?");
	c=getch();
	if(c=='h'||c=='H')
		del_num(fp);		/* 按学号删除 */
	if(c=='m'||c=='M')
		del_name(fp);		/* 按姓名删 */
	else
		printf("\n		mydelete---非法字符!\n");	 
	fclose(fp);
}	
	
/* 定义按学号删除信息管理系统的函数 */
void del_num(FILE *fp)
{
	int n=0;
	char tempnum[10];
	struct student record[N],*p,*k; 
	
	p=record;
	while(feof(fp)==0)
	{
		fscanf(fp,"%23s%15s%15s\n",p->num,p->name,p->tel);
		p++;
		n++; 
	} 
	fclose(fp);  
	
	printf("\n		请输入要删除记录的学号:");
	gets(tempnum);    
	
	for(k=record;k<record+n;k++)
		if(strcmp(tempnum,k->num)==0)
			break;			/* 找到要删记录结束循环 */
	if(k<record+n)          /* 提前结束循环，说明找到人 */
		for(p=k;p<k+n-1;p++)   /* 向左移一位，相当于删除记录 */
			*p=*(p+1);  
	else
		printf("\n		无此人!\n");
	
	fp=fopen("./guanli.dat","w");
	if(fp==NULL)
	{
		printf("\n		打开文件失败!\n");
		return;
	}  
	
	for(p=record;p<record+n-1;p++) 
		fprintf(fp,"%23s%15s%15s\n",p->num,p->name,p->tel);
}	

/* 定义按姓名删除信息管理系统的函数 */
void del_name(FILE *fp)
{
	int n=0;
	char tempname[10];
	struct student record[N],*p,*k;
	 
	
	p=record;
	while(feof(fp)==0)
	{
		fscanf(fp,"%23s%15s%15s\n",p->num,p->name,p->tel);
		p++;
		n++; 
	} 
	fclose(fp);  
	
	printf("\n		请输入要删除记录的姓名:");
	gets(tempname);    
	
	for(k=record;k<record+n;k++)
		if(strcmp(tempname,k->name)==0)
			break;			/* 找到要删记录结束循环 */
	if(k<record+n)          /* 提前结束循环，说明找到人 */
		for(p=k;p<k+n-1;p++)   /* 向左移一位，相当于删除记录 */
			*p=*(p+1);  
	else
		printf("\n		无此人!\n");
	
	fp=fopen("./guanli.dat","w");
	if(fp==NULL)
	{
		printf("\n		打开文件失败!\n");
		return;
	}  
	
	for(p=record;p<record+n-1;p++) 
		fprintf(fp,"%23s%15s%15s\n",p->num,p->name,p->tel);
}	

/* 定义排序信息管理系统的函数 */  
void mysort()
{
	char c;
	FILE *fp;
	
	fp=fopen("./guanli.dat","r+");
	if(fp==NULL)
	{
		printf("\n		打开文件失败!\n");
		return;
	}   
	fclose(fp);

	printf("\n		按学号排序(h),还是按姓名排序(m)?");
	c=getch();
	if(c=='h'||c=='H')
		sort_num();		/* 按学号排序 */
	//if(c=='m'||c=='M')		
	else if(c=='m'||c=='M')  /// renbin.guo modify 2017-08-04
		sort_name();		/* 按姓名排序 */
	else
		printf("\n		mysort---非法字符!\n");	 	
}	 

/* 定义按学号排序信息管理系统的函数 */
void sort_num()
{
	int i,j,k,n=0;
	char c;
	struct student record[N],*p,temp; 
	FILE *fp;
		
	fp=fopen("./guanli.dat","r");
	if(fp==NULL)
	{
		printf("\n		打开文件失败!\n");
		return;
	} 
	
	p=record;
	while(feof(fp)==0)
	{
		fscanf(fp,"%23s%15s%15s\n",p->num,p->name,p->tel);
		p++;
		n++; 
	} 
	fclose(fp);  
	
	printf("\n		按升序(s)，还是按降序(j)?");
	c=getch();    
	if(c=='s'||c=='S')    /* 按学号的升序排列 */
		for(i=0;i<n-1;i++)              /* 选择法排序 */
		{
			k=i;
			for(j=i+1;j<n;j++)
				if(strcmp((p+k)->num,(p+j)->num)>0) 
					k=j;
			temp=*(p+k);
			*(p+k)=*(p+i);
			*(p+i)=temp;
		}
	else
		if(c=='j'||c=='J')    /* 按学号的降序排列 */
		for(i=0;i<n-1;i++)              /* 选择法排序 */
		{
			k=i;
			for(j=i+1;j<n;j++)
				if(strcmp((p+k)->num,(p+j)->num)<0) 
					k=j;
			temp=*(p+k);
			*(p+k)=*(p+i);
			*(p+i)=temp;
		} 
		else
		{
			printf("\n 		sortnum---非法字符!\n");
			return;
		}		
	
	fp=fopen("./guanli.dat","w");
	if(fp==NULL)
	{
		printf("\n		打开文件失败!\n");
		return;
	}  
	
	for(p=record;p<record+n;p++)
	{ 
		fprintf(fp,"%23s%15s%15s\n",p->num,p->name,p->tel); 
		printf("%23s%15s%15s\n",p->num,p->name,p->tel);
	}
	fclose(fp);
}	

/* 定义按姓名排序信息管理系统的函数 */
void sort_name()
{
	int i,j,k,n=0;
	char c;
	struct student record[N],*p,temp; 
	FILE *fp;
	
	fp=fopen("./guanli.dat","r+");
	if(fp==NULL)
	{
		printf("\n		打开文件失败!\n");
		return;
	}
	
	p=record;
	while(feof(fp)==0)
	{
		fscanf(fp,"%23s%15s%15s\n",p->num,p->name,p->tel);
		p++;
		n++; 
	} 
	fclose(fp);  
	
	printf("\n		按升序(s)，还是按降序(j)?");
	c=getch();    
	if(c=='s'||c=='S')        /* 按姓名的升序排列 */
		for(i=0;i<n-1;i++)  /* 选择法排序 */
		{
			k=i;
			for(j=i+1;j<n;j++)
				if(strcmp((p+k)->name,(p+j)->name)>0) 
					k=j;
			temp=*(p+k);
			*(p+k)=*(p+i);
			*(p+i)=temp;
		}
	else
		if(c=='j'||c=='J')    /* 按姓名的降序排列 */
		for(i=0;i<n-1;i++)  /* 选择法排序 */
		{
			k=i;
			for(j=i+1;j<n;j++)
				if(strcmp((p+k)->name,(p+j)->name)<0) 
					k=j;
			temp=*(p+k);
			*(p+k)=*(p+i);
			*(p+i)=temp;
		} 
		else
		{
			printf("\n 		sortname---非法字符!\n");
			return;
		}		
	
	fp=fopen("./guanli.dat","w");
	if(fp==NULL)
	{
		printf("\n		打开文件失败!\n");
		return;
	}  
	
	for(p=record;p<record+n;p++) 
		fprintf(fp,"%23s%15s%15s\n",p->num,p->name,p->tel); 
	fclose(fp);
}	
