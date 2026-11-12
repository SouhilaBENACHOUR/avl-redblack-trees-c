cmake_minimum_required(VERSION 3.0)

set(CMAKE_INSTALL_RPATH_USE_LINK_PATH true)

project(List C)

# Ajouter la bibliothèque partagée avl-tree
add_library(avl-tree SHARED rn-tree.c rn-tree.h)

# Installation de la bibliothèque
install(
    TARGETS avl-tree
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
)

# Installation de l'en-tête de la bibliothèque
install(
    FILES avl-tree.h
    DESTINATION include
)

# Configuration du fichier pkg-config
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/rn-tree.pc.in
    ${CMAKE_CURRENT_BINARY_DIR}/rn-tree.pc
    @ONLY
)
install(
    FILES ${CMAKE_CURRENT_BINARY_DIR}/rn-tree.pc
    DESTINATION share/pkgconfig
    COMPONENT "PkgConfig"
)

# Configuration de CMake
include(CMakePackageConfigHelpers)
configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/rnTreeConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/rnTreeConfig.cmake
    INSTALL_DESTINATION cmake
)
install(
    FILES ${CMAKE_CURRENT_BINARY_DIR}/rnTreeConfig.cmake
    DESTINATION cmake
)

# Ajouter l'exécutable de test pour l'arbre rouge-noir
add_executable(test-rn-tree test-rn-tree.c rn-tree.c rn-tree.h)

# Dépendance entre l'exécutable de test et la bibliothèque avl-tree
add_dependencies(test-rn-tree avl-tree)

# Lier le programme de test avec la bibliothèque avl-tree
target_link_libraries(test-rn-tree avl-tree)

# Ajouter un exécutable pour tester les performances (test-temps.c)
add_executable(test-temps test-temps.c Temps-Exe-rn-tree.c rn-tree.h)

# Dépendance entre l'exécutable de test-temps et la bibliothèque avl-tree
add_dependencies(test-temps avl-tree)

# Lier test-temps avec la bibliothèque avl-tree
target_link_libraries(test-temps avl-tree)

# Activer les tests
enable_testing()

# Ajouter un test pour test-rn-tree
add_test(NAME test-rn-tree COMMAND test-rn-tree)

# Ajouter un test pour test-temps
add_test(NAME test-temps COMMAND test-temps)

