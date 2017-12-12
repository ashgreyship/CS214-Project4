
/*
> = end of string length
~ = column end
^ = new line
@ = eof
< = end of ip
 */


char* convertToString(char* col, FILE* fp, char* ip) {
	char* ipLine = malloc(strlen(ip)+2);
    strcpy(ipLine, ip);
    strcat(ipLine, "<");

    char* colLine = malloc(strlen(ip)+2);
    strcpy(colLine, col);
    strcat(colLine, "~");

    char* fullStr = (char*) malloc(5000);
    fullStr[0] = '\0';

    long allocationAmt = 500;

    char* newStr = (char*) malloc(500);
    newStr[0] = '\0';

	while (fgets(newStr, 500, fp) != NULL) {
        if (strlen(fullStr) + strlen(newStr) > allocationAmt - 10) {
            allocationAmt = allocationAmt * 2;
            char* tempStr = malloc(allocationAmt * 2);
            strcpy (tempStr, fullStr);
            fullStr = malloc(allocationAmt);
            strcpy (fullStr, tempStr);
        }

        strncat(fullStr, newStr, strlen(newStr)-1);
        strcat(fullStr, "^");
	}

    strcat(fullStr, "@");


    char* returnStr = malloc(strlen(fullStr) + strlen(ipLine) + strlen(colLine)+100);
    itoa(strlen(fullStr) + strlen(ipLine) + strlen(colLine) + 100, returnStr, 10);
    strcat(returnStr, ">");
    strcat(returnStr, colLine);
    strcat(returnStr, fullStr);
    strcat(returnStr, ipLine);

    return returnStr;
}