#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
#include <thread>


bool quit = false;

using namespace std;

string exec(const char* cmd) {
    array<char, 128> buffer;
    string result;
    unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

void controlLoopThread() {

    while(!quit) {
        
        
    }

}

void terminalReadThread() {

    while(!quit) {
        char message = getchar();

        switch(message) {
            case
        }
    }
}

int main() {
    return 0;
}