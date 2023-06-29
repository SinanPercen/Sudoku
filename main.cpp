#include "Sudoku.h"
#include "firstWindow.h"
#include <QtWidgets/QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    firstWindow firstWindow;
    firstWindow.show();
    return a.exec();
}
