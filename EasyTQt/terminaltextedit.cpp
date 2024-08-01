#include "terminaltextedit.h"
#include <QFont>
#include <QTextCursor>

TerminalTextEdit::TerminalTextEdit(QWidget *parent) : QPlainTextEdit(parent),
    prompt(QString("$ ")) {
    this->setFont(QFont("Monospace", 10));
    this->setCursorWidth(10);
    insertPlainText(prompt);
}

void TerminalTextEdit::setPrompt(QString str){
    this->prompt = str;
}

QString TerminalTextEdit::getPrompt(){
    return this->prompt;
}

void TerminalTextEdit::keyPressEvent(QKeyEvent *e){
    switch(e->key()){
    case Qt::Key_Return:
        handleEnter();
        break;
    case Qt::Key_Backspace:
        handleBackSpace(e);
        break;
    case Qt::Key_Up:
        handleUp();
        break;
    case Qt::Key_Down:
        handleDown();
        break;
    case Qt::Key_Left:
        handleLeft(e);
        break;
    default:
        QPlainTextEdit::keyPressEvent(e);
        break;
    }
}

void TerminalTextEdit::handleEnter(){
    QTextCursor curs = this->textCursor();
    curs.select(QTextCursor::LineUnderCursor);
    QString inp = curs.selectedText();
    upHistory.push(inp);

    return ;
}

void TerminalTextEdit::handleBackSpace(QKeyEvent *e){
    QPlainTextEdit::keyPressEvent(e);
    // set a limit to how much backspace the user can do
}

void TerminalTextEdit::handleLeft(QKeyEvent *e){
    QPlainTextEdit::keyPressEvent(e);
    // handle similarly to backspace
}

void TerminalTextEdit::handleUp(){
    if(upHistory.count() < 1){
        return;
    }
    QString cmd = upHistory.pop();
    downHistory.push(cmd);
    clearLine();
    insertPlainText(cmd);
}

void TerminalTextEdit::handleDown(){
    if(downHistory.count() < 1){
        return;
    }
    QString cmd = downHistory.pop();
    upHistory.push(cmd);
    clearLine();
    insertPlainText(cmd);
}

void TerminalTextEdit::clearLine(){
    QTextCursor curs = this->textCursor();
    curs.select(QTextCursor::LineUnderCursor);
    curs.clearSelection();
    insertPlainText(getPrompt());
    return;
}

TerminalTextEdit::~TerminalTextEdit(){

}
