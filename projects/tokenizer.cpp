#include<bits/stdc++.h>

using namespace std;
#define TOKENIZER_INIT "tokenizer initialized..."
#define FILE_NOT_FOUND_EXCEPTION "file %s not found, initialization failed..."
class tokenizer
{
private:
    char* file_name;
    stack<char> stk;
    FILE* file;
    char buffer[4096];
public:
    tokenizer(char* file_name) {
        this->file_name = file_name;
        this->file = fopen(file_name, "r");
    }
    ~tokenizer();
    void init() {
        if (! file) {
            perror(FILE_NOT_FOUND_EXCEPTION);
        }
        printf("%s", TOKENIZER_INIT);
        while (! feof(file)) {
            if (fgets(buffer, 4096, file) == NULL) {
                break;
            }
            fputs(buffer, stdout);
        }
        fclose(file);
    }
    
    void parse_section() {
        
    }
    
};

tokenizer::tokenizer(char* file_name)
{
}

tokenizer::~tokenizer()
{
}




int main() {}