set(DEPS
    driver
    app_update
    OpenMRN
    vfs
   )
   
idf_component_register(SRCS Azatrax.cpp
                       INCLUDE_DIRS "include"
                       REQUIRES "${DEPS}"
                      )
