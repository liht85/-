

#ifndef _LOGGER_H_
#define _LOGGER_H_

#include <Windows.h>
#include <string>
using namespace std;

#define OUTLOGERR(fm, ...)	gLogger.traceEX(FALSE, __FILE__, __LINE__,fm,__VA_ARGS__)
#define OUTLOGINF(fm, ...)	gLogger.traceEX(TRUE, __FILE__, __LINE__,fm,__VA_ARGS__)



class CLogger
{
public:
	CLogger();
	~CLogger();
	void traceEX(BOOL bTAG, char *pFile, int iLineNumb, char *fmt, ...);
	void SetLogSwitch(bool bswitch);
private:
	bool m_Switch;
	char szFilePath[MAX_PATH] = { 0 };
	char szFileName[_MAX_PATH] = { 0 };
	FILE *pLogHandle = nullptr;
	tm timeInfo;
	time_t curTime;
	string m_strFolderName;
	CRITICAL_SECTION m_cs;
	HANDLE m_hMutex = NULL;
	string strMutexName;// = "Mutex_Name";
	void StartMutex(HANDLE hMutex);
	void StopMutex(HANDLE hMutex);

};


#endif
