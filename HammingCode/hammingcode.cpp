#include <math.h>
#include <stdio.h>
#include <string.h>
  
int store_ham_code[32];
int input[32];
int calc_ith_posn_bit(int, int);
void calc_hamming_code(int input[], int);
  
int calc_ith_posn_bit(int position, int c_l)
{
    int count = 0, i, j;
    i = position - 1;
  
    while (i < c_l) {
  
        for (j = i; j < i + position; j++) {
  
            if (store_ham_code[j] == 1)
                count++;
        }
  
        i = i + 2 * position;
    }
  
    if (count % 2 == 0)
        return 0;
    else
        return 1;
}
  
void calc_hamming_code(int input[], int n)
{
    int i, count = 0, count_c, j, k;
    i = 0;
  
    while (n > (int)pow(2, i) - (i + 1)) {
        count++;
        i++;
    }
  
    count_c = count + n;
  
    j = k = 0;
  
    for (i = 0; i < count_c; i++) {
  
        if (i == ((int)pow(2, k) - 1)) {
            store_ham_code[i] = 0;
            k++;
        }
  
        else {
            store_ham_code[i] = input[j];
            j++;
        }
    }
  
    for (i = 0; i < count; i++) {
  
        int position = (int)pow(2, i);
  
        int value = calc_ith_posn_bit(position, count_c);
  
        store_ham_code[position - 1] = value;
    }
  
    printf("\nGenerating Hamming Code Word is: ");
    for (i = 0; i < count_c; i++) {
        printf("%d", store_ham_code[i]);
    }
}
 
int main()
{
	char msg[4];
	printf("\nEnter a 4 character message bit:");
	scanf("%s",msg);
	for(int i=0; i<4; i++){
		input[i]=msg[i]-'0';
	}
    
  
    int N = 4;
  
    calc_hamming_code(input, N);
    return 0;
}
