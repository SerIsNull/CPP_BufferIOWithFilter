# ifndef __F_FILTER_EXAMPLE__
# define __F_FILTER_EXAMPLE__

// The buffer_type with the declaration of function filter here
# include "buffer_type.hpp"

// The declaration of  namespace for example
namespace example {

	using buffer_char     = buffer_type<char>;
	
	using ch_type         = buffer_char::char_type;

	using str_filter_type = buffer_char::str_filter_type;

	using sz_filter_type  = buffer_char::sz_filter_type;

	using fnc_filter_type = buffer_char::fnc_filter_type;

	using pos_type        = buffer_char::pos_type;
}

//==================================================================
// userFilter - this is interface function of filter for buffer_type
// pBuffer    - is a pointer to Buffer
// SZ_Buff    - is a size of buffer
// ArrFilters - is an array of template str
// SZ         - is a size if array of template str
//==================================================================
example::str_filter_type userFilter ( const example::ch_type *pBuffer,
					    example::pos_type SZ_Buf,
		                      	    example::str_filter_type *ArrFilters,
				            example::sz_filter_type   SZ 
				    );
# endif
