cmake_minimum_required( VERSION 3.16.0 )
project(echocolor)

set(C_FILES
  src/main.c
)

add_executable(${PROJECT_NAME}
    ${C_FILES}
)

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)

# building tarball with CPack -------------------------------------------------
include (InstallRequiredSystemLibraries)
set (CPACK_PACKAGE_VERSION_MAJOR 0)
set (CPACK_PACKAGE_VERSION_MINOR 1)
set (CPACK_PACKAGE_VERSION_PATCH 0)
set (CPACK_GENERATOR TBZ2)
set (CPACK_SOURCE_GENERATOR TBZ2)
set (CPACK_SOURCE_IGNORE_FILES /build/;.gitignore;.*~;.git;.kdev4;temp)
include (CPack)
