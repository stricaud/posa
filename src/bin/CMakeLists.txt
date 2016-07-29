include_directories(AFTER ${POSA_INCLUDE_DIRS})

set(POSA_LINK_LIBRARIES
  ${POSA_LIBRARY}
)

set(POSADEBUG_SRC_FILES
  pos-debuger.c
)

set(POSASIMPLE_SRC_FILES
  simple.c
)


add_executable(pos-debugger ${POSADEBUG_SRC_FILES})
target_link_libraries(pos-debugger ${POSA_LINK_LIBRARIES})

add_executable(simple ${POSASIMPLE_SRC_FILES})
target_link_libraries(simple ${POSA_LINK_LIBRARIES})
