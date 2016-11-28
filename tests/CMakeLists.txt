include_directories(${PROJECT_SOURCE_DIR}/src)
link_directories(${PROJECT_BINARY_DIR}/lib)

add_executable(rbm-tests        main.cpp rbm_test.cpp)
target_link_libraries(rbm-tests CRBM     cppunit dl)

add_executable(crbmcontroller-tests        main.cpp crbmcontroller_test.cpp)
target_link_libraries(crbmcontroller-tests CRBM     cppunit dl)

add_executable(discretiser-tests        main.cpp discretiser_test.cpp)
target_link_libraries(discretiser-tests CRBM     cppunit dl)

ADD_TEST(RBM             "${PROJECT_BINARY_DIR}/bin/rbm-tests")
ADD_TEST(CRBM-Controller "${PROJECT_BINARY_DIR}/bin/crbmcontroller-tests")
ADD_TEST(Discretiser     "${PROJECT_BINARY_DIR}/bin/discretiser-tests")
