#pragma once
#include "Grid.h"
#include "blocks.cpp"
class Game {
	public:
		Game();
		Block GetRandomBlock();
		std::vector<Block> GetAllBlocks();
		void Draw();
		void HandleInput();
		void MoveBlockLeft();
		void MoveBlockLRight();
		void MoveBlockDown();
		void Run();
		Grid grid;
		bool GameOver;
	private:
		bool IsBlockOutside();
		void Reset();
		void RotateBlock();
		void LockBlock();
		bool BlockFits();
		std::vector<Block> blocks;
		Block currentBlock;
		Block nextBlock;
};