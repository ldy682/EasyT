#include "terminaltextedit.h"
#include <QFont>
#include <QTextCursor>

TerminalTextEdit::TerminalTextEdit(QWidget *parent) : QTextEdit(parent) {
    // QFont font("Monospace", 12);
    this->setFont(QFont("Monospace", 12));
    this->setCursorWidth(12);
}

TerminalTextEdit::~TerminalTextEdit(){

}
