#include "Player.h"

#ifndef OUTPUT_H
#define OUTPUT_H

class Output {
public:
	//Constructor
	Output(Player*, Player*);

	//Destructor
	~Output();

	//Variables

	//Functions
	void Update(bool);
private:
	//Variables
	static const int width= 10;
	static const int height= 10;

	int ship_layout[width][height];
	int ai_shots[width][height];
	int human_shots[width][height];

	Player* human_player;
	Player* ai_player;

	//Functions
	void Load();
	void PrintHumanShots();
	void PrintShipsAndShots();
};
Output::Output(Player* hum_ptr, Player* ai_ptr) {
	human_player= hum_ptr;
	ai_player= ai_ptr;

	for(int x(0); x < width; x++) {
		for(int y(0); y < height; y++) {
			ship_layout[x][y]= 0;
			ai_shots[x][y]= 0;
			human_shots[x][y]= 0;
		};
	};
}
Output::~Output() {}

void Output::Update(bool play) {
	if(play) {
		system("tput reset");
		Load();
		PrintHumanShots();
		PrintShipsAndShots();
	};
}
void Output::Load() {
	for(int x(0); x < width; x++) {
		for(int y(0); y < height; y++) {
			ship_layout[x][y]= human_player->GetPlacement('s', x, y);
			ai_shots[x][y]= human_player->GetPlacement('e', x, y);
			human_shots[x][y]= human_player->GetPlacement('m', x, y);
		};
	};
}
void Output::PrintHumanShots() {
	cout << "   ";
	for(int x(0); x < width; x++) {
		cout << char(x + 'A') << " ";
	};
	for(int x(0); x < width; x++) {
		cout << "\n" << x + 1;
		if(x + 1 != 10) {
			cout << "  ";
		} else cout << " ";
		for(int y(0); y < height; y++) {
			int shot= human_shots[x][y];

			if(shot == 1) {
				cout << 'M' << " ";
			} else if(shot == 2) {
				cout << 'H' << " ";
			} else cout << '~' << " ";
		};
	};
	cout << endl;
	cout << "Your Last Shot: " << human_player->GetColumn() << " " << human_player->GetRow() + 1;
	cout << endl << endl;
}
void Output::PrintShipsAndShots() {
	cout << "   ";
	for(int x(0); x < width; x++) {
		cout << char(x + 'A') << " ";
	};
	for(int x(0); x < height; x++) {
		cout << "\n" << x + 1;
		if(x+1 != 10) {
			cout << "  ";
		} else cout << " ";

		for(int y(0); y < width; y++) {
			int ship_shot= ship_layout[x][y];
			int shot= ai_shots[x][y];
			if(shot == 1) {
				ship_shot= 6;
			}else if(shot == 2) ship_shot= 7;

			if(ship_shot == 0) {
				cout << "~" << " ";
			}else if(ship_shot == 1) {
				cout << "P" << " ";
			}else if(ship_shot == 2) {
				cout << "S" << " ";
			}else if(ship_shot == 3) {
				cout << "D" << " ";
			}else if(ship_shot == 4) {
				cout << "B" << " ";
			}else if(ship_shot == 5) {
				cout << "C" << " ";
			}else if(ship_shot == 6) {
				cout << "M" << " ";
			}else if(ship_shot == 7) {
				cout << "H" << " ";
			}else cout << "~" << " ";
		};
	};
	cout << endl;
	cout << "Computer's Next Shot: " << ai_player->GetColumn() << " " << ai_player->GetRow() + 1;
	cout << endl << endl;
}
#endif
