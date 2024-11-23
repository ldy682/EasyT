#ifndef TERMINALTEXTEDIT_H
#define TERMINALTEXTEDIT_H

#include <QPlainTextEdit>
#include <QKeyEvent>
#include <QStack>
#include <QString>

class TerminalTextEdit : public QPlainTextEdit
{
Q_OBJECT
public:
    TerminalTextEdit(QWidget *parent);
    ~TerminalTextEdit();
protected:
    void keyPressEvent(QKeyEvent *e);
    void setPrompt(QString str);
    // void mousePressEvent(QMouseEvent *e);
    // void mouseDoubleClickEvent(QMouseEvent *e);
    QString getPrompt();
private:
    void handleLeft(QKeyEvent *e);
    void handleEnter();
    void handleBackSpace(QKeyEvent *e);
    void handleUp();
    void handleDown();
    void clearLine();
    QString cleanResult(QString str); // cleans the shell output
    QStack<QString> upHistory;
    QStack<QString> downHistory;
    bool skip;
    bool notPrompt();
    bool isCurrentBlock(QTextBlock block);
    QString prompt;

    // this is used for making the master and slave connection to talk to the shell
    int aMaster;
    int aSlave;
    pid_t pid;

signals:
    void sendCmd(QString cmd);
public slots:
    void recvRes(QString cmd);
    // void redirectCursor();
};

#endif // TERMINALTEXTEDIT_H
