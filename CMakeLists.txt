file(GLOB HEADERS "include/eosio/acc_check_plugin/*.hpp")
add_library( acc_check_plugin
             acc_check_plugin.cpp
             ${HEADERS} )

target_link_libraries( acc_check_plugin chain_plugin http_plugin appbase fc )
target_include_directories( acc_check_plugin PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )
