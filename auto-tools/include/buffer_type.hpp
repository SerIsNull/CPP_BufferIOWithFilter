# ifndef __BUFFER_TYPE__
# define __BUFFER_TYPE__

# include <iostream>
# include <string>
# include <streambuf>
# include <fstream>
# include <type_traits>
# include <vector>
# include <cstring>
# include <functional> 
# include <limits>


//============================================================================+
//========================== Declaration section =============================+
//============================================================================+
// buffer_type realize buffer for input/output stream.
// It may be used for filtering data.
// For more information see: README.md

template<class TypeData, 
	 class traits_type = std::char_traits<TypeData>>
class buffer_type : public std::basic_streambuf<typename traits_type::char_type> 	
	{

	protected:
		using BaseBuff    = std::basic_streambuf<typename traits_type::char_type>;

	public:
		// Common types
		using int_type    = typename BaseBuff::int_type ;
		using char_type   = typename BaseBuff::char_type;
		using pos_type    = typename BaseBuff::pos_type ;

		// Types for filtering
		using str_filter_type = typename std::basic_string <char_type>;
		using sz_filter_type  = typename str_filter_type::size_type;
		using fnc_filter_type = typename std::function< str_filter_type (const char_type*, pos_type, str_filter_type*, sz_filter_type)>;

		// Create the buffer for read (i.e. geta area) or write (i.e.put area)
		buffer_type(std::string &&Path, std::ios_base::openmode Mode, pos_type SZ );
	
		// Write user's data into the buffer
		std::streamsize xsputn(const char_type* SrcData, 
		                       std::streamsize cnt_NotWrite) override;

		// Write bufer's data into the destination file
		int_type overflow(int_type cn_NotBuff) override;

		// Read data from source file
		int_type underflow() override;

		// Set user's filter
		void set_filter( fnc_filter_type  usr_fnc_filter,	
				 str_filter_type *usr_str_filter,
				 sz_filter_type   usr_sz_filter
			       );

	private:

		// Handle for read / write errors
		bool is_clean_up_mess( const std::exception_ptr &eptr = std::current_exception() );

		// For put area
		using BaseBuff::setp;
		using BaseBuff::epptr;
		using BaseBuff::pbase;
		using BaseBuff::overflow;
		using BaseBuff::xsputn;

		// For get area
		using BaseBuff::setg;
		using BaseBuff::underflow;
		using BaseBuff::gptr;


		// Open mode
		std::ios_base::openmode       m_Mode;

		// The buffer
		std::vector<char_type>        m_Buffer;

		// The src-file or dest-file 
		std::basic_fstream<char_type> m_Data;

		// The path to the file
		std::string                   m_Path;

		// The size of our buffer
		pos_type                      m_BuffSZ;

		// For user's filter
		fnc_filter_type	              m_FncFilter ;
		str_filter_type	             *m_StrFilter ;
		sz_filter_type	              m_SzFilter  ;
};

//============================================================================+
//========================== Implementation section ==========================+
//============================================================================+

//============================================================================]
// Constructor: This method for create the buffer for input / output stream.  ]
// This method maybe throws exceptions, if the file doesn't open or size of   ]
// buffer <= 0 - Exception                                                    ]
//============================================================================]
// 1) Mode - is a mode of buffer.					      ]
//        std::ios_base::in  - getting buffer ouput stream;                   ]
//        std::ios_base::out - getting buffer input stream.                   ]
//____________________________________________________________________________]
// 2) Path - is a path to the destination-file, if it opens for output stream ]
// or to the source-file, if it opens for input stream.                       ]
//____________________________________________________________________________]
// 3) SZ   - is a size of buffer. This parametr is optional. It's default     ]
// value means that the flow is unbuffered.                                   ]
//____________________________________________________________________________]
template<class TypeData, class traits_type>
buffer_type< TypeData,
	     traits_type>::buffer_type( std::string &&Path,
				        std::ios_base::openmode Mode,
			      	        pos_type SZ)
		try :

	 	     m_BuffSZ    { SZ == 0 ? throw std::invalid_argument(" cannot create the buffer of size == 0 !") : 
			           SZ   },
		     m_Mode      { Mode },
		     m_Path      { Path },
		     m_Buffer    ( SZ   ),
		     m_Data      ( Path, Mode) {


		//  Prepare our buffer
		m_Buffer.shrink_to_fit();

		// Does this file open ?
		if( !m_Data.is_open() ) 
			throw std::ios_base::failure( " cannot open the file. You have to use only modes such as in,out,out|app and out|trunc. You also check that the path to the file is valid !");

		//  Set pointers to the get area or put area
		switch (m_Mode) {

			// get area
			case std::ios_base::in:
				setg(m_Buffer.data(), 
				     m_Buffer.data() + m_BuffSZ,
				     m_Buffer.data() + m_BuffSZ
				    );
				break;

			// put area
			case std::ios_base::out : 
			case std::ios_base::out | std::ios_base::trunc : 
			case std::ios_base::out | std::ios_base::app   :

				setp(m_Buffer.data(),
				     m_Buffer.data() + m_BuffSZ
				    );
				break;

			// uncnown mode
			default:
				throw std::invalid_argument( "  cannot open the file. You have to use only modes such as in,out,out|app and out|trunc !");
			}
		}

		// The handlers of erros in open file and create buffer
		catch ( const std::length_error &e     )  { std::cerr << "Fatal error : cannot create the buffer of size < 0 !\n"; throw e; }
		catch ( const std::invalid_argument  &e)  { std::cerr << "Fatal error :" << e.what() << '\n'; throw e; }
		catch ( const std::ios_base::failure &e)  { std::cerr << "Fatal error :" << e.what() << '\n'; throw e; }

//============================================================================]
// set_filter() :This method sets user's filter for output buffer before      ]
// writing. It maybe used for input buffer before getting data.               ]
//============================================================================]
// 1) usr_fnc_filter - is a pointer to the function of user's filter          ]
// 2)*usr_str_filter - is a pointer to the value of user's filter             ]
// 3) usr_sz_filter  - is a size filter's value                               ]
//____________________________________________________________________________]
template<class TypeData,
	 class traits_type>
void buffer_type<TypeData, traits_type>::set_filter( fnc_filter_type  usr_fnc_filter,	
				 		     str_filter_type *usr_str_filter,
				 		     sz_filter_type   usr_sz_filter
			      			   ) {
		     m_FncFilter   = usr_fnc_filter;
		     m_StrFilter   = usr_str_filter;
		     m_SzFilter    = usr_sz_filter ;
}

//============================================================================]
// is_clean_up_mess() :This methods shows error and try to clear errors in    ]
// the file and then it reopen. If it's impossible - this function returns    ]
// false 	                                                              ]
//============================================================================]
template<class TypeData,
	 class traits_type>
bool buffer_type<TypeData, traits_type>::is_clean_up_mess( const std::exception_ptr &eptr ) {
	
try {   // Fatall error
	if( eptr == nullptr )
		throw std::bad_exception();

	// Rethrow it
	else 

		std::rethrow_exception( eptr );
    }

// Hahdle of fatal error
catch( const std::bad_exception &e) { 

		std::cerr << " Try to up : cannot handle this error! Fatal error !" << '\n';
		throw e;
    }

// Handle of read/write error
catch( const std::ios_base::failure &e) {
		std::cerr << e.what() << '\n';

	// Try to clear and reopened
	m_Data.clear();
	m_Data.close();
	m_Data.open(m_Path, m_Mode);

	// Does it clear?
	if ( m_Data.is_open() && !m_Data.bad() )
		std::clog << " Try to up : the file " + m_Path + " was reopened !";

	else
		std::cerr << " Try to up : the file " + m_Path + " isn't up! Fatal error !";
}
     	
return m_Data.is_open() && !m_Data.bad();
}

//============================================================================]
// xsputn() :This method gets sourse data and size of it. It writes this data ]
// from user into the output buffer. When the buffer is full - calls          ]
// overflow(). It happens till the source data exists.                        ]
//============================================================================]
// 1) SrcData      - is a source data from user                               ]
//____________________________________________________________________________]
// 2) cnt_NotWrite - is a counter of characters which didn't write into the   ]
// buffer  	                                                              ]
// 3) cnt_Write    - is a counter of characters which wrote into the buffer   ]
// 4) cnt_FullBuf  - is a counter of full-buffers                             ]
//____________________________________________________________________________]
// 5) setp(pStrt, pEnd) - this method sets new pointers into the put area     ] 
// area before calling overflow()                                             ]
//____________________________________________________________________________]
template<class TypeData,
	 class traits_type>
std::streamsize buffer_type<TypeData, traits_type>::xsputn(const char_type* SrcData, 
		                                           std::streamsize cnt_NotWrite) {

		if ( m_Mode == std::ios_base::in ) return cnt_NotWrite;

			std::streamsize cnt_Write      { 0 },
			                cnt_AllWrite   { 0 },
					cnt_FullBuf    { cnt_NotWrite / m_BuffSZ };

		// Write source data into the buffer. For fully filled buffers
		for(std::streamsize i_Buf{0}; i_Buf < cnt_FullBuf; i_Buf++){

			for(char_type &Ch_Buf : m_Buffer) {
				       Ch_Buf = SrcData[cnt_Write];
				       cnt_Write++;
			}
				
				//  The buffer is full. Update poiners to the buffer (put area)
				setp(m_Buffer.data(), m_Buffer.data() + m_Buffer.size());


				//  Write it to the destination file. Maybe exceptions
			try  {
				overflow( SrcData[cnt_Write] );

				cnt_AllWrite += cnt_Write;
				cnt_NotWrite -= cnt_Write;
			     }
			
			// Handler for error of writing
			catch( const std::ios_base::failure &e ) {

				// Try to clear and continue
			        if ( !is_clean_up_mess( ) ) throw e;
			}
				
				cnt_Write = 0;
			}
			
		// Is there any source data left ?
		if ( cnt_NotWrite > 0) {

			// Change buffer's size for it
			m_Buffer.resize(cnt_NotWrite);

			// For partially filled buffer
			for(char_type &Ch_Buf : m_Buffer) {
				       Ch_Buf = SrcData[cnt_Write];
				       cnt_Write++;
			}
										
				//  The buffer is full. Update poiners to the put area.
				setp(m_Buffer.data(), m_Buffer.data() + m_Buffer.size() );
				

				//  Write it to the destination file. Maybe exceptions
			try  {
				overflow( SrcData[cnt_Write] );

				cnt_AllWrite += cnt_Write;
			     }

			// Handler for error of writing
			catch( const std::ios_base::failure &e ) {

				// Try to clear and exit
			        if ( !is_clean_up_mess( ) ) throw e;
			}
			
				//  Restore buffer's size
				m_Buffer.resize(m_BuffSZ);
		}

return cnt_AllWrite;
}

//============================================================================]
// overflow() :This method handles overflowing of the buffer for output stream]
// It writes the data to the destination file. The valid data maybe filtered  ]
// before writing or not. The filter works if the user defines this function. ]
// When the buffer is empty - this method returns EOF into the xputn()        ]
//============================================================================]
// 1) Cn_NotBuff  - is a first character which didn't fit into the buffer     ]
//____________________________________________________________________________]
// 2) SZ_PutArea  - is a size of put area ( ouput buffer )                    ]
//____________________________________________________________________________]
// 3) m_FncFilter, m_StrFilter, m_SzFilter - it's about filter		      ]
//____________________________________________________________________________]
template<class TypeData,
	 class traits_type>
typename buffer_type<TypeData, traits_type>::int_type
buffer_type<TypeData, traits_type>::overflow(int_type ch_NotBuff) {

		// Checking a file before write
		if ( m_Data.bad() )
			throw std::ios_base::failure ("Error in writing into the " +
						       m_Path + "." +
						       " It'll tries to reopened !");

		// How many characters do we need to write ?
		pos_type SZ_PutArea = epptr() - pbase();

		// We try to accept the user's filter
		if ( m_FncFilter ) {

			std::vector<char_type> cpyBuffer ( m_Buffer );

			str_filter_type ResFilter { m_FncFilter ( cpyBuffer.data(), SZ_PutArea, m_StrFilter, m_SzFilter) };

			// The symbols in the buffer is valid - save it !!!
			if ( !ResFilter.empty()) {

				SZ_PutArea = ResFilter.size();

				// Copy filtered symbols instead of non-filtered symbols in the get area !!!
				std::memcpy( m_Buffer.data(), ResFilter.data(), SZ_PutArea );
				}
				// The symbols in the buffer is not valid - exit !!!
				else 
					return traits_type::eof();
			}

		
			// Writing it to the destination-file
			m_Data.write( m_Buffer.data(), SZ_PutArea );

return m_Data.good() ? ch_NotBuff : traits_type::eof();
}

//============================================================================]
// underflow() : This method handles underflowing of the buffer for input     ]
// stream. It reads the data from the resource-file. The data maybe filtered  ]
// before getting to user. The filter works if the user defines m_FncFilter   ]
// function. When the buffer is empty - this method returns EOF. If           ]
// neccessary - we try to start one more reading from the resource-file.      ]
//============================================================================]
// 1) Cn_NotBuff  - is a first character which didn't fit into the buffer     ]
//____________________________________________________________________________]
// 2) SZ_GetArea  - is a size of get area ( input buffer )                    ]
//____________________________________________________________________________]
// 4) m_FncFilter, m_StrFilter, m_SzFilter - it's about filter		      ]
//____________________________________________________________________________]
template<class TypeData,
	 class traits_type>
typename buffer_type<TypeData, traits_type>::int_type
buffer_type<TypeData, traits_type>::underflow() {

		// Read from source file to the buffer or exit.
		if ( m_Data.eof() ) return traits_type::eof();

		pos_type SZ_GetArea {0};

	// Checking a file before read
	try  {
		if ( m_Data.bad() )
		throw std::ios_base::failure ("Error in reading from the " +
					       m_Path + "." +
					      " It'll tries to reopened !");

		m_Data.read( m_Buffer.data(), m_Buffer.size());

		// How many characters do we read ?
		SZ_GetArea = m_Data.gcount();
        }

	// Handler for error of writing
	catch( const std::ios_base::failure &e ) {

		// Try to clear and exit
		if ( !is_clean_up_mess( ) ) throw e ;
		SZ_GetArea = 0;
	}

		// Is there any data ?
		if ( SZ_GetArea > 0 ) {

			m_Buffer.resize( SZ_GetArea );

			// We try to accept the user's filter
			if ( m_FncFilter ) {
					
				std::vector<char_type> cpyBuffer( m_Buffer );

				str_filter_type ResFilter { m_FncFilter ( cpyBuffer.data(), SZ_GetArea, m_StrFilter, m_SzFilter ) };

				// The characters is valid - save it
				if ( !ResFilter.empty() ) {

					SZ_GetArea = ResFilter.size();

					// Copy filtered symbols instead of non-filtered symbols in the get area !!!
					std::memcpy( m_Buffer.data(), ResFilter.data(), SZ_GetArea );

				}

				// The characters isn't valid - exit
				else 
					return traits_type::eof();
				
			}

			// Update pointers to the get area
			setg( m_Buffer.data(), m_Buffer.data(), m_Buffer.data() + SZ_GetArea );
		}

return *gptr() != traits_type::eof() ? *gptr() : traits_type::eof();
}

# endif
