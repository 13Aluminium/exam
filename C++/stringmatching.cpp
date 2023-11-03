#include <bits/stdc++.h>
using namespace std;
int main()
{
	string txt, pat;
	cout << "Enter the text: ";
	cin >> txt;
	cout << "Enter the pattern: ";
	cin >> pat;
	int N = txt.length();
	int M = pat.length();
	for (int i = 0; i <= N - M; i++)
	{
		int j;
		for (j = 0; j < M; j++)
		{
			if (txt[i + j] != pat[j] && pat[j] != '*')
			{
				break;
			}
		}
		if (j == M)
		{
			cout << "Pattern found at index " << i << endl;
		}
	}
	return 0;
}

