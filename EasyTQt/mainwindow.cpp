#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "terminaltextedit.h"
#include "filecontainer.h"
#include <QWidget>
#include <QDockWidget>
#include <QVBoxLayout>
#include <QRect>
#include <QLineEdit>

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
    QDockWidget *dockWidget = new QDockWidget("Files Location", this);
    dockWidget->setFeatures(QDockWidget::DockWidgetMovable);

    QWidget *widgetContainer = new QWidget(dockWidget);
    QVBoxLayout *vBox = new QVBoxLayout(widgetContainer);
    FileContainer *file = new FileContainer(widgetContainer, "smth");
    vBox->addWidget(file);

    dockWidget->setWidget(widgetContainer);
    addDockWidget(Qt::LeftDockWidgetArea, dockWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}
