// -*- c++ -*-

/*!
 * This file is part of CameraPlus.
 *
 * Copyright (C) 2012-2014 Mohammed Sameer <msameer@foolab.org>
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

#ifndef VIDEO_MODE_H
#define VIDEO_MODE_H

#include "mode.h"

class QtCamVideoMode;
class Resolution;

class VideoMode : public Mode {
  Q_OBJECT
  Q_PROPERTY(bool recording READ isRecording NOTIFY recordingStateChanged);
  Q_PROPERTY(bool paused READ isPaused NOTIFY pauseStateChanged);

public:
  VideoMode(QObject *parent = 0);
  ~VideoMode();

  Q_INVOKABLE bool startRecording(const QString& fileName, const QString& tmpFileName);

  bool isRecording();
  bool isPaused();

public slots:
  void stopRecording(bool sync);
  void pauseRecording(bool pause);

signals:
  void recordingStateChanged();
  void pauseStateChanged();

protected:
  virtual void preChangeMode();
  virtual void postChangeMode();
  virtual void changeMode();
  virtual Resolution *resolution();

private:
  QtCamVideoMode *m_video;
};

#endif /* VIDEO_MODE_H */
