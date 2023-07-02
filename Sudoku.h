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

private:
    Ui::SudokuClass *ui;
    QLabel currentName;
    QTableWidget* sudokuTable;
    QTableWidget* playerTable;
    const int size;
    std::vector<char> fields;
    std::vector<char> solutionFields;
    int currentPlayer = 0;
    int currentPosition = -1;
    QList<QString> players;
    std::vector<int> scores;
    int amountPlayers = 0;
    std::vector<char> usedCharsInTurn;

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

    void updateGUI();
    void createSolution();
    void initalizeBlock(int pos);
    int complete(int maxSolutions);
    [[nodiscard]] int findFree() const;
    [[nodiscard]] bool isPossible(int pos, char guess) const;

    void tableMouseClicked(const QModelIndex &index);

    void keyPressEvent(QKeyEvent *event);

    void initialGUI();

    void changePlayer();

    void changeScore();

    bool checkIfGameWon();
};

#endif // SUDOKU_H



