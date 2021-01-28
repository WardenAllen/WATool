
/*
 * @author WardenAllen
 * @date   2020/10/22 20:36:49
 * @brief  
 */

#pragma once

#include "Header.h"
#include "Buffer.h"
#include "MsgHead.h"

#include "Protobuf/CSBase.pb.h"
#include "Protobuf/CSMsg.pb.h"

#define MAX_BUFFER_SIZE		60 * 1024

class WATcp : public QObject
{
	Q_OBJECT

public:
	explicit WATcp(QObject* parent_ = nullptr);
	~WATcp();

public:
	bool Connect(const QString& ip_, const quint16 port_,
		bool debug_ = true);
	bool Close();

public:
	int SendProto(uint16_t msgid, google::protobuf::Message& proto);
	int SendMsg(const char* data_, int len_);

signals:
	void TcpConnected();
	void TcpClosed();
	void TcpRead(const char*, int);
	void TcpWrite(const char*, int);

public slots:
	void OnConnected();
	void OnClosed();
	void OnReadyRead();

private:
	int Decode(const char* data, int size, WAMsgHead& head);

private:
	QTcpSocket _socket;
	QString _ip;
	quint16 _port;
	bool _is_debug;
	bool _is_connect;
	WABuffer _readbuf;
};
