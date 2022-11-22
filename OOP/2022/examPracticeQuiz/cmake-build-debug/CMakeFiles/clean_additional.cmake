# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/exam-practice-quiz_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/exam-practice-quiz_autogen.dir/ParseCache.txt"
  "exam-practice-quiz_autogen"
  )
endif()
