#include <iostream>
#include <winsock2.h>

using namespace std;

#pragma comment(lib,"WS2_32.LIB")

int main ()
{
	WSADATA wsaData;
	BYTE	nMajor = 2, nMinor = 2;
	WORD	wVersionRequested = MAKEWORD (nMinor, nMajor);
	int		nRet = WSAStartup (wVersionRequested, &wsaData);
	if (nRet == SOCKET_ERROR)
	{
		cout << "윈도우 소켓을 초기화 할 수 없습니다." << endl;
		return -1;
	}

	if (LOBYTE (wsaData.wVersion) != nMajor || 
		HIBYTE (wsaData.wVersion) != nMinor) 
	{ 
		cout << "윈도우 소켓 " << nMajor << "." << nMinor << " 을 사용할 수 없습니다." << endl;
		WSACleanup (); 
		return -1; 
	}

	cout << "윈도우 소켓을 초기화 하였습니다." << endl;

	WSACleanup ();

	return 0;
}