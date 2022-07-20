#include "Sudoku.h"
#include <QFileDialog>
#include <QDir>
#include <fstream>
#include <QDebug>
#include <QTextStream>
#include <iostream>

Sudoku::Sudoku(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SudokuClass())
{
    // Set up UI
    ui->setupUi(this);

    // Connect signals and slots
    connect(ui->pushButton, SIGNAL(released()), this, SLOT(print()));
    connect(ui->actionSolve_entire_puzzle, SIGNAL(triggered()), this, SLOT(solve()));
    connect(ui->action_Open, SIGNAL(triggered()), this, SLOT(loadPuzzle()));
}

Sudoku::~Sudoku()
{
    delete ui;
}

// update cell values in UI
void Sudoku::print()
{
    ui->textEdit->clear();

    for (int r = 0; r < 9; r++)
    {
        for (int c = 0; c < 9; c++)
        {
            // set cell widget text
            ui->textEdit->insertPlainText(QString::number(s.getCellValue(r, c)) + " ");
            QTextStream(stdout) << c << " ";
        }

        ui->textEdit->insertPlainText("\n");
        QTextStream(stdout) << "\n";
    }
}

void Sudoku::solve()
{
    ui->textEdit->clear();
    ui->textEdit->insertPlainText("Solving...");
    s.solve();
    print();
}

void Sudoku::loadPuzzle()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Open a puzzle", "Puzzles//", "Text files (*.txt);;Puzzle files (*.sud)");

    s.loadFromFile(filePath.toStdString());
    print();
}