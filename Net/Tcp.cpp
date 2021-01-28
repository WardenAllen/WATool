
/*
 * @author WardenAllen
 * @date   2020/10/22 20:36:58
 * @brief  
 */

#include <windows.h>

#include "Tcp.h"

WATcp::WATcp(QObject* parent_) : QObject(parent_),
	_socket(this), _ip(), _port(0), _is_debug(false),
	_is_connect(false), _readbuf()
{
	connect(&_socket, &QTcpSocket::connected, this, &WATcp::OnConnected);
	connect(&_socket, &QTcpSocket::disconnected, this, &WATcp::OnClosed);
	connect(&_socket, &QTcpSocket::readyRead, this, &WATcp::OnReadyRead);
}

WATcp::~WATcp()
{
}

bool WATcp::Connect(const QString& ip_, const quint16 port_, bool debug_)
{
	_ip = ip_;
	_port = port_;
	_is_debug = debug_;

	//取消已有的连接
	_socket.abort();

	//连接服务器
	_socket.connectToHost(_ip, _port);

	//等待连接成功
	if (!_socket.waitForConnected(30000))
	{
		if (_is_debug) qDebug() << "Connection failed!";
		return false;
	}

	return true;
}

bool WATcp::Close()
{
	_socket.disconnectFromHost();
	return true;
}

int WATcp::SendProto(uint16_t msgid, google::protobuf::Message& proto)
{
	std::string data = proto.SerializeAsString();
	int len = (int)data.size();

	WAMsgHead head(len, (uint16_t)msgid);
	WABuffer buf((size_t)(WAMsgHead::MSG_HEAD_BYTES + len));

	// write head.
	head.Encode((char*)buf.GetWritePointer());
	buf.WriteComplete(WAMsgHead::MSG_HEAD_BYTES);

	if (!proto.SerializeToArray(buf.GetWritePointer(), len))
		return 0;

	buf.WriteComplete(len);

	return SendMsg((const char*)buf.GetReadPointer(), buf.ActiveSize());
}

int WATcp::SendMsg(const char* data_, int len_)
{
	return (int)_socket.write(data_, len_);
}

void WATcp::OnConnected()
{
	if (_is_debug) qDebug() << "Tcp connected.";
	_is_connect = true;
	emit TcpConnected();

	static int idx = 1;
	
	{
		CSProto::LoginReq req;
		req.set_username("Allen" + std::to_string(idx++));
		SendProto(CSProto::LoginReqID, req);
	}

	{
		CSProto::EnterRoomReq req;
		SendProto(CSProto::EnterRoomReqID, req);
	}

	{
		CSProto::MoveReq req;
		auto m = req.mutable_movement();
		m->set_movedir(1);
		m->set_facedir(2);
		m->set_time(1600000000);
		m->set_movetype(3);

		auto pos = m->mutable_position();
		pos->set_indexx(999);
		pos->set_indexy(888);

		SendProto(CSProto::MoveReqID, req);
	}
}

void WATcp::OnClosed()
{
	if (_is_debug) qDebug() << "Tcp closed!";
	_is_connect = false;
	emit TcpClosed();
}

void WATcp::OnReadyRead()
{
	int bytes = _socket.read((char*)_readbuf.GetWritePointer(), _readbuf.SpareSize());
	if (bytes < 0) Close();

	_readbuf.WriteComplete(bytes);

	while (_readbuf.ActiveSize() >= WAMsgHead::MSG_HEAD_BYTES)
	{
		WAMsgHead head;

		int body_size = Decode((const char*)_readbuf.GetReadPointer(), (int)_readbuf.ActiveSize(), head);
		if (body_size < 0)
			break;

		// TODO: process.
		/*handler::handler_mgr_t::instance()->process(_handle, head.msgid(),
			(const char*)_readbuf.get_read_ptr() + msg_head_t::MSG_HEAD_BYTES, body_size);*/

		emit TcpRead((const char*)_readbuf.GetReadPointer() + WAMsgHead::MSG_HEAD_BYTES, body_size);

		_readbuf.ReadComplete(WAMsgHead::MSG_HEAD_BYTES + body_size);
	}

	

	/*std::string data = "test data.";

	char MsgData[6] = { 0 };

	MsgHeader* pHead = (MsgHeader*)MsgData;
	pHead->msgid = htons(1);
	pHead->len = htonl(data.length() + 6);

	std::string pack;
	pack.append(MsgData, 6);
	pack += data;

	SendMsg(pack.c_str(), pack.length());*/
}

int WATcp::Decode(const char* data, int size, WAMsgHead& head)
{
	if (size < WAMsgHead::MSG_HEAD_BYTES)
		return -1;

	head.Decode(data);

	if ((int)head.Length() > (size - WAMsgHead::MSG_HEAD_BYTES))
		return -2;

	return head.Length();
}


