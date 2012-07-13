#include <vector>

enum direction
{
	up,
	down,
	left,
	right,
	unknown
};

enum cell
{
	player,
	empty,
	object,
	wall
};

struct net
{
public:
	hgeQuad square;
	int n;
	int m;
	cell various;
	direction queue;
	direction previous;
	bool toUp;
	bool toDown;
	bool toLeft;
	bool toRight;
	float increaseX;
	float increaseY;
	bool reflux;
};

struct work
{
public:
	int x, y;
	direction moveTo;
};

using namespace std;
vector <net> snake;
vector <work> search;