# Standard drivers
add_subdirectory(src)

add_library(hm_drivers STATIC
	$<TARGET_OBJECTS:gen_drivers>
)

install(TARGETS hm_drivers DESTINATION lib${LIB_SUFFIX})

