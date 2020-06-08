/*
** EPITECH PROJECT, 2020
** CNA_trade_2019
** File description:
** main
*/

#include <iostream>
#include <string>
#include "Trade.hpp"

int main(__attribute__((unused)) int ac, __attribute__((unused))char const **av)
{
    Trade *engine = new Trade();

    engine->mainEngine();

    return (0);
}

