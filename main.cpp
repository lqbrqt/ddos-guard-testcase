#include <iostream>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <cstring>
#include <json-c/json.h>
#include <readline/readline.h>
#include <readline/history.h>

using namespace std;

void textFormater(char *sourceStr){
    int localCounter = 0;
    char *outStr = (char*)malloc(256 * sizeof(char*));
    for (int i=0; i<= 256; i++){
        outStr[i] = NULL;
    }
    for (int i=0; i<=strlen(sourceStr); i++){
        if ((sourceStr[i] == ' ') && (i == strlen(sourceStr))){
            continue;
        }
        if ((sourceStr[i] == ' ') && (sourceStr[i+1] == ' ')){
            continue;
        }

        outStr[i]=sourceStr[i];
        localCounter++;

        sourceStr = outStr;


    }

}

int split(char *sourceStr, char **arr){ //Split string to tokens function creation

	int wordCount = 1; //Word counter variable
	int localCounter = 1; //Position in array variable

    textFormater(sourceStr);

	for (int i=0; i<(strlen(sourceStr)); i++){ //Finding count of words in string
		if (sourceStr[i] == ' '){
			wordCount++;
		}
	}

	char *localStr = strtok(sourceStr, " "); //Splitting and adding to array
 	arr[0] = localStr;
  	while (localStr != NULL)
  	{

    	localStr = strtok (NULL, " ");
    	arr[localCounter] = localStr;
    	localCounter++;

	}

	return wordCount;
}

int main(int argc, char **argv){

	char *readBuffer; //String var for input



	json_object *finalJSONarr = json_object_new_array();
	json_object *finalJSONobj = json_object_new_object();
	string outString;

  	while (true) {
  		json_object *localJSONobj = json_object_new_object();
  		json_object *localJSONarr = json_object_new_array();
  		json_object *localJSONstr;

  		readBuffer = readline("> "); //Reading strings

  		int wordCount=0;

  		if (strcmp(readBuffer, "EXIT") == 0){
  			break;
  		}

        if (strcmp(readBuffer, "") == 0){
            continue;
        }

    	if (strlen(readBuffer) > 0){ //Adding strings to history (for comfortable use)
      		add_history(readBuffer);
    	}

    	char *wordArray[256]; //Words array creation (for 256 words, but we can do any number of elements)
    	
    	for(int i=0; i<=256; i++){
    	    wordArray[i] = NULL;
    	}

    	wordCount = split(readBuffer, wordArray); //splitting string to words

    	if (wordArray[0] == NULL) continue;

    	localJSONstr = json_object_new_string(wordArray[0]); //Create json string object from first word (command)
    	json_object_object_add(localJSONobj,"command", localJSONstr); //Adding it to json object

    	if(wordArray[1]!=nullptr){ //Checking is there arguments
    		for(int i=1; wordArray[i] != NULL; i++){ //Creation of json array object from else words
    			localJSONstr = json_object_new_string(wordArray[i]);
    			json_object_array_add(localJSONarr, localJSONstr);
    		}

    		json_object_object_add(localJSONobj,"arguments", localJSONarr); //Adding it to local json object

        }
    	json_object_array_add(finalJSONarr, localJSONobj); //Adding local json object to global json array


    	free(readBuffer);
	}


	outString = json_object_to_json_string(finalJSONarr); //Converting JSON arr to string
	for (int i=0; i<outString.length(); i++){
	    if (outString[i] == '{'){
	        outString[i] = '[';
	    }
        else if (outString[i] == '}'){
            outString[i] = ']';
        }
	}
    cout << '{' << outString << '}' << endl;


	return 0;
}