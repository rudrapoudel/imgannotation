/**
 * Image Annotation Tool for image annotations with pixelwise masks
 *
 * Author: Rudra Poudel
 */
#include <QApplication>
#include <QFile>
#include "MainWindow.h"
#include <QtDebug>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow mainWin;
	mainWin.show();

    return app.exec();
}
