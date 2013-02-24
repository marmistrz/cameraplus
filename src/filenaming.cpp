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

#include "filenaming.h"
#include <QDir>
#include <QDate>
#include <QFile>
#include <QDeclarativeInfo>

#define PATH QString("%1%2MyDocs%2cameraplus%2").arg(QDir::homePath()).arg(QDir::separator())
#define TEMP_PATH QString("%1%2MyDocs%2.cameraplus%2").arg(QDir::homePath()).arg(QDir::separator())

FileNaming::FileNaming(QObject *parent) :
  QObject(parent), m_index(-1) {

}

FileNaming::~FileNaming() {

}

QString FileNaming::imageSuffix() const {
  return m_image;
}

void FileNaming::setImageSuffix(const QString& suffix) {
  if (m_image != suffix) {
    m_image = suffix;
    emit imageSuffixChanged();
  }
}

QString FileNaming::videoSuffix() const {
  return m_video;
}

void FileNaming::setVideoSuffix(const QString& suffix) {
  if (m_video != suffix) {
    m_video = suffix;
    emit videoSuffixChanged();
  }
}

QString FileNaming::imageFileName() {
  return fileName(m_image);
}

QString FileNaming::videoFileName() {
  return fileName(m_video);
}

QString FileNaming::fileName(const QString& suffix) {
  QString path = FileNaming::path();
  QString date = QDate::currentDate().toString("yyyyMMdd");
  QDir dir(path);

  if (suffix.isEmpty()) {
    return QString();
  }

  if (path.isEmpty()) {
    return QString();
  }

  if (date != m_date) {
    m_index = -1;
    m_date = date;
  }

  if (m_index == -1) {
    QStringList filters(QString("*%1_*").arg(date));
    QStringList entries = dir.entryList(filters, QDir::Files, QDir::Name);
    if (entries.isEmpty()) {
      m_index = 0;
    }
    else {
      QString name = QFile(entries.last()).fileName();
      m_index = name.section('_', 1, 1).section('.', 0, 0).toInt();
    }
  }

  ++m_index;

  QString name = QString("%1%2_%3.%4").arg(path).arg(date).arg(QString().sprintf("%03i", m_index)).
    arg(suffix);

  if (QFile(name).exists()) {
    return QString();
  }

  return name;
}

QString FileNaming::path() {
  if (m_path.isEmpty()) {
    m_path = canonicalPath(PATH);
  }

  return m_path;
}

QString FileNaming::temporaryPath() {
  if (m_temp.isEmpty()) {
    m_temp = canonicalPath(TEMP_PATH);
  }

  return m_temp;
}

QString FileNaming::canonicalPath(const QString& path) {
  if (!QDir::root().mkpath(path)) {
    qmlInfo(this) << "Failed to create path" << path;
    return QString();
  }

  QString newPath = QFileInfo(path).canonicalFilePath();

  if (newPath.isEmpty()) {
    return newPath;
  }

  if (!newPath.endsWith(QDir::separator())) {
    newPath.append(QDir::separator());
  }

  return newPath;
}

QString FileNaming::temporaryVideoFileName() {
  QString path = temporaryPath();

  if (path.isEmpty()) {
    return path;
  }

  return QString("%1.cameraplus_video.tmp").arg(path);
}
