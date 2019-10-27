import QtQuick 2.0
import QtQuick.Controls 2.0

import CuteHMI 2.0 as CuteHMI

Item {
	id: extensionContainer

	CuteHMI.Dialog {
		id: dialog

		type: CuteHMI.Dialog.CRITICAL
		text: "Could not load extension '" + cutehmi_view_extensionBasename + "." + cutehmi_view_extensionMajor + "'."
		buttons: CuteHMI.Dialog.BUTTON_OK
	}

	Component.onCompleted: {
		if (cutehmi_view_extensionBasename && cutehmi_view_extensionMajor) {
			var qmlData = "import " + cutehmi_view_extensionBasename + " " + cutehmi_view_extensionMajor
			qmlData += "\n" + cutehmi_view_extensionComponent + " { anchors.fill: parent }\n"

			try {
				Qt.createQmlObject(qmlData, extensionContainer)
			} catch(error) {
				showDefaultScreen()
				dialog.informativeText = error.qmlErrors.length > 1 ? qsTr("Reasons: ") : qsTr("Reason: ")
				dialog.informativeText += error.qmlErrors.map(function (obj) { return obj.message }).join("; ") + "."
				createDialog(dialog)
			}
		} else {
			showDefaultScreen()
		}
	}

	function showDefaultScreen() {
		var defaultScreenComponent = Qt.createComponent("DefaultScreen.qml")
		var defaultScreen = defaultScreenComponent.createObject(extensionContainer)
		defaultScreen.anchors.centerIn = extensionContainer
	}
}

//(c)C: Copyright © 2019, Michal Policht <michpolicht@gmail.com>, Mr CuteBOT <michpolicht@gmail.com>, Wojtek Zygmuntowicz <wzygmuntowicz.zygmuntowicz@gmail.com>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
