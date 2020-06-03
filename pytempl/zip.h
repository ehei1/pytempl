#pragma once

#include <set>
#include <tuple>
#include <type_traits>

#include "common\_container_adaptor.h"

/*
https://docs.python.org/3/library/functions.html#zip

// TODO: iterator supports
*/
namespace pytempl {
	template<typename T>
	class _Container_iterator
	{
	public:
		T m_iterator;

		using value_type = typename T::reference;

	public:
		_Container_iterator( T& t ) : m_iterator{ t }
		{}

		value_type get_value() const
		{
			return *m_iterator;
		}

		bool iterate()
		{
			++m_iterator;

			return true;
		}

		bool operator==( const _Container_iterator<T>& _iterator ) const
		{
			return _iterator != m_iterator;
		}
	};

	class Dummy_iterator_trait
	{};

	template<typename...Ts>
	class Container_iterator : public std::iterator_traits<Dummy_iterator_trait>, public _Container_iterator<Ts>...
	{
	public:
		using iterator_category = typename std::forward_iterator_tag;
		using value_type = std::tuple<typename _Container_iterator<Ts>::value_type...>;
		using difference_type = void;
		using pointer = value_type*;
		using reference = value_type;

	public:
		Container_iterator( Ts&&...ts ) : _Container_iterator<Ts>( ts )...
		{}

		value_type operator*() const
		{
			return{ _Container_iterator<Ts>::get_value()... };
		}

		void operator++()
		{
			std::initializer_list<bool>{ _Container_iterator<Ts>::iterate()... };
		}

		bool operator==( const Container_iterator<Ts...>& iterator ) const
		{
			return _is_equal<Ts...>( iterator );
		}

		bool operator!=( const Container_iterator<Ts...>& iterator ) const
		{
			return !operator==( iterator );
		}

	private:
		template<typename A, typename...As>
		bool _is_equal( const Container_iterator<Ts...>& iterator ) const
		{
			auto lhs{ _Container_iterator<A>::m_iterator };
			auto rhs{ static_cast<_Container_iterator<A>>( iterator ).m_iterator };

			if ( lhs == rhs ) {
				return true;
			}

			auto r{ std::set<bool>{ _is_equal<As>( iterator )... } };

			if ( r.count( true ) ) {
				return true;
			}
			else {
				return false;
			}
		}
	};

	template<typename T>
	class _Reference_container : public _Container_adaptor<T>
	{
		T& m_container;
		using iterator_type = typename _Container_adaptor<T>::iterator_type;

	public:
		_Reference_container( T& t ) : m_container{ t }
		{}

		iterator_type begin() const
		{
			return _Container_adaptor<T>::begin( m_container );
		}

		iterator_type end() const
		{
			return _Container_adaptor<T>::end( m_container );
		}
	};

	template<typename...Ts>
	class _Zip : public _Reference_container<Ts>...
	{
	public:
		using iterator = Container_iterator<typename _Reference_container<Ts>::iterator_type...>;

	public:
		_Zip ( Ts&...ts ) : _Reference_container<Ts>( ts )...
		{}

		iterator begin() const
		{
			return iterator{ _Reference_container<Ts>::begin()... };
		}

		iterator end() const
		{
			return iterator{ _Reference_container<Ts>::end()... };
		}
	};

	template<typename...Ts>
	auto zip(Ts&&...ts) noexcept
	{
		return _Zip<Ts...>{ ts... };
	}
};