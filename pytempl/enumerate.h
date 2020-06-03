#pragma once

#include <tuple>

#include "common\_container_adaptor.h"

/*
https://docs.python.org/3/library/functions.html#enumerate
*/
namespace pytempl {
	template<typename ITER, typename START = int>
	class Enumerate_iterator
	{
		START m_index{};
		ITER m_iterator;

		using value_type = std::tuple<int, typename ITER::reference>;

	public:
		explicit Enumerate_iterator(ITER&& iter, START index) : m_iterator{ std::forward<ITER>(iter) }, m_index{ index }
		{}

		explicit Enumerate_iterator(ITER&& iter) : m_iterator{ std::forward<ITER>(iter) }
		{}

		value_type operator*()
		{
			return { m_index++, *m_iterator };
		}

		Enumerate_iterator<ITER, START>& operator++()
		{
			++m_iterator;

			return *this;
		}

		bool operator==(const Enumerate_iterator<ITER, START>& iter) const
		{
			return iter.m_iterator == m_iterator;
		}

		bool operator!=(const Enumerate_iterator<ITER, START>& iter) const
		{
			return !operator==(iter);
		}
	};


	template<typename T, typename START>
	class _Enumerate : _Container_adaptor<T>
	{
		T& m_container;
		const START m_start{};

		using iterator_type = Enumerate_iterator<typename _Container_adaptor<T>::iterator_type, START>;

	public:
		explicit _Enumerate(T& t, START start) : m_container{ t }, m_start{ start }
		{}

		iterator_type begin() const
		{
			auto iterator = _Container_adaptor<T>::begin(m_container);

			return iterator_type{ std::move( iterator ), m_start };
		}

		iterator_type end() const
		{
			auto iterator = _Container_adaptor<T>::end(m_container);

			return iterator_type{ std::move( iterator ) };
		}
	};

	template<typename T, typename START = int>
	auto enumerate(T& t, START start = 0)
	{
		return _Enumerate<T, START>{ t, start };
	}
}