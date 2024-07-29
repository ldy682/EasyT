#include "terminaltextedit.h"
#include <QFont>
#include <QTextCursor>

TerminalTextEdit::TerminalTextEdit(QWidget *parent) : QTextEdit(parent) {
    this->setFont(QFont("Monospace", 10));
    this->setCursorWidth(10);
    // add signals and slots eventually
}

TerminalTextEdit::~TerminalTextEdit(){

}
