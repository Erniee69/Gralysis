#pragma once

template <typename T>
class ConstIterator {
public:

	ConstIterator(T* p_element);

	const T& operator*() const;

	const T* operator->() const;

	ConstIterator& operator++();

	ConstIterator operator++(int);

	bool operator==(const ConstIterator& other);
	bool operator!=(const ConstIterator& other);

private:

	T* m_element;
};

template <typename T>
ConstIterator<T>::ConstIterator(T* p_element) {

	m_element = p_element;
}

template <typename T>
const T& ConstIterator<T>::operator*() const {

	return *m_element;
}

template <typename T>
const T* ConstIterator<T>::operator->() const {

	return m_element;
}

template <typename T>
ConstIterator<T>& ConstIterator<T>::operator++() {

	m_element++;

	return *this;
}

template <typename T>
ConstIterator<T> ConstIterator<T>::operator++(int) {

	Iterator tmp = *this;

	m_element++;

	return tmp;
}

template <typename T>
bool ConstIterator<T>::operator==(const ConstIterator& other) {

	return m_element == other.m_element;
}

template <typename T>
bool ConstIterator<T>::operator!=(const ConstIterator& other) {

	return m_element != other.m_element;
}