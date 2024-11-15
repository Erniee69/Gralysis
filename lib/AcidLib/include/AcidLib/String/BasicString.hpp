#pragma once
#include <AcidLib/Math/Math.hpp>
#include <AcidLib/Exception/IndexOutOfBoundsException.hpp>

namespace ac {

	template <typename T>
	class BasicString {
	public:

		BasicString();

		BasicString(const T* p_data);

		BasicString(char p_data);

		BasicString(const BasicString& other);

		BasicString(BasicString&& other) noexcept;

		~BasicString();

		BasicString& operator=(const BasicString& other);

		BasicString& operator=(BasicString&& other) noexcept;

		T& operator[](int index);

		const T& operator[](int index) const;

		bool operator==(const BasicString& other) const;

		bool operator!=(const BasicString& other) const;

		bool operator<(const BasicString& other) const;

		bool operator>(const BasicString& other) const;

		bool operator<=(const BasicString& other) const;

		bool operator>=(const BasicString& other) const;

		BasicString operator+(const BasicString& other) const;

		BasicString& operator+=(const BasicString& other);

		void append(const T& element);

		void insert(const T& element, int index);

		void remove(int index);

		void clear();

		void resize(int p_size);

		void reserve(int p_capacity);

		int size() const;

		int capacity() const;

		T* data();

		const T* data() const;

		const T* cstr() const;

		bool isEmpty() const;

	private:

		int mapIndex(int index) const;

		int m_size;
		int m_capacity;
		T* m_data;
	};

	template <typename T>
	BasicString<T>::BasicString() {

		m_size = 0;
		m_capacity = 1;
		m_data = new T[m_capacity];

		m_data[0] = '\0';
	}

	template <typename T>
	BasicString<T>::BasicString(char p_data) {

		m_size = 1;
		m_capacity = 2;
		m_data = new T[m_capacity];

		m_data[0] = p_data;
		m_data[1] = '\0';
	}

	template <typename T>
	BasicString<T>::BasicString(const T* p_data) {

		m_size = 0;
		m_capacity = 1;
		m_data = new T[m_capacity];

		m_data[0] = '\0';

		int i = 0;

		while (p_data[i] != '\0') {

			append(p_data[i]);
			i++;
		}
	}

	template <typename T>
	BasicString<T>::BasicString(const BasicString& other) {

		m_size = other.m_size;
		m_capacity = other.m_capacity;
		m_data = new T[m_capacity];

		for (int i = 0; i < m_size; i++) {

			m_data[i] = other.m_data[i];
		}

		m_data[m_size] = '\0';
	}

	template <typename T>
	BasicString<T>::BasicString(BasicString&& other) noexcept {

		m_size = other.m_size;
		m_capacity = other.m_capacity;
		m_data = other.m_data;

		other.m_size = 0;
		other.m_capacity = 0;
		other.m_data = nullptr;
	}

	template <typename T>
	BasicString<T>::~BasicString() {

		delete[] m_data;
	}

	template <typename T>
	BasicString<T>& BasicString<T>::operator=(const BasicString<T>& other) {

		delete[] m_data;

		m_size = other.m_size;
		m_capacity = other.m_capacity;
		m_data = new T[m_capacity];

		for (int i = 0; i < m_size; i++) {

			m_data[i] = other.m_data[i];
		}

		m_data[m_size] = '\0';

		return *this;
	}

	template <typename T>
	BasicString<T>& BasicString<T>::operator=(BasicString<T>&& other) noexcept {

		delete[] m_data;

		m_size = other.m_size;
		m_capacity = other.m_capacity;
		m_data = other.m_data;

		other.m_size = 0;
		other.m_capacity = 0;
		other.m_data = nullptr;

		return *this;
	}

	template <typename T>
	T& BasicString<T>::operator[](int index) {

		index = mapIndex(index);

		if (index < 0 || index >= m_size) {

			throw IndexOutOfBoundsException(index, -m_size, m_size - 1);
		}

		return m_data[index];
	}

	template <typename T>
	const T& BasicString<T>::operator[](int index) const {

		index = mapIndex(index);

		if (index < 0 || index >= m_size) {

			throw IndexOutOfBoundsException(index, -m_size, m_size - 1);
		}

		return m_data[index];
	}

	template <typename T>
	bool BasicString<T>::operator==(const BasicString& other) const {

		bool result = m_size == other.m_size;

		if (result) {

			for (int i = 0; i < m_size; i++) {

				result = result && (m_data[i] == other.m_data[i]);
			}
		}

		return result;
	}

	template <typename T>
	bool BasicString<T>::operator!=(const BasicString& other) const {

		return !(*this == other);
	}

	template <typename T>
	bool BasicString<T>::operator<(const BasicString& other) const {

		for (int i = 0; i < min(m_size, other.m_size); i++) {

			if (m_data[i] < other.m_data[i]) {

				return true;
			}
			else if (m_data[i] > other.m_data[i]) {

				return false;
			}
		}

		return m_size < other.m_size;
	}

	template <typename T>
	bool BasicString<T>::operator>(const BasicString& other) const {

		for (int i = 0; i < min(m_size, other.m_size); i++) {

			if (m_data[i] < other.m_data[i]) {

				return false;
			}
			else if (m_data[i] > other.m_data[i]) {

				return true;
			}
		}

		return m_size > other.m_size;
	}

	template <typename T>
	bool BasicString<T>::operator<=(const BasicString& other) const {

		for (int i = 0; i < min(m_size, other.m_size); i++) {

			if (m_data[i] < other.m_data[i]) {

				return true;
			}
			else if (m_data[i] > other.m_data[i]) {

				return false;
			}
		}

		return m_size <= other.m_size;
	}

	template <typename T>
	bool BasicString<T>::operator>=(const BasicString& other) const {

		for (int i = 0; i < min(m_size, other.m_size); i++) {

			if (m_data[i] < other.m_data[i]) {

				return false;
			}
			else if (m_data[i] > other.m_data[i]) {

				return true;
			}
		}

		return m_size >= other.m_size;
	}

	template <typename T>
	BasicString<T> BasicString<T>::operator+(const BasicString& other) const {

		BasicString<T> result;

		result.resize(m_size + other.m_size);

		for (int i = 0; i < m_size; i++) {

			result.m_data[i] = m_data[i];
		}

		for (int i = m_size; i < other.m_size; i++) {

			result[m_size + i] = m_data[i];
		}

		return result;
	}

	template <typename T>
	BasicString<T>& BasicString<T>::operator+=(const BasicString& other) {

		int oldSize = m_size;

		resize(m_size + other.m_size);

		for (int i = oldSize; i < m_size; i++) {

			m_data[i] = other.m_data[i - oldSize];
		}

		return *this;
	}

	template <typename T>
	void BasicString<T>::append(const T& element) {

		if (m_size == m_capacity - 1) {

			m_capacity = 2 * m_capacity;

			T* tmp = new T[m_capacity];

			for (int i = 0; i < m_size; i++) {

				tmp[i] = m_data[i];
			}

			delete[] m_data;

			m_data = tmp;
		}

		m_data[m_size] = element;
		m_size++;
		m_data[m_size] = '\0';
	}

	template <typename T>
	void BasicString<T>::insert(const T& element, int index) {

		index = mapIndex(index);

		if (index < 0 || index >= m_size) {

			throw IndexOutOfBoundsException(index, -m_size, m_size - 1);
		}

		if (m_size == m_capacity - 1) {

			m_capacity = 2 * m_capacity;

			T* tmp = new T[m_capacity];

			for (int i = 0; i < m_size; i++) {

				tmp[i] = m_data[i];
			}

			delete[] m_data;

			m_data = tmp;
		}

		for (int i = m_size - 1; i > index; i--) {

			m_data[i] = m_data[i - 1];
		}

		m_data[index] = element;
		m_size++;

		m_data[m_size] = '\0';
	}

	template <typename T>
	void BasicString<T>::remove(int index) {

		index = mapIndex(index);

		if (index < 0 || index >= m_size) {

			throw IndexOutOfBoundsException(index, -m_size, m_size - 1);
		}

		for (int i = index; i < m_size - 1; i--) {

			m_data[i] = m_data[i + 1];
		}

		m_size--;
		m_data[m_size] = '\0';
	}

	template <typename T>
	void BasicString<T>::clear() {

		m_size = 0;
		m_data[0] = '\0';
	}

	template <typename T>
	void BasicString<T>::resize(int p_size) {

		if (m_capacity - 1 < p_size) {

			m_capacity = p_size + 1;

			T* tmp = new T[m_capacity];

			for (int i = 0; i < m_size; i++) {

				tmp[i] = m_data[i];
			}

			delete[] m_data;

			m_data = tmp;
		}

		m_size = p_size;
		m_data[m_size] = '\0';
	}

	template <typename T>
	void BasicString<T>::reserve(int p_capacity) {

		m_size = min(m_size, p_capacity);
		m_capacity = p_capacity + 1;

		T* tmp = new T[m_capacity];

		for (int i = 0; i < m_size; i++) {

			tmp[i] = m_data[i];
		}

		delete[] m_data;

		m_data = tmp;
	}

	template <typename T>
	int BasicString<T>::size() const {

		return m_size;
	}

	template <typename T>
	int BasicString<T>::capacity() const {

		return m_capacity - 1;
	}

	template <typename T>
	T* BasicString<T>::data() {

		return m_data;
	}

	template <typename T>
	const T* BasicString<T>::data() const {

		return m_data;
	}

	template <typename T>
	const T* BasicString<T>::cstr() const {

		return m_data;
	}

	template <typename T>
	bool BasicString<T>::isEmpty() const {

		return m_size == 0;
	}

	template <typename T>
	int BasicString<T>::mapIndex(int index) const {

		if (index < 0) {

			index = m_size + index;
		}

		return index;
	}
}