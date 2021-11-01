#include <iostream>
#include "board.h"
#include "handler.h"
#include "move.h"
#include <ctime>

const  int board::val_regular = 300;
const  int board::val_queen = 500;

const  std::string board::dashed = "   ------------------------------------------------------------------------";
const  std::string board::p1reg = "\e[44m.\033[0m";
const  std::string board::p1king = "\e[44m#\033[0m";
const  std::string board::p2reg = "\e[30m\e[105m.\033[0m";
const  std::string board::p2king = "\e[30m\e[105m#\033[0m";
const  std::string board::redSpace = "\e[31m\e[41m________\033[0m";
const  int board::neighbors [32][4] = {               {-1, -1, 04, 05}, {-1, -1,  5,  6}, {-1, -1,  6,  7}, {-1, -1,  7, -1},
                                                     {-1, 0,  -1,  8}, { 0,  1,  8,  9}, {1,   2,  9, 10}, {02, 03, 10, 11},
                                                     {4,  5,  12, 13}, { 5,  6, 13, 14}, {6,   7, 14, 15}, {7, -1, 15, -1},
                                                     {-1, 8,  -1, 16}, { 8,  9, 16, 17}, {9,  10, 17, 18}, {10, 11, 18, 19},
                                                     {12, 13, 20, 21}, {13, 14, 21, 22}, {14, 15, 22, 23}, {15, -1, 23, -1},
                                                     {-1, 16, -1, 24}, {16, 17, 24, 25}, {17, 18, 25, 26}, {18, 19, 26, 27},
                                                     {20, 21, 28, 29}, {21, 22, 29, 30}, {22, 23, 30, 31}, {23, -1, 31, -1},
                                                     {-1, 24, -1, -1}, {24, 25, -1, -1}, {25, 26, -1, -1}, {26, 27, -1, -1}};
int main() {
    std::setvbuf(stdout, nullptr, _IOFBF, 0);
    handler handle = handler();
    handle.gameStart();
    bool quit = false;
    while (!quit) {
        handle.gameBoard.printBoard();
        if (handle.gameBoard.p1TurnFirst) {

            std::pair<int, bool> endGame = handle.gameBoard.EndGamePos(true);
            if(endGame.second > 0){
                std::cout << "Congrats PLayer 1 has won";
            }
            if(endGame.second < 0){
                std::cout << "Congrats PLayer 2 has won";
            }
            std::clock_t c_start = std::clock();
            std::cout << "It's Player 1's Turn - Please Pick a Move \n";
            int index = 1;
            auto vr = handle.gameBoard.getLegalMoves(true);
            for (auto i : vr) {
                std::cout << index << ". " << i.print() << ") " << std::endl;
                index++;
            }
            std::clock_t c_end = std::clock();
            long time_elapsed_ms = (c_end-c_start);
            std::cout << "Clock Cycles: " << time_elapsed_ms << " ms\n";

            move bestMove = handle.alphaBetaSearch(handle.gameBoard,true);
            std::cout << bestMove.print() << '\n';


            int choice = 70;
            while (choice > vr.size() || choice == 0 || choice < -1) {
                int input;
                std::cout << "pick:";
                std::cin >> input;
                choice = (int) input;
            }

            if (choice == -1) {
                quit = true;
                continue;
            }
            handle.gameBoard.applyMove(vr[choice - 1]);

            handle.gameBoard.printBoard();
            endGame = handle.gameBoard.EndGamePos(false);
            if(endGame.first > 0){
                std::cout << "Congrats Player 2 has won";
                break;
            }
            if(endGame.first < 0){
                std::cout << "Congrats PLayer 1 has won";
                break;
            }

            std::cout << "It's Player 2's Turn - Please Pick a Move \n";
            auto vvvv = handle.gameBoard.getLegalMoves(false);
            index = 1;
            for (auto i : vvvv) {
                std::cout << index << ". " << i.print() << ") \n";
                index++;
            }

            choice = 70;
            while (choice > vvvv.size() || choice == 0 || choice < -1) {
                std::cout << "pick:";
                int input;
                std::cin >> input;
                choice = (int) input;
            }
            if (choice == -1) {
                quit = true;
                continue;
            }
            handle.gameBoard.applyMove(vvvv[choice - 1]);


        }else{

            std::pair<int, bool> endGame = handle.gameBoard.EndGamePos(false);
            if(endGame.first > 0){
                std::cout << "Congrats Player 2 has won";
            }
            if(endGame.first < 0){
                std::cout << "Congrats PLayer 1 has won";
            }

            std::cout << "It's Player 2's Turn - Please Pick a Move \n";
            int index = 1;
            auto vr = handle.gameBoard.getLegalMoves(false);
            for (auto i : vr) {
                std::cout << index << ". " << i.print() << ") " << std::endl;
                index++;
            }

            int choice = 70;
            while (choice > vr.size() || choice == 0 || choice < -1) {
                int input;
                std::cout << "pick:";
                std::cin >> input;
                choice = (int) input;
            }

            if (choice == -1) {
                break;
            }
            handle.gameBoard.applyMove(vr[choice - 1]);

            handle.gameBoard.printBoard();

            endGame = handle.gameBoard.EndGamePos(true);
            if(endGame.first > 0){
                std::cout << "Congrats Player 1 has won";
            }
            if(endGame.first < 0){
                std::cout << "Congrats PLayer 2 has won";
            }


            std::cout << "It's Player 1's Turn - Please Pick a Move \n";
            auto vvvv = handle.gameBoard.getLegalMoves(true);
            index = 1;
            for (auto i : vvvv) {
                std::cout << index << ". " << i.print() << ") \n";
                index++;
            }

            choice = 70;
            while (choice > vvvv.size() || choice == 0 || choice < -1) {
                std::cout << "pick:";
                int input;
                std::cin >> input;
                choice = (int) input;
            }
            if (choice == -1) {
                break;
            }
            handle.gameBoard.applyMove(vvvv[choice - 1]);


        }

    }



    }

