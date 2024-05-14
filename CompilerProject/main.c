#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>



#include "../SemanticProject/semanticAnalyzer.c"



void main()
{
	lexicalAnalysis();
	semanticAnalysis(syntactAnalysis());
}
