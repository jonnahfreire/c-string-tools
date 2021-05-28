#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int indexOf(char chr, char *str){
    // returns the first character occurrence in a string
    int i = 0, found = -1;

    for(i; (str[i] != '\0'); i++){
        if(((int)str[i] == (int)chr)){
            found = i;
            break;
        }
    }
    return found;
}


int lastIndexOf(char chr, char *str){
    // returns the last character occurrence in a string
    int i = 0, found = -1;

    for(i; (str[i] != '\0'); i++)
    if(((int)str[i] == (int)chr)) found = i;
    
    return found;
}

char *concat(char* str1, char* str2) {
    // Inserts str2 at the end of str1
    int len = strlen(str1) + strlen(str2);
    char st1[strlen(str1)]; strcpy(st1, str1);
    char st2[strlen(str2)]; strcpy(st2, str2);

    char *newstr = (char*)calloc(len, sizeof(char));
    if(strlen(str2) > 0) {
        strcpy(newstr, strcat(st1, st2));
        return newstr;
    }
    free(newstr);
    return str1;
}

char *slice(char *str, int start, int endStr){
    // slices a given part of a string
    int i;
    char *sliced = (char *) calloc(endStr, sizeof(char));
    char *temp = (char *) calloc(strlen(str), sizeof(char));
    strcpy(temp, str);

    for(i = start; i <= endStr; i++)
    if(temp[i] != '\0') sliced[strlen(sliced)] = temp[i];
    
    free(temp);
    return concat(sliced, "");
}

int findStrIndex(char *str, char *tofind){
    //Find index of a given string
    int i, index = indexOf(tofind[0], str);

    if((index == -1) || (strlen(tofind) == 1)) return -1;

    for(i = index; i <= strlen(str); i++){
        if(strcmp(tofind, slice(str, index, index+strlen(tofind)-1))) index++;
        else break;
    }
    return index;
}

char *removeStr(char *str, char *strToRemove){
    //Remove a set of characters of a given string
    //return the new sized string
    int i, index = indexOf(strToRemove[0], str);

    if((index == -1)) return (char*)'\0';

    for(i = index; i <= strlen(str); i++){
        if(strcmp(strToRemove, slice(str, index, index+strlen(strToRemove)-1))){
            index++;
        }else{
            if(index == 0) return slice(str, index+strlen(strToRemove), strlen(str));
            else if(index == strlen(str)) return (char*)'\0';
            else return concat(
                    slice(str, 0, index-1), //First part
                    slice(str, index+strlen(strToRemove), strlen(str))); //Second part/
            break;
        }
    }
}

char *removeChr(char *str, char c){
    // Removes the first occurrence of a Character from a given string
    int i = 0, index = indexOf(c, str);
    if(index == -1) return (char*)'\0';

    for(i; i < strlen(str); i++){
        if((int)str[i] == c){
            char *t = (char*) calloc(2, sizeof(char));
            t[0] = str[i];

            char *n = removeStr(str, t);
            free(t);
            return n;
        }
    }
}

char *removeAllChr(char *str, char c) {
    // Removes all occurrences of a given character in a string
    int i, index = indexOf(c, str);
    if(index == -1) return (char*)'\0';

    char *newstr = (char*) calloc(strlen(str), sizeof(char));
    strcpy(newstr, str);

    for(i = 0; i < strlen(newstr); i++){
        if((int)newstr[i] == (int)c){
            char *e = removeChr(newstr, newstr[i]);
            strcpy(newstr, e);
        }
    }
    return newstr;
}


int countChar(char *str, char chr){
    // Returns the length of occurrences of a given character in a string
    int i=0, counter=0;

    for(i; (str[i] != '\0'); i++)
    if(((int)str[i] == (int)chr))  counter++;

    return counter;
}

char *replaceStr(char *str, char *strRep, char *rep){
    // Replaces a given set of characters in a string by another string
    int index = 0;

    if((strlen(strRep) == 0) || (strlen(rep) == 0)) return (char*)'\0';

    if((strlen(removeStr(str, strRep)) != strlen(str)) && ((strlen(strRep)>1) && (strlen(rep)>1))){
        index = findStrIndex(str, strRep);
        if(index == 0) return concat(rep, slice(str, index+strlen(strRep), strlen(str)));
        else return concat(concat(slice(str, 0, index-1), rep), slice(str, index+strlen(strRep), strlen(str)));

    }else{
        index = indexOf(strRep[0], str);
        if(index == 0) return concat(rep, slice(str, index+strlen(strRep), strlen(str)));
        else return concat(slice(str, 0, index-1), concat(rep, slice(str, index+1, strlen(str))));
    }
}
