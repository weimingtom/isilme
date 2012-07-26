#include <vector>

enum direction
{
	up,
	down,
	lft,
	rght,
	unknown
};

enum cell
{
	player,
	empty,
	object,
	wall,
	invalid
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