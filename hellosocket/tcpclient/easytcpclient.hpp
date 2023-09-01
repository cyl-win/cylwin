#ifndef _easytcpclient_hpp_
#define _easytcpclient_hpp_
#ifdef _WIN32
#include <windows.h>
#include <WinSock2.h>
#else
#include <unistd.h> //unix std
#include <arpa/inet.h>
#include <string.h>
#define SOCKET int
#define INVALID_SOCKET  (SOCKET)(~0)
#define SOCKET_ERROR            (-1)
#endif
#include<stdio.h>
#include<iostream>
#include <thread>
#include "message.hpp"
class easytcpclient
{
public:
	
	SOCKET _sock;
	//接收缓冲区
	char szrecv[10240] = {};
	//第二缓冲区 消息缓冲区
	char msgrecv[102400] = {};
	//消息尾部位置
	int lastpos = 0;
	int proc(SOCKET csock) {
		
		int nlen = recv(csock, szrecv, 10240, 0);
		//printf("nlen=%d\n", nlen);
		//将数据从接收缓冲区拷贝消息缓冲区
		memcpy(msgrecv+ lastpos, szrecv, nlen);
		lastpos = lastpos + nlen;
		//判断消息缓冲区的数据长度是否大于消息头长度
		while(lastpos>=sizeof(dataheader)){
			//这时知道消息长度
			dataheader* header = (dataheader*)msgrecv;
			//如果消息缓冲区长度大于消息长度
			if (lastpos >= header->datalength) {
				//剩余未处理消息缓冲区数据长度
				int nsize = lastpos - header->datalength;
				//处理网络消息
				doit(header);
				//将未处理数据的位置传到缓冲区头部
				memcpy(msgrecv, msgrecv + header->datalength, nlen);
				//更新尾坐标
				lastpos = nsize;
			}
		else { break; }//剩余消息不属于消息缓冲区

		}
		/*
		dataheader* header = (dataheader*)szrecv;
		if (nlen <= 0) {
			printf("与服务器断开连接\n");
			return -1;
		}
		recv(csock, szrecv + sizeof(header), header->datalength - sizeof(header), 0);
		doit( header);*/
		return 0;
	}
	void doit(dataheader* header) {
		
		switch (header->cmd)
		{
		case CMD_LOGIN_RESULT: {
			
			loginresult* log = (loginresult*)header;
			//printf("收到服务端返回数据  CMD_LOGIN_RESULT 长度 :%d \n", header->datalength);
		}
		break;
		case CMD_LOGINOUT_RESULT: {
			
			loginoutresult* log2 = (loginoutresult*)header;
			//printf("收到服务端返回数据  CMD_LOGINOUT_RESULT 长度 :%d \n", header->datalength);
		}
		break;
		case CMD_NEW_USER_JOIN: {
			
			newuserjoin* newuser = (newuserjoin*)header;
			//printf("收到服务端返回数据  CMD_NEW_USER_JOIN 长度 :%d \n", header->datalength);
		}
		break;
		case CMD_ERROR: {

			
			printf("收到服务端返回数据  CMD_ERROR 长度 :%d \n", header->datalength);
		}
		break;
		
		}
	}
	int senddata(dataheader* header) {
		if (isrun() && header) {
			return send(_sock, (const char*)header, header->datalength, 0);
		}
		return SOCKET_ERROR;
	}
	easytcpclient() {
		_sock = INVALID_SOCKET;
	}
	virtual ~easytcpclient() {
		Close();
	}
	void initsocket() {
#ifdef _WIN32
		WORD ver = MAKEWORD(2, 2);
		WSADATA dat;
		WSAStartup(ver, &dat);
#endif
		if (INVALID_SOCKET != _sock) {
			printf("<_sock>=%d关闭连接\n", _sock);
			Close();
		}
		_sock = socket(AF_INET, SOCK_STREAM, 0);
		if (INVALID_SOCKET == _sock) {
			printf("建立连接失败。\n");
		}
		else {
			printf("建立连接成功。\n");
		}
		
	}
	int Connect(const char* ip, unsigned short port) {
		if (INVALID_SOCKET != _sock) {
			initsocket();
		}
		sockaddr_in _sin = {};
		_sin.sin_family = AF_INET;
		_sin.sin_port = htons(4567);
#ifdef _WIN32
		_sin.sin_addr.S_un.S_addr =inet_addr(ip) ;
#else
		_sin.sin_addr.s_addr = inet_addr(ip);
#endif
		int ret = connect(_sock, (sockaddr*)&_sin, sizeof(sockaddr_in));
		if (SOCKET_ERROR == ret) {
			printf("error\n");
		}
		else {
			printf("连接成功\n");
		}
		return ret;
	}
	void Close() {
		if (_sock != INVALID_SOCKET) {
	#ifdef _WIN32
			closesocket(_sock);
			WSACleanup(); 
	#else
			close(_sock);
	#endif
		}
		_sock = INVALID_SOCKET;
	}
	bool onrun() {
		if (isrun()) {
			fd_set fdread;
			FD_ZERO(&fdread);
			FD_SET(_sock, &fdread);
			timeval t = { 1,0 };
			int ret = select(_sock, &fdread, 0, 0, &t);
			if (ret < 0) {
				printf("断开连接\n");
				return false;
			}
			if (FD_ISSET(_sock, &fdread)) {
				FD_CLR(_sock, &fdread);
				if (-1 == proc(_sock)) {
					printf("断开连接\n");
					return false;
				}
				return true;
			}
		}
		
		
	}
	bool isrun() {
		return _sock != INVALID_SOCKET;
	}
private:

};


#endif 
