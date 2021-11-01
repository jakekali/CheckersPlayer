//
// Created by Jacob on 10/17/2021.
//
#include <utility>      // std::pair, std::make_pair
#include <string>       // std::string
#include <iostream>     // std::cout
#include <vector>
#include "move.h"

#ifndef CHECKERSPLAYER_BOARD_H
#define CHECKERSPLAYER_BOARD_H
class board {
public:
    const static int val_regular;
    const static int val_queen;
    // -3 Represents opponents regular piece
    // -5 represent opponents king piece
    // 3 Represents max's regular piece
    // 5 represent max's king piece

private:
    const static std::string dashed;
    const static std::string p1reg;
    const static std::string p1king;
    const static std::string p2reg;
    const static std::string p2king;
    const static std::string redSpace;

    std::vector<move*> cleanMeUp= {};

    int board_arr [32] = { -val_regular, -val_regular, -val_regular, -val_regular,
                           -val_regular, -val_regular, -val_regular, -val_regular,
                           -val_regular, -val_regular, -val_regular, -val_regular,
                           0, 0, 0, 0,
                           0, 0, 0, 0,
                           val_regular, val_regular, val_regular, val_regular,
                           val_regular, val_regular, val_regular, val_regular,
                           val_regular, val_regular, val_regular, val_regular
    };
const static int neighbors [32][4];
    bool jumpAvaliable = false;
    std::string getPrintPiece(int row, int col);
    std::vector<move> getRegularMoves(int pos, bool p1Turn);

public:
    void board_load(const std::vector<int>& arr);
    std::vector<move> getLegalMoves(bool p1);
    void printBoard();
    board(board *pBoard) {
        for(int i = 0; i < 32; i++){
            board_arr[i] = pBoard->board_arr[i];
        }
    };
    board()= default;
    std::vector<move> getJumpMoves(std::vector<move> ogMoves, int pos, bool p1Turn);
    std::vector<move*> getJumpsByPosSteps(move* ogMove);
    std::vector<move> getJumpsByPosOG(int pos, int exclude, bool p1);

    bool p1TurnFirst = true;
    int timelimit = 5;
    void applyMove(const move& appliedMove);
    std::pair<bool, int> EndGamePos(bool p1);
    int eval(bool p1Turn);

};
#endif //CHECKERSPLAYER_BOARD_H
