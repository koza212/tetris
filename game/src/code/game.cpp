#include "game.h"
#include <random>

Game::Game(){
	grid = Grid();
	blocks = GetAllBlocks();
	currentBlock = GetRandomBlock();
	nextBlock = GetRandomBlock();
	GameOver = false;
}

double lastUpdateTime = 0;

bool EventTriggered(double interval) {
	double currentTime = GetTime();
	if (currentTime - lastUpdateTime >= interval) {
		lastUpdateTime = currentTime;
		return true;
	}
	return false;
}

Block Game::GetRandomBlock() {
	srand(time(NULL));
	if (blocks.empty()) {
		blocks = GetAllBlocks();
	}
	int randomIndex = rand() % blocks.size();
	Block block = blocks[randomIndex];
	blocks.erase(blocks.begin() + randomIndex);
	return block;
}
 

std::vector<Block> Game::GetAllBlocks() {
	return { Iblock(), Jblock(), Oblock(), Sblock(), Tblock(), Zblock() };
}
void Game::Draw() {
	grid.Draw();
	currentBlock.Draw();
}

void Game::HandleInput(){
	int keyPressed = GetKeyPressed();
	if (GameOver && keyPressed != 0) {
		GameOver = false;
		Reset();
	}
	switch (keyPressed) {
		case KEY_LEFT:
			MoveBlockLeft();
			break;
		case KEY_RIGHT:
			MoveBlockLRight();
			break;
		case KEY_DOWN:
			MoveBlockDown();
			break;
		case KEY_UP:
			RotateBlock();
			break;
	}
}
void Game::MoveBlockLeft() {
	if (!GameOver) {
		currentBlock.Move(0, -1);
		if (IsBlockOutside() || BlockFits() == false) {
			currentBlock.Move(0, 1);
		}
	}
}
void Game::MoveBlockLRight() {
	if (!GameOver) {
		currentBlock.Move(0, 1);
		if (IsBlockOutside() || BlockFits() == false) {
			currentBlock.Move(0, -1);
		}
	}
}
void Game::MoveBlockDown() {
	if (!GameOver) {
		currentBlock.Move(1, 0);
		if (IsBlockOutside() || BlockFits() == false) {
			currentBlock.Move(-1, 0);
			LockBlock();
		}
	}
}

void Game::Run(){
	HandleInput();
	if (EventTriggered(0.2)) {
		MoveBlockDown();
	}
	BeginDrawing();
	ClearBackground(background);
	Draw();
	EndDrawing();
}

bool Game::IsBlockOutside(){
	std::vector<Position> tiles = currentBlock.GetCellPositions();
	for (Position item : tiles) {
		if (grid.isCellOutside(item.row, item.column)) {
			return true;
		}
	}
	return false;
}

void Game::Reset(){
	grid.Initialize();
	blocks = GetAllBlocks();
	currentBlock = GetRandomBlock();
	nextBlock = GetRandomBlock();
}

void Game::RotateBlock(){
	if (!GameOver) {
		currentBlock.Rotate();
		if (IsBlockOutside() || BlockFits() == false) {
			currentBlock.UndoRotation();
		}
	}
}

void Game::LockBlock(){
	std::vector<Position> tiles = currentBlock.GetCellPositions();
	for (Position item : tiles) {
		grid.grid[item.row][item.column] = currentBlock.id;
	}
	currentBlock = nextBlock;
	if (BlockFits() == false) {
		GameOver = true;
	}
	nextBlock = GetRandomBlock();
	grid.ClearFullRows();
}

bool Game::BlockFits(){
	std::vector<Position> tiles = currentBlock.GetCellPositions();
	for (Position item : tiles) {
		if (grid.isCellEmpty(item.row, item.column) == false) {
			return false;
		}
	}
	return true;
}
