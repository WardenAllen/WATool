
/*
 * @author WardenAllen
 * @date   2020/10/27 15:46:04
 * @brief  
 */

#pragma once

template <class T>
class Singleton
{
protected:
	Singleton() = default;
	virtual ~Singleton() = default;

private:
	Singleton(const T& other) = delete;

public:
	static T* Instance() {
		static T instance;
		return &instance;
	}
};