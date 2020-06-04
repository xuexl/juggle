#include "mainwindow.h"

#include <QSurfaceFormat>
#include <QVTKOpenGLNativeWidget.h>

#include <QApplication>

int main(int argc, char *argv[])
{
    QSurfaceFormat::setDefaultFormat(QVTKOpenGLNativeWidget::defaultFormat());
    
    QApplication a(argc, argv);
    
    MainWindow w;
    w.show();
    
    return a.exec();
}
