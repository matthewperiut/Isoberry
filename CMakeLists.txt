cmake_minimum_required(VERSION 3.26)
project(Isoberry)

set(CMAKE_CXX_STANDARD 17)

set(OpenGL_GL_PREFERENCE GLVND)
set(qu3e_build_static TRUE)
add_subdirectory("submodules/qu3e")
add_subdirectory("submodules/olcPixelGameEngine")
add_subdirectory("submodules/olcNet")
add_subdirectory("submodules/fpng")
add_subdirectory("submodules/stbImage")

file (GLOB MY_SRC
        "src/header/*.h"
        "src/main.cpp"
        "src/utility/*.cpp"
        "src/utility/*.h"
        "src/utility/settings/*.cpp"
        "src/utility/settings/*.h"
        "src/objects/collision/*.cpp"
        "src/objects/collision/*.h"
        "src/objects/animation/*.cpp"
        "src/objects/animation/*.h"
        "src/objects/*.cpp"
        "src/objects/*.h"
        "src/editor/*.cpp"
        "src/editor/*.h"
        "src/tool/*.cpp"
        "src/tool/*.h"
        "src/tool/sprite_saving/*.cpp"
        "src/tool/sprite_saving/*.h"
        "src/tool/draw_sprites/*.cpp"
        "src/tool/draw_sprites/*.h"
        "src/tool/layering/*.cpp"
        "src/tool/input/*.cpp"
        "src/tool/input/*.h"
        "src/tool/art/*.cpp"
        "src/tool/art/*.h"
        "src/network/server/*.cpp"
        "src/network/server/*.h"
        "src/network/client/*.cpp"
        "src/network/client/*.h"
        "src/tool/memory/*.cpp"
        "src/tool/memory/*.h"
        "src/level/*.cpp"
        "src/level/*.h"
        "src/*.cpp"
        "src/*.h")


if (WIN32 OR LINUX)
    add_executable(Isoberry ${MY_SRC})
    file(COPY resources/assets/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/assets/)
endif (WIN32 OR LINUX)

if (WIN32)
    # Windows moment
    target_compile_definitions(Isoberry PRIVATE NOMINMAX)
endif (WIN32)

if (APPLE)
    add_compile_options(-stdlib=libc++ -framework Carbon)

    set(CUR_TARGET Isoberry)
    set(MACOSX_BUNDLE_ICON_FILE isoberry.icns)
    file(COPY resources/assets/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Isoberry.app/Contents/assets)

    set(myApp_ICON resources/app/icon/isoberry.icns)
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

    set(OPENSSL_INCLUDE_DIR /usr/local/opt/openssl)
    set(OPENSSL_CRYPTO_LIBRARY /usr/local/opt/openssl/lib)
endif(APPLE)

target_link_libraries(Isoberry
        PRIVATE qu3e)

target_include_directories(Isoberry PRIVATE
        "submodules/olcPixelGameEngine"
        "submodules/olcNet"
        "submodules/fpng"
        "submodules/stbImage"
        "submodules/qu3e")

if(${CMAKE_SYSTEM} MATCHES "Linux")
    set(LINUX 1)
endif(${CMAKE_SYSTEM} MATCHES "Linux")

if (UNIX)
    # X11
    if(LINUX)
        find_package(X11 REQUIRED)
        include_directories(${X11_INCLUDE_DIR})
        link_directories(${X11_LIBRARIES})
        target_link_libraries(Isoberry PRIVATE ${X11_LIBRARIES})
    endif(LINUX)
    # GLUT
    if(APPLE)
        find_package(GLUT REQUIRED)
        include_directories(${GLUT_INCLUDE_DIR})
        link_directories(${GLUT_LIBRARIES})
        target_link_libraries(Isoberry PRIVATE ${GLUT_LIBRARIES})
    endif(APPLE)

    find_package(OpenGL REQUIRED)
    include_directories(${OPENGL_INCLUDE_DIR})
    link_directories(${OPENGL_LIBRARIES})
    target_link_libraries(Isoberry PRIVATE ${OPENGL_LIBRARIES})

    set(THREADS_PREFER_PTHREAD_FLAG ON)
    find_package(Threads REQUIRED)
    target_link_libraries(Isoberry PRIVATE Threads::Threads)
endif (UNIX)

find_package(unofficial-enet CONFIG REQUIRED)
target_link_libraries(Isoberry PRIVATE unofficial::enet::enet)
find_package(asio CONFIG REQUIRED)
add_definitions(-DASIO_STANDALONE)
target_link_libraries(Isoberry PRIVATE ${OPEN_SSL_LIBRARY} asio::asio ${ENET_LIBRARIES})