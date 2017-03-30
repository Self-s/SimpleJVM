#include <cstring>
#include <cstdlib>
#include <cstdio>

#include "utils.h"

using namespace std;

double Utils::generateFriendlyVersionNumber(ClassFile *classFile) {
    if (classFile->major_version < 45 || classFile->major_version > 52) {
        return 0;
    }
    
    if (classFile->major_version <= 48) {
        return 1.0 + (classFile->major_version - 44)*0.1;
    }
    
    return 5 + (classFile->major_version - 49);
}

bool Utils::compareUtf8WithString(CONSTANT_Utf8_info constant, const char *str) {
    if (constant.length != strlen(str)) {
        return false;
    }
    
    for (int i = 0; i < constant.length; i++) {
        if(constant.bytes[i] != str[i]) return false;
    }
    
    return true;
}

void Utils::printTabs(FILE *out, uint8_t n) {
    for (uint8_t i = 0; i < n; i++) fprintf(out, "\t");
}

const char* Utils::streamToCString(const stringstream &ss) {
    string tmp = ss.str();
    char *result = (char*) malloc(sizeof(char) * (tmp.size() + 1));
    tmp.copy(result, tmp.size());
    result[tmp.size()] = '\0';
    
    return result;
}
