-------------- Lexical Analysis ---------------


#include <stdio.h>
#include <string.h>

int isKeyword(char *lexeme)
{
    char keywords[][10] = {"void", "main", "int", "scanf", "printf"};
    int i, flag = 0;

    for (i = 0; i < sizeof(keywords) / sizeof(keywords[0]); i++)
    {
        if (strcmp(lexeme, keywords[i]) == 0)
        {
            flag = 1;
            break;
        }
    }
    return flag;
}

int main()
{
    char input[] = "void main()\n"
                   "{\n"
                   "   int c;\n"
                   "   scanf(\"%d\", &c);\n"
                   "   printf(\"%d\", c);\n"
                   "}\n";

    char *token = strtok(input, " \t\n()\";,{}");

    while (token != NULL)
    {
        if (strcmp(token, "void") == 0 || strcmp(token, "main") == 0 || strcmp(token, "int") == 0 || strcmp(token, "scanf") == 0 || strcmp(token, "printf") == 0)
        {
            printf("%s - keyword\n", token);
        }
        else if (token[0] == '(' || token[0] == ')' || token[0] == '"' || token[0] == ',' || token[0] == '{' || token[0] == '}')
        {
            printf("%s - special character\n", token);
        }
        else if (token[0] == '&' || token[0] == '%')
        {
            printf("%s - special character\n", token);
            token = strtok(NULL, " \t\n()\";,{}"); 
            
            printf("%s - format specifier\n", token);
        }
        else
        {
            printf("%s - identifier\n", token);
        }

        token = strtok(NULL, " \t\n()\";,{}");
    }

    return 0;
}

-------------- Epsilon closure ---------------

#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

void epsilonClosure(int state, int n, vector<vector<int>> &epsilonTransitions, vector<bool> &visited, unordered_set<int> &epsilonClosureSet)
{
    visited[state] = true;
    epsilonClosureSet.insert(state);
    for (int i = 0; i < epsilonTransitions[state].size(); ++i)
    {
        int nextState = epsilonTransitions[state][i];
        if (!visited[nextState])
        {
            epsilonClosure(nextState, n, epsilonTransitions, visited, epsilonClosureSet);
        }
    }
}

int main()
{
    int n; 
    cout << "Enter the number of states: ";
    cin >> n;
    vector<vector<int>> epsilonTransitions(n); 
    cout << "Enter the epsilon transitions~ \n\n";

    for (int i = 0; i < n; ++i)
    {
        int numTransitions;
        cout << "Enter the number of epsilon transitions for state " << i << ": ";
        cin >> numTransitions;

        if (numTransitions>0)
        {
            cout << "Enter epsilon transitions for state " << i << " (state indices separated by space): ";
        }

        for (int j = 0; j < numTransitions; ++j)
        {
            int nextState;
            cin >> nextState;
            epsilonTransitions[i].push_back(nextState);
        }
    } 

    for (int i = 0; i < n; ++i)
    {
        vector<bool> visited(n, false);
        unordered_set<int> epsilonClosureSet;
        epsilonClosure(i, n, epsilonTransitions, visited, epsilonClosureSet); 

        cout << "Epsilon closure of state " << i << ": { ";
        for (int state : epsilonClosureSet)
        {
            cout << state << " ";
        }
        cout << "}\n";
    }
    return 0;
}

--------------- Reg exp to NFA ---------------

#include <stdio.h>
#include <string.h>

int main()
{
	char reg[20];
	int q[20][3], i = 0, j = 1, len, a, b;

	for (a = 0; a < 20; a++)
		for (b = 0; b < 3; b++)
			q[a][b] = 0;
			
	printf("Enter Regular Expression: ");
	scanf("%s", reg);
	printf("\n");
	
	len = strlen(reg);
	while (i < len)
	{
		if (reg[i] == 'a' && reg[i + 1] != '|' && reg[i + 1] != '*')
		{
			q[j][0] = j + 1;
			j++;
		}
		if (reg[i] == 'b' && reg[i + 1] != '|' && reg[i + 1] != '*')
		{
			q[j][1] = j + 1;
			j++;
		}
		if (reg[i] == 'e' && reg[i + 1] != '|' && reg[i + 1] != '*')
		{
			q[j][2] = j + 1;
			j++;
		}
		if (reg[i] == 'a' && reg[i + 1] == '|' && reg[i + 2] == 'b')
		{
			q[j][2] = ((j + 1) * 10) + (j + 3);
			j++;
			q[j][0] = j + 1;
			j++;
			q[j][2] = j + 3;
			j++;
			q[j][1] = j + 1;
			j++;
			q[j][2] = j + 1;
			j++;
			i = i + 2;
		}
		if (reg[i] == 'b' && reg[i + 1] == '|' && reg[i + 2] == 'a')
		{
			q[j][2] = ((j + 1) * 10) + (j + 3);
			j++;
			q[j][1] = j + 1;
			j++;
			q[j][2] = j + 3;
			j++;
			q[j][0] = j + 1;
			j++;
			q[j][2] = j + 1;
			j++;
			i = i + 2;
		}
		if (reg[i] == 'a' && reg[i + 1] == '*')
		{
			q[j][2] = ((j + 1) * 10) + (j + 3);
			j++;
			q[j][0] = j + 1;
			j++;
			q[j][2] = ((j + 1) * 10) + (j - 1);
			j++;
		}
		if (reg[i] == 'b' && reg[i + 1] == '*')
		{
			q[j][2] = ((j + 1) * 10) + (j + 3);
			j++;
			q[j][1] = j + 1;
			j++;
			q[j][2] = ((j + 1) * 10) + (j - 1);
			j++;
		}
		if (reg[i] == ')' && reg[i + 1] == '*')
		{
			q[0][2] = ((j + 1) * 10) + 1;
			q[j][2] = ((j + 1) * 10) + 1;
			j++;
		}
		i++;
	}
	
	printf("Current State | Input | Possible Next States");

	for (i = 0; i <= j; i++)
	{
		if (q[i][0] != 0)
			printf("\n    q[%d]      |   a   |  q[%d]", i, q[i][0]);
		if (q[i][1] != 0)
			printf("\n    q[%d]      |   b   |  q[%d]", i, q[i][1]);
		if (q[i][2] != 0)
		{
			if (q[i][2] < 10)
				printf("\n    q[%d]      |   e   |  q[%d]", i, q[i][2]);
			else
				printf("\n    q[%d]      |   e   |  q[%d] , q[%d]", i, q[i][2] / 10, q[i][2] % 10);
		}
	}
	
	return 0;
}

--------------- LEX Program ---------------

lex a.lex
gcc lex.yy.c
./a.out

%{ 
#include <stdio.h> 
int vowel_count = 0; 
int consonant_count = 0; 
%} 
%% 
[aeiouAEIOU] { vowel_count++; } 
[a-zA-Z] { consonant_count++; } 
2 | Page 
 
. ; // ignore all other characters 
%% 
int main() { 
    char input[100]; // Assuming maximum input length is 100 characters 
    printf("Enter a string: "); 
    fgets(input, sizeof(input), stdin); // Read input from the terminal 
    yy_scan_string(input); // Pass the input string to the lexer 
    yylex(); // Perform lexical analysis 
    printf("\nNumber of vowels: %d\n", vowel_count); 
    printf("Number of consonants: %d\n", consonant_count); 
    return 0; 
} 
int yywrap(){return(1);} 


%{ 
#include <stdio.h> 
int keyword_count = 0; 
int identifier_count = 0; 
int digit_count = 0; 
%} 
%% 
"auto"|"break"|"case"|"char"|"const"|"continue"|"default"|"do"|"double
 "|"else"|"enum"|"extern"|"float"|"for"|"goto"|"if"|"int"|"long"|"register
 "|"return"|"short"|"signed"|"sizeof"|"static"|"struct"|"switch"|"typedef"|
 "union"|"unsigned"|"void"|"volatile"|"while"    { keyword_count++; } 
[a-zA-Z_][a-zA-Z0-9_]*     { identifier_count++; } 
[0-9]+                      { digit_count++; } 
.                           ; // ignore all other characters 
%% 
int main() { 
    char input[100]; // Assuming maximum input length is 100 characters 
    printf("Enter a string or sample C program: "); 
    fgets(input, sizeof(input), stdin); // Read input from the terminal 
    yy_scan_string(input); // Pass the input string to the lexer 
    yylex(); // Perform lexical analysis 
    printf("\nNumber of keywords: %d\n", keyword_count); 
    printf("Number of identifiers: %d\n", identifier_count); 
    printf("Number of digits: %d\n", digit_count); 
    return 0; 
} 
int yywrap(){return(1);}


%{ 
%} 
%% 
[a-z]+[.][a-z]+[2][0][2][1][@][v][i][t][s][t][u][d][e][n][t][.][a][c][.][i][n] { 
printf("\nValid VIT mail id\n"); 
return 0; 
} 
. {printf("\nInvalid VIT mail id\n");return 0;} 
%% 
int main(){ 
yylex(); 
return 0; 
} 
int yywrap(){} 


--------------- First Follow ---------------

(store in file)
->CA 
A->+CA|^ 
B->*DB|^ 
C->DB 
D->e|(S) 

#include <stdio.h>
#include <string.h>
#define MAX_SIZE 128

int table[100][MAX_SIZE];
char terminal[MAX_SIZE];
char nonterminal[26];

struct product
{
    char str[100];
    int len;
} pro[20];

int no_pro;
char first[26][MAX_SIZE];
char follow[26][MAX_SIZE];
char first_rhs[100][MAX_SIZE];

int isNT(char c)
{
    return c >= 'A' && c <= 'Z';
}

void readFromFile()
{
    FILE *fptr;
    fptr = fopen("text.txt", "r");
    char buffer[255];
    int i;
    int j;
    while (fgets(buffer, sizeof(buffer), fptr))
    {
        j = 0;
        nonterminal[buffer[0] - 'A'] = 1;
        for (i = 0; i < strlen(buffer) - 1; ++i)
        {
            if (buffer[i] == '|')
            {
                ++no_pro;
                pro[no_pro - 1].str[j] = '\0';
                pro[no_pro - 1].len = j;
                pro[no_pro].str[0] = pro[no_pro - 1].str[0];
                pro[no_pro].str[1] = pro[no_pro - 1].str[1];
                pro[no_pro].str[2] = pro[no_pro - 1].str[2];
                j = 3;
            }
            else
            {
                pro[no_pro].str[j] = buffer[i];
                ++j;
                if (!isNT(buffer[i]) && buffer[i] != '-' && buffer[i] != '>')
                {
                    terminal[buffer[i]] = 1;
                }
            }
        }
        pro[no_pro].len = j;
        ++no_pro;
    }
}

void add_FIRST_A_to_FOLLOW_B(char A, char B)
{
    int i;
    for (i = 0; i < MAX_SIZE; ++i)
    {
        if (i != '^')
            follow[B - 'A'][i] = follow[B - 'A'][i] || first[A - 'A'][i];
    }
}
void add_FOLLOW_A_to_FOLLOW_B(char A, char B)
{
    int i;
    for (i = 0; i < MAX_SIZE; ++i)
    {
        if (i != '^')
            follow[B - 'A'][i] = follow[B - 'A'][i] || follow[A - 'A'][i];
    }
}
void FOLLOW()
{
    int t = 0;
    int i, j, k, x;
    while (t++ < no_pro)
    {
        for (k = 0; k < 26; ++k)
        {
            if (!nonterminal[k])
                continue;
            char nt = k + 'A';
            for (i = 0; i < no_pro; ++i)
            {
                for (j = 3; j < pro[i].len; ++j)
                {
                    if (nt == pro[i].str[j])
                    {
                        for (x = j + 1; x < pro[i].len; ++x)
                        {
                            char sc = pro[i].str[x];
                            if (isNT(sc))
                            {
                                add_FIRST_A_to_FOLLOW_B(sc, nt);
                                if (first[sc - 'A']['^'])
                                    continue;
                            }
                            else
                            {
                                follow[nt - 'A'][sc] = 1;
                            }
                            break;
                        }
                        if (x == pro[i].len)
                            add_FOLLOW_A_to_FOLLOW_B(pro[i].str[0], nt);
                    }
                }
            }
        }
    }
}
void add_FIRST_A_to_FIRST_B(char A, char B)
{
    int i;
    for (i = 0; i < MAX_SIZE; ++i)
    {
        if (i != '^')
        {
            first[B - 'A'][i] = first[A - 'A'][i] || first[B - 'A'][i];
        }
    }
}
void FIRST()
{
    int i, j;
    int t = 0;
    while (t < no_pro)
    {
        for (i = 0; i < no_pro; ++i)
        {
            for (j = 3; j < pro[i].len; ++j)
            {
                char sc = pro[i].str[j];
                if (isNT(sc))
                {
                    add_FIRST_A_to_FIRST_B(sc, pro[i].str[0]);
                    if (first[sc - 'A']['^'])
                        continue;
                }
                else
                {
                    first[pro[i].str[0] - 'A'][sc] = 1;
                }
                break;
            }
            if (j == pro[i].len)
                first[pro[i].str[0] - 'A']['^'] = 1;
        }
        ++t;
    }
}
void add_FIRST_A_to_FIRST_RHS__B(char A, int B)
{
    int i;
    for (i = 0; i < MAX_SIZE; ++i)
    {
        if (i != '^')
            first_rhs[B][i] = first[A - 'A'][i] || first_rhs[B][i];
    }
}

void FIRST_RHS()
{
    int i, j;
    int t = 0;
    while (t < no_pro)
    {
        for (i = 0; i < no_pro; ++i)
        {
            for (j = 3; j < pro[i].len; ++j)
            {
                char sc = pro[i].str[j];
                if (isNT(sc))
                {
                    add_FIRST_A_to_FIRST_RHS__B(sc, i);
                    if (first[sc - 'A']['^'])
                        continue;
                }
                else
                {
                    first_rhs[i][sc] = 1;
                }
                break;
            }
            if (j == pro[i].len)
                first_rhs[i]['^'] = 1;
        }
        ++t;
    }
}

int main()
{
    readFromFile();
    follow[pro[0].str[0] - 'A']['$'] = 1;
    FIRST();
    FOLLOW();
    FIRST_RHS();
    int i, j, k;

    printf("\n");
    for (i = 0; i < no_pro; ++i)
    {
        if (i == 0 || (pro[i - 1].str[0] != pro[i].str[0]))
        {
            char c = pro[i].str[0];
            printf("FIRST OF %c: ", c);
            for (j = 0; j < MAX_SIZE; ++j)
            {
                if (first[c - 'A'][j])
                {
                    printf("%c ", j);
                }
            }
            printf("\n");
        }
    }

    printf("\n");
    for (i = 0; i < no_pro; ++i)
    {
        if (i == 0 || (pro[i - 1].str[0] != pro[i].str[0]))
        {
            char c = pro[i].str[0];
            printf("FOLLOW OF %c: ", c);
            for (j = 0; j < MAX_SIZE; ++j)
            {
                if (follow[c - 'A'][j])
                {
                    printf("%c ", j);
                }
            }
            printf("\n");
        }
    }

    terminal['$'] = 1;
    terminal['^'] = 0;

    printf("\n");
    printf("\n\t Predictive Parser Table \n");
    printf("\n");
    printf("%-10s", "");
    for (i = 0; i < MAX_SIZE; ++i)
    {
        if (terminal[i])
            printf("%-10c", i);
    }
    printf("\n");
    int p = 0;
    for (i = 0; i < no_pro; ++i)
    {
        if (i != 0 && (pro[i].str[0] != pro[i - 1].str[0]))
            p = p + 1;
        for (j = 0; j < MAX_SIZE; ++j)
        {
            if (first_rhs[i][j] && j != '^')
            {
                table[p][j] = i + 1;
            }
            else if (first_rhs[i]['^'])
            {
                for (k = 0; k < MAX_SIZE; ++k)
                {
                    if (follow[pro[i].str[0] - 'A'][k])
                    {
                        table[p][k] = i + 1;
                    }
                }
            }
        }
    }
    k = 0;
    for (i = 0; i < no_pro; ++i)
    {
        if (i == 0 || (pro[i - 1].str[0] != pro[i].str[0]))
        {
            printf("%-10c", pro[i].str[0]);
            for (j = 0; j < MAX_SIZE; ++j)
            {
                if (table[k][j])
                {
                    printf("%-10s", pro[table[k][j] - 1].str);
                }
                else if (terminal[j])
                {
                    printf("%-10s", "");
                }
            }
            ++k;
            printf("\n");
        }
    }
}


--------------- Left Recursion ---------------

S->Sa| Sb| c | epsilon 

#include<stdio.h>  
#include<string.h>  
#define SIZE 10  

int main () {  
    char non_terminal;  
    char beta,alpha;  
    int num;  
    char production[10][SIZE];  
    int index=3; /* starting of the string following "->" */  
     printf("Enter Number of Production : ");  
     scanf("%d",&num);  
     printf("Enter the grammar: ");  
     for(int i=0;i<num;i++){  
          scanf("%s",production[i]);  
     }  
     for(int i=0;i<num;i++){  
          printf("\n Given Grammar \n%s\n ", production[i]);  
          non_terminal=production[i][0];  
          if(non_terminal==production[i][index]) {  
               alpha=production[i][index+1];  
               printf(" is left recursive.\n");  
               while(production[i][index]!=0 && production[i][index]!='|')  
                    index++;  
               if(production[i][index]!=0) {  
                    beta=production[i][index+1];  
                    printf("Grammar without left recursion:\n");  
                    printf("%c->%c%c\'",non_terminal,beta,non_terminal);  
                    printf("\n%c\'->%c%c\'|E\n",non_terminal,alpha,non_terminal);  
               }  
               else  
                    printf(" can't be reduced\n");  
          }  
          else  
               printf(" is not left recursive.\n");  
          index=3;  
     }  
}   

--------------- Left Factoring ---------------

S → iEtS / iEtSeS / a 
E → b 

#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
void main()
{
	char ch,lhs[20][20],rhs[20][20][20],temp[20],temp1[20];
	int n,n1,count[20],x,y,i,j,k,c[20];
	printf("\nEnter the no. of nonterminals : ");
	scanf("%d",&n);
	n1=n;
	for(i=0;i<n;i++)
	{
		printf("\nNonterminal %d \nEnter the no. of productions : ",i+1);
		scanf("%d",&c[i]);
		printf("\nEnter LHS : ");
		scanf("%s",lhs[i]);
		for(j=0;j<c[i];j++)
		{
			printf("%s->",lhs[i]);
			scanf("%s",rhs[i][j]);
		}
	}
	for(i=0;i<n;i++)
	{
		count[i]=1;
		while(memcmp(rhs[i][0],rhs[i][1],count[i])==0)
			count[i]++;
	}
	for(i=0;i<n;i++)
	{
		count[i]--;
		if(count[i]>0)
		{
			strcpy(lhs[n1],lhs[i]);
			strcat(lhs[i],"'");
			for(k=0;k<count[i];k++)
				temp1[k] = rhs[i][0][k];
			temp1[k++] = '\0';
			for(j=0;j<c[i];j++)
			{
				for(k=count[i],x=0;k<strlen(rhs[i][j]);x++,k++)
					temp[x] = rhs[i][j][k];
				temp[x++] = '\0';
				if(strlen(rhs[i][j])==1)
					strcpy(rhs[n1][1],rhs[i][j]);
				strcpy(rhs[i][j],temp);
			}
			c[n1]=2;
			strcpy(rhs[n1][0],temp1);
			strcat(rhs[n1][0],lhs[n1]);
			strcat(rhs[n1][0],"'");
			n1++;
		}
	}
	printf("\n\nThe resulting productions are : \n");
	for(i=0;i<n1;i++)
	{
		if(i==0)
			printf("\n %s -> %c|",lhs[i],(char)238);
		else
			printf("\n %s -> ",lhs[i]);
		for(j=0;j<c[i];j++)
		{
			printf(" %s ",rhs[i][j]);
			if((j+1)!=c[i])
				printf("|");
		}
		printf("\b\b\b\n");
	}
}

--------------- SR Parser ---------------

E->E+E 
E->E*E 
E->a

#include <stdio.h>
#include <string.h>

struct ProductionRule
{
    char left[10];
    char right[10];
};

int main()
{
    char input[20], stack[50], temp[50], ch[2], *token1, *token2, *substring;
    int i, j, stack_length, substring_length, stack_top, rule_count = 0;
    struct ProductionRule rules[10];

    stack[0] = '\0';

    // User input for the number of production rules
    printf("\nEnter the number of production rules: ");
    scanf("%d", &rule_count);

    // User input for each production rule in the form 'left->right'
    printf("\nEnter the production rules (in the form 'left->right'): \n");
    for (i = 0; i < rule_count; i++)
    {
        scanf("%s", temp);
        token1 = strtok(temp, "->");
        token2 = strtok(NULL, "->");
        strcpy(rules[i].left, token1);
        strcpy(rules[i].right, token2);
    }

    // User input for the input string
    printf("\nEnter the input string: ");
    scanf("%s", input);
    printf("\n\nState\tInput\tAction\n");

    i = 0;
    while (1)
    {
        // If there are more characters in the input string, add the next character to the stack
        if (i < strlen(input))
        {
            ch[0] = input[i];
            ch[1] = '\0';
            i++;
            int k;
            strcat(stack, ch);
            printf("$%s\t", stack);
            for (k = i; k < strlen(input); k++)
            {
                 printf("%c$", input[k]);
            }
            if (k==0)
            {
            	printf("$");
            }
            printf("\tShift %s\n", ch);
        }
        
        // Iterate through the production rules
        for (j = 0; j < rule_count; j++)
        {
            // Check if the right-hand side of the production rule matches a substring in the stack
            substring = strstr(stack, rules[j].right);
            if (substring != NULL)
            {
                // Replace the matched substring with the left-hand side of the production rule
                stack_length = strlen(stack);
                substring_length = strlen(substring);
                stack_top = stack_length - substring_length;
                stack[stack_top] = '\0';
                strcat(stack, rules[j].left);
                printf("$%s\t", stack);
                for (int k = i; k < strlen(input); k++)
                {
                    printf("%c$", input[k]);
                }
                printf("\tReduce %s->%s\n", rules[j].left, rules[j].right);
                j = -1; // Restart the loop to ensure immediate reduction of the newly derived production rule
            }
        }

        // Check if the stack contains only the start symbol and if the entire input string has been processed
        if (strcmp(stack, rules[0].left) == 0 && i == strlen(input))
        {
            printf("\nAccepted\n");
            break;
        }

        // Check if the entire input string has been processed but the stack doesn't match the start symbol
        if (i == strlen(input))
        {
            printf("\nNot Accepted\n");
            break;
        }
    }

    return 0;
}


--------------- Leading Trailing ---------------

Enter the no. of variables : 3 
Enter the variables : E, T, F 
Enter the no. of terminals : 5 
Enter the terminals : ), (, *, +, i 
 
Enter the no. of production of E:2 
E->E+T 
E->T 
Enter the no. of production of T:2 
T->T*F 
T->F 
Enter the no. of production of F:2 
F->(E) 
F->i 


#include<iostream>
#include<conio.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
using namespace std;

int vars,terms,i,j,k,m,rep,count,temp=-1;
char var[10],term[10],lead[10][10],trail[10][10];
struct grammar
{	
	int prodno;
	char lhs,rhs[20][20];
}gram[50];
void get()
{
	cout<<"\nLEADING AND TRAILING\n";
	cout<<"\nEnter the no. of variables : ";
	cin>>vars;
	cout<<"\nEnter the variables : \n";
	for(i=0;i<vars;i++)
	{
		cin>>gram[i].lhs;
		var[i]=gram[i].lhs;
	}
	cout<<"\nEnter the no. of terminals : ";
	cin>>terms;
	cout<<"\nEnter the terminals : ";
	for(j=0;j<terms;j++)
		cin>>term[j];
	cout<<"\nPRODUCTION DETAILS\n";
	for(i=0;i<vars;i++)
	{
		cout<<"\nEnter the no. of production of "<<gram[i].lhs<<":";
		cin>>gram[i].prodno;
		for(j=0;j<gram[i].prodno;j++)
		{
			cout<<gram[i].lhs<<"->";
			cin>>gram[i].rhs[j];
		}
	}
}
void leading()
{
	for(i=0;i<vars;i++)
	{
		for(j=0;j<gram[i].prodno;j++)
		{
			for(k=0;k<terms;k++)
			{
				if(gram[i].rhs[j][0]==term[k])
					lead[i][k]=1;
				else
				{
					if(gram[i].rhs[j][1]==term[k])
						lead[i][k]=1;
				}
			}
		}
	}
	for(rep=0;rep<vars;rep++)
	{
		for(i=0;i<vars;i++)
		{
			for(j=0;j<gram[i].prodno;j++)
			{
				for(m=1;m<vars;m++)
				{
					if(gram[i].rhs[j][0]==var[m])
					{
						temp=m;
						goto out;
					}
				}
				out:
				for(k=0;k<terms;k++)
				{
					if(lead[temp][k]==1)
						lead[i][k]=1;
				}
			}
		}
	}
}
void trailing()
{
	for(i=0;i<vars;i++)
	{
		for(j=0;j<gram[i].prodno;j++)
		{
			count=0;
			while(gram[i].rhs[j][count]!='\x0')
				count++;
			for(k=0;k<terms;k++)
			{
				if(gram[i].rhs[j][count-1]==term[k])
					trail[i][k]=1;
				else
				{
					if(gram[i].rhs[j][count-2]==term[k])
						trail[i][k]=1;
				}
			}
		}
	}
	for(rep=0;rep<vars;rep++)
	{
		for(i=0;i<vars;i++)
		{
			for(j=0;j<gram[i].prodno;j++)
			{
				count=0;
				while(gram[i].rhs[j][count]!='\x0')
					count++;
				for(m=1;m<vars;m++)
				{
					if(gram[i].rhs[j][count-1]==var[m])
						temp=m;
				}
				for(k=0;k<terms;k++)
				{
					if(trail[temp][k]==1)
						trail[i][k]=1;
				}
			}
		}
	}
}
void display()
{
	for(i=0;i<vars;i++)
	{
		cout<<"\nLEADING("<<gram[i].lhs<<") = ";
		for(j=0;j<terms;j++)
		{
			if(lead[i][j]==1)
				cout<<term[j]<<",";
		}
	}
	cout<<endl;
	for(i=0;i<vars;i++)
	{
		cout<<"\nTRAILING("<<gram[i].lhs<<") = ";
		for(j=0;j<terms;j++)
		{
			if(trail[i][j]==1)
				cout<<term[j]<<",";
		}
	}
}
int main()
{

	get();
	leading();
	trailing();
	display();

}

---------------  Intermediate Code Generation ---------------

out = in1 + in2 + in3


#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

struct three
{
    char data[10], temp[7];
} s[30];
void main()
{
    char d1[7], d2[7] = "t";
    int i = 0, j = 1, len = 0;
    FILE *f1, *f2;
    f1 = fopen("sum.txt", "r");
    f2 = fopen("out.txt", "w");
    while (fscanf(f1, "%s", s[len].data) != EOF)
        len++;
    itoa(j, d1, 7);
    strcat(d2, d1);
    strcpy(s[j].temp, d2);
    strcpy(d1, "");
    strcpy(d2, "t");
    if (!strcmp(s[3].data, "+"))
    {
        fprintf(f2, "%s=%s+%s", s[j].temp, s[i + 2].data, s[i + 4].data);
        j++;
    }
    else if (!strcmp(s[3].data, "-"))
    {
        fprintf(f2, "%s=%s-%s", s[j].temp, s[i + 2].data, s[i + 4].data);
        j++;
    }
    for (i = 4; i < len - 2; i += 2)
    {
        itoa(j, d1, 7);
        strcat(d2, d1);
        strcpy(s[j].temp, d2);
        if (!strcmp(s[i + 1].data, "+"))
            fprintf(f2, "\n%s=%s+%s", s[j].temp, s[j - 1].temp, s[i + 2].data);
        else if (!strcmp(s[i + 1].data, "-"))
            fprintf(f2, "\n%s=%s-%s", s[j].temp, s[j - 1].temp, s[i + 2].data);
        strcpy(d1, "");
        strcpy(d2, "t");
        j++;
    }
    fprintf(f2, "\n%s=%s", s[0].data, s[j - 1].temp);
    fclose(f1);
    fclose(f2);
}



--------------- Infix to prefix ---------------
a+b

#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <conio.h>
#define SIZE 50

char s[SIZE];
int top = -1;
int s1[SIZE];
int top1 = -1;
void push1(int elem)
{
    s1[++top1] = elem;
}
int pop2()
{
    return (s1[top1--]);
}
void push(char elem)
{
    s[++top] = elem;
}
char pop()
{
    return (s[top--]);
}
int pr(char elem)
{
    switch (elem)
    {
    case '#':
        return 0;
    case ')':
        return 1;
    case '+':
    case '-':
        return 2;
    case '*':
    case '/':
        return 3;
    }
    return 0;
}
void prefix(char *infx, char *prfx)
{
    int i = 0, k = 0;
    char ch, elem;
    push('#');
    strrev(infx);
    while ((ch = infx[i++]) != '\0')
    {
        if (ch == ')')
            push(ch);
        else if (isalnum(ch))
            prfx[k++] = ch;
        else if (ch == '(')
        {
            while (s[top] != ')')
                prfx[k++] = pop();
            top--;
        }
        else
        {
            while (pr(s[top]) >= pr(ch))
                prfx[k++] = pop();
            push(ch);
        }
    }
    while (s[top] != '#')
        prfx[k++] = pop();
    prfx[k] = '\0';
    strrev(prfx);
    strrev(infx);
    printf("\nPrefix Expression: %s\n", prfx);
}
void caddress(char *prfx)
{
    int i, j = 0, k = 0, l = 0;
    char op1, op2;
    for (i = strlen(prfx) - 1; i >= 0; --i)
        if (prfx[i] != '+' && prfx[i] != '-' && prfx[i] != '*' && prfx[i] != '/' && prfx[i] != '=')
            push(prfx[i]);
        else
        {
            k = 0;
            l = 0;
            ++j;
            op1 = pop();
            op2 = pop();

            if (op1 == '$')
                k = pop2();
            if (op2 == '$')
                l = pop2();
            if (k == 0 && l == 0)
                printf("t%d=%c%c%c \n", j, op1, prfx[i], op2);
            if (k != 0 && l == 0)
                printf("t%d=t%d%c%c \n", j, k, prfx[i], op2);
            if (l != 0 && k == 0)
                printf("t%d=%c%ct%d \n", j, op1, prfx[i], l);
            if (l != 0 && k != 0)
                printf("t%d=t%d%ct%d \n ", j, k, prfx[i], l);

            push('$');
            push1(j);
        }
}
int main()
{
    char infx[50], prfx[50];
    printf("\nEnter the Infix Expression: ");
    scanf("%s", infx);
    prefix(infx, prfx);
    // printf("\n3-address code is:\n");
    // caddress(prfx);
    return 0;
}



--------------- Infix to postfix ---------------

a+b 

#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#define SIZE 400

char s[SIZE];
int top = -1;
void push(char elem)
{
    s[++top] = elem;
}
char pop()
{
    return (s[top--]);
}
int pr(char elem)
{
    switch (elem)
    {
    case '#':
        return 0;
    case '(':
        return 1;
    case '+':
    case '-':
        return 2;
    case '*':
    case '/':
        return 3;
    }
    return 0;
}
int main()
{

    char infx[400], pofx[400], ch;
    int i = 0, k = 0;
    printf("\n\nEnter the Infix Expression: ");
    scanf("%s", infx);
    push('#');
    while ((ch = infx[i++]) != '\0')
    {
        if (ch == '(')
            push(ch);
        else if (isalnum(ch))
            pofx[k++] = ch;
        else if (ch == ')')
        {
            while (s[top] != '(')
                pofx[k++] = pop();
            top--;
        }
        else
        {
            while (pr(s[top]) >= pr(ch))
                pofx[k++] = pop();
            push(ch);
        }
    }
    while (s[top] != '#')
        pofx[k++] = pop();
    pofx[k] = '\0';
    printf("Postfix Expression is:%s", pofx);

    return 0;
}

--------------- end ---------------