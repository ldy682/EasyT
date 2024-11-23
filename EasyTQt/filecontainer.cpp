#include "filecontainer.h"
#include <QStringList>
#include <QDebug>

FileContainer::FileContainer(QWidget *parent): QScrollArea(parent) {
    setDirectory();
}

void FileContainer::setDirectory(){
    QDir curDir = QDir::currentPath();
    QStringList directoryNames = curDir.entryList(QDir::NoDotAndDotDot | QDir::AllDirs);
    QStringList fileNames = curDir.entryList(QDir::NoDotAndDotDot | QDir::Files);

    scrollLayout = new QVBoxLayout(this);
    foreach(QString directory, directoryNames){
        QLabel* label = new QLabel(directory);
        QPalette palette = label->palette();
        palette.setColor(QPalette::WindowText, Qt::magenta);
        label->setPalette(palette);
        scrollLayout->addWidget(label);
    }
    foreach(QString file, fileNames){
        scrollLayout->addWidget(new QLabel(file));
    }
    scrollWidget = new QWidget(this);
    scrollWidget->setLayout(scrollLayout);

    this->setWidget(scrollWidget);
}

void FileContainer::refreshDirectory(){
    while (QLayoutItem* item = scrollLayout->takeAt(0)) {
        if (QWidget* widget = item->widget()) {
            widget->deleteLater(); // Schedule widget for deletion
        }
        delete item; // Delete the layout item
    }
    setDirectory();
}

FileContainer::~FileContainer(){

}
