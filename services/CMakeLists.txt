# Services
add_subdirectory(lcd_service/src)
add_subdirectory(co2_monitor/src)

add_library(hm_services STATIC
	$<TARGET_OBJECTS:lcd_service>
	$<TARGET_OBJECTS:co2_monitor>
)

install(TARGETS hm_services DESTINATION lib${LIB_SUFFIX})

