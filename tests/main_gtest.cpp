# include "gtest/gtest.h"

int main( int cnt_arg, char **value_arg ) {


	// Init  the tests

	::testing::InitGoogleTest( &cnt_arg, value_arg );


// Running the test
return RUN_ALL_TESTS();
}
