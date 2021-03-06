set(SOURCE_FILES
  panoramaplugin.cpp
  panorama.cpp
  panoramatracker.cpp
  panoramastitcher.cpp
  panoramainput.cpp
  )

set(HEADER_FILES
  panoramaplugin.h
  panorama.h
  panoramatracker.h
  panoramastitcher.h
  panoramainput.h
  )

qt_wrap_cpp(MOC_FILES ${HEADER_FILES})

find_package(TIFF REQUIRED)

link_directories(${LIBYUV_LIB_DIR} ${PANORAMA_STITCHER_LIB_DIR})
add_library(cameraplus-panorama MODULE ${SOURCE_FILES} ${MOC_FILES})
target_link_libraries(cameraplus-panorama qtcamera yuv panorama-stitcher ${TIFF_LIBRARIES})
include_directories(../lib/
  ${LIBYUV_INCLUDE_DIR}
  ${PANORAMA_STITCHER_INCLUDE_DIR}
  ${TIFF_INCLUDE_DIR}
  )

configure_gst(cameraplus-panorama)
add_dependencies(cameraplus-panorama libyuv panorama-stitcher qtcamera)
install(TARGETS cameraplus-panorama DESTINATION ${QT_INSTALL_IMPORTS}/CameraPlus/Panorama)
install(FILES qmldir DESTINATION ${QT_INSTALL_IMPORTS}/CameraPlus/Panorama)

if (QT5)
  qt5_use_modules(cameraplus-panorama Qml Quick)
endif()
