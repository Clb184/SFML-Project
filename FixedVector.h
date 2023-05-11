#pragma once
#include <cstdlib>

template <class T>
class FixedVector {
public:
	FixedVector();
	FixedVector(size_t);
	

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

template <class T>
FixedVector<T>::FixedVector() : m_Usable(false), m_MaxSize(0) {

}

template <class T>
FixedVector<T>::FixedVector(size_t alloc) : m_Usable(true), m_MaxSize(alloc) {
	this->m_pData = (T*)std::malloc(alloc * sizeof(T));
	ZeroMemory(this->m_pData, alloc * sizeof(T));
}

template <class T>
void FixedVector<T>::destroy() {
	if (this->m_pData) {
		free(this->m_pData);
	}
}

template <class T>
void FixedVector<T>::clear() {
	this->m_Size = 0;
}

template <class T>
void FixedVector<T>::insert_back(T&& data) {
	const int size = this->m_Size;
	if (this->m_Usable && (size < this->m_MaxSize)) {
		this->m_pData[size] = data;
		this->m_Size++;
	}
}