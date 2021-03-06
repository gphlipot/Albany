##*****************************************************************//
##    Albany 3.0:  Copyright 2016 Sandia Corporation               //
##    This Software is released under the BSD license detailed     //
##    in the file "license.txt" in the top-level Albany directory  //
##*****************************************************************//

if(SEACAS_EXODIFF)
# Create a symlink to the runtest.py script
execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink
  ${runtest.py} ${CMAKE_CURRENT_BINARY_DIR}/runtest.py)

# Create a symlink to the MPS
execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink
  ${MPS.exe} ${CMAKE_CURRENT_BINARY_DIR}/MPS)

# Create a symlink to exodiff
execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink
  ${SEACAS_EXODIFF} ${CMAKE_CURRENT_BINARY_DIR}/exodiff)

# Copy script file from source to binary dir
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Neohookean.py
               ${CMAKE_CURRENT_BINARY_DIR}/Neohookean.py COPYONLY)

# Copy Input files from source to binary dir
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Neohookean-uniaxial.yaml
               ${CMAKE_CURRENT_BINARY_DIR}/Neohookean-uniaxial.yaml COPYONLY)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Neohookean-shear.yaml
               ${CMAKE_CURRENT_BINARY_DIR}/Neohookean-shear.yaml COPYONLY)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Neohookean-hydrostatic.yaml
               ${CMAKE_CURRENT_BINARY_DIR}/Neohookean-hydrostatic.yaml COPYONLY)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Neohookean-general.yaml
               ${CMAKE_CURRENT_BINARY_DIR}/Neohookean-general.yaml COPYONLY)

# Copy the reference solution and exodiff files
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Neohookean-uniaxial.gold.exo
               ${CMAKE_CURRENT_BINARY_DIR}/Neohookean-uniaxial.gold.exo COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Neohookean-uniaxial.exodiff
               ${CMAKE_CURRENT_BINARY_DIR}/Neohookean-uniaxial.exodiff COPYONLY)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Neohookean-shear.gold.exo
               ${CMAKE_CURRENT_BINARY_DIR}/Neohookean-shear.gold.exo COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Neohookean-shear.exodiff
               ${CMAKE_CURRENT_BINARY_DIR}/Neohookean-shear.exodiff COPYONLY)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Neohookean-hydrostatic.gold.exo
               ${CMAKE_CURRENT_BINARY_DIR}/Neohookean-hydrostatic.gold.exo COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Neohookean-hydrostatic.exodiff
               ${CMAKE_CURRENT_BINARY_DIR}/Neohookean-hydrostatic.exodiff COPYONLY)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Neohookean-general.gold.exo
               ${CMAKE_CURRENT_BINARY_DIR}/Neohookean-general.gold.exo COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Neohookean-general.exodiff
               ${CMAKE_CURRENT_BINARY_DIR}/Neohookean-general.exodiff COPYONLY)

# Name the test with the directory name
get_filename_component(testName ${CMAKE_CURRENT_SOURCE_DIR} NAME)

# Run the "runtest.py" file in the CWD
add_test(NAME ${testName} COMMAND "python" "Neohookean.py")
endif(SEACAS_EXODIFF)
