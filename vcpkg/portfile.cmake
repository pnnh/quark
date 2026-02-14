vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO your-username/quark
    REF v${VERSION}
    SHA512 0
    HEAD_REF main
)

vcpkg_cmake_configure(
    SOURCE_PATH "${SOURCE_PATH}"
)

vcpkg_cmake_install()

vcpkg_cmake_config_fixup(PACKAGE_NAME quark CONFIG_PATH lib/cmake/quark)

# 处理版权文件
file(INSTALL "${SOURCE_PATH}/LICENSE" DESTINATION "${CURRENT_PACKAGES_DIR}/share/quark" RENAME copyright)

# 移除不必要的文件
vcpkg_copy_pdbs()
file(REMOVE_RECURSE "${CURRENT_PACKAGES_DIR}/debug/share")

