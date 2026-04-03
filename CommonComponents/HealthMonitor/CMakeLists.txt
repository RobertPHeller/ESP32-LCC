set(DEPS
    OpenMRN
    log
   )
   
idf_component_register(INCLUDE_DIRS include
                       REQUIRES "${DEPS}"
                      )
