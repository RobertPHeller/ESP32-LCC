set(DEPS
    OpenMRNIDF
    NVSManager
   )
   

idf_component_register(INCLUDE_DIRS include
                       REQUIRES "${DEPS}"
                      )
                      
