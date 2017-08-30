#ifndef CUTEHMI_CUTEHMI__AUTHSSH__1__LIB_INCLUDE_AUTHSSH_AUTH_HPP
#define CUTEHMI_CUTEHMI__AUTHSSH__1__LIB_INCLUDE_AUTHSSH_AUTH_HPP

#include <QObject>

namespace cutehmi {
namespace authssh {

class Auth:
	public QObject
{
	Q_OBJECT

	public:
//		Q_PROPERTY(QString user READ user NOTIFY userChanged)

		explicit Auth(QObject * parent = nullptr);

	signals:
//		void userChanged();

	public slots:
		void login(const QString & user, const QString & password);

		void logout();
};

}
}

#endif

//(c)MPWZ: Copyright © 2017, Michal Policht, Wojciech Zygmuntowicz. All rights reserved.
//(c)MPWZ: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
