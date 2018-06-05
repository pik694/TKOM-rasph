//
// Created by Piotr Żelazko on 05.06.2018.
//

#include <iostream>
#include "WorkerThread.hpp"


using namespace rasph::interpreter::environment;


WorkerThread *WorkerThread::instance_ = nullptr;

WorkerThread &WorkerThread::getInstance() {
    if (instance_ == nullptr)
        instance_ = new WorkerThread();

    return *instance_;
}


void WorkerThread::close() {
    io_context_->stop();
    worker_threads_.join_all();
}

WorkerThread::WorkerThread() :
        io_context_(new boost::asio::io_context()) {

    work_ = std::make_shared<boost::asio::io_context::work>(*io_context_);

    for (int i = 0; i < 1; ++i) {
        worker_threads_.create_thread(
                boost::bind(&WorkerThread::thread, io_context_)
        );
    }

}

void WorkerThread::thread(std::shared_ptr<boost::asio::io_context> context) {
  while(true){
      try {
          boost::system::error_code ec;
          context->run(ec);
          break;
      }
      catch (std::exception &e){
          std::cerr << e.what() << std::endl;
      }
  }
}


void WorkerThread::addJob(std::function<void()> func, WorkerThread::Minutes period) {

    addJob(func, WorkerThread::Milliseconds(period.get() * 60 * 1000));
}

void WorkerThread::addJob(std::function<void()> func, WorkerThread::Seconds period) {
    addJob(func, WorkerThread::Milliseconds(period.get() * 1000));;
}

void WorkerThread::addJob(std::function<void()> func, WorkerThread::Milliseconds period) {

    std::shared_ptr<boost::asio::deadline_timer> timer(
            new boost::asio::deadline_timer(*io_context_)
    );

    auto func_ptr = std::make_shared<std::function<void()>>(std::move(func));

    boost::posix_time::milliseconds milliseconds(period.get());

    timer->expires_from_now(milliseconds);
    timer->async_wait(boost::bind(&WorkerThread::job, this, func_ptr, milliseconds, timer, _1));
}


void WorkerThread::job(std::shared_ptr<std::function<void()>> func, boost::posix_time::milliseconds milliseconds,
                       std::shared_ptr<boost::asio::deadline_timer> timer, const boost::system::error_code &error) {

    if (!error) {
        func->operator()();
        timer->expires_from_now(milliseconds);
        timer->async_wait(boost::bind(&WorkerThread::job, this, func, milliseconds, timer, _1));
    }

}
