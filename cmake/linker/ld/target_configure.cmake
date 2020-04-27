# SPDX-License-Identifier: Apache-2.0

# See root CMakeLists.txt for description and expectations of these macros

macro(toolchain_ld_configure_files)
  configure_file(
       ${ZEPHYR_BASE}/include/arch/common/app_data_alignment.ld
       ${PROJECT_BINARY_DIR}/include/generated/app_data_alignment.ld)
endmacro()
