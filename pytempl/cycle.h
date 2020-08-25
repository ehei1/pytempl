#pragma once

#include <type_traits>


namespace pytempl {
	template<typename Iterator>
	struct Cycle_iterator
	{
		using iterator_category = typename std::forward_iterator_tag;
		using value_type = typename Iterator::value_type;
		using difference_type = typename std::ptrdiff_t;
		using pointer = value_type * ;
		using reference = value_type & ;

	private:
		Iterator _iterator;
		Iterator _begin_iterator;
		size_t _count{};
		bool _is_infinite{};

	public:
		Cycle_iterator(Iterator& iterator, size_t count) : _iterator{ iterator }, _begin_iterator{ iterator }, _count{ count }, _is_infinite{ !count }
		{}

		Cycle_iterator(Iterator&& iterator) : _iterator{ std::forward<Iterator>(iterator) }
		{}

		bool operator==(Cycle_iterator const& other)
		{
			if (_iterator == other._iterator) {
				if (!_is_infinite) {
					if (0 == _count - 1) {
						return true;
					}
				}
				
				--_count;
				_iterator = _begin_iterator;
			}

			return false;
		}

		bool operator!=(Cycle_iterator const& other)
		{
			return !operator==(other);
		}

		value_type operator*()
		{
			return *_iterator;
		}

		Cycle_iterator& operator++()
		{
			++_iterator;

			return *this;
		}
	};

	template<typename T>
	class Cycle
	{
		using Iterator_type = typename std::decay_t<T>::iterator;
		using Cycle_Iterator_type = Cycle_iterator<Iterator_type>;

		T _container;
		size_t const _count{};

	public:
		Cycle(T&& t, size_t count) :_container{ std::forward<T>(t) }, _count{ count }
		{}

		Cycle_Iterator_type begin() const
		{
			return {std::begin(_container), _count};
		}

		Cycle_Iterator_type end() const
		{
			return{ std::end(_container) };
		}
	};

	template<typename T>
	auto cycle(T&& t, size_t count = 0)
	{
		return Cycle<T>{std::forward<T>(t), count};
	}
}