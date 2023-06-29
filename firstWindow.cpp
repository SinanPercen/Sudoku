
#include "firstWindow.h"
#include "ui_firstWindow.h"
#include "Sudoku.h"
//test
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
        //Extrahiere die Größe des Sudokufelds
        QString fieldSize = ui->gridSizeComboBox->currentText();



        if (fieldSize.isEmpty()) {
            fieldSize = "9x9"; // Setze Standardwert auf 9x9
        }
        QStringList sizeParts = fieldSize.split("x");
        int size = sizeParts[0].toInt();

        //Extrahiere Spielernamen in Liste; Prüfe Input auf Güligkeit
        QString playerAmountStr = ui->playerAmountcomboBox->currentText();
        int playerSize = playerAmountStr.toInt();

        /**
         *

        QString inputText = ui->nameInput->text();
        if(inputText.count(',') > 3){
            ui->errorLabel->setText("Too many comma's");
            return;
        }
        inputText.remove(' ');
        if(inputText.isEmpty()){
            ui->errorLabel->setText("Pick a name");
            return;
        }
        QStringList nameList = inputText.split(',',QString::SkipEmptyParts);
        */

        //Sudoku-Fenster
        Sudoku* sudoku = new Sudoku(size, playerSize);
        //sudoku->move(pos());
        hide();
        sudoku->show();
    }

