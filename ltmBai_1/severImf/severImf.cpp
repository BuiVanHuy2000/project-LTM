#include <stdio.h>
#include <string>
#include <WinSock2.h>

#pragma comment(lib, "ws2_32")
#pragma warning(disable:4996)

using namespace std;

int main(int arg, char* argv[])
{
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);

    SOCKET server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    SOCKADDR_IN addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    int portNumber = stoi(argv[1]);
    addr.sin_port = htons(portNumber);

    bind(server, (SOCKADDR*)&addr, sizeof(addr));

    listen(server, 5);

    printf("Bat dau nhan tin nhan!!\n");

    SOCKET client = accept(server, NULL, NULL);

    char buffer[256];
    int ret = recv(client, buffer, sizeof(buffer), 0);

    printf("Du lieu tu client:\n%s\n", buffer);

    while (1)
    {
        printf("Nhap thong tin muon gui: ");

        fgets(buffer, sizeof(buffer), stdin);

        if (strncmp(buffer, "exit", 4) == 0) break;

        send(client, buffer, sizeof(buffer), 0);
    }

    closesocket(client);
    closesocket(server);
    WSACleanup();

}