#ifndef SUDOKU_H
#define SUDOKU_H

#include <QWidget>
#include <QTableWidget>
#include <QMainWindow>
#include "ui_sudoku.h"
#include "cmath"
#include <iostream>
#include <vector>


class Sudoku : public QMainWindow
{
Q_OBJECT

public:
    explicit Sudoku(int size, int playerSize, QWidget *parent = nullptr);
    struct Player{
        QString name;
        int score;
    };
    /**
     * unnötig weil methoden
    */
    struct SudokuPos {
        int row;
        int column;
        int block;
    };

public slots:
    void addPlayer(const QString& name);
    void showCurrentName(const QString &name);

private:
    Ui::SudokuClass *ui;
    QLabel currentName;
    QTableWidget* sudokuTable;
    QTableWidget* playerTable;
    QList<Player> playerList;
    const int size;
    std::vector<char> fields;
    std::vector<char> solutionFields;
    int currentPlayer = 0;
    int currentPosition = -1;
    std::vector<QString> players;

    [[nodiscard]] int gridSize() const {
        return sqrt(size);
    }

    [[nodiscard]] int blockSize() const {
        return sqrt(gridSize());
    }

    int getRowFrom(int pos) const{
        return pos / gridSize();
    }
    int getColumnFrom(int pos) const {
        return pos % gridSize();;
    }
    int getBlockFrom(int pos) const {
        return (pos/(gridSize()*blockSize()))*blockSize() + getColumnFrom(pos)/blockSize();
    }
    /**
     * in methoden ausgelagert
     * @param pos
     * @return

    [[nodiscard]] SudokuPos getPos(int pos) const {
        SudokuPos sudokuPos{
        };
        sudokuPos.row = pos / gridSize();
        sudokuPos.column = pos % gridSize();
        sudokuPos.block = (pos/(gridSize()*blockSize()))*blockSize() + sudokuPos.column/blockSize();
        return sudokuPos;
    }*/
/**
 *
 * @return

    [[nodiscard]] std::vector<char> getAllowedCharacters() const {
        std::vector<char> allowed;
        for(int i = 0; i < gridSize(); i++) {
            //zuerst alle Zahlen, dann ab Ascii Code für A weiter
            int base;
            if(i < 9) {
                //49 ist Ascii Code für 1
                allowed.push_back(char(49 + i));
            } else {
                //65 ist Ascii Code für A
                allowed.push_back(char(65-9+i));
            }
        }
        return allowed;
    }
    */
    [[nodiscard]] std::vector<char> getAllowedCharacters() const {
        std::vector<char> allowed;
        for (int i = 1; i <= gridSize(); i++) {
            if (i <= 9) {
                allowed.push_back('0' + i);
            } else {
                allowed.push_back('A' + (i - 10));
            }
        }
        return allowed;
    }
    /** besser? für oben
     *
     for (int i = 1; i <= gridSize; i++) {
    if (i <= 9) {
        allowed.push_back('0' + i);
    } else {
        allowed.push_back('A' + (i - 10));
    }
}
     */
    void updateGUI();
    void createSolution();
    void initalizeBlock(int pos);
    int complete(int maxSolutions);
    [[nodiscard]] int findFree() const;
    [[nodiscard]] bool isPossible(int pos, char guess) const;

    void tableMouseClicked(const QModelIndex &index);

    void keyPressEvent(QKeyEvent *event);

    void initialGUI();
};

#endif // SUDOKU_H



