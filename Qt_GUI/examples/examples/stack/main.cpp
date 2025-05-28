#include "maindlg.h"
#include <QApplication>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    maindlg dlg;
    dlg.show();

    return app.exec();
}