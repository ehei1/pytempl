#pragma once

#include <limits>


namespace pytempl {
	template<typename T>
	struct Repeat_iterator
	{
		using iterator_category = typename std::forward_iterator_tag;
		using value_type = T;
		using difference_type = typename std::ptrdiff_t;
		using pointer = value_type*;
		using reference = value_type&;

	private:
		T _value;
		size_t _count{};
		bool const _is_infinite{};

	public:
		Repeat_iterator(T value, size_t count) : _value{ value }, _count{ count }, _is_infinite{ !count }
		{}

		Repeat_iterator()
		{}

		bool operator==(const Repeat_iterator& other) const
		{
			if (_is_infinite) {
				return false;
			}
			else if (_count > other._count) {
				return false;
			}
			else {
				return true;
			}
		}

		bool operator!=(const Repeat_iterator& other) const
		{
			return !operator==(other);
		}

		T& operator*()
		{
			return _value;
		}

		Repeat_iterator& operator++()
		{
			--_count;

			return *this;
		}
	};

	template<typename T>
	class Repeat
	{
		size_t const _count{};
		T _value;
		using Iterator_type = Repeat_iterator<T>;
		
	public:
		Repeat(T&& value, size_t count) : _value{ std::forward<T>(value) }, _count{ count }
		{}

		Iterator_type begin() const
		{
			return { _value, _count };
		}

		Iterator_type end() const
		{
			return {};
		}
	};

	template<typename T>
	Repeat<T> repeat(T&& value, size_t count = {})
	{
		return Repeat<T>( std::forward<T>(value), count );
	};
}