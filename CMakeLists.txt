cmake_minimum_required(VERSION 3.11)
project(bomberman)

set(CMAKE_CXX_STANDARD 11)
set(GCC_COVERAGE_COMPILE_FLAGS "-Wall -lIrrlicht -lGL")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/Release)
set(LIB_JSON_PARSER_INCLUDE libs/json_parser/include/)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake/Irrlicht")

if (UNIX)
    set(SFML_DIR "$/usr/lib/cmake/SFML")
else ()
    set(SFML_DIR "${CMAKE_CURRENT_LIST_DIR}/cmake/SFML/lib/cmake/SFML")
endif (UNIX)

include("cmake/Irrlicht/FindIrrlicht.cmake")
find_package(SFML 2.5.1 COMPONENTS audio REQUIRED)

file(GLOB_RECURSE SFML_LIB
        cmake/SFML/bin/*
        cmake/SFML/lib/*.lib)

if (NOT Irrlicht_FOUND OR NOT SFML_FOUND)

    message("failed to find irrlicht or SFML")
else()
    include_directories("include"
            ${CMAKE_CURRENT_LIST_DIR}/cmake/SFML/include
            ${LIB_JSON_PARSER_INCLUDE}
            ${Irrlicht_INCLUDE_DIRS})

    add_library(json_parser STATIC
            libs/json_parser/src/deleter/delete_json_object.c
            libs/json_parser/src/reader/array_parser.c
            libs/json_parser/src/reader/chained_list.c
            libs/json_parser/src/reader/data.c
            libs/json_parser/src/reader/data_getter.c
            libs/json_parser/src/reader/line_parser.c
            libs/json_parser/src/reader/object_parser.c
            libs/json_parser/src/reader/parser.c
            libs/json_parser/src/writer/write_array.c
            libs/json_parser/src/writer/write_data.c
            libs/json_parser/src/writer/write_object.c
            libs/json_parser/src/writer/writer.c)

    add_executable(bomberman
            src/main.cpp src/Game.cpp
            include/Game.hpp
            include/visual/IMesh.hpp
            src/visual/Mesh.cpp
            include/visual/Mesh.hpp
            src/visual/Particle.cpp
            include/visual/Particle.hpp
            src/visual/AnimatedMesh.cpp
            include/visual/AnimatedMesh.hpp
            include/scenes/IScene.hpp
            include/scenes/SceneIndex.hpp
            src/visual/VisualManager.cpp
            include/visual/VisualManager.hpp
            include/visual/IGUI.hpp
            src/visual/Gui.cpp
            include/visual/Gui.hpp
            src/events/EventManager.cpp
            include/events/EventManager.hpp
            include/events/IEventManager.hpp
            include/config/IdGen.hpp
            src/config/IdGen.cpp
            include/ECS/Components.hpp
            include/ECS/ECSEntity.hpp
            include/ECS/InputSystem.hpp
            include/ECS/MovementSystem.hpp
            include/ECS/CollisionSystem.hpp
            include/ECS/EndGameSystem.hpp
            include/ECS/EffectSystem.hpp
            include/ECS/CollectibleSystem.hpp
            include/ECS/ActionSystem.hpp
            include/ECS/MapSystem.hpp
            include/ECS/Instance.hpp
            include/ECS/Storage.hpp
            include/ECS/IASystem.hpp
            src/ECS/ECSEntity.cpp
            src/ECS/InputSystem.cpp
            src/ECS/CollectibleSystem.cpp
            src/ECS/MovementSystem.cpp
            src/ECS/EndGameSystem.cpp
            src/ECS/ActionSystem.cpp
            src/ECS/MapSystem.cpp
            src/ECS/EffectSystem.cpp
            src/ECS/CollisionSystem.cpp
            src/ECS/Instance.cpp
            src/ECS/IASystem.cpp
            src/config/IdGen.cpp
            include/scenes/AScene.hpp
            src/scenes/AScene.cpp
            include/scenes/SceneGame.hpp
            src/scenes/SceneGame.cpp
            include/scenes/SceneMenu.hpp
            include/scenes/SceneOption.hpp
            src/config/JsonParser.cpp
            include/config/JsonParser.hpp
            src/config/JsonData.cpp
            include/config/JsonData.hpp
            src/config/Config.cpp
            include/config/Config.hpp
            src/scenes/SceneGame.cpp
            src/scenes/SceneMenu.cpp
            src/scenes/SceneOption.cpp src/visual/Camera.cpp include/visual/Camera.hpp src/ECS/ExplosiveSystem.cpp include/ECS/ExplosiveSystem.hpp src/ECS/TimerSystem.cpp include/ECS/TimerSystem.hpp src/config/GameConfig.cpp include/config/GameConfig.hpp src/scenes/SceneMapSelection.cpp include/scenes/SceneMapSelection.hpp
            src/scenes/ScenePlayerSelection.cpp include/scenes/ScenePlayerSelection.hpp src/visual/AMesh.cpp include/visual/AMesh.hpp)

    target_link_libraries(bomberman
            ${Irrlicht_LIBRARIES}
            json_parser
            sfml-audio)

    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/cmake/Irrlicht/Irrlicht.dll
    DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/Release)
    file(COPY ${SFML_LIB}
            DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/Release)

endif()
