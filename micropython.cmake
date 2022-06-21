add_library(usermod_ufastecdsa INTERFACE)

target_sources(usermod_ufastecdsa INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/moducrypto.c
)

target_include_directories(usermod_ufastecdsa INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries(usermod INTERFACE usermod_ufastecdsa)