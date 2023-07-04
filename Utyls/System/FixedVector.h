#pragma once
#include <cstdlib>
#include <Windows.h>
#define WIN32_LEAN_AND_MEAN

template <class T, size_t MAX_ALLOC>
class FixedVector {
public:
	FixedVector();
	

	void clear();
	void insert_back(T&&);

	void destroy();

public:
	size_t m_Size = 0;
	T* m_pData;
private:
	bool m_Usable;
	const int m_MaxSize;
};

template <class T, size_t MAX_ALLOC>
FixedVector<T, MAX_ALLOC>::FixedVector() : m_Usable(true), m_MaxSize(MAX_ALLOC) {
	this->m_pData = (T*)malloc(MAX_ALLOC * sizeof(T));
	ZeroMemory(this->m_pData, MAX_ALLOC * sizeof(T));
}

template <class T, size_t MAX_ALLOC>
void FixedVector<T, MAX_ALLOC>::destroy() {
	if (this->m_pData) {
		free(this->m_pData);
	}
}

template <class T, size_t MAX_ALLOC>
void FixedVector<T, MAX_ALLOC>::clear() {
	this->m_Size = 0;
}

template <class T, size_t MAX_ALLOC>
void FixedVector<T, MAX_ALLOC>::insert_back(T&& data) {
	const int size = this->m_Size;
	if (this->m_Usable && (size < this->m_MaxSize)) {
		this->m_pData[size] = data;
		this->m_Size++;
	}
}