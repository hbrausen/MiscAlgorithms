#include "disjoint.cpp"

#include <iostream>

int main(int argc, char **argv)
{
	DisjointSets DS(5);
	for (int i = 0; i < 5; ++i) DS.MakeSet(i);
	DS.Union(0,1);
	DS.Union(1,2);
	DS.Union(3,4);
	cout << DS.Find(0) << ' ' << DS.Find(2) << endl;
	cout << DS.Find(4) << endl;
	DS.Union(4,0);
	cout << DS.Find(0) << ' ' << DS.Find(1) << ' ' << DS.Find(4) << endl; 
}
