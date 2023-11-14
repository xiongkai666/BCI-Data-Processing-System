
#include <QApplication>
#include "boardselectdialog.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

#ifdef __APPLE__
    app.setStyle(QStyleFactory::create("Fusion"));
#endif

    BoardSelectDialog boardSelectDialog;
    return app.exec();
}
