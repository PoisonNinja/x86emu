target_sources(tinyx86
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/board.c
)

add_subdirectory(chipset)
add_subdirectory(cpu)
add_subdirectory(vga)
