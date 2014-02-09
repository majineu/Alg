#include "ShortestPath.h"
void DisMatrix(vector<vector<double> > & m)
{
	fprintf(stderr, "\n----------------------\n");
	for (size_t i = 0; i < m.size(); ++i)
	{
		for (size_t k = 0; k < m[i].size(); ++k)
			fprintf(stderr, "%-5.2f ", m[i][k] == DOUBLE_MAX ? -1000: m[i][k]);
		fprintf(stderr, "\n");
	}
	fprintf(stderr, "----------------------\n");
}

void DisMatrix(vector<vector<int> > & m)
{
	fprintf(stderr, "\n----------------------\n");
	for (size_t i = 0; i < m.size(); ++i)
	{
		for (size_t k = 0; k < m[i].size(); ++k)
			fprintf(stderr, "%-d ", m[i][k]);
		fprintf(stderr, "\n");
	}
	fprintf(stderr, "----------------------\n");
}

void test()
{
#if 0
	int weights[][3] = {{0, 1, 3},
											{0, 2, 8},
											{0, 4, -4},
											{1, 3, 1},
											{1, 4, 7},
											{2, 1, 4},
											{3, 0, 2},
											{3, 2, -5},
											{4,3,6}};
	int weights[][3] = {{0, 1, 3},
											{1, 0, -5},
											{2, 0, 1},
											{2, 1, 5},
											{0, 3, 2}};
	
	int weights[][3] = {{0, 1, 1},
											{0, 2, 1},
											{2, 3, 1},
											{2, 4, 1},
											{1, 2, 1},
											{1, 4, 1},
											{3, 4, 1}};
#endif
	int weights[][3] = {{0, 1, 1},
											{1, 2, 1}};

	CGraph g(3);

	for (int i = 0; i < sizeof(weights)/sizeof(*weights); ++i)
		g.AddEdge(weights[i][0], weights[i][1], weights[i][2], true);
	vector<vector<double> > res;
	vector<vector<int> > pi;
//	g.FloydWarshall(res, pi);
	vector<bool> vArt;
	g.FindArticulation(vArt);

	for (size_t i = 0; i < vArt.size(); ++i)
		fprintf(stderr, "Articulation %lu ? %s\n", i, vArt[i] ? "true":"false");
}

void TopoSort()
{
	int weights[][3] = {{5, 0, 1},
											{5, 2, 1},
											{4, 0, 1},
											{4, 1, 1},
											{2, 3, 1},
											{3, 1, 1}};
	CGraph g(6);
	for (int i = 0; i < sizeof(weights)/sizeof(*weights); ++i)
		g.AddEdge(weights[i][0], weights[i][1], weights[i][2], false);

	vector<int> reverseOrder;
	bool cycle = g.TopoSort(reverseOrder);

	if (cycle == true)
		fprintf(stderr, "contain cycle\n");
	else
		for (int i = (int)reverseOrder.size() - 1; i >= 0; --i)
			fprintf(stderr, "%d\n", reverseOrder[i]);
}

int main(int argc, char ** argv)
{
	TopoSort();
	return 0;
}
