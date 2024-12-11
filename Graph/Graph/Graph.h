#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>
#include<map>
#include<queue>
#include<functional>
using namespace std;

//使用邻接矩阵存储
namespace matrix
{
	template<class V, class W, W MAX_W = INT_MAX, bool Direction = false>//默认为无向图
	class Graph
	{
	public:
		typedef Graph<V, W, MAX_W, Direction> Self;

		//【1.图的基本操作】
		Graph() = default;//生成一个默认构造函数

		Graph(const V* a, int n)
		{
			_vertexs.reserve(n);
			for (int i = 0; i < n; i++)
			{
				_vertexs.push_back(a[i]);//构建图的顶点集合
				_indexMap[a[i]] = i;//顶点映射下标存储在_indexMap里
			}

			_matrix.resize(n);//温馨提示：此处不可用reserve，否则下面_vertexs[i]访问将越界
			for (int i = 0; i < n; i++)
			{
				_matrix[i].resize(n, MAX_W);//顶点之间默认权值为MAX_W
			}
		}

		int GetVertexIndex(const V& x)
		{
			auto it = _indexMap.find(x);//it类型是pair<V, int>*
			if (it != _indexMap.end())
			{
				return it->second;
			}
			else
			{
				throw invalid_argument("没有该顶点");

				return -1;//其实没什么用，因为没有找到顶点就直接抛异常了，但主要是编译器不知道，所以这里写一个返回值
			}
		}

		void AddEdge(const V& src, const V& dst, const W& w)//添加边
		{
			int srci = GetVertexIndex(src);
			int dsti = GetVertexIndex(dst);

			_AddEdge(srci, dsti, w);//使用子函数实现会好一些
		}

		void Print()const
		{
			int n = _vertexs.size();

			cout << "----------------Print()-------------------" << endl;
			cout << "图的顶点集：" << endl;
			for (int i = 0; i < n; i++)
				cout << "[" << i << "]:" << _vertexs[i] << endl;
			cout << "- - - - - - - - - - - - - - - - - - - - -" << endl;


			cout << "图的邻接矩阵：" << endl;
			cout << " ";
			for (int i = 0; i < n; i++)//横下标
			{
				printf("%3d", i);
			}
			cout << endl;
			for (int i = 0; i < n; i++)
			{
				printf("%d", i);//纵下标
				for (int j = 0; j < n; j++)
				{
					if (_matrix[i][j] != MAX_W)
						printf("%3d", _matrix[i][j]);
					else
						printf("  *");
				}
				cout << endl;
			}
			cout << "------------------------------------------" << endl;


		}

		//【2.图的遍历】

		void BFS(const V& src)//广度优先遍历
		{
			int n = _vertexs.size();

			vector<bool> visited(n, false);//标记数组，访问过的做标记，不再重新入队列以致反复遍历
			queue<int> q;//跟二叉树层序遍历一样，借助队列

			q.push(_indexMap[src]);//出发顶点先入队列
			visited[_indexMap[src]] = true;//入了队列立马标记

			int levelsize = 1;//每一层的个数，与下面for循环控制一层一层输出

			while (!q.empty())
			{
				for (int i = 0; i < levelsize; i++)//控制一层一层输出
				{
					int front = q.front();
					q.pop();
					//visited[front] = true;//【错误】应该入队列之后立马标记，而不是访问时标记，后者仍然会出现队列里面有重复顶点的情况
					cout << "[" << front << "]:" << _vertexs[front] << " ";

					for (int j = 0; j < n; j++)
					{
						if (_matrix[front][j] != MAX_W && !visited[j])
						{
							q.push(j);
							visited[j] = true;
						}
					}
				}
				levelsize = q.size();//更新levelsize值
				cout << endl;
			}
			cout << endl;
		}


		void DFS(const V& src)//深度优先遍历
		{
			vector<bool> visited(_vertexs.size(), false);//标记访问过的元素
			
			int i = GetVertexIndex(src);
			_DFS(i, visited);
		}

		
		//【3.最小生成树】

		struct Edge//边
		{
			int _srci;
			int _dsti;
			W _w;

			Edge(int srci, int dsti, const W& w)
				:_srci(srci)
				,_dsti(dsti)
				,_w(w)
			{}

			bool operator>(const Edge& e)const//适配greater<Edge>比较
			{
				return _w > e._w;
			}
		};


		W Kruskal(Self& minTree)//适用于稀疏网的最小生成树
		{
			int n = _vertexs.size();
			
			//最小生成树初始化为与原图有相同顶点集和下标关系
			minTree._vertexs = _vertexs;
			minTree._indexMap = _indexMap;
			minTree._matrix.resize(n);
			for (int i = 0; i < n; i++)
			{
				minTree._matrix[i].resize(n, MAX_W);
			}
				
			priority_queue<Edge, vector<Edge>, greater<Edge>> minque;//优先级队列，按权值小到大保存边
			for (int i = 0; i < n; i++)
			{
				for (int j = 0; j < i; j++)//注意需要让j < i,我们只研究无向图的最小生成树
				{
					if (_matrix[i][j] != MAX_W)
					{
						minque.push(Edge(i, j, _matrix[i][j]));
					}
				}
			}

			int size = 0;//记录最小生成树的边数
			W totalW = W();//记录最小生成树的边权值和
			UnionFindSet ufs(n);//利用并查集判环(最小生成树边数是n-1(顶点数-1)，即不可能有环，若有环则边数肯定小于n-1)

			while (!minque.empty())//我们需要遍历原图的所有边
			{
				Edge min = minque.top();
				minque.pop();

				if (ufs.FindRoot(min._srci) != ufs.FindRoot(min._dsti))//如果取出来的边的两个顶点不在一个集合，则不会成环，否则成环
				{
					//cout << _vertexs[min._srci] << "-" << _vertexs[min._dsti] << ":" << min._w << endl;

					ufs.Union(min._srci, min._dsti);//新加的边的两个顶点加入到同一集合
					minTree._AddEdge(min._srci, min._dsti, min._w);
					
					size++;
					totalW += min._w;
				}

			}

			if (size == n - 1)//该算法不是百分之百能找到最小生成树，可能找不到，此时size!=n-1
			{
				return totalW;
			}
			else
			{
				return W();
			}

		}

		W Prim(Self& minTree, const V& src)//适用于稠密网的最小生成树
		{
			int n = _vertexs.size();

			//最小生成树初始化：
			minTree._vertexs = _vertexs;
			minTree._indexMap = _indexMap;
			minTree._matrix.resize(n);
			for (int i = 0; i < n; i++)
			{
				minTree._matrix[i].resize(n, MAX_W);
			}

			vector<bool>X(n, false);//已纳入最小生成树的顶点
			vector<bool>Y(n, true);//未纳入最小生成树的顶点

			priority_queue<Edge, vector<Edge>, greater<Edge>>minque;
			
			//把初始顶点src加入最小生成树
			int srci = GetVertexIndex(src);
			X[srci] = true;
			Y[srci] = false;

			//src相邻的边都添加到优先级队列中
			for (int i = 0; i < n; i++)
			{
				if (_matrix[srci][i] != MAX_W && Y[i])
				{
					minque.push(Edge(srci, i, _matrix[srci][i]));
				}
			}

			int size = 0;
			W totalW = W();
			while (!minque.empty())
			{
				Edge min = minque.top();
				minque.pop();

				if (!X[min._dsti])//判环，如果添加的边的终点顶点在当前的最小生成树中，则成环，否则不成环，继续
				{
					//cout << _vertexs[min._srci] << "-" << _vertexs[min._dsti] << ":" << min._w << endl;

					X[min._dsti] = true;
					Y[min._dsti] = false;

					minTree._AddEdge(min._srci, min._dsti, min._w);
					
					size++;
					totalW += min._w;

					if (size == n - 1)
						break;

					for (int i = 0; i < n; i++)//把刚加入最小生成树的边的终点相邻的边都加入优先级队列
					{
						if (!_matrix[min._dsti][i] != MAX_W && Y[i])
						{
							minque.push(Edge(min._dsti, i, _matrix[min._dsti][i]));
						}
					}

				}
			}

			if (size == n - 1)
				return totalW;
			else
				return W();
		}


		//【4.最短路径问题】
		void PrintShortPath(const V& src, const vector<W>& dst, const vector<int>& path)
		{
			cout << "----------------PrintShortPath()-------------------" << endl;
			cout << "以" << src << "起点的最短路径:" << endl;
			int n = _vertexs.size();
			int srci = GetVertexIndex(src);

			for (int i = 0; i < n; i++)
			{
				vector<int> Path;
				int parenti = i;
				while (parenti != srci)
				{
					Path.push_back(parenti);
					parenti = path[parenti];
				}

				Path.push_back(srci);
				reverse(Path.begin(), Path.end());

				vector<int>::iterator it = Path.begin();
				while (it != Path.end())
				{
					cout << _vertexs[*it];
					if (it != Path.end() - 1)
						cout << "->";
					it++;
				}
				cout << ":" << dst[i] << endl;
			}
			cout << "---------------------------------------------------" << endl;

		}


		void Dijkstra(const V& src, vector<W>& dst, vector<int>& path)//时间复杂度O(N^2),不适用带负权值的图
		{
			//dst数组用于存储src到图每个顶点的最短路径长度
			//path数组每个下标的数值意为src到该下标对应顶点的最短路径的该顶点的父顶点(上一个与其相连的顶点)。可以迭代path数组找到最短路径
			int n = _vertexs.size();
			int srci = GetVertexIndex(src);
			
			dst.resize(n, MAX_W);//最短路径数组元素值初始化为MAX_W
			path.resize(n, -1);//默认path数组元素值为-1，意为最开始不知道谁是父顶点

			dst[srci] = W();
			path[srci] = srci;

			vector<bool> final(n, false);//final数组用于记录某顶点是否已经计算了最短路径

			for (int i = 0; i < n; i++)
			{
				//贪心算法：src到不在final中路径最短的那个顶点u
				int u = 0;
				W min = MAX_W;
				for (int j = 0; j < n; j++)
				{
					if (!final[j] && dst[j] < min)
					{
						u = j;
						min = dst[j];
					}
				}
				final[u] = true;//u这个顶点找到了最短路径，设置为true

				//再让u为出发点进行松弛操作，即让u遍历一遍与u相连的边，看看能不能更新最短路径
				for (int v = 0; v < n; v++)
				{
					// !final[v]：已经确定最短路径的顶点不用管
					// dst[u]+_matrix[u][v]<dst[v]：意为 src->u的距离 + u->v的距离 < src->v的距离，此时就要更新src->v最短路径
					if (!final[v] && _matrix[u][v] != MAX_W && dst[u] + _matrix[u][v] < dst[v])
					{
						dst[v] = dst[u] + _matrix[u][v];//更新最短路径权值和
						path[v] = u;//记录该最短路径下与v顶点的父顶点(即与v紧挨着的、相连的上一个顶点)
					}
				}
			}
		}


		bool BellmanFord(const V& src, vector<W>& dst, vector<int>& path)//暴力算法，时间复杂度O(N^3)
		{
			int n = _vertexs.size();
			int srci = GetVertexIndex(src);

			dst.resize(n, MAX_W);
			path.resize(n, -1);

			//先更新src->src为最小值
			dst[srci] = W();

			//总体最多k轮
			for (int k = 0; k < n; k++)
			{
				bool update = false;//【优化】如果这一轮不更新了，就说明已完成，直接退出循环
				
				//为了确定srci->j, 就从srci->i->j，遍历每一种可能(即取遍所有i, j)
				for (int i = 0; i < n; i++)
				{
					for (int j = 0; j < n; j++)
					{
						if (_matrix[i][j] != MAX_W && dst[i] + _matrix[i][j] < dst[j])
						{
							update = true;//标记本轮更新了dst数组

							dst[j] = dst[i] + _matrix[i][j];
							path[j] = i;//由于i,j相连，自然j父顶点为i
						}
					}
				}

				if (!update)//本轮不更新的话直接退出循环
					break;

			}

			//还能更新就说明带负权回路
			//所有最短路径算法都不能解决带负权回路问题，此时无最短路径
			for (size_t i = 0; i < n; ++i)
			{
				for (size_t j = 0; j < n; ++j)
				{
					if (_matrix[i][j] != MAX_W && dst[i] + _matrix[i][j] < dst[j])
					{
						return false;
					}
				}
			}
			return true;
		}



		void FloydWarShall(vector<vector<W>>& dst, vector<vector<int>>& path)
		{
			int n = _vertexs.size();
			dst.resize(n);
			path.resize(n);

			for (int i = 0; i < n; i++)
			{
				dst[i].resize(n, MAX_W);
				path[i].resize(n, -1);
			}

			//更新直接相连的边
			for (int i = 0; i < n; i++)
			{
				for (int j = 0; j < n; j++)
				{
					if (_matrix[i][j] != MAX_W)
					{
						dst[i][j] = _matrix[i][j];
						path[i][j] = i;
					}

					if (i == j)
					{
						dst[i][j] = W();
					}
				}
			}

			for (int k = 0; k < n; k++)
			{
				for (int i = 0; i < n; i++)
				{
					for (int j = 0; j < n; j++)
					{
						//以k作为中间的顶点尝试去更新i->j的路径
						if (dst[i][k] != MAX_W && dst[k][j] != MAX_W && dst[i][k] + dst[k][j] < dst[i][j])
						{
							dst[i][j] = dst[i][k] + dst[k][j];

							//找跟j相连的上一个邻接顶点
							//如果k->j 直接相连，上一个点就k，path[k][j]存就是k
							//如果k->j 没有直接相连，k->...->x->j，path[k][j]存就是x
							path[i][j] = path[k][j];
						}
					}
				}
			}
		}
		
	private:

		void _AddEdge(int srci, int dsti, const W& w)
		{
			_matrix[srci][dsti] = w;

			//如果是无向图，则对称位置也添加权值
			if (Direction == false)
				_matrix[dsti][srci] = w;
		}

		void _DFS(int i, vector<bool>& visited)
		{
			visited[i] = true;
			cout << "[" << i << "]:" << _vertexs[i] << endl;

			for (int j = 0; j < _vertexs.size(); j++)
			{
				if (_matrix[i][j] != MAX_W && !visited[j])//找一个与i相连的没有访问过的顶点，继续深度优先遍历
				{
					_DFS(j, visited);
				}
			}

		}

	private:
		vector<V> _vertexs;//顶点集合
		map<V, int> _indexMap;//顶点与下标的映射关系
		vector<vector<W>> _matrix;//邻接矩阵
	};
};


//使用邻接表存储
namespace link_table
{
	template<class W>
	struct Edge
	{
		//int _srci; //不需要srci，因为这里我们使用边时，本身就已知起点
		int _dsti;//目标点下标
		W _w;//权值
		Edge<W>* _next;

		Edge(int dsti, const W& w)
			:_dsti(dsti)
			,_w(w)
			,_next(nullptr)
		{}
	};

	
	template<class V, class W, bool Direction = false>
	class Graph
	{
	public:
		typedef Edge<W> Edge;
		Graph(const V* a, int n)
		{
			_vertexs.reserve(n);
			for (int i = 0; i < n; i++)
			{
				_vertexs.push_back(a[i]);
				_indexMap[a[i]] = i;
			}

			_table.resize(n, nullptr);//邻接表resize并给每个元素赋为空指针
		}

		int GetVertexIndex(const V& x)
		{
			auto it = _indexMap.find(x);
			if (it != _indexMap.end())
			{
				return it->second;
			}
			else
			{
				throw invalid_argument("找不到该节点");
				return -1;
			}

		}

		void AddEdge(const V& src, const V& dst, const W& w)
		{
			int srci = GetVertexIndex(src);
			int dsti = GetVertexIndex(dst);
			_AddEdge(srci, dsti, w);
		}

		void Print()const
		{
			int n = _vertexs.size();
			cout << "图的顶点集：" << endl;
			for (int i = 0; i < n; i++)
				cout << "[" << i << "]:" << _vertexs[i] << endl;
			cout << "------------------------------------------" << endl;


			cout << "图的邻接表：" << endl;
			for (int i = 0; i < n; i++)
			{
				cout << "[" << i << "]:" << _vertexs[i] << "->";
				Edge* cur = _table[i];
				while (cur)
				{
					cout << "{[" << cur->_dsti << "]:" << _vertexs[cur->_dsti] << ":" << cur->_w << "}->";
					cur = cur->_next;
				}
				cout << "nullptr";
				cout << endl;
			}
			cout << "------------------------------------------" << endl;

		}

	private:
		void _AddEdge(int srci, int dsti, const W& w)
		{
			Edge* e = new Edge(dsti, w);
			//头插：
			e->_next = _table[srci];
			_table[srci] = e;

			if (Direction == false)
			{
				Edge* E = new Edge(srci, w);
				//头插：
				E->_next = _table[dsti];
				_table[dsti] = E;
			}
		}

	private:
		vector<V> _vertexs;
		map<V, int> _indexMap;
		vector<Edge*> _table;//邻接表
	};
};