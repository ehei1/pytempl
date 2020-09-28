#pragma once

#include <type_traits>

#include "common/_iterator_adaptor.h"


namespace pytempl
{
	template<typename PRED, typename CONT>
	struct DropWhile_iterator
	{
		using iterator_category = typename std::forward_iterator_tag;
		using value_type = typename CONT::value_type;
		using difference_type = typename std::ptrdiff_t;
		using pointer = value_type*;
		using reference = value_type&;

		using iterator_type = _make_iterator_type_t<CONT>;
		iterator_type _iterator;

	public:
		DropWhile_iterator( PRED prediction, iterator_type iterator, bool predicted ) : _prediction{ prediction }, _iterator{ iterator }, _predicted{ predicted }
		{}

		bool operator==( DropWhile_iterator const& other )
		{
			if (_predicted) {
				_predicted = false;

				while (_iterator != other._iterator) {
					if (_prediction( *_iterator )) {
						++_iterator;
					}
					else {
						break;
					}
				}
			}

			return _iterator == other._iterator;
		}

		bool operator!=( DropWhile_iterator const& other )
		{
			return !operator==( other );
		}

		value_type operator*()
		{
			return *_iterator;
		}

		DropWhile_iterator& operator++()
		{
			++_iterator;

			return *this;
		}

	private:
		PRED _prediction;
		bool _predicted;
	};


	template<typename PRED, typename CONT>
	class DropWhile
	{
		PRED _prediction;
		CONT&& _container;

	public:
		DropWhile( PRED prediction, CONT&& container ) : _prediction{ prediction }, _container{std::forward<CONT>(container)}
		{}

		DropWhile_iterator<PRED, CONT> begin() const
		{
			return DropWhile_iterator<PRED, CONT>( _prediction, std::begin( _container ), true );
		}

		DropWhile_iterator<PRED, CONT> end() const
		{
			return DropWhile_iterator<PRED, CONT>( _prediction, std::end( _container ), false );
		}
	};


	template<typename PRED, typename CONT>
	auto dropwhile(PRED prediction, CONT&& container)
	{
		//static_assert(std::is_function<PRED>::value, "PRED must be callable");

		return DropWhile<PRED, CONT>( std::forward<PRED>( prediction ), std::forward<CONT>( container ) );
	}
}