#pragma once

#include <type_traits>


namespace pytempl
{
	template<typename T>
	struct _make_iterator_type
	{
		using decayed_type = std::decay_t<T>;
		using iterator = typename decayed_type::iterator;
		using const_iterator = typename decayed_type::const_iterator;
		using type = std::conditional_t<std::is_const<std::remove_reference<T>>::value, const_iterator, iterator>;
	};


	template<typename T>
	using _make_iterator_type_t = typename _make_iterator_type<T>::type;
}
