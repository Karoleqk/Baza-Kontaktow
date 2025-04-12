# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "Baza_Kontaktow_autogen"
  "CMakeFiles/Baza_Kontaktow_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/Baza_Kontaktow_autogen.dir/ParseCache.txt"
  )
endif()
