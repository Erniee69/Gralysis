#pragma once
#include <AcidLib/Math/Math.hpp>
#include <AcidLib/Exception/IndexOutOfBoundsException.hpp>

namespace ac {

	class String {
	public:

		String();

		String(const char* p_data);

		String(char p_data);

		String(const String& other);

		String(String&& other) noexcept;

		~String();

		String& operator=(const String& other);

		String& operator=(String&& other) noexcept;

		char& operator[](int index);

		const char& operator[](int index) const;

		bool operator==(const String& other) const;

		bool operator!=(const String& other) const;

		bool operator<(const String& other) const;

		bool operator>(const String& other) const;

		bool operator<=(const String& other) const;

		bool operator>=(const String& other) const;

		String operator+(const String& other) const;

		String& operator+=(const String& other);

		void append(const char& element);

		void insert(const char& element, int index);

		void remove(int index);

		void clear();

		void resize(int p_size);

		void reserve(int p_capacity);

		int charCount() const;

		int size() const;

		int capacity() const;

		char* data();

		const char* data() const;

		const char* cstr() const;

		bool isEmpty() const;

	private:

		int mapIndex(int index) const;

		int m_size;
		int m_capacity;
		char* m_data;
	};

	String::String() {

		m_size = 0;
		m_capacity = 1;
		m_data = new char[m_capacity];

		m_data[0] = '\0';
	}

	String::String(char p_data) {

		m_size = 1;
		m_capacity = 2;
		m_data = new char[m_capacity];

		m_data[0] = p_data;
		m_data[1] = '\0';
	}

	String::String(const char* p_data) {

		m_size = 0;
		m_capacity = 1;
		m_data = new char[m_capacity];

		m_data[0] = '\0';

		int i = 0;

		while (p_data[i] != '\0') {

			append(p_data[i]);
			i++;
		}
	}

	String::String(const String& other) {

		m_size = other.m_size;
		m_capacity = other.m_capacity;
		m_data = new char[m_capacity];

		for (int i = 0; i < m_size; i++) {

			m_data[i] = other.m_data[i];
		}

		m_data[m_size] = '\0';
	}

	String::String(String&& other) noexcept {

		m_size = other.m_size;
		m_capacity = other.m_capacity;
		m_data = other.m_data;

		other.m_size = 0;
		other.m_capacity = 0;
		other.m_data = nullptr;
	}

	String::~String() {

		delete[] m_data;
	}

	String& String::operator=(const String& other) {

		delete[] m_data;

		m_size = other.m_size;
		m_capacity = other.m_capacity;
		m_data = new char[m_capacity];

		for (int i = 0; i < m_size; i++) {

			m_data[i] = other.m_data[i];
		}

		m_data[m_size] = '\0';

		return *this;
	}

	String& String::operator=(String&& other) noexcept {

		delete[] m_data;

		m_size = other.m_size;
		m_capacity = other.m_capacity;
		m_data = other.m_data;

		other.m_size = 0;
		other.m_capacity = 0;
		other.m_data = nullptr;

		return *this;
	}

	char& String::operator[](int index) {

		index = mapIndex(index);

		if (index < 0 || index >= m_size) {

			throw IndexOutOfBoundsException(index, -m_size, m_size - 1);
		}

		return m_data[index];
	}

	const char& String::operator[](int index) const {

		index = mapIndex(index);

		if (index < 0 || index >= m_size) {

			throw IndexOutOfBoundsException(index, -m_size, m_size - 1);
		}

		return m_data[index];
	}

	bool String::operator==(const String& other) const {

		bool result = m_size == other.m_size;

		if (result) {

			for (int i = 0; i < m_size; i++) {

				result = result && (m_data[i] == other.m_data[i]);
			}
		}

		return result;
	}

	bool String::operator!=(const String& other) const {

		return !(*this == other);
	}

	bool String::operator<(const String& other) const {

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

	bool String::operator>(const String& other) const {

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

	bool String::operator<=(const String& other) const {

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

	bool String::operator>=(const String& other) const {

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

	String String::operator+(const String& other) const {

		String result;

		result.resize(m_size + other.m_size);

		for (int i = 0; i < m_size; i++) {

			result.m_data[i] = m_data[i];
		}

		for (int i = m_size; i < other.m_size; i++) {

			result[m_size + i] = m_data[i];
		}

		return result;
	}

	String& String::operator+=(const String& other) {

		int oldSize = m_size;

		resize(m_size + other.m_size);

		for (int i = oldSize; i < m_size; i++) {

			m_data[i] = other.m_data[i - oldSize];
		}

		return *this;
	}

	void String::append(const char& element) {

		if (m_size == m_capacity - 1) {

			m_capacity = 2 * m_capacity;

			char* tmp = new char[m_capacity];

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

	void String::insert(const char& element, int index) {

		index = mapIndex(index);

		if (index < 0 || index >= m_size) {

			throw IndexOutOfBoundsException(index, -m_size, m_size - 1);
		}

		if (m_size == m_capacity - 1) {

			m_capacity = 2 * m_capacity;

			char* tmp = new char[m_capacity];

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

	void String::remove(int index) {

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

	void String::clear() {

		m_size = 0;
		m_data[0] = '\0';
	}

	void String::resize(int p_size) {

		if (m_capacity - 1 < p_size) {

			m_capacity = p_size + 1;

			char* tmp = new char[m_capacity];

			for (int i = 0; i < m_size; i++) {

				tmp[i] = m_data[i];
			}

			delete[] m_data;

			m_data = tmp;
		}

		m_size = p_size;
		m_data[m_size] = '\0';
	}

	void String::reserve(int p_capacity) {

		m_size = min(m_size, p_capacity);
		m_capacity = p_capacity + 1;

		char* tmp = new char[m_capacity];

		for (int i = 0; i < m_size; i++) {

			tmp[i] = m_data[i];
		}

		delete[] m_data;

		m_data = tmp;
	}

	int String::size() const {

		return m_size;
	}

	int String::capacity() const {

		return m_capacity - 1;
	}

	char* String::data() {

		return m_data;
	}

	const char* String::data() const {

		return m_data;
	}

	const char* String::cstr() const {

		return m_data;
	}

	bool String::isEmpty() const {

		return m_size == 0;
	}

	int String::mapIndex(int index) const {

		if (index < 0) {

			index = m_size + index;
		}

		return index;
	}
}