# Standard drivers
add_subdirectory(ipc/src)

add_library(hm_middleware STATIC
	$<TARGET_OBJECTS:hm_msg_ch>
)

install(TARGETS hm_middleware DESTINATION lib${LIB_SUFFIX})

