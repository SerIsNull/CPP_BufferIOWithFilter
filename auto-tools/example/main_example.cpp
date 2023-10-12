//==============================================]
// This is example demonstrates work of         ]
// buffer_type for writing data into the 	]
// outFile_example.txt and reading - from       ]
// inFile_example.txt.                          ]
//                                              ]
// The data before writing filtered with user's ]
// function called "userFilter".                ]
// The namespace "example" , user's filter and  ]
// buffer_type declared in "fFilter_example.hpp"]
//						]
// The scheme for writing:		        ]
// storage ->buffer ->filter ->destination file ]
// 						] 
// The scheme for reading:		        ]
// source file ->buffer ->filter ->storage      ]
//                                              ]
// It's optional filter. You can use it without ]
// filter.                                      ]
// For information see:/include/buffer_type.hpp ]
// =============================================]


# include "fFilter_example.hpp"
# include <iostream>
# include <string>



int main() {

try { 


// ==============================
// Prepare filter
// ==============================

	// Define the user's function for filtering data
	example::fnc_filter_type fncFilter {  userFilter  };

	// Define the value of filtering
	example::str_filter_type strFilter[] { "Привет", "Привет","three" };

	// Define the size of value filtering
	example::sz_filter_type szFilter = sizeof(strFilter) / sizeof(strFilter[0]) ;

// ==============================
// Writing with user's filter
// ==============================
   {
	// Init the buffer like a file
	example::buffer_char out_buffer("./outFile_example.txt", std::ios_base::out|std::ios_base::app, 30) ;
	
	// Set user's filter in the buffer 
	out_buffer.set_filter(fncFilter, strFilter, szFilter);

	// Join the buffer to iostream	
	std::basic_iostream<example::ch_type> out_flow (&out_buffer);

	// The storage for out data
	std::basic_string<example::ch_type> out_data[3] {"Привет",
		                                         "Привет Bye-Bye three",
							 "Hello, I'm writing it"};
	
	// Fully valid. Write into the file     "Привет"
	out_flow << out_data[0]; 

	// Partially valid. Write into the file "Привет         three"
        out_flow << out_data[1];

	// Not valid. Write into the file       "                     "
        out_flow << out_data[2];

   } // In this way we wrote the data such as "ПриветПривет         three                     "


// ==============================
// Reading with user's filter 
// ==============================
   {

	/* Init the buffer like a file with: "Привет",
	                                     "Привет Bye-Bye three",
                                             "Hello, I'm writing it" */
 
	example::buffer_char in_buffer("./inFile_example.txt", std::ios_base::in, 30);
	
	// Set user's filter in the buffer 
	in_buffer.set_filter(fncFilter, strFilter, szFilter);

	// Prepare iostream
	std::basic_iostream<example::ch_type> in_flow ( &in_buffer );

	// The storage for input data
	std::basic_string<example::ch_type> in_data[3];

	// Str No1 is valid. Get from the file "Привет"
	in_flow >> in_data[0];

	// Str No2 partially valid. Get from the file "Привет" and "three"
	in_flow >> in_data[1];
	in_flow >> in_data[2];

	// Str No3 is not valid. Get from the file ""
	in_flow >> in_data[3]; 

	std::cout << in_data[0] << "|" << in_data[1] << "|" << in_data[2] << "|" << in_data[3] << "|";
   }



// !!! You can define the user's filter how you want or without it !!!
}

catch ( ... ) { std::cerr << "Anything error !"<< '\n'; }
return 0;	
};
