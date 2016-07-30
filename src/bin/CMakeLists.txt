include_directories(AFTER ${POSA_INCLUDE_DIRS})

set(POSA_LINK_LIBRARIES
  ${POSA_LIBRARY}
)

set(POSADEBUG_SRC_FILES
  pos-debuger.c
)

set(POSAPOSA-PPRINT_SRC_FILES
  posa-pprint.c
)


add_executable(pos-debugger ${POSADEBUG_SRC_FILES})
target_link_libraries(pos-debugger ${POSA_LINK_LIBRARIES})

add_executable(posa-pprint ${POSAPOSA-PPRINT_SRC_FILES})
target_link_libraries(posa-pprint ${POSA_LINK_LIBRARIES})
