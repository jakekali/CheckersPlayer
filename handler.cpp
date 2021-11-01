//
// Created by Jacob on 10/17/2021.
//

#include "handler.h"
#include "board.h"
#include "move.h"
#include <iostream>
#include <fstream>
#include <iterator>
#include <sstream>
#include <ctime>
#include <climits>


void handler::gameStart() {
    std::cout << "Do you want to load a game from a file? (Y/N):" << std::endl;
    std::string inputFromFileQ;
    // std::cin >> inputFromFileQ;
    if( 1 ||inputFromFileQ == "y" || inputFromFileQ == "Y"){
        std::cout << "Enter Filename: \n";
        std::string inputFileName;
        std::cin >> inputFileName;
        std::ifstream file(inputFileName);
        std::vector<int> c;
        std::string line;
        // Loops Through Lines in the File
        int index = 0;
        int newLineCount = 0;
        while(newLineCount < 8 && std::getline(file, line)){
            for(int i = 0; i < line.size(); i++){
                if(line[i] == '0'){
                    c.push_back(0);
                    index++;
                }else if(line[i] == '1') {
                    c.push_back(-gameBoard.val_regular);
                    index++;
                }else if(line[i] == '2'){
                    c.push_back(gameBoard.val_regular);
                    index++;
                }else if (line[i] == '3'){
                    c.push_back(-gameBoard.val_queen);
                    index++;
                }else if (line[i] == '4'){
                    c.push_back(gameBoard.val_queen);
                    index++;
                }
            }
            newLineCount++;
        }
        gameBoard.board_load(c);
        std::getline(file, line);
        if(line[0] == '2'){
            gameBoard.p1TurnFirst = false;
        }

        std::getline(file, line);
        std::stringstream geek(line);
        geek >> gameBoard.timelimit;
    }



}

void printGarysTab(int num){
    num *= 2;
    for(;num>0;num--){
        std::cerr << "    ";
    }

}


move handler::alphaBetaSearch(board RecGameBoard, bool p1Turn) {
    auto* currentGameBoard = new board(RecGameBoard);
    cleanUpBoards.push_back(currentGameBoard);

    std::pair<int, move> movePair = maxValue(currentGameBoard, p1Turn, -INT32_MAX, INT32_MAX,depthLimit);
    int c_start = std::clock();
    for(auto boardToBeCleaned : cleanUpBoards){
        delete boardToBeCleaned;
    }
    int c_end = std::clock();
    double time_elapsed_ms = (c_end-c_start);
    std::cout << "Clock Cycles: " << time_elapsed_ms << " ms\n";
    cleanUpBoards.clear();

    std::cout << "Best Move is: " << movePair.second.print();
    return movePair.second;
}

std::pair<int, move> handler::maxValue(board *RecGameBoard, bool p1Turn, int alpha, int beta, int depthLeft) {
    //If Game is Terminal
    auto endGame = RecGameBoard->EndGamePos(p1Turn);
    if(endGame.first){
        //RETURN UNTIL, NULL;
        printGarysTab(depthLimit - depthLeft);
        std::cerr << "Leaf-Max @ Depth: " << depthLimit - depthLeft << " Value: "<< endGame.second <<'\n';
        return std::make_pair(endGame.second,move());
    }
    //If Depth Limit is reached eval;
    if(depthLeft == 0){
        printGarysTab(depthLimit - depthLeft);
        int z = RecGameBoard->eval(p1Turn);
        if(z == 2){
            std::cerr << "Gary";
        }
        std::cerr << "Leaf-Max @ Depth: " << depthLimit - depthLeft << " Value: "<< z <<'\n';
        return std::make_pair(RecGameBoard->eval(p1Turn),move());
    }

    //V = -INF
    int value = INT32_MIN;
    int bestMoveIndex = 0;
    auto legalMoves = RecGameBoard->getLegalMoves(p1Turn);
    for(int i = 0; i < legalMoves.size();i++){
        board *tmpBoard = new board(RecGameBoard);
        tmpBoard->applyMove(legalMoves[i]);
        cleanUpBoards.push_back(tmpBoard);
        auto minPick = minValue(tmpBoard,!p1Turn,alpha,beta,depthLeft-1);
        if(minPick.first > value){
            value = minPick.first;
            bestMoveIndex = i;
            alpha = std::max(alpha,value);
        }
        if(value >= beta){
            return std::make_pair(value,move());
        }
    }
    auto returnMove = new move(legalMoves[bestMoveIndex]);
    cleanUpMoves.push_back(returnMove);
    printGarysTab(depthLimit - depthLeft);
    std::cerr << "Node-Max @ Depth: " << depthLimit - depthLeft << " Value: "<< value <<'\n';
    return std::make_pair(value,returnMove);
}
std::pair<int, move> handler::minValue(board *RecGameBoard, bool p1Turn, int alpha, int beta, int depthLeft) {
    //If Game is Terminal
    auto endGame = RecGameBoard->EndGamePos(p1Turn);
    if(endGame.first){
        //RETURN UNTIL, NULL;
        printGarysTab(depthLimit - depthLeft);
        std::cerr << "Leaf-Min @ Depth: " << depthLimit - depthLeft << " Value: "<< endGame.second <<'\n';
        //RETURN UNTIL, NULL;
        return std::make_pair(endGame.second,move());
    }
    //If Depth Limit is reached eval;
    if(depthLeft == 0){
        //RETURN UNTIL, NULL;
        printGarysTab(depthLimit - depthLeft);
        std::cerr << "Leaf-Min @ Depth: " << depthLimit - depthLeft << " Value: "<< endGame.second <<'\n';
        return std::make_pair(RecGameBoard->eval(p1Turn),move());
    }

    int value = INT32_MAX;
    int bestMoveIndex = 0;
    auto legalMoves = RecGameBoard->getLegalMoves(p1Turn);
    for(int i = 0; i < legalMoves.size();i++) {
        board *tmpBoard = new board(RecGameBoard);
        tmpBoard->applyMove(legalMoves[i]);
        cleanUpBoards.push_back(tmpBoard);
        auto maxPick = maxValue(tmpBoard,!p1Turn,alpha,beta,depthLeft-1);
        if(maxPick.first < value){
            value = maxPick.first;
            bestMoveIndex = i;
            beta = std::min(beta,value);
        }
        if(value <= alpha){
            return std::make_pair(value,legalMoves[bestMoveIndex]);
        }
    }
    printGarysTab(depthLimit - depthLeft);
    std::cerr << "Node-Min @ Depth: " << depthLimit - depthLeft << " Value: "<< value <<'\n';
    return std::make_pair(value,legalMoves[bestMoveIndex]);
}

