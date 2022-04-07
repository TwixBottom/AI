//! \file QueueList_TODO.h
//! \brief Defines the <code>fullsail_ai::data_structures::QueueList</code> class template
//! implementation.
//! \author Cromwell D. Enage
#ifndef _FULLSAIL_AI_FUNDAMENTALS_QUEUELIST_TODO_H_
#define _FULLSAIL_AI_FUNDAMENTALS_QUEUELIST_TODO_H_

namespace fullsail_ai { namespace fundamentals {

	//! \TODO
	//!   - Complete the definition of the <code>QueueList::Iterator</code> pre-increment operator.
	//!   - Complete the definition of the <code>QueueList::Iterator</code> dereference operator.
	//!   - Define the <code>QueueList</code> constructor.
	//!   - Define the <code>QueueList</code> destructor.
	//!   - Define the <code>QueueList</code> methods.

	template<typename T>
	QueueList<T>::QueueList()
	{
		front = back = nullptr;
	}

	template<typename T>
	QueueList<T>::~QueueList()
	{
		removeAll();
	}

	template <typename T>
	typename QueueList<T>::Iterator& QueueList<T>::Iterator::operator++()
	{
		// TODO: Complete the definition of this operator.
		this->currentNode = this->currentNode->next;
		return *this;
	}

	template <typename T>
	T QueueList<T>::Iterator::operator*() const
	{
		// TODO: Complete the definition of this operator.
		return this->currentNode->data;
	}

	template <typename T>
	bool QueueList<T>::isEmpty() const
	{
		if (front == nullptr)
		{
			return true;
		}
		return false;		
	}

	template <typename T>
	void QueueList<T>::enqueue(T element)
	{
		Node* node = new QueueList<T>::Node(element);

		if (isEmpty())
		{
			front = node;
		}
		else
		{
			back->next = node;
		}
		back = node;
	}
	
	template <typename T>
	T QueueList<T>::getFront() const
	{
		return front->data;
	}

	template <typename T>
	void QueueList<T>::dequeue()
	{
		remove(front->data);
	}

	template <typename T>
	void QueueList<T>::removeAll()
	{
		while (!isEmpty())
		{
			remove(front->data);
		}

		front = back = nullptr;
	}

	template <typename T>
	bool QueueList<T>::contains(T element) const
	{
		Node* temp = front;

		while (temp != nullptr)
		{
			if (temp->data == element)
			{
				return true;
			}

			temp = temp->next;
		}
		return false;
	}

	template <typename T>
	void QueueList<T>::remove(T element)
	{
		Node* temp = front;

		if (front->data == element)
		{
			front = temp->next;
			delete temp;
			return;
		}

		while (temp != nullptr)
		{
			if (temp->next == nullptr)
			{
				return;
			}
			else if (temp->next->data == element)
			{
				Node* del = temp->next;
				temp->next = del->next;
				delete del;
				return;
			}

			temp = temp->next;
		}
	}

}}  // namespace fullsail_ai::fundamentals

#endif  // _FULLSAIL_AI_FUNDAMENTALS_QUEUELIST_TODO_H_

