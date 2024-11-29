#pragma once
#include <AcidLib/Exception/EmptyStackException.hpp>

namespace ac {

	template <typename T>
	class Stack {
	public:

		Stack();

		Stack(const Stack& other);

		Stack(Stack&& other) noexcept;

		~Stack();

		Stack& operator=(const Stack& other);

		Stack& operator=(Stack&& other) noexcept;

		void push(const T& p_element);

		T& pop();

		T& peek();

		const T& peek() const;

		void clear();

		int size() const;

		bool isEmpty() const;

	private:

		int m_size;
		int m_capacity;

		T* m_base;
	};

	template <typename T>
	Stack<T>::Stack() {

		m_size = 0;
		m_capacity = 0;

		m_base = nullptr;
	}

	template <typename T>
	Stack<T>::Stack(const Stack& other) {

		m_size = other.m_size;
		m_capacity = other.m_capacity;
		m_base = new T[m_capacity];

		for (int i = 0; i < m_size; i++) {

			m_base[i] = other.m_base[i];
		}
	}

	template <typename T>
	Stack<T>::Stack(Stack&& other) noexcept {

		m_size = other.m_size;
		m_capacity = other.m_capacity;
		m_base = other.m_base;

		other.m_size = 0;
		other.m_capacity = 0;
		other.m_base = nullptr;
	}

	template <typename T>
	Stack<T>::~Stack() {
		
		delete[] m_base;
	}

	template <typename T>
	Stack<T>& Stack<T>::operator=(const Stack& other) {

		delete[] m_base;

		m_size = other.m_size;
		m_capacity = other.m_capacity;
		m_base = new T[m_capacity];

		for (int i = 0; i < m_size; i++) {

			m_base[i] = other.m_base[i];
		}

		return *this;
	}

	template <typename T>
	Stack<T>& Stack<T>::operator=(Stack&& other) noexcept {

		m_size = other.m_size;
		m_capacity = other.m_capacity;
		m_base = other.m_base;

		other.m_size = 0;
		other.m_capacity = 0;
		other.m_base = nullptr;
	}

	template <typename T>
	void Stack<T>::push(const T& p_element) {

		if (m_capacity == 0) {

			m_capacity = 1;

			m_base = new T[m_capacity];
		}
		else if (m_size == m_capacity) {

			m_capacity = m_capacity * 2;

			T* tmp = new T[m_capacity];

			for (int i = 0; i < m_size; i++) {

				tmp[i] = m_base[i];
			}

			delete[] m_base;

			m_base = tmp;
		}

		m_base[m_size] = p_element;
		m_size++;
	}

	template <typename T>
	T& Stack<T>::pop() {

		if (m_size == 0) {

			throw EmptyStackException("Can't pop from empty stack.");
		}

		m_size--;
		return m_base[m_size];
	}

	template <typename T>
	T& Stack<T>::peek() {

		if (m_size == 0) {

			throw EmptyStackException("Can't peek on empty stack!");
		}

		return m_base[m_size - 1];
	}

	template <typename T>
	const T& Stack<T>::peek() const {

		if (m_size == 0) {

			throw EmptyStackException("Can't peek on empty stack!");
		}

		return m_base[m_size - 1];
	}

	template <typename T>
	void Stack<T>::clear() {

		m_size = 0;
	}

	template <typename T>
	int Stack<T>::size() const {

		return m_size;
	}

	template <typename T>
	bool Stack<T>::isEmpty() const {

		return m_size == 0;
	}
}