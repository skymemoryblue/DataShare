/*
	ThreadAdderTwo.cpp
	프로그램 설명: 전역변수를 이용한 쓰레드 기반 Adder.
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <tchar.h>

static int total = 0;

DWORD WINAPI ThreadProc( LPVOID lpParam ) 
{ 
	DWORD * nPtr = (DWORD *) lpParam;

	DWORD numOne = *nPtr;

	for(DWORD i=numOne; i<= numOne + 3; i++)
	{
		total += i;
	}

    return 0; // 정상적 종료.
}


int _tmain(int argc, TCHAR* argv[])
{
    DWORD dwThreadID[3];
    HANDLE hThread[3];
	DWORD paramThread[12];

	for (int i = 0; i < 11; i++) {
		scanf("%d ", &paramThread[i]);
	}
	scanf("%d", &paramThread[11]);

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
				(LPVOID)(&paramThread[4]),
				0, &dwThreadID[1]
		    );			                
 
    hThread[2] = 
		CreateThread ( 
				NULL, 0,
				ThreadProc,
				(LPVOID)(&paramThread[8]),
				0, &dwThreadID[2]
		    );
 

	if(hThread[0] == NULL || hThread[1] == NULL || hThread[2] == NULL)
	{
		_tprintf(_T("Thread creation fault! \n"));
		return -1;
	}

	WaitForMultipleObjects(3, hThread, TRUE, INFINITE);

	_tprintf(_T("total (1 ~ 12): %d \n"), total);

    CloseHandle(hThread[0]);
    CloseHandle(hThread[1]);
    CloseHandle(hThread[2]);

	return 0;
}

