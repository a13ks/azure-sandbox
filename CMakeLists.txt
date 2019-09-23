project(test1)

add_executable(test-app test.cpp)

install(TARGETS test-app RUNTIME DESTINATION ${PROJECT_NAME}/app)


find_package(Doxygen)

if(DOXYGEN_FOUND)
  MESSAGE("Doxygen not found")
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
  add_custom_target(doc ALL
    COMMAND "${DOXYGEN_EXECUTABLE}" "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile"
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/.."
    COMMENT "Generating documentation with Doxygen" VERBATIM
  )
else()
  MESSAGE("Doxygen not found")
endif()

