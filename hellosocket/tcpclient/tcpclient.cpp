#define WIN32_LEAN_AND_MEAN
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include"easytcpclient.hpp"
#include <thread>
using namespace std;

//struct datab
//{
   // int yearin;
  //  char a[32];
//};


void threadCMD(easytcpclient *client) {
    while(true){
        char bufcmd[1024];
        scanf("%s", bufcmd);
        if (0 == strcmp(bufcmd, "exit")) {
            printf("进程结束");
            client->Close();
            return;
        }
        else if (0 == strcmp(bufcmd, "login")) {
            login lo;
            strcpy(lo.username, "cylwin");
            strcpy(lo.password, "cylwin");
            client->senddata(&lo);
            
        }
        else if (0 == strcmp(bufcmd, "loginout")) {
            loginout lo2;
            strcpy(lo2.username, "cylwin");
            client->senddata(&lo2);
        }
        else {
            printf("不支持该命令");
        }
    }
   
  
}
int main()
{

   
    easytcpclient client;
    thread t1(threadCMD,&client);
    t1.detach();
    client.initsocket();
    client.Connect("127.0.0.1", 4567);
    login lo;
    strcmp(lo.password, "cyl");
    strcmp(lo.username, "cyl");
    while (client.isrun())
    {
        client.onrun();
        client.senddata(&lo);
     
    }
    
    client.Close();
   
    getchar();
    return 0;
}

