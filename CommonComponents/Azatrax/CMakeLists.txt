set(DEPS
    driver
    app_update
    OpenMRNIDF
    vfs
   )
   
idf_component_register(SRCS Azatrax.cpp
                       INCLUDE_DIRS "include"
                       REQUIRES "${DEPS}"
                      )
