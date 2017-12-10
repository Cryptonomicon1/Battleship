#ifndef GAME_H
#define GAME_H
class Game {
public:
	//Constructor
	Game();

	//Destructor
	~Game();

	//Functions
	bool Victory(int, int);
};
Game::Game() {}

Game::~Game() {}

bool Game::Victory(int human_hits, int computer_hits) {
	int victory_points= 17;

	if(human_hits >= victory_points && computer_hits >= victory_points) {
		cout << "Tie Game!" << endl << endl;
		return false;
	} else if(human_hits >= victory_points) {
		cout << "You Win!" << endl << endl;
		return false;
	} else if(computer_hits >= victory_points) {
		cout << "You Lose!" << endl << endl;
		return false;
	} else return true;
}
#endif
