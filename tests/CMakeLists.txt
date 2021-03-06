MACRO(ADD_TEST name )
  configure_gst(${name})
  target_link_libraries(${name} -L../declarative -ldeclarativeqtcamera -Wl,-rpath=/usr/lib/qt4/imports/QtCamera/)
  target_link_libraries(${name} qtcamera)
  if (QT4)
    target_link_libraries(${name} Qt4::QtTest Qt4::QtDeclarative)
  elseif (QT5)
    qt5_use_modules(${name} Test)
  endif()
ENDMACRO(ADD_TEST)

if (QT4)
  find_package(Qt4 REQUIRED QtTest)
  find_package(Qt4 REQUIRED QtDeclarative)
  include(${QT_USE_FILE})
elseif (QT5)
  find_package(Qt5Test REQUIRED)
endif()

qt_wrap_cpp(tst_camera_moc tst_camera.h)
add_executable(tst_camera tst_camera.cpp ${tst_camera_moc})
add_test(tst_camera)

qt_wrap_cpp(tst_position_moc tst_position.h ../src/position.h)
add_executable(tst_position tst_position.cpp ../src/position.cpp ${tst_position_moc})
add_test(tst_position)

include_directories(../lib/ ../declarative/ ../src/)

add_dependencies(tst_camera declarativeqtcamera)
add_dependencies(tst_position declarativeqtcamera)
