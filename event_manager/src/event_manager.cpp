#include "event_manager.hpp"
#include <iostream>
#include <unistd.h>
#include <cstring>
#include <unordered_set>
#include "logger.hpp"

namespace qfapp {

    #ifdef __APPLE__
    // macOS (kqueue implementation)
    EventManager::EventManager() : isRunning(false) {
        kqueueFd = kqueue();
        if (kqueueFd == -1) {
            perror("kqueue");
            LOG_ERROR("kqueue create failed");
            throw std::runtime_error("Failed to create kqueue instance");
        }
    }

    EventManager::~EventManager() {
        close(kqueueFd);
    }

    void EventManager::addFileDescriptor(FileDescriptor* fd, RW_FLAG rw) {
        struct kevent event;
        //EV_SET(&event, fd->getFd(), EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, fd.get());
        //EV_SET(&event, fd->getFd(), EVFILT_WRITE, EV_ADD | EV_ENABLE, 0, 0, fd.get());
        int flag = (rw == RW_FLAG::FL_READ) ? EVFILT_READ : EVFILT_WRITE;
        EV_SET(&event, fd->getFd(), flag, EV_ADD | EV_ENABLE, 0, 0, fd);

        if (kevent(kqueueFd, &event, 1, nullptr, 0, nullptr) == -1) {
            perror("kevent");
            LOG_ERROR("kevent add fd={} failed", fd->getFd());
            throw std::runtime_error("Failed to add file descriptor to kqueue");
        }

        fdMap[fd->getFd()] = fd;
    }

    void EventManager::makeReadableWritable(int fd) {
        struct kevent event;

        int flag = EVFILT_READ;
        EV_SET(&event, fd, flag, EV_ADD | EV_ENABLE, 0, 0, nullptr);

        if (kevent(kqueueFd, &event, 1, nullptr, 0, nullptr) == -1) {
            perror("kevent");
            LOG_ERROR("kevent add fd={} failed", fd);
            throw std::runtime_error("Failed to add file descriptor to kqueue");
        }

        flag = EVFILT_READ | EVFILT_WRITE;
        EV_SET(&event, fd, flag, EV_ADD | EV_ENABLE, 0, 0,  fdMap[fd]);

        if (kevent(kqueueFd, &event, 1, nullptr, 0, nullptr) == -1) {
            perror("kevent");
            LOG_ERROR("kevent add fd={} failed", fd);
            throw std::runtime_error("Failed to add file descriptor to kqueue");
        }
    }

    void EventManager::removeFileDescriptor(int fd, RW_FLAG rw) {
        struct kevent event;
        //EV_SET(&event, fd, EVFILT_READ, EV_DELETE, 0, 0, nullptr);
        int flag = (rw == RW_FLAG::FL_READ) ? EVFILT_READ : EVFILT_WRITE ;
        EV_SET(&event, fd, flag, EV_DELETE, 0, 0, nullptr);

        if (kevent(kqueueFd, &event, 1, nullptr, 0, nullptr) == -1) {
            perror("kevent");
            throw std::runtime_error("Failed to remove file descriptor from kqueue");
        }

        fdMap.erase(fd);
    }
    #endif
    #ifdef __linux__
    // Linux (epoll implementation)
    EventManager::EventManager() : isRunning(false) {
        epollFd = epoll_create1(0);
        if (epollFd == -1) {
            perror("epoll_create1");
            throw std::runtime_error("Failed to create epoll instance");
        }
    }

    EventManager::~EventManager() {
        close(epollFd);
    }

    void EventManager::makeReadableWritable(int) {}


    void EventManager::addFileDescriptor(FileDescriptor* fd, RW_FLAG) {
        std::cout << "addFileDes " << fd->getFd() << std::endl;
        struct epoll_event event;
        event.data.ptr = fd;
        event.events = EPOLLIN | EPOLLOUT | EPOLLERR | EPOLLET;

        std::cout << "bef added fd=" << " event " << event.data.fd << std::endl; 

        if (epoll_ctl(epollFd, EPOLL_CTL_ADD, fd->getFd(), &event) == -1) {
            perror("epoll_ctl");
            throw std::runtime_error("Failed to add file descriptor to epoll");
        }
        
        std::cout << "added fd=" << fd->getFd() << " event " << event.data.fd << std::endl; 
        fdMap[fd->getFd()] = fd;
    }

    void EventManager::removeFileDescriptor(int fd, RW_FLAG) {
        std::cout << fd << " has been removed" << std::endl;

        if (epoll_ctl(epollFd, EPOLL_CTL_DEL, fd, nullptr) == -1) {
            perror("epoll_ctl");
            throw std::runtime_error("Failed to remove file descriptor from epoll");
        }
        fdMap.erase(fd);
    }
    #endif


    void EventManager::addTimer(std::shared_ptr<Timer> timer) {
        mTimers.push_back(timer);      
    }

    void EventManager::removeTimer(std::shared_ptr<Timer> timer) {
        mTimers.erase(std::remove_if(mTimers.begin(), mTimers.end(),
                             [timer](const std::shared_ptr<Timer>& obj) {
                                 return obj->name() == timer->name();
                             }),
              mTimers.end());
    }

    #ifdef __APPLE__
    void EventManager::run() {
        isRunning = true;

        LOG_INFO("event manager starting ...");

        while (isRunning) {
            processTimers();

            struct kevent events[MAX_EVENTS];
            struct timespec tmout = { 0,             /* block for 0 seconds at most */ 
                                    500000000 };     /* nanoseconds */
            int numEvents = kevent(kqueueFd, nullptr, 0, events, MAX_EVENTS, &tmout);

            if (numEvents == -1) {
                if (errno == EINTR) 
                {
                    LOG_DEBUG("time out!");
                    continue;
                }
                LOG_ERROR("poll_wait failed with errno={}", errno);
                for( const auto& kv : fdMap) {
                    kv.second->onError();
                }
                break;
            }

            if (numEvents > 0)
            {
                for (int i = 0; i < numEvents; ++i) {
                    auto* fd = static_cast<FileDescriptor*>(events[i].udata);
                    //LOG_DEBUG("onEvent {} ident {}", events[i].flags, events[i].ident);
                    if(events[i].filter == EVFILT_WRITE ) {
                        if (!fd->isConnected()) {
                            int ssl_res = fd->onWrite();                                                           
                            if (ssl_res == 1) {
                                LOG_DEBUG("SSL handshake done!");

                                //struct kevent event;
                                // Remove the write event:
                                //EV_SET(&event, fd->getFd(), EVFILT_WRITE, EV_DELETE, 0, 0, fdMap[fd->getFd()].get());
                                //if (kevent(kqueueFd, &event, 1, nullptr, 0, nullptr) == -1) {
                                //    perror("kevent");
                                //    LOG_ERROR("kevent add fd={} failed", fd->getFd());
                                //    throw std::runtime_error("Failed to add file descriptor to kqueue");
                                //}
                                removeFileDescriptor(fd->getFd(), RW_FLAG::FL_WRITE);
                                // Read the event: 
                                //EV_SET(&event, fd->getFd(), EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, fdMap[fd->getFd()].get());
                                //if (kevent(kqueueFd, &event, 1, nullptr, 0, nullptr) == -1) {
                                //    perror("kevent");
                                //    LOG_ERROR("kevent add fd={} failed", fd->getFd());
                                //    throw std::runtime_error("Failed to add file descriptor to kqueue");
                                //}
                                addFileDescriptor(fd, RW_FLAG::FL_READ);
                                fd->onConnected();
                            }
                        } else {
                            int bytesSent = fd->onWrite(); 
                            if (bytesSent == 0) {
                                LOG_INFO("temporary buffer is empty, all data sent, make readable only");
                                removeFileDescriptor(fd->getFd(), RW_FLAG::FL_WRITE);
                                addFileDescriptor(fd, RW_FLAG::FL_READ);
                            }
                        }
                    }
                    if (events[i].filter == EVFILT_READ) {
                        auto recved = fd->onData();
                        if (recved == 0) {
                            fd->onClose();
                            removeFileDescriptor(fd->getFd(), RW_FLAG::FL_READ);
                        } else if (recved < 0) {
                            fd->onError();
                            removeFileDescriptor(fd->getFd(), RW_FLAG::FL_READ);
                        }
                    }
                }
            }
        }            
    }
    #endif

    #ifdef __linux__

    void EventManager::run() {
        isRunning = true;

        std::cout  << "event manager starting ..." << std::endl;

        struct epoll_event events[MAX_EVENTS];

        while (isRunning) {
            processTimers();

            
            int numEvents = epoll_wait(epollFd, events, MAX_EVENTS, POLL_TIMEOUT);
            if (numEvents < 0) {
                perror("Epoll wait failed");
                break;
            }
            
            for (int i = 0; i < numEvents; ++i) {
                std::cout << "handling " << events[i].events << " on fd " <<  events[i].data.fd << std::endl;
                
                auto* handler = static_cast<FileDescriptor*>(events[i].data.ptr);
                std::cout << "handler data from " << handler->getFd() << ", events " << events[i].events << std::endl;

                if (events[i].events & EPOLLERR) {
                    handler->onError();
                } else if (events[i].events & EPOLLIN) {
                    handler->onData();
                } else {
                    //handler->onEvent(events[i].events);
                }
            }
        }
    }
    #endif

    void EventManager::processTimers() {
        auto now = std::chrono::steady_clock::now();
        std::unordered_set<std::shared_ptr<Timer>> to_remove = {};

        LOG_DEBUG("processTimers");

        for (auto& timer : mTimers) {             
            if (timer->elapsed(now)) {
                LOG_DEBUG("timer {} elapsed", timer->name());
                timer->mCallback();
                timer->reset();
                if (timer->elapsed(now)) {
                    to_remove.insert(timer);
                    LOG_DEBUG("remove timer");
                }
            }            
        }
        mTimers.erase(std::remove_if(mTimers.begin(), mTimers.end(), [&](std::shared_ptr<Timer> x) { return to_remove.count(x); }), mTimers.end());
    }

    void EventManager::stop() {
        isRunning = false;
    }

}