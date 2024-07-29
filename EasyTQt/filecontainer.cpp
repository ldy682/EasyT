#include "filecontainer.h"
#include <QStringList>
#include <QDebug>

FileContainer::FileContainer(QWidget *parent): QScrollArea(parent) {
    QDir curDir = QDir::currentPath();
    QStringList filenames = curDir.entryList(QDir::NoDotAndDotDot | QDir::AllEntries);

    QVBoxLayout *scrollLayout = new QVBoxLayout(this);
    foreach(QString file, filenames){
        scrollLayout->addWidget(new QLabel(file));
    }
    QWidget *scrollWidget = new QWidget(this);
    scrollWidget->setLayout(scrollLayout);

    this->setWidget(scrollWidget);
}

FileContainer::~FileContainer(){

}
