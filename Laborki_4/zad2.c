#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
bool decode(void);
bool foo(const int *org, const int *try, int white, int black);
int ** fill(int **tab, int *size, const int *org, int val, int num, int white, int black);

int main(void)
{
	int a[4] = {5, 4, 3, 6};
	int b[4] = {6, 3, 5, 4};
	//foo(a, b, 0, 0);
	
	if (decode())
		puts("I win");
	else
		puts("You win");
	
	return 0;
}

bool decode(void)
{
	int i = 0;
	int white = 0, black = 0;
	int tab[4] = {0, 0, 0, 0};
	int x = 1;
	int c = 0, c_p = 0;
	int **kol = (int **)malloc(50 * sizeof(int *));
	kol[0] = (int *)malloc(4 * sizeof(int));
	kol[0][0] = kol[0][1] = kol[0][2] = kol[0][3] = 0;
	int r = 1;
	
	while (i < 10)
	{
		//for (int j = 0; j < r; j++)
		//	printf("[%d] [%d] [%d] [%d]?\n", kol[j][0], kol[j][1], kol[j][2], kol[j][3]);
		//putchar('\n');
		
		for (int j = 0; j < 4; j++)
			tab[j] = kol[0][j];
		//printf("[%d] [%d] [%d] [%d]?\n", tab[0], tab[1], tab[2], tab[3]);
		//getchar();
		//getchar();
		
		for (int j = 0; j < 4; j++)
			if (tab[j] == 0)
				tab[j] = x;
		
		// wyswietlanie propozycji i pobieranie odpowiedzi
		printf("[%d] [%d] [%d] [%d]?\n", tab[0], tab[1], tab[2], tab[3]);
		printf("white: ");
		scanf("%d", &white);
		printf("black: ");
		scanf("%d", &black);
		
		if (black == 4)
			return true;
		
		c = white + black;
		kol = fill(kol, &r, tab, x, c - c_p, white, black);
		
		c_p = c;
		x++; i++;
	}
	
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

int** fill(int **tab, int *size, const int *org, int val, int num, int white, int black)
{
	int **t = (int **)malloc(50 * sizeof(int *));
	int r = 0;
	int tmp[4];
	bool flag, koniec;
	int j, l;
	
	for (int i = 0; i < *size; i++)
	{	
		// wypelnianie tablicy tmp
		for (j = 0; j < 4; j++)
			tmp[j] = tab[i][j];
		
		koniec = false;
		int n = num, k = 0;
		while (1)
		{
			// ETAP 1 - wstawianie n wartosci val zamiast kolejnych zer
			// teoretycznie w warunku moze byc samo n, ale sie ubezpieczam
			for (j = k; j < 4 && n; j++)
				if (tmp[j] == 0)
				{	
					tmp[j] = val;
					n--;
				}
			
			if (num == 0)
				koniec = true;
			n++;	
			k = j - 1;
			
			// sprawdzanie i ew. dodanie do stosu
			if (foo(org, tmp, white, black))
			{
				t[r++] = (int *)malloc(4 * sizeof(int));
				for (int i = 0; i < 4; i++)
					t[r-1][i] = tmp[i];
			}
			if (koniec)
				break;
			//printf("%d%d%d%d\n", tmp[0], tmp[1], tmp[2], tmp[3]);
			
			// ETAP 2 - glowny etap przesuwania
			flag = false;
			for (j = k + 1; j < 4; j++)
			{
				if (tmp[j] == 0)
					flag = true;
			}
			if (flag)
			{
				tmp[k++] = 0;
				continue;
			}
			else
			{
				// usuwa dany element i n kolejnych elementow
				for (j = k, l = 0; l < n; j++)
					if (tmp[j] == val)
					{
						tmp[j] = 0;
						l++;
					}
				
				flag = false;
				for (j = k - 1; j >= 0; j--)
				{
					if (tmp[j] == 0)
						flag = true;
					
					if (tmp[j] == val && flag)
					{
						n++;
						k = j + 1;
						tmp[j] = 0;
						break;
					}
					if (tmp[j] == val && !flag)
					{
						tmp[j] = 0;
						n++;
					}
				}
				if (j < 0)
					break;
			}
		}
	}
	
	for (int i = 0; i < *size; i++)
		free(tab[i]);
	free(tab);
	
	*size = r;
	
	return t;
}