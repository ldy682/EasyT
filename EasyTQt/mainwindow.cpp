#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "terminaltextedit.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    TerminalTextEdit *textEdit = new TerminalTextEdit(this);
    // setCentralWidget(textEdit);
}

MainWindow::~MainWindow()
{
    delete ui;
}
