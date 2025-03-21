#ifndef REDIS_ENDPOINT_CPP
#define REDIS_ENDPOINT_CPP

#include <hiredis/async.h>
#include <hiredis/hiredis.h>
#include <unordered_map>
#include <functional>
#include "file_descriptor.hpp"
#include "logger.hpp"


using namespace qfapp;

namespace qfapp {

    using RedisCallback = std::function<void()>;

    
    class RedisEndpoint : public FileDescriptor {
        public:

        RedisEndpoint(RedisCallback onConnected, RedisCallback onDisconnected) : OnConnected(onConnected), OnDisconnected(onDisconnected) {}

        void openConnection(const std::string& ip, int port);

        static void onResponse(redisAsyncContext*, void* reply, void*) {
            redisReply* r = static_cast<redisReply*>(reply);
            if (r == nullptr || r->type != REDIS_REPLY_ARRAY || r->elements < 3 || r->element[2]->len == 0) {
                return;
            }
            LOG_INFO("Received message: %s", std::string(r->element[2]->str, r->element[2]->len));
        }

        static void onSubscribe(redisAsyncContext*, void* reply, void*) {
            redisReply* r = static_cast<redisReply*>(reply);
            if (r == nullptr || r->type != REDIS_REPLY_ARRAY || r->elements < 3 || r->element[2]->len == 0) {
                return;
            }
            LOG_INFO("Received message: %s", std::string(r->element[2]->str, r->element[2]->len));
        }

        static void onMessage(redisAsyncContext*, void* reply, void* ) {
            redisReply* r = static_cast<redisReply*>(reply);
            if (r == nullptr || r->type != REDIS_REPLY_ARRAY || r->elements < 3 || r->element[2]->len == 0) {
                return;
            }
            LOG_INFO("Received message: %s", std::string(r->element[2]->str, r->element[2]->len));
        }

        void publishTradeTick(const std::string& data);
        void publishPrice(const char* key, const std::string& data);

        void publish(const std::string& channel, const std::string& data);
        void subscribe(const std::string& channel);

        void get(const char*);
        void set(const char*, const std::string&);

        void hset(const char*, const char*, const std::string&);

        void jsonset(const char*, const std::string&);

        int onData() override ;
        int onWrite() override ;

        void onError() override ;
        void onClose() override ;

        void onConnected() override ;

        RedisCallback OnConnected {nullptr};
        RedisCallback OnDisconnected {nullptr};

        int getFd() const  override { return mFd;}
        bool isInitiator() const  override { return true;}
        bool isConnected() const  override { return mConnected;}

        private:

        redisAsyncContext* mContext{nullptr};
        bool mConnected{false};
        int mFd{0};
    };

}


#endif // REDIS_ENDPOINT_CPP