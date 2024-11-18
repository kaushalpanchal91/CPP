/*
Problem Statement:

  - Your task is to implement an in-memory cache of order objects that supports
    adding new orders, removing existing orders and matching buy and sell orders.
		- An "order" is a request to buy or sell a financial security (eg. bond, stock,
		  commodity, etc.)
		- Each order is uniquely identified by an order id
		- Each security has a different security id
		- Order matching occurs for orders with the same security id, different side (buy or sell),
		  and different company (company of person who requested the order)

  - Provide an implementation for the OrderCacheInterface class in OrderCache.h
    - An Order class is provided for you:
       - This class holds basic order info
       - Do not remove the provided member variables and methods in the Order class
       - You may add additional members if you like
       - For your implementation of OrderCacheInterface:
            - Write a class that derives OrderCacheInterface
            - Choose appropriate data structure(s) to hold Order objects and any additional data you'd like
            - Implement the following methods (do not change their signatures)
                - addOrder()
                - cancelOrder()
                - cancelOrdersForUser()
                - cancelOrdersForSecIdWithMinimumQty()
			    - getMatchingSizeForSecurity()
                - getAllOrders()
            - Add any additional methods and variables you'd like to your class

  - There are more comments in OrderCache.h to provide additional guidance

  - Order matching rules for getMatchingSizeForSecurity()
        - Your implementation of getMatchingSizeForSecurity() should give the total qty that can match for a security id
        - Can only match orders with the same security id
        - Can only match a Buy order with a Sell order
        - Buy order can match against multiple Sell orders (and vice versa)
            - eg a security id "ABCD" has
                Buy  order with qty 10000
                Sell order with qty  2000
                Sell order with qty  1000
            - security id "ABCD" has a total match of 3000. The Buy order's qty is big enough
              to match against both Sell orders and still has 7000 remaining
        - Any order quantity already allocated to a match cannot be reused as a match
          against a differnt order (eg the qty 3000 matched above for security id "ABCD" example)
        - Some orders may not match entirely or at all
        - Users in the same company cannot match against each other


  - Order matching example and explanation
        - Example set of orders added using addOrder()
            OrdId1 SecId1 Buy  1000 User1 CompanyA
            OrdId2 SecId2 Sell 3000 User2 CompanyB
            OrdId3 SecId1 Sell  500 User3 CompanyA
            OrdId4 SecId2 Buy   600 User4 CompanyC
            OrdId5 SecId2 Buy   100 User5 CompanyB
            OrdId6 SecId3 Buy  1000 User6 CompanyD
            OrdId7 SecId2 Buy  2000 User7 CompanyE
            OrdId8 SecId2 Sell 5000 User8 CompanyE
        - Explanation
            - SecId1
                - SecId1 has 1 Buy order and 1 Sell order
                - Both orders are for users in CompanyA so they are not allowed to match
                - There are no matches for SecId1
            - SecId2
                - OrdId2 matches quantity  600 against OrdId4
                - OrdId2 matches quantity 2000 against OrdId7
                - OrdId2 has a total matched quantity of 2600
                - OrdId8 matches quantity 100 against OrdId5 only
                    - OrdId8 has a remaining qty of 4900
                - OrdId4 had its quantity fully allocated to match OrdId2
                    - No remaining qty on OrdId4 for the remaining 4900 of OrdId8
                - Total quantity matched for SecId2 is 2700.  (2600 + 100)
                - Note: there are other combinations of matches among the orders which
                  would lead to the same result of 2700 total qty matching
       - SecId3 has only one Buy order, no other orders to match against


  - More Examples

    - Example 1:

        Orders in cache:
            OrdId1 SecId1 Sell 100 User10 Company2
            OrdId2 SecId3 Sell 200 User8 Company2
            OrdId3 SecId1 Buy 300 User13 Company2
            OrdId4 SecId2 Sell 400 User12 Company2
            OrdId5 SecId3 Sell 500 User7 Company2
            OrdId6 SecId3 Buy 600 User3 Company1
            OrdId7 SecId1 Sell 700 User10 Company2
            OrdId8 SecId1 Sell 800 User2 Company1
            OrdId9 SecId2 Buy 900 User6 Company2
            OrdId10 SecId2 Sell 1000 User5 Company1
            OrdId11 SecId1 Sell 1100 User13 Company2
            OrdId12 SecId2 Buy 1200 User9 Company2
            OrdId13 SecId1 Sell 1300 User1 Company2

        Total qty matching for security ids:
            SecId1 300
            SecId2 1000
            SecId3 600


    - Example 2:

        Orders in cache:
            OrdId1 SecId3 Sell 100 User1 Company1
            OrdId2 SecId3 Sell 200 User3 Company2
            OrdId3 SecId1 Buy 300 User2 Company1
            OrdId4 SecId3 Sell 400 User5 Company2
            OrdId5 SecId2 Sell 500 User2 Company1
            OrdId6 SecId2 Buy 600 User3 Company2
            OrdId7 SecId2 Sell 700 User1 Company1
            OrdId8 SecId1 Sell 800 User2 Company1
            OrdId9 SecId1 Buy 900 User5 Company2
            OrdId10 SecId1 Sell 1000 User1 Company1
            OrdId11 SecId2 Sell 1100 User6 Company2

        Total qty matching for security ids:
			SecId1 900
            SecId2 600
            SecId3 0
*/


#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

class Order{
 public:
  // do not alter signature of this constructor
 Order(): m_orderId("0"), m_securityId("0"), m_side(""), m_qty(0), m_user(""), m_company("") { }  //Added for Error "No matching fn for call to 'Order::order()"
 Order(const std::string& ordId, const std::string& secId, const std::string& side, const unsigned int qty, const std::string& user,
       const std::string& company)
   : m_orderId(ordId), m_securityId(secId), m_side(side), m_qty(qty), m_user(user), m_company(company) { }

  // do not alter these accessor methods
  std::string orderId() const    { return m_orderId; }
  std::string securityId() const { return m_securityId; }
  std::string side() const       { return m_side; }
  std::string user() const       { return m_user; }
  std::string company() const    { return m_company; }
  unsigned int qty() const       { return m_qty; }
  void set_qty(unsigned int qty) { m_qty = qty; }  //Added to update qty in "getMatchingSizeForSecurity()"
  ~Order(){} //Adding destructor

 private:
  // use the below to hold the order data
  // do not remove the these member variables
  std::string m_orderId;     // unique order id
  std::string m_securityId;  // security identifier
  std::string m_side;        // side of the order, eg Buy or Sell
  unsigned int m_qty;        // qty for this order
  std::string m_user;        // user name who owns this order
  std::string m_company;     // company for user

};


// Provide an implementation for the OrderCacheInterface interface class.
// Your implementation class should hold all relevant data structures you think
// are needed.
class OrderCacheInterface{
public:
  // implememnt the 6 methods below, do not alter signatures
  // add order to the cache
  virtual void addOrder(Order order) = 0;
  // remove order with this unique order id from the cache
  virtual void cancelOrder(const std::string& orderId) = 0;
  // remove all orders in the cache for this user
  virtual void cancelOrdersForUser(const std::string& user) = 0;
  // remove all orders in the cache for this security with qty >= minQty
  virtual void cancelOrdersForSecIdWithMinimumQty(const std::string& securityId, unsigned int minQty) = 0;
  // return the total qty that can match for the security id
  virtual unsigned int getMatchingSizeForSecurity(const std::string& securityId) = 0;
  // return all orders in cache in a vector
  virtual std::vector<Order> getAllOrders() const = 0;
};

class OrderCache : public OrderCacheInterface {
private:
    std::unordered_map<std::string, Order> orders; // mapping Order ID to Order object
    std::unordered_map<std::string, std::vector<Order*>> ordersBySecId; // mapping Security ID to list of orders pointers

public:
    OrderCache(std::unordered_map<std::string, Order> ord = {{"",Order()}},
               std::unordered_map<std::string, std::vector<Order*>> ordSecId = {{"",{new Order()}}} )
               : orders(ord),ordersBySecId(ordSecId){}

    // add order to the cache
    void addOrder(Order order) override {
        orders[order.orderId()] = order;
        ordersBySecId[order.securityId()].push_back(&orders[order.orderId()]);
    }

    // remove order with this unique order id from the cache
    void cancelOrder(const std::string& orderId) override {
        auto it = orders.find(orderId);
        if (it != orders.end()) {
            std::cout<<"order with orderId: "<<orderId<<" would be removed..\n";
            auto& secOrders = ordersBySecId[it->second.securityId()];
            secOrders.erase(std::remove(secOrders.begin(), secOrders.end(), &it->second), secOrders.end());
            orders.erase(it);
        }else{
            std::cout<<"No order found with orderId: "<<orderId<<"\n";
        }
    }

    // remove all orders in the cache for this user
    void cancelOrdersForUser(const std::string& user) override {
        int user_found = 0;
        for (auto it = orders.begin(); it != orders.end();) {
            if (it->second.user() == user) {
                auto it0 = it;
                if(it != orders.end()) it++;
                cancelOrder(it0->first);
                user_found = 1;
            } else {
                ++it;
            }
        }
        if(!user_found) std::cout<<"\nNo User found with UserId: "<<user<<"\n";
    }

    // remove all orders in the cache for this security with qty >= minQty
    void cancelOrdersForSecIdWithMinimumQty(const std::string& securityId,unsigned int minQty) override {
        std::vector<Order> all_order = getAllOrders();
        int match_found = 0;
        for(auto x: all_order){
            if(x.securityId() == securityId) {
                match_found = 1;
                break;
            }
        }

        if(match_found){
            auto& secOrders = ordersBySecId[securityId];
            for (auto it = secOrders.begin(); it != secOrders.end(); ) {
                if ((*it)->qty() >= minQty) {
                    cancelOrder((*it)->orderId());
                } else {
                    ++it;
                }
            }
        }else{
            std::cout<<"No order match found with securityId: "<<securityId<<"\n";
        }
    }

    // return the total qty that can match for the security id
    unsigned int getMatchingSizeForSecurity(const std::string& securityId) override {
        int totalMatchedQty = 0;
        auto& secOrders = ordersBySecId[securityId];

        std::vector<Order*> buyOrders;
        std::vector<Order*> sellOrders;

        for (Order* order : secOrders) {
            if (order->side() == "buy") {
                buyOrders.push_back(order);
            } else {
                sellOrders.push_back(order);
            }
        }

        for (Order* buyOrder : buyOrders) {
            unsigned int remainingQty = buyOrder->qty();
            for (Order* sellOrder : sellOrders) {
                if (sellOrder->company() != buyOrder->company() && remainingQty > 0) {
                    int matchQty = std::min(remainingQty, sellOrder->qty());
                    totalMatchedQty += matchQty;
                    remainingQty -= matchQty;
                    unsigned int remainingSellQty = sellOrder->qty();
                    remainingSellQty -= matchQty;
                    sellOrder->set_qty(remainingSellQty);
                }
            }
        }
        return totalMatchedQty;
    }

    // return all orders in cache in a vector
    std::vector<Order> getAllOrders() const override {
        std::vector<Order> allOrders;
        for (const auto& pair : orders) {
            allOrders.push_back(pair.second);
        }
        return allOrders;
    }

    ~OrderCache(){
        for(auto& pairs : ordersBySecId){
            for(Order* vecPtr : pairs.second){
                if(vecPtr != nullptr) {
                    //delete vecPtr;  //In class orders are in stack and destruction is in process
                    vecPtr = nullptr;
                }
            }
        }
    }
};


int main() {
    OrderCache cache;

    Order order1("1", "1", "sell", 100, "1", "Company2");
    Order order2("2", "3", "sell", 200, "1", "Company2");
    Order order3("3", "1", "buy", 300, "2", "Company2");
    Order order4("4", "2", "sell", 400, "2", "Company2");
    Order order5("5", "3", "sell", 500, "2", "Company2");
    Order order6("6", "3", "buy", 600, "2", "Company1");
    Order order7("7", "1", "sell", 700, "2", "Company2");
    Order order8("8", "1", "sell", 800, "1", "Company1");
    Order order9("9", "2", "buy", 900, "2", "Company2");
    Order order10("10", "2", "sell", 1000, "2", "Company1");
    Order order11("11", "1", "sell", 1100, "2", "Company2");
    Order order12("12", "2", "buy", 1200, "2", "Company2");
    Order order13("13", "1", "sell", 1300, "2", "Company2");

    /*Order order1("1", "3", "sell", 100, "1", "Company1");
    Order order2("2", "3", "sell", 200, "1", "Company2");
    Order order3("3", "1", "buy", 300, "1", "Company1");
    Order order4("4", "3", "sell", 400, "1", "Company2");
    Order order5("5", "2", "sell", 500, "1", "Company1");
    Order order6("6", "2", "buy", 600, "1", "Company1");
    Order order7("7", "2", "sell", 700, "1", "Company1");
    Order order8("8", "1", "sell", 800, "1", "Company1");
    Order order9("9", "1", "buy", 900, "1", "Company2");
    Order order10("10", "1", "sell", 1000, "1", "Company1");
    Order order11("11", "2", "sell", 1100, "1", "Company2");*/


   /* Order order1("1", "1", "buy", 1000,"1", "CompanyA");
    Order order2("2", "2", "sell", 3000,"2", "CompanyB");
    Order order3("3", "1", "sell", 500,"3", "CompanyA");
    Order order4("4", "2", "buy", 600,"4", "CompanyC");
    Order order5("5", "2", "buy", 100,"5", "CompanyB");
    Order order6("6", "3", "buy", 1000,"6", "CompanyD");
    Order order7("7", "2", "buy", 2000,"7", "CompanyE");
    Order order8("8", "2", "sell", 5000,"8", "CompanyE"); */

    cache.addOrder(Order("1", "1", "sell", 100, "1", "Company2"));
    cache.addOrder(Order("2", "3", "sell", 200, "1", "Company2"));
   /* cache.addOrder(order3);
    cache.addOrder(order4);
    cache.addOrder(order5);
    cache.addOrder(order6);
    cache.addOrder(order7);
    cache.addOrder(order8);
    cache.addOrder(order9);
    cache.addOrder(order10);
    cache.addOrder(order11);
    cache.addOrder(order12);
    cache.addOrder(order13); */

    std::vector<Order> all_order = cache.getAllOrders();
    all_order = cache.getAllOrders();

    for(auto x: all_order){
        std::cout<<x.orderId()<<" : "<<x.securityId()<<" : "<<x.qty()<<" : "<<x.user()<<" : "<<x.company()<< " \n";
    }

    //cache.cancelOrdersForSecIdWithMinimumQty("2",1000);
    //cache.cancelOrder("13");
    //cache.cancelOrder("12");

    //std::cout << "secId1: " << cache.getMatchingSizeForSecurity("1") << std::endl;
    //std::cout << "secId2: " << cache.getMatchingSizeForSecurity("2") << std::endl;
    //std::cout << "secId3: " << cache.getMatchingSizeForSecurity("3") << std::endl;

    //cache.cancelOrdersForUser("2");

    all_order = cache.getAllOrders();
    for(auto x: all_order){
        std::cout<<x.orderId()<<" : "<<x.securityId()<<" : "<<x.qty()<<" : "<<x.user()<<" : "<<x.company()<< " \n";
    }
    return 0;
}
