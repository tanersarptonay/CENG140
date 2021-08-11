#include <stdio.h>
#include <stdlib.h>



/* Some string helper functions */
int strlength(char* str)
{
	char *p = NULL;
	int length;
	for (p=str, length=0 ; *p ; p++)
	{
		length += 1;
	}
	return length;
}
void strcopy(char* main, char* copy)
{
	char *m;
	char *c;

	for (m=main, c=copy ; *m ; m++)
	{
		*(c++) = *m;
	}
	*c = '\0';
}
void strdel(int start_index, int end_index, char* str)
{
	/* deletes start_index to end_index of a string */
	/* strdel(3, 6, "123456789") ==> "126789"      */
	char *s = str;
	char *copy = NULL;
	int i, j;

	copy = (char*) malloc(strlength(str)+1);
	if (copy==NULL)
	{
		printf("ERROR: copy is not allocated - strdel\n");
		exit(0);
	}
	
	strcopy(str, copy);

	for (i=start_index, j=end_index ; copy[j] ; i++)
	{
		s[i] = copy[j++];
	}
	s[i] = '\0';

	free(copy);
}
void strreplace(int start_index, int end_index, char* sub_string, char* main_str)
{
	/* Replaces the sub_string with the given gap of the main_str */
	/* strreplace(3, 6, "(ABCDEFGH)", "0123456789") ===> main_str = 012(ABCDEFGH)6789 */
	char *sub = sub_string;
	char *main = main_str;
	char *safe = NULL;
	int main_len;
	int i, j, k=0;

	strdel(start_index, end_index, main_str);
	main_len = strlength(main_str);
	safe = (char*) malloc(main_len + 1);
	if (safe==NULL) printf("ERROR: safe is not allocated - strreplace\n");
	else
	{
		strcopy(main_str, safe);
		if (strlength(main_str) == start_index)
		{
			for (i=start_index, j=start_index ; safe[j-1] ; i++)
			{
				if (sub[k])
				{
					main[i] = sub[k++];
				}
				else
				{
					main[i] = safe[j++];
				}
			}
		}
		else
		{
			for (i=start_index, j=start_index ; safe[j] ; i++)
			{
				if (sub[k])
				{
					main[i] = sub[k++];
				}
				else
				{
					main[i] = safe[j++];
				}
			}
		}
		main[i] = '\0';
	}
	free(safe);
}
void strappend(char* sub_string, char* main_str)
{
	int len = strlength(main_str);
	strreplace(len,len,sub_string,main_str);
}

/* Helper functions for 2-D char arrays */
int strarrlength(char strarr[256][256])
{
	int length=0 , i;

	for (i=0 ; strarr[i][0] ; i++)
	{
		length += 1;
	}
	return length;
}
void strarrappend(char* str, char strarr[256][256])
{
	int length = strarrlength(strarr), i;
    for(i=0 ; str[i] ; i++)
    {
        strarr[length][i] = str[i];
    }
	strarr[++length][0] = '\0';
	strarr[length][1] = '\0';
	
}
void derivativeclean(char derivative[256][256])
{
	/* Cleans the unused derivatives from the derivative stack  */
	int i, j;
	int length = strarrlength(derivative);

	if (length >= 3)
	{
		for (i=0 ; derivative[length-1][i] ; i++)
		{
			derivative[length-3][i] = derivative[length-1][i];
		}
		derivative[length-3][i] = '\0';
		derivative[length-2][0] = '\0';
		derivative[length-1][0] = '\0';
		printf("cleaned...\n");
	}
}

void whitespace_remover(char* a)
{
	/* removes all whitespace from the infix */
	char *b = malloc(strlength(a)+1);
	char *new = b;
	char *old = a;
	
	if (b == NULL)
	{
		printf("ERROR: Memory not allocated in whitespace_remover");
		exit(0);
	}
	while (*old)
	{
		if (*old != ' ') *(new++) = *old;
		old += 1;
	}

	new = b;
	while (*(new) != '\0')
	{
		*(a++) = *(new++);
	}
	*a = '\0';

	free(b);
}


int if_operator_itp(char token) 
{
	/* Cheks if the token is a operator for infix to postfix function*/
	if (token=='+' || token=='-' || token=='*' || token=='/' || token=='^' || token=='(' || token==')') return 1;
	else return 0;
}
int if_operator(char token) 
{
	/* Cheks if the token is a operator */
	if (token=='+' || token=='-' || token=='*' || token=='/' || token=='^') return 1;
	else return 0;
}

int element_finder(char item, char array[7][7])
{
	/* Finds the index number of a token for the function infix_to_postfix */
	int i;
	for (i=0 ; i<7 ; ++i)
	{
		if (array[0][i] == item) return i;    
	}
	printf("ERROR: element_finder\n");
	exit(0);
	return -1;
}

/* Helper functions for stacks */
int isempty(char* stack, int* top)
{
	if (*top == -1) return 1;
	else return 0;
}
int pop(char* stack, int* top)
{
	int to_pop;
	if (isempty(stack, top) == 0)
	{
		to_pop = *(stack + *top);
		*top -= 1;
		return to_pop;
	}
	else 
	{
		printf("ERROR: Stack is empty\n");
		exit(0);
		return -1;
	}
}
void push(char to_push, char* stack, int* top)
{
	*top += 1;
	stack[*top] = to_push;
	stack[*top + 1] = '\0';
}
char top_data(char* stack)
{
	return stack[strlength(stack)-1];
}


void infix_to_postfix(char* whole_op, int length, char* postfix)
{
	/* tan = t , sin = s , ln = l , ch = c , sh = h */
	char *stack = malloc(128 * sizeof(char));
	int i=0, j=0;
	int *top = (int*) malloc(sizeof(int));
	char pre[7][7] = {{'(', ')', '+', '-', '*', '/', '^'},
					  {'#', '0', '1', '1', '2', '2', '3'}};

	char assoc[7][7] = {{'(', ')', '+', '-', '*', '/', '^'},
						{'n', 'n', 'l', 'l', 'l', 'l', 'r'}};

	if (top == NULL) 
	{
		printf("ERROR: The pointer top isn't allocated.\n");
		exit(0);
	}
	*top = -1;
	
	/*  ASCII, ) = 41, * = 42, + = 43, - = 45, / = 47, ^ = 94   */
	
	while (i < length)
	{
		if (if_operator_itp(whole_op[i]) == 0)
		{
			label:
			/* if the token is not a operator nor parenthesis */
			if ((whole_op[i] == 'l' && whole_op[i+1] == 'n') || (whole_op[i+1] == 'h'))
			{
				/* if the token is ln, sh or ch */
				if (whole_op[i] == 'l') postfix[j++] = 'l';
				else if (whole_op[i] == 's') postfix[j++] = 'h';
				else if (whole_op[i] == 'c') postfix[j++] = 'm';
				i += 2;
				if (if_operator_itp(whole_op[i]) == 0) goto label;
			}
			if ((whole_op[i] == 's' && whole_op[i+2] == 'n') || (whole_op[i] == 't' && whole_op[i+2] == 'n'))
			{
				/* if the token is sin or tan */
				if (whole_op[i] == 's') postfix[j++] = 's';
				else if (whole_op[i] == 't') postfix[j++] = 't';
				i += 3;
				if (if_operator_itp(whole_op[i]) == 0) goto label;
			}
			if (whole_op[i] >='0' && whole_op[i] <= '9')
			{
				while (whole_op[i] >='0' && whole_op[i] <= '9')
				{
					postfix[j++] = whole_op[i++];
				}
				if (if_operator_itp(whole_op[i]) == 0) goto label;
			}
			if ( (whole_op[i] >= 'A' && whole_op[i] <= 'Z') || (whole_op[i] >= 'a' && whole_op[i] <= 'z') )
			{
				postfix[j++] = whole_op[i++];
				if (if_operator_itp(whole_op[i]) == 0) goto label;
			}
			postfix[j++] = ' ';
		}
				
		else
		{
			/* If is not a function nor a number */
			if (whole_op[i] == '(')
			{
				push(whole_op[i], stack, top);
			}
			else if (whole_op[i] == ')')
			{
				while (pre[1][element_finder(whole_op[i],pre)] < pre[1][element_finder(stack[*top],pre)])
				{
					postfix[j] = stack[*top];
					postfix[j+1] = ' ';
					pop(stack, top);
					j += 2;
				}
				if (pre[1][element_finder(whole_op[i],pre)] > pre[1][element_finder(stack[*top],pre)])
				{
					pop(stack, top);
				}
			}
			
			else
			{
				/* If the token is an operator */

				if ( (isempty(stack,top) == 0) && (pre[1][element_finder(whole_op[i],pre)] < pre[1][element_finder(stack[*top],pre)]) )
				{
					while ((isempty(stack,top) == 0) && (pre[1][element_finder(whole_op[i],pre)] < pre[1][element_finder(stack[*top],pre)]))        
					{
						postfix[j] = stack[*top];
						pop(stack, top);
						postfix[j+1] = ' ';
						j += 2;
					}
				}
				if ( (isempty(stack,top) == 0) && (pre[1][element_finder(whole_op[i],pre)] == pre[1][element_finder(stack[*top],pre)]) )
				{
					if ((assoc[1][element_finder(whole_op[i],assoc)] == 'l') && (assoc[1][element_finder(stack[*top],assoc)] == 'l'))
					{
						while ( (isempty(stack,top) == 0) && (assoc[1][element_finder(stack[*top],assoc)] == 'l') && (pre[1][element_finder(whole_op[i],pre)] == pre[1][element_finder(stack[*top],pre)]) )
						{
							postfix[j] = stack[*top];
							pop(stack, top);
							postfix[j+1] = ' ';
							j += 2;
						}
					push(whole_op[i], stack, top);
					}
				}
				if ( (isempty(stack,top) == 0) && (pre[1][element_finder(whole_op[i],pre)] > pre[1][element_finder(stack[*top],pre)]) )
				{			
					push(whole_op[i], stack, top);
				}
				if (  isempty(stack,top) == 1 )
				{
					push(whole_op[i], stack, top);
				}
			}  
			i += 1;  
		}
	}

	while (isempty(stack,top) == 0)
	{
		postfix[j++] = stack[*top];
		postfix[j++] = ' ';
		pop(stack, top);
	}
	
	free(top);
	free(stack);
}

char* basic_derivative(char* exp, char* der_arr)
{   
	char *p = der_arr;

	if (*exp =='X') /* if the operand is X */
	{
		*(p++)='1';
	}
	else if (*exp>='0' && *exp<='9') /* if the operand is a number*/
	{
		*(p++)='0';
	}
	else if (*exp == 's') /* if the operand is sin */
	{
		*(p++) = 'c';
	}
	else if (*exp == 't') /* if the operand is tan */
	{
		*(p++) = '(';
		*(p++) = 't';
		*(p++) = '^'; *(p++) = '2';
		*(p++) = '+'; *(p++) = '1';
		*(p++)=')';
	}
	else if (*exp == 'l') /* if the operand is ln */
	{
		*(p++) = '(';
		*(p++) = '1';
		*(p++) = '/';
		*(p++) = 'X';
		*(p++)=')';
	}
	else if (*exp == 'h') /* if the operand is sh */
	{
		*(p++) = 'm';
	}
	else if (*exp == 'm') /* if the operand is ch */
	{
		*(p++) = 'h';
	}

	
	*(p++)='\0'; *(p++)='\0'; *(p++)='\0'; *(p++)='\0';
	return der_arr;
}

void basic_op_derivative(char* operation, char derivative[256][256])
{
	/* Creates a pointer containing the derivaive and adds that pointer to the stack */
	char* op = operation;
	char first[128];
	char second[128];
	char first_der[128];
	char sec_der[128];
	char new_exp[5];
	char operator;
	int space_count=0, i=0, j=0, exp;
	int length;
	char *temp = NULL;

	
	
	for (op = operation ; space_count<2 ; op++)
	{
		
		if (*op == ' ')
		{
			space_count += 1;
			continue;
		}
		else if (space_count==0)
		{
			first[i++] = *op;
		}
		
		else if (space_count==1)
		{
			second[j++] = *op;
		}
	}
	
	first[i++] = '\0';
	second[j++] = '\0';
	operator = *op;


	if (operator == '^')
	{
		temp = malloc(128 * sizeof(char));
		*temp = '\0'; *(temp+1) = '\0'; *(temp+2) = '\0';
		*(temp+3) = '\0'; *(temp+4) = '\0'; *(temp+5) = '\0';
		length = strlength(temp);
		exp = atoi(second);
		if (first[0] == 'X')
		{
			temp[length] = '(';
			for (i=0 ; second[i] ; i++)
			{
				temp[length+1+i] = second[i];
			}
			length += i-1;
			temp[length+2] = '*';
			temp[length+3] = 'X';
			if (exp-1 == 1) 
			{
				temp[length+4] = ')';
			}
			else if (exp<10)
			{
				temp[length+4] = '^';
				temp[length+5] = (char) (exp - 1 + '0');
				temp[length+6] = ')';
			}
			else if (exp>=10)
			{
				sprintf(new_exp, "%d", exp-1);
				temp[length+4] = '^';
				for (i=0 ; new_exp[i] ; i++)
				{
					temp[length+5+i] = new_exp[i];
				}
				length += i-1;
				temp[length+6] = ')';

			}
		}
		else if (first[0]>='a' && first[0]<='z')
		{
			/* if the first element is a function */
			basic_derivative(first, first_der);
			temp[length] = '(';
			length = strlength(temp);
			for (i=0 ; first_der[i] ; i++)
			{
				temp[length+i] = first_der[i];
			}
			length = strlength(temp);
			temp[length] = '*';
			for (i=0 ; second[i] ; i++)
			{
				temp[length+1+i] = second[i];
			}
			length += i-1;
			temp[length+2] = '*';
			temp[length+3] = first[0];
			if ((exp - 1) == 1) 
			{
				temp[length+4] = ')';
			}
			else if (exp<10)
			{
				temp[length+4] = '^';
				temp[length+5] = (char) (exp - 1 + '0');
				temp[length+6] = ')';
			}
			else if (exp>=10)
			{
				sprintf(new_exp, "%d", exp-1);
				temp[length+4] = '^';
				for (i=0 ; new_exp[i] ; i++)
				{
					temp[length+5+i] = new_exp[i];
				}
				length += i-1;
				temp[length+6] = ')';
			}
		}
		else if (first[0]=='(')
		{
			if ((exp-1) == 1)
			{
				sprintf(temp, "(%s*%s*%s)", derivative[strarrlength(derivative)-1], second, first);
			}
			else if (exp < 10)
			{
				sprintf(temp, "(%s*%s*%s^%c)", derivative[strarrlength(derivative)-1], second, first, (char)(exp - 1 + '0'));
			}
			else if (exp >= 10)
			{
				sprintf(new_exp, "%d", exp-1);
				sprintf(temp, "(%s*%s*%s^", derivative[strarrlength(derivative)-1], second, first);
				length = strlength(temp);
				for (i=0 ; new_exp[i] ; i++)
				{
					temp[length+i] = new_exp[i];
				}
				temp[length+i] = ')';
				temp[length+i+1] = '\0';
			}
		}
		printf("TEMPPP: %s\n", temp);
		strarrappend(temp, derivative);
		length = strlength(temp);
		derivative[strarrlength(derivative)-1][length] = '\0';
		free(temp);
	}
	else
	{
		basic_derivative(first, first_der);
		basic_derivative(second, sec_der);
		if (first[0] != '(')
		{
			printf("in basic-op der1: %s\n", first_der);
			strarrappend(first_der, derivative);
			length = strlength(first_der);
			derivative[strarrlength(derivative)-1][length] = '\0';
		}
		
		
		if (second[0] != '(')
		{
			printf("in basic-op der2: %s\n", sec_der);
			printf("in basic-op| derivative: ");
			for (i=0 ; derivative[i][0] ; i++)
			{
				printf("%s ", derivative[i]);
			}
			printf("\n");
			strarrappend(sec_der, derivative);
			length = strlength(sec_der);
			derivative[strarrlength(derivative)-1][length] = '\0';
			printf("in basic-op| derivative: ");
			for (i=0 ; derivative[i][0] ; i++)
			{
				printf("%s ", derivative[i]);
			}
			printf("\n");
		}
	}
	
}

char* derive(int index, char* postfix, char derivative[256][256], char* first, char* second, char operator)
{
	int space_1=0, space_2=0, i=0, j=0, k=0;
	int space_count=0, len = strarrlength(derivative), strlen1, strlen2;
	char *post_p = postfix;
	char first_der[128];
	char sec_der[128];
	char infix[260];
	char derfix[260];
	int expprblm, exp_len=0, eleman_number=0, exp_num, flag=0;
	char exp_str[10], new_second[128];
	
	
	if (strlength(postfix) == 2)
	{
		basic_derivative(postfix, derivative[0]);
		return derivative[0];
	}
	
	if (postfix[0]=='(' && postfix[strlength(postfix)-2]==')')
	{   
		/* if the whole expression is differientiated */
		printf("ZUUUU\n");
		if (derivative[len-1][0]=='(')
		{
			strlen1 = strlength(derivative[len-1]);
			strdel(strlen1-1, strlen1, derivative[len-1]);
			strdel(0,1, derivative[len-1]);
		}
		return derivative[len-1];
	}

	else if (postfix[index] == ' ')
	{
		return derive(index+1, post_p, derivative, first, second, operator);
	}

	else if (index!=0 && postfix[index-1]!=' ')
	{
		return derive(index+1, post_p, derivative, first, second, operator);
	}

	printf("index: %d\n", index);
	printf("postfix: %s\n", post_p);
	printf("derivative: ");
	for (i=0 ; derivative[i][0] ; i++)
	{
		printf("%s ", derivative[i]);
	}
	printf("\n");
	
	for (k=index,i=0,j=0 ; space_count<2 ; k++)
	{
		if (postfix[k]==' ')
		{
			if (space_1==0) space_1=k;
			else if (space_2==0) space_2=k;
			space_count += 1;
			continue;
		}
		else if (space_count==0)
		{
			first[i++] = postfix[k];
		}
		else if (space_count==1)
		{
			second[j++] = postfix[k];
		}
	}
	first[i] = '\0';
	second[j] = '\0';
	operator = postfix[k];
	post_p = postfix;
	
	if (if_operator(operator) == 0)
	{
		return derive(index+1, postfix, derivative, first, second, operator);
	}
	printf("first: %s\nsecond: %s\noperator: %c\n", first, second, operator);

	if (operator == '^')
	{
		printf("space_1: %d\nspace_2: %d\n",space_1, space_2 );
		basic_op_derivative(post_p+index, derivative);
		printf("new derivative: ");
		for (i=0 ; derivative[i][0] ; i++)
		{
			printf("%s ", derivative[i]);
		}
		printf("\n");
		sprintf(infix, "(%s^%s)", first, second);
		strreplace(index, space_2+2, infix, postfix);
		printf("\n");
		return derive(0,postfix, derivative, first, second, operator);
		
	}
	else if (operator == '*')
	{
		basic_op_derivative(post_p+index, derivative);
		sprintf(infix, "(%s*%s)",first, second);

		printf("new derivative: ");
		for (i=0 ; derivative[i][0] ; i++)
		{
			printf("%s  ", derivative[i]);
		}
		printf("\n");
		len = strarrlength(derivative);
		strreplace(index, space_2+2, infix, postfix);
		
		if ( (derivative[len-2][0]=='0' && !derivative[len-2][1]) || (second[0]=='0' && !second[1]) )
		{sprintf(infix,"(%s*%s)",first, derivative[len-1]);}
		else if ( (derivative[len-1][0]=='0' && !derivative[len-1][1]) || (first[0]=='0' && !first[1]) )
		{sprintf(infix,"(%s*%s)",derivative[len-2], first);}
		else {sprintf(infix,"(%s*%s+%s*%s)",derivative[len-2], second, first, derivative[len-1]);}

		strarrappend(infix, derivative);
		printf("new derivative: ");
		for (i=0 ; derivative[i][0] ; i++)
		{
			printf("%s  ", derivative[i]);
		}
		printf("\n");
		derivativeclean(derivative);
		printf("anew derivative: ");
		for (i=0 ; derivative[i][0] ; i++)
		{
			printf("%s  ", derivative[i]);
		}
		printf("\n\n");
		return derive(0, postfix, derivative, first, second, operator);
	}
	else if (operator == '/')
	{
		basic_op_derivative(post_p+index, derivative);
		sprintf(infix, "(%s/%s)", first, second);

		printf("new derivative: ");
		for (i=0 ; derivative[i][0] ; i++)
		{
			printf("%s  ", derivative[i]);
		}
		printf("\n");
		len = strarrlength(derivative);
		strreplace(index, space_2+2, infix, postfix);
		printf("firstder: %s\nsecder: %s\n", derivative[len-2], derivative[len-1]);

		
		exp_len = strlength(second);
		printf("EXP_LEN: %d\n", exp_len);
		for (i=0 ; second[i] ; i++)
		{
			if ( second[i]=='^' && ((exp_len-i) <= 4) )
			{	
				flag = 1;
				if (exp_len-i==3)
				{
					
					exp_num = (int) (second[i+1] - '0');
					sprintf(exp_str, "%d", exp_num*2);
					break;
				}
				else if (exp_len-i==4 || exp_len-i==5)
				{
					
					for (j=i ; j<exp_len+i ; j++)
					{
						exp_str[j-i] = second[j];
					}
					exp_str[j-i] = '\0';
					exp_num = atoi(exp_str);
					sprintf(exp_str, "%d\n", exp_num*2);
					break;
				}

			}
		}
		if (flag==1)
		{
			strcopy(second, new_second);
			strreplace(i+1, exp_len, exp_str, new_second);
			exp_len = strlength(new_second);
			new_second[exp_len++] = ')';
			new_second[exp_len++] = '\0';
			printf("second- exnum: %s\n", new_second);
		}
		
		
		
		if (first[0]=='(' && second[0]=='(')
		{	
			if (flag==0) sprintf(infix, "((%s*%s-%s*%s)/(%s^2))", derivative[len-2], second, first, derivative[len-1], second);
			else sprintf(infix, "((%s*%s-%s*%s)/%s)", derivative[len-2], second, first, derivative[len-1], new_second);
			
		}
		else if (second[0]=='(')
		{
			
			if (flag==0) sprintf(infix, "((%s*%s-%s*%s)/(%s^2))", derivative[len-1], second, first, derivative[len-2], second);
			else sprintf(infix, "((%s*%s-%s*%s)/%s)", derivative[len-1], second, first, derivative[len-2], new_second);
			
		}
		else
		{
			if (flag==0) sprintf(infix, "((%s*%s-%s*%s)/(%s^2))", derivative[len-2], second, first, derivative[len-1], second);
			else sprintf(infix, "((%s*%s-%s*%s)/%s)", derivative[len-2], second, first, derivative[len-1], new_second);
		}


		printf("deriv: %s\n", infix);
		strarrappend(infix, derivative);
		printf("new derivative: ");
		for (i=0 ; derivative[i][0] ; i++)
		{
			printf("%s  ", derivative[i]);
		}
		printf("\n");
		derivativeclean(derivative);
		printf("anew derivative: ");
		for (i=0 ; derivative[i][0] ; i++)
		{
			printf("%s  ", derivative[i]);
		}
		printf("\n\n");

		return derive(0, postfix, derivative, first, second, operator);

	}
	else 
	{	
		/* if the operator is + - or don't exist */
		if (first[0] == '(')
		{
			sprintf(infix, "(%s%c%s)", first, operator, second);
			printf("sprintf infix: %s\n",infix);
			basic_op_derivative(postfix+index, derivative);
			printf("derivative: ");
			for (i=0 ; derivative[i][0] ; i++)
			{
				printf("%s ", derivative[i]);
			}
			printf("\n");

			strreplace(index, space_2+2, infix, postfix);

			printf("new derivative: ");
			for (i=0 ; derivative[i][0] ; i++)
			{
				printf("%s  ", derivative[i]);
			}
			printf("\n");
			len = strarrlength(derivative);

			
		
			
			{
				/* if both of the expressions are differientiated */
				if (derivative[len-2][0]=='0' && operator=='+') sprintf(infix, "%s", derivative[len-1]);
				else if (derivative[len-2][0]=='0' && operator=='-') sprintf(infix, "-%s", derivative[len-1]);
				else if (derivative[len-1][0]=='0') sprintf(infix, "%s", derivative[len-2]);
				else sprintf(infix, "(%s%c%s)", derivative[len-2], operator, derivative[len-1]);
				
			}

			{
				/* only the first expression is differientiated */ /*
				if (derivative[len-1][0]=='0' && operator=='+') sprintf(infix, "%s", derivative[len-2]);
				else if (derivative[len-1][0]=='0' && operator=='-') sprintf(infix, "-%s", derivative[len-2]);
				else if (derivative[len-2][0]=='0') sprintf(infix, "%s", derivative[len-1]);
				else sprintf(infix, "(%s%c%s)", derivative[len-1], operator, derivative[len-2]); */
			}
			
			

			strarrappend(infix, derivative);

			printf("Anew derivative: ");
			for (i=0 ; derivative[i][0] ; i++)
			{
				printf("%s  ", derivative[i]);
			}
			printf("\n");
			
		}
		else if(first[0] != '(')
		{
			printf("space_1: %d\nspace_2: %d\n",space_1, space_2 );
			basic_op_derivative(postfix+index, derivative);
			printf("derivative: ");
			for (i=0 ; derivative[i][0] ; i++)
			{
				printf("%s ", derivative[i]);
			}
			printf("\n");
			
			len = strarrlength(derivative);

			for (i=0 ; derivative[len-2][i] ; i++)
			{
				first_der[i] = derivative[len-2][i];
			}
			first_der[i] = '\0';
			for (i=0 ; derivative[len-1][i] ; i++)
			{
				sec_der[i] = derivative[len-1][i];
			}
			sec_der[i] = '\0';
		
			printf("first_der: %s\nsec_der: %s\n", first_der,sec_der);

			if (second[0]!='(')
			{
				/* if only the second expression is differentiated */
				if (first_der[0]=='0' && operator=='+') sprintf(derfix, "(%s)", sec_der);
				else if (first_der[0]=='0' && operator=='-') sprintf(derfix, "(-%s)", sec_der);
				else if (sec_der[0]=='0') sprintf(derfix, "(%s)", first_der);
				else sprintf(derfix, "(%s%c%s)", first_der, operator, sec_der);
			}
			else
			{
				/* if none of the expressions are differientiated */
				if (sec_der[0]=='0' && operator=='+') sprintf(derfix, "(%s)", first_der);
				else if (sec_der[0]=='0' && operator=='-') sprintf(derfix, "(-%s)", first_der);
				else if (first_der[0]=='0') sprintf(derfix, "(%s)", sec_der);
				else sprintf(derfix, "(%s%c%s)", sec_der, operator, first_der);
			}
			strarrappend(derfix, derivative);
			infix[0] = '\0';
			printf("derivative: ");
			for (i=0 ; derivative[i][0] ; i++)
			{
				printf("%s ", derivative[i]);
			}
			printf("\n");
			sprintf(infix, "(%s%c%s)", first, operator, second);
			
			strreplace(index, space_2+2, infix, postfix);
			

			printf("post: %s\n", postfix);
	
		}
		derivativeclean(derivative);
		printf("anew derivative: ");
		for (i=0 ; derivative[i][0] ; i++)
		{
			printf("%s  ", derivative[i]);
		}
		printf("\n\n");
		return derive(0, postfix, derivative, first, second, operator);
	}

}

char* token_to_function(int index ,char* derivative)
{
	/* changes tokens to correct string forms */
	/* t==>tan | c==>cos | s==>sin | l==>ln | h==>sh | m==>ch */
	int length = strlength(derivative);
	char *t="tan", *c="cos", *s="sin", *l="ln", *h="sh", *m="ch";


	if (length==1 && derivative[0]>='0' && derivative[0]<='1')
	{
		return derivative;
	}

	if ((length>1) && (index >= length-1))
	{
		return derivative;
	}
	
	if (derivative[index]=='t' && derivative[index+1] != 'a')
	{
		strreplace(index, index+1, t, derivative);
		return token_to_function(0, derivative);
	}
	else if (derivative[index]=='c' && derivative[index+1] != 'o' && derivative[index+1] != 'h')
	{
		if (length>1) strreplace(index, index+1, c, derivative);
		else
		{
			strreplace(index, index+2, c, derivative);
			derivative[index+3] = '\0';
		}
		return token_to_function(0, derivative);
	}
	else if (derivative[index]=='s' && derivative[index+1] != 'i' && derivative[index+1] != 'h' && derivative[index-1]!='o' && derivative[index-1]!='s')
	{
		if (length>1) strreplace(index, index+1, s, derivative);
		else
		{
			strreplace(index, index+2, s, derivative);
			derivative[index+3] = '\0';
		}
		return token_to_function(0, derivative);
	}
	else if (derivative[index]=='l' && derivative[index+1] != 'n')
	{
		if (length>1) strreplace(index, index+1, l, derivative);
		else
		{
			strreplace(index, index+2, l, derivative);
			derivative[index+2] = '\0';
		}
		return token_to_function(0, derivative);
		return token_to_function(0, derivative);
	}
	else if (derivative[index]=='h' && derivative[index+1] != 'i' && derivative[index+1] != 'h' && derivative[index-1] != 'c' && derivative[index-1] != 's')
	{
		if (length>1) strreplace(index, index+1, h, derivative);
		else
		{
			strreplace(index, index+2, h, derivative);
			derivative[index+2] = '\0';
		}
		return token_to_function(0, derivative);
	}
	else if (derivative[index]=='m' && derivative[index+1] != 'o' && derivative[index-1] != 's')
	{
		if (length>1) strreplace(index, index+1, m, derivative);
		else
		{
			strreplace(index, index+2, m, derivative);
			derivative[index+2] = '\0';
		}
		return token_to_function(0, derivative);
	}
	else
	{
		return token_to_function(index+1, derivative);
	}
}

char* exponent_reducer_postfix(int index ,char* postfix)
{
	char exp1_int, exp2_int, *op=NULL;
	int i=0,j=0, k=0, m=0, space_count=0;
	char exp1[10], exp2[10], op1[10], op2[10];
	int new_exp_int; 
	char new_exp[10], new_exp_digits[10];
	int space_indexes[10], *s=NULL;
	int length = strlength(postfix);
	int exp_num=0;
	s = space_indexes;
	

	if (index==0)
	{
		for (i=0 ; postfix[i] && strlength(postfix)>i+4 ; i++)
		{
			if (postfix[i] == '^' && postfix[i+4]=='^')
			{
				exp_num += 2;
			}
			if (exp_num>=2) break;
		}
		if (exp_num<2)
		{
			return postfix;
		}
	}


	printf("index: %d\nPostfix: %s\n\n",index, postfix);

	if (index == length)
	{
		return postfix;
	}
	
	else if (length < 7)
	{
		return postfix;
	}


	for (op = (postfix+index) ; space_count<4 ; op++)
	{
		
		if (*op == ' ')
		{
			space_count += 1;
			*(s++) = op-postfix;
			continue;
		}
		else if (space_count==0)
		{
			exp1[i++] = *op;
		}
		
		else if (space_count==1)
		{
			op1[j++] = *op;
		}

		else if (space_count==2)
		{
			exp2[k++] = *op;
		}
		else if (space_count==3)
		{
			op2[m++] = *op;
		}
	}
	*(s++) = op-postfix;
	exp1[i++]= '\0';
	op1[j++] = '\0';
	exp2[k++] = '\0';
	op2[m++] = '\0';
	exp1_int = atoi(exp1);
	exp2_int = atoi(exp2);

	if (exp1_int>=1 && exp1_int<=100 && exp2_int>=1 && exp2_int<=100 && op1[0]=='^' && op2[0]=='^')
	{
		new_exp_int = exp1_int * exp2_int;
		if (new_exp_int<10)
		{
			new_exp_digits[0] = (char) (new_exp_int + '0');
			new_exp_digits[1] = '\0';
		}
		else
		{
			sprintf(new_exp, "%d", new_exp_int);
			for (i=0 ; new_exp[i] ; i++)
			{
				new_exp_digits[i] = new_exp[i];
			}
			new_exp_digits[i] = '\0';
		}
		strreplace(index, space_indexes[2], new_exp_digits, postfix);
		return exponent_reducer_postfix(0, postfix);
	}
	else
	{
		return exponent_reducer_postfix(index+1, postfix);
	}

	/*
	if (postfix[i]>='0' && postfix[i]<='9' && postfix[i+2]=='^' && postfix[i+4]>='0' && postfix[i+4]<='9' && postfix[i+6]=='^')
	{
		exp1 = atoi(postfix)
	}
	*/
}

char* product_reducer_postfix(int index, char* postfix)
{
	char pr1_int, pr2_int, *op=NULL;
	int i=0,j=0, k=0, m=0, space_count=0;
	char pr1[10], pr2[10], op1[10], op2[10];
	int new_pr_int; 
	char new_pr[10], new_pr_digits[10];
	int space_indexes[10], *s=NULL;
	int length = strlength(postfix);
	int pr_num=0;
	s = space_indexes;

	if (index==0)
	{
		for (i=0 ; postfix[i] && strlength(postfix)>i+6 ; i++)
		{
			if (postfix[i] == '*' && postfix[i+4]=='*' && (postfix[i+2]>='A' && postfix[i+2]<='z') && postfix[i+4]=='*' && (postfix[i+6]>='A' && postfix[i+6]<='z'))


			if (postfix[i] == '*' && postfix[i+4]=='*')
			{
				pr_num += 2;
			}

			if (pr_num>=2) break;
		}
		if (pr_num<2)
		{
			return postfix;
		}
	}
	
	if (index == length)
	{
		return postfix;
	}
	
	for (op = (postfix+index) ; space_count<4 ; op++)
	{
		if (*op == ' ')
		{
			space_count += 1;
			*(s++) = op-postfix;
			continue;
		}
		else if (space_count==0)
		{
			pr1[i++] = *op;
		}
	
		else if (space_count==1)
		{
			op1[j++] = *op;
		}

		else if (space_count==2)
		{
			pr2[k++] = *op;
		}
		else if (space_count==3)
		{
			op2[m++] = *op;
		}
	}
	*(s++) = op-postfix;
	pr1[i++]= '\0';
	op1[j++] = '\0';
	pr2[k++] = '\0';
	op2[m++] = '\0';
	pr1_int = atoi(pr1);
	pr2_int = atoi(pr2);

	if (pr1[0]>='0' && pr1[0]<='9' && pr2[0]>='0' && pr2[0]<='9' && pr1_int>=0 && pr1_int<=10000 && pr2_int>=0 && pr2_int<=10000 && op1[0]=='*' && op2[0]=='*')
	{
		new_pr_int = pr1_int * pr2_int;
		if (new_pr_int<10)
		{
			new_pr_digits[0] = (char) (new_pr_int + '0');
			new_pr_digits[1] = '\0';
		}
		else
		{
			sprintf(new_pr, "%d", new_pr_int);
			for (i=0 ; new_pr[i] ; i++)
			{
				new_pr_digits[i] = new_pr[i];
			}
			new_pr_digits[i] = '\0';
		}
		strreplace(index, space_indexes[2], new_pr_digits, postfix);
		return product_reducer_postfix(0, postfix);
	}
	else
	{
		return product_reducer_postfix(index+1, postfix);
	}
}


int main()
{
	char whole_op[256]= "X*X*(X+tan)*X*X", c;
	/* tan cos sin ln sh ch  */
	/* t   c   s   l  h  m   */
	char postfix[256] = "\0";
	int length, i=0;
	char derivative[256][256];
	char first[128], second[128];
	char operator = 0;

	derivative[0][0] = '\0';
	/*
	whole_op = malloc(128 * sizeof(char));
	while (c != EOF)
  	{
		c = getc(stdin);
		if (c != ' ')
		{
			whole_op[i] = c;
			whole_op[i+1] = '\0';
			i += 1;
		}

  	}
  	whole_op[i-1] = '\0';
	if (whole_op[i-2]=='\n') whole_op[i-2]='\0';
	*/

	whitespace_remover(whole_op);
	length = strlength(whole_op);

	printf("\nINFIX: %s\n", whole_op);
	infix_to_postfix(whole_op, length, postfix);
	printf("POSTFIX: %s\n", postfix);

	exponent_reducer_postfix(0, postfix);
	printf("NEW POSTFIX: %s\n\n", postfix);

	

	
	
	printf("________________________________________\nThe Final Derivative: %s\n", derive(0, postfix, derivative, first, second, operator));

	
	token_to_function(i, derivative[strarrlength(derivative)-1]);

	printf("\n%s\n\n", derivative[strarrlength(derivative)-1]);
	



	
	return 0;
}

/*
Some test cases:

sin/((ch^2)^2)^2


(cos*(((ch^2)^2)^2)-sin*(((sh*2*ch)*2*(ch^2))*2*((ch^2)^2)))/((((ch^2)^2)^2)^2)

(cos*(ch^8)-sin*(sh*8*ch^7))/((ch^8)^2)

(cos*(ch^8)-sin*(sh*8*ch^7))/(ch^16)
*/

/*
(((1*X+X*1)*(X+tan)+(X*X)*(1+(tan^2+1)))*X+((X*X)*(X+tan))*1)*X+(((X*X)*(X+tan))*X)*1

X
*/



/*
X/(ln-sin/X)
(1*(ln-(sin/X))-X*((1/X)-((cos*X-sin*1)/(X^2))))/((ln-(sin/X))^2)


*/

/* 
X/(tan^2-1)-ln^2
((1*((tan^2)-1)-X*((tan^2+1)*2*tan))/(((tan^2)-1)^2))-((1/X)*2*ln)


*/

/*
(X^2-1)*tan-ln^2/X
((2*X)*tan+((X^2)-1)*(tan^2+1))-((((1/X)*2*ln)*X-(ln^2)*1)/(X^2))


(Xˆ2-1)*(tanˆ2+1)+2*X*tan+(2*ln*X-lnˆ2)/Xˆ2
*/

/*


(((1*X+X*1)*(X+tan)+(X*X)*(1+(tan^2+1)))*X+((X*X)*(X+tan))*1)*X+(((X*X)*(X+tan))*X)*1
(((1*X+X*1)*(X+tan)+(X*X)*(1+(tan^2+1)))*X+((X*X)*(X+tan))*1)*X+(((X*X)*(X+tan))*X)*1

*/
