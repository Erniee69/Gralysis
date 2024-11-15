#pragma once

template <typename T>
class Iterator {
public:

	Iterator(T* p_element);

	T& operator*() const;

	T* operator->() const;

	Iterator& operator++();

	Iterator operator++(int);

	bool operator==(const Iterator& other);
	bool operator!=(const Iterator& other);

private:

	T* m_element;
};

template <typename T>
Iterator<T>::Iterator(T* p_element) {

	m_element = p_element;
}

template <typename T>
T& Iterator<T>::operator*() const {

	return *m_element;
}

template <typename T>
T* Iterator<T>::operator->() const {

	return m_element;
}

template <typename T>
Iterator<T>& Iterator<T>::operator++() {

	m_element++;

	return *this;
}

template <typename T>
Iterator<T> Iterator<T>::operator++(int) {

	Iterator tmp = *this;

	m_element++;

	return tmp;
}

template <typename T>
bool Iterator<T>::operator==(const Iterator& other) {

	return m_element == other.m_element;
}

template <typename T>
bool Iterator<T>::operator!=(const Iterator& other) {

	return m_element != other.m_element;
}