#include "filecontainer.h"
#include <QStringList>
#include <QDebug>

FileContainer::FileContainer(QWidget *parent): QScrollArea(parent) {
    setDirectory();
}

void FileContainer::setDirectory(){
    QDir curDir = QDir::currentPath();
    QStringList filenames = curDir.entryList(QDir::NoDotAndDotDot | QDir::AllEntries);

    scrollLayout = new QVBoxLayout(this);
    foreach(QString file, filenames){
        scrollLayout->addWidget(new QLabel(file));
    }
    scrollWidget = new QWidget(this);
    scrollWidget->setLayout(scrollLayout);

    this->setWidget(scrollWidget);
}

void FileContainer::refreshDirectory(){
    setDirectory();
}

FileContainer::~FileContainer(){

}
