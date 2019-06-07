project(test1)

add_executable(test-app test.cpp)

install(TARGETS test-app RUNTIME DESTINATION ${PROJECT_NAME}/app)