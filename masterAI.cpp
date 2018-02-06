// Project 2 - Othello AI
// David Brown 
// 28472403

#ifndef MASTERAI_CPP
#define MASTERAI_CPP

#include <ics46/factory/DynamicFactory.hpp>
#include "masterAI.hpp"
#include "OthelloBoard.hpp"
#include <iostream>

ICS46_DYNAMIC_FACTORY_REGISTER(OthelloAI, daviddb::masterAI, "Master AI (Required)");


std::pair<int, int> daviddb::masterAI::chooseMove(const OthelloGameState& state)
{
	//insert AI here - assume were starging with maxPlayer

	// determin what color the AI is
	if(state.isBlackTurn())
	{
		blackPlayerAI = true;
		whitePlayerAI = false;
	}
	else
	{
		blackPlayerAI = false;
		whitePlayerAI = true;
	}

	depth = 7;
	
	// begin to search for the best move based on the blackPlayer position 
	if(blackPlayerAI)
	{
		// determin board size 
		int bWidth = state.board().width();
		int bHeight = state.board().height();
		
		// for each valid move we want to search possible outcomes
		for(int i = 0; i < bWidth; i++) // rows 
		{
			for(int j = 0; j < bHeight; j++) // cols
			{
				// once a valid move is found start searching here
				if(state.isValidMove(i,j))
				{
					finalMove.first = i;
					finalMove.second = j;
					
					// make a move on a "cloned board" and return best move 
					tempStatePtr = state.clone();
					bestMove = searchMoves(*tempStatePtr, true, depth, i, j);
				}
			}
		}
		
		return finalMove;
	}// end of blackPlayerAI

	// begin to search for the best move based on the whitePlayer position 
	if(whitePlayerAI)
	{
		// determin board size
		int bWidth = state.board().width() - 1;
		int bHeight = state.board().height() - 1;

		// for each valid move we want to search possible outcomes
		for(int i = bWidth; i > -1 ; i--)
		{
			for(int j = bHeight; j > -1; j--)
			{
				if(state.isValidMove(i,j))
				{
					finalMove.first = i;
					finalMove.second = j;
					
					// make a move on a "cloned" board and return best move
					tempStatePtr = state.clone();
					bestMove = searchMoves(*tempStatePtr, true, depth, i, j);

				}
			}
		}
		
		return finalMove;
	} // end of whitePlayerAI

	return finalMove;
} // end of choose move


std::pair<int, int> daviddb::masterAI::calculateNextMove(const OthelloGameState & state)
{
	// calculate the next move based on being the blackPlayer
	if(blackPlayerAI)
	{
		// determin board size
		int bWidth = state.board().width();
		int bHeight = state.board().height();
		
		for(int i = 0; i < bWidth; i++)
		{
			for(int j = 0; j < bHeight; j++)
			{
				// once the next move is found return it	
				if(tempStatePtr -> isValidMove(i,j))
				{
					currentMove.first = i;
					currentMove.second = j;
				
					return currentMove;	
				}
		}
	}
	return currentMove;
	
	} // end of searching for blackPlayer move

	// calculate the next move based on being the blackPlayer
	if(whitePlayerAI)
	{

		// determin board size
		int bWidth = state.board().width() - 1;
		int bHeight = state.board().height() - 1;

		for(int i = bWidth; i > -1; i--)
		{
			for(int j = bHeight; j > -1; j--)
			{
				// once the next move is found return it
				if(tempStatePtr -> isValidMove(i,j))
				{
					currentMove.first = i;
					currentMove.second = j;
				
					return currentMove;	
				}
		}
	}
	return currentMove;
	} // end of whitePlayer move

	return currentMove;
} // end of calculateNextMove


std::pair<int, int> daviddb::masterAI::searchMoves(const OthelloGameState& state, bool maxPlayer, 
												   int depth, int xCoord, int yCoord)
{

	// valuse to be used in evaluation function for each cell
	int tileValues[8][8] = {
	 {20, -3, 11, 8, 8, 11, -3, 20}
	,{-3, -7, -4, 1, 1, -4, -7, -3}
	,{11, -4, 2, 2, 2, 2, -4, 11}
	,{8, 1, 2, -3, -3, 2, 1, 8}
	,{8, 1, 2, -3, -3, 2, 1, 8}
	,{11, -4, 2, 2, 2, 2, -4, 11}
	,{-3, -7, -4, 1, 1, -4, -7, -3}
	,{20, -3, 11, 8, 8, 11, -3, 20}};

	// return best move if game is over or base depth is reached	
	if((depth == 0) || (state.isGameOver()))
	{
		return bestMove;
	}
	
// begin calculating the best move based on being the blackPlayer
if(blackPlayerAI)
{
	// looking for the max score
	if(maxPlayer) 
	{
		// base evaluation amount 
		evaluationMaxValue = -1000;
		
		// make a "temporary move" based on next move found 
		tempStatePtr -> makeMove(xCoord, yCoord);
		
		// find the next move
		nextMove = calculateNextMove(*tempStatePtr);

		// check to see if the "evaluation amount" is better than the current amount
		if(tileValues[nextMove.first][nextMove.second] > evaluationMaxValue)
		{
			bestMove.first = currentMove.first;
			bestMove.second = currentMove.second;
		}

		// decrese the depth and search again based on being the minplayer
		--depth;
		bestMove = searchMoves(*tempStatePtr, false, depth, nextMove.first, nextMove.second);
		
		return bestMove;

	} // end of maxPlayer for blackAI

	// minPlayer for blackAI
	else
	{
		// base evaluation amount 
		evaluationMinValue = 1000;

		// make a "temporary move" based on next move found
		tempStatePtr -> makeMove(xCoord, yCoord);

		// find the next move
		nextMove = calculateNextMove(*tempStatePtr);
		
		// check to see if the "evaluation amount" is less than the current amount
		if(tileValues[nextMove.first][nextMove.second] < evaluationMinValue)
		{
			bestMove.first = nextMove.first;
			bestMove.second = nextMove.second;
		}

		// decrese the depth and search again based on being the maxplayer
		--depth;
		searchMoves(*tempStatePtr, true, depth, nextMove.first, nextMove.second);
		return bestMove;

	} // end of else (minPlayer for blackAI)

}

// begin calculating the best move based on being the whitePlayer
if(whitePlayerAI)
{
	// looking for max score
	if(maxPlayer) 
	{
		// base evaluation amount 
		evaluationMinValue = -1000;

		// make a "temporary move" based on next move found
		tempStatePtr -> makeMove(xCoord, yCoord);

		// find the next move
		nextMove = calculateNextMove(*tempStatePtr);

		// check to see if the "evaluation amount" is less than the current amount
		if(tileValues[nextMove.first][nextMove.second] > evaluationMinValue)
		{
			bestMove.first = nextMove.first;
			bestMove.second = nextMove.second;
		}

		// decrese the depth and search again based on being the maxplayer
		--depth;
		searchMoves(*tempStatePtr, false, depth, nextMove.first, nextMove.second);

		return bestMove;

	} // end of maxPlayer

	// minPlayer
	else
	{
		// base evaluation amount 
		evaluationMaxValue = 1000;
		
		// make a "temporary move" based on next move found
		tempStatePtr -> makeMove(xCoord, yCoord);
		
		// find the next move
		nextMove = calculateNextMove(*tempStatePtr);
		
		// check to see if the "evaluation amount" is greater than the current amount
		if(tileValues[nextMove.first][nextMove.second] < evaluationMaxValue)
		{
			bestMove.first = currentMove.first;
			bestMove.second = currentMove.second;
		}

		// decrese the depth and search again based on being the minplayer
		--depth;
		bestMove = searchMoves(*tempStatePtr, true, depth, nextMove.first, nextMove.second);

		return bestMove;


	} // end of else (minPlayer)

}

	return bestMove;
} // end of searchMoves

#endif
