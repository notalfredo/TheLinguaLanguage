#include <cctype>
#include <iostream>
#include <fstream>
#include <string>


typedef enum token{
    tok_invalid, //Invalid token


    tok_plus,
    tok_minus,
    tok_multiply,
    tok_divide,


    tok_lit_integer,


    tok_init_identifier, // 'let'
    tok_identifier_name,
    tok_assignment, // ':='


    tok_type, // ':'
    tok_type_int,


    tok_eof
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

    {"let", tok_init_identifier},

    {"integer", tok_type_int},
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
        return result != tok_invalid ? result : tok_identifier_name;
    }
    //integer
    else if(isdigit(characterFound)){
        std::string digitString;

        do{
            digitString += characterFound;
            inputFile.get(characterFound);

        }while(isdigit(characterFound));

        currNumber = std::stoi(digitString);
        return tok_lit_integer;
    }
    else if(characterFound == ':'){

        inputFile.get(characterFound);
        if(characterFound == '='){
            return tok_assignment;
        }else{
            return tok_type;
        }
        
    }


    return tok_invalid;
}

void getNextToken(){
    currToken = getTok();
}

    //tok_invalid, //Invalid token

    //tok_plus,
    //tok_minus,
    //tok_multiply,
    //tok_divide,

    //tok_lit_integer,

    //tok_init_identifier, // 'let'
    //tok_identifier_name,
    //tok_assignment, // ':='

    //tok_type, // ':'
    //tok_type_int

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

        case tok_lit_integer:
            std::cout << "tok_integer " << currNumber << std::endl;
            break;

        case tok_init_identifier:
            std::cout << "tok_init_identifier" << std::endl;
            break;

        case tok_identifier_name:
            std::cout << "tok_identifier_name " << identifierString << std::endl;
            break;

        case tok_assignment:
            std::cout << "tok_assignment" << std::endl;
            break;

        case tok_type:
            std::cout << "tok_type" << std::endl;
            break;

        case tok_type_int:
            std::cout << "tok_type_int" << std::endl;
            break;

        case tok_eof:
            std::cout << "tok_eof" << std::endl;
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
    
    while(currToken != tok_eof){
        getNextToken();
        dumpToken();
    }
    
    inputFile.close();

    return 0;
}

