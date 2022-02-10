/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvan-aud <rvan-aud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 13:37:06 by rvan-aud          #+#    #+#             */
/*   Updated: 2022/02/10 14:28:09 by rvan-aud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <memory>

#include "utils.hpp"

namespace	ft
{
	/********************/
	/*     Iterator     */
	/********************/

	template <class Category, class T, class Distance = ptrdiff_t,
				class Pointer = T*, class Reference = T&>
	struct iterator
	{
		typedef T			value_type;
		typedef Distance	difference_type;
		typedef Pointer		pointer;
		typedef Reference	reference;
		typedef Category	iterator_category;
	};

	template <class T>
	class	random_access_iterator
	{
		private :

			T	*_pointer;

		public:

			typedef typename ft::iterator<random_access_iterator, T>::iterator_category	iterator_category;
			typedef typename ft::iterator<random_access_iterator, T>::value_type		value_type;
			typedef typename ft::iterator<random_access_iterator, T>::difference_type	difference_type;
			typedef typename ft::iterator<random_access_iterator, T>::pointer			pointer;
			typedef typename ft::iterator<random_access_iterator, T>::reference			reference;

			//Constructors
			random_access_iterator(void) : _pointer(NULL) {};
			random_access_iterator(pointer pointer) : _pointer(pointer) {};
			random_access_iterator(const random_access_iterator<typename remove_const<T>::type>& it) : _pointer(it.base()) {};

			//Destructor
			~random_access_iterator(void) {};

			//Operator=
			random_access_iterator<T> &operator=(const random_access_iterator<typename remove_const<T>::type>& it)
			{
				this->_pointer = it.base();
				return (*this);
			}

			//Member functions
			pointer base() const {return this->_pointer;};

			reference operator*() const {return *this->_pointer;};

			random_access_iterator& operator++()
			{
				this->_pointer++;
				return (*this);
			};
			random_access_iterator operator++(int)
			{
				random_access_iterator	tmp = *this;
				this->_pointer++;
				return (tmp);
			};

			random_access_iterator& operator--()
			{
				this->_pointer--;
				return (*this);
			};
			random_access_iterator operator--(int)
			{
				random_access_iterator	tmp = *this;
				this->_pointer--;
				return (tmp);
			};

			bool operator!=(random_access_iterator const rhs) {return (this->_pointer != rhs._pointer);};
			bool operator==(random_access_iterator const rhs) {return (this->_pointer == rhs._pointer);};
			bool operator<(random_access_iterator const rhs) {return (this->_pointer < rhs._pointer);};
			bool operator<=(random_access_iterator const rhs) {return (this->_pointer <= rhs._pointer);};
			bool operator>(random_access_iterator const rhs) {return (this->_pointer > rhs._pointer);};
			bool operator>=(random_access_iterator const rhs) {return (this->_pointer >= rhs._pointer);};

			random_access_iterator	operator+(difference_type n) const {return this->_pointer + n;};
			random_access_iterator	operator-(difference_type n) const {return this->_pointer - n;};

			random_access_iterator& operator+=(difference_type n)
			{
				this->_pointer += n;
				return (*this);
			};
			random_access_iterator& operator-=(difference_type n)
			{
				this->_pointer -= n;
				return (*this);
			};

			pointer operator->() const {return &(operator*());};
			reference operator[](difference_type n) const {return *(operator+(n));};
	};
	
	/********************/
	/* Reverse_iterator */
	/********************/

	template <class Category, class T, class Distance = ptrdiff_t,
				class Pointer = T*, class Reference = T&>
	struct reverse_iterator
	{
		typedef T			value_type;
		typedef Distance	difference_type;
		typedef Pointer		pointer;
		typedef Reference	reference;
		typedef Category	iterator_category;
	};

	template <class T>
	class	reverse_random_access_iterator
	{
		private :

			T	*_pointer;

		public:

			typedef typename ft::reverse_iterator<reverse_random_access_iterator, T>::iterator_category	iterator_category;
			typedef typename ft::reverse_iterator<reverse_random_access_iterator, T>::value_type		value_type;
			typedef typename ft::reverse_iterator<reverse_random_access_iterator, T>::difference_type	difference_type;
			typedef typename ft::reverse_iterator<reverse_random_access_iterator, T>::pointer			pointer;
			typedef typename ft::reverse_iterator<reverse_random_access_iterator, T>::reference			reference;

			//Constructors
			reverse_random_access_iterator(void) : _pointer(NULL) {};
			reverse_random_access_iterator(pointer pointer) : _pointer(pointer) {};
			reverse_random_access_iterator(const reverse_random_access_iterator& it) : _pointer(it._pointer) {};

			//Destructor
			~reverse_random_access_iterator(void) {};

			//Operator=
			reverse_random_access_iterator &operator=(const reverse_random_access_iterator& it)
			{
				if (this == &it)
					return (*this);
				this->_pointer = it._pointer;
				return (*this);
			}

			//Member functions
			pointer base() const {return this->_pointer;};

			reference operator*() const {return *this->_pointer;};

			reverse_random_access_iterator& operator++()
			{
				this->_pointer--;
				return (*this);
			};
			reverse_random_access_iterator operator++(int)
			{
				reverse_random_access_iterator	tmp = *this;
				this->_pointer--;
				return (tmp);
			};

			reverse_random_access_iterator& operator--()
			{
				this->_pointer++;
				return (*this);
			};
			reverse_random_access_iterator operator--(int)
			{
				reverse_random_access_iterator	tmp = *this;
				this->_pointer++;
				return (tmp);
			};

			bool operator!=(reverse_random_access_iterator const rhs) {return (this->_pointer != rhs._pointer);};
			bool operator==(reverse_random_access_iterator const rhs) {return (this->_pointer == rhs._pointer);};
			bool operator<(reverse_random_access_iterator const rhs) {return (this->_pointer > rhs._pointer);};
			bool operator<=(reverse_random_access_iterator const rhs) {return (this->_pointer >= rhs._pointer);};
			bool operator>(reverse_random_access_iterator const rhs) {return (this->_pointer < rhs._pointer);};
			bool operator>=(reverse_random_access_iterator const rhs) {return (this->_pointer <= rhs._pointer);};

			reverse_random_access_iterator	operator+(difference_type n) const {return this->_pointer - n;};
			reverse_random_access_iterator	operator-(difference_type n) const {return this->_pointer + n;};

			reverse_random_access_iterator& operator+=(difference_type n)
			{
				this->_pointer -= n;
				return (*this);
			};
			reverse_random_access_iterator& operator-=(difference_type n)
			{
				this->_pointer += n;
				return (*this);
			};

			pointer operator->() const {return &(operator*());};
			reference operator[](difference_type n) const {return *(operator+(n));};
	};

	//Non-member function overloads
	//(all the template<typename T_L, typename T_R> functions are to compare iterator with const_iterator)

	//Relational operators
	template <class Iterator>
	bool operator== (const ft::random_access_iterator<Iterator>& lhs,
        const ft::random_access_iterator<Iterator>& rhs)
	{
		return (lhs.base() == rhs.base());
	};
	template<typename T_L, typename T_R>
    typename ft::random_access_iterator<T_L>::difference_type
    operator==(const ft::random_access_iterator<T_L> lhs,
              const ft::random_access_iterator<T_R> rhs)
    {
        return (lhs.base() == rhs.base());
    };

	template <class Iterator>
	bool operator!= (const ft::random_access_iterator<Iterator>& lhs,
		const ft::random_access_iterator<Iterator>& rhs)
	{
		return (lhs.base() != rhs.base());
	};
	template<typename T_L, typename T_R>
    typename ft::random_access_iterator<T_L>::difference_type
    operator!=(const ft::random_access_iterator<T_L> lhs,
              const ft::random_access_iterator<T_R> rhs)
    {
        return (lhs.base() != rhs.base());
    };

	template <class Iterator>
	bool operator<  (const ft::random_access_iterator<Iterator>& lhs,
		const ft::random_access_iterator<Iterator>& rhs)
	{
		return (lhs.base() < rhs.base());
	};
	template<typename T_L, typename T_R>
    typename ft::random_access_iterator<T_L>::difference_type
    operator<(const ft::random_access_iterator<T_L> lhs,
              const ft::random_access_iterator<T_R> rhs)
    {
        return (lhs.base() < rhs.base());
    };

	template <class Iterator>
	bool operator<= (const ft::random_access_iterator<Iterator>& lhs,
		const ft::random_access_iterator<Iterator>& rhs)
	{
		return (lhs.base() <= rhs.base());
	};
	template<typename T_L, typename T_R>
    typename ft::random_access_iterator<T_L>::difference_type
    operator<=(const ft::random_access_iterator<T_L> lhs,
              const ft::random_access_iterator<T_R> rhs)
    {
        return (lhs.base() <= rhs.base());
    };

	template <class Iterator>
	bool operator>  (const ft::random_access_iterator<Iterator>& lhs,
		const ft::random_access_iterator<Iterator>& rhs)
	{
		return (lhs.base() > rhs.base());
	};
	template<typename T_L, typename T_R>
    typename ft::random_access_iterator<T_L>::difference_type
    operator>(const ft::random_access_iterator<T_L> lhs,
              const ft::random_access_iterator<T_R> rhs)
    {
        return (lhs.base() > rhs.base());
    };

	template <class Iterator>
	bool operator>= (const ft::random_access_iterator<Iterator>& lhs,
		const ft::random_access_iterator<Iterator>& rhs)
	{
		return (lhs.base() >= rhs.base());
	};
	template<typename T_L, typename T_R>
    typename ft::random_access_iterator<T_L>::difference_type
    operator>=(const ft::random_access_iterator<T_L> lhs,
              const ft::random_access_iterator<T_R> rhs)
    {
        return (lhs.base() >= rhs.base());
    };

	//Operators + and -
	template <class Iterator>
	ft::random_access_iterator<Iterator> operator+ (
		typename ft::random_access_iterator<Iterator>::difference_type n,
		const ft::random_access_iterator<Iterator>& it)
	{
		return (it + n);
	};

	template <class Iterator>
	typename ft::random_access_iterator<Iterator>::difference_type operator- (
		const ft::random_access_iterator<Iterator>& lhs,
		const ft::random_access_iterator<Iterator>& rhs)
	{
		return (lhs.base() - rhs.base());
	};
	template <class Iterator_L, class Iterator_R>
	typename ft::random_access_iterator<Iterator_L>::difference_type operator- (
		const ft::random_access_iterator<Iterator_L>& lhs,
		const ft::random_access_iterator<Iterator_R>& rhs)
	{
		return (lhs.base() - rhs.base());
	};
}
