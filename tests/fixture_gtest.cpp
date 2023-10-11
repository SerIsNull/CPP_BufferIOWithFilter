# include "fixture_gtest.hpp"

// path to the file
const char *test::validPath   = "./File_test.txt" ;
const char *test::invalidPath = "./Not_exist.txt" ;
const char *test::emptyPath   = "" ;


// size of buffer
const test::buf_type::pos_type test::validSZ    { 33 };
const test::buf_type::pos_type test::invalidSZ1 { -2 };
const test::buf_type::pos_type test::invalidSZ2 {  0 };

// some text
const char *test::engOneStr { "Hello, this is a test str" };
const char *test::engTwoStr { "Hello, this is first str!\n This is the second str!" };
const char *test::rusOneStr { "Привет это тестовая строка" };
const char *test::rusTwoStr { "Привет, это первая строка!\n Это вторая строка!" };
const char *test::emptyStr  { "" };

// size of text
test::pos_type test::sz_engOneStr  = strlen(engOneStr);
test::pos_type test::sz_rusOneStr  = strlen(rusOneStr);
test::pos_type test::sz_engTwoStr  = strlen(engTwoStr);
test::pos_type test::sz_rusTwoStr  = strlen(rusTwoStr);

// value of filter
test::str_filter_type test::engStr_Filter[] {"Hello", "Str"};
test::str_filter_type test::rusStr_Filter[] {"Привет","строка"};
test::sz_filter_type test::sz_engFilter { sizeof(test::engStr_Filter)/ sizeof(test::engStr_Filter[0])};
test::sz_filter_type test::sz_rusFilter { sizeof(test::rusStr_Filter)/ sizeof(test::rusStr_Filter[0])};

// func filter
test::str_filter_type test::filter( const test::ch_type   *pBuffer   ,
				    test::pos_type 	   SZ_Buffer ,	
		                    test::str_filter_type *ArrFilters,
				    test::sz_filter_type   SZ) {
	
	// The str for filtering
	std::basic_string<test::ch_type> srcStr( pBuffer, SZ_Buffer);

	// The result str
	std::basic_string<test::ch_type> resStr(srcStr.size(), ' ');

	// Position of valid token
	std::basic_string<test::ch_type>::size_type posFnd{ 0 };

	// Try to filter the src str
	for(size_t i {0}; i < SZ; ) {

		posFnd = srcStr.find( ArrFilters[i] );

		if ( posFnd != std::basic_string<test::ch_type>::npos ) {
			resStr.replace( posFnd, ArrFilters[i].size(), ArrFilters[i]);

			// Clear finded token in source str
			srcStr.replace(posFnd, ArrFilters[i].size(), ArrFilters[i].size(),' ');
		}

		else 
			i++;
	}

return resStr.empty() ? std::basic_string<test::ch_type>() : resStr;
}

// create files
bool test::create_files( const char *someText ){
		std::fstream f( validPath, test::mode::out );
		if ( f.is_open() ) {
			f << someText;
			f.close();
		}
return !f.is_open();
}

// delete files
void test::delete_files(){
		// if doesn't exist
		std::string CmdUpdate { std::string("touch ") + test::validPath + std::string(" ") + test::invalidPath };

		std::system( CmdUpdate.c_str() );
		// Delete
		std::string CmdDelete { std::string("rm ") + test::validPath + std::string(" ") + test::invalidPath };
		std::system( CmdDelete.c_str() );
}

// create object and stream
test::ReadTest::ReadTest( ) : buf( test::validPath, test::mode::in, test::validSZ ) {}
void test::ReadTest::SetUp() { }
void test::ReadTest::TearDown() { }
