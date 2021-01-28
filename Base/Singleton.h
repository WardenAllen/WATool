#pragma once

/*
 * @author WardenAllen
 * @date   2020/10/26 19:57:12
 * @brief  Singleton helper template.
 */

/* 1. c++11 style template. */

template <class T>
class Singleton
{
protected:
	Singleton() = default;
	virtual ~Singleton() = default;

private:
	Singleton(const T& other) = delete;

public:
	static T* instance() {
		static T instance;
		return &instance;
	}
};

