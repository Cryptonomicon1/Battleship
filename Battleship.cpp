#include<iostream>
using std::cout;
using std::cin;
using std::endl;

#include<cstdlib>
using std::rand;
using std::srand;

#include<vector>
using std::vector;

#include<string>
using std::string;

#include "Board.h"
#include "Player.h"
#include "Output.h"
#include "Input.h"
#include "Game.h"

int main() {
	srand(time(NULL));

	static const int board_width= 10;
	static const int board_height= 10;

	bool play_flag(true);
	int count(0);

	Player* players[2];
	for(int x(0); x < 2; x++) {
		players[x]= new Player(!bool(x));
	};
	Output Out(players[0], players[1]);
	Input In;
	Game G;

	Out.Update(play_flag);
	In.Fetch(play_flag);

	while(play_flag) {

		players[0]->LoadInput(&In);
		players[1]->SetHit(players[0]->GetHit(players[1]->GetRow(), players[1]->GetColumn()), players[1]->GetRow(), players[1]->GetColumn());
		play_flag= G.Victory(players[0]->GetHits(), players[1]->GetHits());

		if(!players[1]->GetHuman() && players[1]->GetHits() < 17) {
			players[1]->AIAttack(players[0]->GetHit(players[1]->GetRow(), players[1]->GetColumn()));
		};
		players[0]->SetHit(players[1]->GetHit(players[0]->GetRow(), players[0]->GetColumn()), players[0]->GetRow(), players[0]->GetColumn());
		play_flag= G.Victory(players[0]->GetHits(), players[1]->GetHits());

		Out.Update(play_flag);
		In.Fetch(play_flag);
	};
}
