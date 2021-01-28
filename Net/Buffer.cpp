
/*
 * @author WardenAllen
 * @date   2021/01/14 16:19:52
 * @brief
 */

#include "Buffer.h"

#include <string.h>

#include "buffer.h"

WABuffer::WABuffer() : _head(0), _tail(0), _data()
{
	_data.resize(8192);
}

WABuffer::WABuffer(std::size_t size) :
	_head(0), _tail(0), _data()
{
	_data.resize(size);
}

WABuffer::WABuffer(const WABuffer& other) :
	_head(other._head), _tail(other._tail), _data(other._data)
{
}

WABuffer::WABuffer(WABuffer&& other) noexcept :
	_head(other._head), _tail(other._tail), _data(other.MoveData())
{
}

WABuffer& WABuffer::operator=(const WABuffer& other)
{
	if (this == &other) return *this;

	_head = other._head;
	_tail = other._tail;
	_data = other._data;

	return *this;
}

WABuffer& WABuffer::operator=(WABuffer&& other) noexcept
{
	if (this == &other) return *this;

	_head = other._head;
	_tail = other._tail;
	_data = other.MoveData();

	return *this;
}

WABuffer::~WABuffer()
{
}

void WABuffer::Reset()
{
	_head = 0;
	_tail = 0;
}

void WABuffer::Resize(size_type bytes)
{
	_data.resize(bytes);
}

void WABuffer::Write(const void* data, std::size_t size)
{
	if (!size) return;

	memcpy(GetWritePointer(), data, size);
	WriteComplete(size);
}

void WABuffer::Normalize()
{
	if (!_tail) return;

	if (_tail != _head)
		memmove(GetBasePointer(), GetReadPointer(), ActiveSize());

	_head -= _tail;
	_tail = 0;
}

void WABuffer::CheckSize()
{
	if (SpareSize() == 0)
		_data.resize(_data.size() << 1);
}

std::vector<uint8_t>&& WABuffer::MoveData()
{
	_head = 0;
	_tail = 0;
	return std::move(_data);
}

