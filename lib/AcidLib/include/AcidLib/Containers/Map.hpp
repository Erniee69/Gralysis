#pragma once
#include <AcidLib/Utilities/Iterator.hpp>
#include <AcidLib/Utilities/ConstIterator.hpp>
#include <AcidLib/Exception/KeyNotFoundException.hpp>
#include <AcidLib/Exception/KeyAlreadyExistsException.hpp>
#include <AcidLib/Containers/ArrayList.hpp>

using namespace ac;

template <typename K, typename V>
class KeyValuePair {
public:

	K key;
	V value;

	KeyValuePair();

	KeyValuePair(K p_key, V p_value);
};

template <typename K, typename V>
class Map {
public:

	Map();

	Map(const Map& other);

	Map(Map&& other) noexcept;

	~Map();

	Map& operator=(const Map& other);

	Map& operator=(Map&& other) noexcept;

	V& operator[](const K& key);

	const V& operator[](const K& key) const;

	bool operator==(const Map& other) const;

	bool operator!=(const Map& other) const;

	void append(const K& key, const V& value);

	void remove(const K& key);

	int size() const;

	int capacity() const;

	bool has(const K& key) const;

	bool contains(const V& value) const;

	ArrayList<K> keys() const;

	ArrayList<V> values() const;

	Iterator<KeyValuePair<K, V>> begin();

	Iterator<KeyValuePair<K, V>> end();

	ConstIterator<KeyValuePair<K, V>> begin() const;

	ConstIterator<KeyValuePair<K, V>> end() const;

private:

	int m_size;
	int m_capacity;

	KeyValuePair<K, V>* m_data;
};

template <typename K, typename V>
KeyValuePair<K, V>::KeyValuePair() {}

template <typename K, typename V>
KeyValuePair<K, V>::KeyValuePair(K p_key, V p_value) {

	key = p_key;
	value = p_value;
}

template <typename K, typename V>
Map<K, V>::Map() {

	m_size = 0;
	m_capacity = 0;

	m_data = nullptr;
}

template <typename K, typename V>
Map<K, V>::Map(const Map& other) {

	m_size = other.m_size;
	m_capacity = other.m_capacity;

	m_data = new KeyValuePair<K, V>[m_capacity];

	for (int i = 0; i < m_size; i++) {

		m_data[i] = other.m_data[i];
	}
}

template <typename K, typename V>
Map<K, V>::Map(Map&& other) noexcept {

	m_size = other.m_size;
	m_capacity = other.m_capacity;
	m_data = other.m_data;

	other.m_size = 0;
	other.m_capacity = 0;
	other.m_data = nullptr;
}

template <typename K, typename V>
Map<K, V>::~Map() {

	delete[] m_data;
}

template <typename K, typename V>
Map<K, V>& Map<K, V>::operator=(const Map<K, V>& other) {

	delete[] m_data;

	m_size = other.m_size;
	m_capacity = other.m_capacity;

	m_data = new KeyValuePair<K, V>[m_capacity];

	for (int i = 0; i < m_size; i++) {

		m_data[i] = other.m_data[i];
	}

	return *this;
}

template <typename K, typename V>
Map<K, V>& Map<K, V>::operator=(Map<K, V>&& other) noexcept {

	delete[] m_data;

	m_size = other.m_size;
	m_capacity = other.m_capacity;
	m_data = other.m_data;

	other.m_size = 0;
	other.m_capacity = 0;
	other.m_data = nullptr;

	return *this;
}

template <typename K, typename V>
V& Map<K, V>::operator[](const K& key) {

	for (int i = 0; i < m_size; i++) {

		if (m_data[i].key == key) {

			return m_data[i].value;
		}
	}

	throw KeyNotFoundException();
}

template <typename K, typename V>
const V& Map<K, V>::operator[](const K& key) const {

	for (int i = 0; i < m_size; i++) {

		if (m_data[i].key == key) {

			return m_data[i].value;
		}
	}

	throw KeyNotFoundException();
}

template <typename K, typename V>
bool Map<K, V>::operator==(const Map& other) const {

	if (m_size != other.m_size) {

		return false;
	}

	for (int i = 0; i < m_size; i++) {

		KeyValuePair<K, V> element = m_data[i];

		try {

			if (other[element.key] != element.value) {

				return false;
			}

		}
		catch (const KeyNotFoundException&) {

			return false;
		}
	}

	return true;
}

template <typename K, typename V>
bool Map<K, V>::operator!=(const Map& other) const {

	return !(*this == other);
}

template <typename K, typename V>
void Map<K, V>::append(const K& key, const V& value) {

	bool keyExists = true;

	try {

		(*this).operator[](key);
	}
	catch (const KeyNotFoundException&) {
		
		keyExists = false;
	}

	if (keyExists) {

		throw KeyAlreadyExistsException();
	}

	if (m_capacity == 0) {

		m_capacity = 1;

		m_data = new KeyValuePair<K, V>[m_capacity];
	}
	else if (m_size == m_capacity) {

		m_capacity = m_capacity * 2;

		KeyValuePair<K, V>* tmp = new KeyValuePair<K, V>[m_capacity];

		for (int i = 0; i < m_size; i++) {

			tmp[i] = m_data[i];
		}

		delete[] m_data;

		m_data = tmp;
	}

	m_data[m_size] = KeyValuePair(key, value);
	m_size++;
}

template <typename K, typename V>
void Map<K, V>::remove(const K& key) {

	int index = -1;

	for (int i = 0; i < m_size; i++) {

		if (m_data[i].key == key) {

			index = i;
			break;
		}
	}

	if (index == -1) {

		throw KeyNotFoundException();
	}

	m_size--;
	m_data[index] = m_data[m_size];
}

template <typename K, typename V>
int Map<K, V>::size() const {

	return m_size;
}

template <typename K, typename V>
int Map<K, V>::capacity() const {

	return m_capacity;
}

template <typename K, typename V>
bool Map<K, V>::has(const K& key) const {

	for (int i = 0; i < m_size; i++) {

		if (m_data[i].key == key) {

			return true;
		}
	}

	return false;
}

template <typename K, typename V>
bool Map<K, V>::contains(const V& value) const {

	for (int i = 0; i < m_size; i++) {

		if (m_data[i].value == value) {

			return true;
		}
	}

	return false;
}

template <typename K, typename V>
ArrayList<K> Map<K, V>::keys() const {

	ArrayList<K> result;

	for (KeyValuePair<K, V> kv : *this) {

		result.append(kv.key);
	}

	return result;
}

template <typename K, typename V>
ArrayList<V> Map<K, V>::values() const {

	ArrayList<V> result;

	for (KeyValuePair<K, V> kv : *this) {

		result.append(kv.value);
	}

	return result;
}

template <typename K, typename V>
Iterator<KeyValuePair<K, V>> Map<K, V>::begin() {

	return Iterator<KeyValuePair<K, V>>(m_data);
}

template <typename K, typename V>
Iterator<KeyValuePair<K, V>> Map<K, V>::end() {

	return Iterator<KeyValuePair<K, V>>(m_data + m_size);
}

template <typename K, typename V>
ConstIterator<KeyValuePair<K, V>> Map<K, V>::begin() const {

	return ConstIterator<KeyValuePair<K, V>>(m_data);
}

template <typename K, typename V>
ConstIterator<KeyValuePair<K, V>> Map<K, V>::end() const {

	return ConstIterator<KeyValuePair<K, V>>(m_data + m_size);
}