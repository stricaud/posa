include_directories(AFTER "include/" ${POSA_INCLUDE_DIRS})

set(LIBPOSA_SRC
  object.c
  pack.c
  posa.c
  parser/pos-instructions.c
  parser/pos-parser.c
  parser/pos-table.c
  parser/pos-table-read.c
  unpack.c
  utils.c
  )

set(POSA_LINK_LIBRARIES
${POSA_LINK_LIBRARIES}
  )

# Our dynamic library
add_library(posa SHARED ${LIBPOSA_SRC})
set_target_properties(posa PROPERTIES SOVERSION 1)
target_link_libraries(posa ${POSA_LINK_LIBRARIES})
