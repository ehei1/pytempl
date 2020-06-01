#pragma once

#include <tuple>

#include "common\_container_adaptor.h"

/*
https://docs.python.org/3/library/functions.html#enumerate
*/
namespace pytempl {
	template<typename ITER, typename START>
	class Enumerate_iterator
	{
		START m_index{ -1 };
		ITER m_iterator;

		using value_type = std::tuple<int, T::reference>;

	public:
		explicit Enumerate_iterator(ITER&& iter, START index) : m_iterator{ iter }, m_index{ index - 1 }
		{}

		explicit Enumerate_iterator(ITER&& iter) : m_iterator{ iter }
		{}

		value_type operator*()
		{
			return { ++m_index, *m_iterator };
		}

		void operator++()
		{
			++m_iterator;
		}

		bool operator==(Enumerate_iterator<ITER, START>& iter)
		{
			return iter.m_iterator == m_iterator;
		}

		bool operator!=(Enumerate_iterator<ITER, START>& iter)
		{
			return !operator==(iter);
		}
	};


	template<typename T, typename START>
	class _Enumerate : _Container_adaptor<T>
	{
		T& m_container;
		const START m_start{};

		using iterator_type = typename _Container_adaptor<T>::iterator_type;

	public:
		explicit _Enumerate(T&& t, START start) : m_container{ t }, m_start{ start }
		{}

		iterator_type begin()
		{
			auto iterator = _Container_adaptor<T>::begin(m_container);

			return Enumerate_iterator<T, START>(iterator, m_start);
		}

		iterator_type end()
		{
			auto iterator = _Container_adaptor<T>::end(m_container);

			return Enumerate_iterator<T, START>(iterator);
		}
	};

	template<typename T, typename START>
	_Enumerate<T, START> enumerate(T&& t, START start)
	{
		return {t, start};
	}
}