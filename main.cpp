#include <pty.h>
#include <iostream>
#include <cstdio>
#include <termios.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <utmp.h>


using std::cout;
using std::endl;

int main(){
    int aMaster, aSlave;
    termios term;
    winsize win;
    pid_t pid;

    if(openpty(&aMaster, &aSlave, nullptr, &term, &win) == -1){
        std::cerr<<"openpty error"<<endl;
    }


    pid = fork();

    switch (pid)
    {
        case -1:
            std::cerr<<"failed to fork"<<endl;
            break;
        case 0:
            close(aMaster);
            // cout<<"in child process"<<getpid()<<endl;
            if(login_tty(aSlave) == -1){
                std::cerr<<"logintty error"<<endl;
            }
            execlp("/bin/sh", "/bin/sh", nullptr);
            close(aSlave);
            break;
        default:
            close(aSlave);
            // Example of writing to the master side (input to the child)
            write(aMaster, "ls\n", 3);

            // Example of reading from the master side (output from the child)
            char buffer[256];
            int bytesRead;
            while ((bytesRead = read(aMaster, buffer, sizeof(buffer))) > 0) {
                write(STDOUT_FILENO, buffer, bytesRead);
            }
            // cout<<"parent process"<<getpid()<<endl;
            close(aMaster);
            break;
    }
    

}