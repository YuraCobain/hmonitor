# Standard drivers
add_subdirectory(gen_drivers/src)
add_subdirectory(mh_z19)

add_library(hm_drivers STATIC
	$<TARGET_OBJECTS:gen_drivers>
	$<TARGET_OBJECTS:mh_z19_driver>
)

install(TARGETS hm_drivers DESTINATION lib${LIB_SUFFIX})

