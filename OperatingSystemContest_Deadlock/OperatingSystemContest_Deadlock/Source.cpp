#include <cstdio>
#include <string>
#include <string.h>

char *edges_name[300];
int matrix[300][300] = {0};
int n;
struct spisok
{
	char *edge_name;
	int count;
} graph[300];

bool is_exist(std::string edge, int row);
int main()
{	
	scanf_s("%d", &n);
	
	for (int i = 0; i < n; i++)
	{
		char a[2];
		scanf_s("\n%s", a);
		scanf_s("%s %d", graph[i].edge_name, &graph[i].count);
		if (!is_exist(graph[i].edge_name, i))
			edges_name[i] = graph[i].edge_name;
		for (int j = 0; j < graph[i].count; j++)
		{
			char name[2];
			scanf_s("%s", name);
			if (!is_exist(name, i))
				edges_name[i] = name;
		}
	}
	printf_s(" ");
	for (int i = 0; i < n; i++)
	{
		if (i != n - 1)
			printf_s("%s ", edges_name[i]);
		else
			printf_s("%s", edges_name[i]);
	}


	return 0;
}

bool is_exist(std::string edge, int row)
{
	bool check = false;
	for (int i = 0; i < n; i++)
	{
		if (edge.compare(edges_name[i]) == 0)
		{
			check = true;
			break;
		}
	}
	return check;
}

