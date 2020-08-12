#pragma once

#include <algorithm>
#include <cassert>

namespace pytempl
{
	template<typename T>
	class _Range_iterator : public std::iterator_traits<T>
	{
		T m_start{};
		const T m_stop{};
		const T m_step{};

	public:
		using iterator_category = typename std::bidirectional_iterator_tag;
		using value_type = T;
		using difference_type = typename std::ptrdiff_t;
		using pointer = T*;
		using reference = T&;

	public:
		explicit _Range_iterator(T start, T step) : m_start{ start }, m_step{ step }
		{
			assert(0 != step);
		}

		explicit _Range_iterator(T stop) : m_stop{ stop }
		{}

		_Range_iterator& operator++()
		{
			m_start += m_step;

			return *this;
		}

		T operator*() const
		{
			return m_start;
		}

		bool operator==(const _Range_iterator& iterator) const
		{
			if (0 < m_step)
			{
				return m_start >= iterator.m_stop;
			}
			else
			{
				return m_start <= iterator.m_stop;
			}
		}

		bool operator!=(const _Range_iterator& iterator) const
		{
			return !operator==(iterator);
		}
	};

	template<typename T>
	class _Range
	{
		const T m_start{};
		const T m_stop{};
		const T m_step{};

		using iterator_type = _Range_iterator<T>;

	public:
		explicit _Range(T start, T stop, T step) : m_start{ start }, m_stop{ stop }, m_step{ step }
		{
			assert(0 != step);
		}

		iterator_type begin() const
		{
			return iterator_type{ m_start, m_step };
		}

		iterator_type end() const
		{
			return iterator_type{ m_stop };
		}

		iterator_type rbegin() const
		{
			return iterator_type{ m_stop, -m_step };
		}

		iterator_type rend() const
		{
			return iterator_type{ m_start };
		}
	};

	template<typename T>
	_Range<T> range(T stop)
	{
		return _Range<T>{0, stop, 1};
	}

	template<typename T>
	_Range<T> range(T start, T stop)
	{
		return _Range<T>{start, stop, 1};
	}

	template<typename T>
	_Range<T> range(T start, T stop, T step)
	{
		return _Range<T>{start, stop, step};
	}
}