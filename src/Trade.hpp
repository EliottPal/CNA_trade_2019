/*
** EPITECH PROJECT, 2020
** CNA_trade_2019
** File description:
** Trade
*/

#ifndef TRADE_HPP_
#define TRADE_HPP_

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>

typedef struct settings_s {
    std::string candleFormat;
    int timebank;
    int timePerMove;
    int candleInterval;
    int candlesTotal;
    int candlesGiven;
    int initialStack;
    float transactionFeePercent;
    std::string playerNames;
    std::string yourBot;
} settings_t;

typedef struct candle_s {
    int date;
    float high;
    float low;
    float open;
    float close;
    float volume;
} candle_t;

typedef struct stacks_s {
    float BTC;
    float ETH;
    float USDT;
} stacks_t;

typedef struct averages_s
{
    float twenty_USDT_ETH;
    float fourty_USDT_ETH;
    float twenty_USDT_BTC;
    float fourty_USDT_BTC;
    float twenty_BTC_ETH;
    float fourty_BTC_ETH;
} averages_t;


class Trade {
    public:
        Trade();
        void mainEngine(void);
        void getInput(std::string inputLine);
        void whichCommand(const char *str);
        void settings(void);
        void whichUpdate(void);
        void updateStacks(void);
        void updateCandles(void);
        void actionEngine(void);
        void twenty_USDT_ETH(void);
        void fourty_USDT_ETH(void);
        void twenty_USDT_BTC(void);
        void fourty_USDT_BTC(void);
        void twenty_BTC_ETH(void);
        void fourty_BTC_ETH(void);
        void getAverages(void);
        void buy(int i);
        void sell(int i);
        void wait(void) const;
        ~Trade();
    private:
        std::vector<std::string> _input;
        settings_t _settings;
        stacks_t _stacks;
        averages_t _avgs;
        std::vector <candle_t> _BTC_ETH;
        std::vector <candle_t> _USDT_ETH;
        std::vector <candle_t> _USDT_BTC;
};

#endif /* !TRADE_HPP_ */
