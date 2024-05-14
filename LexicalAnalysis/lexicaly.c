#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define GARBAGE 0xcdcdcdcdcdcdcdcd
#define MAX_SIZE 20 // Maximum number of lines to read
#define MAX_STR_SIZE 50 // Maximum size for the string

#include "lexemes.c"

#define NO_ERROR 0
#define specialTavArr 24
#define sizeOfNameTOK_OP 10
#define row 12
#define column 7
#define dollarValue 58
#ifndef TOKEN_H
#define TOKEN_H
#endif // TOKEN_H
#define DEGEL 0
#define NUM_STATES 220
#define GARBAGE 0xcdcdcdcdcdcdcdcd
//מילוי מערך המצבים
typedef struct CurrentState {
	char letter;
	int nextIndex;
	struct CurrentState* csptr;

}CurrentState;
CurrentState cs;
CurrentState* currentStateArr[NUM_STATES];
CurrentState* ptr;
struct Data {
	char str[MAX_STR_SIZE];
	int num;
};	struct Data dataArray[MAX_SIZE];
int mat[row][column];


typedef struct Token {
	char* value;
	char* nameToken;
	int index;
	struct Token* next;

}Token;



Token* token1;
Token* tokenPtr;
Token** headList;

char characters[specialTavArr];

void ListOfTokens(char* value, char* nameToken, int index);




int automate()
{//מילוי מבנה האוטומט

	FILE* fileStates = NULL;
	int index;

	fileStates = fopen("C:/Users/User/Desktop/compilerProject/state.txt", "r");

	if (fileStates == NULL)
	{
		printf("error in the file states.txt \n");
		exit(1);
	}
	for (int i = 0; i < NUM_STATES; i++)
	{
		currentStateArr[i] = malloc(sizeof(CurrentState));
		currentStateArr[i]->nextIndex = -999;
	}

	while (fscanf(fileStates, "%d %c %d", &index, &(cs.letter), &(cs.nextIndex)) != EOF)
	{

		if (currentStateArr[index] != NULL && currentStateArr[index]->nextIndex == -999)
		{
			currentStateArr[index] = malloc(sizeof(CurrentState));
			currentStateArr[index]->letter = cs.letter;
			currentStateArr[index]->nextIndex = cs.nextIndex;
			currentStateArr[index]->csptr = cs.csptr;
		}


		else
		{
			ptr = currentStateArr[index];
			while (ptr->csptr != NULL && ptr->csptr != GARBAGE)
				ptr = ptr->csptr;

			ptr->csptr = malloc(sizeof(CurrentState));
			ptr->csptr->letter = cs.letter;
			ptr->csptr->nextIndex = cs.nextIndex;
			ptr->csptr->csptr = NULL;
		}

	}

	fclose(fileStates);
	//free(currentStateArr);
	//free(pointer->csptr->csptr);
	return 0;
}
//פונקציה שיוצרת רשימה של טוקנים 
void ListOfTokens(char* value, char* nameToken, int index)
{
	FILE* writeFile = NULL;

	tokenPtr = malloc(sizeof(Token));
	if (tokenPtr == NULL)
	{
		printf("Error allocating memory for tokenPtr\n");
		exit(1);
	}

	token1 = malloc(sizeof(Token));
	if (token1 == NULL)
	{
		printf("Error allocating memory for token1\n");
		exit(1);
	}
	tokenPtr = token1;

	token1->value = value;
	token1->nameToken = nameToken;
	token1->index = index;

	token1->next = NULL;
	if (tokenPtr != NULL && tokenPtr != GARBAGE)

		tokenPtr->next = token1;
	else
		*headList = tokenPtr;



	writeFile = fopen("C:/Users/User/Desktop/compilerProject/myTokens.txt", "a");

	if (writeFile == NULL)
	{
		printf("error in the file tokens.txt \n");
		exit(1);
	}
	fprintf(writeFile, " %s %s \n", value, nameToken);
	fclose(writeFile);
}
//פונקצית מעבר על האוטומט לפי המילה המתקבלת
void overTheWord(char* word)
{
	int i = 0, w = DEGEL, degel = DEGEL, j;
	while (cs.nextIndex <= NUM_STATES && cs.nextIndex >= 0 && word[w] != '\0')

	{
		//if(currentStateArr[i]!= 0x0000000000000000)
		cs = *currentStateArr[i];
		while (cs.csptr != NULL && ((int)cs.letter != (int)word[w]))
			cs = *(cs.csptr);

		w++;

		j = i;
		i = cs.nextIndex;

	}
	//חיפוש בטבלת מצבים סופיים אם הגענו למצב סופי

	degel = findToken(&j, &word[0]);
	if (!degel)
	{

		ListOfTokens(word, "TOK_ID", DEGEL);

		return 1;



	}



}

void fillMat()
{
	FILE* file = NULL;

	//יצירת מטריצה עבור בדיקה של ביטויים חשבוניים אם הם מורכבים מ2 תווים ברצף והוצאת הטוקן המתאים
	int num;
	int rows = 0, cols;
	file = fopen("C:/Users/User/Desktop/compilerProject/mat.txt", "r");
	if (file == NULL)
	{
		printf("error in the file mat.txt \n");
		exit(1);
	}
	while (fscanf(file, "%d", &num) == 1 && rows < row) {
		cols = 0;
		mat[rows][cols] = num;
		cols++;

		// Continue reading numbers from the same row
		while (fscanf(file, "%d", &num) == 1 && cols < column) {
			mat[rows][cols] = num;
			cols++;
		}

		rows++;
	}

	fclose(file); // Close the file
}
void fillSpecialTavArr()
{
	FILE* file;
	int index = 0;

	file = fopen("C:/Users/User/Desktop/compilerProject/specialTavs.txt", "r"); // Open the file in read mode

	if (file == NULL) {
		printf("Error opening file.\n");
		return 1;
	}

	// Read characters from the file and store them in the array
	while ((characters[index] = fgetc(file)) != EOF && index < specialTavArr) {
		index++;
	}

	characters[index] = '\0'; // Add null terminator at the end

	fclose(file); // Close the file

}
void fillDuplicateTavs() {


	FILE* file;
	int index = 0;

	file = fopen("C:/Users/User/Desktop/compilerProject/duplicateCharacters.txt", "r"); // Open the file in read mode

	if (file == NULL) {
		printf("Error opening file.\n");
		return 1;
	}

	// Read values from the file and store them in the array of structures
	while (fscanf(file, "%s %d", dataArray[index].str, &dataArray[index].num) == 2 && index < MAX_SIZE) {
		index++;
	}

	fclose(file); // Close the file

}

//פונקציה ראשית לניהול הניתוח הלקסיקלי
void lexicalAnalysis()
{
	int degel = NO_ERROR;

	FILE* file = NULL;

	automate();
	FillEndStatesArr();

	fillMat();
	fillSpecialTavArr();
	fillDuplicateTavs();



	char tav;
	int size = NO_ERROR;

	char* word = malloc(size);
	if (word == NULL) {
		perror("Error allocating memory");
		return 1;
	}
	headList = malloc(sizeof(Token*));
	if (headList == NULL) {
		perror("Error allocating memory");
		return 1;
	}

	file = fopen("C:/Users/User/Desktop/compilerProject/text.txt", "r");
	if (file == NULL)
	{
		printf("error in the file text.txt \n");
		exit(1);
	}

	tav = fgetc(file);
	while (tav != EOF)
	{

		size++;
		for (int i = 0, j = 0; i < specialTavArr; i++)

			if (characters[i] == tav)
			{


				if (size != 0) {
					word = realloc(word, size + 1);
					word[size] = '\0';
					overTheWord(word);

					word = NULL;
				}
				while (tav != ' ' && i < row && j < column)
				{
					if (characters[j] == peek(file)) {
						word = realloc(word, 2);
						word[0] = tav;
						word[1] = fgetc(file);

						ListOfTokens(word, dataArray[mat[i][j]].str, dataArray[mat[i][j]].num);
						word = NULL;
						degel = 1;
					}

					j++;
				}

				if (!degel)
					overTheWord(&tav);

				size = 0;
			}


		if (size)
		{
			word = realloc(word, size);
			word[size - 1] = tav;

		}

		tav = fgetc(file);
	}
	if (word) {
		word = realloc(word, size + 1);
		word[size] = '\0';
		overTheWord(word);
		free(word);
	}
	fclose(file);

	free(word);
	// משתמשת בזה בתחביריfree(headList);
	ListOfTokens('$', "dollar", dollarValue);
}


