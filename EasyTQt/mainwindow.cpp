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
    addDockWidget(Qt::LeftDockWidgetArea, dockWidget);

    QWidget *widgetContainer = new QWidget(dockWidget);
    QVBoxLayout *vBox = new QVBoxLayout(widgetContainer);
    vBox->setContentsMargins(0,0,0,0);

    FileContainer *file = new FileContainer(widgetContainer, "smth");
    FileContainer *file2 = new FileContainer(widgetContainer, "smth2");

    vBox->addWidget(file);
    vBox->addWidget(file2);
    vBox->addStretch();


    dockWidget->setWidget(widgetContainer);

}

MainWindow::~MainWindow()
{
    delete ui;
}
