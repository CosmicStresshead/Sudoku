#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Sudoku.h"
#include "SudokuCore.h"

QT_BEGIN_NAMESPACE
namespace Ui { class SudokuClass; };
QT_END_NAMESPACE

class Sudoku : public QMainWindow
{
    Q_OBJECT

public:
    Sudoku(QWidget *parent = nullptr);
    ~Sudoku();

private slots:
    void print();
    void solve();
    void loadPuzzle();

private:
    Ui::SudokuClass* ui;
    SudokuCore s;

};
