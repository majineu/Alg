#ifndef __SHOREST_PATH_H__
#define __SHOREST_PATH_H__
#include<vector>
#include<stack>
#include<cassert>
#include<cstdio>
#include<cstdlib>

#define DOUBLE_MAX 1.7e300
using std::vector;

void DisMatrix(vector<vector<double> > & m);
void DisMatrix(vector<vector<int> > & m);

class CGraph
{
public:
	CGraph(int n):m_vNum(n)
	{
		m_W.resize(n, vector<double>(n, DOUBLE_MAX));
		for (int i = 0; i < m_vNum; ++i)
			m_W[i][i] = 0;
	}
	
	void AddEdge(int r, int c, int w, bool biDirectional)
	{
		assert(r >= 0 && r < m_vNum);
		assert(c >= 0 && c < m_vNum);
		m_W[r][c] = w;
		if (biDirectional == true)
			m_W[c][r] = w;
	}

	// O(n^2) space complexity
	void FloydWarshall(vector<vector<double> > &res, 
										 vector<vector<int> > &pi)
	{
		res = m_W;
		pi.resize(m_vNum, vector<int> (m_vNum, -1));

		for (int i = 0; i < m_vNum; ++i)
			for (int j = 0; j < m_vNum; ++j)
				pi[i][j] = (i == j || res[i][j] == DOUBLE_MAX) ? -1:i;

		for (int i = 0; i < m_vNum; ++i)
		{
			for (int k = 0; k < m_vNum; ++k)
				for (int m = 0; m < m_vNum; ++m)
					if (res[k][i] + res[i][m] < res[k][m])
					{
						res[k][m] = res[k][i] + res[i][m];
						pi[k][m] = pi[i][m];
					}
		}

		fprintf(stderr, "path weight matrix:");
		DisMatrix(res);
		fprintf(stderr, "predecessor matrix:");
		DisMatrix(pi);
	}


	void PrintPath(vector<vector<int> >  &pi, int i, int j)
	{
		if (j == i)
			fprintf(stderr, "%d ", i);
		if (pi[i][j] == -1)
			fprintf(stderr, "No path\n");

		PrintPath(pi, i, pi[i][j]);
		fprintf(stderr, "%d ", j);
	}

	
	bool TopoSort(vector<int> &vInverse)
	{
		vInverse.clear();
		vector<bool> vVisit(m_vNum, false), vStack(m_vNum, false);
		for (int i = 0; i < m_vNum; ++i)
			if (vVisit[i] == false)
				if (_DFSTopoSort(i, vVisit, vStack, vInverse) == true)
					return true;

		return false;
	}

	bool _DFSTopoSort(int u, vector<bool> &vVisit, 
										vector<bool> &vStack, vector<int> &vInverse)
	{
		vStack[u] = vVisit[u] = true;
		for (int w = 0; w < m_vNum; ++w)
			if (w != u && m_W[u][w] != DOUBLE_MAX)
				if (vVisit[w] == false)
				{
					if (_DFSTopoSort(w, vVisit, vStack, vInverse) == true)
						return true;				
				}
				else if (vStack[w] == true)
					return true;	// contain cycle
		
		vInverse.push_back(u);
		vStack[u] = false;
		return false;
	}


	bool FindArticulation(vector<bool> &vArt)
	{
		vArt.resize(m_vNum, false);
		vector<bool> 	vVisit(m_vNum, false),	_stack(m_vNum, false);
		vector<int>  	dTime(m_vNum, -1);

		int _time = 0;
		_DFSArticulation(0, _time, _stack, dTime, vVisit, vArt);
	
		bool success = _time == m_vNum;
		if (!success)
			fprintf(stderr, "The graph is not connected\n");
		return success;
	}

	int _DFSArticulation(int u, 	int &_time, 	vector<bool> &_stack, 
												vector<int> &dTime,  vector<bool> &vVisit,  
												vector<bool> &vArt)
	{
		_stack[u] = vVisit[u] = true;
		dTime[u] = _time++;
		int lowCur = dTime[u], nChild = 0, lowDec = dTime[u];
		for (int v = 0; v < m_vNum; ++v)
		{
			if (m_W[u][v] == DOUBLE_MAX)
				continue;

			if (_stack[v] == true)
				lowCur = std::min(dTime[v], lowCur);
			else if(vVisit[v] == false)
			{
				int lowDec = _DFSArticulation(v, _time, _stack, dTime, vVisit, vArt);
				lowCur = std::min(lowCur, lowDec);
				++ nChild;								// child number denotes the number of connected component
				
				if (dTime[u] == 0 && nChild > 1)
					vArt[u] = true;					// root node connect more than 1 DIS-JOINT	component

				if (dTime[u] != 0 && lowDec >= dTime[u])
					vArt[u] = true;					// the component rooted at v cannot be reached without u
			}
		}
		_stack[u] = false;
		return lowCur; 
	}

private:
	int m_vNum;
	vector<vector<double> > m_W;
};


#endif  /*__SHOREST_PATH_H__*/
