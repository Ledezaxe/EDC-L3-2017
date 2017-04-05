cmake_minimum_required(VERSION 3.5)

if (UNIX AND NOT WIN32)
    project("Word_Scramble")

    set(PROJECT_MAJOR_VERSION 1)
    set(PROJECT_MINOR_VERSION 0)
    set(PROJECT_PATCH_VERSION 0)
    set(PROJECT_VERSION ${PROJECT_MAJOR_VERSION}.${PROJECT_MINOR_VERSION}.${PROJECT_PATCH_VERSION})


    message("-- ->Project ${PROJECT_NAME} Version: ${PROJECT_VERSION}")

    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11 -g3 -W -Wall -Wextra -pedantic-errors -lpthread  ")
    MESSAGE(test)
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(SDL sdl>=1.2)
    if (NOT SDL_FOUND)
        message(FATAL_ERROR "-- ->Install SDL 1.2 .")
    endif ()
    pkg_check_modules(SDL_TTF  SDL_ttf)
    if (NOT SDL_TTF_FOUND)
        message(FATAL_ERROR "-- ->Install SDL TTF.")
    endif ()
    pkg_check_modules(ZMQ libzmq>=4.1)
    if (NOT ZMQ_FOUND)
        message(FATAL_ERROR "-- ->Install ZMQ >= 4.1 .")
    endif ()

    include_directories(${SDL_INCLUDE_DIR} ${SDL_TTF_INCLUDE_DIRS} ${ZMQ_INCLUDE_DIRS})
    link_directories(${SDL_LIBRARY_DIRS} ${SDL_TTF_LIBRARY_DIRS} ${ZMQ_INCLUDE_DIRS})
    add_definitions(${SDL_CFLAGS_OTHER} ${SDL_TTF_CFLAGS_OTHER} ${ZMQ_CFLAGS_OTHER})


    set(SERVER_DATA_CLIENT server_client_data.h server_client_data.c)
    set(DICTIONARY dico.c dico.h)
    set(VERIF verif_mot.h verif_mot.c)
    set(constrution construction.c construction.h test.c ${DICTIONARY})
    set(SERVER_ALPHA server_a.c server_a.h construction.c construction.h ${DICTIONARY} ${VERIF} ${SERVER_DATA_CLIENT} client_texte1.h)
    set(INC_H server_client_data.h dico.h verif_mot.h construction.h client_texte1.h client_texte2.h client_brute_force.h client_sdl.h)
    set(CLIENT_TEXT_1 client_texte1.c  client_texte1.h)
    set(CLIENT_TEXT_2 client_texte2.c  client_texte2.h)
    set(FORCE force_brute.h force_brute.c)
    set(CLIENT_BR client_brute_force.c  client_brute_force.h)
    set(CLIENT_SDL client_sdl.c  client_sdl.h)

    set(SDLT sdlTest.c sdlTest.h)
    add_executable(sdlt ${SDLT})
    target_link_libraries(sdlt ${SDL_LIBRARIES} ${SDL_TTF_LIBRARIES})

    add_executable(server_alpha ${SERVER_ALPHA})
    target_link_libraries(server_alpha ${ZMQ_LIBRARIES} -lpthread -lzmq)

    add_executable(client_texte1 ${CLIENT_TEXT_1})
    target_link_libraries(client_texte1 ${ZMQ_LIBRARIES} -lpthread -lzmq)

    add_executable(client_texte2 ${CLIENT_TEXT_2})
    target_link_libraries(client_texte2 ${ZMQ_LIBRARIES} -lpthread -lzmq)

    add_executable(client_brute_force ${CLIENT_BR} ${FORCE})
    target_link_libraries(client_brute_force ${ZMQ_LIBRARIES} -lpthread -lzmq)

    add_executable(client_sdl ${CLIENT_SDL})
    target_link_libraries(client_sdl ${ZMQ_LIBRARIES} ${SDL_LIBRARIES} ${SDL_TTF_LIBRARIES} -lpthread -lzmq)

    set(INC_H server_client_data.h dico.h verif_mot.h construction.h client_texte1.h client_texte2.h client_brute_force.h client_sdl.h)
    set(BIN server_alpha client_texte1 client_texte2 client_brute_force client_sdl)

    install(FILES
            ${INC_H}
            DESTINATION include
    )


    install(FILES
            arial.ttf
            DESTINATION bin
            )

    install(PROGRAMS
            ${CMAKE_CURRENT_BINARY_DIR}/server_alpha
            ${CMAKE_CURRENT_BINARY_DIR}/client_texte1
            ${CMAKE_CURRENT_BINARY_DIR}/client_texte2
            ${CMAKE_CURRENT_BINARY_DIR}/client_brute_force
            ${CMAKE_CURRENT_BINARY_DIR}/client_sdl
            DESTINATION bin
            )

    install(DIRECTORY
            dico
            DESTINATION bin
            )

    add_subdirectory(./test)
    add_subdirectory(./Documentation)

    install(PROGRAMS
            ${CMAKE_CURRENT_BINARY_DIR}/test/verif_mot_test
            ${CMAKE_CURRENT_BINARY_DIR}/test/constrution_dico_test
            ${CMAKE_CURRENT_BINARY_DIR}/test/constrution_test
            ${CMAKE_CURRENT_BINARY_DIR}/test/server_client_data_test

            DESTINATION bin/test/
            )

    install(DIRECTORY
            ${CMAKE_CURRENT_BINARY_DIR}/Documentation/html/
            DESTINATION bin/Documentation/
            )

    enable_testing()
else ()
    message(FATAL_ERROR "Le project est juste pour les unix.")
endif ()