#include "terminaltextedit.h"
#include <QFont>

TerminalTextEdit::TerminalTextEdit(QWidget *parent) : QTextEdit(parent) {
    QFont font("Monospace", 12);
    this->setFont(font);
}

TerminalTextEdit::~TerminalTextEdit(){

}
