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
	//���ջ�����
	char szrecv[10240] = {};
	//�ڶ������� ��Ϣ������
	char msgrecv[102400] = {};
	//��Ϣβ��λ��
	int lastpos = 0;
	int proc(SOCKET csock) {
		
		int nlen = recv(csock, szrecv, 10240, 0);
		//printf("nlen=%d\n", nlen);
		//�����ݴӽ��ջ�����������Ϣ������
		memcpy(msgrecv+ lastpos, szrecv, nlen);
		lastpos = lastpos + nlen;
		//�ж���Ϣ�����������ݳ����Ƿ������Ϣͷ����
		while(lastpos>=sizeof(dataheader)){
			//��ʱ֪����Ϣ����
			dataheader* header = (dataheader*)msgrecv;
			//�����Ϣ���������ȴ�����Ϣ����
			if (lastpos >= header->datalength) {
				//ʣ��δ������Ϣ���������ݳ���
				int nsize = lastpos - header->datalength;
				//����������Ϣ
				doit(header);
				//��δ�������ݵ�λ�ô���������ͷ��
				memcpy(msgrecv, msgrecv + header->datalength, nlen);
				//����β����
				lastpos = nsize;
			}
		else { break; }//ʣ����Ϣ��������Ϣ������

		}
		/*
		dataheader* header = (dataheader*)szrecv;
		if (nlen <= 0) {
			printf("��������Ͽ�����\n");
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
			//printf("�յ�����˷�������  CMD_LOGIN_RESULT ���� :%d \n", header->datalength);
		}
		break;
		case CMD_LOGINOUT_RESULT: {
			
			loginoutresult* log2 = (loginoutresult*)header;
			//printf("�յ�����˷�������  CMD_LOGINOUT_RESULT ���� :%d \n", header->datalength);
		}
		break;
		case CMD_NEW_USER_JOIN: {
			
			newuserjoin* newuser = (newuserjoin*)header;
			//printf("�յ�����˷�������  CMD_NEW_USER_JOIN ���� :%d \n", header->datalength);
		}
		break;
		case CMD_ERROR: {

			
			printf("�յ�����˷�������  CMD_ERROR ���� :%d \n", header->datalength);
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
			printf("<_sock>=%d�ر�����\n", _sock);
			Close();
		}
		_sock = socket(AF_INET, SOCK_STREAM, 0);
		if (INVALID_SOCKET == _sock) {
			printf("��������ʧ�ܡ�\n");
		}
		else {
			printf("�������ӳɹ���\n");
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
			printf("���ӳɹ�\n");
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
				printf("�Ͽ�����\n");
				return false;
			}
			if (FD_ISSET(_sock, &fdread)) {
				FD_CLR(_sock, &fdread);
				if (-1 == proc(_sock)) {
					printf("�Ͽ�����\n");
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
