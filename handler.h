//
// Created by Jacob on 10/17/2021.
//
#include <iostream>
#include "board.h"
#ifndef CHECKERSPLAYER_HANDLER_H
#define CHECKERSPLAYER_HANDLER_H


class handler {
public:
    handler()= default;
    board gameBoard;
    void gameStart();
    int depthLimit = 6;

    std::vector<board *> cleanUpBoards;
    std::vector<move *> cleanUpMoves;

    std::pair<int, move> minValue(board *RecGameBoard, bool p1Turn, int alpha, int beta, int depthLeft);
    std::pair<int, move> maxValue(board *RecGameBoard, bool p1Turn, int alpha, int beta, int depthLeft);
    move alphaBetaSearch(board RecGameBoard, bool p1Turn);
};


#endif //CHECKERSPLAYER_HANDLER_H
