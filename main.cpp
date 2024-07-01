#include <pty.h>
#include <iostream>
#include <cstdio>
#include <termios.h>
#include <sys/ioctl.h>
#include <unistd.h>


using std::cout;
using std::endl;

int main(){
    int aMaster, aSlave;
    termios term;
    winsize win;
    pid_t pid;
    pid = fork();

    switch (pid)
    {
    case 0:
        cout<<"in child process"<<getpid()<<endl;;
        break;
    default:
        cout<<"parent process"<<getpid()<<endl;
        break;
    }
    // openpty(&aMaster, &aSlave, nullptr, &term, &win);

}