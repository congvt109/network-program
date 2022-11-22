#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

void getIPByHostname(char string[])
{
    struct hostent *hostName;
    printf("Hostname: %s\n", string);
    hostName = gethostbyname(string);

    if (hostName == NULL)
    {
        printf("Not found information.\n");
        return;
    }
    printf("Offical IP: %s \n", inet_ntoa(*((struct in_addr *)hostName->h_addr)));

    struct in_addr **addr_list = (struct in_addr **)hostName->h_addr_list;
    if (addr_list[1] != NULL)
    {
        printf("Alias IP:\n");
        for (int i = 1; addr_list[i] != NULL; i++)
        {
            printf("%s\n", inet_ntoa(*addr_list[i]));
        }
    }
    else
    {
        printf("(Empty address list)\n");
    }
}

void getHostnameByID(char string[])
{
    struct hostent *hostIP;
    struct in_addr address;

    printf("IP Address: %s\n", string);
    address.s_addr = inet_addr(string);
    if (address.s_addr == INADDR_NONE)
    {
        printf("Not found information.\n");
        return;
    }
    else
    {
        hostIP = gethostbyaddr((char *)&address, 4, AF_INET);
    }

    if (hostIP == NULL)
    {
        printf("Not found information.\n");
        return;
    }

    printf("Offical name: %s\n", hostIP->h_name);
    char **pAlias;

    printf("Alias name: \n");

    for (pAlias = hostIP->h_aliases; *pAlias != NULL; pAlias++)
    {
        printf("%s\n", *pAlias);
    }
}

int main(int argc, char *argv[])
{
    if (argc != 3 || (strcmp(argv[1], "1") == 0 && atoi(argv[2]) == 0) || (strcmp(argv[1], "2") == 0 && atoi(argv[2]) != 0))
    {
        printf("Wrong parameter.\n");
    }

    if (strcmp(argv[1], "1") == 0 && atoi(argv[2]) != 0)
    {
        getHostnameByID(argv[2]);
    }
    else if (strcmp(argv[1], "2") == 0 && atoi(argv[2]) == 0)
    {
        getIPByHostname(argv[2]);
    }
}