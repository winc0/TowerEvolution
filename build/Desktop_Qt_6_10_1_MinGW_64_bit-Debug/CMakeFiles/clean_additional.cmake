# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\TowerDefense_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\TowerDefense_autogen.dir\\ParseCache.txt"
  "TowerDefense_autogen"
  )
endif()
