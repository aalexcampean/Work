# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/t3_aalexcampean_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/t3_aalexcampean_autogen.dir/ParseCache.txt"
  "t3_aalexcampean_autogen"
  )
endif()
