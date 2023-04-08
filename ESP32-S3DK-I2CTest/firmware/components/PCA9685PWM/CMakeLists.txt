set(DEPS
    driver
    app_update
    OpenMRNIDF
    MD_I2CDriver
    vfs
   )
   
idf_component_register(SRCS PCA9685PWM.cpp
                       INCLUDE_DIRS "include"
                       REQUIRES "${DEPS}"
                       )

