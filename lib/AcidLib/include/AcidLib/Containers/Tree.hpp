#pragma once
#include <AcidLib/Containers/ArrayList.hpp>
#include <AcidLib/Containers/Stack.hpp>
#include <AcidLib/Exception/NoParentException.hpp>

namespace ac {

	template <typename T>
	class TreeNode;

	template <typename T>
	class TreeIterator {
	public:

		TreeIterator(TreeNode<T>* p_node);
		
		TreeIterator& operator++();

		TreeIterator operator++(int);

		bool operator==(const TreeIterator& other) const;

		bool operator!=(const TreeIterator& other) const;

		TreeNode<T>& operator*();

	private:

		TreeNode<T>* m_current;

		Stack<TreeNode<T>*> m_stack;
	};

	template <typename T>
	class ConstTreeIterator {
	public:

		ConstTreeIterator(TreeNode<T>* p_node);

		ConstTreeIterator& operator++();

		ConstTreeIterator operator++(int);

		bool operator==(const ConstTreeIterator& other) const;

		bool operator!=(const ConstTreeIterator& other) const;

		const TreeNode<T>& operator*();

	private:

		TreeNode<T>* m_current;

		Stack<int> m_stack;
	};

	template <typename T>
	class TreeNode {
	public:

		TreeNode();

		TreeNode(const T& p_element);

		TreeNode(const TreeNode& other);

		TreeNode(TreeNode&& other) noexcept;

		~TreeNode();

		TreeNode& operator=(const TreeNode& other);

		TreeNode& operator=(TreeNode&& other) noexcept;

		TreeNode& operator=(const T& p_element);

		TreeNode& operator[](int index);

		const TreeNode& operator[](int index) const;

		operator T& ();

		operator const T& () const;

		ArrayList<TreeNode*>& children();

		const ArrayList<TreeNode*>& children() const;

		TreeNode& parent();

		const TreeNode& parent() const;

		TreeNode* child(int index);

		const TreeNode* child(int index) const;

		void appendChild(TreeNode& p_node);

		void appendChild(T p_element);

		void insertChild(TreeNode& p_node, int index);

		void insertChild(T p_element, int index);

		void removeChild(int index);

		void clearChildren();

		bool isLeaf() const;

		bool isRoot() const;

		int childCount() const;

		TreeIterator<T> begin();

		ConstTreeIterator<T> begin() const;

		TreeIterator<T> end();

		ConstTreeIterator<T> end() const;

	private:

		TreeNode* m_parent;

		T m_element;

		ArrayList<TreeNode*> m_children;

		TreeNode* copySubtree();
	};

	template <typename T>
	using Tree = TreeNode<T>;

	template <typename T>
	TreeIterator<T>::TreeIterator(TreeNode<T>* p_node) {

		m_current = p_node;

		if (m_current != nullptr) {

			for (int i = m_current->childCount() - 1; i >= 0; i--) {

				m_stack.push(m_current->child(i));
			}
		}
	}

	template <typename T>
	TreeIterator<T>& TreeIterator<T>::operator++() {

		if (m_stack.isEmpty()) {

			m_current = nullptr;
		}
		else {

			m_current = m_stack.pop();

			for (int i = m_current->childCount() - 1; i >= 0; i--) {

				m_stack.push(m_current->child(i));
			}
		}

		return *this;
	}

	template <typename T>
	TreeIterator<T> TreeIterator<T>::operator++(int) {

		TreeIterator result = *this;

		++(*this);

		return result;
	}

	template <typename T>
	bool TreeIterator<T>::operator==(const TreeIterator& other) const {

		return (*this).m_current == other.m_current;
	}

	template <typename T>
	bool TreeIterator<T>::operator!=(const TreeIterator& other) const {

		return (*this).m_current != other.m_current;
	}

	template <typename T>
	TreeNode<T>& TreeIterator<T>::operator*() {

		return *m_current;
	}

	template <typename T>
	ConstTreeIterator<T>::ConstTreeIterator(TreeNode<T>* p_node) {

		m_current = p_node;

		if (m_current != nullptr) {

			for (int i = m_current->childCount(); i >= 0; i--) {

				m_stack.push(m_current->child(i));
			}
		}
	}

	template <typename T>
	ConstTreeIterator<T>& ConstTreeIterator<T>::operator++() {

		if (m_stack.isEmpty()) {

			m_current = nullptr;
		}
		else {

			m_current = m_stack.pop();

			for (int i = m_current->childCount(); i >= 0; i--) {

				m_stack.push(m_current->child(i));
			}
		}
	}

	template <typename T>
	ConstTreeIterator<T> ConstTreeIterator<T>::operator++(int) {

		ConstTreeIterator result = *this;

		++(*this);

		return result;
	}

	template <typename T>
	bool ConstTreeIterator<T>::operator==(const ConstTreeIterator& other) const {

		return (*this).m_current == other.m_current;
	}

	template <typename T>
	bool ConstTreeIterator<T>::operator!=(const ConstTreeIterator& other) const {

		return (*this).m_current != other.m_current;
	}

	template <typename T>
	const TreeNode<T>& ConstTreeIterator<T>::operator*() {

		return *m_current;
	}

	template <typename T>
	TreeNode<T>::TreeNode() {

		m_parent = nullptr;
	}

	template <typename T>
	TreeNode<T>::TreeNode(const T& p_element) {

		m_parent = nullptr;
		m_element = p_element;
	}

	template <typename T>
	TreeNode<T>::TreeNode(const TreeNode& other) {

		(*this) = other;
	}

	template <typename T>
	TreeNode<T>::TreeNode(TreeNode&& other) noexcept {

		m_children = other.m_children;
		m_element = other.m_element;
		m_parent = nullptr;

		for (TreeNode* child : m_children) {

			child->m_parent = this;
		}
	}

	template <typename T>
	TreeNode<T>::~TreeNode() {

		for (TreeNode* child : m_children) {

			delete child;
		}
	}

	template <typename T>
	TreeNode<T>& TreeNode<T>::operator=(const TreeNode& other) {

		m_element = other.m_element;
		m_parent = nullptr;

		for (TreeNode* child : m_children) {

			delete child;
		}

		for (TreeNode* child : other.m_children) {

			m_children.append(child->copySubtree());
		}

		return *this;
	}

	template <typename T>
	TreeNode<T>& TreeNode<T>::operator=(TreeNode&& other) noexcept {

		for (TreeNode* child : m_children) {

			delete child;
		}

		m_element = other.m_element;
		m_parent = nullptr;
		m_children = other.m_children;

		return *this;
	}

	template <typename T>
	TreeNode<T>& TreeNode<T>::operator=(const T& p_element) {

		m_element = p_element;
	}

	template <typename T>
	TreeNode<T>& TreeNode<T>::operator[](int index) {

		return *(m_children[index]);
	}

	template <typename T>
	const TreeNode<T>& TreeNode<T>::operator[](int index) const {

		return *(m_children[index]);
	}

	template <typename T>
	TreeNode<T>::operator T& () {

		return m_element;
	}

	template <typename T>
	TreeNode<T>::operator const T& () const {

		return m_element;
	}

	template <typename T>
	ArrayList<TreeNode<T>*>& TreeNode<T>::children() {

		return m_children;
	}

	template <typename T>
	const ArrayList<TreeNode<T>*>& TreeNode<T>::children() const {

		return m_children;
	}

	template <typename T>
	TreeNode<T>& TreeNode<T>::parent() {

		if (m_parent == nullptr) {

			throw NoParentException();
		}

		return *m_parent;
	}

	template <typename T>
	const TreeNode<T>& TreeNode<T>::parent() const {

		if (m_parent == nullptr) {

			throw NoParentException();
		}

		return *m_parent;
	}

	template <typename T>
	TreeNode<T>* TreeNode<T>::child(int index) {

		return m_children[index];
	}

	template <typename T>
	const TreeNode<T>* TreeNode<T>::child(int index) const {

		return m_children[index];
	}

	template <typename T>
	void TreeNode<T>::appendChild(TreeNode& p_node) {

		m_children.append(&p_node);
	}

	template <typename T>
	void TreeNode<T>::appendChild(T p_element) {

		TreeNode* node = new TreeNode(p_element);

		m_children.append(node);
	}

	template <typename T>
	void TreeNode<T>::insertChild(TreeNode& p_node, int index) {

		m_children.insert(&p_node, index);
	}

	template <typename T>
	void TreeNode<T>::insertChild(T p_element, int index) {

		TreeNode* node = new TreeNode(p_element);

		m_children.insert(node, index);
	}

	template <typename T>
	void TreeNode<T>::removeChild(int index) {

		delete m_children[index];

		m_children.remove(index);
	}

	template <typename T>
	void TreeNode<T>::clearChildren() {

		for (TreeNode* child : m_children) {

			delete child;
		}

		m_children.clear();
	}

	template <typename T>
	bool TreeNode<T>::isLeaf() const {

		return m_children.size() == 0;
	}

	template <typename T>
	bool TreeNode<T>::isRoot() const {

		return m_parent != nullptr;
	}

	template <typename T>
	int TreeNode<T>::childCount() const {

		return m_children.size();
	}

	template <typename T>
	TreeIterator<T> TreeNode<T>::begin() {

		return TreeIterator<T>(this);
	}

	template <typename T>
	ConstTreeIterator<T> TreeNode<T>::begin() const {

		return ConstTreeIterator<T>(this);
	}

	template <typename T>
	TreeIterator<T> TreeNode<T>::end() {

		return TreeIterator<T>(nullptr);
	}

	template <typename T>
	ConstTreeIterator<T> TreeNode<T>::end() const {

		return ConstTreeIterator<T>(nullptr);
	}

	template <typename T>
	TreeNode<T>* TreeNode<T>::copySubtree() {

		TreeNode* result = new TreeNode(m_element);

		for (TreeNode* child : m_children) {

			result->appendChild(child->copySubtree());
		}

		return result;
	}
}