#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <chrono>
#include <iomanip>
#include <nlohmann/json.hpp>
#include "logger.hpp"


namespace qffixlib {

#define FEED_NAME "FEED_NAME"

enum class Side { BID, ASK, UNKNOWN };

using json = nlohmann::json;

struct PriceLevel {
    int level {0}; 
    double price {0};
    double volume {0};
    int64_t timestamp;
};

class OrderBook {
public:

    std::string mFeedName = std::getenv(FEED_NAME);

    std::vector<PriceLevel> bids;
    std::vector<PriceLevel> asks;

    void addOrAmendLevel(Side side, int level, double price, double volume, int64_t timestamp) {
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
        book[level - 1] = PriceLevel{level, price, volume, timestamp};
    }

    // Delete a level on a given side.
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

    json orderBookAsJson(const std::string& symbol) {
        json jbids = json::array();
        int64_t tstamp;
        for(const auto& bid : bids) {
           jbids.push_back({
                {"price", bid.price},
                {"size", bid.volume},
            });
            tstamp = std::max(tstamp, bid.timestamp);
        }
        json jasks = json::array();
        for(const auto& ask : asks) {
           jasks.push_back({
            {"price", ask.price},
            {"size", ask.volume},
            });
            tstamp = std::max(tstamp, ask.timestamp);
        }
        json orderBookFeed = {
            {"feed", "COINBASE_INT"},
            {"symbol", symbol},
            {"timestamp", tstamp}, 
            {"asks", jasks},
            {"bids", jbids}
        };
        return orderBookFeed;
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