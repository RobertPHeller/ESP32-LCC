set(DEPS
    driver
    app_update
    OpenMRN
    vfs
   )
   
idf_component_register(SRCS PCA9685PWM.cpp
                       INCLUDE_DIRS "include"
                       REQUIRES "${DEPS}"
                       )

