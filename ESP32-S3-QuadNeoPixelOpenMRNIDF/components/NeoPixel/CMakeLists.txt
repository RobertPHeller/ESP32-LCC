set(DEPS
    driver
    esp_timer
    app_update
    OpenMRNIDF
    Config
   )
   
idf_component_register(SRCS Esp32NeoPixel.cpp esp.c
                       INCLUDE_DIRS "include"
                       REQUIRES "${DEPS}"
                      )

set_source_files_properties(Esp32NeoPixel.cpp PROPERTIES COMPILE_FLAGS "-Wno-error=maybe-uninitialized -Wno-implicit-fallthrough -Wno-ignored-qualifiers")
set_source_files_properties(esp.c PROPERTIES COMPILE_FLAGS "-Wno-error=maybe-uninitialized -Wno-implicit-fallthrough -Wno-ignored-qualifiers")
