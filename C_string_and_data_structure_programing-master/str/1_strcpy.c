

/**
 * @Author   renbin.guo
 * @DateTime 2017-10-21
 * @note:
 *      需要注意的点：
 *      1. 要检查参数是否为NULL
 *      2. 要把最后一个'\0'也复制到。
 *
 * 
 * @param    dest       [description]
 * @param    src        [description]
 * @return              [description]
 */
char *strcpy(char *dest, const char *src)
{
	char *temp =  dest;
	if(dest == NULL || src == NULL)
		return NULL;
	while( (*temp++ = *src++)!='\0' );
	return dest;
}

