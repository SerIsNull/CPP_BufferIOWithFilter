AUTOMAKE_OPTIONS = foreign

# For gtest lib
check_LTLIBRARIES     = libgtest.la
libgtest_la_SOURCES  = $(top_srcdir)/third-party/googletest/googletest/src/gtest-all.cc
libgtest_la_CPPFLAGS = -I$(top_srcdir)/third-party/googletest/googletest/include -I$(top_srcdir)/third-party/googletest/googletest -pthread

# For bin test
check_PROGRAMS = gtest

gtest_SOURCES  = main_gtest.cpp construct_gtest.cpp fixture_gtest.cpp read_gtest.cpp write_gtest.cpp

# Link the gtest lib to the bin
gtest_LDADD    = libgtest.la
gtest_CPPFLAGS = -I$(top_srcdir)/third-party/googletest/googletest/include -I$(top_srcdir)/third-party/googletest/googletest -pthread
gtest_LDFLAGS  = -pthread

# For Run gtest
TESTS = gtest
