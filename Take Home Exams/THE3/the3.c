#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "the3.h"

vp CreateVertex(char* label)
{
	vp node = malloc(sizeof(vertex) + 56*sizeof(vp));
	
	LABEL(node) = malloc(strlen(label)*sizeof(char) + 1);
	strcpy(LABEL(node), label);
	TAG(node) = 0;
	EDGE(node)[0] = NULL;

	return node;
}

vp AddNewEdge(vp father, char* label)
{
	int i;
	vp child = CreateVertex(label);

	TAG(child) = 0;
	for (i=0; EDGE(father)[i] ; i++) continue;
	EDGE(father)[i++] = child;
	EDGE(father)[i] = NULL;

	return child;
}

vp AddEdge(vp father, vp edge)
{
	int i;
	char* edge_label = LABEL(edge);
	

	for (i=0 ; EDGE(father)[i] ; i++)
	{
		if (strcmp(edge_label, LABEL(EDGE(father)[i]) ) == 0) return NULL;
	}

	for (i=0; EDGE(father)[i] ; i++) continue;
	EDGE(father)[i++] = edge;
	EDGE(father)[i] = NULL;

	return edge;
}

vp FindVertex(vp supernode, char* label)
{
	int i;
	vp a;
	if ( strcmp(LABEL(supernode), label) == 0 ) return supernode;
	else TAG(supernode) += 1;
	
	for (i=0 ; EDGE(supernode)[i] ; i++)
	{
		if ( (int)TAG(EDGE(supernode)[i])%10 != 0) continue;
		else
		{
			a = FindVertex(EDGE(supernode)[i], label);
			if (a) return a;
		}
	}

	return NULL;
}

int Vertexlen(vp node)
{
	int i, len;
	for (i=0, len=0 ; EDGE(node)[i] ; i++) len += 1;
	return len;
}

int FindLabelArray(char** list, char* label)
{
	char** curr = list;
	while (*curr)
	{	
		if ( *curr && strcmp(*curr, label) == 0 ) return 1;
		else curr += 1;
	}
	return 0;
}

char** AddtoArr(char** list, char* label)
{
	char** curr = list;
	int i=0;

	while (curr[i])
	{
		if ( FindLabelArray(list, label) ) goto go;
		i += 1;
	}
	curr[i] = malloc(sizeof(char)*(1+strlen(label)));
	strcpy(curr[i], label);
	i += 1;
	curr[i] = NULL;
	
	go:
	return list;
}

void AddAlltoArr(char** list, vp supernode)
{
	int i;
	vp node = supernode;
	
	if (FindLabelArray(list, LABEL(node)) == 0) AddtoArr(list, LABEL(node));
	
	for (i=0 ; EDGE(node)[i] ; i++)
	{
		if (FindLabelArray(list, LABEL(EDGE(node)[i])) == 1) continue;
		else AddAlltoArr(list, EDGE(node)[i]);
	}
}

void TagZero_all(vp node)
{
	int i;

	TAG(node) = 0;

	for (i=0 ; EDGE(node)[i] ; i++)
	{
		if ( (int)TAG(EDGE(node)[i]) == 0 ) continue;
		TagZero_all(EDGE(node)[i]);
	}
}

void TagZero_ones(vp node)
{
	int i;

	if ( (int)TAG(node)%10 != 0)
	{
		TAG(node) -= ((int)TAG(node) % 10);
	}

	for (i=0 ; EDGE(node)[i] ; i++)
	{
		if ((int)TAG(EDGE(node)[i])%10 == 0) continue;
		TagZero_ones(EDGE(node)[i]);
	}
}

void TagZero_tens(vp node)
{
	int i;
	int dig_ones, dig_tens, dig_e_ones, dig_e_tens;

	if ( (int)TAG(node) < 10 ) exit(0);

	dig_ones = (int)TAG(node)%10;
	dig_tens = (int)TAG(node) - dig_ones;

	if (dig_tens != 0) TAG(node) -= dig_tens;
	
	for (i=0 ; EDGE(node)[i] ; i++)
	{
		dig_e_ones = (int)TAG(EDGE(node)[i])%10;
		dig_e_tens = (int)TAG(EDGE(node)[i]) - dig_e_ones;
		if (dig_e_tens == 0) continue;
		TagZero_tens(EDGE(node)[i]);
	}

}

int Tag_dig_ones(vp node)
{
	return ( (int)TAG(node) % 10 );
}

int Tag_dig_tens(vp node)
{
	int dig_ones = Tag_dig_ones(node);
	int number = (int) TAG(node);

	return ( (number-dig_ones)/10 );
}

int edgecmp(const void* first, const void* second)
{
	vp f = *(vp*)first, s = *(vp*)second;
	if (strcmp(LABEL(f), LABEL(s)) > 0) return 1;
	else if (strcmp(LABEL(f), LABEL(s)) < 0) return -1;
	else return 0;
}

void Graph_Sort(vp graph)
{
	int i, len;
	if (EDGE(graph)[0])
	{
		len = Vertexlen(graph);

		qsort((EDGE(graph)), len , sizeof(LABEL(EDGE(graph)[0])), &edgecmp);
		TAG(graph) += 1;

		for (i=0 ; EDGE(graph)[i] ; i++)
		{
			if ( (int)TAG(EDGE(graph)[i]) != 0 ) continue;
			Graph_Sort(EDGE(graph)[i]);
		}
	}
}

void merge_helper_sec(vp graph1, vp graph2, vp graph1_full, vp graph2_full, char** list1_full)
{
	int i;
	vp curr1 = graph1, curr2 = graph2, test, edge;
	char **list = malloc(128*sizeof(char*));
	for (i=0; i<128 ; i++)
	{
		list[i] = malloc(10*sizeof(char));
		list[i] = NULL;
	}
	AddAlltoArr(list, graph1);

	AddAlltoArr(list1_full, graph1_full);
	
	test = FindVertex(curr2, LABEL(curr1));
	TagZero_ones(curr2); 

	if (test)
	{
		for (i=0 ; EDGE(test)[i] ; i++)
		{			
			if (FindLabelArray(list1_full, LABEL(EDGE(test)[i])))
			{
				edge = FindVertex(graph1_full, LABEL(EDGE(test)[i]) );
				TagZero_ones(graph1_full);
				AddEdge(curr1, edge);

			}
			else
			{
				AddNewEdge(curr1, LABEL(EDGE(test)[i]));
			}
		}
	}
	
	AddAlltoArr(list1_full, curr1);

	TAG(curr1) += 10;
	for (i=0 ; EDGE(curr1)[i] ; i++)
	{
		if ( Tag_dig_tens(EDGE(curr1)[i]) != 0 ) continue;
		merge_helper_sec(EDGE(curr1)[i], graph2, graph1_full, graph2_full, list1_full);
	}
}

void merge_helper_first(vp graph1, vp graph2)
{
	int i;
	char** list1_full = malloc(128*sizeof(char*));
	for (i=0; i<128 ; i++)
	{
		list1_full[i] = malloc(32*sizeof(char));
		list1_full[i] = NULL;
	}
	
	AddAlltoArr(list1_full, graph1);

	merge_helper_sec(graph1, graph2, graph1, graph2, list1_full);

	for (i=0 ; i<128 ; i++) free(list1_full[i]);
	free(list1_full);
}

vp merge(vp graph1, vp graph2)
{
	vp merged;
	
	TagZero_all(graph1);
	TagZero_all(graph2);
	
	merged = CreateVertex(LABEL(graph1));

	merge_helper_first(merged, graph1);
	TagZero_ones(merged);
	TagZero_tens(merged);

	merge_helper_first(merged, graph2);
	TagZero_ones(merged);
	TagZero_tens(merged);
	
	Graph_Sort(merged);
	TagZero_all(merged);
	
	return merged;
}
