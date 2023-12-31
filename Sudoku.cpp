#include <QGridLayout>
#include <QLineEdit>
#include <QLabel>
#include <QHeaderView>
#include <QFile>
#include <QTextStream>
#include <iostream>
#include <random>
#include "Sudoku.h"
#include "cmath"
#include "set"
#include <QDebug>
#include <QKeyEvent>
#include <vector>
#include <algorithm>

Sudoku::Sudoku(int size, int playerSize, int difficulty, QWidget *parent) : QMainWindow(parent),
                                                                  ui(new Ui::SudokuClass), size(size*size) {
    ui->setupUi(this);
    sudokuTable = ui->sudokuTable;
    amountPlayers = playerSize;
    playerTable = ui->playerTable;
    int gridSize = this->gridSize();
    gameDiff = difficulty;
    QFont font;
    font.setPointSize(12);
    sudokuTable->setFont(font);
    sudokuTable->setMouseTracking(false);
    sudokuTable->setFrameShadow(QFrame::Plain);
    sudokuTable->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    sudokuTable->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    sudokuTable->setRowCount(gridSize); //auf size anpassen
    sudokuTable->setColumnCount(gridSize);
    sudokuTable->horizontalHeader()->setVisible(false);
    sudokuTable->horizontalHeader()->setMinimumSectionSize(10);
    sudokuTable->horizontalHeader()->setDefaultSectionSize(32);
    sudokuTable->horizontalHeader()->setHighlightSections(false);
    sudokuTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    sudokuTable->verticalHeader()->setVisible(false);
    sudokuTable->verticalHeader()->setMinimumSectionSize(10);
    sudokuTable->verticalHeader()->setDefaultSectionSize(32);
    sudokuTable->verticalHeader()->setHighlightSections(false);
    sudokuTable->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    sudokuTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    sudokuTable->setFocusPolicy(Qt::NoFocus);
    sudokuTable->setSelectionMode(QAbstractItemView::NoSelection);
    QTableWidget::connect(sudokuTable, &QTableWidget::clicked, this, &Sudoku::tableMouseClicked);

    //Initialisiere GUI
    initialGUI();

    //Initalisieren des Felds
    createSolution();

    // Schleife zur Initialisierung der Spieler in Playerlist
    //Spielernamen erstellen von Spieleranzahl und den Spielern hinzufügen
    for (int i = 0; i < playerSize; i++) {
        QString name = "Player ";
        name.append(QString::number(i + 1));
        players.append(name);
        scores.push_back(0);
    }

    //Spieler erstellen und in Tabelle hinzufügen
    for (int i = 0; i < playerSize; i++) {
        playerTable->insertRow(i);
        QTableWidgetItem* nameItem = new QTableWidgetItem(players[i]);
        QTableWidgetItem* scoreItem = new QTableWidgetItem(QString::number(scores[i])); //in QTSTring machen
        scoreItem->setTextAlignment(Qt::AlignCenter);

        playerTable->setItem(i, 0, nameItem);
        playerTable->setItem(i, 1, scoreItem);
        if (i==0) {
            nameItem->setBackgroundColor(Qt::yellow);
        }
    }
    playerTable->repaint();
    ui->currentName->setText(players[currentPlayer]); //aktuellen namen setzen und in gui anzeigen lassen
}

void Sudoku::tableMouseClicked(const QModelIndex &index) {
    int row = index.row();
    int column = index.column();

    // Position des geklickten Elements ermitteln
    int pos = row * gridSize() + column;
    currentPosition = pos;
}

void Sudoku::keyPressEvent(QKeyEvent *event) {
    ui->statusLabel->clear();
    //tastendruck länge 1
    if (event->count() != 1) {
        return;
    }
    try {

    //taste einlesen
    QChar qtKey = event->text().at(0);
    char key= qtKey.toLatin1();
    //wenn das Zeichen ein Buchstabe ist
    int asciiValue = static_cast<int>(key);
    if (asciiValue >= 97 & asciiValue <= 122) {
        key = std::toupper(key);
    }
    std::vector<char> allowedChars = getAllowedCharacters();


    QTableWidgetItem* item = sudokuTable->item(getRowFrom(currentPosition), getColumnFrom(currentPosition));
    if (item) { //wenn schon richtig belegtes feld abbrechen
        QColor backgroundColor = item->backgroundColor();
        if (backgroundColor == Qt::green) {
            return;
        }
    }

    fields[currentPosition] = key;
    //wenn gefunden, gibt key zurück und wenn nicht, gibt allowedChars.end() zurück
    if(std::find(allowedChars.begin(), allowedChars.end(), key) != allowedChars.end()) {
        int addToScore = asciiValue;
        //richtige Stelle in der ascii tabelle damit 1 = 1, ... und a = 10 usw. entspricht
        if (asciiValue > 96 ) { //wäre nicht drin
             addToScore = asciiValue-87;
        } else if(asciiValue > 47 & asciiValue <58) {
            addToScore = asciiValue - 48;
        }
        //wenn wenn möglich
        if (isPossible(currentPosition, key)) {
            if (key == solutionFields[currentPosition]) { //wenn möglich und auch richtig
                scores[currentPlayer] += addToScore;
                usedCharsInTurn.push_back(key);
                changeScore();
                sudokuTable->item(getRowFrom(currentPosition), getColumnFrom(currentPosition))->setBackgroundColor(Qt::green);
                //checken ob spiel vorbei ist
                if(checkIfGameWon()) {
                    QString winner = checkWinner();
                    QString output = "Game over! ";
                    output.append(winner);
                    output.append(" has won.");
                    ui->statusLabel->setText(output);
                }
            } else {  // Gültig aber nicht richtig -> gelb
                sudokuTable->item(getRowFrom(currentPosition), getColumnFrom(currentPosition))->setBackgroundColor(Qt::yellow);
            }
        } else { // Nicht gültig -> rot
            sudokuTable->item(getRowFrom(currentPosition), getColumnFrom(currentPosition))->setBackgroundColor(Qt::red);
            //spieler wecheln
            changePlayer();
        }

        updateGUI();

    } else {
        ui->statusLabel->setText("Ungültige Eingabe");
        throw std::runtime_error("Eingabefehler");
    }
    } catch (const std::exception& e) {
        std::cout << "Fehler: " << e.what() << std::endl;
    }
}

void Sudoku::changePlayer() {
    int previousPlayer = currentPlayer;
    if (currentPlayer == amountPlayers - 1) {
        currentPlayer = 0;
    } else {
        currentPlayer++;
    }
    ui->currentName->setText(players[currentPlayer]); //aktuellen namen setzen und in gui anzeigen lassen
    playerTable->item(previousPlayer, 0)->setBackgroundColor(Qt::white);
    playerTable->item(currentPlayer, 0)->setBackgroundColor(Qt::yellow);
    usedCharsInTurn.clear();
}
void Sudoku::changeScore() {
    QTableWidgetItem* scoreItem = new QTableWidgetItem(QString::number(scores[currentPlayer]));
    scoreItem->setTextAlignment(Qt::AlignCenter);
    ui->playerTable->setItem(currentPlayer, 1, scoreItem);
    playerTable->repaint();
}

class Attempt {
public:
    Attempt(int pos, int charIndex) {
        this->pos = pos;
        this->charIndex = charIndex;
    }

    int pos;
    int charIndex;
    void next() {
        ++charIndex;
    }
};

QString Sudoku:: checkWinner() {
    int highest = 0;
    int currentWinner = 0;
    for(int i = 0; i < scores.size(); i++) {
        if (scores[i] > highest) {
            highest = scores[i];
            currentWinner = i;
        }
    }
    return players[currentWinner];
}

void Sudoku::initialGUI() {
    for(int i = 0; i < size; i++) {
        QTableWidgetItem *entry = new QTableWidgetItem(QString::fromStdString(std::string(1, ' ')));
        entry->setTextAlignment(Qt::AlignCenter);
        sudokuTable->setItem(getRowFrom(i), getColumnFrom(i), entry);
    }
}

bool Sudoku::checkIfGameWon() {
    for (int i = 0; i < fields.size(); i++) {
        if(sudokuTable->item(getRowFrom(i), getColumnFrom(i))->backgroundColor() != Qt::green) {
           return false;
        }
    }
    return true;
}


void Sudoku::updateGUI() {
    for(int i = 0; i < size; i++) {
        QTableWidgetItem *entry = sudokuTable->item(getRowFrom(i), getColumnFrom(i));
        entry->setText( QString::fromStdString(std::string(1, fields.at(i))));
        entry->setTextAlignment(Qt::AlignCenter);
    }
}


void Sudoku::createSolution() {
    for(int i = 0; i < size; i++) {
        fields.push_back(' ');
    }
    for(int i = 0; i < blockSize(); i++) {
        initalizeBlock(i * blockSize() + i * blockSize() * gridSize());
    }

    complete(1);
    solutionFields.assign(fields.begin(), fields.end());
    int maxDelete;
    switch (gameDiff) {
        case 1:
            maxDelete = 2 * gridSize();
            break;
        case 2:
            maxDelete = 3 * gridSize();
            break;
        default:
            maxDelete = 5 * gridSize();
            break;
    }
    std::set<int> deleted;
    while(true) {
        int rnd = std::rand() % size;
        if (deleted.find(rnd) != deleted.end()) {
            continue;
        }

        for(int iterator : deleted) {
            fields.at(iterator) = ' ';
        }
        char tmp = fields.at(rnd);
        fields.at(rnd) = ' ';
        deleted.insert(rnd);

        if(deleted.size() <= maxDelete && complete(2) != 2) {
            continue;
        }

        for(int iterator : deleted) {
            fields.at(iterator) = ' ';
        }
        fields.at(rnd) = tmp;
        break;
    }

    updateGUI();
    //alle grün machen
    for (int i = 0; i < fields.size(); i++) {
        if(sudokuTable->item(getRowFrom(i), getColumnFrom(i))->text() != ' ')
        sudokuTable->item(getRowFrom(i), getColumnFrom(i))->setBackgroundColor(Qt::green);
    }

}

void Sudoku::initalizeBlock(const int pos) {
    std::vector<char> characters = getAllowedCharacters();
    std::shuffle(characters.begin(), characters.end(), std::mt19937(std::random_device()()));
    for(int row = 0; row < blockSize(); row++) {
        for(int column = 0; column < blockSize(); column++) {
            fields.at(pos + column + (row * gridSize())) = characters.back();
            characters.pop_back();
        }
    }
}




int Sudoku::complete(const int maxSolutions) {
    std::vector<char> characters = getAllowedCharacters();
    std::vector<Attempt> attempts;
    int firstFree = findFree();
    if(firstFree != -1) {
        attempts.emplace_back(firstFree, 0);
        fields[firstFree] = characters.at(0);
    }

    int found = 0;
    while(!attempts.empty()) {
        Attempt current = attempts.back();
        if(isPossible(current.pos, characters.at(current.charIndex))) { //gültiger versuch
            int nextFree = findFree();
            if ( nextFree == -1 ) {
                if ( ++found == maxSolutions ) {
                    return found;
                }
                current.next();
                while (current.charIndex >= characters.size()) { //backtracking
                    attempts.pop_back();
                    fields.at(current.pos) = ' ';
                    if(attempts.empty()) {
                        return found;
                    }
                    current = attempts.back();
                    current.next();
                }
                //naechster versuch gefunden
                attempts.back() = current;
                fields.at(current.pos) = characters.at(current.charIndex);
            }
            else {//weitere felder finden
                attempts.emplace_back(nextFree, 0);
                fields.at(nextFree) = characters.at(0);
            }
        } else {//ungültiger versuch
            current.next();
            //hohe eingabe
            while (current.charIndex >= characters.size()) {
                attempts.pop_back();
                fields.at(current.pos) = ' ';
                if(attempts.empty()) {
                    return found;
                }
                current = attempts.back();
                current.next();
            }
            //neuer versuch gefunden
            attempts.back() = current;
            fields.at(current.pos) = characters.at(current.charIndex);
        }
    }

    return -1;
}
//freies feld für complete finden
int Sudoku::findFree() const {
    for(int i = 0; i < size; i++) {
        if(fields.at(i) == ' ') {
            return i;
        }
    }
    return -1;
}

bool Sudoku::isPossible(int pos, char guess) const {
    for(int i = 0; i < size; i++) {
        if(i == pos || fields.at(i) != guess) {
            continue;
        }
        if(getBlockFrom(pos) == getBlockFrom(i) || getRowFrom(pos) == getRowFrom(i) ||
                getColumnFrom(pos) == getColumnFrom(i)) {
            return false;
        }
    }
    return true;
}


