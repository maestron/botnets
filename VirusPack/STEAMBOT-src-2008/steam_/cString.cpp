#include "stdafx.h"

int wildcmp(char *wild, char *string) {
    char *cp = NULL, *mp = NULL;
        while ((*string) && (*wild != '*')) {
            if ((*wild != *string) && (*wild != '?')) {
            return 0;
        }

        wild++;
        string++;
    }

while (*string) {
            if (*wild == '*') {
                if (!*++wild) {
                return 1;
            }

            mp = wild;
            cp = string+1;
            } else if ((*wild == *string) || (*wild == '?')) {

            wild++;
            string++;
            } else {

				if (!cp || !mp) return 0; wild = mp; string = cp++;

            wild = mp;
            string = cp++;
        }

    }

while (*wild == '*') {
        wild++;
    }

return !*wild;
}
