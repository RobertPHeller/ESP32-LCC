set(deps
    driver
    heap
    nvs_flash
    vfs
    app_update
    spiffs
    OpenMRNIDF
    Config
    I2CDriver
    GeneralIO
    Signals
    Logic
    NVSManager
    FS
    HealthMonitor
    RebootHelpers
    json
)

idf_component_register(SRCS esp32multifunction.cpp
                        PCA9685PWM.cpp
                       REQUIRES "${deps}")

# export the project version as a define for the SNIP data, note it must be
# truncated to 21 characters max.
idf_build_get_property(project_ver PROJECT_VER)
string(SUBSTRING "${project_ver}" 0 20 SNIP_SW_VERSION)
idf_build_get_property(project_name PROJECT_NAME)
string(SUBSTRING "${project_name}" 0 40 SNIP_PROJECT_NAME)

set(SNIP_HW_VERSION "1.0.0")
set(SNIP_PROJECT_PAGE "https://www.deepsoft.com/")
set(CDI_VERSION "0x0101")

set_source_files_properties(esp32multifunction.cpp PROPERTIES COMPILE_FLAGS "-Wno-error=maybe-uninitialized -Wno-implicit-fallthrough -Wno-ignored-qualifiers")
set_source_files_properties(esp32multifunction.cpp PROPERTIES COMPILE_DEFINITIONS "SNIP_PROJECT_PAGE=\"${SNIP_PROJECT_PAGE}\"; SNIP_HW_VERSION=\"${SNIP_HW_VERSION}\"; SNIP_SW_VERSION=\"${SNIP_SW_VERSION}\"; SNIP_PROJECT_NAME=\"${SNIP_PROJECT_NAME}\"; CDI_VERSION=${CDI_VERSION}")
set_source_files_properties(PCA9685PWM.cpp PROPERTIES COMPILE_FLAGS "-Wno-error=maybe-uninitialized -Wno-implicit-fallthrough -Wno-ignored-qualifiers")

set(CDIDEPS
    ${CMAKE_CURRENT_SOURCE_DIR}/../components/Config/include/cdi.hxx
    ${CMAKE_CURRENT_SOURCE_DIR}/../../.git/index
    ${CMAKE_CURRENT_SOURCE_DIR}/../sdkconfig
   )

set(DOCDEPS
    ${CMAKE_CURRENT_SOURCE_DIR}/../../.git/index
    ${CMAKE_CURRENT_SOURCE_DIR}/../sdkconfig
    )
    
add_custom_command(OUTPUT "${CMAKE_CURRENT_SOURCE_DIR}/../components/Config/include/cdidata.hxx"
                          "${CMAKE_CURRENT_SOURCE_DIR}/../components/Config/include/Revision.hxxout"
                   COMMAND make CONFIG_DEVKIT_BREADBOARD="${CONFIG_DEVKIT_BREADBOARD}" CONFIG_T7S3="${CONFIG_T7S3}" CONFIG_SERVO_TURNOUTS="${CONFIG_SERVO_TURNOUTS}" -C ${CMAKE_CURRENT_SOURCE_DIR}/../components/Config/CDI 
                   DEPENDS "${CDIDEPS}"
                   VERBATIM
                  )

idf_build_get_property(component_dirs COMPONENT_DIRS)

add_custom_command(OUTPUT "${CMAKE_CURRENT_SOURCE_DIR}/../doc/pdf"
                          "${CMAKE_CURRENT_SOURCE_DIR}/../doc/html/index.html"
                   COMMAND make PROJECTNAME="${project_name}" PROJECTNUMBER="${project_ver}" -C "${CMAKE_CURRENT_SOURCE_DIR}/../doc"
                   DEPENDS "${DOCDEPS}"
                   VERBATIM
                  )

add_custom_target(FORCE 
                  ALL
                  DEPENDS 
                  "${CMAKE_CURRENT_SOURCE_DIR}/../components/Config/include/cdidata.hxx"
                  "${CMAKE_CURRENT_SOURCE_DIR}/../doc/pdf"
                 )

