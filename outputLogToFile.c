#include "stdio.h"
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <time.h>
#include <stdarg.h>
#include <stdbool.h>
#define STR_LEN_2048		2048
#define LOG_FILE_PATH          "./mylog.txt"        
#define LOG_PARAMS             LOG_FILE_PATH,__FILE__,__func__,__LINE__ 

#define DEBUGINFR(A,B,args...)	debugInfo(LOG_PARAMS,A,B,##args)
int giInfoNumb = 1;
int debugInfo(char *pLogPath, char *pFile, const char *pFuncName, int iLineNumb, bool bTAG,char *fmt, ...)
{
/*    if(0 == (giInfoNumb % 1000))
    {
        struct stat fileStat;
        if(0 == stat(pLogPath, &fileStat) && fileStat.st_size > SIZE_16M)	////#define SIZE_16M               16777216             //1024*1024*16
            remove(pLogPath);
    }
  */

  FILE *pLogHandle = fopen(pLogPath, "a+");
    if(NULL == pLogHandle)
        return 1;
    time_t timeSecs = time(NULL);
    struct tm *timeInfo = localtime(&timeSecs);
  
    char szHead[100]={0};
    if(bTAG)
    snprintf(szHead, sizeof(szHead), "[INF] [%04d] [%d%02d%02d/%02d:%02d:%02d] [%s] [%s:%d]", giInfoNumb++,
             timeInfo->tm_year + 1900, timeInfo->tm_mon + 1, timeInfo->tm_mday, 
             timeInfo->tm_hour, timeInfo->tm_min, timeInfo->tm_sec, pFile, pFuncName, iLineNumb);
    else
    snprintf(szHead, sizeof(szHead), "[ERR] [%04d] [%d%02d%02d/%02d:%02d:%02d] [%s] [%s:%d]", giInfoNumb++,
             timeInfo->tm_year + 1900, timeInfo->tm_mon + 1, timeInfo->tm_mday, 
             timeInfo->tm_hour, timeInfo->tm_min, timeInfo->tm_sec, pFile, pFuncName, iLineNumb);
    int iLen = strlen(szHead);
    fwrite(szHead, iLen, 1, pLogHandle);

    fwrite("\t", 1, 1, pLogHandle);
    char acTitle[STR_LEN_2048] = { 0 };
    va_list args;
    va_start(args, fmt);
    vsnprintf(acTitle, sizeof(acTitle), fmt, args);
    va_end(args);
    iLen = strlen(acTitle);
    fwrite(acTitle, iLen, 1, pLogHandle);
    fwrite("\n", 1, 1, pLogHandle);
    fclose(pLogHandle);
    return 0;
}

int main()
{

int i = 0;
	DEBUGINFR(false," char *fmt, ...%d",i++);

	DEBUGINFR(true," char *fmt, ...%d",i++);
	return 0;
}
