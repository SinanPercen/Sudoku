
#include "firstWindow.h"
#include "ui_firstWindow.h"
#include "Sudoku.h"
firstWindow::firstWindow(QWidget *parent)
        : QMainWindow(parent),
          ui(new Ui::mainWindow)
{
    ui->setupUi(this);

    ui->errorLabel->setStyleSheet("color: red");
    connect(ui->startButton, &QPushButton::clicked, this, &firstWindow::on_Start_clicked);
}

firstWindow::~firstWindow()
{
    delete ui;
}
    void firstWindow::on_Start_clicked()
    {
        ui->errorLabel->clear();
        QString fieldSize = ui->gridSizeComboBox->currentText();
        QStringList sizeParts = fieldSize.split("x");
        int size = sizeParts[0].toInt();

        QString playerAmountStr = ui->playerAmountcomboBox->currentText();
        int playerSize = playerAmountStr.toInt();

        //Schwierigkeit einstellen
        int diff = ui->difficultyComboBox->currentIndex();
        diff++;

        //Sudoku-Fenster
        Sudoku* sudoku = new Sudoku(size, playerSize, diff);
        hide();
        sudoku->show();
    }

