#ifndef FILECONTAINER_H
#define FILECONTAINER_H

#include <QLineEdit>

class FileContainer: public QLineEdit
{
public:
    FileContainer(QWidget *parent, QString filename);
    ~FileContainer();
};

#endif // FILECONTAINER_H
