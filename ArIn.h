#ifndef ARIN_H
#define ARIN_H

class ArIn {
protected:
	//Constructor
	ArIn();

	//Destructor
	~ArIn();

	//Variables

	//Functions
	void RandomShip(char);
	int GetSchemaRow(int, int);
	int GetSchemaCol(int, int);
	int GetLayout(int, int);

private:
	//Variables
	vector<vector<vector<int>>> schema2;
	vector<vector<int>> layout;

	//Functions
	void InitSchema();
	void InitLayout();
	bool RandomBool();
	int ShipLength(char);
	void SchemaAmnesia(bool, int);
	void DeleteCells(vector<vector<int>>);
	void SetRandomShip(bool, char, int);
	int ShipCharToInt(char);
};
ArIn::ArIn() {
	layout.resize(10, vector<int>(10, 0));
	InitLayout();
	InitSchema();
}
ArIn::~ArIn() {
}
void ArIn::RandomShip(char ship) {
	bool vert= RandomBool(); //Is the ship verticle or horizontal?
	int ship_length= 0;
	int ship_int= 0;

	InitSchema();
	ship_length= ShipLength(ship);
	SchemaAmnesia(vert, ship_length);
	SetRandomShip(vert, ship, ship_length);
}
int ArIn::GetSchemaRow(int r, int c) {
	return schema2[r][c][0];
}
int ArIn::GetSchemaCol(int r, int c) {
	return schema2[r][c][1];
}
int ArIn::GetLayout(int r, int c) {
	return layout[r][c];
}
void ArIn::InitSchema() {
	schema2.resize(0);
	schema2.resize(10, vector<vector<int>>(10, vector<int>(2, 0)));

	for(int i(0); i < 10; i++) {
		for(int j(0); j < 10; j++) {
			schema2[i][j][0]= i;
			schema2[i][j][1]= j;
		};
	};
}
void ArIn::InitLayout() {
	for(int i(0); i < 10; i++) {
		for(int j(0); j < 10; j++) {
			layout[i][j]= 0;
		};
	};
}
bool ArIn::RandomBool() {
	return bool(rand() % 2);
}
int ArIn::ShipLength(char ship) {
	switch(ship) {
		case 'P' :
			return 2;
			break;
		case 'p' :
			return 2;
			break;
		case 'S' :
			return 3;
			break;
		case 's' :
			return 3;
			break;
		case 'D' :
			return 3;
			break;
		case 'd' :
			return 3;
			break;
		case 'B' :
			return 4;
			break;
		case 'b' :
			return 4;
			break;
		case 'C' :
			return 5;
	 		break;
		case 'c' :
			return 5;
			break;
		default :
			return 0;
	}
}
void ArIn::SchemaAmnesia(bool vert, int ship_length) {
	vector<vector<int>> delete_list;

	for(int r(0); r < 10; r++) {
		for(int c(0); c < 10; c++) {
			if((layout[r][c] != 0) && vert) {
				if(ship_length <= r) {
					delete_list.resize(ship_length, vector<int>(2, c));
				} else {
					delete_list.resize(r+1, vector<int>(2, c));
				};
				for(int i(0); i < delete_list.size(); i++) {
					delete_list[i][0]= r-i;
				};
				DeleteCells(delete_list);
				delete_list.resize(0);

			} else if(layout[r][c] != 0) {
				if(ship_length <= c) {
					delete_list.resize(ship_length, vector<int>(2, r));
				} else {
					delete_list.resize(c+1, vector<int>(2, r));
				};
				for(int i(0); i < delete_list.size(); i++) {
					delete_list[i][1]= c-i;
				};
				DeleteCells(delete_list);
				delete_list.resize(0);
			};
		};
	};
	delete_list.resize(0);

	//Chop off end of schema matrix
	if(vert) {
		for(int r(9); r > (10 - ship_length); r--) {
			for(int c(0); c < 10; c++) {
				delete_list.push_back(vector<int>(2, r));
				delete_list[delete_list.size() - 1][1]= c;
			};
		};
		DeleteCells(delete_list);
	} else {
		for(int r(0); r < 10; r++) {
			for(int c(9); c > (10 - ship_length); c--) {
				delete_list.push_back(vector<int>(2, r));
				delete_list[delete_list.size() - 1][1]= c;
			};
		};
		DeleteCells(delete_list);
	};
}
void ArIn::DeleteCells(vector<vector<int>> del_list) {
	for(int r(0); r < schema2.size(); r++) {
		for(int c(0); c < schema2[r].size(); c++) {
			for(int i(0); i < del_list.size(); i++) {
				if(del_list[i][0] == schema2[r][c][0] && del_list[i][1] == schema2[r][c][1]) {
					schema2[r][c].erase(schema2[r][c].begin());
					schema2[r][c].erase(schema2[r][c].begin());
					schema2[r].erase(schema2[r].begin() + c);
					c--;
					i= del_list.size();
				};
			};
		};
	};
    for(int i(0); i < schema2.size(); i++) {
        if(schema2[i].size() == 0) {
            schema2.erase(schema2.begin() + i);
			i--;
        };
    };
}
void ArIn::SetRandomShip(bool vert, char ship, int ship_length) {
	int layout_row(0);
	int layout_col(0);
	int schema_row(0);
	int schema_col(0);

	schema_row= rand() % schema2.size();
	schema_col= rand() % schema2[schema_row].size();

	layout_row= schema2[schema_row][schema_col][0];
	layout_col= schema2[schema_row][schema_col][1];

	if(vert) {
		for(int i(0); i < ship_length; i++) {
			layout[layout_row + i][layout_col]= ShipCharToInt(ship);
		};
	} else {
		for(int i(0); i < ship_length; i++) {
			layout[layout_row][layout_col + i]= ShipCharToInt(ship);
		};
	};
}
int ArIn::ShipCharToInt(char ship) {
	switch(ship) {
		case 'P' :
			return 1;
			break;
		case 'p' :
			return 1;
			break;
		case 'S' :
			return 2;
			break;
		case 's' :
			return 2;
			break;
		case 'D' :
			return 3;
			break;
		case 'd' :
			return 3;
			break;
		case 'B' :
			return 4;
			break;
		case 'b' :
			return 4;
			break;
		case 'C' :
			return 5;
			break;
		case 'c' :
			return 5;
			break;
	}
}
#endif
