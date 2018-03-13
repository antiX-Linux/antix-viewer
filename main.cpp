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

//  if all's well, this fn will return 1
static int dropElevatedPrivileges()
{
    //   COULD check, and conditionally skip           if (getuid() == 0) || geteuid == 0)

    //    initgroups()
    // ref:  https://www.safaribooksonline.com/library/view/secure-programming-cookbook/0596003943/ch01s03.html#secureprgckbk-CHP-1-SECT-3.3

    //   change guid + uid   ~~  nobody (uid 65534), nogroup (gid 65534), users (gid 100)
    if (setgid(65534) != 0) return 1;  //  ("Failed to set nonroot GID") so apparently NOT root
    if (setuid(65534) != 0) return 1;  //  ("Failed to set nonroot UID") so apparently NOT root
    //                                                          or failed due to brittle/flawed expectation that nobody and nogroup exist

    // On systems with defined _POSIX_SAVED_IDS in the unistd.h file, it should be 
    // impossible to regain elevated privs after the setuid() call, above.  Test, try to regain elev priv:
    if (setuid(0) != -1)  return 0;   // and the calling fn should EXIT/abort the program
    //  COULD also confirm that setregid() fails
    
    // change cwd, for good measure (if unable to, treat as overall failure)
    if (chdir("/tmp") != 0)   return 0;  // consider fprint()ing or logging the failure reason
        
    return 1;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon("/usr/share/pixmaps/antix-viewer.png"));

    QString arg1 = argv[1];
    QString url;
    QString title;

    if(!dropElevatedPrivileges())
    {
        exit(1);  // log a reason, display a dialogbox?
    }
    
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
