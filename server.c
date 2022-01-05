// Server side C/C++ program to demonstrate Socket programming
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#define PORT 8080
#define ADD 1
#define ABS 2
#define MUL 3
#define NOT 4

int get_next_space(char *str, int start)
{
    int i;
    for (i = start; str[i] != ' ' && i < strlen(str); i++)
        ;
    return i == strlen(str) ? -1 : i;
}

int get_int(char *str, int start)
{
    int i, res = 0;
    for (i = start; i < strlen(str) && str[i] >= '0' && str[i] <= '9'; i++)
    {
        res *= 10;
        res += (str[i] - '0');
    }
    return res;
}

int main(int argc, char const *argv[])
{
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    char *hello = "Hello\n";
    char *del;
    char ans[100];
    char str[100];
    char num1[1000];
    char num2[1000];
    int i, overflow = 0;
    long long a, b, x;
    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr *)&address,
             sizeof(address)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
                             (socklen_t *)&addrlen)) < 0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    while (1)
    {
        // write your code!
        //offset the buffer
        memset(buffer, '\0', sizeof(buffer) / sizeof(char));
        memset(ans, '\0', sizeof(ans) / sizeof(char));
        //read the messge from client to buffer
        valread = read(new_socket, buffer, 1024);
        // printf("%s\n", buffer);
        //read the command to str
        //because the command will follow with the space so we read the buffer until read ' '
        for (i = 0; buffer[i] != ' ' && i < 6; ++i)
            str[i] = buffer[i];
        str[i] = '\0';           //terminate str with '\0'
        if (!strcmp(str, "add")) //add function
        {
            sscanf(buffer, "%s%s%s", str, num1, num2); //read the number in string to chack if the input overflow
            sscanf(buffer, "%s%lld%lld", str, &a, &b); //read in the number
            if (strlen(num1) >= 19)                    //check if input overflow
            {                                          // long long range -9,223,372,036,854,775,808 to 9,223,372,036,854,775,807
                if (strlen(num1) >= 21)                //if string len > 21 exceed the max of long long
                    overflow = 1;
                else if (strlen(num1) == 20 && (num1[0] != '-' || a > 0)) //if the strlen == 20 check if the number is negative
                    overflow = 1;
                else if (strlen(num1) == 19 && a < 0) //if the strlen == 19 check if the number overflow if overflow the number will resent negative
                    overflow = 1;
            }
            if (strlen(num2) >= 19)
            {
                if (strlen(num2) >= 21)
                    overflow = 1;
                else if (strlen(num2) == 20 && (num2[0] != '-' || b > 0))
                    overflow = 1;
                else if (strlen(num2) == 19 && b < 0)
                    overflow = 1;
            }
            if (overflow)
                sprintf(ans, "input overflow");
            else
            {
                if (a >= 0 ? b > INT64_MAX - a : b < INT64_MIN - a) //check if a+b overflow
                {
                    if (a >= 0)
                        sprintf(ans, "output overflow"); //determine overflow or underflow
                    else
                        sprintf(ans, "output underflow");
                }
                else
                    sprintf(ans, "%lld", a + b); //if no overflow print the answer to ans
            }
        }
        else if (!strcmp(str, "abs"))
        {
            sscanf(buffer, "%s%s", str, num2);
            if (*num2 == '-')
                for (int i = 0; i < strlen(num2); ++i)
                    num2[i] = num2[i + 1];
            sprintf(ans, "%s", num2);
        }
        else if (!strcmp(str, "mul"))
        {
            sscanf(buffer, "%s%s%s", str, num1, num2); //read the number in string to chack if the input overflow
            sscanf(buffer, "%s%lld%lld", str, &a, &b); //read in the number
            if (strlen(num1) >= 19)                    //check if input overflow
            {                                          // long long range -9,223,372,036,854,775,808 to 9,223,372,036,854,775,807
                if (strlen(num1) >= 21)                //if string len > 21 exceed the max of long long
                    overflow = 1;
                else if (strlen(num1) == 20 && (num1[0] != '-' || a > 0)) //if the strlen == 20 check if the number is negative
                    overflow = 1;
                else if (strlen(num1) == 19 && a < 0) //if the strlen == 19 check if the number overflow if overflow the number will resent negative
                    overflow = 1;
            }
            if (strlen(num2) >= 19)
            {
                if (strlen(num2) >= 21)
                    overflow = 1;
                else if (strlen(num2) == 20 && (num2[0] != '-' || b > 0))
                    overflow = 1;
                else if (strlen(num2) == 19 && b < 0)
                    overflow = 1;
            }
            if (overflow)
                sprintf(ans, "input overflow");
            else
            {
                x = a * b;
                if (a != 0 && x / a != b)
                {
                    if ((a > 0 && b > 0) || (a < 0 && b < 0))
                        sprintf(ans, "output overflow");
                    else
                        sprintf(ans, "output underflow");
                }
                else
                    sprintf(ans, "%lld", a * b);
            }
        }
        else if (!strcmp(buffer, "kill"))
        {
            break;
            return 0;
        }
        else
        {
            sprintf(ans, "Hello");
        }
        send(new_socket, ans, strlen(ans), 0);
        overflow = 0;
    }

    return 0;
}
