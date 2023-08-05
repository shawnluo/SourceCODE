
/*
Shortest Route
View
Try
Insights
Recommended Time: 45 mins
Points: 100
15 test cases (3 samples)
CodingHARDGraphShortest Path
There are roads_node buildings and m roads in HackerLand. The ith road connects building roads_from[i] and roads_to[i], is bidirectional, and has length roads_weight[i].
A delivery person has to deliver an order before returning back to the office. The delivery person starts at building a, the order has to be delivered at building c, and the office is at b. If a road is traveled multiple times, its length will be counted only once.
Find the shortest route from a to b via c. If there is no such path, return -1.
Example
roads_nodes = 4, m = 3, a = 1, b = 3, c = 2
roads_from = [0, 0, 0], roads_to = [2, 1, 3], roads_weight = [1, 2, 3]
The shortest path is 1 (a) → 0 → 2 (c) → 0 → 3 (b).
Return the path length (2 + 1 + 0 + 3) = 6.
Function Description 
Complete the function getShortestRoute in the editor below.
getShortestRoute has the following parameter(s):
    roads_nodes: the number of buildings
    int roads_from[m]: the first endpoints of each ith edge
    int roads_to[m]: roads_to[i] the other endpoints of each ith edge
    int roads_weight[m]: roads_weight[i] the weights of each ith edge.
    int a: the start of the route
    int b: the building where the office is located
    int c: the building where the order has to be delivered

Returns
    long: the minimum time required by the delivery person to go from building a to b via c
Constraints
1 ≤ roads_nodes < 105
1 ≤ m ≤ 105
0 ≤ roads_from[i] < roads_nodes where 0 ≤ i < m 
0 ≤ roads_to[i] < roads_nodes where 0 ≤ i < m 
0 ≤ roads_weight[i] < 106 where 0 ≤ i < m 
0 ≤ a,b,c < roads_nodes
Input Format for Custom Testing
The first line contains two integers roads_nodes and m, the number of buildings and the number of roads in the city.
Each of the next n lines contains three integers: roads_from[i], roads_to[i] and roads_weight[i].
The next three lines contain three integers, a, b, and c.
Sample Case 0
Sample Input 0
STDIN         FUNCTION
-----         --------
3 3     →    roads_nodes = 3 and number of edges = 3
0 2 4   →    roads_from = [0, 0, 1]
0 1 10  →    roads_to = [2, 1, 2]
1 2 5   →    roads_weight = [4, 10, 5]
0       →    a = 0, b = 2, c = 1
2
1
Sample Output 0
9
Explanation
The shortest path is 0 (a) → 2 → 1(c) → 2 (b) with a path length (4 + 5 + 0) = 9.
Sample Case 1
Sample Input 1
STDIN          FUNCTION
-----          --------
4 5     →    roads_nodes = 4 and number of edges = 5
0 2 20  →    roads_from = [0, 2, 1, 3, 0]
2 1 25  →    roads_to = [2, 1, 0, 1, 3]
1 0 15  →    roads_weight = [20, 25, 15, 10, 5]
3 1 10
0 3 5
0       →    a = 0, b = 3, c = 1
3
1
Sample Output 1
15
Explanation


The shortest path is 0 (a) → 3 → 1 (c) → 3 (b) with a path length (5 + 10 + 0) = 15.
*/

int m, n, p, q;
int min = 999999999;
int a[100][100]; //1 empty,2 some thing
int v[100][100]; //0 not accessed,1 accessed

void dfs(int x, int y, int step)
{

	if(x == p && y == q)
	{
		if(step < min)
			min = step;
		return;	
	}	

	if(a[x+1][y] == 1 && v[x+1][y] == 0) 
	{

		v[x+1][y] = 1;
		dfs(x+1, y, step+1);

		v[x+1][y] = 0; 
	}

	if(a[x][y-1] == 1 && v[x][y-1] == 0) 
	{
		v[x][y-1] = 1;
		dfs(x, y-1, step+1);
		v[x][y-1] = 0;
	}

	if(a[x-1][y] == 1 && v[x-1][y] == 0) 
	{
		v[x-1][y] = 1;
		dfs(x-1, y, step+1);
		v[x-1][y] = 0; 
	}

	if(a[x][y+1] == 1 && v[x][y+1] == 0) 
	{
		v[x][y+1] = 1;
		dfs(x, y+1, step+1);
		v[x][y+1] = 0;
	}


	return;
}

main()
{
	int i, j;
	//定义起点坐标
	int startx,starty;
	//定义数组的行和列 
	scanf("%d%d",&m,&n);
	
	//给地图赋值 
	for(i = 1; i <= m; i++)
	{
		for(j = 1; j <= n; j++)
		{
			scanf("%d",&a[i][j]);
		}
	}
	//定义起点和终点 
	scanf("%d%d%d%d",&startx,&starty,&p,&q);
	//将起点坐标设为访问
	v[startx][starty]  = 1; 
	dfs(startx,starty,0);
	
	printf("%d",min);
	
	return 0;
}