// Project 2 - Othello AI
// David Brown 
// 28472403

#ifndef MASTERAI_HPP
#define MASTERAI_HPP

#include "OthelloAI.hpp"


namespace daviddb
{
	class masterAI : public OthelloAI
	{
	public:
		virtual std::pair<int, int> chooseMove(const OthelloGameState& state);
		std::pair<int, int> calculateNextMove(const OthelloGameState & state);
		std::pair<int, int> searchMoves(const OthelloGameState& state, 
											  bool maxPlayer, int depth, 
												int xCoord, int yCoord);


	private: 
		bool blackPlayerAI;
		bool whitePlayerAI;
		int evaluationMaxValue;
		int evaluationMinValue;
		int depth;
		std::pair<int, int> bestMove;
		std::pair<int, int> nextMove;
		std::pair<int, int> currentMove;
		std::pair<int, int> maxMove;
		std::pair<int, int> minMove;
		std::pair<int, int> finalMove;
		std::unique_ptr<OthelloGameState> tempStatePtr;


	};
}



#endif
