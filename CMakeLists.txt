cmake_minimum_required(VERSION 3.19)

project(Isoberry)

# sudo dnf groupinstall "Development Tools" "Development Libraries"
# sudo dnf install glew-devel SDL2-devel SDL2_image-devel glm-devel freetype-devel
# sudo dnf install g++
# sudo dnf install enet-devel.x86_64
set(CMAKE_CXX_STANDARD 20)
set(ISOBERRY_VERSION 0.1)

if(${CMAKE_SYSTEM} MATCHES "Linux")
    set(LINUX 1)
endif(${CMAKE_SYSTEM} MATCHES "Linux")

file (GLOB MY_SRC
        "header/*.h"
        "main.cpp"
        "utility/*.cpp"
        "utility/*.h"
        "utility/settings/*.cpp"
        "utility/settings/*.h"
        "assets/*.h"
        "game/objects/collision/*.cpp"
        "game/objects/collision/*.h"
        "game/objects/animation/*.cpp"
        "game/objects/animation/*.h"
        "game/objects/*.cpp"
        "game/objects/*.h"
        "game/editor/*.cpp"
        "game/editor/*.h"
        "game/tool/*.cpp"
        "game/tool/*.h"
        "game/tool/sprite_saving/*.cpp"
        "game/tool/sprite_saving/*.h"
        "game/tool/draw_sprites/*.cpp"
        "game/tool/draw_sprites/*.h"
        "game/tool/layering/*.cpp"
        "game/tool/layering/*.h"
        "game/tool/input/*.cpp"
        "game/tool/input/*.h"
        "game/tool/art/*.cpp"
        "game/tool/art/*.h"
        "game/level/*.cpp"
        "game/level/*.h"
        "game/*.cpp"
        "game/*.h")

if (WIN32 OR LINUX)
    add_executable(Isoberry ${MY_SRC})
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/assets/)
endif (WIN32 OR LINUX)

if (APPLE)
    add_compile_options(-stdlib=libc++ -framework Carbon)

    set(CUR_TARGET Isoberry)
    set(MACOSX_BUNDLE_ICON_FILE isoberry.icns)
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Isoberry.app/Contents/assets)

    set(myApp_ICON ${CMAKE_CURRENT_SOURCE_DIR}/app/icon/isoberry.icns)
    set_source_files_properties(${myApp_ICON} PROPERTIES
            MACOSX_PACKAGE_LOCATION "Resources")

    add_executable(${CUR_TARGET} MACOSX_BUNDLE ${MY_SRC} ${myApp_ICON})
    set_target_properties(${CUR_TARGET} PROPERTIES
            BUNDLE True
            MACOSX_BUNDLE_GUI_IDENTIFIER my.domain.style.identifier.${CUR_TARGET}
            MACOSX_BUNDLE_BUNDLE_NAME ${CUR_TARGET}
            MACOSX_BUNDLE_BUNDLE_VERSION ${ISOBERRY_VERSION}
            MACOSX_BUNDLE_SHORT_VERSION_STRING ${ISOBERRY_VERSION}
            )
endif(APPLE)

if (UNIX)
    # X11
    if(LINUX)
        find_package(X11 REQUIRED)
        include_directories(${X11_INCLUDE_DIR})
        link_directories(${X11_LIBRARIES})
        target_link_libraries(Isoberry ${X11_LIBRARIES})
    endif(LINUX)
    # GLUT
    if(APPLE)
        find_package(GLUT REQUIRED)
        include_directories(${GLUT_INCLUDE_DIR})
        link_directories(${GLUT_LIBRARIES})
        target_link_libraries(Isoberry ${GLUT_LIBRARIES})
    endif(APPLE)

    find_package(OpenGL REQUIRED)
    include_directories(${OPENGL_INCLUDE_DIR})
    link_directories(${OPENGL_LIBRARIES})
    target_link_libraries(Isoberry ${OPENGL_LIBRARIES})

    set(THREADS_PREFER_PTHREAD_FLAG ON)
    find_package(Threads REQUIRED)
    target_link_libraries(Isoberry Threads::Threads)

endif (UNIX)

#target_link_directories(Isoberry ${ENET_LIBRARIES})