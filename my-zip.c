/*
    my-zip
	Goal - to compress a file using run-length encoding (RLE)
	
	Read through the file to store, counting the characters
	write the number followed by the character using fwrite();
	
	When reading multiple files - Make sure that if a file ends with a letter, and the next
	files start with the same letter, that they are considered as one collection of the same letter
	
	>aaaa
	>aaaaa
	
	should be stored as 9a
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int main (int argc, char ** argv) {
	
	//user does not provide any arguments, just calls my-zip
    if (argc == 1){
		printf("my-zip: file1 [file2 ...]\n"); //no search term 
        return 1;
    }
	
	//user provides more than one argument 
	if (argc > 1) {
		
		int charCount=0;
		char charCurrent;

        //cycle through each argument if more than one is passed to the program
        for(int i = 1; i < argc; i++){
			
			FILE *fp;
			char *line = NULL;
			size_t len = 0;
			ssize_t nread;
						
            //open each file per arguments 
            fp = fopen(argv[i], "r");
            
			//check if fopen() call succeeded ie pointer is not NULL
            if (fp == NULL) {
                printf("my-zip: cannot open file\n");
                exit(1);
            }
			
			//while not at EOF - get each line. nread contains the total number of elements successfully returned
			while((nread = getline(&line, &len, fp)) != -1){
				
				//loop through each char in the line
				for (int j = 0; j < nread; j++){
					//check if any characters have been read yet. If not - set 1st character as current character
					if(charCount == 0){
						charCurrent = line[0];
						charCount = 1;
					}
					//if character is the same as the character we are counting - charCurrent - increase count
					else if (charCurrent == line[j]){
						charCount++;
					}
					//if characer is not the same as the character we are counting - output number and letter to stdout, then change character we are following and reset count
					else {
						fwrite(&charCount, 4, 1, stdout);
						fwrite(&charCurrent, 1, 1, stdout);
						fflush(stdout);
						charCurrent = line[j];
						charCount = 1;
					}
				}		
			}
			free(line);
			fclose(fp);
        }
		
		fwrite(&charCount, 4, 1, stdout);
		fwrite(&charCurrent, 1, 1, stdout);
		fflush(stdout);
	}

	return 0;
}


