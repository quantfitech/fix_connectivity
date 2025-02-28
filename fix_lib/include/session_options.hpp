#ifndef session_options_hpp
#define session_options_hpp

#include "field.hpp"

namespace qffixlib
{

class session_options
{
public: 

    const std::string& begin_string() const noexcept { return m_begin_string; }
    void begin_string(const std::string& begin_string) noexcept { m_begin_string = begin_string; }

    const std::string& sender_comp_id() const noexcept { return m_sender_comp_id; }
    void sender_comp_id(const std::string& sender_comp_id) noexcept { m_sender_comp_id = sender_comp_id; }   

    const std::string& username() const noexcept { return m_username; }
    void username(const std::string& username) noexcept { m_username = username; }    

    const std::string& password() const noexcept { return m_password; }
    void password(const std::string& password) noexcept { m_password = password; }  

     const std::string& secretKey() const noexcept { return m_secretKey; }
    void secretKey(const std::string& secretKey) noexcept { m_secretKey = secretKey; }    


    const std::string& target_comp_id() const noexcept { return m_target_comp_id; }
    void target_comp_id(const std::string& target_comp_id) noexcept { m_target_comp_id = target_comp_id; }

    uint32_t heartbeat_interval() const noexcept { return m_heartbeat_interval; }
    void heartbeat_interval(uint32_t interval) noexcept { m_heartbeat_interval = interval; }

    uint32_t test_request_delay() const noexcept { return m_test_request_delay; }
    void test_request_delay(uint32_t delay) noexcept { m_test_request_delay = delay; }

    qffixlib::timestamp_format timestamp_format() const noexcept { return m_timestamp_format; }
    void timestamp_format(qffixlib::timestamp_format format) noexcept { m_timestamp_format = format; }

    bool use_next_expected_msg_seq_num() const noexcept { return m_use_next_expected_msg_seq_num; }
    void use_next_expected_msg_seq_num(bool value) noexcept { m_use_next_expected_msg_seq_num = value; }

private:

    std::string m_begin_string;
    std::string m_sender_comp_id;
    std::string m_target_comp_id;
    std::string m_username;
    std::string m_password;
    std::string m_secretKey;
    uint32_t m_heartbeat_interval = 30;
    uint32_t m_test_request_delay = 0;
    qffixlib::timestamp_format m_timestamp_format = qffixlib::timestamp_format::microseconds;
    bool m_use_next_expected_msg_seq_num = false;

};

}

#endif