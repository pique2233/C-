#include "application.h"
#include <iostream>
using namespace std;

#define NULL 0;

//board
int maze[8][8];
//初始化棋盘
void Application::initialize() {
    for (int i = 0; i <8 ; i++) {
        for (int j = 0; j <8 ; j++) {
            maze[i][j]=0;
        }
    }
}

Position Application::getStartPosition()
{
    initialize();
    return Position(0, 0);
}
//判断是否有皇后，对角线是否有皇后
/*
bool Application::isValid(const Position& p)
{
 int row = p.getRow();
 int column = p.getColumn();
    for (int i = 0; i < row; ++i) {
        if (maze[i][column]==9) return false;
    }//主对角线皇后
    for (int i = row-1,j=column-1; i >=0&&j>=0; i--,j--) {
        if (maze[i][j] == 9) return false;
    }//副对角线皇后
    for (int i = row+1,j=column+1; i >=0&&j<=8; i--,j++) {
        if (maze[i][j] == 9) return false;
    }
 return true;
}*/
bool Application::isValid(const Position& p) {
    int row = p.getRow();
    int column = p.getColumn();

    // Check column for any queens
    for (int i = 0; i < row; ++i) {
        if (maze[i][column] == 9) return false;
    }

    // Check main diagonal (top-left to bottom-right)
    for (int i = row - 1, j = column - 1; i >= 0 && j >= 0; i--, j--) {
        if (maze[i][j] == 9) return false;

    }

    // Check secondary diagonal (top-right to bottom-left)

    for (int i = row - 1, j = column + 1; i >= 0 && j < 8; i--, j++) {
        if (maze[i][j] == 9) return false;
    }

    return true;
}


bool Application::success(const Position& p)
{
    return p.getRow() == 7;
}
void Application::progress(const Position& p)
{
    maze[p.getRow()][p.getColumn()] = 9;
}
void Application::goBack(const Position& p)
{
    maze[p.getRow()][p.getColumn()] = 0;//撤销放置


}

void Application::print()
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
            cout << maze[i][j] << " ";
        cout << endl;
    }

}

//======================================================================

struct itrPosition
{
    int row;
    int column;
};

//application iterator
Application::Iterator::Iterator()
{
    currItrPosPtr = NULL;
}

Application::Iterator::Iterator(const Position& currPos)
{
    itrPosition* p = new itrPosition;
    p->row = currPos.getRow();
    p->column = currPos.getColumn();
    currItrPosPtr = p;
}


Position Application::Iterator::getNextPosition() {
    int row = ((itrPosition *)currItrPosPtr)->row;
    int column = ((itrPosition *)currItrPosPtr)->column;

    column++;
    ((itrPosition *)currItrPosPtr)->column = column;

    if (column >= 8) {
        return Position(row, 8); // 返回的位置超出了棋盘范围
    }
    return Position(row, column);
}


bool Application::Iterator::noNextPosition() {
    return ((itrPosition *)currItrPosPtr)->column >= 8;
}

Application::Iterator::~Iterator()
{
    delete (itrPosition*)currItrPosPtr;
}