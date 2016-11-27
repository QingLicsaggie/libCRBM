include_directories(${PROJECT_SOURCE_DIR}/src)
link_directories(${PROJECT_BINARY_DIR}/lib)

set(SRC
  RBM.cpp
  CRBM.cpp
  Random.cpp
)

if(APPLE)
  add_library(CRBM SHARED ${SRC})
  install(TARGETS CRBM LIBRARY DESTINATION lib)
else(APPLE)
  add_library(CRBM STATIC ${SRC})
endif(APPLE)

target_link_libraries(CRBM ${Boost_LIBRARIES} Matrix)

