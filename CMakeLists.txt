project(test1)


if (APPLE)
  add_executable(test-app test.cpp)

  install(TARGETS test-app RUNTIME DESTINATION ${PROJECT_NAME}/app)

  # add_subdirectory(doc)

  set_target_properties(test-app PROPERTIES 
    MACOSX_BUNDLE ON
    MACOSX_FRAMEWORK_IDENTIFIER  org.test.app
    MACOSX_BUNDLE_GUI_IDENTIFIER org.test.app
    MACOSX_BUNDLE_INFO_PLIST MacOSXBundleInfo.plist.in
    MACOSX_BUNDLE_LONG_VERSION_STRING "1.0.0.0"
    MACOSX_BUNDLE_SHORT_VERSION_STRING "1.0.0.0"
    MACOSX_BUNDLE_BUNDLE_VERSION "1.0.0.0"
  )
else()
  add_executable(test-app test_winhttp.cpp)
endif()