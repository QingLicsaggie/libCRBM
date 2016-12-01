include_directories(${PROJECT_SOURCE_DIR}/src)
link_directories(${PROJECT_BINARY_DIR}/lib)

set(SRC
  CRBM.cpp
  CRBMIO.cpp
  CRBMController.cpp
  CRBMTrainer.cpp
  Random.cpp
  Discretiser.cpp

  ext/progressbar.c
)

if(APPLE)
  add_library(CRBM SHARED ${SRC})
  install(TARGETS CRBM LIBRARY DESTINATION lib)
else(APPLE)
  add_library(CRBM STATIC ${SRC})
endif(APPLE)

target_link_libraries(CRBM ${Boost_LIBRARIES} Matrix m Entropy++ glog ncurses)

add_executable(train main_train.cpp)
target_link_libraries(train CRBM gflags)
