#include <stdio.h>

typedef long Align; /*安装long类型边界对齐*/

/* 链表的节点定义 */
/* 注意这里是一个联合体 */
union header        /*块的头部*/
{
    struct
    {
        union header *ptr; /*空闲块链表中的下一块*/
        unsigned size;     /*本块的大小*/
    }s;
    Align x;               /*强制块的对齐*/
}；

typedef union header Header;

/* 定义一个链表节点的对象 */
static Header base;       /*从空链表开始*/

/* 定义一个存放链表节点的指针 */
static Header *freep = NULL; /*空闲链表的初始指针*/

/* 分配指定大小的内存，并返回给char*  */
char *sbrk(int);

#define NALLOC 1024

/*向系统申请更多的存储空间*/
Header *morecore(unsigned nu)
{
    char *cp;
    Header *up;

    /* 每次至少分配NALLOC大小的内存 */
    if (nu < NALLOC)
        nu = NALLOC;

    /* 分配的不是nu字节，而是nu个header对象所占的内存大小 */
    cp = sbrk(nu * sizeof(Header));
    if (cp == (char *)-1) /*没有空间*/
        return NULL;

    /** 将up指向sbrk返回的首地址,并让编译器将该地址解释成Hearder类型 */
    up = (Header *)cp;
    up->s.size = nu;        /** 为第一个地址的nu字段赋值 */

    /*  从系统分配出来的空闲空间要放到空闲队列中去 */
    free((void *)(up+1));   /** 给free函数传入的参数是up+1，即从首地址跳过一个Header类型 */

    /**< 返回的是全局变量freep */
    return freep;
}


/* 从空间队列中取出一块，给用户使用 */
void *malloc(unsigned nbytes)
{
    /** 节点指针 */
    Header *p, *prevp;
    unsigned nunits;

    /** 确保分配的大小至少为nbtytes，且满足对齐(是head大小的整数倍)。并且多分配了一个header大小，用来记录额外信息。指向下一个链表的*next指针，size */
    nunits = (nbytes+sizeof(Header)-1)/sizeof(Header)+1;

    /*没有空闲链表*/
    /** 使用frepp为prevp赋值，初始时freep 为NULL */
    if ((prevp = freep) == NULL)
    {
        /** base是上面分配的一个Head对象，而不是一个指针，它是实际分配了内存了的 */
        /** 填充base的字段 ,注意这里也同时将freep进行了赋值为base */
        base.s.ptr = freep = prevp = &base;         /* 将next指针指向本身 */
        base.s.size = 0;                            /* 填充s.size */
    }

    for (p = prevp->s.ptr;       ; prevp = p, p = p->s.ptr)
    {
       
        /* 第一次为空，显然是不满足的 */
        if (p->s.size >= nunits) /*足够大*/
        {
            if (p->s.size == nunits)/*正好*/
            {
                prevp->s.ptr = p->s.ptr;
            }
            else                    /*分配末尾部分*/
            {
                p->s.size -= nunits;        /* 设置size大小 */
                p += p->s.size;             /* 移动p指针*/
                p->s.size = nunits;         /* 更新指针的大小 */
            }
            freep = prevp;                  /* freep指向的是分配的前面一个块 */
            return (void *)(p+1);           /* 将p指针返回 */
        }

        /**< 显然第一次p是等于freep的 ,需要调用sbrk向系统申请*/
        if (p == freep)        /*闭环的空闲链表*/
            if ((p = morecore(nunits)) == NULL)
                return NULL;   /*没有剩余的存储空间*/
    }
}

/*将块ap放入空闲块链表中,传入的是首地址，但是它会包含size，也就是知道要回收的是多大*/
void free(void *ap)
{
    Header *bp, *p;

    bp = (Header *)ap - 1; /*指向块头*/

    /**< freep之前都还是NULL */

    /* 寻找两个空余块的中间地段 */
    for (p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr)
    {
        /**< 之前在malloc中，已经将freep指向了base,而base是指向自身的，所以满足p = p->s.str */
        /** bp 这里是sbkl分配的内存的起始地址，它与base比较，是什么意义呢?无法比较啊 */
        /* 注意空闲地址是升序的，即最后一块地址最大 */
        /* 所以这里p>p->s.ptr说明到了末尾 */
        if (p >= p->s.ptr && (bp > p || bp < p->s.ptr))
            break;         /*被释放的块在链表的开头或末尾*/
    }

    if (bp + bp->s.size == p->s.ptr)   /*与上一相邻块合并*/
    {
        bp->s.size += p->s.ptr->s.size;
        bp->s.ptr = p->s.ptr->s.ptr;
    }
    else
    {
        bp->s.ptr = p->s.ptr;
    }

    if (p + p->s.size == bp)          /*与下一相邻块合并*/
    {
        p->s.size += bp->s.size;
        p->s.ptr = bp->s.ptr;
    }
    else
    {
        p->s.ptr = bp;
    }

    /* 注意这里,将从for循环中找出的p赋值给了freep */
    freep = p;
}
