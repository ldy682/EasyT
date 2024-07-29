#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "terminaltextedit.h"
#include "filecontainer.h"
#include <QWidget>
#include <QDockWidget>
#include <QVBoxLayout>
#include <QRect>
#include <QLineEdit>
#include <QSpacerItem>
#include <QMargins>
#include <QScrollArea>
#include <QString>
#include <QScrollBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    // initial set up of terminal and its background
    this->setStyleSheet("background-color: beige;");
    ui->setupUi(this);
    TerminalTextEdit *textEdit = new TerminalTextEdit(this);
    setCentralWidget(textEdit);

    // set up for file bar on the left
    QDockWidget *dockWidget = new QDockWidget("Current Directory Files", this);
    dockWidget->setFeatures(QDockWidget::DockWidgetMovable);
    addDockWidget(Qt::LeftDockWidgetArea, dockWidget);

    FileContainer *files = new FileContainer(this);

    dockWidget->setWidget(files);

}

MainWindow::~MainWindow()
{
    delete ui;
}
