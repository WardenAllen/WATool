
/*
 * @author WardenAllen
 * @date   2021/01/14 16:19:52
 * @brief  
 */

#pragma once

#include <vector>
#include <string>
#include <inttypes.h>

class WABuffer
{
	using size_type = std::vector<uint8_t>::size_type;

public:
	WABuffer();
	explicit WABuffer(std::size_t size);
	WABuffer(const WABuffer& other);
	WABuffer(WABuffer&& other) noexcept;
	WABuffer& operator= (const WABuffer& other);
	WABuffer& operator= (WABuffer&& other) noexcept;
	~WABuffer();

public:
	/* reset buffer. */
	void Reset();

	/* resize data vec. */
	void Resize(size_type bytes);

	/* write data. */
	void Write(const void* data, std::size_t size);

	/* discard inactive data(already read). */
	void Normalize();

	/* auto resize when space is not enough. */
	void CheckSize();

	/* used when copy to another buffer. */
	std::vector<uint8_t>&& MoveData();

public:
	inline uint8_t* GetBasePointer() { return _data.data(); }
	inline uint8_t* GetReadPointer() { return GetBasePointer() + _tail; }
	inline uint8_t* GetWritePointer() { return GetBasePointer() + _head; }
	inline void ReadComplete(size_type bytes) { _tail += bytes; }
	inline void WriteComplete(size_type bytes) { _head += bytes; }
	inline size_type ActiveSize() { return _head - _tail; }
	inline size_type SpareSize() { return _data.size() - _head; }
	inline size_type TotalSize() { return _data.size(); }

private:
	size_type _head;
	size_type _tail;
	std::vector<uint8_t> _data;

};

