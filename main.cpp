/*****************************************************************************
 * main.cpp
 *****************************************************************************
 * Copyright (C) 2014 MX Authors
 *
 * Authors: Adrian
 *          MX Linux <http://mxlinux.org>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * MX Viewer is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with MX Viewer.  If not, see <http://www.gnu.org/licenses/>.
 **********************************************************************/

#include <QApplication>
#include <QMessageBox>
#include "antixview.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon("/usr/share/pixmaps/antix-viewer.png"));

    QString arg1 = argv[1];
    QString url;
    QString title;

    if (argc == 1) {
        url = "http://duckduckgo.com";
        title = "antiX Viewer";
    } else if (arg1 == "--help" or arg1 == "-h") {
        QMessageBox::information(0, QString::null,
                                 QApplication::tr("Usage: call program with: antix-view URL [window title]\n\n"
                                                  "The 'antix-viewer' program will display the URL content in a window, window title is optional.\n\n"
                                                  "note: 'URL' destination can also be a local document or imagefile, e.g.  file:///path/to/local/file"));
        return 1;
    } else {
        url = argc > 1 ? QString(argv[1]) : QString();
        title = argc > 2 ? QString(argv[2]) : QString();
    }

    MainWindow w(url, title);
    w.show();

    return a.exec();
}
