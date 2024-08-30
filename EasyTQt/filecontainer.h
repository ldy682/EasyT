// Contains the display of files in the current directory meant to be docked
#ifndef FILECONTAINER_H
#define FILECONTAINER_H

#include <QLabel>
#include <QVBoxLayout>
#include <QDir>
#include <QScrollArea>

class FileContainer: public QScrollArea
{
public:
    FileContainer(QWidget *parent);
    void setDirectory();
    void getCurDirectory();
    ~FileContainer();
public slots:
    void refreshDirectory();
    QVBoxLayout *scrollLayout;
    QWidget *scrollWidget;

};

#endif // FILECONTAINER_H
