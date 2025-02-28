#include "fix_protocol.hpp"
#include <iostream>
#include <filesystem>

int main() {
    try {
        std::cout << "Current path is " << std::filesystem::current_path() << std::endl;
        FixProtocol fixProtocol;
        fixProtocol.loadFromFile("../xml/Coinbase/marketdata/FIX50.xml");

        fixProtocol.printFields();
        fixProtocol.printMessages();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
