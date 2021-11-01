//
// Created by Jacob on 10/18/2021.
//
#include <utility>      // std::pair, std::make_pair
#include <string>       // std::string
#include <iostream>     // std::cout
#include <vector>


#ifndef CHECKERSPLAYER_MOVE_H
#define CHECKERSPLAYER_MOVE_H

class move {
public:
    int inital_pos = -1;
    int final_pos = -1;

    bool jump_move = false;
    int steps [32] = {-1, -1, -1, -1, -1, -1, -1, -1,-1, -1, -1, -1, -1, -1, -1, -1,-1, -1, -1, -1, -1, -1, -1, -1,-1, -1, -1, -1, -1, -1, -1, -1};
    int stepsFull = 0;
    int neighborsPiece [32] = {-1, -1, -1, -1, -1, -1, -1, -1,-1, -1, -1, -1, -1, -1, -1, -1,-1, -1, -1, -1, -1, -1, -1, -1,-1, -1, -1, -1, -1, -1, -1, -1};
    int recentDir = -1;
    bool reachedEnd = false;
    bool p1;

    move(move const &inMove) {
        inital_pos = inMove.inital_pos;
        final_pos = inMove.final_pos;
        jump_move = inMove.jump_move;
        stepsFull = inMove.stepsFull;
        if(stepsFull > 0 && jump_move){
            for(int i = 0; i < (stepsFull - 1); i++){
                steps[i] = inMove.steps[i];
                neighborsPiece[i] = inMove.neighborsPiece[i];
            }
            steps[stepsFull-1] = inMove.steps[stepsFull-1];
        }
        reachedEnd = inMove.reachedEnd;
        p1 = inMove.p1;
    }

    move(move const *inMove) {
        inital_pos = inMove->inital_pos;
        final_pos = inMove->final_pos;
        jump_move = inMove->jump_move;
        stepsFull = inMove->stepsFull;
        if(stepsFull > 0 && jump_move){
            for(int i = 0; i < (stepsFull - 1); i++){
                steps[i] = inMove->steps[i];
                neighborsPiece[i] = inMove->neighborsPiece[i];
            }
            steps[stepsFull-1] = inMove->steps[stepsFull-1];
        }
        reachedEnd = inMove->reachedEnd;
        p1 = inMove->p1;
    }

    move() = default;

    move(int inital_pos_in, int final_pos_in, int dir, const int stepsIn [], bool p1_n, const int neighborsPiece_index [], bool reach, int stepsFull_i) {
        inital_pos = inital_pos_in;
        final_pos = final_pos_in;
        jump_move = true;
        recentDir = dir;
        reachedEnd = reach;
        stepsFull = stepsFull_i;
        for(int i = 0; i < (stepsFull - 1); i++){
            steps[i] = stepsIn[i];
            neighborsPiece[i] = neighborsPiece_index[i];
        }
        steps[stepsFull-1] = stepsIn[stepsFull-1];
        p1 = p1_n;
    }


    move(int initalPosIn, int final_pos_in) {
        inital_pos = initalPosIn;
        final_pos = final_pos_in;
        jump_move = false;
    }

    std::string print(){
        if(!jump_move)
            return "("+std::to_string(inital_pos)+", "+std::to_string(final_pos)+")";
        std::string output = "(";
        for(int i = 0; i < stepsFull; i++){
            output += std::to_string(steps[i]) + ", ";
        }
        return output;

    }
    
    move addJumpPart(int final, int dir, bool reachEd, int neigbor){
        final_pos = final;
        recentDir = dir;
        reachedEnd = reachEd;
        steps[stepsFull] = final;
        neighborsPiece[stepsFull-1] = neigbor;
        stepsFull += 1;
    }
    
};


#endif //CHECKERSPLAYER_MOVE_H
