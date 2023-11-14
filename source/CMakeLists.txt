set(target ${LIBRARY})

file(GLOB hdrs "*.h*" "${PROJ_INCLUDE}/*.h*")
file(GLOB srcs "*.cpp")

add_library(${target} STATIC ${srcs} ${hdrs})
target_link_libraries(${target} ${LIBRARY_DEPS})