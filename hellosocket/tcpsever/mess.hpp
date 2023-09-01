enum CMD
{
    CMD_LOGININ,
    CMD_LOGIN_RESULT,
    CMD_LOGINOUT,
    CMD_LOGINOUT_RESULT,
    CMD_NEW_USER_JOIN,
    CMD_ERROR

};
struct dataheader
{
    dataheader() {
        datalength = sizeof(dataheader);
        cmd = CMD_ERROR;
}
    int datalength;
    int cmd;
};
struct login :public dataheader
{
    login() {
        datalength = sizeof(login);
        cmd = CMD_LOGININ;
    }
    char username[32] ;
    char password[32] ;
    char dat[956];
};
struct loginresult :public dataheader
{
    loginresult() {
        datalength = sizeof(loginresult);
        cmd = CMD_LOGIN_RESULT;
        result = 0;
    }
    int result;
    char da[992];
};
struct loginout :public dataheader
{
    loginout() {
        datalength = sizeof(loginout);
        cmd = CMD_LOGINOUT;
    }
    char username[32];
};
struct loginoutresult :public dataheader
{
    loginoutresult() {
        datalength = sizeof(loginoutresult);
        cmd = CMD_LOGINOUT_RESULT;
        result = 0;
    }
    int result;
};
struct newuserjoin :public dataheader
{
    newuserjoin() {
        datalength = sizeof(newuserjoin);
        cmd = CMD_NEW_USER_JOIN;
        sockn = 0;
    }
    int sockn;
};