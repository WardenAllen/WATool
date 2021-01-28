
/*
 * @author WardenAllen
 * @date   2021/01/14 16:31:57
 * @brief  
 */

#pragma once

#include <inttypes.h>

 /**
  * head's format:
  *
  * +----------+--------------------+
  * |   msgid  |        size        |
  * |  2 bytes |       4 bytes      |
  * +----------+--------------------+
  *
  */

#pragma pack(1)

class WAMsgHead
{
public:
	WAMsgHead();
	WAMsgHead(uint32_t s, uint16_t id);
	~WAMsgHead();

public:
	static constexpr int MSG_HEAD_BYTES = 6;

public:
	void Encode(char* data);
	void Decode(const char* data);

public:
	inline uint32_t Length() { return _len; }
	inline uint16_t MsgID() { return _msgid; }
	inline void SetLength(uint32_t len) { _len = len; }
	inline void SetMsgID(uint16_t id) { _msgid = id; }

private:
	uint32_t _len;
	uint16_t _msgid;
};

#pragma pack()