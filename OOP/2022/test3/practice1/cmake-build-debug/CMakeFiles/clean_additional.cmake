# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/t3-practice1_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/t3-practice1_autogen.dir/ParseCache.txt"
  "t3-practice1_autogen"
  )
endif()
