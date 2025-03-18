#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <chrono>
#include <iomanip>
#include "logger.hpp"


namespace qffixlib {
// Enumeration for bid and ask sides.
enum class Side { BID, ASK, UNKNOWN };

//  price level.
struct PriceLevel {
    int level; 
    double price;
    double volume;
    std::string timestamp;
};

class OrderBook {
public:
    // Vectors for bids and asks.
    std::vector<PriceLevel> bids;
    std::vector<PriceLevel> asks;

    void addOrAmendLevel(Side side, int level, double price, double volume, const std::string& timestamp) {
        if (level < 1) {
            LOG_ERROR("revceived invalid price level")
            return; // Level must be at least 1.
        } 
        std::vector<PriceLevel>& book = (side == Side::BID) ? bids : asks;
        if (static_cast<size_t>(level) > book.size()) {
            // Resize the vector; new levels are default-constructed.
            book.resize(level);
        }
        // Update the price level.
        //book.emplace_back(level, price, volume, timestamp); 
        book[level - 1] = PriceLevel{level, price, volume, timestamp};
    }

    // Delete a level on a given side.
    // After deletion, the levels below are renumbered.
    void deleteLevel(Side side, double price) {        
        std::vector<PriceLevel>& book = (side == Side::BID) ? bids : asks;
        
        auto it = std::find_if(book.begin(), book.end(), [price](const PriceLevel& lvl) { return std::abs(lvl.price - price) < 1e-9; });

        if (it != book.end()) {
            book.erase(it);
            // Renumber subsequent levels.
            auto level = std::distance(it, book.begin());
            for (size_t i = level - 1; i < book.size(); i++) {
                book[i].level = i + 1;
            }            
        } else {
            LOG_WARN("remove px {} at side {} failed", price, (side == Side::BID) ? "bid" : "ask");
        }
    }

    // Print the order book.
    void print(const std::string& symbol) const {
        LOG_INFO("Bids: {}", symbol);
        for (const auto& lvl : bids) {
            LOG_INFO("Level {} : Price={}, Volume={}, Timestamp={}", lvl.level, lvl.price, lvl.volume, lvl.timestamp);
        }
         LOG_INFO("Asks:{}", symbol);
        for (const auto& lvl : asks) {
            LOG_INFO("Level {} : Price={}, Volume={}, Timestamp={}", lvl.level, lvl.price, lvl.volume, lvl.timestamp);
        }
    }
};

class OrderBookManager {
public:
    std::map<std::string, OrderBook> books;

    // Retrieve the order book for a given symbol (creates one if not present).
    OrderBook& getBook(const std::string& symbol) {
        return books[symbol];
    }
};

}