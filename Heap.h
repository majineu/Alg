#ifndef __HEAP_H__
#define __HEAP_H__
#include<vector>
#include<cstdio>
#include<cstdlib>
#include<cassert>
using std::vector;

class CHeap
{
public:
	CHeap():m_len(0)								{m_vec.clear();}


	// this function will violate heap property
	void Add(int val)								
	{
		m_len ++;
		m_vec.push_back(val);
	}


	void MaxHeapify(int idx)
	{
		int maxVal = m_vec[idx];
		int maxId = idx, leftIdx = left(idx), rightIdx = right(idx);
		if (m_len > leftIdx && maxVal < m_vec[leftIdx])
		{
			maxVal = m_vec[leftIdx];
			maxId = leftIdx;
		}

		if (m_len > rightIdx && maxVal < m_vec[rightIdx])
		{
			maxVal = m_vec[rightIdx];
			maxId = rightIdx;
		}

		if (maxId != idx)
		{
			std::swap(m_vec[idx], m_vec[maxId]);
			MaxHeapify(maxId);
		}
	}


	void BuildHeap()
	{
		for (int i = parent(m_len - 1); i >= 0; --i)
			MaxHeapify(i);
	}


	void Pop()
	{
		assert(m_len > 0);
		std::swap(m_vec[m_len - 1], m_vec[0]);
		if (--m_len > 0)
			MaxHeapify(0);
	}

	void IncreaseKey(int idx, int val)
	{
		assert(idx < m_len && idx >=0);
		assert(m_vec[idx] < val);

		m_vec[idx] = val;
		while (parent(idx) >= 0 && m_vec[parent(idx)] < val)
		{
			std::swap(val, m_vec[parent(idx)]);
			idx = parent(idx);
		}
	}

	void DecreaseKey(int idx, int val)
	{
		m_vec[idx] = val;
		MaxHeapify(idx);
	}

	void Insert(int val)
	{
		if (m_vec.size() == (size_t)m_len)
			m_vec.resize(m_len * 2);
		m_vec[m_len++] = -100000;
		InceaseKey(m_len - 1, val); 
	}

	void Show()
	{
		for (int i = 0; i < m_len; ++i)
			fprintf(stderr, "%d left %d, right %d\n:", 
					m_vec[i], 
					left(i) < m_len? m_vec[left(i)]: -1000,
					right(i) < m_len? m_vec[right(i)]:-1000);
	}


	int Top()											{return m_vec[0];}
	bool Empty()										{return m_len == 0;}
private:
	int parent(int i)								{return (i-1)/2;}
	int left(int i)									{return 2*i + 1;}
	int right(int i)								{return 2*i + 2;}

private:
	int m_len;
	vector<int> m_vec;
};


#endif  /*__HEAP_H__*/
