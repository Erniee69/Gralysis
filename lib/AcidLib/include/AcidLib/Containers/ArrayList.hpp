#pragma once
#include <AcidLib/Utilities/Iterator.hpp>
#include <AcidLib/Utilities/ConstIterator.hpp>
#include <AcidLib/Math/Math.hpp>
#include <AcidLib/Exception/IndexOutOfBoundsException.hpp>

namespace ac {

	template <typename T>
	class ArrayList {
	public:

		ArrayList();

		ArrayList(const ArrayList& other);

		ArrayList(ArrayList&& other) noexcept;

		~ArrayList();

		ArrayList& operator=(const ArrayList& other);

		ArrayList& operator=(ArrayList&& other);

		T& operator[](int index);

		const T& operator[](int index) const;

		bool operator==(const ArrayList& other) const;

		bool operator!=(const ArrayList& other) const;

		bool contains(const T& p_element) const;

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

		Iterator<T> begin();

		Iterator<T> end();

		ConstIterator<T> begin() const;

		ConstIterator<T> end() const;

	private:

		int mapIndex(int index) const;

		T* m_data;

		int m_size;
		int m_capacity;
	};

	template <typename T>
	ArrayList<T>::ArrayList() {

		m_size = 0;
		m_capacity = 0;

		m_data = nullptr;
	}

	template <typename T>
	ArrayList<T>::ArrayList(const ArrayList& other) {

		m_size = other.m_size;
		m_capacity = other.m_capacity;

		m_data = new T[m_capacity];

		for (int i = 0; i < m_size; i++) {

			m_data[i] = other.m_data[i];
		}
	}

	template <typename T>
	ArrayList<T>::ArrayList(ArrayList&& other) noexcept {

		m_size = other.m_size;
		m_capacity = other.m_capacity;
		m_data = other.m_data;

		other.m_size = 0;
		other.m_capacity = 0;
		other.m_data = nullptr;
	}

	template <typename T>
	ArrayList<T>::~ArrayList() {

		delete[] m_data;
	}

	template <typename T>
	ArrayList<T>& ArrayList<T>::operator=(const ArrayList& other) {

		delete[] m_data;

		m_size = other.m_size;
		m_capacity = other.m_capacity;

		m_data = new T[m_capacity];

		for (int i = 0; i < m_size; i++) {

			m_data[i] = other.m_data[i];
		}

		return *this;
	}

	template <typename T>
	ArrayList<T>& ArrayList<T>::operator=(ArrayList&& other) {

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
	T& ArrayList<T>::operator[](int index) {

		index = mapIndex(index);

		if (index < 0 || index >= m_size) {

			throw IndexOutOfBoundsException(index, -m_size, m_size - 1);
		}

		return m_data[index];
	}

	template <typename T>
	const T& ArrayList<T>::operator[](int index) const {

		index = mapIndex(index);

		if (index < 0 || index >= m_size) {

			throw IndexOutOfBoundsException(index, -m_size, m_size - 1);
		}

		return m_data[index];
	}

	template <typename T>
	bool ArrayList<T>::operator==(const ArrayList& other) const {

		if (m_size != other.m_size) {

			return false;
		}

		for (int i = 0; i < m_size; i++) {

			if (m_data[i] != other.m_data[i]) {

				return false;
			}
		}

		return true;
	}

	template <typename T>
	bool ArrayList<T>::operator!=(const ArrayList& other) const {

		return !(*this == other);
	}

	template <typename T>
	bool ArrayList<T>::contains(const T& p_element) const {

		for (int i = 0; i < m_size; i++) {

			if (m_data[i] == p_element) {

				return true;
			}
		}

		return false;
	}

	template <typename T>
	void ArrayList<T>::append(const T& element) {

		if (m_capacity == 0) {

			m_capacity = 1;
			m_data = new T[m_capacity];
		}
		else if (m_capacity <= m_size) {

			m_capacity = m_capacity * 2;
			T* tmp = new T[m_capacity];

			for (int i = 0; i < m_size; i++) {

				tmp[i] = m_data[i];
			}

			delete[] m_data;
			m_data = tmp;
		}

		m_data[m_size] = element;
		m_size++;
	}

	template <typename T>
	void ArrayList<T>::insert(const T& element, int index) {

		index = mapIndex(index);

		if (index < 0 || index >= m_size) {

			throw IndexOutOfBoundsException(index, -m_size, m_size - 1);
		}

		if (m_capacity == 0) {

			m_capacity = 1;
			m_data = new T[m_capacity];
		}
		else if (m_capacity <= m_size) {

			m_capacity = m_capacity * 2;
			T* tmp = new T[m_capacity];

			for (int i = 0; i < m_size; i++) {

				tmp[i] = m_data[i];
			}

			delete[] m_data;
			m_data = tmp;
		}

		for (int i = m_size; i > index; i--) {

			m_data[i] = m_data[i - 1];
		}

		m_data[index] = element;
		m_size++;
	}

	template <typename T>
	void ArrayList<T>::remove(int index) {

		index = mapIndex(index);

		if (index < 0 || index >= m_size) {

			throw IndexOutOfBoundsException(index, -m_size, m_size - 1);
		}

		m_size--;

		for (int i = index; i < m_size; i++) {

			m_data[i] = m_data[i + 1];
		}
	}

	template <typename T>
	void ArrayList<T>::clear() {

		m_size = 0;
	}

	template <typename T>
	void ArrayList<T>::resize(int p_size) {

		if (p_size > m_capacity) {

			reserve(p_size);
		}

		m_size = max(0, p_size);
	}

	template <typename T>
	void ArrayList<T>::reserve(int p_capacity) {

		if (p_capacity <= 0) {

			m_size = 0;
			m_capacity = 0;
			m_data = nullptr;
		}
		else {

			m_size = min(m_size, p_capacity);
			m_capacity = p_capacity;

			T* tmp = new T[m_capacity];

			for (int i = 0; i < m_size; i++) {

				tmp[i] = m_data[i];
			}

			delete[] m_data;

			m_data = tmp;
		}
	}

	template <typename T>
	int ArrayList<T>::size() const {

		return m_size;
	}

	template <typename T>
	int ArrayList<T>::capacity() const {

		return m_capacity;
	}

	template <typename T>
	T* ArrayList<T>::data() {

		return m_data;
	}

	template <typename T>
	const T* ArrayList<T>::data() const {

		return m_data;
	}

	template <typename T>
	Iterator<T> ArrayList<T>::begin() {

		return Iterator<T>(m_data);
	}

	template <typename T>
	Iterator<T> ArrayList<T>::end() {

		return Iterator<T>(m_data + m_size);
	}

	template <typename T>
	ConstIterator<T> ArrayList<T>::begin() const {

		return ConstIterator<T>(m_data);
	}

	template <typename T>
	ConstIterator<T> ArrayList<T>::end() const {

		return ConstIterator<T>(m_data + m_size);
	}

	template <typename T>
	int ArrayList<T>::mapIndex(int index) const {

		if (index < 0) {

			index = m_size + index;
		}

		return index;
	}
}