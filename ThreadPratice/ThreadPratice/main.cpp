/*
	ThreadAdderOne.cpp
	프로그램 설명: 프로세스 유사형태 쓰레드 생성.
*/

#include <stdio.h>
#include <windows.h>
#include <tchar.h>

DWORD last_thread_first;

DWORD WINAPI ThreadProc( LPVOID lpParam ) 
{ 
	DWORD * nPtr = (DWORD *) lpParam;
	DWORD scale;

	if (* nPtr == last_thread_first) {
		scale = 4;
	}
	else {
		scale = 3;
	}

	DWORD total = 0;

	for(DWORD i = 0; i< scale; i++)
	{
		total += * (nPtr + i);
	}

    return total; 
}


int _tmain(int argc, TCHAR* argv[])
{
    DWORD dwThreadID[3];
    HANDLE hThread[3];

	DWORD paramThread[10];
	DWORD total = 0;
	DWORD result = 0;

	for (int i = 0; i < 10; i++) {
		scanf_s("%d ", &paramThread[i]);
	}
	
	last_thread_first = paramThread[6];

    hThread[0] = 
		CreateThread ( 
				NULL, 0,
				ThreadProc,
				(LPVOID)(&paramThread[0]),
				0, &dwThreadID[0]
		    );			                
 
    hThread[1] = 
		CreateThread ( 
				NULL, 0,
				ThreadProc,
				(LPVOID)(&paramThread[3]),
				0, &dwThreadID[1]
		    );			                
 
    hThread[2] = 
		CreateThread ( 
				NULL, 0,
				ThreadProc,
				(LPVOID)(&paramThread[6]),
				0, &dwThreadID[2]
		    );

	if(hThread[0] == NULL || hThread[1] == NULL || hThread[2] == NULL)
	{
		_tprintf(_T("Thread creation fault! \n"));
		return -1;
	}

	WaitForMultipleObjects(3, hThread, TRUE, INFINITE);

	GetExitCodeThread(hThread[0] , &result);
	printf("result = %d\n", result);
	total += result;

	GetExitCodeThread(hThread[1] , &result);
	printf("result = %d\n", result);
	total += result;

	GetExitCodeThread(hThread[2] , &result);
	printf("result = %d\n", result);
	total += result;

	_tprintf(_T("total: %d \n"), total);

    CloseHandle(hThread[0]);//Thread 종료
    CloseHandle(hThread[1]);
    CloseHandle(hThread[2]);

	return 0;
}

