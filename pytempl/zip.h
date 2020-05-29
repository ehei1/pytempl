#pragma once

#include <set>
#include <tuple>


namespace pytempl {
	template<typename T>
	class _Container_iterator
	{
	public:
		T m_iterator;

		using value_type = typename T::value_type;

	public:
		_Container_iterator( T& t ) : m_iterator{ t }
		{}

		value_type get_value()
		{
			return *m_iterator;
		}

		bool iterate()
		{
			++m_iterator;

			return true;
		}

		bool operator==( _Container_iterator<T>& _iterator )
		{
			return _iterator != m_iterator;
		}
	};

	template<typename...Ts>
	class Container_iterator : _Container_iterator<Ts>...
	{
	public:
		using value_type = std::tuple<typename _Container_iterator<Ts>::value_type...>;
		using iterator_category = std::forward_iterator_tag;

	public:
		Container_iterator( Ts&&...ts ) : _Container_iterator<Ts>( ts )...
		{}

		value_type operator*()
		{
			return{ _Container_iterator<Ts>::get_value()... };
		}

		void operator++()
		{
			std::initializer_list<bool>{ _Container_iterator<Ts>::iterate()... };
		}

		bool operator==( Container_iterator<Ts...>& iterator )
		{
			return _is_equal<Ts...>( iterator );
		}

		bool operator!=( Container_iterator<Ts...>& iterator )
		{
			return !operator==( iterator );
		}

	private:
		template<typename A, typename...As>
		bool _is_equal( Container_iterator<Ts...>& iterator )
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
	class _Reference_container
	{
		T& m_container;

	protected:
		using value_type = typename T::value_type;
		using iterator = typename T::iterator;
		using const_iterator = typename T::const_iterator;

	public:
		_Reference_container( T& t ) : m_container{ t }
		{}

		iterator begin()
		{
			return std::begin( m_container );
		}

		iterator end()
		{
			return std::end( m_container );
		}

		const_iterator begin() const
		{
			return std::cbegin( m_container );
		}

		const_iterator end() const
		{
			return std::cend( m_container );
		}
	};

	template<typename...Ts>
	class Zip : _Reference_container<Ts>...
	{
	public:
		using value_type = std::tuple<typename _Reference_container<Ts>::value_type...>;
		using iterator = Container_iterator<typename _Reference_container<Ts>::iterator...>;
		using const_iterator = Container_iterator<typename _Reference_container<Ts>::const_iterator...>;

	public:
		Zip( Ts&...ts ) : _Reference_container<Ts>( ts )...
		{}

		iterator begin()
		{
			return iterator{ _Reference_container<Ts>::begin()... };
		}

		iterator end()
		{
			return iterator{ _Reference_container<Ts>::end()... };
		}

		const_iterator begin() const
		{
			return const_iterator{ _Reference_container<Ts>::begin()... };
		}

		const_iterator end() const
		{
			return const_iterator{ _Reference_container<Ts>::end()... };
		}
	};
};