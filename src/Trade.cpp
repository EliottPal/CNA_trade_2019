/*
** EPITECH PROJECT, 2020
** CNA_trade_2019
** File description:
** Trade
*/

#include "Trade.hpp"


Trade::Trade()
{
}

// Bot engine -> getline puis on call la bonne command
void Trade::mainEngine(void)
{
    std::string inputLine;

    while(std::getline(std::cin, inputLine)) {
        if (inputLine.size() > 0)
            getInput(inputLine);
        whichCommand(this->_input.front().c_str());
        this->_input.clear();
    }
}

// On recup l'input de getline qu'on met dans this->_input
void Trade::getInput(std::string inputLine)
{
    char *input_str = const_cast<char *> (inputLine.c_str());
    char *input_token = std::strtok(input_str, " ");

    for (; input_token; input_token = std::strtok(NULL, " "))
        this->_input.push_back(input_token);
}

// Call la bonne fonction selon la commande entrée (Settings / Update / Action)
void Trade::whichCommand(const char *str)
{
    if (std::strcmp(str, "settings") == 0)
        this->settings();
    if (std::strcmp(str, "update") == 0)
        this->whichUpdate();
    if (std::strcmp(str, "action") == 0)
        this->actionEngine();
}

// Get setting a update et on le change
void Trade::settings()
{
    const char *toChange = this->_input[1].c_str();

    if (strcmp(toChange, "candle_format"))
        this->_settings.candleFormat = this->_input.back();
    if (strcmp(toChange, "timebank"))
        this->_settings.timebank = atoi(this->_input.back().c_str());
    if (strcmp(toChange, "time_per_move"))
        this->_settings.timePerMove = atoi(this->_input.back().c_str());
    if (strcmp(toChange, "candle_interval"))
        this->_settings.candleInterval = atoi(this->_input.back().c_str());
    if (strcmp(toChange, "candles_total"))
        this->_settings.candlesTotal = atoi(this->_input.back().c_str());
    if (strcmp(toChange, "candles_given"))
        this->_settings.candlesGiven = atoi(this->_input.back().c_str());
    if (strcmp(toChange, "initial_stack"))
        this->_settings.initialStack = atoi(this->_input.back().c_str());
    if (strcmp(toChange, "transaction_fee_percent"))
        this->_settings.transactionFeePercent = atof(this->_input.back().c_str());
    if (strcmp(toChange, "player_names"))
        this->_settings.playerNames = this->_input.back();
    if (strcmp(toChange, "your_bot"))
        this->_settings.yourBot = this->_input.back();
}

// Call la bonne fonction d'update (Candles / Stacks)
void Trade::whichUpdate()
{
    if (std::strcmp(this->_input[2].c_str(), "next_candles") == 0)
        this->updateCandles();
    if (std::strcmp(this->_input[2].c_str(), "stacks") == 0)
        this->updateStacks();
}

// Update les stacks
// On reçoit une line comme ça->
//      update game stacks BTC:0.00000000,ETH:0.00000000,USDT:1000.00
// On parse la line en splittant avec " ,:" et on stocke tout dans le vector stacks
// Dans le vector on a donc ->
//      BTC 0.00000000 ETH 0.00000000 USDT 1000.00
// Puis on récupere les values pour update la structure this->_stacks
void Trade::updateStacks()
{
    char *input_str = const_cast<char *> (this->_input[3].c_str());
    char *token = std::strtok(input_str, " ,:");
    std::vector<std::string> stacks;

    for (; token; token = std::strtok(NULL, " ,:"))
        stacks.push_back(token);

    this->_stacks.BTC = atof(stacks[1].c_str());
    this->_stacks.ETH = atof(stacks[3].c_str());
    this->_stacks.USDT = atof(stacks[5].c_str());
}

// Update les candles
// On reçoit une line comme ça->
//      update game next_candles BTC_ETH,1516694400,1.3388420345209027,1.3388420345209027,1.301039320124042,1.2996928219761725,67.5554485;USDT_ETH,1516694400,83.81087818493644,79.62033427568961,81.92474276832498,81.50735022556468,207934.45713782;USDT_BTC,1516694400,62.599527071860805,59.46955071826776,60.888457843958335,61.039750194264776,648776.89698492
// On parse la line en splittant avec " ;" ->
//      BTC_ETH,1516764600,0.7348257435134913,0.7348257435134913,0.7191062097748714,0.7199022082225971,45.94557742
//      USDT_ETH,1516755600,67.51972825204392,64.14374183944172,65.77846884750711,65.57359505353797,159234.51597948
//      USDT_BTC,1516755600,91.18991801532289,86.63042211455674,89.3461388017511,88.66284684669391,899934.3787562
// On reparse avec "," et on stocke les bonne values dans une nouvelle candle
// Puis on push back la candle dans le vector correspondant
void Trade::updateCandles()
{
    char *input_str = const_cast<char *> (this->_input[3].c_str());
    char *token = std::strtok(input_str, " ;");
    char *token_bis = NULL;
    std::vector<std::string> parsed;
    std::vector<std::string> tmp;
    candle_t toAdd;

    for (; token; token = std::strtok(NULL, " ;"))
        parsed.push_back(token);

    // Fill BTC_ETH vector
    token_bis = std::strtok(const_cast<char *> (parsed[0].c_str()), ",");
    for (; token_bis; token_bis = std::strtok(NULL, ","))
        tmp.push_back(token_bis);
    toAdd.date = atoi(tmp[1].c_str());
    toAdd.high = atof(tmp[2].c_str());
    toAdd.low = atof(tmp[3].c_str());
    toAdd.open = atof(tmp[4].c_str());
    toAdd.close = atof(tmp[5].c_str());
    toAdd.volume = atof(tmp[6].c_str());
    this->_BTC_ETH.push_back(toAdd);

    // Fill USDT_ETH vector
    token_bis = std::strtok(const_cast<char *> (parsed[1].c_str()), ",");
    tmp.clear();
    for (; token_bis; token_bis = std::strtok(NULL, ","))
        tmp.push_back(token_bis);
    toAdd.date = atoi(tmp[1].c_str());
    toAdd.high = atof(tmp[2].c_str());
    toAdd.low = atof(tmp[3].c_str());
    toAdd.open = atof(tmp[4].c_str());
    toAdd.close = atof(tmp[5].c_str());
    toAdd.volume = atof(tmp[6].c_str());
    this->_USDT_ETH.push_back(toAdd);

    // Fill USDT_BTC vector
    token_bis = std::strtok(const_cast<char *> (parsed[2].c_str()), ",");
    tmp.clear();
    for (; token_bis; token_bis = std::strtok(NULL, ","))
        tmp.push_back(token_bis);
    toAdd.date = atoi(tmp[1].c_str());
    toAdd.high = atof(tmp[2].c_str());
    toAdd.low = atof(tmp[3].c_str());
    toAdd.open = atof(tmp[4].c_str());
    toAdd.close = atof(tmp[5].c_str());
    toAdd.volume = atof(tmp[6].c_str());
    this->_USDT_BTC.push_back(toAdd);
}

// Les 6 fonctions suivantes servent a récupérer les moyennes mobiles du cours des cryptos
// twenty... -> moyenne sur les 20 derniers jours
// fourty.. -> moyenne sur les 40 derniers jours
// On stocke ensuite tout ça dans la struct averages (this->_avgs) pour pouvoir les comparer

//// USDT_ETH ////
void Trade::twenty_USDT_ETH(void)
{
    float USDT_ETH = 0;

    for (std::size_t i = this->_USDT_ETH.size() - 20; i != this->_USDT_ETH.size() ; i++)
        USDT_ETH += this->_USDT_ETH[i].close;
    this->_avgs.twenty_USDT_ETH = USDT_ETH / 20;
}

void Trade::fourty_USDT_ETH(void)
{
    float USDT_ETH = 0;

    for (std::size_t i = this->_USDT_ETH.size() - 40; i != this->_USDT_ETH.size() ; i++)
        USDT_ETH += this->_USDT_ETH[i].close;
    this->_avgs.fourty_USDT_ETH = USDT_ETH / 40;
}

//// USDT_BTC ////
void Trade::twenty_USDT_BTC(void)
{
    float USDT_BTC = 0;

    for (std::size_t i = this->_USDT_BTC.size() - 20; i != this->_USDT_BTC.size() ; i++)
        USDT_BTC += this->_USDT_BTC[i].close;
    this->_avgs.twenty_USDT_BTC = USDT_BTC / 20;
}

void Trade::fourty_USDT_BTC(void)
{
    float USDT_BTC = 0;

    for (std::size_t i = this->_USDT_BTC.size() - 40; i != this->_USDT_BTC.size() ; i++)
        USDT_BTC += this->_USDT_BTC[i].close;
    this->_avgs.fourty_USDT_BTC = USDT_BTC / 40;
}

//// BTC_ETH ////
void Trade::twenty_BTC_ETH(void)
{
    float BTC_ETH = 0;

    for (std::size_t i = this->_BTC_ETH.size() - 20; i != this->_BTC_ETH.size() ; i++)
        BTC_ETH += this->_BTC_ETH[i].close;
    this->_avgs.twenty_BTC_ETH = BTC_ETH / 20;
}

void Trade::fourty_BTC_ETH(void)
{
    float BTC_ETH = 0;

    for (std::size_t i = this->_USDT_BTC.size() - 40; i != this->_USDT_BTC.size() ; i++)
        BTC_ETH += this->_USDT_BTC[i].close;
    this->_avgs.fourty_BTC_ETH = BTC_ETH / 40;
}

// On update les moyennes mobiles
void Trade::getAverages()
{
    this->twenty_USDT_ETH();
    this->fourty_USDT_ETH();
    this->twenty_USDT_BTC();
    this->fourty_USDT_BTC();
    this->twenty_BTC_ETH();
    this->fourty_BTC_ETH();
}

// On analyse les moyennes mobiles puis on agit dans cet ordre:
// 1 - Determiner la crypto la plus rentable a achter/vendre OU si pas intéressant on ne fait rien
// 2 - On détermine le choix le plus judicieux: 2.1 / 2.2
// 2.1 - Si il vaut mieux acheter ET qu'on a assez de money -> on achete
// 2.2 - Si il vaut mieux vendre ET qu'on a du stock  a vendre -> on vends
void Trade::actionEngine()
{
    this->getAverages();
    // USDT_ETH
    if (this->_stacks.USDT > (this->_USDT_ETH.back().open + 0.4) && this->_avgs.twenty_USDT_ETH > this->_avgs.fourty_USDT_ETH)
        this->buy(0);
    else if (this->_stacks.ETH > 0.1 && this->_avgs.twenty_USDT_ETH < this->_avgs.fourty_USDT_ETH)
        this->sell(0);
    // USDT_BTC
    else if (this->_stacks.USDT > (this->_USDT_BTC.back().open + 0.4) && this->_avgs.twenty_USDT_BTC > this->_avgs.fourty_USDT_BTC)
        this->buy(1);
    else if (this->_stacks.BTC > 0.1 && this->_avgs.twenty_USDT_BTC < this->_avgs.fourty_USDT_BTC)
        this->sell(1);
    // BTC_ETH
    else if (this->_stacks.BTC > (this->_BTC_ETH.back().open + 0.4) && this->_avgs.twenty_BTC_ETH > this->_avgs.fourty_BTC_ETH)
        this->buy(2);
    else if (this->_stacks.ETH > 0.1 && this->_avgs.twenty_BTC_ETH < this->_avgs.fourty_BTC_ETH)
        this->sell(2);
    // WAIT
    else
        this->wait();
}

// On achete la bonne crypto
// On achete 1 unité
void Trade::buy(int i)
{
    if (i == 0)
        std::cout << "buy USDT_ETH 1" << std::endl;
    if (i == 1)
        std::cout << "buy USDT_BTC 1" << std::endl;
    if (i == 2)
        std::cout << "buy BTC_ETH 1" << std::endl;
}

// On vends la bonne crypto
// On vends 1 quart de ce qu'on a
void Trade::sell(int i)
{
    std::string command = "sell ";

    if (i == 0) {
        command += "USDT_ETH ";
        command += std::to_string(this->_stacks.ETH * 0.25);
        std::cout << command << std::endl;
    }
    if (i == 1) {
        command += "USDT_BTC ";
        command += std::to_string(this->_stacks.BTC * 0.25);
        std::cout << command << std::endl;
    }
    if (i == 2) {
        command += "BTC_ETH ";
        command += std::to_string(this->_stacks.ETH * 0.25);
        std::cout << command << std::endl;
    }
}

// On passe son tour en gros
void Trade::wait() const
{
    std::cout << "no_moves" << std::endl;
}

Trade::~Trade()
{
}
