#include "dialog.h"
#include <QApplication>

int main(int argc, char **argv)
{
    qDebug() << "Qt version:" << QT_VERSION_STR;

    QApplication app(argc, argv);

    dialog dlg;
    dlg.show();

    return app.exec();
}