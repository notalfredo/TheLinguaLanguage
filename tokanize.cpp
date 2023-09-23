#include <cctype>
#include <iostream>
#include <fstream>
#include <string>


typedef enum token{
    tok_invalid = 0,

    tok_plus = 1,
    tok_minus = 2,
    tok_multiply = 3,
    tok_divide = 4,

    tok_integer = 5,

    tok_identifier = 6,
    tok_assignment = 7,
}token;

typedef struct keyWord{
    std::string tokenString;
    token tokenEnum;
}stringToToken;


static token currToken;
static int currNumber;
static std::string identifierString;
static std::ifstream inputFile;

static stringToToken mapKeyWordStringToToken[] = {
    {"plus", tok_plus},
    {"minus", tok_minus},
    {"multiply", tok_multiply},
    {"divide", tok_divide},
    {"<=", tok_assignment}
};



//===----------------------------------------------------------------------===//
// File Handlaing
//===----------------------------------------------------------------------===//
int openFile(std::string fileName){
    inputFile.open(fileName);
    if (!inputFile.is_open()) {
        std::cerr << "Error: Could not open the file " << fileName << std::endl;
        return 0;
    }
    return 1;
}

//===----------------------------------------------------------------------===//
// Tokenizer
//===----------------------------------------------------------------------===//

token checkIfStringIsKeyword(std::string foundWord);
token getTok(std::ifstream &inputFile);
void getNextToken();


token checkIfStringIsKeyword(std::string foundWord){
    for(int index = 0; index < sizeof(mapKeyWordStringToToken) / sizeof(keyWord); index ++){
        if(foundWord == mapKeyWordStringToToken[index].tokenString){
            return mapKeyWordStringToToken[index].tokenEnum;
        }
    }
    return tok_invalid;
}


token getTok(){
    char characterFound = ' ';  
    inputFile.get(characterFound);

    //Skip any whitespace
    while(characterFound == ' '){
        inputFile.get(characterFound);    
    }

    //keyword or identifier
    if(isalpha(characterFound)){
        identifierString = characterFound;
        inputFile.get(characterFound);

        while(isalnum(characterFound)){
            identifierString += characterFound;
            inputFile.get(characterFound);
        }

        token result = checkIfStringIsKeyword(identifierString);
        return result != tok_invalid ? result : tok_identifier;
    }
    //integer
    else if(isdigit(characterFound)){
        std::string digitString;

        do{
            digitString += characterFound;
            inputFile.get(characterFound);
        }while(isdigit(characterFound));

        currNumber = std::stoi(digitString);
        return tok_integer;
    }

    return tok_invalid;
}

void getNextToken(){
    currToken = getTok();
}


void dumpToken(){
    switch (currToken){
        case tok_invalid:
            std::cout << "tok_invalid" << std::endl;
            break;

        case tok_plus:
            std::cout << "tok_plus" << std::endl;
            break;

        case tok_minus:
            std::cout << "tok_minus" << std::endl;
            break;

        case tok_divide:
            std::cout << "tok_divide" << std::endl;
            break;

        case tok_multiply:
            std::cout << "tok_multiply" << std::endl;
            break;

        case tok_integer:
            std::cout << "tok_integer " << currNumber << std::endl;
            break;

        case tok_identifier:
            std::cout << "tok_identifier " << identifierString << std::endl;
            break;

        case tok_assignment:
            std::cout << "tok_assignment" << std::endl;
            break;

        default:
            std::cout << "DUDE WTF HOW DID YOU BREAK MY PROGRAM " << currToken << std::endl;
            break;
    }
}


//Temp main
int main() {
    std::string fileName = "tokenTest.txt"; // Change this to the path of your file
    openFile(fileName);

    getNextToken();
    dumpToken();

    getNextToken();
    dumpToken();
                       
    getNextToken();
    dumpToken();

    getNextToken();
    dumpToken();

    getNextToken();
    dumpToken();
                       
    getNextToken();
    dumpToken();


    getNextToken();
    dumpToken();
                       
    getNextToken();
    dumpToken();
    return 0;
}

