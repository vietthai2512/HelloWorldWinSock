#include <stdio.h>
#include <Winsock2.h>
#include <WS2tcpip.h>

int main()
{
	WSADATA wsaData;
	int error = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (error == SOCKET_ERROR)
	{
		printf("Khong the khoi tao\n");
	}
	else
	{
		printf("Khoi tao thanh cong\n");
		SOCKET s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (s == INVALID_SOCKET)
		{
			printf("Khong the khoi tao socket\n");
		}
		else
		{
			printf("Gia tri socket vua tao: %d\n", s);
			SOCKADDR_IN saddr;
			saddr.sin_family = AF_INET;
			saddr.sin_port = htons(80);
			saddr.sin_addr.S_un.S_addr = inet_pton(AF_INET, "127.0.0.1", NULL);
			PADDRINFOA result = NULL;
			getaddrinfo("vnexpress.net", "http", NULL, &result);
			while (result != NULL)
			{
				printf("Dia chi tim duoc: \n");
				SOCKADDR_IN addr;
				if (result->ai_family == AF_INET)
				{
					memcpy_s(&addr, sizeof(addr), result->ai_addr, result->ai_addrlen);
					char buffer[17];
					buffer[16] = 0;
					inet_ntop(AF_INET, &addr.sin_addr, buffer, sizeof(buffer));
					printf_s("%s", buffer);
				}
				result = result->ai_next;
			}
		}
		WSACleanup();
	}
}