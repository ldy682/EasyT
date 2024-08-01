#include "terminaltextedit.h"
#include <QFont>
#include <QTextCursor>

TerminalTextEdit::TerminalTextEdit(QWidget *parent) : QPlainTextEdit(parent) {
    this->setFont(QFont("Monospace", 10));
    this->setCursorWidth(10);

}

TerminalTextEdit::~TerminalTextEdit(){

}
