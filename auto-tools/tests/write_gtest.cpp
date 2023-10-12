// This test checking the writing to the destination file with help of byffer_type.
// This test for functions such as xsgetn() and overflow()

# include "fixture_gtest.hpp"
# include <memory>
# include <istream>

// positive test
//
// result: The data user's data must be equal to the data in the destination file
//
// 1) Writing the data to the buffer. And then the data from buffer writes into the destination file.
// If the data from user is empty then the data in the destination file is also empty.
//
// Act:
// - to create the file with modes such as: out, out | app, out | trunc;
// - to create an object which will be associated with this file;
// - to join the outputstream to outputbuffer;
// - to write user's data into the buffer and then it writes into the destination file.
// - to check the destination file. The data into this file must be equal to the user's data.

TEST( WriteEnglishWithoutFilter, OneStrReturnOneStr ) {
	
	// Write the data 
	{
	test::buf_type Buf( test::validPath, test::mode::out, test::sz_engOneStr);

	std::ostream os(&Buf);

	os << test::engOneStr;

	os.flush();
	}

	// Check
	std::string Result;

	std::fstream File( test::validPath );

	char C;
	while( File.get(C) && C != std::char_traits<test::ch_type>::eof() ) Result.push_back(C);
	
	ASSERT_TRUE( test::engOneStr == Result );
	
	test::delete_files();
}


TEST( WriteEnglishWithoutFilter, TwoStrReturnTwoStr ) {
	
	// Write the data 
	{
	test::buf_type Buf( test::validPath, test::mode::out, test::sz_engTwoStr );

	std::ostream os(&Buf);

	os << test::engTwoStr;

	os.flush();
	}

	// Check
	std::string Result;

	std::fstream File( test::validPath );

	char C;
	while( File.get(C) && C != std::char_traits<test::ch_type>::eof() ) Result.push_back(C);
	
	ASSERT_TRUE( test::engTwoStr == Result );
	
	test::delete_files();
}


TEST( WriteRussianWithoutFilter, OneStrReturnOneStr ) {
	
	// Write the data 
	{
	test::buf_type Buf( test::validPath, test::mode::out, test::sz_rusOneStr);

	std::ostream os(&Buf);

	os << test::rusOneStr;

	os.flush();
	}

	// Check
	std::string Result;

	std::fstream File( test::validPath );

	char C;
	while( File.get(C) && C != std::char_traits<test::ch_type>::eof() ) Result.push_back(C);
	
	ASSERT_TRUE( test::rusOneStr == Result );
	
	test::delete_files();
}


TEST( WriteRussianWithoutFilter, TwoStrReturnTwoStr ) {
	
	// Write the data 
	{
	test::buf_type Buf( test::validPath, test::mode::out, test::sz_rusTwoStr);

	std::ostream os(&Buf);

	os << test::rusTwoStr;

	os.flush();
	}

	// Check
	std::string Result;

	std::fstream File( test::validPath );

	char C;
	while( File.get(C) && C != std::char_traits<test::ch_type>::eof() ) Result.push_back(C);
	
	ASSERT_TRUE( test::rusTwoStr == Result );
	
	test::delete_files();
}


// positive test
//
// result: The data user's data must be equal to the data in the destination file
//
// 2) Writing the data to the buffer. And then the data from buffer writes into the destination file with
// filter.If the data from user is empty then the data in the destination file is also empty.
//
// Act:
// - to create the file with modes such as: out, out | app, out | trunc;
// - to create an object which will be associated with this file;
// - set filter;
// - to join the outputstream to outputbuffer;
// - to write user's data into the buffer and then it writes into the destination file;
// - to check the destination file. The data into this file must be equal to the user's data.

TEST( WriteEnglishWithFilter, OneStrReturnNewStr ) {
	
	// Get result directly ( without buffer )
	std::string ResOfFunction = test::filter ( test::engOneStr, 
			                           test::sz_engOneStr,
						   test::engStr_Filter,
						   test::sz_engFilter
						 );

	// Write the data 
	{
	
	test::buf_type Buf( test::validPath, test::mode::out, test::sz_engTwoStr);

	Buf.set_filter( test::filter, test::engStr_Filter, test::sz_engFilter);

	std::ostream os(&Buf);

	os << test::engOneStr;

	os.flush();
	}

	// Check
	std::string ResOfWriting;

	std::fstream File( test::validPath );

	char C;
	while( File.get(C) && C != std::char_traits<test::ch_type>::eof() ) ResOfWriting.push_back(C);
	
	ASSERT_TRUE( ResOfWriting == ResOfFunction );
	
	test::delete_files();
}


TEST( WriteEnglishWithFilter, TwoStrReturnNewStr ) {
	
	// Get result directly ( without buffer )
	std::string ResOfFunction = test::filter ( test::engTwoStr, 
			                           test::sz_engTwoStr,
						   test::engStr_Filter,
						   test::sz_engFilter
						 );

	// Write the data 
	{
	
	test::buf_type Buf( test::validPath, test::mode::out, test::sz_engTwoStr);

	Buf.set_filter( test::filter, test::engStr_Filter, test::sz_engFilter);

	std::ostream os(&Buf);

	os << test::engTwoStr;

	os.flush();
	}

	// Check
	std::string ResOfWriting;

	std::fstream File( test::validPath );

	char C;
	while( File.get(C) && C != std::char_traits<test::ch_type>::eof() ) ResOfWriting.push_back(C);
	
	ASSERT_TRUE( ResOfWriting == ResOfFunction );
	
	test::delete_files();
}

TEST( WriteRussianWithFilter, OneStrReturnNewStr ) {
	
	// Get result directly ( without buffer )
	std::string ResOfFunction = test::filter ( test::rusOneStr, 
			                           test::sz_rusOneStr,
						   test::rusStr_Filter,
						   test::sz_rusFilter
						 );

	// Write the data 
	{
	
	test::buf_type Buf( test::validPath, test::mode::out, test::sz_rusOneStr);

	Buf.set_filter( test::filter, test::rusStr_Filter, test::sz_rusFilter);

	std::ostream os(&Buf);

	os << test::rusOneStr;

	os.flush();
	}

	// Check
	std::string ResOfWriting;

	std::fstream File( test::validPath );

	char C;
	while( File.get(C) && C != std::char_traits<test::ch_type>::eof() ) ResOfWriting.push_back(C);
	
	ASSERT_TRUE( ResOfWriting == ResOfFunction );
	
	test::delete_files();
}

TEST( WriteRussianWithFilter, TwoStrReturnNewStr ) {
	
	// Get result directly ( without buffer )
	std::string ResOfFunction = test::filter ( test::rusTwoStr, 
			                           test::sz_rusTwoStr,
						   test::rusStr_Filter,
						   test::sz_rusFilter
						 );

	// Write the data 
	{
	
	test::buf_type Buf( test::validPath, test::mode::out, test::sz_rusTwoStr);

	Buf.set_filter( test::filter, test::rusStr_Filter, test::sz_rusFilter);

	std::ostream os(&Buf);

	os << test::rusTwoStr;

	os.flush();
	}

	// Check
	std::string ResOfWriting;

	std::fstream File( test::validPath );

	char C;
	while( File.get(C) && C != std::char_traits<test::ch_type>::eof() ) ResOfWriting.push_back(C);
	
	ASSERT_TRUE( ResOfWriting == ResOfFunction );
	
	test::delete_files();
}


TEST( WriteRussinaWithFilter, OneStrReturnEmptyStr ) {

	// Write the data 
	{
	
	test::buf_type Buf( test::validPath, test::mode::out, test::sz_rusTwoStr);

	Buf.set_filter( test::filter, test::engStr_Filter, test::sz_engFilter);

	std::ostream os(&Buf);

	os << test::rusTwoStr;

	os.flush();
	}

	// Check
	std::string ResOfWriting;

	std::fstream File( test::validPath );

	File >> ResOfWriting;
		
	ASSERT_TRUE( ResOfWriting.empty() );
	
	test::delete_files();
}
