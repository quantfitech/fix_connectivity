#ifndef REDIS_ENDPOINT_CPP
#define REDIS_ENDPOINT_CPP

#include <hiredis/async.h>
#include <hiredis/adapters/poll.h>
#include <hiredis/hiredis.h>
#include <unordered_map>
#include "file_descriptor.hpp"
#include "logger.hpp"


using namespace qfapp;

namespace qffixlib {

    
    class RedisEndpoint : public FileDescriptor {
        public:

        static void connectCallback(const redisAsyncContext *c, int status) {
            if (status != REDIS_OK) {
                LOG_ERROR("Connect error:", c->errstr);
                return;
            }
            
            LOG_INFO("Connected");
        }

        static void disconnectCallback(const redisAsyncContext *c, int status) {
            if (status != REDIS_OK) {
                LOG_ERROR("Error: ", c->errstr);
                return;
            }
            
            LOG_INFO("Disconnected");
        }

        void openConnection(const std::string& ip, int port) {
            redisAsyncContext* context = redisAsyncConnect(ip.data(), port);
            if (context == nullptr || context->err) {
                if (context) {
                    LOG_ERROR("Connection error: {}", context->errstr);
                    redisAsyncFree(context);
                } else {
                    LOG_ERROR("Connection error: can't allocate redis context");
                }
                return;
            }

            mContext = context;
            mFd = context->c.fd;

            redisAsyncSetConnectCallback(mContext,connectCallback);
            redisAsyncSetDisconnectCallback(mContext,disconnectCallback);
        }

        void publish(const std::string& channel, const std::string& data){
            if (REDIS_OK != redisAsyncCommand(mContext, NULL, NULL, "PUBLISH %s %b", channel.c_str(), data.data(), data.length())) {
                LOG_ERROR("Failed to execute command");
            }
            redisAsyncHandleWrite(mContext);
        }

        static void onResponse(redisAsyncContext* context, void* reply, void*) {
            redisReply* r = static_cast<redisReply*>(reply);
            if (r == nullptr || r->type != REDIS_REPLY_ARRAY || r->elements < 3 || r->element[2]->len == 0) {
                return;
            }
            LOG_INFO("Received message: %s", std::string(r->element[2]->str, r->element[2]->len));
        }

        static void onSubscribe(redisAsyncContext* context, void* reply, void* privdata) {
            redisReply* r = static_cast<redisReply*>(reply);
            if (r == nullptr || r->type != REDIS_REPLY_ARRAY || r->elements < 3 || r->element[2]->len == 0) {
                return;
            }
            LOG_INFO("Received message: %s", std::string(r->element[2]->str, r->element[2]->len));
        }

        static void onMessage(redisAsyncContext* context, void* reply, void* privdata) {
            redisReply* r = static_cast<redisReply*>(reply);
            if (r == nullptr || r->type != REDIS_REPLY_ARRAY || r->elements < 3 || r->element[2]->len == 0) {
                return;
            }
            LOG_INFO("Received message: %s", std::string(r->element[2]->str, r->element[2]->len));
        }

        void subscribe(const std::string& channel) {            
            redisAsyncCommand(mContext, RedisEndpoint::onSubscribe, NULL, "SUBSCRIBE %s", channel.c_str());
            redisAsyncHandleWrite(mContext);
        }
        
        void get(const std::string& key) { 
            redisAsyncCommand(mContext, RedisEndpoint::onResponse, NULL, "GET key %b", key.data(), key.length());
            redisAsyncHandleWrite(mContext);
        }

        void set(const std::string& data) {
            redisAsyncCommand(mContext, NULL, NULL, "SET key %b", data.data(), data.length());
            redisAsyncHandleWrite(mContext);
        }

        int onData() override {
            redisAsyncHandleRead(mContext);
            return 1;
        }

        void onError() override { 
            LOG_ERROR("fd error");
        }

        void onClose()  override { 
            mConnected = false; 
        }
        int onWrite()  override {
            redisAsyncHandleWrite(mContext);
            redisContext *c = &(mContext->c);
            if (!mConnected) {
                if (c->flags & REDIS_CONNECTED) {                
                    mConnected = true;
                    return 1;
                }
            }
            return 0;
        }

        void onConnected()  override { 
            LOG_INFO("On connected");
        }

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
