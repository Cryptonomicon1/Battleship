#include "Input.h"
#include "ArIn.h"

#ifndef PLAYER_H
#define PLAYER_H

class Player : public Board, public ArIn {
public:
	//Constructor
	Player(bool human);

	//Destructor
	~Player();

	//Functions
	void LoadInput(Input*);
	bool GetHit(int, char);
	void SetHit(bool, int, char);
	char GetColumn();
	int GetRow();
	int GetHits();
	bool GetHuman();
	void AIAttack(bool);
	void SetRandomShipPlacement();

private:
	//Variables
	int row;
	char column;
	bool Hit;
	vector<vector<vector<int>>> schema;
	int ai_strategy;
	int hit_count;
	int temp_hit_count;
	bool human;
	bool change_case;

	//Functions
	int CharToInt(char);
	void RandCoords();
	void DeleteChosenSchemaCell();
	void DeleteEmptyRows();
	bool OutOfBounds();
};
Player::Player(bool h) {
	schema.resize(10, vector<vector<int>>(10, vector<int>(2, 0)));
	for(int i(0); i < 10; i++) {
		for(int j(0); j < 10; j++) {
			schema[i][j][0]= i;
			schema[i][j][1]= j;
		};
	};
	ai_strategy= 0;
	hit_count= 0;
	temp_hit_count= 0;
	human= h;
	change_case= false;

	if(human) {
		RandomShip('P');
		RandomShip('S');
		RandomShip('D');
		RandomShip('B');
		RandomShip('C');

		for(int r(0); r < 10; r++) {
			for(int c(0); c < 10; c++) {
				SetShipLayout(GetLayout(r, c), r, c);
			};
		};
	} else {
		RandomShip('P');
		RandomShip('S');
		RandomShip('D');
		RandomShip('B');
		RandomShip('C');

		for(int r(0); r < 10; r++) {
			for(int c(0); c < 10; c++) {
				SetShipLayout(GetLayout(r, c), r, c);
			};
		};
		RandCoords();
	};
}
Player::~Player() {}

void Player::LoadInput(Input* I) {
	row= I->get_row();
	column= I->get_column();
}
bool Player::GetHit(int x, char yc) {
	int y= CharToInt(yc);

	if(GetPlacement('s', x, y) != 0) {
		SetEnemyShots(true, x, y);
		return true;
	} else {
		SetEnemyShots(false, x, y);
		return false;
	};
}
bool Player::GetHuman() {return human;}

void Player::SetHit(bool H, int x, char yc) {

	int y= CharToInt(yc);
	SetMyShots(H, x, y);
	if(H) {
		hit_count+= 1;
		temp_hit_count+= 1;
	};
}
char Player::GetColumn() {
	if(column >= 'a' && column <= 'z') {
		return column + 'A' - 'a';
	} else {
		return column;
	};
};
int Player::GetRow() {return row;}

int Player::GetHits() {return hit_count;}

int Player::CharToInt(char in) {
	int out;
	if(in >= 'A' && in <= 'Z') {
		out= int(in) - 'A';
	} else if(in >= 'a' && in <= 'z') {
		out= int(in) - 'a';
	} else out= 0;

	return out;
}
void Player::AIAttack(bool H) {
	bool ai_think= true;

	while(ai_think) {
		switch(ai_strategy) {
			case 0 :
				if(!H) {
					RandCoords();
					ai_think= false;
					change_case= false;
				} else {
					change_case= true;
					ai_strategy+= 1;
					temp_hit_count= 0;
				};
				break;
			case 1 : //Cases 1-4 is finding the ship around the hit.
				if(change_case) {
					row++;
				};
				if(OutOfBounds() && change_case) {
					ai_strategy+= 1;
					change_case= true;
				} else if(!H && !change_case) {
					ai_strategy+= 1; //miss
					change_case= true;
				} else if(H && !change_case) {
					ai_strategy+= 4; //hit
					change_case= true;
				} else {
					change_case= false;
					ai_think= false;
				};
				break;
			case 2 :
				if(change_case) {
					row--;
					column++;
				};
				if(OutOfBounds() && change_case) {
					ai_strategy+= 1;
					change_case= true;
				} else if(!H && !change_case) {
					ai_strategy+= 1; //miss
					change_case= true;
				} else if(H && !change_case) {
					ai_strategy+= 4; //hit
					change_case= true;
				} else {
					change_case= false;
					ai_think= false;
				};
				break;
			case 3 :
				if(change_case) {
					row--;
					column--;
				};
				if(OutOfBounds() && change_case) {
					ai_strategy+= 1;
					change_case= true;
				} else if(!H && !change_case) {
					ai_strategy+= 1; //miss
					change_case= true;
				} else if(H && !change_case) {
					ai_strategy+= 4; //hit
					change_case= true;
				} else {
					change_case= false;
					ai_think= false;
				};
				break;
			case 4 :
				if(change_case) {
					row++;
					column--;
				};
				if(OutOfBounds() && change_case) {
					ai_strategy= 0;
					change_case= true;
				} else if(!H && !change_case) {
					ai_strategy= 0; //miss
					change_case= true;
				} else if(H && !change_case) {
					ai_strategy+= 4; //hit
					change_case= true;
				} else {
					change_case= false;
					ai_think= false;
				};
				break;
			case 5 : //Cases 5-8 is raking the ship
				row++;
				if(OutOfBounds()) {
					ai_strategy+= 4;
					change_case= true;
				} else if(!H && !change_case) {
					ai_strategy+= 4; //miss
					change_case= true;
				} else if(H && !change_case) {
					ai_think= false; //hit
				} else {
					change_case= false;
					ai_think= false;
				};
				break;
			case 6 :
				column++;
				if(OutOfBounds()) {
					ai_strategy+= 4;
					change_case= true;
				} else if(!H && !change_case) {
					ai_strategy+= 4; //miss
					change_case= true;
				} else if(H && !change_case) {
					ai_think= false; //hit
				} else {
					change_case= false;
					ai_think= false;
				};
				break;
			case 7 :
				row--;
				if(OutOfBounds()) {
					ai_strategy+= 4;
					change_case= true;
				} else if(!H && !change_case) {
					ai_strategy+= 4; //miss
					change_case= true;
				} else if(H && !change_case) {
					ai_think= false; //hit
				} else {
					change_case= false;
					ai_think= false;
				};
				break;
			case 8 :
				column--;
				if(OutOfBounds()) {
					ai_strategy+= 4;
					change_case= true;
				} else if(!H && !change_case) {
					ai_strategy+= 4; //miss
					change_case= true;
				} else if(H && !change_case) {
					ai_think= false; //hit
				} else {
					change_case= false;
					ai_think= false;
				};
				break;
			case 9 : //Cases 9-12 just reverse the raking direction
				row-= (temp_hit_count + 2);
				ai_strategy+= 4;
				break;
			case 10 :
				column-= (temp_hit_count + 2);
				ai_strategy+= 4;
				break;
			case 11 :
				row+= (temp_hit_count + 2);
				ai_strategy+= 4;
				break;
			case 12 :
				column+= (temp_hit_count + 2);
				ai_strategy+= 4;
				break;
			case 13 : //Cases 13-16 rake backwards
				row--;
				if(OutOfBounds()) {
					ai_strategy= 0;
				} else if(!H && !change_case) {
					ai_strategy= 0; //miss
				} else if(H && !change_case) {
					ai_think= false; //hit
				} else {
					change_case= false;
					ai_think= false;
				};
				break;
			case 14 :
				column--;
				if(OutOfBounds()) {
					ai_strategy= 0;
				} else if(!H && !change_case) {
					ai_strategy= 0; //miss
				} else if(H && !change_case) {
					ai_think= false; //hit
				} else {
					change_case= false;
					ai_think= false;
				};
				break;
			case 15 :
				row++;
				if(OutOfBounds()) {
					ai_strategy= 0;
				} else if(!H && !change_case) {
					ai_strategy= 0; //miss
				} else if(H && !change_case) {
					ai_think= false; //hit
				} else {
					change_case= false;
					ai_think= false;
				};
				break;
			case 16 :
				column++;
				if(OutOfBounds()) {
					ai_strategy= 0;
				} else if(!H && !change_case) {
					ai_strategy= 0; //miss
				} else if(H && !change_case) {
					ai_think= false; //hit
				} else {
					change_case= false;
					ai_think= false;
				};
				break;
			default:
				ai_strategy= 0;
				change_case= false;
				break;
		};
	};
	DeleteChosenSchemaCell();
}
void Player::RandCoords() {
	int temp_int;
	int r;
	int c;

	if(row < 0 || row > 9) row= 0;

	temp_int= int(rand()) % schema.size();
	r= temp_int;

	temp_int= int(rand()) % schema[r].size();
	c= temp_int;

	row= schema[r][c][0];
	column= char(schema[r][c][1] + 'A');
}
void Player::DeleteChosenSchemaCell() {
	bool abort= false;
	int r= 0;
	int c= 0;

	//Once shot is chosen, find shot in schema and delete
	while(!abort) {
		if(row == schema[r][c][0] && CharToInt(column) == schema[r][c][1]) {
			abort= true;
			schema[r][c].erase(schema[r][c].begin());
			schema[r][c].erase(schema[r][c].begin());
			schema[r].erase(schema[r].begin() + c);

			DeleteEmptyRows();
		};
		c+= 1;
		if(c >= schema[r].size()) {
			c= 0;
			r+= 1;
//			if(r >= schema.size()) abort= true;
		};
		if(r >= schema.size()) abort= true;
	};
}
void Player::DeleteEmptyRows() {
	for(int i(0); i < schema.size(); i++) {
		if(schema[i].size() == 0) {
			schema.erase(schema.begin() + i);
		};
	};
}
void Player::SetRandomShipPlacement() {
	vector<vector<vector<int>>> ship_schema;
	ship_schema.resize(10, vector<vector<int>>(10, vector<int>(2, 0)));

	for(int i(0); i < 10; i++) {
		for(int j(0); j < 10; j++) {
			ship_schema[i][j][0]= i;
			ship_schema[i][j][1]= j;
		};
	};
}
bool Player::OutOfBounds() {
	if(row < 0 || row > 9) {
		return true;
	} else if(column < 'A' || column > 'J') {
		return true;
	} else if(GetMyShot(row, CharToInt(column)) != 0) {
		return true;
	} else return false;
}
#endif
