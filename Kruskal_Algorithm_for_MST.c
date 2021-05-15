#include <stdio.h>
#include <stdbool.h>

typedef struct node_structure
{
	int name;
	int status;
}node;
typedef struct edge_structure
{
	int start,end;
	int start_index,end_index;
	int weight;
}edge;


// functions declaration------
bool is_this_node_is_in_nodes_array(node nodes_array[], int length, int item);
int index_of_node_in_nodes_array(node nodes_array[], int length, int item);
void sort_edges_by_weight_in_ascending_order(edge* edges_array, int length);
bool is_this_edge_forming_a_cycle(edge x, node* nodes_array);
int total_weight_of_mst(edge* mst, int length);
void kruskal_algorithm(edge* edges_array, node* nodes_array, int edge_length);
void swap(edge* x, edge* y);

int main()
{
	int edge_count;
	printf("How many edges are in the graph:- ");
	scanf("%d", &edge_count);

	node nodes_array[100];
	int node_count = 0;
	edge edges_array[200];

	// taking input of edges and nodes of the graph ------
	int j = 0;	// initialising temporary variable to store values in nodes_array.
	for (int i = 0; i < edge_count; i++)
	{
		printf("\n==========: Values for Edge %d :==========\n", i + 1);

		// doing operations for start node of this edge------
		printf("The starting node is:- ");
		scanf("%d", &edges_array[i].start);
		if (is_this_node_is_in_nodes_array(nodes_array, node_count, edges_array[i].start) == false)
		{
			nodes_array[j].name = edges_array[i].start;
			nodes_array[j].status = 1;
			j++;
			node_count++;
		}
		edges_array[i].start_index = index_of_node_in_nodes_array(nodes_array, node_count, edges_array[i].start);

		// doing operations for end node of this edge------
		printf("The ending node is:- ");
		scanf("%d", &edges_array[i].end);
		if (is_this_node_is_in_nodes_array(nodes_array, node_count, edges_array[i].end) == false)
		{
			nodes_array[j].name = edges_array[i].end;
			nodes_array[j].status = 1;
			j++;
			node_count++;
		}
		edges_array[i].end_index = index_of_node_in_nodes_array(nodes_array, node_count, edges_array[i].end);

		// getting the weight of the edge -----
		printf("Weight of this edge is:- ");
		scanf("%d", &edges_array[i].weight);
	}

	// starting calculations for MST (Minimum Spanning Tree) -------
	// creating table of edge and weight in sorted order ----
	sort_edges_by_weight_in_ascending_order(edges_array, edge_count);
	kruskal_algorithm(edges_array, nodes_array, edge_count);
}

bool is_this_node_is_in_nodes_array(node nodes_array[], int length, int item)
{
	bool flag=false;
	for (int i = 0; i < length; i++)
	{
		if (item == nodes_array[i].name)
		{
			flag=true;
			break;
		}
	}
	return flag;
}

int index_of_node_in_nodes_array(node nodes_array[], int length, int item)
{
	int index=0;
	for (int i = 0; i < length; i++)
	{
		if (item == nodes_array[i].name)
		{
			index=i;
			break;
		}
	}
	return index;
}

void sort_edges_by_weight_in_ascending_order(edge* edges_array, int length)
{
	// in bubble sort technique ------
	for (int i = 0; i < length-1; i++)
	{
		for (int j = i+1; j < length; j++)
		{
			if (edges_array[i].weight > edges_array[j].weight)
			{
				swap(&edges_array[i], &edges_array[j]);
			}
		}
	}
}

bool is_this_edge_forming_a_cycle(edge x, node* nodes_array)
{
	/*
	* any node in MST can have maximum 2 edges.
	* so if the status of both nodes of a edge is <= 2 then only
	* that node is eligible for inserting in MST
	* otherwise not.
	*/
	bool flag = true;
	if (nodes_array[x.start_index].status <= 2 && nodes_array[x.end_index].status <= 2)
	{
		flag = false;
	}
	return flag;
}

int total_weight_of_mst(edge* mst, int length)
{
	int sum = 0;
	for (int i = 0; i < length; i++)
	{
		sum = sum + mst[i].weight;
	}
	return sum;
}

void kruskal_algorithm(edge* edges_array, node* nodes_array, int edge_length)
{
	edge mst[100];
	int j = 0;	// initialising a variable to store values in mst
				// it will be length of mst after the loop.
	for (int i = 0; i < edge_length; i++)
	{
		// if this edge will not form a cycle then only it could be inserted in MST.
		if (is_this_edge_forming_a_cycle(edges_array[i], nodes_array) == false)
		{
			nodes_array[edges_array[i].start_index].status++;
			nodes_array[edges_array[i].end_index].status++;
			mst[j] = edges_array[i];
			j++;
		}
	}

	// displaying Minimum Spanning Tree -----
	printf("\n\nThe edges of MST are below --------\n\n");
	for (int i = 0; i < j; i++)
	{
		printf("\t(%d, %d)\n", mst[i].start, mst[i].end);
	}
	printf("\n");

	// calculating & displaying total weight of MST -------
	int total_weight;
	total_weight = total_weight_of_mst(mst, j);
	printf("\nThe total weight of mst is:- %d\n\n", total_weight);
}

void swap(edge* x, edge* y)
{
	edge temp;
	temp = *x;
	*x = *y;
	*y = temp;
}
