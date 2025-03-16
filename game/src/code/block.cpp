#include "block.h"

Block::Block() {
	CellSize = 30;
	RotationState = 0;
	colors = GetCellsColors();
	rowOffset = 0;
	ColumnOffset = 0;
}

void Block::Draw() {
	int margin = 1;
	int padding = 10;
	std::vector<Position> tiles = GetCellPositions();
	for (Position item : tiles) {
		DrawRectangle(item.column*CellSize+margin+padding, item.row*CellSize+ margin + padding, CellSize- margin, CellSize-margin, colors[id]);
	}
}
void Block::Move(int rows, int columns) {
	rowOffset += rows;
	ColumnOffset+= columns;
}
std::vector<Position> Block::GetCellPositions() {
	std::vector<Position> tiles = Cells[RotationState];
	std::vector<Position>movedTiles;
	for (Position item : tiles) {
		Position newPos = Position(item.row + rowOffset, item.column + ColumnOffset);
		movedTiles.push_back(newPos);
	}
	return movedTiles;
}

void Block::Rotate(){
	RotationState++;
	if (RotationState == (int)Cells.size()) {
		RotationState = 0;
	}
}

void Block::UndoRotation(){
	RotationState--;
	if (RotationState == -1) {
		RotationState = Cells.size()-1;
	}
}
