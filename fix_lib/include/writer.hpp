#ifndef WRITTER_HPP
#define WRITTER_HPP

#include <iostream>

namespace qffixlib
{

class Writer
{
public:

    virtual void sendMessage(const char*, std::size_t) = 0;
    
};

}

#endif //WRITTER_HPP