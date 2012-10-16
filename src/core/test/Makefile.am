bin_PROGRAMS = \
	point_test \
	vector_test \
	point_vector_test \
	matrix_test \
	transform_test \
	transform_point_test \
	transform_vector_test

AM_LDFLAGS = --coverage
AM_CPPFLAGS = -I$(top_srcdir)/lib -I$(top_srcdir)/src \
              -g --coverage -Wall
LDADD = $(top_srcdir)/lib/libUnitTest++.a

point_test_SOURCES = main.cpp point_test.cpp ../point.cpp ../vector.cpp
vector_test_SOURCES = main.cpp vector_test.cpp ../vector.cpp
point_vector_test_SOURCES = main.cpp point_vector_test.cpp \
                            ../point.cpp \
                            ../vector.cpp
matrix_test_SOURCES = main.cpp matrix_test.cpp ../matrix.cpp
transform_vector_test_SOURCES = main.cpp transform_vector_test.cpp \
                                ../transform.cpp \
				 ../matrix.cpp ../point.cpp ../vector.cpp
transform_point_test_SOURCES = main.cpp transform_point_test.cpp \
                               ../transform.cpp \
		 	        ../matrix.cpp ../point.cpp ../vector.cpp
transform_test_SOURCES = main.cpp transform_test.cpp \
                         ../transform.cpp \
                         ../matrix.cpp ../point.cpp ../vector.cpp


check: all
	@echo 'Executing unittests for core ...'
	@for prog in $(bin_PROGRAMS); do \
		echo 'Executing '$$prog; \
		./$$prog; \
	done;

coverage: check
	@echo 'Generating coverage info for core ...'
	lcov --capture --directory ../ --output-file coverage.info
	lcov --remove coverage.info "/usr*" -o coverage.info
	lcov --remove coverage.info "*lib/UnitTest++*" -o coverage.info
	genhtml coverage.info --output-directory cov-html