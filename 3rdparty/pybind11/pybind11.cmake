include(FetchContent)

find_package(Git QUIET REQUIRED)

FetchContent_Declare(
    ext_pybind11
    PREFIX pybind11
    URL https://github.com/pybind/pybind11/archive/refs/tags/v2.11.1.tar.gz
    URL_HASH SHA256=d475978da0cdc2d43b73f30910786759d593a9d8ee05b1b6846d1eb16c6d2e0c
    DOWNLOAD_DIR "${OPEN3D_THIRD_PARTY_DOWNLOAD_DIR}/pybind11"
    PATCH_COMMAND ${GIT_EXECUTABLE} init
    COMMAND ${GIT_EXECUTABLE} apply --ignore-space-change --ignore-whitespace
        ${CMAKE_CURRENT_LIST_DIR}/0001-fix-for-iOS.patch
)

FetchContent_MakeAvailable(ext_pybind11)
