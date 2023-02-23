set(DEPS
    OpenMRNIDF
    app_update
    spiffs
    vfs
   )
   

idf_component_register(SRCS fs.cpp
                       INCLUDE_DIRS "include"
                       REQUIRES "${DEPS}"
                      )
                      
set_source_files_properties(fs.cpp PROPERTIES COMPILE_FLAGS "-Wno-error=maybe-uninitialized -Wno-implicit-fallthrough -Wno-ignored-qualifiers")

