#pragma once
#include <AcidLib/Math/Math.hpp>
#include <AcidLib/Utilities/Iterator.hpp>
#include <AcidLib/Utilities/ConstIterator.hpp>
#include <AcidLib/Exception/IndexOutOfBoundsException.hpp>

namespace ac {

	template <typename T>
	class DynamicArray {
	public:

		DynamicArray();

		explicit DynamicArray(int p_size);

		DynamicArray(T* p_data, int p_size);

		DynamicArray(const DynamicArray& other);

		DynamicArray(DynamicArray&& other) noexcept;

		~DynamicArray();

		DynamicArray& operator=(const DynamicArray& other);

		DynamicArray& operator=(DynamicArray&& other) noexcept;

		T& operator[](int index);

		const T& operator[](int index) const;

		bool operator==(const DynamicArray& other) const;

		bool operator!=(const DynamicArray& other) const;

		bool contains(const T& p_element) const;

		T* data();

		const T* data() const;

		int size();

		void resize(int p_size);

		Iterator<T> begin();

		Iterator<T> end();

		ConstIterator<T> begin() const;
		ConstIterator<T> end() const;

	private:

		int mapIndex(int index) const;

		int m_size;

		T* m_data;
	};

	template <typename T>
	DynamicArray<T>::DynamicArray() {

		m_size = 0;

		m_data = nullptr;
	}

	template <typename T>
	DynamicArray<T>::DynamicArray(int p_size) {

		if (p_size <= 0) {

			m_size = 0;

			m_data = nullptr;
		}
		else {

			m_size = p_size;

			m_data = new T[m_size];
		}
	}

	template <typename T>
	DynamicArray<T>::DynamicArray(T* p_data, int p_size) {

		if (p_size <= 0) {

			m_size = 0;

			m_data = nullptr;
		}
		else {

			m_size = p_size;

			m_data = new T[m_size];
		}

		for (int i = 0; i < m_size; i++) {

			m_data[i] = p_data[i];
		}
	}

	template <typename T>
	DynamicArray<T>::DynamicArray(const DynamicArray& other) {

		m_size = other.m_size;

		if (m_size <= 0) {

			m_data = nullptr;
		}
		else {

			m_data = new T[m_size];
		}

		for (int i = 0; i < m_size; i++) {

			m_data[i] = other.m_data[i];
		}
	}

	template <typename T>
	DynamicArray<T>::DynamicArray(DynamicArray&& other) noexcept {

		m_size = other.m_size;
		m_data = other.m_data;

		other.m_size = 0;
		other.m_data = nullptr;
	}

	template <typename T>
	DynamicArray<T>::~DynamicArray() {

		delete[] m_data;
	}

	template <typename T>
	DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray<T>& other) {

		delete[] m_data;

		m_size = other.m_size;

		if (m_size <= 0) {

			m_data = nullptr;
		}
		else {

			m_data = new T[m_size];
		}

		for (int i = 0; i < m_size; i++) {

			m_data[i] = other.m_data[i];
		}

		return *this;
	}

	template <typename T>
	DynamicArray<T>& DynamicArray<T>::operator=(DynamicArray<T>&& other) noexcept {

		delete[] m_data;

		m_size = other.m_size;
		m_data = other.m_data;

		other.m_size = 0;
		other.m_data = nullptr;

		return *this;
	}

	template <typename T>
	T& DynamicArray<T>::operator[](int index) {

		index = mapIndex(index);

		if (index < 0 || index >= m_size) {

			throw IndexOutOfBoundsException(index, -m_size, m_size - 1);
		}

		return m_data[index];
	}

	template <typename T>
	const T& DynamicArray<T>::operator[](int index) const {

		index = mapIndex(index);

		if (index < 0 || index >= m_size) {

			throw IndexOutOfBoundsException(index, -m_size, m_size - 1);
		}

		return m_data[index];
	}

	template <typename T>
	bool DynamicArray<T>::operator==(const DynamicArray& other) const {

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
	bool DynamicArray<T>::operator!=(const DynamicArray& other) const {

		return !(*this == other);
	}

	template <typename T>
	bool DynamicArray<T>::contains(const T& p_element) const {

		for (int i = 0; i < m_size; i++) {

			if (m_data[i] == p_element) {

				return true;
			}
		}

		return false;
	}

	template <typename T>
	T* DynamicArray<T>::data() {

		return m_data;
	}

	template <typename T>
	const T* DynamicArray<T>::data() const {

		return m_data;
	}

	template <typename T>
	int DynamicArray<T>::size() {

		return m_size;
	}

	template <typename T>
	void DynamicArray<T>::resize(int p_size) {

		if (p_size <= 0) {

			delete[] m_data;

			m_size = 0;
			m_data = nullptr;
		}
		else {

			T* newData = new T[p_size];

			for (int i = 0; i < min(m_size, p_size); i++) {

				newData[i] = m_data[i];
			}

			delete[] m_data;

			m_size = p_size;

			m_data = newData;
		}
	}

	template <typename T>
	Iterator<T> DynamicArray<T>::begin() {

		return Iterator<T>(m_data);
	}

	template <typename T>
	Iterator<T> DynamicArray<T>::end() {

		return Iterator<T>(m_data + m_size);
	}

	template <typename T>
	ConstIterator<T> DynamicArray<T>::begin() const {

		return ConstIterator<T>(m_data);
	}

	template <typename T>
	ConstIterator<T> DynamicArray<T>::end() const {

		return ConstIterator<T>(m_data + m_size);
	}

	template <typename T>
	int DynamicArray<T>::mapIndex(int index) const {

		if (index < 0) {

			index = m_size + index;
		}

		return index;
	}
}