#include "UnionFindSet.hpp"
#include "Graph.hpp"
#include <cstring>

void testUnionFindSet()
{
	UnionFindSet u(10);

	u.Union(0, 6);
	u.Union(7, 6);
	u.Union(7, 8);

	u.Union(1, 4);
	u.Union(4, 9);

	u.Union(2, 3);
	u.Union(2, 5);

	cout << u.Count() << endl;
}

void testGraph1() // 测试邻接矩阵存储
{
	matrix::Graph<char, int, INT_MAX, true> g("0123", 4);
	g.AddEdge('0', '1', 1);
	g.AddEdge('0', '3', 4);
	g.AddEdge('1', '3', 2);
	g.AddEdge('1', '2', 9);
	g.AddEdge('2', '3', 8);
	g.AddEdge('2', '1', 5);
	g.AddEdge('2', '0', 3);
	g.AddEdge('3', '2', 6);

	g.Print();
}

void testGraph2() // 测试邻接表存储
{
	string a[] = {"张三", "李四", "王五", "赵六"};
	link_table::Graph<string, int> g1(a, 4);
	g1.AddEdge("张三", "李四", 100);
	g1.AddEdge("张三", "王五", 200);
	g1.AddEdge("王五", "赵六", 30);

	g1.Print();
}

void testGraph3() // 测试图的遍历
{
	string a[] = {"张三", "李四", "王五", "赵六", "周七"};
	matrix::Graph<string, int> g1(a, sizeof(a) / sizeof(string));
	g1.AddEdge("张三", "李四", 100);
	g1.AddEdge("张三", "王五", 200);
	g1.AddEdge("王五", "赵六", 30);
	g1.AddEdge("王五", "周七", 30);
	g1.BFS("张三");
	g1.DFS("张三");
}

void testGraph4() // 测试最小生成树
{
	const char *str = "abcdefghi";
	matrix::Graph<char, int> g(str, strlen(str));
	g.AddEdge('a', 'b', 4);
	g.AddEdge('a', 'h', 8);
	g.AddEdge('b', 'c', 8);
	g.AddEdge('b', 'h', 11);
	g.AddEdge('c', 'i', 2);
	g.AddEdge('c', 'f', 4);
	g.AddEdge('c', 'd', 7);
	g.AddEdge('d', 'f', 14);
	g.AddEdge('d', 'e', 9);
	g.AddEdge('e', 'f', 10);
	g.AddEdge('f', 'g', 2);
	g.AddEdge('g', 'h', 1);
	g.AddEdge('g', 'i', 6);
	g.AddEdge('h', 'i', 7);

	matrix::Graph<char, int> kminTree;
	cout << "Kruskal:" << g.Kruskal(kminTree) << endl;
	kminTree.Print();

	matrix::Graph<char, int> pminTree;
	cout << "Prim:" << g.Prim(pminTree, 'a') << endl;
	pminTree.Print();
}

void testGraph5()
{
	const char *str = "syztx";
	matrix::Graph<char, int, INT_MAX, true> g(str, strlen(str));
	g.AddEdge('s', 't', 10);
	g.AddEdge('s', 'y', 5);
	g.AddEdge('y', 't', 3);
	g.AddEdge('y', 'x', 9);
	g.AddEdge('y', 'z', 2);
	g.AddEdge('z', 's', 7);
	g.AddEdge('z', 'x', 6);
	g.AddEdge('t', 'y', 2);
	g.AddEdge('t', 'x', 1);
	g.AddEdge('x', 'z', 4);
	vector<int> dist;
	vector<int> parentPath;
	g.Dijkstra('s', dist, parentPath);
	g.PrintShortPath('s', dist, parentPath);

	//// 图中带有负权路径时，贪心策略则失效了。
	//// 测试结果可以看到s->t->y之间的最短路径没更新出来
	// const char* str2 = "sytx";
	// matrix::Graph<char, int, INT_MAX, true> g2(str, strlen(str));
	// g2.AddEdge('s', 't', 10);
	// g2.AddEdge('s', 'y', 5);
	// g2.AddEdge('t', 'y', -7);
	// g2.AddEdge('y', 'x', 3);
	// vector<int> dist2;
	// vector<int> parentPath2;
	// g2.Dijkstra('s', dist2, parentPath2);
	// g2.PrintShortPath('s', dist2, parentPath2);
}

void testGraph6()
{
	const char *str = "12345";
	matrix::Graph<char, int, INT_MAX, true> g(str, strlen(str));
	g.AddEdge('1', '2', 3);
	g.AddEdge('1', '3', 8);
	g.AddEdge('1', '5', -4);
	g.AddEdge('2', '4', 1);
	g.AddEdge('2', '5', 7);
	g.AddEdge('3', '2', 4);
	g.AddEdge('4', '1', 2);
	g.AddEdge('4', '3', -5);
	g.AddEdge('5', '4', 6);
	vector<vector<int>> vvDist;
	vector<vector<int>> vvParentPath;
	g.FloydWarShall(vvDist, vvParentPath);
	// 打印任意两点之间的最短路径
	for (size_t i = 0; i < strlen(str); ++i)
	{
		g.PrintShortPath(str[i], vvDist[i], vvParentPath[i]);
		cout << endl;
	}
}

void testGraph7()
{
	const char *str = "syztx";
	matrix::Graph<char, int, INT_MAX, true> g(str, strlen(str));
	g.AddEdge('s', 't', 6);
	g.AddEdge('s', 'y', 7);
	g.AddEdge('y', 'z', 9);
	g.AddEdge('y', 'x', -3);
	g.AddEdge('z', 's', 2);
	g.AddEdge('z', 'x', 7);
	g.AddEdge('t', 'x', 5);
	g.AddEdge('t', 'y', 8);
	g.AddEdge('t', 'z', -4);
	g.AddEdge('x', 't', -2);
	vector<int> dist;
	vector<int> parentPath;
	if (g.BellmanFord('s', dist, parentPath))
	{
		g.PrintShortPath('s', dist, parentPath);
	}
	else
	{
		cout << "存在负权回路" << endl;
	}

	// 微调图结构，带有负权回路的测试
	// const char* str = "syztx";
	// Graph<char, int, INT_MAX, true> g(str, strlen(str));
	// g.AddEdge('s', 't', 6);
	// g.AddEdge('s', 'y', 7);
	// g.AddEdge('y', 'x', -3);
	// g.AddEdge('y', 'z', 9);
	// g.AddEdge('y', 'x', -3);
	// g.AddEdge('y', 's', 1); // 新增
	// g.AddEdge('z', 's', 2);
	// g.AddEdge('z', 'x', 7);
	// g.AddEdge('t', 'x', 5);
	// g.AddEdge('t', 'y', -8); // 更改
	// g.AddEdge('t', 'z', -4);
	// g.AddEdge('x', 't', -2);
	// vector<int> dist;
	// vector<int> parentPath;
	// if (g.BellmanFord('s', dist, parentPath))
	//{
	// g.PrinrtShotPath('s', dist, parentPath);
	//}
	// else
	//{
	// cout << "存在负权回路" << endl;
	//}
}
int main()
{
	// testUnionFindSet();
	// testGraph1();
	// testGraph2();
	// testGraph3();
	// testGraph4();
	// testGraph5();
	testGraph6();
	// testGraph7();

	return 0;
}