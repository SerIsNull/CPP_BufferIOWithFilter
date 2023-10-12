# CPP_BufferIOWithFilter

-------------------------------
Description :
-------------------------------
	The class buffer_type may be used for input/output operations, i.e. for writing or reading data. 

-------------------------------
The feature :
-------------------------------
	This class allows that the user to define his own a data-filter.

-------------------------------
The structure of this type :
-------------------------------
	This type is inherited from std::basic_streambuf <char_type>. In this way, this type is used such members as:

	Inherted form std::basic_streambuf<char_type>

	- setg() - for set pointers to get area;
	- underflow() - for read data from source file and get it;
	- gptr() - for get the pointer to next character;

	- setp()    - for set pointers to put area;
	- eeptr()   - for get poiner to the end of put area;
	- pbase()   - for get pointer to the begin of put area;
	- xsputn()  - for writing to the put area;
	- overflow()- for writing data from put area to the destanation file;
	
	My members

	- constructor() - for create the object of buffer;
		- m_Mode   - mode of buffer;
		- m_Path   - path to the associated file;
		- m_Buffer - put or get area;
		- m_Data   - destanation file or source file;

	- set_filter ()	- for setting user's filter ;
		- m_FncFilter - pointer to the function of user's filter ; 
		- m_StrFilter - pointer to the value of user's filter ;
		- m_SzFilter  - size filter's value ;

	- is_clean_up_mess() - for show errors. It tries to clear and up;

-------------------------------
How does it work for reading data ?
-------------------------------

1) An object of buffer is created;
2) It joins to inputstream;
3) When we try to read the data from inputstream to some user's storage
then the function "underflow()" is called;
4) In this function the data is reading from source file to the buffer;
5) The data before getting to user's some storage is filtered
   if the user's filter is defined ( set_filter() );
6) In this way the filtering or not data is returned to the some user's storage.

The scheme for it:
	with filter:
Source file  -> Buffer -> Filter -> Data storage

	without filter:
Source file  -> Buffer -> Data storage


-------------------------------
How does it work for writing data ?
-------------------------------

1) An object of buffer is created;
2) It joins to outputstream;
3) When we try to write the data of some user's storage to outputstream
then the function xsputn() is called;
4) In this function the data is writing to the buffer and call "overflow()".
5) In the "overflow()" before writing the data to the destanation file is filtered
   if the user's filter is defined ( set_filter() );
6) In this way the filtering or not data is writing to the destanation file ( m_Path );


The scheme for it:

with filter 
	Data storage -> Buffer -> Filter -> Destination file

without filter
	Data storage -> Buffer -> Destination file

-------------------------------
The details of working : 
-------------------------------
	If you would like to get more information about working of buffer_type, you may see "include/buffer_type.hpp".
This file contains decloration and definition buffer_type.


-------------------------------
The tests :
-------------------------------

	For tests I used the framework called "googletest".
 I made the tests for reading data and writing data via my buffer with the filter and without it.
 - You can see they in this directory: /tests/reading_gtest.cpp or writing_gtest.cpp.
 I also made the test for create the buffer.
- You can see it in this directory: "/tests/constructor_gtest.cpp".

	The files such as "/tests/fixture_gtest.cpp" and "/tests/fixture_gtest.hpp" just contain useful stuf for testing.
If you need more information about it - you can see these files.
The results of testing present on a picture: /tests/TheResult.PNG

-------------------------------
The building :
-------------------------------

	So, I used in this progect the autotools for the building. 
 If you need to build this projects that to test it or to run the example you can use it.
 The steps for it:
- to make directory for building in the project-dir;
- to go to this directory;
- to run the script "./configure" from current directory. It's very important;
- to wait while the broject will be built;
- to run make utility in the current directory.
Plese, remember, if you need to do it again after the changes you'll need to copy
/examples and /tests into the directory "autotools"
For example:
- mkdir build;
- cp -pr examples ./autotools/ && cp -pr tests ./autotools/ && cp -pr include ./autotools/ 
- cd build;
- ../autotools/./configure;
- make;
- cd example;
- ./example.

	These steps are enough for the build of example.

	If you need to build the tests, you need to run make with keys -check.
This command build the tests and run they.
See the result: ./tests/TheResult.PNG
If you need to run it again you can use the comand make -check_TESTS
For example:
- make check;
- make -check-TESTS.
-------------------------------
How do you need to use it in your programm ?
-------------------------------
	So, the answer to this question is located in the directory : "/example".
 You can include the header file with buffer_type "/include/buffer_type.hpp"

1) ./example/fFilter_example.hpp - this file contains all the necessary for using:
	- #include "buffer_type.hpp" - for declaration and defininition of buffer_type < char_type >;
	- The namesapce "example" - for usability;
	- The function of user's filter.

2) ./example/fFilter_example.cpp - this file contains the definition of user's filter.

3) ./example/main_example.cpp - this file contains the using buffer_type for operatins such as:
	- for reading;
	- for writing;


