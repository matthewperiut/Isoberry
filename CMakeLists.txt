cmake_minimum_required(VERSION 3.19)
project(Isoberry)

set(CMAKE_CXX_STANDARD 17)

add_executable(Isoberry main.cpp header/olcPixelGameEngine.h game/tool/v3.h game/tool/collider.cpp game/tool/collider.h game/tool/img.cpp game/tool/img.h utility/settings/resolution.cpp utility/settings/resolution.h utility/settings/settings.cpp utility/settings/settings.h game/game.cpp game/game.h game/objects/player.cpp game/objects/player.h utility/settings/native.h game/tool/DrawLineToSprite.h game/tool/DrawLineToSprite.cpp game/tool/SpriteSaving/lodepng.cpp game/tool/SpriteSaving/lodepng.h game/tool/SpriteSaving/svpng.h game/tool/SpriteSaving/saving.cpp game/tool/SpriteSaving/saving.h game/tool/art/colliderTemplate.cpp game/tool/art/colliderTemplate.h)

if (UNIX)
    #X11
    find_package(X11 REQUIRED)
    include_directories(${X11_INCLUDE_DIR})
    link_directories(${X11_LIBRARIES})
    target_link_libraries(Isoberry ${X11_LIBRARIES})

    find_package(OpenGL REQUIRED)
    include_directories(${OPENGL_INCLUDE_DIR})
    link_directories(${OPENGL_LIBRARIES})
    target_link_libraries(Isoberry ${OPENGL_LIBRARIES})

    set(THREADS_PREFER_PTHREAD_FLAG ON)
    find_package(Threads REQUIRED)
    target_link_libraries(Isoberry Threads::Threads)

    find_package(PNG REQUIRED)
    include_directories(${PNG_INCLUDE_DIR})
    link_directories(${PNG_LIBRARIES})
    target_link_libraries(Isoberry ${PNG_LIBRARIES})

    target_link_libraries(${PROJECT_NAME} stdc++fs)
endif (UNIX)