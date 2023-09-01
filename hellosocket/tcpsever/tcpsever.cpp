
#define WIN32_LEAN_AND_MEAN
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "easytcpsever.hpp"
using namespace std;
//struct datab
//{
 //   int yearin;
   // char a[32];
//};
int main()
{

    easytcpclient sever;
    sever.initsocket();
    sever.Bind(nullptr, 4567);
    sever.Listen(5);
    

    char _recon[128] = {};

    while (sever.isrun())
    {
        sever.onrun();
    }

    //6.关闭套接字sock
    
    sever.Close();
    getchar();
    printf("已退出");
    return 0;
}


//printf("收到命令 : %d  长度 :%d", header.cmd, header.datalength);

       //printf("收到命令 : %s \n", _recon);
       //2-----------------------------------------
       //if (0 == strcmp(_recon, "getinfo")) {
          // datab dp = {10000000,"cylwin"};
         //  send(csock, (const char *) & dp, sizeof(dp), 0);
      // }
      // ---------------------------------------------
       //-------------------------------------------------
       //the first version
      // else if (0 == strcmp(_recon, "getname")) {
         //  char msg[] = "my name is cylwin";
        //   send(csock, msg, strlen(msg) + 1, 0);
      // }
      // else if (0== strcmp(_recon, "get")) {
        //   char msg[] = "hello i am sever ";
        //   send(csock, msg, strlen(msg) + 1, 0);
      // }
      // else {
       //    char msg[] = "??";
         //  send(csock, msg, strlen(msg) + 1, 0);
      // }
       //----------------------------------------------------



