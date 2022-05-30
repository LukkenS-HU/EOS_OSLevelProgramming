add_executable(HBO_TI_EOS_OLP_1 main.cpp
        SysCalls.cpp SysCalls.h
        File.cpp File.h
        Util.h Util.cpp)

target_link_libraries(HBO_TI_EOS_OLP_1 fmt)

target_compile_definitions(HBO_TI_EOS_OLP_1 PRIVATE
        RC_PATH=".sshellrc"
        COMMAND_NOT_FOUND_MESSAGE="Command '{}' not found!")
