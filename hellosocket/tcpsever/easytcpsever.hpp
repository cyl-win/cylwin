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
#include <vector>
#include "mess.hpp"
class clientsocket
{
public:
	clientsocket(SOCKET csock) {
		csockfd = csock;
	}
	~clientsocket() {}
	SOCKET getsock() {
		return csockfd;
	}
	char* getmsgr() {
		return msgrecv;
	}
	int getlast() {
		return lastpos;
	}
	void setlast(int pos) {
		lastpos = pos;
	}
private:
	SOCKET csockfd;
	char szrecv[10240] = {};
	char msgrecv[102400] = {};
	int lastpos = 0;
};


class easytcpclient
{
public:
	SOCKET _sock;
	std::vector <clientsocket*> g_client;
	easytcpclient() {
		_sock = INVALID_SOCKET;
	}
	~easytcpclient() {
		Close();
	}
	SOCKET initsocket() {
#ifdef _WIN32
		WORD ver = MAKEWORD(2, 2);
		WSADATA dat;
		WSAStartup(ver, &dat);
#endif
		if (INVALID_SOCKET != _sock) {
			printf("<_sock>=%d�رվ�����\n", _sock);
			Close();
		}
		_sock = socket(AF_INET, SOCK_STREAM, 0);
		if (INVALID_SOCKET == _sock) {
			printf("��������ʧ�ܡ�\n");
		}
		else {
			printf("�������ӳɹ���\n");
		}
		return _sock;
	}
	int Bind(const char* ip, unsigned short port) {
		//2.ʹ��bind������˿�
		sockaddr_in _sin = {};
		_sin.sin_family = AF_INET;
		_sin.sin_port = htons(port);
		if (ip) {
			_sin.sin_addr.S_un.S_addr = inet_addr(ip);
		}
		else {
			_sin.sin_addr.S_un.S_addr = INADDR_ANY;
		}
		int ret = bind(_sock, (sockaddr*)&_sin, sizeof(_sin));
		if (SOCKET_ERROR == ret) {
			printf("error , ��ʧ��\n");
		}
		else {
			printf("�󶨳ɹ��˿�<%d>\n", port);
		}
		return ret;
	}
	int Listen(int n) {
		//3.ʹ��listen��������˿�
		int ret = listen(_sock, n);
		if (SOCKET_ERROR == listen(_sock, n)) {
			printf("error , ����ʧ��\n");
		}
		else {
			printf("�����ɹ�\n");
		}
		return ret;
	}
		SOCKET Accept() {
		sockaddr_in clients = { };
		int clilength = sizeof(sockaddr_in);
		SOCKET csock = INVALID_SOCKET;

		csock = accept(_sock, (sockaddr*)&clients, &clilength);
		if (INVALID_SOCKET == csock) {
			printf("error\n");
		}
		
			newuserjoin newsu;
			senddatatoall(&newsu);
		
		g_client.push_back(new clientsocket(csock));
		printf("�¿ͻ��˼���:socket=%d, IP= %s \n", (int)csock, inet_ntoa(clients.sin_addr));
		return csock;
	}
		bool onrun() {
			if (isrun()) {
				//������ �׽���
				fd_set fdread;
				fd_set fdwrite;
				fd_set fdecp;
				FD_ZERO(&fdread);//��غ�������fd_set.count����Ϊ0
				FD_ZERO(&fdwrite);
				FD_ZERO(&fdecp);
				FD_SET(_sock, &fdread);//���׽���_sock����fd_set
				FD_SET(_sock, &fdwrite);
				FD_SET(_sock, &fdecp);
				for (int i = (int)g_client.size() - 1; i >= 0; i--) {
					FD_SET(g_client[i]->getsock(), &fdread);//���ͻ����������η���ɶ��¼�����
				}
				//nfdsָ����fd_set������������������SOCKET���ķ�Χ
				timeval t = { 1,0 };
				//��������� ������ ΪNULL��Ϊ����
				int ret = select(_sock + 1, &fdread, &fdwrite, &fdecp, &t);
				if (ret < 0) {
					printf("���ִ���û�н����κβ���\n");
					return false;
				}
				if (FD_ISSET(_sock, &fdread)) {
					FD_CLR(_sock, &fdread);
					Accept();
					//sockaddr_in clients = { };
					//int clilength = sizeof(sockaddr_in);
					//SOCKET csock = INVALID_SOCKET;

					//csock = accept(_sock, (sockaddr*)&clients, (int*)&clilength);
					//if (INVALID_SOCKET == csock) {
					//	printf("error\n");
					//}
					//for (int i = (int)g_client.size() - 1; i >= 0; i--) {
					//	newuserjoin newsu;
					//	send(g_client[i]->getsock(), (const char*)&newsu, sizeof(newuserjoin), 0);
					//}
					//g_client.push_back(new clientsocket(csock));
					//printf("�¿ͻ��˼���:socket=%d, IP= %s \n", (int)csock, inet_ntoa(clients.sin_addr));
				}
				for (int i = (int)g_client.size() - 1; i >= 0; i--) {
					if (FD_ISSET(g_client[i]->getsock(), &fdread)) {
						if (-1 == proc(g_client[i])) {
							auto iter = g_client.begin();
							if (iter != g_client.end()) {
								g_client.erase(iter);
								delete g_client[i];
							}
						}
					}
				}
				//printf("����ʱ�䴦������ҵ��\n");
				return true;
			}
			return false;
		}
		bool isrun() {
			return _sock != INVALID_SOCKET;
		}
		char szrecv[10240] = {};
		int proc(clientsocket * pclient) {
			
			int nlen = recv(pclient->getsock(), szrecv, 10240, 0);
			if (nlen <= 0) {
				printf("client exit");
				return -1;
			}
			memcpy(pclient->getmsgr() + pclient->getlast(), szrecv, nlen);
			pclient->setlast(pclient->getlast() + nlen);
			//�ж���Ϣ�����������ݳ����Ƿ������Ϣͷ����
			while (pclient->getlast() >= sizeof(dataheader)) {
				//��ʱ֪����Ϣ����
				dataheader* header = (dataheader*)pclient->getmsgr();
				//�����Ϣ���������ȴ�����Ϣ����
				if (pclient->getlast() >= header->datalength) {
					//ʣ��δ������Ϣ���������ݳ���
					int nsize = pclient->getlast() - header->datalength;
					//����������Ϣ
					doit(pclient->getsock(),header);
					//��δ�������ݵ�λ�ô���������ͷ��
					memcpy(pclient->getmsgr(), pclient->getmsgr() + header->datalength, nlen);
					//����β����
					pclient->setlast(nsize);
				}
				else { break; }
			}//ʣ����Ϣ��������Ϣ������
			return 0;
		}
		void doit(SOCKET csock,dataheader* header) {
			switch (header->cmd)
			{
			case CMD_LOGININ: {
				login* log = (login*)header;
				//printf("�յ�����  CMD_LOGIN ���� :%d username: %s password :%s\n", log->datalength, log->username, log->password);
				loginresult logret;
				//send(csock, (char*)&header, sizeof(dataheader), 0);
				//send(csock, (char*)&logret, sizeof(logret), 0);
				senddata(csock, &logret); }
			break;
			case CMD_LOGINOUT: {


				loginout* log2 = (loginout*)header;
				loginoutresult log2ret;
				//printf("�յ�����  CMD_LOGINOUT ���� :%d username: %s\n ", log2->datalength, log2->username);
				senddata(csock, &log2ret); }
							 break;
			default: {
				dataheader header;
				senddata(csock, &header);
			}
				   break;
			}
		}
		int senddata(SOCKET csock,dataheader* header) {
			if (isrun() && header) {
				return send(csock, (const char*)header, header->datalength, 0);
			}
			return SOCKET_ERROR;
		}
		void senddatatoall(dataheader *header) {
			for (int n = (int)g_client.size() - 1; n >= 0; n--) {
				senddata(g_client[n]->getsock(), header);
			}
		}
		void Close() {
			if (_sock != INVALID_SOCKET) {
#ifdef _WIN32
				for (int i = (int)g_client.size() - 1; i >= 0; i--) {

					closesocket(g_client[i]->getsock());
					delete g_client[i];
				}
				//6.�ر��׽���sock
				closesocket(_sock);
				WSACleanup();
#else
				for (size_t i = g_client.size() - 1; i >= 0; i--) {

					close(g_client[i]->getsock());
				}
				close(_sock);
#endif
			}
			g_client.clear();
		}
			  
private:

};


#endif