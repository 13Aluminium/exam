#include <iostream>
using namespace std;

void searchPatternInString(const string &text, const string &pattern, int q)
{
	int patternLen = pattern.length();
	int textLen = text.length();
	for (int i = 0; i <= textLen - patternLen; i++)
	{
		bool match = true;
		for (int j = 0; j < patternLen; j++)
		{
			if (text[i + j] != pattern[j])
			{
				match = false;
				break;
			}
		}
		if (match)
		{
			cout << "Pattern found at index " << i << endl;
		}
	}
}

int main()
{
	string text, pattern;
	int q;
	cout << "Enter a text: ";
	getline(cin, text);
	cout << "Enter a pattern: ";
	getline(cin, pattern);
	cout << "Enter a value for q: ";
	cin >> q;
	searchPatternInString(text, pattern, q);
	return 0;
}
