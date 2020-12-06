#include <math.h>
#include <stdio.h>

/*parse an individual boarding pass code*/
int parsebp(char* bp)
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
    return place_id; 
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

int max_boarding_id = 0;
int min_boarding_id = 1023;
//const int MAX_ID = 1023;
int boarding_checks[1023];

while ((read = getline(&line, &length, input)) != -1) {

    int boarding_id = parsebp(line);
    boarding_checks[boarding_id] = 1; 

    if(max_boarding_id < boarding_id){
        max_boarding_id = boarding_id; 
    }

    if(min_boarding_id > boarding_id){
        min_boarding_id = boarding_id;     
    }
}

printf("Largest boarding pass id: %i \n", max_boarding_id);
printf("Smallest boarding pass id: %i \n", min_boarding_id);

for(int i = min_boarding_id; i < 1023; i++){
    if(boarding_checks[i] != 1 && i <= max_boarding_id){
        printf("Missing boarding pass id: %i \n", i);   
        printf("Row: %i, Col: %i \n", i/8, i%8);  
   }
}

fclose(input);
return 0;
}
