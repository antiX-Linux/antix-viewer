/*****************************************************************************
 * antixview.h
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

#ifndef ANTIXVIEW_H
#define ANTIXVIEW_H

#include <QMainWindow>
#include <QWebView>
#include <QLineEdit>
#include <QProgressBar>
#include <QTimer>
//#include <QResizeEvent>

class MainWindow : public QMainWindow
{
    Q_OBJECT

protected:
    QTimer *timer;
    void keyPressEvent(QKeyEvent *event);
    void resizeEvent(QResizeEvent *event);

public:
    MainWindow(QString url, QString title, QWidget *parent = 0);    
    ~MainWindow();
    void displaySite(QString url, QString title);

public slots:
    void search();
    void findInPage();
    void loading();
    void done(bool);
    void procTime();

private:
    QLineEdit *searchBox;
    QProgressBar *progressBar;
    QString word;
    QToolBar *toolBar;
    QWebView *webview;

};


#endif // ANTIXVIEW_H
