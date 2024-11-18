# CMakeList.txt: Projekt CMake pro pocet_pismen_a_cislic_a_delky_slov_ale_lepsi, sem přidejte logiku zdrojového
# kódu a definic specifickou pro projekt.
#
cmake_minimum_required (VERSION 3.8)

# Pokud je to podporováno, povolte Opětovné načítání za provozu pro kompilátory MSVC.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("pocet_pismen_a_cislic_a_delky_slov_ale_lepsi")

# Přidejte zdrojový kód ke spustitelnému souboru tohoto projektu.
add_executable (pocet_pismen_a_cislic_a_delky_slov_ale_lepsi "pocet_pismen_a_cislic_a_delky_slov_ale_lepsi.cpp" "pocet_pismen_a_cislic_a_delky_slov_ale_lepsi.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET pocet_pismen_a_cislic_a_delky_slov_ale_lepsi PROPERTY CXX_STANDARD 20)
endif()

# TODO: V případě potřeby přidejte testy a cíle instalace.
