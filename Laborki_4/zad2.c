#include <stdio.h>
#include <stdbool.h>
bool decode(void);
bool foo(const int *org, const int *try, int white, int black);
int * fill(int **tab, int size, int val, int num);

int main(void)
{
	int a[4] = {5, 4, 3, 6};
	int b[4] = {6, 3, 5, 4};
	foo(a, b, 0, 0);
	
	if (decode())
		puts("I win");
	else
		puts("You win");
	
	return 0;
}

bool decode(void)
{
	int i = 0;
	int w_prev = 0, b_prev = 0;
	int white = 0, black = 0;
	int tab[4] = {1, 1, 1, 1};
	int mask[4] = {1, 1, 1, 1};
	//int is[6] = {0, 0, 0, 0, 0, 0};
	int x = 1;
	int c = 0, c_p = 0;
	int t = 0;
	
	while (i < 10 && c != 4)
	{
		w_prev = white; b_prev = black; c_p = c;
		
		for (int j = 0; j < 4; j++)
			if (mask[j])
				tab[j] = x;
		
		// wyswietlanie propozycji i pobieranie odpowiedzi
		printf("[%d] [%d] [%d] [%d]?\n", tab[0], tab[1], tab[2], tab[3]);
		printf("white: ");
		scanf("%d", &white);
		printf("black: ");
		scanf("%d", &black);
		
		c = white + black;
		if (c - c_p> 0)
			for (int j = 0; j < c - c_p; j++)
				mask[t++] = 0;
		//
		//is[x-1] = black - b_prev;
		x++;
	}
	
	if (c == 4)
		return true;
	return false;
}

// wlasciwie to wystarczy sprawdzenie ile jest black'ow
bool foo(const int *org, const int *try, int white, int black)
{
	int b = 0, w = 0;
	int try_c[4], org_c[4];
	
	// liczy czarne
	for (int i = 0; i < 4; i++)
		if (try[i] == org[i])
			b++;
	
	// liczy biale
	for (int i = 0; i < 4; i++)
	{
		try_c[i] = try[i];
		org_c[i] = org[i];
	}
	for (int i = 0; i < 4; i++)
		if (try_c[i] == org_c[i])
			try_c[i] = org_c[i] = 0;
	for (int i = 0; i < 4; i++)
		if (try_c[i] != 0)
			for (int j = 0; j < 4; j++)
				if (try_c[i] == org_c[j])
				{
					w++;
					try_c[i] = org_c[j] = 0;
					break;
				}
	// koniec liczenia bialych
	//printf("czarne: %d, biale: %d\n", b, w);
	
	if (b == black)
		return true;
	return false;
}

int * fill(int **tab, int &size, const int *org, int val, int num, int white, black);
{
	int **t = (int **)malloc(50 * sizeof(int *));
	int mask[5];
	int masks[10][4];
	int r = 0;
	int k, j;
	int tmp[4];
	
	for (int i = 0; i < *size; i++)
	{
		for (j = 0, k = 0; j < 4; j++)
			if (tab[i][j] == 0)
				mask[k++] = j;
		mask[k] = -1;
		
		for (j = 0; j )
		
		// wypelnianie tablicy tmp
		for (int j = 0, k = 0; i < 4 && k < val; j++)
		{
			if (tab[i][j] == 0)
			{	
				tmp[j] = val;
				k++;
			}
			else
				tmp[j] = tab[i][j];
		}	
		
		// sprawdzanie i ew. dodanie do stosu
		if (foo(org, tmp, white, black))
		{
			t[r++] = (int *)malloc(4 * sizeof(int));
			for (int i = 0; i < 4; i++)
				t[r-1][i] = tmp[i];
		}
	}
	
	for (int i = 0; i < *size; i++)
		free(tab[i]);
	free(tab);
	
	tab = t;
	t = NULL;
	*size = r;
	
	return tab[0];
}