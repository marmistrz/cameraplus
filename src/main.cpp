/*!
 * This file is part of CameraPlus.
 *
 * Copyright (C) 2012-2013 Mohammed Sameer <msameer@foolab.org>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#if defined(QT4)
#include <QApplication>
#include <QDeclarativeView>
#include <QDeclarativeContext>
#include <QDeclarativeEngine>
#include <QtDeclarative>
#include <QGLWidget>
#elif defined(QT5)
#include <QGuiApplication>
#include <QQuickView>
#endif

#include "settings.h"
#include "filenaming.h"
#ifdef HARMATTAN
#include "quillitem.h"
#endif
#include "soundvolumecontrol.h"
#include "displaystate.h"
#include "fsmonitor.h"
#include "cameraresources.h"
#include "compass.h"
#include "orientation.h"
#if defined(QT4) // TODO:
#include "geocode.h"
#endif
#include "mountprotector.h"
#include "trackerstore.h"
#include "focusrectangle.h"
#include "sharehelper.h"
#include "deletehelper.h"
#include "galleryhelper.h"
#include "postcapturemodel.h"
#include "batteryinfo.h"
#include "gridlines.h"
#include "deviceinfo.h"
#include "devicekeys.h"
#include "platformsettings.h"
#include "dbusservice.h"
#include <MDeclarativeCache>

#ifdef QMLJSDEBUGGER
#include "qt_private/qdeclarativedebughelper_p.h"
#endif /* QMLJSDEBUGGER */

#if defined(QT4)
#include <QAbstractFileEngineHandler>
#include "qmlfileengine.h"

class QmlFileEngineHandler : public QAbstractFileEngineHandler {
  QAbstractFileEngine *create(const QString& fileName) const {
    QString fn = fileName.toLower();
    if (fn.startsWith(':') && fn.endsWith(".qml")) {
      return new QmlFileEngine(fileName);
    }

    return 0;
  }
};
#endif

Q_DECL_EXPORT int main(int argc, char *argv[]) {
#if defined(QT4)
  QApplication::setAttribute(Qt::AA_X11InitThreads, true);
  QApplication *app = new QApplication(argc, argv);

  QmlFileEngineHandler handler;
  Q_UNUSED(handler);

  QDeclarativeView *view = MDeclarativeCache::qDeclarativeView();
#elif defined(QT5)
  QGuiApplication *app = MDeclarativeCache::qApplication(argc, argv);
  QQuickView *view = MDeclarativeCache::qQuickView();
#endif

#ifdef QMLJSDEBUGGER
  QDeclarativeDebugHelper::enableDebugging();
#endif /* QMLJSDEBUGGER */

#if defined(QT4)
  view->setAttribute(Qt::WA_NoSystemBackground);
  view->setViewport(new QGLWidget);
  view->setResizeMode(QDeclarativeView::SizeRootObjectToView);
  view->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
  view->viewport()->setAttribute(Qt::WA_NoSystemBackground);
#endif

#if defined(QT5)
  view->setResizeMode(QQuickView::SizeRootObjectToView);
  // TODO:
#endif

  qmlRegisterType<Settings>("CameraPlus", 1, 0, "Settings");
  qmlRegisterType<FileNaming>("CameraPlus", 1, 0, "FileNaming");
#ifdef HARMATTAN
  qmlRegisterType<QuillItem>("CameraPlus", 1, 0, "QuillItem");
#endif
  qmlRegisterType<SoundVolumeControl>("CameraPlus", 1, 0, "SoundVolumeControl");
  qmlRegisterType<DisplayState>("CameraPlus", 1, 0, "DisplayState");
  qmlRegisterType<FSMonitor>("CameraPlus", 1, 0, "FSMonitor");
  qmlRegisterType<CameraResources>("CameraPlus", 1, 0, "CameraResources");
  qmlRegisterType<Compass>("CameraPlus", 1, 0, "Compass");
  qmlRegisterType<Orientation>("CameraPlus", 1, 0, "Orientation");
#if defined(QT4) // TODO:
  qmlRegisterType<Geocode>("CameraPlus", 1, 0, "ReverseGeocode");
#endif
  qmlRegisterType<MountProtector>("CameraPlus", 1, 0, "MountProtector");
  qmlRegisterType<TrackerStore>("CameraPlus", 1, 0, "TrackerStore");
  qmlRegisterType<FocusRectangle>("CameraPlus", 1, 0, "FocusRectangle");
  qmlRegisterType<ShareHelper>("CameraPlus", 1, 0, "ShareHelper");
  qmlRegisterType<DeleteHelper>("CameraPlus", 1, 0, "DeleteHelper");
  qmlRegisterType<GalleryHelper>("CameraPlus", 1, 0, "GalleryHelper");
  qmlRegisterType<PostCaptureModel>("CameraPlus", 1, 0, "PostCaptureModel");
  qmlRegisterType<BatteryInfo>("CameraPlus", 1, 0, "BatteryInfo");
  qmlRegisterType<GridLines>("CameraPlus", 1, 0, "GridLines");
#if defined(QT4) // TODO:
  qmlRegisterType<DeviceInfo>("CameraPlus", 1, 0, "DeviceInfo");
#endif
  qmlRegisterType<DeviceKeys>("CameraPlus", 1, 0, "DeviceKeys");
  qmlRegisterType<PlatformSettings>("CameraPlus", 1, 0, "PlatformSettings");

  view->setSource(QUrl("qrc:/qml/main.qml"));

  view->showFullScreen();

  int ret = app->exec();

  delete view;
  delete app;

  return ret;
}
