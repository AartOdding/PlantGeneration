#pragma once

#include <functional>



namespace LSystem
{

	// From: https://stackoverflow.com/questions/2590677/how-do-i-combine-hash-values-in-c0x
	template <class T>
	inline void AddToHash(std::size_t& hash, const T& value)
	{
		std::hash<T> hasher;
		hash ^= hasher(value) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
	}

}
