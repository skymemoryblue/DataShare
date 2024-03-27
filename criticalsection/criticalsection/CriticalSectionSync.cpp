/*
	CriticalSectionSync.cpp
	프로그램 설명: 생성 가능한 쓰레드의 개수 측정.
*/

#include <stdio.h>
#include <windows.h>
#include <process.h>
#include <tchar.h>

#define NUM_OF_GATE		5

LONG gTotal = 0;
int data[12];

CRITICAL_SECTION   hCriticalSection;
CRITICAL_SECTION   hInput;
CRITICAL_SECTION   hOutput;

unsigned int WINAPI ThreadProc_scanf( LPVOID lpParam ) 
{ 
	printf("입력 부분 실행\n");
	EnterCriticalSection(&hInput);
	for(DWORD i=0; i < 11; i++)
	{
		scanf_s("%d ", &data[i]);
	}
	scanf_s("%d", &data[11]);
	LeaveCriticalSection(&hInput);

	return 0;
} 


unsigned int WINAPI ThreadProc_add(LPVOID lpParam)
{
	printf("추가 부분 실행\n");
	EnterCriticalSection(&hCriticalSection);
	DWORD* nPtr = (DWORD*)lpParam;
	DWORD numOne = *nPtr;

	for (DWORD i = numOne; i <= numOne + 3; i++)
	{
		gTotal += data[i];
	}
	LeaveCriticalSection(&hCriticalSection);

	return 0; // 정상적 종료.
}

unsigned int WINAPI ThreadProc_printf(LPVOID lpParam)
{
	printf("출력 부분 실행\n");
	EnterCriticalSection(&hOutput);
	_tprintf(_T("total count: %d \n"), gTotal);
	LeaveCriticalSection(&hOutput);

	return 0;
}


int _tmain(int argc, TCHAR* argv[])
{
    DWORD dwThreadId[NUM_OF_GATE];
    HANDLE hThread[NUM_OF_GATE];

	hThread[0] = (HANDLE)
		_beginthreadex(
			NULL,
			0,
			ThreadProc_scanf,
			NULL,
			CREATE_SUSPENDED,
			(unsigned*)&dwThreadId[0]
		);

	if (hThread[0] == NULL)
	{
		_tprintf(_T("Thread creation fault! \n"));
		return -1;
	}

	for(DWORD i=0; i < 3; i++)
	{
        hThread[i + 1] = (HANDLE)
		    _beginthreadex ( 
			    NULL,
			    0,				        
			    ThreadProc_add,				  
				(LPVOID)(&data[i * 4]),
			    CREATE_SUSPENDED,		   
			    (unsigned *)&dwThreadId[i + 1]   
	        );

	    if(hThread[i] == NULL)
	    {
	        _tprintf(_T("Thread creation fault! \n"));
	        return -1;
	    }
	}

	hThread[4] = (HANDLE)
		_beginthreadex(
			NULL,
			0,
			ThreadProc_printf,
			NULL,
			CREATE_SUSPENDED,
			(unsigned*)&dwThreadId[4]
		);

	if (hThread[4] == NULL)
	{
		_tprintf(_T("Thread creation fault! \n"));
		return -1;
	}

	InitializeCriticalSection(&hInput);
	InitializeCriticalSection(&hCriticalSection);
	InitializeCriticalSection(&hOutput);

	for(DWORD i=0; i<NUM_OF_GATE; i++)
	{
		ResumeThread(hThread[i]);
	}
	WaitForMultipleObjects(NUM_OF_GATE, hThread, TRUE, INFINITE);

	for(DWORD i=0; i<NUM_OF_GATE; i++)
	{
		CloseHandle(hThread[i]);
	}
  
	DeleteCriticalSection(&hCriticalSection);

	return 0;
}
