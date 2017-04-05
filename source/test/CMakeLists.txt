cmake_minimum_required(VERSION 3.5)

if (UNIX AND NOT WIN32)

    find_program(VALGRIND "valgrind")

    enable_testing()

    add_executable(verif_mot_test verif_mot_test.c verif_mot.c verif_mot.h)
    add_executable(constrution_dico_test constrution_dico_test.c construction.c construction.h dico.c dico.h)
    add_executable(constrution_test constrution_test.c construction.h construction.c dico.c dico.h)
    add_executable(server_client_data_test server_client_data_test.c server_client_data.c server_client_data.h)

    add_test(verif_mot_test ./verif_mot_test)
    add_test(constrution_dico_test ./constrution_dico_test)
    add_test(constrution_test ./constrution_test)
    add_test(server_client_data_test ./server_client_data_test)

else ()
    message(FATAL_ERROR "Le project est juste pour les unix.")
endif ()