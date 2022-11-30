#include <arpa/inet.h>
#include <netinet/in.h>
#include<netdb.h>
#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <netdb.h>
#include <ctype.h>

void func1(char input[30]){
    struct sockaddr_in sa;   
    socklen_t len;       
    char hbuf[NI_MAXHOST];
    
    memset(&sa, 0, sizeof(struct sockaddr_in));
    
    /* For IPv4*/
    sa.sin_family = AF_INET;
    sa.sin_addr.s_addr = inet_addr(input);
    len = sizeof(struct sockaddr_in);
    
    if (getnameinfo((struct sockaddr *) &sa, len, hbuf, sizeof(hbuf), 
        NULL, 0, NI_NAMEREQD)) {
        printf("Not found information\n");
    }
    else {
        printf("Official name: %s\n", hbuf);
    }
    return;   
}
void func2(char input[30]){
    struct hostent *host_info;
    struct in_addr *address;

    host_info = gethostbyname(input);
    if(host_info){
        address = (struct in_addr *) (host_info->h_addr);
        printf("Official IP: %s\n", inet_ntoa(*address));

    }
    else{
        printf("Not found information\n");
    }
}
int check(int option, char input[30]){
    if (option == 1) return isdigit(input[0]);
    else return isalpha(input[1]);
}
int main(int argc, char *argv[]){
    if (argc != 3){
        printf("Wrong command line!\n");
        exit(1);
    }
    int option = atoi(argv[1]);
    char input[30];
    strcpy(input, strdup(argv[2]));
    switch (option)
    {
    case 1:
        if (check(1, input))
            func1(input);
        else printf("Wrong parameter\n");
        break;
    case 2:
        if (check(2, input))
            func2(input);
        else printf("Wrong parameter\n");
        break;
    default:
        printf("Invalid command line!\n");
        break;
    }
}