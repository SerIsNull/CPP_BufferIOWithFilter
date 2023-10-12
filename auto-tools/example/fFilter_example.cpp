# include "fFilter_example.hpp"
# include <string>
# include <iostream>

//==================================================================
// userFilter - this is implementation interface of user's filter
// pBuffer    - is a pointer to Buffer
// SZ_Buff    - is a size of buffer for filter
// ArrFilters - is an array of template str
// SZ         - is a size if array of template str
// return     - valid str or empty str
//==================================================================
example::str_filter_type userFilter ( const example::ch_type *pBuffer,
					    example::pos_type SZ_Buff,
		                      	    example::str_filter_type *ArrFilters,
				            example::sz_filter_type   SZ      
				    ) {
	
	// The str for filtering
	std::basic_string<example::ch_type> srcStr( pBuffer, SZ_Buff);
	std::cout << "Src Str in Filter = " << srcStr << "End\n";

	// The result str
	std::basic_string<example::ch_type> resStr(srcStr.size(), ' ');

	// Position of valid token
	std::basic_string<example::ch_type>::size_type posFnd{ 0 };

	// Try to filter the src str
	for(size_t i {0}; i < SZ; ) {

		posFnd = srcStr.find( ArrFilters[i] );

		if ( posFnd != std::basic_string<example::ch_type>::npos ) {
			resStr.replace( posFnd, ArrFilters[i].size(), ArrFilters[i]);

			// Clear finded token in source str
			srcStr.replace(posFnd, ArrFilters[i].size(), ArrFilters[i].size(),' ');
		}

		else 
			i++;
	}

	std::cout << "Res filter = " << resStr << '\n';

return resStr.empty() ? std::basic_string<example::ch_type>() : resStr;
}
