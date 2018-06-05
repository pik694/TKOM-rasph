//
// Created by Piotr Żelazko on 04.06.2018.
//


#include <interpreter/Interpreter.hpp>
#include <iostream>
#include <interpreter/environment/WorkerThread.hpp>

using namespace rasph::interpreter::environment;

int main(){

    rasph::interpreter::Interpreter(std::cin, std::cout)();
z
//    using namespace std::chrono_literals;
//
//    std::function<void()> func = [](){std::cout << "Hello World"<< std::endl;};
//    WorkerThread::getInstance().addJob(func, WorkerThread::Milliseconds(50));
//
//    std::this_thread::sleep_for(1s);
//
//    WorkerThread::getInstance().close();

}
