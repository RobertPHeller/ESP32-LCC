set(DEPS
    driver
    app_update
    OpenMRNIDF
    vfs
   )
                      
idf_component_register(SRCS Esp32HardwareI2C.cpp
                       INCLUDE_DIRS "include"
                       REQUIRES "${DEPS}"
                      )
