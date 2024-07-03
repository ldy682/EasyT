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
            break;
        case 0:
            close(aMaster);
            if(login_tty(aSlave) == -1){
                cerr<<"logintty error"<<endl;
                return 1;
            }
            execlp("/bin/sh", "/bin/sh", "-i", nullptr);
            close(aSlave);
            return 1;
            break;
        default:
            close(aSlave);
  
            std::string command;
            std::cout << "Enter a command (e.g., ls -l): ";
            std::getline(std::cin, command);

            // Send the command to the shell
            command += '\n'; // Add newline to simulate enter keypress
            write(aMaster, command.c_str(), command.size());
            
            // Read and print output from the shell
            char buffer[1024];
            ssize_t bytesRead;
            bool shellExited = false;
            
            while ( (bytesRead = read(aMaster, buffer, sizeof(buffer))) > 0) {
                std::cout.write(buffer, bytesRead)<<std::flush;
                // if (strstr(buffer, "$ ") != nullptr) {
                //     shellExited = true;
                // }
            }
            
            close(aMaster);
            return 0;
            break;
    }
    return 0;
}