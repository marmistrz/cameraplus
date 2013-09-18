// -*- qml -*-

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

import QtQuick 2.0
import QtCamera 1.0

Rectangle {
    id: controller
    property Camera cam
    property bool busy: cam.mode != settings.mode
    property bool dimmed

    z: 1
    anchors.fill: parent
    opacity: dimmed ? 1.0 : 0.0
    color: "black"

    Behavior on opacity {
        PropertyAnimation { duration: 150 }
    }

    onBusyChanged: {
        if (busy) {
            controller.dimmed = true
        }
    }

    Connections {
        target: controller.cam
        onModeChanged: {
            controller.dimmed = false
        }
    }

    PauseAnimation {
        id: pause
        duration: 50
        running: controller.opacity == 1.0 && controller.busy

        onRunningChanged: {
            if (!running && controller.busy) {
                root.resetCamera(cam.deviceId, settings.mode)
            }
        }
    }
}
