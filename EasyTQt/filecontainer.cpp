#include "filecontainer.h"

FileContainer::FileContainer(QWidget *parent, QString filename): QLineEdit(parent) {
    this->setReadOnly(true);
    this->setText(filename);
}

FileContainer::~FileContainer(){

}
