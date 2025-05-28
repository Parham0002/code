#include "dialog.h"
#include <QApplication>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    dialog dlg;
    dlg.show();

    return app.exec();
}