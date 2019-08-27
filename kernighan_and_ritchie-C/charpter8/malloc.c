#include <stdio.h>

typedef long Align; /*��װlong���ͱ߽����*/

/* ����Ľڵ㶨�� */
/* ע��������һ�������� */
union header        /*���ͷ��*/
{
    struct
    {
        union header *ptr; /*���п������е���һ��*/
        unsigned size;     /*����Ĵ�С*/
    }s;
    Align x;               /*ǿ�ƿ�Ķ���*/
}��

typedef union header Header;

/* ����һ������ڵ�Ķ��� */
static Header base;       /*�ӿ�����ʼ*/

/* ����һ���������ڵ��ָ�� */
static Header *freep = NULL; /*��������ĳ�ʼָ��*/

/* ����ָ����С���ڴ棬�����ظ�char*  */
char *sbrk(int);

#define NALLOC 1024

/*��ϵͳ�������Ĵ洢�ռ�*/
Header *morecore(unsigned nu)
{
    char *cp;
    Header *up;

    /* ÿ�����ٷ���NALLOC��С���ڴ� */
    if (nu < NALLOC)
        nu = NALLOC;

    /* ����Ĳ���nu�ֽڣ�����nu��header������ռ���ڴ��С */
    cp = sbrk(nu * sizeof(Header));
    if (cp == (char *)-1) /*û�пռ�*/
        return NULL;

    /** ��upָ��sbrk���ص��׵�ַ,���ñ��������õ�ַ���ͳ�Hearder���� */
    up = (Header *)cp;
    up->s.size = nu;        /** Ϊ��һ����ַ��nu�ֶθ�ֵ */

    /*  ��ϵͳ��������Ŀ��пռ�Ҫ�ŵ����ж�����ȥ */
    free((void *)(up+1));   /** ��free��������Ĳ�����up+1�������׵�ַ����һ��Header���� */

    /**< ���ص���ȫ�ֱ���freep */
    return freep;
}


/* �ӿռ������ȡ��һ�飬���û�ʹ�� */
void *malloc(unsigned nbytes)
{
    /** �ڵ�ָ�� */
    Header *p, *prevp;
    unsigned nunits;

    /** ȷ������Ĵ�С����Ϊnbtytes�����������(��head��С��������)�����Ҷ������һ��header��С��������¼������Ϣ��ָ����һ�������*nextָ�룬size */
    nunits = (nbytes+sizeof(Header)-1)/sizeof(Header)+1;

    /*û�п�������*/
    /** ʹ��freppΪprevp��ֵ����ʼʱfreep ΪNULL */
    if ((prevp = freep) == NULL)
    {
        /** base����������һ��Head���󣬶�����һ��ָ�룬����ʵ�ʷ������ڴ��˵� */
        /** ���base���ֶ� ,ע������Ҳͬʱ��freep�����˸�ֵΪbase */
        base.s.ptr = freep = prevp = &base;         /* ��nextָ��ָ���� */
        base.s.size = 0;                            /* ���s.size */
    }

    for (p = prevp->s.ptr;       ; prevp = p, p = p->s.ptr)
    {
       
        /* ��һ��Ϊ�գ���Ȼ�ǲ������ */
        if (p->s.size >= nunits) /*�㹻��*/
        {
            if (p->s.size == nunits)/*����*/
            {
                prevp->s.ptr = p->s.ptr;
            }
            else                    /*����ĩβ����*/
            {
                p->s.size -= nunits;        /* ����size��С */
                p += p->s.size;             /* �ƶ�pָ��*/
                p->s.size = nunits;         /* ����ָ��Ĵ�С */
            }
            freep = prevp;                  /* freepָ����Ƿ����ǰ��һ���� */
            return (void *)(p+1);           /* ��pָ�뷵�� */
        }

        /**< ��Ȼ��һ��p�ǵ���freep�� ,��Ҫ����sbrk��ϵͳ����*/
        if (p == freep)        /*�ջ��Ŀ�������*/
            if ((p = morecore(nunits)) == NULL)
                return NULL;   /*û��ʣ��Ĵ洢�ռ�*/
    }
}

/*����ap������п�������,��������׵�ַ�������������size��Ҳ����֪��Ҫ���յ��Ƕ��*/
void free(void *ap)
{
    Header *bp, *p;

    bp = (Header *)ap - 1; /*ָ���ͷ*/

    /**< freep֮ǰ������NULL */

    /* Ѱ�������������м�ض� */
    for (p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr)
    {
        /**< ֮ǰ��malloc�У��Ѿ���freepָ����base,��base��ָ������ģ���������p = p->s.str */
        /** bp ������sbkl������ڴ����ʼ��ַ������base�Ƚϣ���ʲô������?�޷��Ƚϰ� */
        /* ע����е�ַ������ģ������һ���ַ��� */
        /* ��������p>p->s.ptr˵������ĩβ */
        if (p >= p->s.ptr && (bp > p || bp < p->s.ptr))
            break;         /*���ͷŵĿ�������Ŀ�ͷ��ĩβ*/
    }

    if (bp + bp->s.size == p->s.ptr)   /*����һ���ڿ�ϲ�*/
    {
        bp->s.size += p->s.ptr->s.size;
        bp->s.ptr = p->s.ptr->s.ptr;
    }
    else
    {
        bp->s.ptr = p->s.ptr;
    }

    if (p + p->s.size == bp)          /*����һ���ڿ�ϲ�*/
    {
        p->s.size += bp->s.size;
        p->s.ptr = bp->s.ptr;
    }
    else
    {
        p->s.ptr = bp;
    }

    /* ע������,����forѭ�����ҳ���p��ֵ����freep */
    freep = p;
}
