set(deps
    driver
    heap
    nvs_flash
    vfs
    app_update
    spiffs
    OpenMRNIDF
    Config
    PCA9685PWM
    GeneralIO
    Signals
    Logic
    NVSManager
    FS
    HealthMonitor
    RebootHelpers
    json
    esp_timer
)

idf_component_register(SRCS esp32pwmhalfsiding.cpp
                       REQUIRES "${deps}")

# export the project version as a define for the SNIP data, note it must be
# truncated to 21 characters max.
idf_build_get_property(project_ver PROJECT_VER)
string(SUBSTRING "${project_ver}" 0 20 SNIP_SW_VERSION)
idf_build_get_property(project_name PROJECT_NAME)
string(SUBSTRING "${project_name}" 0 40 SNIP_PROJECT_NAME)

set(SNIP_HW_VERSION "1.0.0")
set(SNIP_PROJECT_PAGE "https://www.deepsoft.com/")
set(CDI_VERSION "0x0100")

set_source_files_properties(esp32pwmhalfsiding.cpp PROPERTIES COMPILE_FLAGS "-Wno-error=maybe-uninitialized -Wno-implicit-fallthrough -Wno-ignored-qualifiers")
set_source_files_properties(esp32pwmhalfsiding.cpp PROPERTIES COMPILE_DEFINITIONS "SNIP_PROJECT_PAGE=\"${SNIP_PROJECT_PAGE}\"; SNIP_HW_VERSION=\"${SNIP_HW_VERSION}\"; SNIP_SW_VERSION=\"${SNIP_SW_VERSION}\"; SNIP_PROJECT_NAME=\"${SNIP_PROJECT_NAME}\"; CDI_VERSION=${CDI_VERSION}")
set_source_files_properties(PCA9685PWM.cpp PROPERTIES COMPILE_FLAGS "-Wno-error=maybe-uninitialized -Wno-implicit-fallthrough -Wno-ignored-qualifiers")

set(CDIDEPS
    ${CMAKE_CURRENT_SOURCE_DIR}/../components/Config/include/cdi.hxx
    ${CMAKE_CURRENT_SOURCE_DIR}/../../.git/index
    ${CMAKE_CURRENT_SOURCE_DIR}/../sdkconfig
   )

add_custom_command(OUTPUT "${CMAKE_CURRENT_SOURCE_DIR}/../components/Config/include/cdidata.hxx"
                          "${CMAKE_CURRENT_SOURCE_DIR}/../components/Config/include/Revision.hxxout"
                   COMMAND make -C ${CMAKE_CURRENT_SOURCE_DIR}/../components/Config/CDI 
                   DEPENDS "${CDIDEPS}"
                   VERBATIM
                  )

add_custom_target(FORCE 
                  ALL
                  DEPENDS                                                     
                  "${CMAKE_CURRENT_SOURCE_DIR}/../components/Config/include/cdidata.hxx"
                 )

