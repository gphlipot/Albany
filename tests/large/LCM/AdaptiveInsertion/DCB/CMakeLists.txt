##*****************************************************************//
##    Albany 3.0:  Copyright 2016 Sandia Corporation               //
##    This Software is released under the BSD license detailed     //
##    in the file "license.txt" in the top-level Albany directory  //
##*****************************************************************//

# Copy Input file from source to binary dir
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/dcb-hex.jou
               ${CMAKE_CURRENT_BINARY_DIR}/dcb-hex.jou COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/dcb-hex.g
               ${CMAKE_CURRENT_BINARY_DIR}/dcb-hex.g COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/dcb-hex.yaml
               ${CMAKE_CURRENT_BINARY_DIR}/dcb-hex.yaml COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/mat-dcb.yaml
               ${CMAKE_CURRENT_BINARY_DIR}/mat-dcb.yaml COPYONLY)

