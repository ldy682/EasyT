#include <pty.h>
#include <iostream>
#include <cstdio>
#include <termios.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <utmp.h>
#include <unistd.h>
#include <cstring>
#include <string>
#include <signal.h>
#include <sys/time.h>
#include <sys/select.h>

using std::cout;
using std::endl;
using std::cerr;
using std::string;

int main(){
    int aMaster, aSlave;
    termios term;
    winsize win;
    pid_t pid;

    if(openpty(&aMaster, &aSlave, nullptr, &term, &win) == -1){
        cerr<<"openpty error"<<endl;
    }

    pid = fork();


    switch (pid)
    {
        case -1:
            std::cerr<<"failed to fork"<<endl;
            return 1;
            break;
        case 0:
            close(aMaster);
            if(login_tty(aSlave) == -1){
                cerr<<"logintty error"<<endl;
                return 1;
            }
            execlp("sh", "/bin/sh", nullptr);
            close(aSlave);
            return 1;
            break;
        default:
            close(aSlave);
            timeval tv;
            fd_set rfds;

            FD_ZERO(&rfds);
            FD_SET(STDOUT_FILENO, &rfds);
            tv.tv_sec = 0;
            tv.tv_usec = 100000;
            bool stop = false;
            
            string input;
            do{
                getline(std::cin, input);
                if(input == "zzz"){
                    stop = true;
                }
                else{
                    write(aMaster, input.c_str(), input.size());
                    write(aMaster, "\n", 1);
                    int retVal = select(aMaster+1, &rfds, nullptr, nullptr, &tv);
                    if(retVal == -1){
                        cerr<<"select error"<<endl;
                    }
                    else if(retVal){
                        cout<<"data available"<<endl;
                    }
                    else{
                        cout<<"no data available"<<endl;
                    }
                }
            }
            while (!stop);
            
            close(aMaster);
            break;
    }
    return 0;
}