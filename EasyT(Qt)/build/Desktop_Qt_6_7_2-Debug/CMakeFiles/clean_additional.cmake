# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/EasyT_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/EasyT_autogen.dir/ParseCache.txt"
  "EasyT_autogen"
  )
endif()
