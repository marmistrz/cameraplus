// -*- qml -*-

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

import QtQuick 2.0
import CameraPlus 1.0

Item {
    id: zoomHandler
    property bool zoomPressed: false

    signal pressed()
    signal released()

    property bool active: settings.zoomAsShutter && rootWindow.active

    function handlePress() {
        if (!zoomHandler.active || zoomHandler.zoomPressed) {
            return
        }

        zoomHandler.zoomPressed = true
        zoomHandler.pressed()
    }

    function handleRelease() {
        if (!zoomHandler.active || !zoomHandler.zoomPressed) {
            return
        }

        zoomHandler.zoomPressed = false

        zoomHandler.released()
    }

    Connections {
        id: zoomConnection
        target: zoomHandler.enabled ? keys : null

        onActiveChanged: {
            if (!zoomConnection.active) {
                zoomHandler.zoomPressed = false
            }
        }

        onVolumeUpPressed: zoomHandler.handlePress()
        onVolumeDownPressed: zoomHandler.handlePress()
        onVolumeUpReleased: zoomHandler.handleRelease()
        onVolumeDownReleased: zoomHandler.handleRelease()
    }

    Connections {
        target: rootWindow
        onActiveChanged: {
            if (!rootWindow.active) {
                zoomHandler.zoomPressed = false
            }
        }
    }
}
