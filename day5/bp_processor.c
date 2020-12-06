#include <math.h>
#include <stdio.h>

/*parse an individual boarding pass code*/
void parsebp(char* bp)
{ 
	/* Binary pariotiioning is equal to binary conversion*/
	/* Most significant bit first */
	
	int row_nbr = 0;
	char row[7] = {bp[0], bp[1], bp[2], bp[3], bp[4], bp[5], bp[6]};
	for(int i = 0; i<7; i++){
		 if(row[i] == 'B'){
		 	row_nbr += pow(2, (6-i));
		 }
	}

	int col_nbr = 0; 
	char col[3] = {bp[7], bp[8], bp[9]};
	for (int i = 0; i<3; i++){
		if(col[i] == 'L'){
			col_nbr += pow(2,(2-i)); 
		}
	}
    int place_id = row_nbr * 8 + col_nbr; 
	printf("row: %i , col %i  , place id: %i ;\n", row_nbr, col_nbr, place_id); 
}

int main() {

FILE *input = fopen("bp.txt", "r");

if(input == NULL)
{
	printf("File could not be opened");
	return 1; 
}

int file_size = 0; 
fseek (input , 0 , SEEK_END);
file_size = ftell (input);
rewind (input);

printf("File size %i \n", file_size); 

char * line; 
size_t length; 
ssize_t read; 

while ((read = getline(&line, &length, input)) != -1) {
    parsebp(line);
}

fclose(input);
return 0;
}
