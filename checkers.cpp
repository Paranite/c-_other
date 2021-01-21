#include <iostream>
#include <windows.h>
#include <vector>
#include <string>

using namespace std;

const char SYM_P1 = 'O';
const char SYM_P1_k = 'Q';
const char SYM_P2 = 'X';
const char SYM_P2_k = 'q';

/*
The different color codes are

0   BLACK
1   BLUE
2   GREEN
3   CYAN
4   RED
5   MAGENTA
6   BROWN
7   LIGHTGRAY
8   DARKGRAY
9   LIGHTBLUE
10  LIGHTGREEN
11  LIGHTCYAN
12  LIGHTRED
13  LIGHTMAGENTA
14  YELLOW
15  WHITE
*/

class Checker {
private:
	int x, y;
	char symbol;
	bool reached_end = false;
public:
	Checker() {}
	Checker(int x, int y, char symbol) {
		this->x = x;
		this->y = y;
		this->symbol = symbol;
	}
	void setX(int x) {
		this->x = x;
	}
	void setY(int y) {
		this->y = y;
	}
	void setSymbol(char symbol) {
		this->symbol = symbol;
	}
	void setReached(bool reached) {
		reached_end = reached;
	}
	int getX() {
		return x;
	}
	int getY() {
		return y;
	}
	char getSymbol() {
		return symbol;
	}
	bool getReached() {
		return reached_end;
	}
};

class Board {
private:
	char field[8][8];
	vector<Checker> player1_checkers;
	vector<Checker> player2_checkers;
	string winner = "";
public:
	Board() {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				field[i][j] = ' ';
			}
		}

		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 8; j++) {
				if ((i + 1) % 2 != 0 && (j + 1) % 2 == 0 || (i + 1) % 2 == 0 && (j + 1) % 2 != 0) {
					Checker newC = Checker(j, i, SYM_P2);
					player2_checkers.push_back(newC);
					field[i][j] = SYM_P2;
				}
			}
		}
		for (int i = 5; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if ((i + 1) % 2 != 0 && (j + 1) % 2 == 0 || (i + 1) % 2 == 0 && (j + 1) % 2 != 0) {
					Checker newC = Checker(j, i, SYM_P1);
					player1_checkers.push_back(newC);
					field[i][j] = SYM_P1; 
				}
			}
		}

		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				field[i][j] = ' ';
			}
		}
		field[player1_checkers.at(0).getY()][player1_checkers.at(0).getX()] = SYM_P1;
		field[player2_checkers.at(0).getY()][player2_checkers.at(0).getX()] = SYM_P2;
		player1_checkers.erase(player1_checkers.begin() + 1, player1_checkers.end());
		player2_checkers.erase(player2_checkers.begin() + 1, player2_checkers.end());

		player1_checkers.at(0).setReached(true);
	}
	void draw() {
		system("CLS");
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);	//reikalinga spalvoms nustatyti
		SetConsoleTextAttribute(hConsole, 4 + 0 * 16);
		cout << "  01234567\n\n";
		bool printed = false;
		for (int i = 0; i < 8; i++) {
			cout << i << " ";
			for (int j = 0; j < 8; j ++) {
				if ((i + 1) % 2 != 0 && (j + 1) % 2 == 0 || (i + 1) % 2 == 0 && (j + 1) % 2 != 0) SetConsoleTextAttribute(hConsole, 4 + 15 * 16);
				/*if (field[i][j] == SYM_P1) {
					cout << SYM_P1;
				}
				else if (field[i][j] == SYM_P2) {
					cout << SYM_P2;
				}
				else {
					cout << field[i][j];
				}*/
				for (Checker c : player1_checkers) {
					if (c.getX() == j && c.getY() == i) {
						if (c.getReached()) {
							cout << SYM_P1_k;
						}
						else {
							cout << SYM_P1;
						}
						printed = true;
					}
				}
				for (Checker c : player2_checkers) {
					if (c.getX() == j && c.getY() == i) {
						if (c.getReached()) {
							cout << SYM_P2_k;
						}
						else {
							cout << SYM_P2;
						}
						printed = true;
					}
				}
				if (!printed) cout << field[i][j];
				printed = false;

				SetConsoleTextAttribute(hConsole, 4 + 0 * 16);
			}
			cout << endl;
		}
	}

	string getWinner() {
		return winner;
	}

	void checkWinner() {
		if (player1_checkers.size() == 0) winner = "Player2";
		if (player2_checkers.size() == 0) winner = "Player1";
	}
	
	bool checkerExists(int x, int y, bool p1) {
		if (p1) {
			for (Checker c : player1_checkers) {
				if (c.getX() == x && c.getY() == y) {
					return  true;
				}
			}
		}
		else {
			for (Checker c : player2_checkers) {
				if (c.getX() == x && c.getY() == y) {
					return  true;
				}
			}
		}
		return false;
	}

	void removeChecker(int x, int y, bool p1) {
		field[y][x] = ' ';
		if (p1) {
			for (int i = 0; i < player2_checkers.size(); i++) {
				if (player2_checkers.at(i).getX() == x && player2_checkers.at(i).getY() == y) {
					player2_checkers.erase(player2_checkers.begin() + i);
				}
			}
		}
		else {
			for (int i = 0; i < player1_checkers.size(); i++) {
				if (player1_checkers.at(i).getX() == x && player1_checkers.at(i).getY() == y) {
					player1_checkers.erase(player1_checkers.begin() + i);
				}
			}
		}
	}

	void cross(int x, int y, int mx, int my, int cx, int cy, bool p1, bool end_reached) {
		move(x, y, mx, my, p1); // pajudinemae musu saske
		removeChecker(cx, cy, p1); // pasaliname prieso saske
		checkWinner(); // paziurime ar yra laimetojas
		bool cross_possible = checkEnemyCross(mx, my, p1, end_reached); // patikriname ar galime toliau kirsti
		cout << cross_possible << endl;
		if (cross_possible) { // jei galima kirsti toliau
			draw(); //is naujo perpiesiame konsole
			Re_enter: //taskas i kuri grizti jei blogai iveda x, y
			cout << "Galimas tolimesnis kirtimas - iveskite x ir y" << endl;
			cin >> x >> y;
			if (!canMove(mx, my, x, y, p1, true)) {
				cout<<"Negalimas judesys"<<endl;
				goto Re_enter;
			}
		}
	}

	bool checkEnemyCross(int x, int y, bool p1, bool end_reached) {
		if (!end_reached) { // jei saske nebuvo pasiekusi pabaigos
			if (p1) { // patikrinama ar tai pirmas zaidimas
				if ((field[y - 1][x - 1] == SYM_P2 && y-2 > -1 && x-2 > -1 && field[y - 2][x - 2] == ' ') || (field[y - 1][x + 1] == SYM_P2 && y-2 > -1 && x+2 < 8 && field[y - 2][x + 2] == ' ') || (field[y + 1][x - 1] == SYM_P2 && y+2 < 8 && x-2 > -1 && field[y + 2][x - 2] == ' ') || (field[y + 1][x + 1] == SYM_P2 && y+2 < 8 && x+2 < 8 && field[y + 2][x + 2] == ' ')) { // ziurima ar saske gali/turi ka kirsti i apacia-kaire, apacia-desine, virsu-kaire ir virsu-desine
					return true; // jei gali returnina true
				}
			}
			else { // jei p1 == false vykdomas sis:
				if ((field[y - 1][x - 1] == SYM_P1 && y-2 > -1 && x-2 > -1 && field[y - 2][x - 2] == ' ') || (field[y - 1][x + 1] == SYM_P1 && y-2 > -1 && x+2 < 8 && field[y - 2][x + 2] == ' ') || (field[y + 1][x - 1] == SYM_P1 && y+2 < 8 && x-2 > -1 && field[y + 2][x - 2] == ' ') || (field[y + 1][x + 1] == SYM_P1 && y+2 < 8 && x+2 < 8 && field[y + 2][x + 2] == ' ')) { // ziurima ar saske gali/turi ka kirsti i apacia-kaire, apacia-desine, virsu-kaire ir virsu-desine
					return true; //jei gali returnina true
				}
			}
		}
		else { // jei saske buvo pasiekusi pabaiga
			int tempX = x + 1;
			int tempY = y + 1;
			while(tempX < 7 && tempY < 7 ){ // tikrinsim istrizai apacia-desine kol maziau nei paskutinis langelis x ar y asyje (paskutinio nenorim tikrinti nes paskui tikrinama ar jis laisvas ar ne - jei nelaisvas, kirtimas negalimas)
				if ((p1 && field[tempY][tempX] == SYM_P2) || (!p1 && field[tempY][tempX] == SYM_P1)) { // ieskome pirmos saskes, kuri priklausytu kitam zaidejui (jei player1, tai iesko player2 saskes)
					if (field[tempY + 1][tempX + 1] == ' ') { // jei saske randama, ziurima ar uz jos istrizai yra tuscias langelis
						return true; // jei tuscias, grazinama true - kirtimas galimas
					}
					break; // jei ne- break; iseiname is ciklo
				}
				tempX++;
				tempY++;
			}
			tempX = x - 1;
			tempY = y + 1;
			while (tempX > 0 && tempY < 7) { // tikrinsim istrizai apacia-kaire
				if ((p1 && field[tempY][tempX] == SYM_P2) || (!p1 && field[tempY][tempX] == SYM_P1)) {
					if (field[tempY + 1][tempX - 1] == ' ') {
						return true;
					}
					break;
				}
				tempX--;
				tempY++;
			}
			tempX = x + 1;
			tempY = y - 1;
			while (tempX < 7 && tempY > 0){ // tikrinsim istrizai virsu-desine
				if ((p1 && field[tempY][tempX] == SYM_P2) || (!p1 && field[tempY][tempX] == SYM_P1)) {
					if (field[tempY - 1][tempX + 1] == ' ') {
						return true;
					}
					break;
				}
				tempX++;
				tempY--;
			}
			tempX = x - 1;
			tempY = y - 1;
			while (tempX > 0 && tempY > 0) { // tikrinsim istrizai virsu-kaire
				if ((p1 && field[tempY][tempX] == SYM_P2) || (!p1 && field[tempY][tempX] == SYM_P1)) {
					if (field[tempY - 1][tempX - 1] == ' ') {
						return true;
					}
					break;
				}
				tempX--;
				tempY--;
			}
		}
		return false;
	}

	void move(int x, int y, int mx, int my, bool p1) {
		field[y][x] = ' '; // dabartines saskes vietoje padarome tarpa - nutriname SYM_P1, nes dabar bus tuscias laukelis
		char symbol;
		if (p1) { // jei tai pirmas zaidejas
			for (int i = 0; i < player1_checkers.size(); i++) { // einame per jo saskes
				if (player1_checkers.at(i).getX() == x && player1_checkers.at(i).getY() == y) { // jei randame saske pagal x ir y
					player1_checkers.at(i).setX(mx); // nustatome nauja x
					player1_checkers.at(i).setY(my); // nustatome nauja y
					if (my == 0) { // jei pasiekia gala
						player1_checkers.at(i).setReached(true); // nustatome, kad end_reached = true
					} 
					symbol = player1_checkers.at(i).getSymbol(); // gauname saskes simboli
					break; // iseiname is ciklo
				}
			}
			field[my][mx] = symbol; //pozicijoje, i kuria saske paejo, irasomas saskes simbolis - kad vaizduotu pirmo zaidejo saske
		}
		else { // jei tai antras zaidejas
			for (int i = 0; i < player2_checkers.size(); i++) { // einame per jo saskes
				if (player2_checkers.at(i).getX() == x && player2_checkers.at(i).getY() == y) { // jei randame saske pagal x ir y
					player2_checkers.at(i).setX(mx); // nustatome nauja x
					player2_checkers.at(i).setY(my); // nustatome nauja y
					if (my == 7) { // jei pasiekia gala
						player2_checkers.at(i).setReached(true); // nustatome, kad end_reached = true
					}
					symbol = player2_checkers.at(i).getSymbol(); // gauname saskes simboli
					break; // iseiname is ciklo
				}
			}
			field[my][mx] = symbol; //pozicijoje, i kuria saske paejo, irasomas saskes simbolis - kad vaizduotu pirmo zaidejo saske
		}
	}

	bool canMove(int x, int y, int mx, int my, bool p1, bool crossing) {
		if (mx < 0 || mx > 7 || my < 0 || my > 7) return false; // neleidziame iseiti is ribu
		if (field[my][mx] == SYM_P1 || field[my][mx] == SYM_P2) return false; // tikriname yra saske langelyje, i kuri norime eiti - jei yra, tai neleistinas judesys

		bool end_reached; // saugosime ar saske buvo pasiekusi gala
		int cx, cy; // saugosime saskes, kuria ruosiames nukirsti x ir y

		if (p1) { // jei tai pirmas zaidejas

			for (Checker c : player1_checkers) {  // pereiname pirmo zaidejo saskes ir ir isirasome ar dabartine saske buvo pasiekusi gala
				if (c.getX() == x && c.getY() == y) {
					end_reached = c.getReached();
					break;
				}
			}
			if (!end_reached) { // jei galo nebuvo pasiekusi saske
				if ((my == y - 2 && mx == x - 2) || (my == y - 2 && mx == x + 2) || (my == y + 2 && mx == x + 2) || (my == y + 2 && mx == x - 2)) { // tikrinama ar saske bando pajudinti per 2 langelius isitrizai i virsu-kaire ar virsu-desine. Jei vykdomas kirtimas ziurima dar ar bando judeti i apacia-kaire ar apacia-desine, nes kirtimo metu tai galima
					//if (field[y - 1][x - 1] == SYM_P2 || field[y - 1][x + 1] == SYM_P2) {
						cy = y - (y - my) / abs(y - my);   // nustatome y, kur turi buti prieso saske
						cx = x - (x - mx) / abs(x - mx); // nustatome x, kur turi buti prieso saske
					if(field[cy][cx] == SYM_P2) { // tikriname ar vietoje, kuria norima kirsti yra prieso saske
						cross(x, y, mx, my, cx, cy, p1, end_reached); // atliekame kirtima
						return true;
					}
				}
				if ((my != y - 1 && mx != x - 1) || (my != y - 1 && mx != x + 1)) return false; // uztikrina kad saske gali judeti tik i virsu-desine ir virsu-kaire
			}
		}
		else {
			for (Checker c : player2_checkers) { // pereiname antro zaidejo saskes ir ir isirasome ar dabartine saske buvo pasiekusi gala
				if (c.getX() == x && c.getY() == y) {
					end_reached = c.getReached();
					break;
				}
			}

			if (!end_reached) { // jei galo nebuvo pasiekusi saske
				if ((my == y + 2 && mx == x - 2) || (my == y + 2 && mx == x + 2) || (my == y - 2 && mx == x + 2) || (my == y - 2 && mx == x - 2)) { // tikrinama ar saske bando pajudinti per 2 langelius isitrizai i apacia-kaire ar apacia-desine. Jei vykdomas kirtimas ziurima dar ar bando judeti i virsu-kaire ar virsu-desine, nes kirtimo metu tai galima
					//if (field[y + 1][x - 1] == SYM_P1 || field[y + 1][x + 1] == SYM_P1) {
						cy = y - (y - my) / abs(y - my); // nustatome y, kur turi buti prieso saske
						cx = x - (x - mx) / abs(x - mx); // nustatome x, kur turi buti prieso saske
					if(field[cy][cx] == SYM_P1){ // tikriname ar vietoje, kuria norima kirsti yra prieso saske
						cross(x, y, mx, my, cx, cy, p1, end_reached); // atliekame kirtima
						return true;
					}
				}
				if ((my != y + 1 && mx != x - 1) || (my != y + 1 && mx != x + 1)) return false; // uztikrina kad saske gali judeti tik i apacia-desine ir apacia-kaire
			}
		}

		if (end_reached) {
			int x_diff = x - mx; // gaunamas skirtumas tarp pradines saskes ir ten kur ji judes x koordinateje
			int y_diff = y - my; // gaunamas skirtumas tarp pradines saskes ir ten kur ji judes y koordinateje
			if (abs(x_diff) != abs(y_diff)) return false; // jei x ir y skirtumus, pavertus i teigiamus sk, jie nera lygus, salyga netinka nes neistrizai eina saskes
			x_diff /= abs(x_diff); // padaliname x skirtuma is teigiamo x skirtumo, kad gautume arba 1 arba -1
			y_diff /= abs(y_diff); // padaliname x skirtuma is teigiamo y skirtumo, kad gautume arba 1 arba -1
			bool on_checker = false; // naudosime patikrinti ar jau buvo praeita bent viena saske
			for (int i = 0; i < abs(x - mx) - 1; i++) { // einame (x-mx (galima ir y-my) - 1) kartu istrizai. -1 nes paskutines vietos nereikia tikrinti nes tikrinamas atliekamas pries tai
				int current_x_diff = x_diff + (x_diff * i); // kadangi x_diff turi kisti (dideti arba mazeti), kad skaiciavimas nebutu atliekamas toje pacioje vietoje naudojame sia formule
				int current_y_diff = y_diff + (y_diff * i); // kadangi y_diff turi kisti (dideti arba mazeti), kad skaiciavimas nebutu atliekamas toje pacioje vietoje naudojame sia formule
				if (p1 && field[y - current_y_diff][x - current_x_diff] == SYM_P1) return false; // patikriname ar player1 nebando pereiti savo saskes, jei bando tai negalimas judesys
				if (!p1 && field[y - current_y_diff][x - current_x_diff] == SYM_P2) return false; // patikriname ar player2 nebando pereiti savo saskes, jei bando tai negalimas judesys
				if (field[y - current_y_diff][x - current_x_diff] == SYM_P1 || field[y - current_y_diff][x - current_x_diff] == SYM_P2) { // toliau tiesiog tikriname ar atsistojame ant kokios nors saskes
					if (on_checker) return false; // patikriname ar pries tai buvome atsistoje/praeje kokia saske. Jei taip - tai negalimas judesys
					on_checker = true; // padarome on_checker true
					cx = x - current_x_diff; // issaugome saskes, kuria kirsime x koordinate
					cy = y - current_y_diff; // issaugome saskes, kuria kirsime y koordinate
				}
			}
			if (on_checker) { // jei buvo saske
				cross(x, y, mx, my, cx, cy, p1, end_reached); // atliekamas kirtimas
				return true;
			}
		}

		if (crossing) return false; // jei vykdomas kirtimas (crossing = true) . Siuo atveju norime cia sustoti, nes tolimesniuose kirtimuose tiesiog pajudejimas nera leistinas judesys

		move(x, y, mx, my, p1); // jei pries tai buve if neivyksta, paprasciausiai pajudiname saske
		return true;
	}

	bool hasCheckers(bool p1) {
		if (p1) {
			if (player1_checkers.size() > 0) return true;
		}
		else {
			if (player2_checkers.size() > 0) return true;
		}
		return false;
	}
};

int main()
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r); //stores the console's current dimensions
	MoveWindow(console, r.left, r.top, 400, 400, TRUE); // https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-movewindow

	CONSOLE_FONT_INFOEX cfi;   // windows.h CONSOLE_FONT_INFOEX
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 25;                  // Width of each character in the font
	cfi.dwFontSize.Y = 25;                  // Height
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	wcscpy_s(cfi.FaceName, L"Consolas"); // Choose your font
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
	
	Board board;
	board.draw();
	int x, y;
	int mx, my;
	while (board.getWinner() == "") {
		if (board.hasCheckers(true)) {
		P1_1:
			cout << "Player1 pasirinkite saske - iveskite x ir y" << endl;
			cin >> x >> y;
			if (!board.checkerExists(x, y, true)) {
				cout << "Tokios saskes nera!" << endl;
				goto P1_1;
			}

		P1_2:
			cout << "Player1 iveskite x ir y kur judeti" << endl;
			cin >> mx >> my;
			if (!board.canMove(x, y, mx, my, true, false)) {
				cout << "Negalimas judejimas" << endl;
				goto P1_2;
			}
			board.draw();
		}
		if (board.hasCheckers(false)) {
		P2_1:
			cout << "Player2 pasirinkite saske - iveskite x ir y" << endl;
			cin >> x >> y;
			if (!board.checkerExists(x, y, false)) {
				cout << "Tokios saskes nera!" << endl;
				goto P2_1;
			}

		P2_2:
			cout << "Player2 iveskite x ir y kur judeti" << endl;
			cin >> mx >> my;
			if (!board.canMove(x, y, mx, my, false, false)) {
				cout << "Negalimas judejimas" << endl;
				goto P2_2;
			}
			board.draw();
		}
	}
	cout << endl;
	cout << board.getWinner() << " WON THE GAME" << endl;
	system("PAUSE");
	exit(1);
}
