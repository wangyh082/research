int overlap(int *sl, int **s, int s1, int s2)
// computes the overlap between the two strings s[s1] and s[s2]
//
// input arguments:
// sl = string lengths
// s  = strings
// s1 = string number 1
// s2 = string number 2
{
	bool is;
	int o,i;
	int minLength = min(sl[s1], sl[s2]);
	// for every alignment position between the two strings such that none of
	// them is a substring of the other
	for (o = minLength - 1; o >= 0; o--)
	{
		// test if the aligned letters are identical
		is = true;
		for (i = 0; i < o; i++)
		{
			if (s[s1][sl[s1] - o + i] != s[s2][i])
			{
				is = false;
				break;
			}
		}
		if (is == true)
		{
			return o;
		}
	}
	return o;
} //overlap

/******************************************************************************/

void createOverlapGraph(int n, int *sl, int **s, int **og)
// creates the overlap graph for the strings s. the self-overlaps are -1 (null)
//
// input arguments:
// n  = number of strings
// si = string lengths
// s  = strings as a 2-dimensional matrix with the elements of each string
//      stored in one row (-1 is the 'end character' of each string)
//
// output arguments:
// og = overlap graph (represented by its adjacency matrix)
{
	int i,j;
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			if (i == j)
				og[i][j] = -1;
			else
				og[i][j] = overlap(sl, s, i, j);
} //createOverlapGraph
