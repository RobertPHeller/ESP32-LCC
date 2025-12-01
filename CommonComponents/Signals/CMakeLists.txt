set(DEPS
    app_update
    OpenMRNIDF
    Config
    Logic
   )
   
idf_component_register(SRCS Mast.cpp Rule.cpp
                       INCLUDE_DIRS "include"
                       REQUIRES "${DEPS}"
                      )
set_source_files_properties(Mast.cpp PROPERTIES COMPILE_FLAGS "-Wno-error=maybe-uninitialized -Wno-implicit-fallthrough -Wno-ignored-qualifiers")
set_source_files_properties(Rule.cpp PROPERTIES COMPILE_FLAGS "-Wno-error=maybe-uninitialized -Wno-implicit-fallthrough -Wno-ignored-qualifiers")
