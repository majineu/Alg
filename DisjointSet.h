#ifndef __DISJOINT_SET_H__
#define __DISJOINT_SET_H__
#include<vector>
#include<cassert>

using std::vector;

class CDisjointSet
{
	struct SNode
	{
		int m_p;			// parent
		int m_r;			// rank
	};
public:

	CDisjointSet(int n):m_nNode(n)
	{
		m_vNode.resize(m_nNode);
		for (int i = 0; i < m_nNode; ++i)
		{
			m_vNode[i].m_p = i;
			m_vNode[i].m_r = 0;
		}	
	}

	int FindSet(int x)
	{
		assert(x >= 0 && x < m_nNode);
		if (m_vNode[x].m_p != x)
			m_vNode[x].m_p = FindSet(m_vNode[x].m_p);   // flatten the tree structure
		
		return m_vNode[x].m_p;
	}


	void Union(int x, int y)
	{
		assert(x >= 0 && x < m_nNode);
		assert(y >= 0 && y < m_nNode);
		int sX = FindSet(x), sY = FindSet(y);
		
		if (m_vNode[sX].m_r > m_vNode[sY].m_r)
			m_vNode[sY].m_p = sX;
		else
		{
			m_vNode[sX].m_p = sY;
			if (m_vNode[sY].m_r == m_vNode[sX].m_r)
				++m_vNode[sY].m_r; 
		}
	}

private:
	int m_nNode;
	vector<SNode> m_vNode;
};


#endif  /*__DISJOINT_SET_H__*/
