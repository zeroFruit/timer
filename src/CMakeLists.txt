add_library(linkedlist linkedlist.c)

set_target_properties(sample PROPERTIES PUBLIC_HEADER linkedlist.h)

install(TARGETS linkedlist
		RUNTIME DESTINATION bin
		LIBRARY DESTINATION lib
		ARCHIVE DESTINATION lib)