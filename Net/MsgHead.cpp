/*
 * @author WardenAllen
 * @date   2021/01/14 16:31:57
 * @brief
 */

#include <string.h>
#include <windows.h>

#include "MsgHead.h"

WAMsgHead::WAMsgHead() :
	_len(0), _msgid(0)
{
}

WAMsgHead::WAMsgHead(uint32_t s, uint16_t id) :
	_len(s), _msgid(id)
{
}

WAMsgHead::~WAMsgHead()
{
}

void WAMsgHead::Encode(char* data)
{
	uint16_t net_msgid = htons(_msgid);
	memcpy(data, (void*)(&net_msgid), sizeof(_msgid));

	uint32_t pack_len = _len + MSG_HEAD_BYTES;
	uint32_t net_len = htonl(pack_len);
	memcpy(data + sizeof(_msgid), (void*)(&net_len), sizeof(_len));
}

void WAMsgHead::Decode(const char* data)
{
	uint16_t net_msgid = 0;
	memcpy(&net_msgid, data, sizeof(_msgid));
	_msgid = ntohs(net_msgid);

	uint32_t pack_len = 0;
	memcpy(&pack_len, data + sizeof(_msgid), sizeof(_len));
	_len = ntohl(pack_len) - MSG_HEAD_BYTES;
}
