#include <iostream> //standard cout & cin
#include <map> //mapping function
#include <string> //standard library addon
#include <vector> //growable array
#include <limits> //for std::numeric_limits

bool loop = true; //kill while
typedef void (*MenuFunction)(); //Define pointer for menu actions

enum class OrderBookType
{
    bid,
    ask
};

class OrderBookEntry
{
    public:
        OrderBookEntry(double _price,
                       double _amount,
                       std::string _timestamp,
                       std::string _product,
                       OrderBookType _orderType)
        : price(_price), amount(_amount), timestamp(_timestamp), product(_product), orderType(_orderType)
        {
            
        }

        double price;
        double amount;
        std::string timestamp;
        std::string product;
        OrderBookType orderType;

};

void printHelp()
{
    std::cout << "Help - your aim si to make money. Analyse the market and make bids and offers" << std::endl;
}

void printMarketStats()
{
    std::cout << "Market looks good" << std::endl;
}

void enterOffer()
{
    std::cout << "Make an offer - enter the amount" << std::endl;
}

void enterBid()
{
    std::cout << "Make a bid - enter the amount" << std::endl;
}

void printWallet()
{
    std::cout << "Your wallet is empty" << std::endl;
}

void gotoNextTimeframe()
{
    std::cout << "Going to next timeframe" << std::endl;
}

void exitProgram()
{
    std::cout << "Exiting the program" << std::endl;
    loop = false;
}

//Create a map to store menu options functions
std::map<int, MenuFunction> menuOptions = {
    {1, printHelp},
    {2, printMarketStats},
    {3, enterOffer},
    {4, enterBid},
    {5, printWallet},
    {6, gotoNextTimeframe},
    {7, exitProgram}
};

void printMenu()
{
    // space line
    std::cout << "" << std::endl;
    // 1 print help
    std::cout << "1: Print help " << std::endl;
    // 2 print exchange stats
    std::cout << "2: Print exchange stats " << std::endl;
    // 3 make an offer
    std::cout << "3: Make an offer " << std::endl;
    // 4 make a bid
    std::cout << "4: Make a bid " << std::endl;
    // 5 print wallet
    std::cout << "5: Print wallet " << std::endl;
    // 6 continue
    std::cout << "6: Continue " << std::endl;
    // 7 exit
    std::cout << "7: Exit " << std::endl;

    std::cout << "============" << std::endl;
}

int getUserOption()
{
    int userOption;
    std::cout << "Type in 1-7" << std::endl;
    std::cin >> userOption;
    std::cout << "You chose: " << userOption << std::endl;
    return userOption;
}

double computeAveragePrice(std::vector<OrderBookEntry>& orders)
{
    double sum = 0.0;
    for (const OrderBookEntry& order : orders)
    {
        sum += order.price;
    }
    if (orders.size() > 0)
    {
        return sum / orders.size();
    }
    return 0.0; // Return 0 if the vector is empty to avoid division by zero.
}

double computeLowPrice(std::vector<OrderBookEntry>& orders)
{
    double minPrice = std::numeric_limits<double>::max();
    for(const OrderBookEntry& order : orders)
    {
        if(order.price < minPrice)
        {
            minPrice = order.price;
        }
    }
    return minPrice;
}

double computeHighPrice(std::vector<OrderBookEntry> &orders)
{
    double highPrice = std::numeric_limits<double>::min();
    for(const OrderBookEntry& order : orders)
    {
        if(order.price > highPrice)
        {
            highPrice = order.price;
        }
    }
    return highPrice;
}

double computePriceSpread(std::vector<OrderBookEntry> &orders)
{
    double lowestAskPrice = std::numeric_limits<double>::max();
    double highBidPrice = std::numeric_limits<double>::min();

    for (const OrderBookEntry& order : orders)
    {
        if (order.price < lowestAskPrice && order.orderType == OrderBookType::ask)
        {
            lowestAskPrice = order.price;
        }
    }
    return lowestAskPrice;

    for (const OrderBookEntry &order : orders)
    {
        if (order.price > highBidPrice && order.orderType == OrderBookType::bid)
        {
            highBidPrice = order.price;
        }
    }
    return highBidPrice;

    double spread = lowestAskPrice - highBidPrice;
    return spread;
}

int main()
{

    std::vector<OrderBookEntry> orders;

    orders.push_back(OrderBookEntry{7000, 0.002, "2020/03/17 17:01:24.884492", "BTC/USDT", OrderBookType::bid});
    orders.push_back(OrderBookEntry{12000, 0.004, "2020/03/17 17:02:24.884492", "BTC/USDT", OrderBookType::ask});
    orders.push_back(OrderBookEntry{15000, 0.006, "2020/03/17 17:03:24.884492", "BTC/USDT", OrderBookType::ask});
    orders.push_back(OrderBookEntry{17000, 0.008, "2020/03/17 17:04:24.884492", "BTC/USDT", OrderBookType::bid});

    std::cout << "Average Price: " << computeAveragePrice(orders) << std::endl;
    std::cout << "Low price: " << computeLowPrice(orders) << std::endl;
    std::cout << "High price: " << computeHighPrice(orders) << std::endl;
    std::cout << "Spread: " << computePriceSpread(orders) << std::endl;

    return 0;
}

/*
    while (loop == true)
    {
        printMenu();
        int userOption = getUserOption();
        //processUserOption(userOption);
        auto it = menuOptions.find(userOption);
        if (it != menuOptions.end()) {
            MenuFunction function = it->second;
            function(); // call the function pointer 
        } else {
            std::cout << "Invalid choice. Choose 1-7" << std::endl;
        }
    }
*/


/*
    for (OrderBookEntry& order : orders) //& don't make a data copy to iterate the vector
    {
        std::cout << "Vector The price is " << order.price << std::endl;
    }

    for (unsigned int i = 0; i < orders.size(); ++i) //++i more efficent, less operation, increment directly in place
    {
        std::cout << "Like array The price is " << orders[i].price << std::endl;
    }

    for (unsigned int i = 0; i < orders.size(); ++i) //object
    {
        std::cout << "Like object The price is " << orders.at(i).price << std::endl;
    }
*/


//OrderBookEntry order1{10000, 0.002, "2020/03/17 17:01:24.884492", "BTC/USDT", OrderBookType::bid};
//double price = 5319.450228; //double type looses less precision while operating with number in the order book and not taking crazy amount of memory
//double amount = 0.00020075;
//std::string timestamp{"2020/03/17 17:01:24.884492"};
//std::string product{"ETH/BTC"};
//std::string orderType{"bid"};
//enum class OrderBookType{bid, ask}; //constrain th epossible amount of value
//OrderBookType orderType = OrderBookType::bid;
//std::vector<double> prices;
//std::vector<double> amounts;
//std::vector<std::string> timestamps;
//std::vector<std::string> products;
//std::vector<std::string> orderTypes;
//prices.push_back(5000.01);
//amounts.push_back(0.001);
//timestamps.push_back("2020/03/17 17:01:24.884492");
//products.push_back("BTC/USDT");
//orderTypes.push_back(OrderBookType::bid);