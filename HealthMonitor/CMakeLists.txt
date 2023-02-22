set(DEPS
    OpenMRNIDF
    log
   )
   
idf_component_register(INCLUDE_DIRS include
                       REQUIRES "${DEPS}"
                      )
