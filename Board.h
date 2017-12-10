#ifndef BOARD_H
#define BOARD_H

class Board {
public:
	//Functions
	int GetPlacement(char, int, int);
	int GetWidth();
	int GetHeight();

protected:
	//Constructor
	Board();

	//Destructor
	~Board();

	//Functions
	void SetMyShots(bool, int, int);
	void SetEnemyShots(bool, int, int);
	int GetMyShot(int, int);
	void SetShipLayout(int, int, int);

private:
	//Variables
	static const int width= 10;
	static const int height= 10;

	int ship_layout[width][height];
	int enemy_shots[width][height];
	int my_shots[width][height];

	//Functions
};
Board::Board() {
	for(int x(0); x < width; x++) {
		for(int y(0); y < height; y++) {
			ship_layout[x][y]= 0;
			enemy_shots[x][y]= 0;
			my_shots[x][y]= 0;
		};
	};
}

Board::~Board() {}

int Board::GetPlacement(char board, int x, int y) {
	if(board == 's') {
		return ship_layout[x][y];
	} else if(board == 'e') {
		return enemy_shots[x][y];
	} else if(board == 'm') {
		return my_shots[x][y];
	};
}
int Board::GetWidth() {return width;}

int Board::GetHeight() {return height;}

void Board::SetMyShots(bool hit, int row, int col){
	my_shots[row][col]= int(hit) + 1;
}
void Board::SetEnemyShots(bool hit, int row, int col) {
	enemy_shots[row][col]= int(hit) + 1;
}
int Board::GetMyShot(int row, int col) {
	return my_shots[row][col];
}
void Board::SetShipLayout(int ship, int x, int y) {
	ship_layout[x][y]= ship;
}
#endif
