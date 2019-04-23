//Jingwen Du
//jd3597
//lab 3 to creat minesweeper 

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
using namespace std;


struct cell {
	cell(bool&_property, bool&_chosen, int count)
		: bomb(_property), chosen(_chosen), count(count) {}
	bool bomb = false;
	bool chosen = false;
	int count;

};

class Minesweeper {
public:
	Minesweeper() :cols(10), rows(10) {
		for (int r = 0;r < rows; r++) {
			vector<cell> aRow;
			for (int c = 0;c < cols; c++) {
				bool property = false;
				bool chosen = false;
				int count = 0;
				if (rand() % 100 < 10) {
					property = true;
				}
				cell aCell(property, chosen, count);
				aRow.push_back(aCell);


			}
			world.push_back(aRow);
		}
		setInitial();
	};

	//count the bombs around each cell
	bool validRow(int row) {

		if (row < 0 || row >world.size() - 1) {
			return false;
		}
		return true;
	}
	bool validCol(int col) {
		if (col < 0 || col>world.size() - 1) {
			return false;
		}
		return true;
	}
	void display(const bool&showBomb) {
		if (showBomb == true) {
			for (size_t r = 0;r < world.size();r++) {
				for (size_t c = 0;c < world[0].size();c++) {
					if (world[r][c].bomb == true) {
						cout << '*';
					}
					
					else { cout << world[r][c].count; }
				}
				cout << endl;
			}
		}
		else {
			for (size_t r = 0;r < world.size();r++) {
				for (size_t c = 0;c < world[0].size();c++) {
					if (world[r][c].chosen) {
						cout << world[r][c].count;
					}
					else { cout << '#'; }
				}
				cout << endl;
			}

		}
		
	}
	//to count the number of neighbour bombs 
	void setInitial() {
		for (size_t r = 0;r < world.size();r++) {
			for (size_t c = 0;c < world[0].size();c++) {
				bool valid = true;
				int count = 0;
				if (validRow(r - 1)) {

					if (world[r - 1][c].bomb) {
						count += 1;
					}
					if (validCol(c - 1)) {

						if (world[r - 1][c - 1].bomb) {
							count += 1;
						}
					}
					if (validCol(c + 1)) {
						if (world[r - 1][c + 1].bomb) {
							count += 1;
						}
					}
				}
				if (validRow(r + 1)) {

					if (world[r + 1][c].bomb) {
						count += 1;
					}
					if (validCol(c - 1)) {
						if (world[r + 1][c - 1].bomb) {
							count += 1;
						}
					}
					if (validCol(c + 1)) {
						if (world[r + 1][c + 1].bomb) {
							count += 1;
						}
					}
				}

				if (validCol(c + 1)) {

					if (world[r][c + 1].bomb) {
						count += 1;
					}
				}

				if (validCol(c - 1)) {
					if (world[r][c - 1].bomb) {
						count += 1;
					}
				}
				world[r][c].count = count;
			}
		}
	}
	bool play(int rn, int cn) {
		if (validRow(rn) && validCol(cn)) {
			if (world[rn][cn].count == 0) {
				world[rn][cn].chosen = true;
				searchSround(rn, cn);
			}
			if (!world[rn][cn].bomb) {
				world[rn][cn].chosen = true;
			}
			else {
				cout << "explosion" << endl;
				world[rn][cn].chosen = true;
				return false;
			}
		}
		return true;
	}


	void searchSround(int rn, int cn) {
		if (validRow(rn - 1)) {
			if (world[rn - 1][cn].chosen == false) {
				play(rn - 1, cn);
			}
			if (validCol(cn - 1)) {
				if (world[rn - 1][cn - 1].chosen == false) {
					play(rn - 1, cn - 1);
				}
			}
			if (validCol(cn + 1)) {
				if (world[rn - 1][cn + 1].chosen == false) {
					play(rn - 1, cn + 1);
				}
			}
		}
		if (validRow(rn + 1)) {
			if (world[rn + 1][cn].chosen == false) {
				play(rn + 1, cn);
			}
			if (validCol(cn - 1)) {
				if (world[rn + 1][cn - 1].chosen == false) {
					play(rn + 1, cn - 1);
				}
			}
			if (validCol(cn + 1)) {
				if (world[rn + 1][cn + 1].chosen == false) {
					play(rn + 1, cn + 1);
				}
			}
		}
		if (validCol(cn + 1)) {
			if (world[rn][cn + 1].chosen == false) {
				play(rn, cn + 1);
			}
		}

		if (validCol(cn - 1)) {
			if (world[rn][cn - 1].chosen == false) {
				play(rn, cn - 1);
			}
		}
	}


	bool isVisible(int rn, int cn) {
		if (world[rn][cn].chosen == true) {
			return true;
		}
		return false;
	}
	bool done() {
		for (size_t rn = 0;rn < world.size();rn++) {
			for (size_t cn = 0; cn < world[0].size();cn++) {
				if (world[rn][cn].bomb==false && world[rn][cn].chosen == false) {
					cout << "rn" << rn+1 << endl;
					cout << "cn" << cn+1 << endl;
					return false;
				}
			}
		}
		return true;
	}
private:
	int cols;
	int rows;
	vector<vector<cell>> world;
	};

	int main() {
		Minesweeper sweeper;
		// Continue until the only invisible cells are bombs
		while (!sweeper.done()) {
			sweeper.display(false); // display the board without bombs
			int row_sel = -1, col_sel = -1;
			while (row_sel == -1) {
				// Get a valid move
				int r, c;
				cout << "row? ";
				cin >> r;
				if (!sweeper.validRow(r-1)) {
					cout << "Row out of bounds\n";
					continue;
				}
				cout << "col? ";
				cin >> c;
				if (!sweeper.validCol(c-1)) {
					cout << "Column out of bounds\n";
					continue;
				}
				if (sweeper.isVisible(r-1, c-1)) {
					cout << "Square already visible\n";
					continue;
				}
				row_sel = r-1;
				col_sel = c-1;
			}
			// Set selected square to be visible. May effect other cells.
			if (!sweeper.play(row_sel, col_sel)) {
				cout << "BOOM!!!\n";
				sweeper.display(true); 
				
				// We're done! Should consider ending more "cleanly",
				// eg. Ask user to play another game.
				exit(0);
			
			}
		}

		// Ah! All invisible cells are bombs, so you won!
		cout << "You won!!!!\n";
		sweeper.display(true); // Final board with bombs shown
	}

