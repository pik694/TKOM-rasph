//
// Created by Piotr Żelazko on 05.06.2018.
//

#ifndef RASPH_WORKERTHREAD_HPP
#define RASPH_WORKERTHREAD_HPP

#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>
#include <utils/NamedType.hpp>

namespace rasph::interpreter::environment {
    class WorkerThread {
    public:
        using Minutes = utils::NamedType<int, struct MinutesStruct>;
        using Seconds = utils::NamedType<int, struct SecondsStruct>;
        using Milliseconds = utils::NamedType<int, struct MillisecondsStruct>;


        WorkerThread(const WorkerThread &) = delete;

        static WorkerThread &getInstance();

        void addJob(std::function<void()> func, Minutes period);

        void addJob(std::function<void()> func, Seconds period);

        void addJob(std::function<void()> func, Milliseconds period);

        void close();

        virtual ~WorkerThread() = default;

    private:
        static WorkerThread *instance_;

        void job(std::shared_ptr<std::function<void()>>, boost::posix_time::milliseconds milliseconds,
                 std::shared_ptr<boost::asio::deadline_timer> timer, const boost::system::error_code &error);

        WorkerThread();

        static void thread(std::shared_ptr<boost::asio::io_context> context);


        std::shared_ptr<boost::asio::io_context> io_context_;
        std::shared_ptr<boost::asio::io_context::work> work_;

        boost::thread_group worker_threads_;
    };


}


#endif //RASPH_WORKERTHREAD_HPP
