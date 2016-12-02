include_directories(${PROJECT_SOURCE_DIR}/src)
link_directories(${PROJECT_BINARY_DIR}/lib)

add_executable(crbm-tests        main.cpp crbm_test.cpp)
target_link_libraries(crbm-tests CRBM     cppunit dl)

add_executable(crbmio-tests        main.cpp crbmio_test.cpp)
target_link_libraries(crbmio-tests CRBM     cppunit dl)

add_executable(crbmcontroller-tests        main.cpp crbmcontroller_test.cpp)
target_link_libraries(crbmcontroller-tests CRBM     cppunit dl)

add_executable(discretiser-tests        main.cpp discretiser_test.cpp)
target_link_libraries(discretiser-tests CRBM     cppunit dl)

ADD_TEST(CRBM            "${PROJECT_BINARY_DIR}/bin/crbm-tests")
ADD_TEST(CRBMIO          "${PROJECT_BINARY_DIR}/bin/crbmio-tests")
ADD_TEST(CRBM-Controller "${PROJECT_BINARY_DIR}/bin/crbmcontroller-tests")
ADD_TEST(Discretiser     "${PROJECT_BINARY_DIR}/bin/discretiser-tests")
