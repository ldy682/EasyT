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
    QString getPrompt();
private:
    void handleLeft(QKeyEvent *e);
    void handleEnter();
    void handleBackSpace(QKeyEvent *e);
    void handleUp();
    void handleDown();

    void clearLine();
    QStack<QString> upHistory;
    QStack<QString> downHistory;
    bool skip;
    bool notPrompt();
    QString prompt;
};

#endif // TERMINALTEXTEDIT_H
