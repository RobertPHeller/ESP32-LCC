set(DEPS
    OpenMRNIDF
    Azatrax
   )
   

idf_component_register(INCLUDE_DIRS include
                       REQUIRES "${DEPS}"
                      )
                      
