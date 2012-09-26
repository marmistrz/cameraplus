TEMPLATE = app
TARGET = cameraplus
DEPENDPATH += . ../
INCLUDEPATH += . ../

QT += declarative opengl

CONFIG += link_pkgconfig debug static mobility

MOBILITY += location

PKGCONFIG = gstreamer-0.10 gstreamer-interfaces-0.10 gstreamer-video-0.10 gstreamer-tag-0.10 \
            gstreamer-pbutils-0.10 meego-gstreamer-interfaces-0.10 quill qmsystem2 libresourceqt1

LIBS +=  -L../imports/ -limports -L../lib/ -lqtcamera

SOURCES += main.cpp settings.cpp filenaming.cpp quillitem.cpp displaystate.cpp fsmonitor.cpp \
           cameraresources.cpp compass.cpp orientation.cpp geocode.cpp

HEADERS += settings.h filenaming.h quillitem.h displaystate.h fsmonitor.h \
           cameraresources.h compass.h orientation.h geocode.h
