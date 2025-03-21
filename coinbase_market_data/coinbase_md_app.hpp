#ifndef COINBASE_MD_APP_HPP 
#define COINBASE_MD_APP_HPP

#include "application.hpp"
#include "coinbase_md_session.hpp"
#include <csignal>

namespace qfapp { namespace coinbase_md {

    using namespace qffixlib;

    class CoinbaseMDApp : public Application {
    public:
        CoinbaseMDApp(AppOptions options, LoggerOptions loggerOptions, const spdlog::pattern_time_type timePattern) : Application(options, loggerOptions, timePattern) {
            mInstance = this;
        }

        static void signalHandler(int signal) {
            LOG_INFO("signal handler: signal {}", signal);
            CoinbaseMDApp::stop();
        }

        static void stop() {
            if (mInstance) {
                mInstance->mSession->stop("force shutdown");
            }   
        }

        void run() override {
            setup();
            start();
            mEventManager->run();
        }
           

        void setup() override {
            mSession = std::make_shared<CoinbaseMdSession<Version::v50sp2>>(mEventManager);
            mSession->sender_comp_id(std::getenv(SENDER_COMP_ID));
            mSession->targetCompId(std::getenv(TARGET_COMP_ID));
            mSession->username(std::getenv(SENDER_COMP_ID));
            mSession->password(std::getenv(SESSION_PASSWORD));
            mSession->secretKey(std::getenv(SESSION_SECRET));
        }
        void start() override {
            mRedisEndpoint = std::make_shared<RedisEndpoint>([this](){
                LOG_INFO("On redis connected");
                mClientConnection->openConnection(std::getenv(SERVER_IP), std::stoi(std::getenv(SERVER_PORT)));
                mEventManager->addFileDescriptor(mClientConnection.get(), RW_FLAG::FL_WRITE);
                },
                [this](){
                    LOG_ERROR("On redis connected");
                    mSession->stop("app forced shut down");
                });

            mSocket = std::make_unique<SSLSocket>();

            mClientConnection = std::make_shared<ClientConnection>(mSession, std::move(mSocket), mEventManager);
            mSession->setWriter(mClientConnection);

          

            mRedisEndpoint->openConnection(std::getenv(REDIS_IP), std::stoi(std::getenv(REDIS_PORT)));
            mEventManager->addFileDescriptor(mRedisEndpoint.get(), RW_FLAG::FL_WRITE);
            mSession->setRedis(mRedisEndpoint);

        }
    private:
        static CoinbaseMDApp* mInstance;
        std::shared_ptr<RedisEndpoint> mRedisEndpoint {nullptr};

        std::unique_ptr<SSLSocket> mSocket {nullptr};
        std::shared_ptr<CoinbaseMdSession<Version::v50sp2>> mSession {nullptr};
        std::shared_ptr<ClientConnection> mClientConnection {nullptr};
    };

    CoinbaseMDApp* CoinbaseMDApp::mInstance {nullptr}; 

}
}

#endif // COINBASE_MD_APP_HPP

