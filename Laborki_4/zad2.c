#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
bool decode(void);
bool code(const int *org, const int *try, int white, int black);
int ** fill(int **tab, int *size, const int *org, int val, int num, int white, int black);

int main(void)
{
	if (decode())
		puts("I win");
	else
		puts("You win");
	system("Rozwiazanie.txt");
	
	return 0;
}

bool decode(void)
{
	int i = 0;
	int white = 0, black = 0;
	int tab[4] = {0, 0, 0, 0};
	int x = 1;
	int c = 0, c_p = 0;
	bool win = false, cheat = false;
	int **kol = (int **)malloc(50 * sizeof(int *));
	kol[0] = (int *)malloc(4 * sizeof(int));
	kol[0][0] = kol[0][1] = kol[0][2] = kol[0][3] = 0;
	int r = 1;
	FILE *plik = fopen("Rozwiazanie.txt", "w");
	
	while (i < 10)
	{
		// WYPISYWANIE DO PLIKU
		// ------------------------------------------------------------
		fprintf(plik, "Kolejka #%d\n", i + 1);
		fprintf(plik, "Mozliwe warianty:\n");
		if (r)
		{
			for (int i = 0; i < r; i++)
				fprintf(plik, "  [%c] [%c] [%c] [%c]\n", 
				(kol[i][0]) ? (kol[i][0] + '0') : 'X',
				(kol[i][1]) ? (kol[i][1] + '0') : 'X',
				(kol[i][2]) ? (kol[i][2] + '0') : 'X',
				(kol[i][3]) ? (kol[i][3] + '0') : 'X');
			
			if (!kol[0][0] || !kol[0][1] || !kol[0][2] || !kol[0][3])
			{
				fprintf(plik, "   gdzie X = {");
				for (int i = x; i < 6; i++)
					fprintf(plik, "%d, ", i);
				fprintf(plik, "6}\n");
			}
		}
		else
		{
			fprintf(plik, "  Brak mozliwosci.\n");
			cheat = true;										// oprocz tej i kolejnej linijki
			break;
		}
		// ------------------------------------------------------------
		
		// do tab przepisywana jest pierwsza tablica z tablicy wszystkich mozliwosci
		// i wszystkie zera zamieniane sa na wartosc x
		for (int j = 0; j < 4; j++)
			tab[j] = (kol[0][j]) ? kol[0][j] : x;
		
		//for (int j = 0; j < 4; j++)
			//if (tab[j] == 0)
				//tab[j] = x;
		
		// WYSWIETLANIE PROPOZYCJI I POBIERANIE ODPOWIEDZI
		// ----------------------------------------------------------------
		printf("[%d] [%d] [%d] [%d]?\n", tab[0], tab[1], tab[2], tab[3]);
		printf("white: ");
		scanf("%d", &white);
		printf("black: ");
		scanf("%d", &black);
		// ----------------------------------------------------------------
		
		// WYPISYWANIE DO PLIKU
		// ------------------------------------------------------------------------------------
		fprintf(plik, "  Zgadywanie: [%d] [%d] [%d] [%d]\n", tab[0], tab[1], tab[2], tab[3]);
		fprintf(plik, "  Odpowiedz: czarne: %d, biale: %d\n", black, white);
		// ------------------------------------------------------------------------------------
		
		if (black == 4)
		{	
			win = true;
			break;
		}
		
		c = white + black;
		if (c > 4 || c - c_p < 0 || (x == 6 && c != 4))
		{
			cheat = true;
			break;
		}
		// WYWOLANIE WAZNEJ FUNKCJI KTORA AKTUALIZUJE TABLICE WSZYSTKICH MOZLIWOSCI
		kol = fill(kol, &r, tab, x, c - c_p, white, black);
		
		c_p = c;
		x++; i++;
	}
	
	// SPRZATANIE PO ZABAWIE
	for (int i = 0; i < r; i++)
		free(kol[i]);
	free(kol);
	fclose(plik);
	
	if (cheat)
		printf("You little cheater!\n");
	return win | cheat;
}

bool code(const int *org, const int *try, int white, int black)
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
			// ------------------------------------------------------------
			for (j = k; j < 4 && n; j++)
				if (tmp[j] == 0)
				{	
					tmp[j] = val;
					n--;
				}
			n++;	
			k = j - 1;
			// ------------------------------------------------------------
			
			// sprawdzanie i ewentualne dodanie do stosu
			// ------------------------------------------------
			if (code(org, tmp, white, black))
			{
				t[r++] = (int *)malloc(4 * sizeof(int));
				for (int i = 0; i < 4; i++)
					t[r-1][i] = tmp[i];
			}
			// ------------------------------------------------
			
			// Jesli nic nie ma byc wstawione
			if (num == 0)
				break;
			
			// CZY Z PRZODU SA JESZCZE JAKIES ZERA?
			// ------------------------------------------------
			flag = false;
			for (j = k + 1; j < 4; j++)
				if (tmp[j] == 0)
					flag = true;
			// ------------------------------------------------
			
			if (flag)
			{
				// Jesli sa to zeruj element k-ty i kontunuuj
				// ETAP 1 wstawi val na kolejnym zerze
				tmp[k++] = 0;
				continue;
			}
			else	// Jesli nie ma zer z przodu tzn. ze trzeba sie cofnac
			{
				// USUWA n KOLEJNYCH ELEMENTOW (wlacznie z tym pierwszym)
				// --------------------------------------------------------
				for (j = k, l = 0; l < n; j++)
					if (tmp[j] == val)
					{
						tmp[j] = 0;
						l++;
					}
				// --------------------------------------------------------
				
				// cofa sie
				flag = false;
				for (j = k - 1; j >= 0; j--)
				{
					// JESLI NATRAFI NA 0
					if (tmp[j] == 0)
						flag = true;
					
					if (tmp[j] == val)
					{
						// ZAMIENIA W tab val NA 0 I ZLICZA ILE val USUNAL
						n++;
						tmp[j] = 0;
						
						// JESLI WYKRYTO 0 A POZNIEJ NATRAFIONO NA val TO CZAS PRZEJSC DO ETAP 1
						if (flag)
						{
							k = j + 1;
							break;
						}
					}
				}
				// TO OZNACZA ZE WSZYSTKIE KOMBINACJE ZOSTALY JUZ WYPROBOWANE
				if (j < 0)
					break;
			}
		}
	}
	
	// SPRZATANIE PO ZABAWIE
	// ------------------------------
	for (int i = 0; i < *size; i++)
		free(tab[i]);
	free(tab);
	*size = r;
	// ------------------------------
	
	return t;
}