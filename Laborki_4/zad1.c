#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
bool match(const char *pat, const char *str);

int main(void)
{
	char t1[50] = "*.doc", t2[50] = "abrak..fa .doadara.doc";
	
	gets(t1);
	//getchar();
	gets(t2);
	
	printf("%d\n", match(t1, t2));
	
	return 0;
}

bool match(const char *pat, const char *str)
{
	int i, j, k, s;
	bool ret = false, flag;
	char next;
	
	i = j = 0;
	while (/*str[i] != '\0' && */pat[j] != '\0')
	{
		if (pat[j] == '?')
		{
			//if (isalpha(str[i]))
				i++;
			//else
				//return false;
		}
		else if (pat[j] == '*')
		{
			while (true)
			{
				k = j + 1;
				next = pat[k];
				// pomija wszystkie znaki az trafi na znak next
				while (str[i] != '\0' && str[i] != next)
					i++;
				s = i;
				
				if (str[i] == '\0')
					break;
				
				flag = true;
				while (flag && pat[k] != '\0' && pat[k] != '*')
				{
					if (pat[k] == '?')
					{
						if (isalpha(str[i]))
							i++;
						else
							flag = false;
					}
					else
					{
						if (str[i] == pat[k])
							i++;
						else
							flag = false;
					}
					k++;
				}
				
				if (flag == true)
				{
					j = k - 1;
					break;
				}
				i = s + 1;
			}
		}
		else
		{
			if (str[i] == pat[j])
				i++;
			else
				return false;
		}
		j++;
	}
	
	//printf("%c %c", pat[j], str[i]);
	if (str[i] == '\0' && pat[j] == '\0')
		return true;
	
	return ret;
}