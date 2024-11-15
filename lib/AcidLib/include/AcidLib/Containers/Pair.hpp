#pragma once

template <typename T1, typename T2>
class Pair {
public:

	T1 first;
	T2 second;

	Pair();

	Pair(T1 p_first, T2 p_second);
};

template <typename T1, typename T2>
Pair<T1, T2>::Pair() {}

template <typename T1, typename T2>
Pair<T1, T2>::Pair(T1 p_first, T2 p_second) {

	first = p_first;
	second = p_second;
}