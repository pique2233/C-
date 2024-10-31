#include "backtrack.h"

BackTrack::BackTrack() {}
	
BackTrack::BackTrack(const Application& thisApp)
{
	this->app = thisApp;
}

bool BackTrack::backTrack(const Position& currPos)
{
    app.progress(currPos);

    if (app.success(currPos))
        return true;
    else
    {
        Application::Iterator itr(currPos);

        Position nextPos;

//按照行迭代
        while (!itr.noNextPosition())
        {
            nextPos = itr.getNextPosition();
            if (app.isValid(nextPos) && backTrack(nextPos)) //recursive call if valid
                return true;
        }
        //cannot reach goal from currPos
        app.goBack(currPos); //backtrack
        return false; //from currPos, no solution
    }

}

/*
bool BackTrack::backTrack(const Position& currPos)
{
    app.progress(currPos);

    if (app.success(currPos))
        return true;
    // 递归地尝试在下一行放置皇后
    for (int col = 0; col < 8; col++) {
        Position nextPos(currPos.getRow() + 1, col);
        if (app.isValid(nextPos) && backTrack(nextPos)) // 如果合法，递归继续
            return true;
    }
    // 无法从当前位置到达终点，回溯
    app.goBack(currPos); // 回溯
    return false;
}
*/