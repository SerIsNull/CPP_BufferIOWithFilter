// This file exists the useful things for test.
# ifndef __FIXTURE_HPP__
# define __FITURE_HPP__


# include "gtest/gtest.h"
# include "../include/buffer_type.hpp"

namespace test {
	using buf_type = buffer_type<char>; 
	using mode      = std::ios_base;
	using str_filter_type = buf_type::str_filter_type;
	using sz_filter_type  = buf_type::sz_filter_type;
	using ch_type = buf_type::char_type;
	using pos_type = buf_type::pos_type;


// path to the file
	extern const char *validPath,
		          *invalidPath,
	 	          *emptyPath;

// some text
	extern const char *engOneStr,
	       		  *rusOneStr,
	                  *engTwoStr,
			  *rusTwoStr,
			  *emptyStr;

// size of text
	extern pos_type sz_engOneStr,
	       		sz_rusOneStr,
			sz_engTwoStr,
			sz_rusTwoStr;

// func filter
str_filter_type filter( const ch_type *pBuff,
			      pos_type SZ_Buff,
		              str_filter_type *ArrFilters,
			      sz_filter_type SZ);

// value of filter
extern str_filter_type engStr_Filter[],
       		       rusStr_Filter[];
extern sz_filter_type sz_engFilter,
                      sz_rusFilter;

// size of buffer
	extern const buf_type::pos_type validSZ,
	                             invalidSZ1,
				     invalidSZ2;

// create or delete files
	bool create_files( const char *someText = "" );

	void delete_files();

// the fixture of class buffer_type for testing the methods
	class ReadTest : public ::testing::Test {

		protected:
			buf_type buf;

			void SetUp() override;

			void TearDown() override;

			ReadTest();
		      
	}; // end fixture

} // end namespace

# endif
