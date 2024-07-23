

// main.cpp
#include <QtCore>
#include <QTimer>
#include "test.h"

test* getTest(QObject* parent){
    return new test(parent);
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QTimer timer;

    timer.singleShot(3000, &a, QCoreApplication::quit);

    test* dog = getTest(&a);
    dog->setObjectName("doggy");

    int value = a.exec();
    qInfo() << "value: " << value;
    return value;
}

