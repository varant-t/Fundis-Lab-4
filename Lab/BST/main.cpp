#include <iostream>
#include <string>

using namespace std;

#include "BST.h"

struct Player
{
	string name;
	int ranking;
};

void printPlayer(Player& p)
{
	cout << p.name << ": " << p.ranking << endl;
}

int main()
{
	Player players[] = {
		{ "Jim", 23 },
		{ "Sally", 75 },
		{ "Bob", 53 },
		{ "Bubba", 18 },
		{ "Alice", 95 },
		{ "George", 98 },
		{ "Lucy", 33 },
		{ "Walter", 66 },
		{ "Abe", 65 },
		{ "Joe", 67 }
	};

	int n = sizeof(players) / sizeof(players[0]);
	int i;


	cout << "Sorting players by name:" << endl;

	BST<string,Player> tree1;

	for (i=0; i<n; i++)
		tree1.insert(players[i].name, players[i]);

	tree1.traverseInOrder(printPlayer);

	BST<int,Player> tree2;

	for (i=0; i<n; i++)
		tree2.insert(players[i].ranking, players[i]);

	cout << endl;
	cout << "In-Order Traversal" << endl;
	tree2.traverseInOrder(printPlayer);

	cout << endl;
	cout << endl;

	cout << "Pre-Order Traversal" << endl;
	tree2.traversePreOrder(printPlayer);

	cout << endl;
	cout << endl;

	cout << "Post-Order Traversal" << endl;
	tree2.traversePostOrder(printPlayer);

	cout << endl;
	cout << endl;

	cout << "Level-Order Traversal" << endl;
	tree2.traverseLevelOrder(printPlayer);

	for (i=0; i<n; i++)
		tree2.remove(players[i].ranking);
	
	cout << endl;
	cout << endl;

	tree2.traverseInOrder(printPlayer);

	return 0;
}
