#pragma once

#include <tuple>


namespace pytempl
{
	template<typename Container_iterators, typename Container_values>
	struct Iterator
	{
		Container_iterators _container_iterators;
		static constexpr size_t Iterator_size = std::tuple_size< Container_iterators>::value;

		using reference = Container_values;

	public:
		Iterator(Container_iterators&& container_iterators) : _container_iterators{ std::forward<Container_iterators>(container_iterators) }
		{}

		bool operator==(const Iterator& other) const
		{
			return _is_equal<Iterator_size>(*this, other);
		}

		bool operator!=(const Iterator& other) const
		{
			return !operator==(other);
		}

		Container_values operator*()
		{
			return _get_values(std::make_index_sequence<Iterator_size>());
		}

		Iterator& operator++()
		{
			_iterate(std::make_index_sequence<Iterator_size>());

			return *this;
		}

	private:
		template<size_t Index>
		bool _is_equal(const Iterator& lhs, const Iterator& rhs) const
		{
			constexpr size_t tuple_index = Index - 1;

			auto lhs_iter = std::get<tuple_index>(lhs._container_iterators);
			auto rhs_iter = std::get<tuple_index>(rhs._container_iterators);

			if (lhs_iter == rhs_iter) {
				return true;
			}
			else {
				return _is_equal<tuple_index>(lhs, rhs);
			}
		}

		template<>
		bool _is_equal<0>(const Iterator& lhs, const Iterator& rhs) const
		{
			return false;
		}

		template<std::size_t... Indices>
		Container_values _get_values(std::index_sequence<Indices...>)
		{
			return std::make_tuple(*(std::get<Indices>(_container_iterators))...);
		}

		template<std::size_t... Indices>
		void _iterate(std::index_sequence<Indices...>)
		{
			std::make_tuple((std::get<Indices>(_container_iterators)++)...);
		}
	};

	template<typename T>
	struct _Zip_element_base
	{
		auto begin(T& t) const
		{
			return std::begin(t);
		}

		auto end(T& t) const
		{
			return std::end(t);
		}
	};

	template<typename T>
	struct _Zip_element_base<T const>
	{
		auto begin(T& t) const
		{
			return std::cbegin(t);
		}

		auto end(T& t) const
		{
			return std::cend(t);
		}
	};

	template<typename T, typename...>
	struct _Zip_element : public _Zip_element_base<T>
	{
		T _container;

		using container_type = typename std::decay_t<T>;
		using iterator_type = typename std::conditional_t< std::is_const<std::remove_reference_t<T>>::value, typename container_type::const_iterator, typename container_type::iterator >;
		using value_type = typename container_type::value_type;
		using Element_base = _Zip_element_base<T>;

	public:
		_Zip_element(T&& t) : _container{ std::forward<T>(t) }
		{}

		iterator_type begin() const
		{
			return Element_base::begin(_container);
		}

		iterator_type end() const
		{
			return Element_base::end(_container);
		}
	};

	template<typename...Ts>
	class Zip;

	template<typename T, typename...Ts>
	struct Zip<T, Ts...> : public _Zip_element<T, Ts...>, public Zip<Ts...>
	{
		using _Container = std::tuple<T, Ts...>;
		using _Element = _Zip_element<T, Ts...>;
		using _Base = Zip<Ts...>;

		using Container_iterators = std::tuple<typename _Element::iterator_type, typename Zip<Ts>::iterator_type...>;
		using Container_values = std::tuple<typename _Element::value_type, typename Zip<Ts>::value_type...>;

		using iterator = Iterator<Container_iterators, Container_values>;

	public:
		Zip(T&& t, Ts&&...ts) :
			Zip<Ts...>{ std::forward<Ts>(ts)... },
			_Zip_element<T, Ts...>{ std::forward<T>(t) }
		{}

		iterator begin()
		{
			auto iterators = _begin();

			return Iterator<Container_iterators, Container_values>(std::move(iterators));
		}

		iterator end()
		{
			auto iterators = _end();

			return Iterator<Container_iterators, Container_values>(std::move(iterators));
		}

	protected:
		Container_iterators _begin()
		{
			return std::tuple_cat(std::tie(_Element::begin()), _Base::_begin());
		}

		Container_iterators _end()
		{
			return std::tuple_cat(std::tie(_Element::end()), _Base::_end());
		}
	};

	template<typename T>
	class Zip<T> : public _Zip_element<T>
	{
		using _Element = _Zip_element<T>;
		using container = std::tuple<T>;
		using value_type = typename std::remove_reference_t<T>::value_type;
		using Container_iterators = std::tuple<typename _Element::iterator_type>;

	public:
		Zip(T&& t) : _Zip_element{ std::forward<T>(t) }
		{}

	protected:
		Container_iterators _begin()
		{
			return std::tuple_cat(std::tie(begin()));
		}

		Container_iterators _end()
		{
			return std::tuple_cat(std::tie(end()));
		}
	};

	template<typename...Ts>
	auto zip(Ts&&...ts) noexcept
	{
		return Zip<Ts...>{ std::forward<Ts>(ts)... };
	}
}