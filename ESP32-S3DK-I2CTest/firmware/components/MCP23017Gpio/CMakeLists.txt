set(DEPS
    driver
    app_update
    OpenMRNIDF
    MD_I2CDriver
    vfs
   )
   
idf_component_register(INCLUDE_DIRS "include"
                       PRIV_INCLUDE_DIRS "private_include"
                       REQUIRES "${DEPS}"
                       )

