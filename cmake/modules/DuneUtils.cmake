# This file is part of the dune-stuff project:
#   https://github.com/wwu-numerik/dune-stuff
# The copyright lies with the authors of this file (see below).
# License: BSD 2-Clause License (http://opensource.org/licenses/BSD-2-Clause)
# Authors:
#   Felix Schindler (2012 - 2015)
#   Rene Milk       (2010 - 2015)
#   Sven Kaulmann   (2013)

include(CheckCXXSourceCompiles)
include(DuneStuffMacros)
include(CTest)

function(TO_LIST_SPACES _LIST_NAME OUTPUT_VAR)
  set(NEW_LIST_SPACE)
  foreach(ITEM ${${_LIST_NAME}})
    set(NEW_LIST_SPACE ${NEW_LIST_SPACE} ${ITEM})
  endforeach()
  set(${OUTPUT_VAR} "${NEW_LIST_SPACE}" PARENT_SCOPE)
endfunction()

MACRO( DS_HEADERCHECK )
	ADD_CUSTOM_TARGET( ds_headercheck SOURCES ${ARGN} )
	FOREACH( HEADER ${ARGN} )
		string(REPLACE "/" "_" fn ${HEADER})
		SET( TEST_NAME "ds_headercheck_${fn}")
		configure_file( ${dune-stuff_SOURCE_DIR}/cmake/headercheck.cpp.in ${CMAKE_CURRENT_BINARY_DIR}/headercheck/${TEST_NAME}.cpp )
		ADD_LIBRARY( ${TEST_NAME} EXCLUDE_FROM_ALL STATIC ${CMAKE_CURRENT_BINARY_DIR}/headercheck/${TEST_NAME}.cpp )
		set_target_properties(${TEST_NAME} PROPERTIES LINKER_LANGUAGE CXX)
		add_dependencies( ds_headercheck ${TEST_NAME} )
	ENDFOREACH( HEADER )
ENDMACRO( HEADERCHECK )

MACRO( DEPENDENCYCHECK )
	ADD_CUSTOM_TARGET( dependenycheck SOURCES ${ARGN} )
	FOREACH( HEADER ${ARGN} )
		string(REPLACE "/" "_" fn ${HEADER})
		SET( TEST_NAME "dependenycheck_${fn}")
		TO_LIST_SPACES( CMAKE_CXX_FLAGS TEST_NAME_FLAGS )
		SET(XARGS ${TEST_NAME_FLAGS} -DHAVE_CONFIG_H -H -c ${HEADER} -w)
		ADD_CUSTOM_TARGET( ${TEST_NAME} + ${dune-stuff_SOURCE_DIR}/cmake/dependencyinfo.py ${CMAKE_CXX_COMPILER} ${XARGS} ${CMAKE_CURRENT_SOURCE_DIR} ${fn}.dep)
		add_dependencies( dependenycheck ${TEST_NAME} )
	ENDFOREACH( HEADER )
ENDMACRO( DEPENDENCYCHECK )

MACRO( ADD_CPPCHECK )
	find_program( CPPCHECK_BINARY NAMES cppcheck )
	IF( EXISTS ${CPPCHECK_BINARY} )
		SET(CPPINLINST ${CMAKE_CURRENT_BINARY_DIR}/cppcheck.files )
		IF( EXISTS ${CPPINLINST} )
			file(REMOVE  ${CPPINLINST} )
		ENDIF()
		FOREACH( SOURCEFILE ${ARGN} )
			FILE( APPEND  ${CPPINLINST}  "${SOURCEFILE}\n" )
		ENDFOREACH( SOURCEFILE )
		TO_LIST_SPACES( CPPCHECK_FLAGS_SPLIT ${CMAKE_CXX_FLAGS} )
		ADD_CUSTOM_TARGET(  cppcheck cppcheck --enable=all --xml --report-progress --file-list=${CPPINLINST}
				${CPPCHECK_FLAGS_SPLIT}  2>cppcheck.xml )
	ELSE( EXISTS ${CPPCHECK_BINARY} )
		MESSAGE( STATUS "Not adding cppcheck target because cppcheck executable not found" )
	ENDIF( EXISTS ${CPPCHECK_BINARY} )
ENDMACRO( ADD_CPPCHECK )

macro(BEGIN_TESTCASES)
# https://cmake.org/cmake/help/v3.0/module/FindGTest.html http://purplekarrot.net/blog/cmake-and-test-suites.html
	file( GLOB test_sources "${CMAKE_CURRENT_SOURCE_DIR}/*.cc" )
	foreach( source ${test_sources} )
		get_filename_component(testname ${source} NAME_WE)
    add_executable( test_${testname} ${source} ${COMMON_HEADER} )
    target_link_libraries( test_${testname} ${ARGN} ${COMMON_LIBS} ${GRID_LIBS} gtest_dune_stuff )
    add_test( NAME test_${testname} COMMAND ${CMAKE_CURRENT_BINARY_DIR}/test_${testname}
                   --gtest_output=xml:${CMAKE_CURRENT_BINARY_DIR}/test_${testname}.xml )
    # currently property seems to have no effect
    set_tests_properties(test_${testname} PROPERTIES TIMEOUT ${DUNE_TEST_TIMEOUT})
		list(APPEND testnames test_${testname} )
	endforeach( source )
endmacro(BEGIN_TESTCASES)

macro(END_TESTCASES)
    add_directory_test_target(_test_target)
    add_dependencies(${_test_target} ${testnames})
	add_custom_target(test_binaries DEPENDS ${testnames})
	add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} --timeout ${DUNE_TEST_TIMEOUT}
                  DEPENDS test_binaries)
endmacro(END_TESTCASES)

ENABLE_TESTING()
