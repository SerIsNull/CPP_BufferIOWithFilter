// This test checking the reading from source file with help of byffer_type.
// This test for functions such as underflow

# include "fixture_gtest.hpp"
# include <memory>
# include <istream>

// positive test
//
// result: The data of the sources file must be equal the getting data of user.
//
// 1) Reading the data from the buffer. On the same time the buffer reads the data from the source file.
// If the data in the source file is empty then the user's data which he got is also empty.
//
// Act:
// - to create the file with mode in;
// - to create an object which will be associated with this file;
// - to join the inputstream to inputbuffer;
// - to read the data from buffer. And then the buffer reads they from the source file. 
// - to check teh user's data. The data in the source file must be equal to the user's data which user got.

TEST( ReadEnglishWithoutFilter, OneStrReturnOneStr ) {
	
	std::string Result;

	test::create_files( test::engOneStr );

	test::buf_type Buf( test::validPath, test::mode::in, test::validSZ );

	std::istream is(&Buf);

	char C;
	while (is.get(C)) Result.push_back(C);

	ASSERT_TRUE( test::engOneStr == Result );
	
	test::delete_files();	
}

TEST( ReadEnglishWithoutFilter, TwoStrReturnTwoStr ) {

	std::string Result;

	test::create_files( test::engTwoStr );

	test::buf_type Buf( test::validPath, test::mode::in, test::validSZ );

	std::istream is(&Buf);

	char C;
	while (is.get(C)) Result.push_back(C);

	ASSERT_TRUE( test::engTwoStr == Result );
	
	test::delete_files();
}


TEST( ReadRussianWithoutFilter, OneStrReturnOneStr ) {
	
	std::string Result;

	test::create_files( test::rusOneStr );

	test::buf_type Buf( test::validPath, test::mode::in, test::validSZ );

	std::istream is(&Buf);

	char C;
	while (is.get(C)) Result.push_back(C);

	ASSERT_TRUE( test::rusOneStr == Result );
	
	test::delete_files();	
}

TEST( ReadRussianWithoutFilter,  TwoStrReturnTwoStr ) {

	std::string Result;

	test::create_files( test::rusTwoStr );

	test::buf_type Buf( test::validPath, test::mode::in, test::validSZ );

	std::istream is(&Buf);

	char C;
	while (is.get(C)) Result.push_back(C);

	ASSERT_TRUE( test::rusTwoStr == Result );
	
	test::delete_files();
}

TEST( ReadEmptyWithoutFilter, EmptyStrReturnEmptyStr ) {

	std::string Result;

	test::create_files( test::emptyStr );

	test::buf_type Buf( test::validPath, test::mode::in, test::validSZ );

	std::istream is(&Buf);

	is >> Result;

	ASSERT_TRUE( test::emptyStr == Result );
	
	test::delete_files();
}

// result: The data of the sources file must be equal the getting data of user.

// 2. But if the user's filter is  is filtered then the result depends on the user's filter.
// result : The filtered data or empty str.

// Act:
// - to create the file with mode in;
// - to create an object which will be associated with this file;
// - to set filter like a user's function;
// - to join the inputstream to inputbuffer;
// - to read the data from buffer. And then the buffer reads they from the source file. 
// - to check the user's data. The user's data must be filtered. 

TEST( ReadEnglishWithFilter, OneStrReturnNewStr ) {
	
	// Get Result directly ( without buffer )
	std::string ResOfFunction = test::filter ( test::engOneStr, 
			                           test::sz_engOneStr,
						   test::engStr_Filter,
						   test::sz_engFilter
						 );

	test::create_files( test::engOneStr );

	test::buf_type Buf( test::validPath, test::mode::in, test::sz_engOneStr);

	Buf.set_filter ( test::filter, test::engStr_Filter, test::sz_engFilter);

	std::istream is(&Buf);

	std::string ResOfReading;

	// Get result with buffer's help
	char C;
	while (is.get(C)) ResOfReading.push_back(C);
	// remove EOF 
	ResOfReading.pop_back();

	ASSERT_TRUE ( ResOfReading == ResOfFunction );
	
	test::delete_files();	
}


TEST( ReadEnglishWithFilter, TwoStrReturnNewStr ) {
	
	// Get Result directly ( without buffer )
	std::string ResOfFunction = test::filter ( test::engTwoStr, 
			                           test::sz_engTwoStr,
						   test::engStr_Filter,
						   test::sz_engFilter
						 );

	test::create_files( test::engTwoStr );

	test::buf_type Buf( test::validPath, test::mode::in, test::sz_engTwoStr);

	Buf.set_filter ( test::filter, test::engStr_Filter, test::sz_engFilter);

	std::istream is(&Buf);

	std::string ResOfReading;

	// Get result with buffer's help
	char C;
	while (is.get(C)) ResOfReading.push_back(C);
	// remove EOF 
	ResOfReading.pop_back();

	ASSERT_TRUE ( ResOfReading == ResOfFunction );
	
	test::delete_files();	
}


TEST( ReadRussianWithFilter, OneStrReturnNewStr ) {
	
	// Get Result directly ( without buffer )
	std::string ResOfFunction = test::filter ( test::rusOneStr, 
			                           test::sz_rusOneStr,
						   test::rusStr_Filter,
						   test::sz_rusFilter
						 );


	test::create_files( test::rusOneStr );

	test::buf_type Buf( test::validPath, test::mode::in, test::sz_rusOneStr);

	Buf.set_filter ( test::filter, test::rusStr_Filter, test::sz_rusFilter );

	std::istream is(&Buf);

	std::string ResOfReading;

	// Get result with buffer's help
	char C;
	while (is.get(C)) ResOfReading.push_back(C);
	
	// remove EOF 
	ResOfReading.pop_back();

	ASSERT_TRUE ( ResOfReading == ResOfFunction );
	
	test::delete_files();	
}


TEST( ReadRussianWithFilter, TwoStrReturnNewStr ) {
	
	// Get Result directly ( without buffer )
	std::string ResOfFunction = test::filter ( test::engTwoStr, 
			                           test::sz_engTwoStr,
						   test::engStr_Filter,
						   test::sz_engFilter
						 );

	test::create_files( test::engTwoStr );

	test::buf_type Buf( test::validPath, test::mode::in, test::sz_engTwoStr);

	Buf.set_filter ( test::filter, test::engStr_Filter, test::sz_engFilter);

	std::istream is(&Buf);

	std::string ResOfReading;

	// Get result with buffer's help
	char C;
	while (is.get(C)) ResOfReading.push_back(C);
	// remove EOF 
	ResOfReading.pop_back();

	ASSERT_TRUE ( ResOfReading == ResOfFunction );
	
	test::delete_files();	
}

TEST( ReadRussinaWithFilter, OneStrReturnEmptyStr ) {
	
	std::string ResOfReading;

	test::create_files( test::rusOneStr );

	test::buf_type Buf( test::validPath, test::mode::in, test::validSZ );

	Buf.set_filter ( test::filter, test::engStr_Filter, test::sz_engFilter);

	std::istream is(&Buf);

	is >> ResOfReading;

	ASSERT_TRUE( ResOfReading.empty() );
	
	test::delete_files();
}
