// This test checking the creation an object of the buffer_type.
// This test for constructor of bufer_type.

# include "fixture_gtest.hpp" // using for test 
# include <memory>
# include <iostream>


// positive:
//
// results: A creation object of buffer_type
//
// 1) The file which will be associated with input buffer must be exist.
// - pass the valid-path to the file;
// 	
// 2) The file which will be associated with output buffer isn't necessary must be exist.
// - pass the valid-path and invalid-path to the file ( The path not empty)
//
// 3) The buffer will be created with valid modes.
// - pass the modes such as: in, out, out | app, out | trunc;
//
// 4) The size of buffer must be greater then zero.
// - pass the size > 0.


TEST( ConstructorPositiveTest, PassValidArgsReturnBufferWasCreated ) {
       
       test::create_files();

       std::unique_ptr<test::buf_type> ptrObj {nullptr};

       // ( 1 ) ( 4.1 )
       ptrObj = std::make_unique<test::buf_type>( test::validPath, test::mode::in, test::validSZ );
       ASSERT_TRUE( ptrObj != nullptr);

       // ( 2.1 ) ( 3.1 ) ( 4.2 )
       ptrObj = std::make_unique<test::buf_type>( test::validPath, test::mode::out, test::validSZ );
       ASSERT_TRUE( ptrObj != nullptr);

       // ( 2.3 ) ( 3.3 ) ( 4.4 )
       ptrObj = std::make_unique<test::buf_type>(test::validPath, test::mode::out | test::mode::app, test::validSZ );
       ASSERT_TRUE( ptrObj != nullptr);

       // ( 2.6 ) ( 3.6 ) ( 4.7 )
       ptrObj = std::make_unique<test::buf_type>(test::validPath, test::mode::out | test::mode::trunc, test::validSZ );
       ASSERT_TRUE( ptrObj != nullptr);

       // ( 2.2 ) ( 3.2 ) ( 4.3 )
       ptrObj = std::make_unique<test::buf_type>(test::invalidPath, test::mode::out, test::validSZ );
       ASSERT_TRUE( ptrObj != nullptr);

       // ( 2.4 ) ( 3.4 ) ( 4.5 )
       ptrObj = std::make_unique<test::buf_type>(test::invalidPath, test::mode::out | test::mode::app, test::validSZ );
       ASSERT_TRUE( ptrObj != nullptr);

       // ( 2.5 ) ( 3.5 ) ( 4.6 )
       ptrObj = std::make_unique<test::buf_type>(test::invalidPath, test::mode::out | test::mode::trunc, test::validSZ );
       ASSERT_TRUE( ptrObj != nullptr);

       test::delete_files();
} 


// negative.
//
// results : An exception type of std::invalid_argument, std::ios_base_failure, std::lenght_error
// and object was not created.
//
// 1) The file which will be associated with input buffer inst't exist;
// - pass the invalid-path to the file;
//
// 2) The file which will be associated  with output buffer is called "".
// - pass the empty path to the file;
//
// 3) The buffer will be created with invalid modes.
// - pass the modes such as : in | app, in | trunc, in | out, in | binary, in | ate,
// 			      
// 			      binary, binary | app, binary | trunc, binary | out,
// 			      binary | ate,
//
// 			      out | ate,
//
// 			      app | trunc
// 4) The size of buffer must be equal zero or largest then zero.
// - pass the size < 0 and == 0.

// invalid path
TEST( ConstructorNegativeTest, PassInvaliadPathReturnExceptionBufferWasNotCreated ){
	
       test::create_files();

       std::unique_ptr<test::buf_type> ptrObj {nullptr};

       ASSERT_THROW(
         ptrObj = std::make_unique<test::buf_type>(test::invalidPath, test::mode::in, test::validSZ), 
	 std::ios_base::failure
       );
       
         ASSERT_TRUE( ptrObj == nullptr );

	 test::delete_files();
}

// empty path
TEST( ConstructorNegativeTest, PassEmptyPathReturnExceptionBufferWasNotCreated ){

       test::create_files();

       std::unique_ptr<test::buf_type> ptrObj {nullptr};

       ASSERT_THROW(
         ptrObj = std::make_unique<test::buf_type>(test::emptyPath, test::mode::in, test::validSZ), 
	 std::ios_base::failure
       );
 
       ASSERT_TRUE( ptrObj == nullptr );

       test::delete_files();
}


// invalid mode
TEST( ConstructorNegativeTest, PassInvalidModeReturnExceptionBufferWasNotCreated ){

       test::create_files();
	       
       std::unique_ptr<test::buf_type> ptrObj {nullptr};

       	ASSERT_THROW(
         	ptrObj = std::make_unique<test::buf_type>(test::validPath, test::mode::in | test::mode::app, test::validSZ), 
	 	std::invalid_argument
       		    );

       ASSERT_TRUE( ptrObj == nullptr );

       ASSERT_THROW(
         ptrObj = std::make_unique<test::buf_type>(test::validPath, test::mode::in | test::mode::trunc, test::validSZ), 
	 std::ios_base::failure
       );

       ASSERT_TRUE( ptrObj == nullptr );

       ASSERT_THROW(
         ptrObj = std::make_unique<test::buf_type>(test::validPath, test::mode::in | test::mode::out, test::validSZ), 
	 std::invalid_argument
       );

       ASSERT_TRUE( ptrObj == nullptr );
         
       ASSERT_THROW(
         ptrObj = std::make_unique<test::buf_type>(test::validPath, test::mode::in | test::mode::binary, test::validSZ), 
	 std::invalid_argument
       );

       ASSERT_TRUE( ptrObj == nullptr );

       ASSERT_THROW(
         ptrObj = std::make_unique<test::buf_type>(test::validPath, test::mode::in | test::mode::ate, test::validSZ), 
	 std::invalid_argument
       );

       ASSERT_TRUE( ptrObj == nullptr );

       ASSERT_THROW(
         ptrObj = std::make_unique<test::buf_type>(test::validPath, test::mode::binary, test::validSZ), 
	 std::ios_base::failure
       );

       ASSERT_TRUE( ptrObj == nullptr );

       ASSERT_THROW(
         ptrObj = std::make_unique<test::buf_type>(test::validPath, test::mode::binary | test::mode::app, test::validSZ), 
	 std::invalid_argument
       );

       ASSERT_TRUE( ptrObj == nullptr );

       ASSERT_THROW(
         ptrObj = std::make_unique<test::buf_type>(test::validPath, test::mode::binary | test::mode::trunc, test::validSZ), 
	 std::ios_base::failure
       );

       ASSERT_TRUE( ptrObj == nullptr );

       ASSERT_THROW(
         ptrObj = std::make_unique<test::buf_type>(test::validPath, test::mode::binary | test::mode::out, test::validSZ), 
	 std::invalid_argument
       );

       ASSERT_TRUE( ptrObj == nullptr );

       ASSERT_THROW(
         ptrObj = std::make_unique<test::buf_type>(test::validPath, test::mode::ate | test::mode::out, test::validSZ), 
	 std::invalid_argument
       );

       ASSERT_TRUE( ptrObj == nullptr );

       ASSERT_THROW(
         ptrObj = std::make_unique<test::buf_type>(test::validPath, test::mode::app | test::mode::trunc, test::validSZ), 
	 std::ios_base::failure
       );

       ASSERT_TRUE( ptrObj == nullptr );
       
       test::delete_files();
}

// invalid size of buffer
TEST( ConstructorNegativeTest, PassInvalidSizeReturnExceptionBufferWasNotCreated ){
 
       test::create_files();

       std::unique_ptr<test::buf_type> ptrObj { nullptr };

       ASSERT_THROW(
         ptrObj = std::make_unique<test::buf_type>(test::validPath, test::mode::out, test::invalidSZ1), 
	 std::length_error
       );

       ASSERT_TRUE( ptrObj == nullptr );

       ASSERT_THROW(
         ptrObj = std::make_unique<test::buf_type>(test::validPath, test::mode::in, test::invalidSZ2), 
	 std::invalid_argument
       );

       ASSERT_TRUE( ptrObj == nullptr );

       test::delete_files();
}
