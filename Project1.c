/*
Travis Mazzy
ENRG 476
Lab 330
Due: 3/5/18
*/


#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>

#define graphSize 8

FILE* graphFile;
char filename[30];
char graphLetters[graphSize];
int graph[graphSize][graphSize];
int destination;
int source;

void dijkstra(int graph[graphSize][graphSize], int output[], int size, int src, int dst);

void main()
{

	printf("Please enter a file name \n");
	scanf("%s", filename);

	if (readFile() != 1) {
		return -1;
	}

	char temp;
	int valid = 0;

	printf("Please enter the source \n");

	while (1)
	{

		
		scanf("%c", &temp);
		for (int i = 0; i < graphSize; i++)
		{
			if (temp == graphLetters[i])
			{
				source = i;
				valid = 1;
				i = graphSize;
			}
		}

		if (valid == 1)
		{
			break;
		}
	}

	valid = 0;

	printf("Please enter the destination \n");

			while (1)
			{
				
				scanf("%c", &temp);
				for (int i = 0; i < graphSize; i++)
				{
					if (temp == graphLetters[i])
					{
						destination = i;
						valid = 1;
						i = graphSize;

					}
				}

				if (valid == 1)
				{
					break;
				}
			}

	int output[graphSize];

	dijkstra(graph, output, graphSize, source, destination);


	system("pause");
}

int readFile() {
	char *line;				//for getLine
	char *t;				//char for parsing
	char buffer[500];		//stores position of first char in line
	int size = 500;			//byte size, may be overshooting it

	graphFile = fopen(filename, "r");
	if (graphFile == NULL) {
		printf("\nfile was not found\n");
		system("pause");
		return -3;
	}

	line = fgets(buffer, size, graphFile);		//Line for graph node lettering
	int i = 0;
	for (i = 0; i < graphSize; i++)
	{
		if (i == 0)
		{
			t = strtok(line, ",");
		}
		else 
		{
			t = strtok(NULL, ",");
		}

		graphLetters[i] = t[0];

	}


	for (i = 0; i < graphSize; i++)
	{
		line = fgets(buffer, size, graphFile);
		t = strtok(line, ",");
		for (int j = 0; j < graphSize; j++)
		{
			if (i < graphSize)
			{
				t = strtok(NULL, ",");
			}
			else
			{
				t = strtok(NULL, "\n");
			}
			int g;
			sscanf(t, "%d", &g);
			graph[i][j] = g;
			if (i != j && g == 0)
				graph[i][j] = INT_MAX;
		}
	}

	return 1;

}

void dijkstra(int graph[graphSize][graphSize], int output[], int size, int src, int dst)
{
	int* dist = malloc(4 * size);				//the shortest route to each node
	int qlength = size;
	int* visited = malloc(4 * size);
	int numVisited;
	int currentNode = src;
	int* path = malloc(4 * size);
	int lastVisited =source;

	//Sets initial values for variables
	for (int i = 0; i < size; i++) {
		dist[i] = graph[src][i];
		visited[i] = 0;
		path[i] = src;
	}

	dist[src] = 0;
	visited[src] = 1;

	//loop until destination has been visited
	while (visited[dst] == 0)
	{
		int localMin = INT_MAX;
		int minIndex;

		//find shortest immediate path to an unvisted node
		for (int i = 0; i < size; i++)
		{
			if (visited[i] != 1 && dist[i] < localMin)
			{
				localMin = dist[i];
				minIndex = i;

			}
		}
		
		//visit shortest node
		visited[minIndex] = 1;

		//update distance value for adjacent nodes
		for (int j = 0; j < size; j++)
		{
			if (visited[j] != 1 && graph[minIndex][j] + localMin < dist[j] && graph[minIndex][j] + localMin >= 0)
			{

				dist[j] = localMin + graph[minIndex][j];
				//mark this path as a predicessor for shortest path to next nodes
				path[j] = minIndex;												
			}



		}


	}

	//Printing output
	//Follows flow of node predicessors, starting with destination, until source node is reached

	output = dist;
	printf("Shortest Path: \n");
	int j;
		j = dst;
		printf("%c", graphLetters[dst]);
		
		do {
			printf(" <- %c", graphLetters[path[j]]);
			j = path[j];
			
		} while (j != src);


	printf("\n");

	printf("Has a distance of: \n");
	printf("%i\n", dist[dst]);
}


