#include "test.h"

test::test(QObject *parent)
    : QObject{parent}
{
    qInfo() << this << "constructed" << parent;
}

test::~test(){
    qInfo() << this << "deconstructed" << parent();
}
