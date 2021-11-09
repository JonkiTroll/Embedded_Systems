#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
#include <fstream>
#include <thread>
#include <mutex>
#include <chrono>

#include "../include/modbus.h"

using namespace std;

constexpr int16_t ref_speed = 800;

bool quit = false;
mutex busMutex;

modbus bus;

void forward();
void backward();
void left();
void right();

typedef struct direction {
    bool forwards;
    bool backwards;
    bool left;
    bool right;
};




void ir_monitoring() {

    int fd = open("/sys/class/gpio/export", O_WRONLY);
    write(fd, "22", 2);
    write(fd, "23", 2);
    close(fd);

    fd = open("/sys/class/gpio/gpio22/direction", O_WRONLY);
    write(fd, "in", 2);
    close(fd);

    fd = open("/sys/class/gpio/gpio23/direction", O_WRONLY);
    write(fd, "in", 2);
    close(fd);

    
    uint8_t pin22_val, pin23_val;
    direction dir = {
        false,
        false,
        false,
        false,
    };

    while(!quit) {
        int pin22fd = open("/sys/class/gpio/gpio22/value", O_RDONLY);
        int pin23fd = open("/sys/class/gpio/gpio23/value", O_RDONLY);

        read(pin22fd, &pin22_val, 1);
        read(pin23fd, &pin23_val, 1);

        close(pin22fd);
        close(pin23fd);

        if(!dir.forwards && !pin22_val && !pin23_val) {
            forward();
            dir.forwards = true;
            dir.backwards = false;
            dir.left = false;
            dir.right = false;
        } else if(!dir.left && pin22_val && !pin23_val) {
            left();
            dir.forwards = false;
            dir.backwards = false;
            dir.left = true;
            dir.right = false;
        } else if(!dir.right && !pin22_val && pin23_val) {
            right();
            dir.forwards = false;
            dir.backwards = false;
            dir.left = false;
            dir.right = true;
        } else if (!dir.backwards && pin22_val && pin23_val){
            backward();
            dir.forwards = false;
            dir.backwards = true;
            dir.left = false;
            dir.right = false;
        }
        
        usleep(150'000);

    }


}

void log_speed(char* filename) {
    ofstream file;
    int16_t val_left = 0;
    int16_t val_right = 0;

    file.open(filename);

    auto start_time = chrono::high_resolution_clock::now();
    while(!quit){

        busMutex.lock();
       // val_left = bus.receive(1, 1);
        val_right = bus.receive(1, 1);
        busMutex.unlock();
        auto current_time = chrono::high_resolution_clock::now();

        file << std::chrono::duration_cast<std::chrono::milliseconds>(current_time - start_time).count()
             << ", " << to_string(val_left) << "," << to_string(val_right) << endl;

    }
    file.close();
}

void readTerminal(){
    char message;
    while(!quit) {
        cin >> message;
        
        switch (message){
            case 'g':
                busMutex.lock();
                bus.send(1,0,1);
                bus.send(2,0,1);
                busMutex.unlock();
                break;
            case 's':
                busMutex.lock();
                bus.send(1,0,2);
                bus.send(2,0,2);
                busMutex.unlock();
                break;
            case 'c':
                busMutex.lock();
                bus.send(1,0,82);
                bus.send(2,0,82);
                busMutex.unlock();
                break;
            case 'p': 
                busMutex.lock();
                bus.send(1,0,80);
                bus.send(2,0,80);
                busMutex.unlock();
                break;
            case 'r': 
                busMutex.lock();
                bus.send(1,0,81);
                bus.send(2,0,81);
                busMutex.unlock();
                break;
            case 'q': 
                quit = true;
                break;
            default:
                break;

        }
    }
}

int main(int argc, char** argv) {

    if(argc != 2) {
        cout << "ERROR, invalid number of arguements\n";
        return 0;
    }
    
    bus.send(1, 0, 80);
    bus.send(2, 0, 80);

    bus.send(1, 1, 800);
    bus.send(2, 1, 800);
    
    //thread controlLoop(ir_monitoring);
    thread LogThread(log_speed, argv[1]);
    thread TerminalThread(readTerminal);
    
    

    TerminalThread.join();
    //controlLoop.join();
    LogThread.join();


    bus.send(1, 0, 80);
    bus.send(2, 0, 80);
    return 0;

}

void forward() {

    bus.send(1, 1, ref_speed);
    bus.send(2, 1, ref_speed);

}

void backward() {

    bus.send(1, 1, -ref_speed);
    bus.send(2, 1, -ref_speed);
}

void left() {

    bus.send(1, 1, ref_speed);
    bus.send(2, 1, ref_speed*0.5);
}

void right() {

    bus.send(1, 1, ref_speed*0.5);
    bus.send(2, 1, ref_speed);
}