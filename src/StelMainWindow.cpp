/*
 * Stellarium
 * Copyright (C) 2007 Fabien Chereau
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Suite 500, Boston, MA  02110-1335, USA.
 */


#include "StelMainWindow.hpp"
#include <stdexcept>
#include "StelApp.hpp"
#include "StelMainGraphicsView.hpp"
#include "StelFileMgr.hpp"
#include "StelModuleMgr.hpp"
#include "StelTranslator.hpp"

#include <QSettings>
#include <QResizeEvent>
#include <QIcon>
#include <QDebug>
#include <QCoreApplication>
#include <QApplication>
#include <QHBoxLayout>
//#include <QGLWidget> //silas

#ifdef BUILD_FOR_MAEMO
#include <QtGui/QX11Info>
#include <X11/Xlib.h>
#include <X11/Xatom.h>
#endif

//silas
//#ifdef Q_OS_UNIX
//#include <QX11Info>
//#include <X11/Xatom.h>
//#include <X11/Xlib.h>
//#endif




void StelMainWindow::writeX11OrientationAngleProperty(Orientation orientation)
{
#ifdef Q_WS_X11

    WId id = winId();
    Display *display = QX11Info::display();
    if (!display)
        return;

    Atom orientationAngleAtom = XInternAtom(display, "_MEEGOTOUCH_ORIENTATION_ANGLE", False);

    XChangeProperty(display, id, orientationAngleAtom, XA_CARDINAL, 32, PropModeReplace, (unsigned char*)&orientation, 1);
    //qDebug() << "Changed orientation: " << orientation;


#endif

}


// Initialize static variables
StelMainWindow* StelMainWindow::singleton = NULL;

StelMainWindow::StelMainWindow() : QMainWindow(NULL)
{
	// Can't create 2 StelMainWindow instances
	Q_ASSERT(!singleton);
	singleton = this;

	setAttribute(Qt::WA_NoSystemBackground);

	setWindowIcon(QIcon(":/mainWindow/icon.bmp"));
	initTitleI18n();

	mainGraphicsView = new StelMainGraphicsView(this);
	setCentralWidget(mainGraphicsView);

#ifdef BUILD_FOR_MAEMO
	if (!winId())
	{
		qWarning("Can't grab keys unless we have a window id");
		return;
	}
	unsigned long val = 1;
	Atom atom = XInternAtom(QX11Info::display(), "_HILDON_ZOOM_KEY_ATOM", False);
	if (!atom)
	{
		qWarning("Unable to obtain _HILDON_ZOOM_KEY_ATOM. This only works on a Maemo 5 device!");
	}
	else
	{
		XChangeProperty (QX11Info::display(), winId(), atom, XA_INTEGER, 32,
			PropModeReplace, reinterpret_cast<unsigned char *>(&val), 1);
	}
#endif
}

// Update the translated title
void StelMainWindow::initTitleI18n()
{
    QString appNameI18n = q_("Stellarium %1").arg(""); //StelUtils::getApplicationVersion());
	setWindowTitle(appNameI18n);
}

void StelMainWindow::init(QSettings* conf)
{
	int width = conf->value("video/screen_w", 800).toInt();
	int height = conf->value("video/screen_h", 600).toInt();
	resize(width, height);
	if (conf->value("video/fullscreen", true).toBool())
	{
		setFullScreen(true);
	}
	else
	{
		setFullScreen(false);
		int x = conf->value("video/screen_x", 0).toInt();
		int y = conf->value("video/screen_y", 0).toInt();
		move(x, y);
	}
	show();
	// Process the event to make the window visible and create the openGL context.
	QCoreApplication::processEvents();
	mainGraphicsView->init(conf);
}

void StelMainWindow::deinit()
{
	mainGraphicsView->deinitGL();
}

// Alternate fullscreen mode/windowed mode if possible
void StelMainWindow::toggleFullScreen()
{
	// Toggle full screen
	if (getFullScreen())
	{
		setFullScreen(false);
	}
	else
	{
		setFullScreen(true);
	}
}

// Get whether fullscreen is activated or not
bool StelMainWindow::getFullScreen() const
{
	return windowState().testFlag(Qt::WindowFullScreen);
}

// Set whether fullscreen is activated or not.
// Don't use the showFullScreen() and showNormal() methods since they have an unexpected behaviour.
void StelMainWindow::setFullScreen(bool b)
{
	if (b)
		setWindowState(windowState() | Qt::WindowFullScreen);
	else
		setWindowState(windowState() & ~Qt::WindowFullScreen);
}

void StelMainWindow::closeEvent(QCloseEvent* event)
{
	event->ignore();
	QCoreApplication::exit();
}

// thanks to elemental from talk.maemo.org for the focusing code
void StelMainWindow::focusOut(QFocusEvent *)
{
    if (mainGraphicsView)
        mainGraphicsView->stopMainLoop();
}

void StelMainWindow::changeEvent(QEvent *e)
{
    if (mainGraphicsView)
    {
        if (e->type() == QEvent::WindowStateChange)
        {
            if (windowState().testFlag(Qt::WindowMinimized))
                mainGraphicsView->stopMainLoop();
            else
                mainGraphicsView->startMainLoop();
        }
    }
}
