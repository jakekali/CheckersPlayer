//
// Created by Jacob on 10/17/2021.
//

#include "board.h"
#include <iostream>
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#include "move.h"
#include <stack>
#include <numeric>
#include <random>



//
//Board Printing
//
void board::printBoard() {
    std::cout << "Current Board: \n";

    std::cout << "Player 1 is " << p1reg << " (regular piece) and " << p1king << " (king) \n";
    std::cout << "Player 2 is " << p2reg << " (regular piece) and " << p2king << " (king) \n";


    for(int i = 0; i <= 7; i+=2){
    std::cout<<"   |" << redSpace << "|        |"  << redSpace << "|        |" << redSpace << "|        |"  << redSpace << "|        |" << '\n';
    std::cout<<"   |" << redSpace << "|   "<< getPrintPiece(i,1) <<"   |"  << redSpace << "|   "<< getPrintPiece(i,2) <<"   |"  << redSpace << "|   "<< getPrintPiece(i,3) <<"   |"  << redSpace << "|   "<< getPrintPiece(i,4) <<"   |"  <<  '\n';
    std::cout<<"   |" << redSpace << "|        |"  << redSpace << "|        |" << redSpace << "|        |"  << redSpace << "|        |" << '\n';
    std::cout << dashed << '\n';

    std::cout<<"   |" << "        |"  << redSpace << "|        |" << redSpace << "|        |"  << redSpace << "|        |" << redSpace << '\n';
    std::cout<<"   |" << "   "<< getPrintPiece(i+1,1) << "   |"  << redSpace << "|   "<< getPrintPiece(i+1,2) <<"   |" << redSpace << "|   "<< getPrintPiece(i+1,3) <<"   |"  << redSpace << "|  "<< getPrintPiece(i+1,4) <<"    |" << redSpace << '\n';
    std::cout<<"   |" << "        |"  << redSpace << "|        |" << redSpace << "|        |"  << redSpace << "|        |" << redSpace << '\n';
    std::cout << dashed << '\n';
    }

}

std::string board::getPrintPiece(int row, int col) {
    if(board_arr[((row*4) + col) -1 ] == 0){
        std::string val = std::to_string(row*4 + col -1);
        if(val.size() > 1){
            return val;
        }else {
            return " " + val;
        }
    }
    if(board_arr[((row*4) + col) -1 ] == -val_regular){
        return " " + p1reg;
    }
    if(board_arr[((row*4) + col) -1 ] == -val_queen){
        return " " + p1king;
    }
    if(board_arr[((row*4) + col) -1 ] == val_regular){
        return " " + p2reg;
    }
    if(board_arr[((row*4) + col) -1] == val_queen){
        return " " + p2king;
    }
    return " ?";
}


void board::board_load(const std::vector<int>& arr) {
    int index = 0;
    for (int i : arr) {
        board_arr[index] = i;
        index++;
        if (index >= 32)
            break;
    }
}
std::vector<move> board::getRegularMoves(int pos, bool p1Turn) {
    std::vector<move> moves; // to, from
    int piece_pos = pos;
    if(p1Turn) {
            if (board_arr[piece_pos] == -val_regular) {
                if (board::neighbors[piece_pos][2] != -1 && board_arr[board::neighbors[piece_pos][2]] == 0) {
                    moves.emplace_back(piece_pos, board::neighbors[piece_pos][2]);
                }
                if (board::neighbors[piece_pos][3] != -1 && board_arr[board::neighbors[piece_pos][3]] == 0) {
                    moves.emplace_back(piece_pos, board::neighbors[piece_pos][3]);
                }
            }
            if (board_arr[piece_pos] == -val_queen) {
                if (board::neighbors[piece_pos][0] != -1 && board_arr[neighbors[piece_pos][0]] == 0) {
                    moves.emplace_back(piece_pos, board::neighbors[piece_pos][0]);
                }
                if (board::neighbors[piece_pos][1] != -1 && board_arr[board::neighbors[piece_pos][1]] == 0) {
                    moves.emplace_back(piece_pos, board::neighbors[piece_pos][1]);
                }
                if (board::neighbors[piece_pos][2] != -1 && board_arr[board::neighbors[piece_pos][2]] == 0) {
                    moves.emplace_back(piece_pos, board::neighbors[piece_pos][2]);
                }
                if (board::neighbors[piece_pos][3] != -1 && board_arr[board::neighbors[piece_pos][3]] == 0) {
                    moves.emplace_back(piece_pos, board::neighbors[piece_pos][3]);
                }
            }
    }else{
            if (board_arr[piece_pos] == val_regular) {
                if (neighbors[piece_pos][0] != -1 && board_arr[neighbors[piece_pos][0]] == 0) {
                    moves.emplace_back(piece_pos, neighbors[piece_pos][0]);
                }
                if (neighbors[piece_pos][1] != -1 && board_arr[neighbors[piece_pos][1]] == 0) {
                    moves.emplace_back(piece_pos, neighbors[piece_pos][1]);
                }
            }
            if (board_arr[piece_pos] == val_queen) {
                if ((neighbors[piece_pos][0] != -1) && board_arr[neighbors[piece_pos][0]] == 0) {
                    moves.emplace_back(piece_pos, neighbors[piece_pos][0]);
                }
                if ((neighbors[piece_pos][1] != -1 ) && board_arr[neighbors[piece_pos][1]] == 0) {
                    moves.emplace_back(piece_pos, neighbors[piece_pos][1]);
                }
                if ((neighbors[piece_pos][2] != -1) && board_arr[neighbors[piece_pos][2]] == 0) {
                    moves.emplace_back(piece_pos, neighbors[piece_pos][2]);
                }
                if ((neighbors[piece_pos][3] != -1) && board_arr[neighbors[piece_pos][3]] == 0) {
                    moves.emplace_back(piece_pos, neighbors[piece_pos][3]);
                }
            }


        }
    return moves;
}

std::vector<move> board::getLegalMoves(bool p1) {
    jumpAvaliable = false;
    std::vector<move> regMoves;
    std::vector<move> jumpMoves;
    for (int pos = 31; pos > -1; pos--){
        if((board_arr[pos] < 0 && !p1)||(board_arr[pos] > 0 && p1) || board_arr[pos] == 0) continue;
        auto jumpMovesNew = getJumpMoves(std::vector<move>(),pos,p1);
        jumpMoves.insert(jumpMoves.end(),jumpMovesNew.begin(),jumpMovesNew.end());
        if(!jumpAvaliable){
            if(!jumpMovesNew.empty()){
                jumpAvaliable = true;
            }else{
                auto regMovesNew = getRegularMoves(pos, p1);
                regMoves.insert(regMoves.end(), regMovesNew.begin(), regMovesNew.end());
            }
        }
    }
    if(!jumpAvaliable)
        return regMoves;
    return jumpMoves;
}

std::vector<move> board::getJumpMoves(std::vector<move> ogMoves, int pos, bool p1Turn) {
if(ogMoves.empty()){
    ogMoves = getJumpsByPosOG(pos, -1, p1Turn);
}
    std::vector<move*> movesReturn;
    for(int i = 0; i < ogMoves.size(); i++){
        move* tmp = new move(ogMoves[i]);
        std::vector<move*> newMoves = getJumpsByPosSteps(tmp);
        if(newMoves.empty()){
            continue;
        }
        ogMoves.erase(ogMoves.begin() + i);
        ogMoves.insert(ogMoves.begin(), newMoves.begin(),newMoves.end());
    }

    return ogMoves;
}


std::vector<move> board::getJumpsByPosOG(int pos, int exclude, bool p1) {

    //If it's the wrong color piece: say no jumps
    if(board_arr[pos] == 0 || (board_arr[pos] > 0 && p1) || board_arr[pos] < 0 && !p1){
        return std::vector<move>();
    }

    std::vector<move> moves;
    for(int i = 0; i < 4; i++){
        //if it is excluded; don't check
        if(i == exclude){
            continue;
        }
        // if it is regular piece, and it can not move in that direction, don't check
        if (board_arr[pos] != val_queen && board_arr[pos] != -val_queen){
            if(p1 && (i == 0 || i == 1)) continue;
            if(!p1 && (i == 2 || i == 3)) continue;
        }

        int neighborsPiece_index =  board::neighbors[pos][i];
        if(neighborsPiece_index == -1){continue;}

        int neighborsPiece_val = board_arr[neighborsPiece_index];
        //check if the opposite player's piece is adjacent


        if((p1 && neighborsPiece_val <= 0) || (!p1 && neighborsPiece_val >= 0)){
            continue;
        }

        int jumpToPiece_index = board::neighbors[neighborsPiece_index][i];
        if (jumpToPiece_index == -1){
            continue;
        }

        int jumpToPiece_val = board_arr[jumpToPiece_index];
        //check if the following space is open
        if(jumpToPiece_val != 0){
            continue;
        }

        //I wrote this on 10/31
        bool reached = false;
        if(p1) {
            if (jumpToPiece_val < 32 && jumpToPiece_val > 27 && board_arr[pos] == -val_regular){
                reached = true;
            }
        }else {
            if (jumpToPiece_val < 4 && jumpToPiece_val > -1 && board_arr[pos] == val_regular) {
                reached = true;
            }
        }
        int stepps [2] = {pos, jumpToPiece_index};
        int nieh [1] = {neighborsPiece_index};
        moves.emplace_back(pos, jumpToPiece_index, i  ,stepps,p1, nieh,reached,2);

    }
    return moves;
}

std::vector<move*> board::getJumpsByPosSteps(move* ogMove) {
    int exc = -1;
    if(ogMove->recentDir  == 2) exc = 1;
    if(ogMove->recentDir  == 1) exc = 2;
    if(ogMove->recentDir  == 3) exc = 0;
    if(ogMove->recentDir  == 0) exc = 3;

    std::vector<move*> moves1;
    for(int i = 0; i < 4; i++){
        if(ogMove->reachedEnd){
            continue;
        }
        //if it is excluded; don't check
        if(i == exc){
            continue;
        }
        // if it is regular piece, and it can not move in that direction, don't check
        if (board_arr[ogMove->inital_pos] != val_queen && board_arr[ogMove->inital_pos] != -val_queen){
            if(ogMove->p1 && (i == 0 || i == 1)) continue;
            if(!ogMove->p1 && (i == 2 || i == 3)) continue;
        }

        int neighborsPiece_index =  board::neighbors[ogMove->final_pos][i];
        if(neighborsPiece_index == -1){continue;}


        int neighborsPiece_val = board_arr[neighborsPiece_index];
        //check if the opposite player's piece is adjacent
        if(ogMove->p1){
            if(neighborsPiece_val <= 0){
                continue;
            }
        }else{
            if(neighborsPiece_val >= 0){
                continue;
            }
        }

        int jumpToPiece_index = board::neighbors[neighborsPiece_index][i];
        if (jumpToPiece_index == -1){
            continue;
        }
        int jumpToPiece_val = board_arr[jumpToPiece_index];
        //check if the following space is open
        if(jumpToPiece_val != 0){
            continue;
        }

        bool breakme = false;
        //Pice
        for(int z : ogMove->neighborsPiece){
            if(z == neighborsPiece_index){
                breakme = true;
                break;
            }
        }
        if(breakme){
            continue;
        }

        bool reached = false;
        if(ogMove->p1) {
            if (jumpToPiece_val < 32 && jumpToPiece_val > 27 && board_arr[ogMove->inital_pos] == -val_regular){
                reached = true;
            }
        }else {
            if (jumpToPiece_val < 4 && jumpToPiece_val > -1 && board_arr[ogMove->inital_pos] == val_regular) {
                reached = true;
            }
        }

        move *temp = new move(ogMove);
        cleanMeUp.push_back(temp);
        temp->addJumpPart(jumpToPiece_index,i,reached,neighborsPiece_index);
        moves1.push_back(temp);
        i++;
        i--;
    }

    for(int i = 0; i < moves1.size(); i++) {
        std::vector<move*> newMoves = getJumpsByPosSteps(moves1[i]);
        if(!newMoves.empty()) {
            //DELTE THE ITEM ALSO, NOt JUST THE POINTER
            moves1.erase(moves1.begin() + i);
            moves1.insert(moves1.begin(), newMoves.begin(), newMoves.end());
        }
    }
    return moves1;
}

void board::applyMove(const move& appliedMove) {
    if(appliedMove.stepsFull > 0){
        int piece_type = board_arr[appliedMove.inital_pos];
        this->board_arr[appliedMove.inital_pos] = 0;
        for(int pos : appliedMove.neighborsPiece){
            this->board_arr[pos] = 0;
        }
        this->board_arr[appliedMove.final_pos] = piece_type;
        jumpAvaliable = false;
        if(appliedMove.final_pos > 27 && this->board_arr[appliedMove.final_pos] == -board::val_regular){
            this->board_arr[appliedMove.final_pos] = -board::val_queen;
        }else if(appliedMove.final_pos < 4 && this->board_arr[appliedMove.final_pos] == board::val_regular){
            this->board_arr[appliedMove.final_pos] = board::val_queen;
        }

        for(move* moveOld : cleanMeUp){
            delete moveOld;
        }
        cleanMeUp.clear();

    }else{
        this->board_arr[appliedMove.final_pos] = board_arr[appliedMove.inital_pos];
        this->board_arr[appliedMove.inital_pos] = 0;
        if(appliedMove.final_pos > 27 && this->board_arr[appliedMove.final_pos] == -board::val_regular){
            this->board_arr[appliedMove.final_pos] = -board::val_queen;
        }else if(appliedMove.final_pos < 4 && this->board_arr[appliedMove.final_pos] == board::val_regular){
            this->board_arr[appliedMove.final_pos] = board::val_queen;
        }
    }

}

std::pair<bool, int> board::EndGamePos(bool p1) {
    std::vector<move> legalMovesP1 = getLegalMoves(p1);
    std::vector<move> legalMovesP2 = getLegalMoves(!p1);
    if(!legalMovesP1.empty() && !legalMovesP2.empty()) {
        return std::make_pair(false, 0);
    }
    if(legalMovesP2.empty()){
        return std::make_pair(true, 100000);
    }
    if(legalMovesP1.empty()){
        return std::make_pair(true, -100000);
    }
     return std::make_pair(false, 0);
}

int board::eval(bool p1Turn) {
    int sumOfBoard = 0;
    for(int i : board_arr)
        sumOfBoard += i;
    if(p1Turn)
        return -sumOfBoard + rand() % 10 + 1;
    return sumOfBoard + rand() % 10 + 1;
}












