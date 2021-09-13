#include <iostream>
#include <vector>
#include <random>
#include <fstream>
#include <time.h>
#include "graphics.h"
#define NUMBEROFWALKERS 10
#define CHANGECOLOR 10000
using namespace std;
time_t timer;
struct tm y2k = { 0 };
unsigned long long seconds;
double trand(double lower, double upper) {
	std::random_device random_device;
	std::mt19937 random_engine(random_device());
	std::uniform_int_distribution<int> distribution_1_1000(lower, upper);

	double randomNumber = distribution_1_1000(random_engine);

	return (double)randomNumber;
}
double trandreal(double lower, double upper) {
	std::random_device random_device;
	std::mt19937 random_engine(random_device());
	std::uniform_real_distribution<double> distribution_1_1000(lower, upper);

	double randomNumber = distribution_1_1000(random_engine);

	return (double)randomNumber;
}
class Walker {
public:
	unsigned long long cnt = 0;
	unsigned long long area = 0;
	double x, y;
	int color;
	void Init() {
		x = trand(0, 1000);
		y = trand(0, 1000);
	}
	void selectcolor() {
		color = trand(1, 15);
		//setcolor(color);
	}
	void setup() {
		putpixel(x, y, color);
	}
	void changecolor() {
		cnt++;
		if (cnt % CHANGECOLOR==0) {
			selectcolor();
		}
	}
	void move() {
		int move = trand(1, 4);
		if (move == 1) {
			if (x + 1 <= 1000&&x+1>=0) {
				x = x + 1;
				area++;
			}
		}
		else if (move == 2) {
			if (x - 1 <= 1000 && x - 1 >= 0) {
				x = x - 1;
				area++;
			}
		}
		else if (move == 3) {
			if (y + 1 <= 1000 && y + 1 >= 0) {
				y++;
				area++;
			}
		}
		else {
			if (y - 1 <= 1000 && y - 1 >= 0) {
				y--;
				area++;
			}
		}
		putpixel(x, y, color);
		//circle(x, y, 5);
	}
};
vector <Walker> ver;
unsigned long long reports = 0;
void showupdates() {
	reports++;
	cout << "______________REPORT NO " << reports << "______________" << endl;
	cout << "CURRENT NUMBER OF WALKERS: "<< NUMBEROFWALKERS<<endl<<endl;
	for (unsigned int i = 0; i < ver.size(); i++) {
		cout << "WALKER NO " << i + 1 << endl;
		cout << "AREA COVERED: " << ver[i].area << endl;
		cout << "CURRENT COLOR INDEX: " << ver[i].color << endl;
		cout << "CURRENT WALKER COORDINATES: x=" << ver[i].x << " ; y=" << ver[i].y<<endl<<endl;
	}
}
int main() {
	initwindow(1000, 1000, "COLORS");
	y2k.tm_hour = 0;   y2k.tm_min = 0; y2k.tm_sec = 0;
	y2k.tm_year = 100; y2k.tm_mon = 0; y2k.tm_mday = 1;
	for (unsigned int i = 1; i <= NUMBEROFWALKERS; i++) {
		Walker a;
		a.Init();
		a.selectcolor();
		//a.setup();
		ver.push_back(a);
	}
	for (unsigned int i = 0; i < ver.size(); i++) {
		ver[i].changecolor();
		ver[i].setup();
	}
	while (1) {
		time(&timer);
		seconds = difftime(timer, mktime(&y2k));
		if (seconds % 10 == 0) {
			showupdates();
		}
		for (unsigned int i = 0; i < ver.size(); i++) {
			ver[i].changecolor();
			ver[i].move();
		}
	}
	delay(10000);
	return 0;
}

