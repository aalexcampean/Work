# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/e911-aalexcampean_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/e911-aalexcampean_autogen.dir/ParseCache.txt"
  "e911-aalexcampean_autogen"
  )
endif()
