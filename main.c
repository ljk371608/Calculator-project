#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

int findFirstIns(char *string, char *key){
	int len_string = strlen(string);
	int len_key = strlen(key);
	char win[len_key + 1];
	int i, j;
	for (i = 0; i < len_string - len_key + 1; i++){
		for (j = 0; j < len_key; j++){
			win[j] = *(string + i + j);
		}
		//win[j + 1] = NULL;
		if (strcmp(win, key) == 0){
			return i;
		}
	}
	return -1;
}

int ContentsOfFirstPr(char *string, char* content){
	
	int len_string = strlen(string);
	int i,s = 0, firstOpen = 0, firstOpenIndex, closed;
	for (i = 0; i < len_string; i++){
		if (*(string + i) == 40){
			s ++; 
			if (firstOpen == 0){firstOpenIndex = i;}
			firstOpen = 1;
		}
		if (*(string + i) == 41){
			s --;
		}
		if (s == 0 && firstOpen == 1){
			closed = i;
			break;
		}
	}
	strncpy(content, string + firstOpenIndex + 1, closed - firstOpenIndex - 1);
	return 1;
}
int indices_split(char *string, char *key, int *result){
	int len_string = strlen(string);
	int len_key = strlen(key);
	int *indices;
	char window[len_key];
	int i, j=0;
	for (i = 0; i < len_string - len_key+1; i ++){
		strncpy(window, string + i, len_key);
		if (strcmp(window, key) == 0){
			*(result + j) = i;
			j++;
		}
	}
	return j;
}
int replace_first_ins(char* string, char* key, char* target){
	int len_string = strlen(string);
	int len_key = strlen(key);
	int len_target = strlen(target);

	int i, index = findFirstIns(string, key);
	if (index == -1){
		return -1;
	}

	char after[len_string - len_key - index + 1] ;
	strncpy(after, string + index + len_key, len_string - len_key - index);
	//after[len_string - len_key - index] = NULL;

	for (i = index; i < index + len_target; i ++){
		*(string + i) = *(target + i - index);
	}
	for (i = index + len_target; i < len_string + len_target - len_key; i++){
		*(string + i) = after[i - index - len_target];
	}

	return 0;

}
int replace(char *string, char *key, char* target){
	while (findFirstIns(string, key) != -1){
		replace_first_ins(string, key, target);
	}
	return 0;
}
int count(char *string, char *key){
	int len_string = strlen(string);
	int len_key = strlen(key);
	int i, j, s = 0;
	char temp[len_key];
	for (i = 0; i < len_string - len_key ; i++){
		for (j = i; j < i + len_key; j++){
			temp[j - i] = *(string + j);
		}//printf("%s\n", temp);
		if (strcmp(temp, key) == 0){
			s ++;
		}
	}
	return s;
}

int isnumber(char *string){
	int len_string = strlen(string);
	int i;
	int neg = 0;
	for (i = 0; i < len_string; i ++){
		if (!((48<=*(string + i) && *(string + i) <= 57) || (*(string+i) == 46) || (*(string+i) == 45))){
			return 0;
		}
		if (*(string+i) == 45){neg = 1;}
		
	}
	if ((count(string, ".") > 1) || *(string) == 46){
		return 0;
	}
	if ((neg == 1) && (*(string) != 45)){
		return 0;
	}
	if (count(string, "-") > 1){
		return 0;
	}
	
	return 1;
}
double evalBaseExpr(char *string){
	
	if (isnumber(string) == 1){
		double n;
		sscanf(string, "%lf", &n);
		return n;
	}
	else {
		replace(string, "--", "+");
		if (findFirstIns(string, "(") != -1){
			char *content=(char *)malloc(100 * (sizeof("c")));
			char *content2 = (char *)malloc(100 * (sizeof("c")));
			char *num = (char *)malloc(100 * (sizeof("c")));
			
			ContentsOfFirstPr(string, content);
			strcpy(content2, content);
			double n = evalBaseExpr(content);
			sprintf(num, "%lf", n);
			char new_string[200];
			sprintf(new_string, "(%s)", content2);
			replace(string, new_string, num);
			//printf("string : %s\n", string);
			char k[200];strcpy(k, string);
			return evalBaseExpr(string);

		}
		else{
			if (findFirstIns(string, "+") != -1){
				int len_string = strlen(string);
				
				int result[100];
				int len_result = indices_split(string, "+", result);
				printf("l : %d\n", len_result);
				char window[100];
				double s = 0;
				int i;
				for (i = 0; i < len_result + 1; i++){
					if (i == 0){
						strncpy(window, string, result[i]);
						printf("1win : %s\n", window);
						s += evalBaseExpr(window);
					}
					else if( i == len_result){
						strncpy(window, string + result[i - 1] + 1, len_string - result[i - 1] - 1);
						printf("3win : %s\n", window);
						s += evalBaseExpr(window);
					}
					else{
						strncpy(window, string + result[i - 1] + 1, result[i] - result[i - 1] - 1);
						printf("i : %d\n", i);
						printf("2win : %s\n", window);
						s += evalBaseExpr(window);
					}
				}
				return s;

			}
			else if (findFirstIns(string, "-") != -1 && *(string) != 45){
				
			}
			else if (findFirstIns(string, "*") != -1){
				
			}
			
			
		}
	}
}
double eval(char *string){
	if (isnumber(string) == 1){
		double n;
		sscanf(string, "%lf", &n);
		return n;
	}
	else{
		
	}
}
int main(){
	char a[300] = "2+3+(4+5)";
	int b[400];
	printf("%lf\n", evalBaseExpr(a));
	
	
}