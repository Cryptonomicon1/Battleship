#ifndef INPUT_H
#define INPUT_H

class Input {
public:
	//Constructor
	Input();

	//Destructor
	~Input();

	//Functions
	void Fetch(bool);
	char get_column();
	int get_row();

private:
	//Variables
	int row;
	char column;

	//Functions
};
Input::Input() {}

Input::~Input() {}

void Input::Fetch(bool play) {
	if(play) {
		bool repeat_input(true);

		while(repeat_input) {
			cout << "Shot column: ";
			cin >> column;
			cout << endl;

			if(column >= 'A' && column <= 'Z' || column >= 'a' && column <='z') {
				repeat_input= false;
			};
			if(repeat_input == true || cin.fail()) {
				cin.clear();
			};
		};
		repeat_input= true;

		while(repeat_input) {
			cout << "Shot row: ";
			cin >> row;
			cout << endl;
			row-= 1;

			if(row >= 0 && row <= 9 && !cin.fail()) {
				repeat_input= false;
			} else cin.clear();
		};
	};
} /*
void Input::Fetch() {
	row= 3;
	column= 'E';
} */
char Input::get_column() {
	return column;
}
int Input::get_row() {
	return row;
}
#endif
