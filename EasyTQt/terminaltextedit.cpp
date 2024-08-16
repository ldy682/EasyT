#include "terminaltextedit.h"
#include <QFont>
#include <QTextCursor>
#include <QTextBlock>

TerminalTextEdit::TerminalTextEdit(QWidget *parent) : QPlainTextEdit(parent) {
    skip = false;
    this->setCursorWidth(9);
    this->setStyleSheet("TerminalTextEdit {font-family: MonoSpace; font-size: 18px;}");
    setPrompt("$ ");
    insertPlainText(prompt);
    QObject::connect(this, &TerminalTextEdit::sendCmd, this, &TerminalTextEdit::recvRes);
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
    inp.remove(0, prompt.length());
    // insertPlainText(QString::number(prompt.length()));

    while(downHistory.length() > 0){
        upHistory.push(downHistory.pop());
    }
    // checks if there was an input
    if(inp.length() > 0){
        upHistory.push(inp);
        emit sendCmd(inp);
    }
    insertPlainText("\n");
    clearLine();
    return ;
}

void TerminalTextEdit::handleBackSpace(QKeyEvent *e){
    if(notPrompt()){
        QPlainTextEdit::keyPressEvent(e);
    }
}

void TerminalTextEdit::handleLeft(QKeyEvent *e){
    if(notPrompt()){
        QPlainTextEdit::keyPressEvent(e);
    }
}

void TerminalTextEdit::handleUp(){
    if(upHistory.count() < 1){
        return;
    }
    QString cmd = upHistory.pop();
    downHistory.push(cmd);
    clearLine();
    insertPlainText(cmd);
    skip = true;
}

void TerminalTextEdit::handleDown(){
    if(skip && downHistory.count() > 0){
        upHistory.push(downHistory.pop());
        skip = false;
    }
    if(downHistory.count() > 0){
        QString cmd = downHistory.pop();
        upHistory.push(cmd);
        clearLine();
        insertPlainText(cmd);
    }
    else{
        clearLine();
    }

}
//---------------------------------- helper functions ----------------------------------//

void TerminalTextEdit::recvRes(QString cmd){
    //
    insertPlainText(res + "hehe");
    return;
}

void TerminalTextEdit::clearLine(){
    QTextCursor curs = this->textCursor();
    curs.select(QTextCursor::LineUnderCursor);
    curs.removeSelectedText();
    insertPlainText(getPrompt());
    return;
}

bool TerminalTextEdit::notPrompt(){
    QTextCursor cursor = textCursor();
    QTextBlock block = cursor.block();
    int pos = cursor.position() - block.position();
    if(pos > prompt.length()){
        return true;
    }
    else{
        return false;
    }
}

TerminalTextEdit::~TerminalTextEdit(){

}
