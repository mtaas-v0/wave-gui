
cmake_policy(SET CMP0079 NEW)

add_subdirectory(imgui)


# 3. Explicitly link the vcpkg glfw target to the imgui target
if(TARGET imgui)
    target_link_libraries(imgui PRIVATE glfw)
else()
    # If the submodule uses a different target name (e.g., ImGui::ImGui)
    target_link_libraries(ImGui PRIVATE glfw)
endif()
