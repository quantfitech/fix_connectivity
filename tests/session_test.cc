#include "gtest/gtest.h"
#include "session.hpp"

using namespace qffixlib;

class MockEventManagerInterface : public EventManagerInterface {
public:
    virtual ~MockEventManagerInterface() {};

    void addFileDescriptor(FileDescriptor*, RW_FLAG) override {}
    void removeFileDescriptor(int, RW_FLAG) override {}
    void addTimer(std::shared_ptr<Timer>) override {}
    void removeTimer(std::shared_ptr<Timer>) override {}
    void stop() override {}
};

class MockWriter : public  Writer {
    void sendMessage(const char*, std::size_t) override {}
};

TEST(session_test, first_msg)
{
    auto ec = std::make_shared<MockEventManagerInterface>(); 
    auto mv = std::make_shared<MockWriter>();
    Session<Version::v50sp2> session(ec);
    session.setWriter(mv);

    std::string logon = "8=FIXT.1.19=18935=A49=pv3hnDiPUkJrGS5K56=CBINTLMD34=152=20250304-14:36:16.72598=0108=30141=Y553=pv3hnDiPUkJrGS5K554=jhgJHGJHFGHf765jhgffghg58=SayZp7U8mieJR6LqIB1oHKzpEvUSoXoAyuM/SLrAkis=1137=910=175";
    TokenIterator ti(logon.data(),logon.length());
    session.onMessageRead(MsgChars{'A','\n'}, 1, false, ti);
    ASSERT_EQ(session.heartbeatInterval(), 30);

}

TEST(session_test, first_msg_and_gap_filled)
{
    auto ec = std::make_shared<MockEventManagerInterface>(); 
    auto mv = std::make_shared<MockWriter>();
    Session<Version::v50sp2> session(ec);
    session.setWriter(mv);

    std::string logon = "8=FIXT.1.19=18935=A49=pv3hnDiPUkJrGS5K56=CBINTLMD34=152=20250304-14:36:16.72598=0108=30141=Y553=pv3hnDiPUkJrGS5K554=jhgJHGJHFGHf765jhgffghg58=SayZp7U8mieJR6LqIB1oHKzpEvUSoXoAyuM/SLrAkis=1137=910=175";
    TokenIterator ti(logon.data(),logon.length());
    session.onMessageRead(MsgChars{'A','\n'}, 1, false, ti);
    ASSERT_EQ(session.heartbeatInterval(), 30);
    ASSERT_EQ(session.incomingMsgSeqNum(), 2);

    std::string aMsg= "8=FIXT.1.19=41435=849=CBINTLOE56=pmRxEAa4bln68mhX34=550=TEST52=20250313-13:26:26.627326369=411=test_oe9880=42308945471917260917=42308945471918899220=037=2wx7c0rh-1-0453=1448=01939cc7-253c-70d0-ba54-b34b418839df452=24150=239=255=BTC-PERP54=138=140=244=8099015=USDC59=6126=20250313-13:27:56.19300000032=131=80990151=014=16=8099060=20250313-13:26:26.627058851=1136=1137=0138=USDC139=48000=Q18=610=094";
    TokenIterator ti8(aMsg.data(),aMsg.length());

    session.onMessageRead(MsgChars{'8','\n'}, 4, false, ti8);
    ASSERT_EQ(session.state(), SessionState::resending);
    ASSERT_EQ(session.incomingMsgSeqNum(), 2);

    session.onMessageRead(MsgChars{'8','\n'}, 2, false, ti8);
    ASSERT_EQ(session.state(), SessionState::resending);

    session.onMessageRead(MsgChars{'8','\n'}, 3, false, ti8);
    ASSERT_EQ(session.state(), SessionState::logged_on);
}
