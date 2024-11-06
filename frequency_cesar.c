#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX_TEXT_SIZE 100
#define ALPHABET_SIZE 26
void calculate_frequencies(char *text, int *frequencies)
{
	for (int i = 0; text[i] != '\0'; i++)
	{
		if (isalpha(text[i]))
		{
			frequencies[toupper(text[i]) - 'A']++;
		}
	}
}
int estimate_key(int *frequencies)
{
	int max_freq_index = 0;
	for (int i = 1; i < ALPHABET_SIZE; i++)
	{
		if (frequencies[i] > frequencies[max_freq_index])
		{
			max_freq_index = i;
		}
	}
	int estimated_key = (max_freq_index - ('E' - 'A') + ALPHABET_SIZE) % ALPHABET_SIZE;
	return estimated_key;
}
void caesar_decrypt(char *ciphertext, int key, char *plaintext)
{
	for (int i = 0; ciphertext[i] != '\0'; i++)
	{
		if (isalpha(ciphertext[i]))
		{
			char offset = isupper(ciphertext[i]) ? 'A' : 'a';
			plaintext[i] = (ciphertext[i] - offset - key + ALPHABET_SIZE) % ALPHABET_SIZE + offset;
		}
		else
		{
			plaintext[i] = ciphertext[i];
		}
	}
	plaintext[strlen(ciphertext)] = '\0';
}
int main()
{
	char ciphertext[MAX_TEXT_SIZE];
	char plaintext[MAX_TEXT_SIZE];
	int frequencies[ALPHABET_SIZE] = {0};
	printf("Entrez le texte chiffré : ");
	fgets(ciphertext, MAX_TEXT_SIZE, stdin);
	ciphertext[strcspn(ciphertext, "\n")] = '\0';
	calculate_frequencies(ciphertext, frequencies);
	int estimated_key = estimate_key(frequencies);
	printf("Clé estimée : %d\n", estimated_key);
	caesar_decrypt(ciphertext, estimated_key, plaintext);
	printf("Texte déchiffré : %s\n", plaintext);
	return 0;
}
