#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "terminaltextedit.h"
#include <QWidget>
#include <QDockWidget>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    this->setStyleSheet("background-color: beige;");

    ui->setupUi(this);
    TerminalTextEdit *textEdit = new TerminalTextEdit(this);
    setCentralWidget(textEdit);

    QDockWidget *dock = new QDockWidget("DockWidget", this);
    addDockWidget(Qt::LeftDockWidgetArea, dock);

    QWidget *dockContent = new QWidget(dock);
    QVBoxLayout *dockLayout = new QVBoxLayout(dockContent);
    // dock->add}

MainWindow::~MainWindow()
{
    delete ui;
}
