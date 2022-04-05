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
	}

	template<typename T>
	QueueList<T>::~QueueList()
	{
	}

	template <typename T>
	typename QueueList<T>::Iterator& QueueList<T>::Iterator::operator++()
	{
		// TODO: Complete the definition of this operator.
	}

	template <typename T>
	T QueueList<T>::Iterator::operator*() const
	{
		// TODO: Complete the definition of this operator.
	}

	template <typename T>
	bool QueueList<T>::isEmpty() const
	{
		// Check if the current node is null 
		// return true is null
		// else return false
		
	}

	template <typename T>
	void QueueList<T>::enqueue(T element)
	{
		// check if the list is not empty
		// set the elements next to the front
		// set the front to the element

		// if it is empty set the front to element
	}
	
	template <typename T>
	T QueueList<T>::getFront() const
	{
		// return front
	}

	template <typename T>
	void QueueList<T>::dequeue()
	{
		// Check if the fronts next is not null
		// if not null create a temp of the front 
		// set the front next to front 
		// delete the temp
		// else delete the front
	}

	template <typename T>
	void QueueList<T>::removeAll()
	{
		// loop while the list is not empty
		// de the same ads dequeue
	}

	template <typename T>
	bool QueueList<T>::contains(T element) const
	{
		return false;
	}

	template <typename T>
	void QueueList<T>::remove(T element)
	{
		
	}

}}  // namespace fullsail_ai::fundamentals

#endif  // _FULLSAIL_AI_FUNDAMENTALS_QUEUELIST_TODO_H_

