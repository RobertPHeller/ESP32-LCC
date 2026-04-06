set(DEPS
    OpenMRN
   )
   

idf_component_register(SRCS WiFiManager.cpp
		       INCLUDE_DIRS include
                       REQUIRES "${DEPS}"
                      )
                      
