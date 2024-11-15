#pragma once
#include <AcidLib/Utilities/Iterator.hpp>
#include <AcidLib/Utilities/ConstIterator.hpp>
#include <AcidLib/Exception/IndexOutOfBoundsException.hpp>

namespace ac {

	template <typename T, unsigned int t_size>
	class Array {
	public:

		Array();

		explicit Array(T* p_data);

		Array(const Array& other);

		Array(Array&& other) noexcept;

		~Array();

		Array& operator=(const Array& other);

		Array& operator=(Array&& other) noexcept;

		T& operator[](int index);

		const T& operator[](int index) const;

		bool operator==(const Array& other) const;

		bool operator!=(const Array& other) const;

		bool contains(const T& p_element) const;

		T* data();

		const T* data() const;

		int size() const;

		Iterator<T> begin();
		Iterator<T> end();

		ConstIterator<T> begin() const;
		ConstIterator<T> end() const;

	private:

		int mapIndex(int index) const;

		T* m_data;
	};

	template <typename T, unsigned int t_size>
	Array<T, t_size>::Array() {

		m_data = new T[t_size];
	}

	template <typename T, unsigned int t_size>
	Array<T, t_size>::Array(T* p_data) {

		m_data = new T[t_size];

		for (int i = 0; i < t_size; i++) {

			m_data[i] = p_data[i];
		}
	}

	template <typename T, unsigned int t_size>
	Array<T, t_size>::Array(const Array& other) {

		m_data = new T[t_size];

		for (int i = 0; i < t_size; i++) {

			m_data[i] = other.m_data[i];
		}
	}

	template <typename T, unsigned int t_size>
	Array<T, t_size>::Array(Array&& other) noexcept {

		m_data = other.m_data;
		other.m_data = nullptr;
	}

	template <typename T, unsigned int t_size>
	Array<T, t_size>::~Array() {

		delete[] m_data;
	}

	template <typename T, unsigned int t_size>
	Array<T, t_size>& Array<T, t_size>::operator=(const Array<T, t_size>& other) {

		for (int i = 0; i < t_size; i++) {

			m_data[i] = other.m_data[i];
		}

		return *this;
	}

	template <typename T, unsigned int t_size>
	Array<T, t_size>& Array<T, t_size>::operator=(Array<T, t_size>&& other) noexcept {

		m_data = other.m_data;
		other.m_data = nullptr;

		return *this;
	}

	template <typename T, unsigned int t_size>
	T& Array<T, t_size>::operator[](int index) {

		index = mapIndex(index);

		if (index < 0 || index >= t_size) {

			throw IndexOutOfBoundsException(index, -int(t_size), t_size - 1);
		}

		return m_data[index];
	}

	template <typename T, unsigned int t_size>
	const T& Array<T, t_size>::operator[](int index) const {

		index = mapIndex(index);

		if (index < 0 || index >= t_size) {

			throw IndexOutOfBoundsException(index, -int(t_size), t_size - 1);
		}

		return m_data[index];
	}

	template <typename T, unsigned int t_size>
	bool Array<T, t_size>::operator==(const Array& other) const {

		for (int i = 0; i < t_size; i++) {

			if (m_data[i] != other.m_data[i]) {

				return false;
			}
		}

		return true;
	}

	template <typename T, unsigned int t_size>
	bool Array<T, t_size>::operator!=(const Array& other) const {

		return !(*this == other);
	}

	template <typename T, unsigned int t_size>
	bool Array<T, t_size>::contains(const T& p_element) const {

		for (int i = 0; i < t_size; i++) {

			if (m_data[i] == p_element) {

				return true;
			}
		}

		return false;
	}

	template <typename T, unsigned int t_size>
	T* Array<T, t_size>::data() {

		return m_data;
	}

	template <typename T, unsigned int t_size>
	const T* Array<T, t_size>::data() const {

		return m_data;
	}

	template <typename T, unsigned int t_size>
	int Array<T, t_size>::size() const {

		return t_size;
	}

	template <typename T, unsigned int t_size>
	Iterator<T> Array<T, t_size>::begin() {

		return Iterator<T>(m_data);
	}

	template <typename T, unsigned int t_size>
	Iterator<T> Array<T, t_size>::end() {

		return Iterator<T>(m_data + t_size);
	}

	template <typename T, unsigned int t_size>
	ConstIterator<T> Array<T, t_size>::begin() const {

		return ConstIterator<T>(m_data);
	}

	template <typename T, unsigned int t_size>
	ConstIterator<T> Array<T, t_size>::end() const {

		return ConstIterator<T>(m_data + t_size);
	}

	template <typename T, unsigned int t_size>
	int Array<T, t_size>::mapIndex(int index) const {

		if (index < 0) {

			index = t_size + index;
		}

		return index;
	}
}