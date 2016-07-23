include_directories(AFTER ${POSA_INCLUDE_DIRS})

set(POSA_SRC_FILES
  pos-debuger.c
  )

set(POSA_LINK_LIBRARIES
${POSA_LIBRARY}
  )

add_executable(pos-debugger ${POSA_SRC_FILES})
target_link_libraries(pos-debugger ${POSA_LINK_LIBRARIES})
