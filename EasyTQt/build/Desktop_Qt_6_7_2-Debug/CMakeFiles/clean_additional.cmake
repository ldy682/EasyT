# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/EasyTQt_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/EasyTQt_autogen.dir/ParseCache.txt"
  "EasyTQt_autogen"
  )
endif()
