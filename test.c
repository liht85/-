#include "stdio.h"
#include <time.h>
#include <stdarg.h>
#include <stdbool.h>

#define LOG_PARAMS           __FILE__,__func__,__LINE__ 
#define DEBUGINFR(A,B,args...)	debugInfo(LOG_PARAMS,A,B,##args)


int debugInfo(char *pFile,const char *pFuncName,int iLineNumb, bool bTAG, char *fmt, ...)
{

   if( NULL == pFile || '\0' == pFile[0] || NULL == pFuncName ||'\0' == pFuncName[0])
        return 1;
    int i = 0;
    time_t timeSecs = time(NULL);
    struct tm *timeInfo = localtime(&timeSecs);
    char szLogHead[100]={0};
    
    if(!bTAG){
	printf("\033[41;36m[ERR] " );
    }else{
	printf("[INF] " );
    }
    snprintf(szLogHead, sizeof(szLogHead), "[%02d:%02d:%02d] [%s] [%s:%d]", \
		timeInfo->tm_hour, timeInfo->tm_min, timeInfo->tm_sec, pFile, pFuncName, iLineNumb);
    printf("%s\t",szLogHead);


    va_list args;
    va_start(args, fmt);
    vprintf(fmt,args);
    va_end(args);
   
    if(!bTAG)
    {
	printf("\033[0m\n");
    }else
    {
	printf("\n");
    }
	
    return 0;
}

int main(int args,char* arg[])
{
	DEBUGINFR(false,"BegIN");
	int n=10;
	int i = 0;
	for(i=0;i<n;i++)
	{
		if(i%2 == 0){
			DEBUGINFR(true, "loop=%d",i);
		}else{
			DEBUGINFR(false,"ddddddddddddddddd");
			DEBUGINFR(false,"loop=%d",i);
		}

	}
	return 0;
}
