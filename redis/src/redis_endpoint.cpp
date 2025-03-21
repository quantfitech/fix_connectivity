#include "redis_endpoint.hpp"

namespace qfapp {

      void RedisEndpoint::openConnection(const std::string& ip, int port) {
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
    }

    void RedisEndpoint::publish(const std::string& channel, const std::string& data){
        if (REDIS_OK != redisAsyncCommand(mContext, NULL, NULL, "PUBLISH %s %b", channel.c_str(), data.data(), data.length())) {
            LOG_ERROR("Failed to execute command");
        }
        redisAsyncHandleWrite(mContext);
    }

    void RedisEndpoint::publishTradeTick(const std::string& data){
        if (REDIS_OK != redisAsyncCommand(mContext, NULL, NULL, "PUBLISH TRADING:COINBASE:TRADETICK %b", data.data(), data.length())) {
            LOG_ERROR("Failed to execute command");
        }
        redisAsyncHandleWrite(mContext);
    }

    void RedisEndpoint::publishPrice(const char* key, const std::string& data) {
        if (REDIS_OK != redisAsyncCommand(mContext, NULL, NULL, "SET TRADING:COINBASE:PRICES:%s %b", key, data.data(), data.length())) {
            LOG_ERROR("Failed to execute command");
        }
        redisAsyncHandleWrite(mContext);
    }

     void RedisEndpoint::subscribe(const std::string& channel) {            
        redisAsyncCommand(mContext, RedisEndpoint::onSubscribe, NULL, "SUBSCRIBE %s", channel.c_str());
        redisAsyncHandleWrite(mContext);
    }
    
    void RedisEndpoint::get(const char* key) { 
        redisAsyncCommand(mContext, RedisEndpoint::onResponse, NULL, "GET %s", key);
        redisAsyncHandleWrite(mContext);
    }

    void RedisEndpoint::set(const char* key, const std::string& data) {
        if (REDIS_OK !=redisAsyncCommand(mContext, NULL, NULL, "SET %s %b", key, data.data(), data.length())) {
                LOG_ERROR("Failed to set key {}", key);
        }
        redisAsyncHandleWrite(mContext);
    }

     void RedisEndpoint::hset(const char* key, const char* field, const std::string& data) {
        if (REDIS_OK !=redisAsyncCommand(mContext, NULL, NULL, "HSET %s %s %b", key, field, data.data(), data.length())) {
                LOG_ERROR("Failed to set key {}", key);
        }
        redisAsyncHandleWrite(mContext);
    }

    void RedisEndpoint::jsonset(const char* key, const std::string& data) {
        if (REDIS_OK !=redisAsyncCommand(mContext, NULL, NULL, "JSON.SET TRADING:COINBASE:PRICE:%s %b", key, data.data(), data.length())) {
                LOG_ERROR("Failed to set key {}", key);
        }
        redisAsyncHandleWrite(mContext);
    }

    int RedisEndpoint::onData() {
        redisAsyncHandleRead(mContext);
        return 1;
    }

    void RedisEndpoint::onError() { 
        LOG_ERROR("fd error");
    }

    void RedisEndpoint::onClose() { 
        mConnected = false; 
        if (OnDisconnected) {
            OnDisconnected();
        }
    }
    int RedisEndpoint::onWrite() {
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

    void RedisEndpoint::onConnected() { 
        LOG_INFO("On connected");
        if (OnConnected) {
            OnConnected();
        }
    }


}