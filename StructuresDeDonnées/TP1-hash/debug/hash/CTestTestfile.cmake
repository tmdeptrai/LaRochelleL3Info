# CMake generated Testfile for 
# Source directory: /home/tmd/Desktop/LaRochelleL3Info/StructuresDeDonnées/TP1-hash/src/hash
# Build directory: /home/tmd/Desktop/LaRochelleL3Info/StructuresDeDonnées/TP1-hash/debug/hash
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(test-hash[valgrind] "/usr/bin/valgrind" "--leak-check=full" "--quiet" "--error-exitcode=1" "./test-hash")
set_tests_properties(test-hash[valgrind] PROPERTIES  _BACKTRACE_TRIPLES "/home/tmd/Desktop/LaRochelleL3Info/StructuresDeDonnées/TP1-hash/src/hash/CMakeLists.txt;62;add_test;/home/tmd/Desktop/LaRochelleL3Info/StructuresDeDonnées/TP1-hash/src/hash/CMakeLists.txt;0;")
add_test(test-hash[normal] "./test-hash")
set_tests_properties(test-hash[normal] PROPERTIES  _BACKTRACE_TRIPLES "/home/tmd/Desktop/LaRochelleL3Info/StructuresDeDonnées/TP1-hash/src/hash/CMakeLists.txt;64;add_test;/home/tmd/Desktop/LaRochelleL3Info/StructuresDeDonnées/TP1-hash/src/hash/CMakeLists.txt;0;")
