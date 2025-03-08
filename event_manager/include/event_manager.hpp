#ifndef EVENT_MANAGER_HPP
#define EVENT_MANAGER_HPP

#include "file_descriptor.hpp"
#include "timer.hpp"
#include "event_manager_interface.hpp"
#include <unordered_map>
#include <vector>
#include <memory>
#include <chrono>

// Platform-specific includes
#ifdef __APPLE__
#include <sys/event.h>
#else
#include <sys/epoll.h>
#endif

namespace qfapp {

    class EventManager : public EventManagerInterface{
    public:
        EventManager();
        virtual ~EventManager();

        void addFileDescriptor(FileDescriptor* fd, RW_FLAG) override;
        void removeFileDescriptor(int fd, RW_FLAG) override;
        void makeReadableWritable(int fd);
        void addTimer(std::shared_ptr<Timer>) override;
        void removeTimer(std::shared_ptr<Timer>) override;
        void run();
        void stop();

    private:
        static constexpr int MAX_EVENTS = 64;
        static constexpr int POLL_TIMEOUT = 500;

    #ifdef __APPLE__
        int kqueueFd;
    #else
        int epollFd;
    #endif

        bool isRunning;
        std::unordered_map<int, FileDescriptor* > fdMap;
        std::vector<std::shared_ptr<Timer>> mTimers;
    public:
        void processTimers();
    };

}

#endif // EVENT_MANAGER_HPP