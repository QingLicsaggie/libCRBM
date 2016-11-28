include_directories(${PROJECT_SOURCE_DIR}/src)
link_directories(${PROJECT_BINARY_DIR}/lib)

add_executable(rbm-tests        main.cpp rbm_test.cpp)
target_link_libraries(rbm-tests CRBM     cppunit dl)

add_executable(discretiser-tests        main.cpp discretiser_test.cpp)
target_link_libraries(discretiser-tests CRBM     cppunit dl)

ADD_TEST(RBM         "${PROJECT_BINARY_DIR}/bin/rbm-tests")
ADD_TEST(Discretiser "${PROJECT_BINARY_DIR}/bin/discretiser-tests")
