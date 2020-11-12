#pragma once

#include <map>
#include <tuple>

namespace pytempl {

	struct _ChainMap_iterator
	{};

	template<typename T, typename...Ts>
	struct _get_one_of_container
	{
		using type = T;
	};

	template<typename...Ts>
	struct _ChainMap
	{
		using _cont_t = typename _get_one_of_container<Ts...>::type;
		using _decayed_cont_t = std::decay_t<_cont_t>;
		using key_type = typename _decayed_cont_t::key_type;
		using mapped_type = typename _decayed_cont_t::mapped_type;
		using _conts_t = std::tuple<Ts...>;

		_conts_t _conts;

		_ChainMap( Ts&&...ts ) : _conts{std::forward<Ts>(ts)...}
		{}

		_ChainMap_iterator begin() const
		{
			return _ChainMap_iterator<Ts...>( _conts, true );
		}

		_ChainMap_iterator end() const
		{
			return _ChainMap_iterator<Ts...>( _conts, false );
		}

		mapped_type& operator[](key_type&& key)
		{
			constexpr auto last_idx = std::tuple_size<_conts_t>::value - 1;

			return _get_value_impl<last_idx>::get_value( _conts, std::forward<key_type>(key) );
		}

		template<size_t index>
		struct _get_value_impl
		{
			static mapped_type& get_value( _conts_t& conts, key_type&& key )
			{
				auto& cont = std::get<index>( conts );
				auto iter = cont.find( key );

				if (cont.end() == iter) {
					return _get_value_impl<index - 1>::get_value( conts, std::forward<key_type>( key ) );
				} 
				
				return iter->second;
			}
		};

		template<>
		struct _get_value_impl<0>
		{
			static mapped_type& get_value( _conts_t& conts, key_type&& key )
			{
				auto& cont = std::get<0>( conts );
				auto iter = cont.find( key );

				if (cont.end() == iter) {
					throw std::out_of_range( "key is not found" );
				}
				
				return iter->second;
			}
		};
	};
	
	template<typename...Ts>
	_ChainMap<Ts...> ChainMap( Ts&&...ts ) {
		return _ChainMap<Ts...>( std::forward<Ts>(ts)... );
	}
}

