#include "coinbase_md_session.hpp"

#define SERVER_IP "3.114.19.227" // Change to the server's IP address
#define SERVER_PORT 6120         // Change to the server's port number
#define BUFFER_SIZE 8192


using namespace qfapp;
using namespace qffixlib;
using namespace quantfi::coinbase_md;

#include "fix_field.hpp"
#include "fix_message.hpp"


int main() {

    AppOptions app_options;
    app_options.application_name = "coinbase_md";
    LoggerOptions logging_options;
    logging_options.console_log = true;
    logging_options.console_log_level_str ="debug";
    auto app = std::make_unique<Application>(app_options, logging_options); 
    LOG_INFO("starting app");

    auto eventManager = std::make_shared<qfapp::EventManager>();

    //auto session_obs = std::make_shared<CoinbaseMdSession<Version::v50sp2>>(nullptr, eventManager);

	//auto sess = std::make_shared<qffixlib::Session<Version::v50sp2>>(session_obs, eventManager);
    auto sess = std::make_shared<CoinbaseMdSession<Version::v50sp2>>( eventManager);
	sess->beginString("FIXT.1.1");
    sess->sender_comp_id("pv3hnDiPUkJrGS5K");  
    sess->targetCompId("CBINTLMD");
	sess->username(sess->senderCompId());
    sess->password("jhgJHGJHFGHf765jhgffghg");
    sess->secretKey("QzAxdm1lUEZFWWoxSlZlNVNRNFpCOENUQ0pEbGZabkI3NE5yTlhjUUg4SkJsZGltN3pBbFg3SElRSzFlYUt4WQ==");

   // session_obs->session = sess;

    SSLSocket* sock = new SSLSocket();
    
    auto client = std::make_shared<ClientConnection>(sess, sock, eventManager);

    sess->setWriter(client.get());

    client->openConnection(SERVER_IP, SERVER_PORT);

    eventManager->addFileDescriptor(client.get(), RW_FLAG::FL_WRITE);

    eventManager->run();

    return 0;
}

