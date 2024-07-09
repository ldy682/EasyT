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
#include <fcntl.h>

using std::cout;
using std::endl;
using std::cerr;
using std::string;


int main(){
    int aMaster, aSlave;
    termios term;
    winsize win;
    pid_t pid;

    if(openpty(&aMaster, &aSlave, nullptr, nullptr, nullptr) == -1){
        cerr<<"openpty error"<<endl;
        return -1;
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
            // dup2(aSlave, 0);
            // dup2(aSlave, 1);
            // dup2(aSlave, 2);
            close(aSlave);
            execlp("/bin/sh", "/bin/sh", NULL);
            return 1;
            break;
        default:
            close(aSlave);
            
            string input;
            char c, co;
            bool stop = false;

            int flags = fcntl(aMaster, F_GETFL, 0);
            fcntl(aMaster, F_SETFL, flags | O_NONBLOCK);
            cout<<"% "<<std::flush;

            do{
                // write(STDOUT_FILENO, "% ", 2);
                // std::cout << "% " << std::flush;
                std::getline(std::cin, input);
                
                bool data = true;
                if(input == "zzz"){
                    stop = true;
                }
                else if(!stop){
                    write(aMaster, input.c_str(), input.size());
                    write(aMaster, "\n", 1);
                    timeval tv;
                    fd_set rfds;
                    do{
                        FD_ZERO(&rfds);
                        FD_SET(aMaster, &rfds);

                        tv.tv_sec = 1;
                        tv.tv_usec = 100000;
                        select(aMaster+1, &rfds, NULL, NULL, &tv);

                        if(FD_ISSET(aMaster, &rfds)){
                            read(aMaster, &c, 1);
                            cout<<c<<std::flush;
                        }
                    } while(FD_ISSET(aMaster, &rfds));
                }
            } while (!stop);
            kill(pid, SIGTERM);
            close(aMaster);
            break;
    }
    return 0;
}

