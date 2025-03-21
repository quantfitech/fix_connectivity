#include "redis_endpoint.hpp"
#include "event_manager.hpp"
#include <memory>
#include <chrono>

using namespace qfapp;
using namespace qffixlib;


int main() {
    
    RedisEndpoint redEp;
    RedisEndpoint redEpPub;

    auto eventManager = std::make_shared<qfapp::EventManager>();
    //redEp.openConnection("127.0.0.1", 6379);
    redEpPub.openConnection("127.0.0.1", 6379);
    eventManager->addTimer(std::make_shared<RecurringTimer>(std::chrono::seconds(5), 
                                                            [&redEpPub](){ redEpPub.publish("channel", "Message published"); },
                                                             "a_timer"));
    //eventManager->addTimer(std::make_shared<Timer>([&redEp](){redEp.subscribe("");}, std::chrono::seconds(1), "a_timer_1"));
    //eventManager->addFileDescriptor(&redEp, RW_FLAG::FL_WRITE);
    eventManager->addFileDescriptor(&redEpPub, RW_FLAG::FL_WRITE);
    eventManager->run();
}