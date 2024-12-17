#include<stdio.h>
int main(){
    char* s = "#include<stdio.h>\nint main(){\n\tchar* t =";
    char* t = ";\n\tprintf(\"%s%s%s\",s,s,t);\n\treturn 0;\n}";
    printf("%s%s%s%s",s,s,t,t);
    return 0;
}