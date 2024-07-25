#ifndef TERMINALTEXTEDIT_H
#define TERMINALTEXTEDIT_H

#include <QTextEdit>

class TerminalTextEdit : public QTextEdit
{
Q_OBJECT
public:
    TerminalTextEdit(QWidget *parent);
    ~TerminalTextEdit();
};

#endif // TERMINALTEXTEDIT_H
