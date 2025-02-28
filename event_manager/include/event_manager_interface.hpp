#ifndef EVENT_MANAGER_INTERFACE_HPP
#define EVENT_MANAGER_INTERFACE_HPP

#include <functional>
#include <chrono>
#include "file_descriptor.hpp"
#include "timer.hpp"

namespace qfapp {

    enum class RW_FLAG {
        FL_READ = 0,
        FL_WRITE = 1
    };

    class EventManagerInterface {
        public:
        virtual ~EventManagerInterface()  = default;
        virtual void addFileDescriptor(FileDescriptor*, RW_FLAG) = 0;
        virtual void removeFileDescriptor(int, RW_FLAG) = 0;
        virtual void addTimer(std::shared_ptr<Timer>) = 0;
        virtual void removeTimer(std::shared_ptr<Timer>) = 0;
    };

}

#endif // EVENT_MANAGER_INTERFACE_HPP