#include "terminaltextedit.h"
#include <QFont>
#include <QTextCursor>
#include <QTextBlock>
#include <QStringList>
#include <pty.h>
#include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <utmp.h>
#include <sys/select.h>
#include <fcntl.h>
#include <signal.h>
#include <ostream>
#include <iostream>

TerminalTextEdit::TerminalTextEdit(QWidget *parent) : QPlainTextEdit(parent) {
    skip = false;
    this->setCursorWidth(9);
    this->setStyleSheet("TerminalTextEdit {font-family: MonoSpace; font-size: 18px;}");
    setPrompt("φ ");
    insertPlainText(prompt);
    QObject::connect(this, &TerminalTextEdit::sendCmd, this, &TerminalTextEdit::recvRes);
    // QObject::connect(this, &TerminalTextEdit::cursorPositionChanged, this, &TerminalTextEdit::redirectCursor);
    shell = getenv("SHELL");
    if(openpty(&aMaster, &aSlave, nullptr, nullptr, nullptr) == -1){
        throw std::runtime_error("openpty failed");
    }

    pid = fork();
    switch(pid){
    case -1:
        throw std::runtime_error("failed to fork");
        break;
    case 0:
        // uses global close function
        ::close(aMaster);
        if(login_tty(aSlave) == -1){
            throw std::runtime_error("login_tty failed");
        }
        ::close(aSlave);
        execlp(shell, shell, nullptr);
        break;
    default:

        break;
    }
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

// void TerminalTextEdit::mousePressEvent(QMouseEvent *e){
//     switch(e->button()){
//     case Qt::LeftButton:
//         break;
//     default:
//         QPlainTextEdit::mousePressEvent(e);
//         break;
//     }
// }

// void TerminalTextEdit::mouseDoubleClickEvent(QMouseEvent *e){
//     switch(e->button()){
//     case Qt::LeftButton:{
//         break;
//     }
//     default:
//         QPlainTextEdit::mouseDoubleClickEvent(e);
//         break;
//     }
// }

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
        if(inp == "clear"){
            clear();
        }
        else{
            upHistory.push(inp);
            emit sendCmd(inp);
        }
    }
    clearLine();
    return ;
}

void TerminalTextEdit::handleBackSpace(QKeyEvent *e){
    if(notPrompt() && !isCurrentBlock(textCursor().block())){
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
    // insertPlainText(cmd + "hehe");

    int flags = fcntl(aMaster, F_GETFL, 0);
    fcntl(aMaster, F_SETFL, flags | O_NONBLOCK);
    // cmd = "stty -echo; " + cmd;
    QByteArray byteArray = cmd.toUtf8();
    char* input = byteArray.data();

    write(aMaster, input, cmd.size());
    write(aMaster, "\n", 1);
    timeval tv;
    fd_set rfds;

    char c;
    int buffsize = 1024;
    char buffer[buffsize];
    int index = 0;
    QString res;
    do{
        FD_ZERO(&rfds);
        FD_SET(aMaster, &rfds);

        tv.tv_sec = 0;
        tv.tv_usec = 100000;
        select(aMaster+1, &rfds, nullptr, nullptr, &tv);

        if(FD_ISSET(aMaster, &rfds) && index < buffsize - 2){
            read(aMaster, &c, 1);
            buffer[index++] = c;
        }
        // this is the case where text received > buffsize
        else if(FD_ISSET(aMaster, &rfds)){
            buffer[index] = '\0';
            res = res + cleanResult(QString::fromUtf8(buffer));
            index = 0;
        }
    } while(FD_ISSET(aMaster, &rfds));
    buffer[index] = '\0';
    res = res + cleanResult(QString::fromUtf8(buffer));
    insertPlainText(res);
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

bool TerminalTextEdit::isCurrentBlock(QTextBlock block){
    return block != document()->lastBlock();
}

TerminalTextEdit::~TerminalTextEdit(){
    // closing open fds and terminating the slave
    ::close(aMaster);
    ::close(aSlave);
    kill(pid, SIGTERM);
}

QString TerminalTextEdit::cleanResult(QString str){
    QStringList tmp = str.split("\n");
    if(!tmp.isEmpty()){
        tmp.removeFirst();
        tmp.removeLast();
    }
    tmp.prepend("\n");
    return tmp.join("");
}

// void TerminalTextEdit::redirectCursor(){
//     // if(!isCurrentBlock(textCursor().block())){
//     //     // textCursor().setPosition(2);

//     // }
// }
