#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>

#define ACC 0
#define WA 2

using namespace std;

FILE *in, *out;

int from[10001];
int to[10001];

const int MAXRANGE = 1000;

int main()
{
	/*int m, n;	
	int item = 0;
	std::vector<int> e;
	static int arr[MAXRANGE][MAXRANGE];

	scanf_s("%d %d", &m, &n);
	for (int i = 0; i < m; i++)
	{
		scanf_s("%d", &item);
		e.push_back(item);
	}

	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
		{
			scanf_s("%d", &arr[i][j]);
		}
	for (int i = 0; i < m; i++)
	{
		int sum = 0;
		for (int j = 0; j < n; j++)
		{
			sum += arr[j][i];	
		}
		printf_s("%d ", e[i] - sum);
	}*/
	int n,k,s,c=0,t;
    cin >> n >> k;
    for(int i=0; i<k; ++i)
    {
        cin >> s;
        for(int j=0; j<s; ++j)
        {
            ++c;
            cin >> t;
            from[t]=c;
            to[c]=t;
        }
    }
	for(int i=1; i<=c; ++i)
	{
		cout << t;
        if(to[i]!=t)
			fprintf(stderr,"Wrong Answer\n"), exit(WA);
	}
    for(int i=1; i<=n; ++i)
        if(from[i])
		{
			cout << t;
            if(from[i]!=t)
				fprintf(stderr,"Wrong Answer\n"), exit(WA);
		}
	fclose(stdin);
	fprintf(stderr,"Accepted\n");
	return ACC;

	return 0;
}