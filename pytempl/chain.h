#pragma once

#include <array>
#include <cassert>
#include <functional>
#include <iostream>
#include <tuple>
#include <type_traits>

#include "common/_iterator_adaptor.h"


namespace pytempl {
	template<typename Iterators>
	struct Chain_iterator
	{
		using iterator_category = typename std::forward_iterator_tag;
		using value_type = typename std::tuple_element_t<0, Iterators>::value_type;
		using difference_type = typename std::ptrdiff_t;
		using pointer = value_type*;
		using reference = value_type&;

		static constexpr size_t _iterator_count = std::tuple_size<Iterators>::value;

		Iterators _iterators;
		size_t _iterator_index{};

		Chain_iterator(Iterators&& iterators) : _iterators{ std::forward<Iterators>(iterators) }
		{}

		bool operator==(Chain_iterator const& other)
		{
			while (_is_iterator_end_impl<_iterator_count>::visit(_iterators, other._iterators, _iterator_index)) 
			{
				if (_iterator_index == _iterator_count - 1) {
					return true;
				}

				++_iterator_index;
			}

			return false;
		}

		bool operator!=(Chain_iterator const& other)
		{
			return !operator==(other);
		}

		value_type operator*()
		{
			return _get_value_impl<_iterator_count>::visit(_iterators, _iterator_index);
		}

		Chain_iterator& operator++()
		{
			_forward_iterate_impl<_iterator_count>::visit(_iterators, _iterator_index);

			return *this;
		}

	private:
		// https://stackoverflow.com/questions/28997271/c11-way-to-index-tuple-at-runtime-without-using-switch
		template<size_t Index>
		struct _forward_iterate_impl
		{
			static void visit(Iterators& iterators, size_t target_index)
			{
				constexpr size_t current_index = _iterator_count - Index;

				if (target_index == current_index) {
					++std::get<current_index>(iterators);
				}
				else {
					_forward_iterate_impl<Index - 1>::visit(iterators, target_index);
				}
			}
		};

		template<>
		struct _forward_iterate_impl<0>
		{
			static void visit(Iterators& iterators, size_t target_index)
			{}
		};

		template<size_t Index>
		struct _is_iterator_end_impl
		{
			static bool visit(Iterators const& begin_iterators, Iterators const& end_iterators, size_t target_index)
			{
				constexpr size_t current_index = _iterator_count - Index;

				if (target_index == current_index) {
					auto begin_iterator = std::get<current_index>(begin_iterators);
					auto end_iterator = std::get<current_index>(end_iterators);

					return begin_iterator == end_iterator;
				}
				else {
					return _is_iterator_end_impl<Index - 1>::visit(begin_iterators, end_iterators, target_index);
				}
			}
		};

		template<>
		struct _is_iterator_end_impl<0>
		{
			static bool visit(Iterators const& begin_iterators, Iterators const& end_iterators, size_t target_index)
			{
				return false;
			}
		};

		template<size_t Index>
		struct _get_value_impl
		{
			static value_type visit(Iterators& iterators, size_t target_index)
			{
				constexpr size_t current_index = _iterator_count - Index;

				if (target_index == current_index) {
					return *std::get<current_index>(iterators);
				}
				else {
					return _get_value_impl<Index - 1>::visit(iterators, target_index);
				}
			}
		};

		template<>
		struct _get_value_impl<0>
		{
			static value_type visit(Iterators& iterators, size_t target_index)
			{
				return {};
			}
		};
	};

	template<typename...Ts>
	struct Chain
	{
		using _container_types = std::tuple<Ts...>;
		_container_types _containers;

		using _iterator_types = std::tuple<_make_iterator_type_t<Ts>...>;

		Chain(Ts&&...ts) : _containers{std::forward<Ts>(ts)...}
		{}

		Chain_iterator<_iterator_types> begin() const
		{
			_iterator_types begin_iterators{ _get_begin(std::make_index_sequence<sizeof...(Ts)>()) };
			_iterator_types end_iterators{ _get_end(std::make_index_sequence<sizeof...(Ts)>()) };

			return { std::move(begin_iterators) };
		}

		Chain_iterator<_iterator_types> end() const
		{
			_iterator_types end_iterators{ _get_end(std::make_index_sequence<sizeof...(Ts)>()) };

			return { std::move(end_iterators) };
		}

	private:
		template<std::size_t... Indices>
		_iterator_types _get_begin(std::index_sequence<Indices...>) const
		{
			return std::make_tuple(std::begin(std::get<Indices>(_containers))...);
		}

		template<std::size_t... Indices>
		_iterator_types _get_end(std::index_sequence<Indices...>) const
		{
			return std::make_tuple(std::end(std::get<Indices>(_containers))...);
		}
	};

	template<typename...Ts>
	struct __check_same_types
	{};

	template<typename T>
	struct __check_same_types<T>
	{
		using value_type = typename std::decay_t<T>::value_type;
		static constexpr bool is_same = true;
	};

	template<typename T, typename...Ts>
	struct __check_same_types<T, Ts...> : __check_same_types<Ts...>
	{
		using value_type = typename std::decay_t<T>::value_type;
		static constexpr bool is_same = std::is_same<value_type, __check_same_types<Ts...>::value_type>::value;
	};

	template<typename...Ts>
	struct _check_same_types : __check_same_types<Ts...>
	{
		static constexpr bool is_same = __check_same_types<Ts...>::is_same;
	};

	template<typename...Ts>
	auto chain(Ts&&...ts)
	{
		static_assert(_check_same_types<Ts...>::is_same, "chain require same type about all containers");

		return Chain<Ts...>{std::forward<Ts>(ts)...};
	}
}