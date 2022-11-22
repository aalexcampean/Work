# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/exam_practice_question_answers_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/exam_practice_question_answers_autogen.dir/ParseCache.txt"
  "exam_practice_question_answers_autogen"
  )
endif()
