/*
   DivvyDroid - Application to screencast and remote control Android devices.

   Copyright (C) 2019 - Mladen Milinkovic <maxrd2@smoothware.net>

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/
#ifndef DEVICETOUCHHANDLER_H
#define DEVICETOUCHHANDLER_H

#include "inputhandler.h"

class DeviceTouchHandler : public InputHandler
{
public:
	explicit DeviceTouchHandler(QObject *parent = nullptr);
	virtual ~DeviceTouchHandler();

	bool init() override;

protected:
	bool eventFilter(QObject *obj, QEvent *ev) override;

private:
	bool m_inputMouseDown;
	qint32 m_lastTouchId;
};

#endif // DEVICETOUCHHANDLER_H