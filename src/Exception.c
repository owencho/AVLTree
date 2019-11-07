#include "unity.h"
#include "Exception.h"
#include "Error.h"
#include "CException.h"
#include <stdio.h>
#include <stdint.h>
#include <malloc.h>
#include <stdarg.h>

void dumpException(Exception *ex){
    printf("%s (err=%d)", ex->errorMessage , ex->errorCode);
}

void freeException(Exception *ex){
  if(ex)
    free(ex);
}

void throwException(uint32_t errorCode,char *errorMessage,...){
    int actualLength;
    char* buffer;
    Exception *exceptionPtr;

    va_list arg;
    va_start(arg, errorMessage);

    actualLength = vsnprintf(NULL,0, errorMessage, arg);   //trick system to take actualLength
    buffer =malloc(actualLength + 1);               // allocate value to buffer
    vsnprintf(buffer,actualLength + 1, errorMessage, arg); //

  /*printf("%s \n v = %d\n", format, v); old version 1 */
  //v = va_arg(arg, int);
    va_end(arg);

  exceptionPtr = malloc(sizeof(Exception));
  exceptionPtr -> errorCode = errorCode;
  exceptionPtr -> errorMessage = buffer;
  Throw(exceptionPtr);
}
