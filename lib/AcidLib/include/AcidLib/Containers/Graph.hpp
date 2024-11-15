#pragma once
#include <AcidLib/Containers/ArrayList.hpp>
#include <AcidLib/Exception/GraphException.hpp>

namespace ac {

	template <typename T>
	class Graph {
	public:

		void addNode(T p_element);

		void removeNode(T p_node);

		void clearNodes();

		ArrayList<T> getNeighbors(T p_node);

		void connect(T begin, T end);

		void disconnect(T begin, T end);

		ArrayList<T>& elements();

		ArrayList<ArrayList<int>>& adjecencies();

	private:

		ArrayList<T> m_elements;

		ArrayList<ArrayList<int>> m_adjacencies;
	};

	template <typename T>
	void Graph<T>::addNode(T p_element) {

		for (T& element : m_elements) {

			if (element == p_element) {

				throw GraphException("Node already exists!");
			}
		}

		m_elements.append(p_element);
		m_adjacencies.append(ArrayList<int>());
	}

	template <typename T>
	void Graph<T>::removeNode(T p_node) {

		for (int i = 0; i < m_elements.size(); i++) {

			if (m_elements[i] == p_node) {

				m_elements.remove(i);
				m_adjacencies.remove(i);

				for (int j = 0; j < m_adjacencies.size(); j++) {

					for (int k = 0; k < m_adjacencies[j].size(); k++) {

						if (m_adjacencies[j][k] == i) {

							m_adjacencies[j].remove(k);
						}
						else if (m_adjacencies[j][k] > i) {

							m_adjacencies[j][k] -= 1;
						}
					}
				}

				return;
			}
		}

		throw GraphException("Node not found!");
	}

	template <typename T>
	void Graph<T>::clearNodes() {

		m_elements.clear();
		m_adjacencies.clear();
	}

	template <typename T>
	ArrayList<T> Graph<T>::getNeighbors(T p_node) {

		ArrayList<T> result;

		int nodeIndex = -1;

		for (int i = 0; i < m_elements.size(); i++) {

			if (m_elements[i] == p_node) {

				nodeIndex = i;
				break;
			}
		}

		if (nodeIndex == -1) {

			throw GraphException("Node not found!");
		}

		for (int adj : m_adjacencies[nodeIndex]) {

			result.append(m_elements[adj]);
		}

		return result;
	}

	template <typename T>
	void Graph<T>::connect(T begin, T end) {

		if (begin == end) {

			throw GraphException("Can't connect a node to itself!");
		}

		int second = -1;

		for (int i = 0; i < m_elements.size(); i++) {

			if (m_elements[i] == end) {

				second = i;
				break;
			}
		}

		if (second == -1) {

			throw GraphException("Node not found!");
		}

		for (int i = 0; i < m_elements.size(); i++) {

			if (m_elements[i] == begin) {

				if (m_adjacencies[i].contains(second)) {

					return;
				}
				else {

					m_adjacencies[i].append(second);
					return;
				}
			}
		}

		throw GraphException("Node not found!");
	}

	template <typename T>
	void Graph<T>::disconnect(T begin, T end) {

		int first = -1;
		int second = -1;

		for (int i = 0; i < m_elements.size(); i++) {

			if (m_elements[i] == begin) {

				first = i;
			}

			if (m_elements[i] == end) {

				second = i;
			}
		}

		if (first == -1 || second == -1) {

			throw GraphException("Node not found!");
		}

		if (first == second) {

			return;
		}

		for (int i = 0; i < m_adjacencies[first]; i++) {

			if (m_adjacencies[first][i] == second) {

				m_adjacencies[first].remove(i);
			}
		}
	}

	template <typename T>
	ArrayList<T>& Graph<T>::elements() {

		return m_elements;
	}

	template <typename T>
	ArrayList<ArrayList<int>>& Graph<T>::adjecencies() {

		return m_adjacencies;
	}
}