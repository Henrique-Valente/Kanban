#include <time.h>
#include <stdio.h>

#include "data.h"

char* get_date_hour(time_t t)
{
    struct tm* timeInfo;
    timeInfo = gmtime(&t);
    char temp[100];
    sprintf(temp,"%02d:%02d:%2d %2d/%2d/%4d",timeInfo->tm_hour,timeInfo->tm_min,timeInfo->tm_sec,
            timeInfo->tm_mday,timeInfo->tm_mon+1,timeInfo->tm_year+1900);
    char* s = strdup(temp);
    return s;
}

char* get_date(time_t* t){
    struct tm* timeInfo;
    timeInfo = gmtime(t);
    char temp[100];
    sprintf(temp,"%2d/%2d/%4d",timeInfo->tm_mday,timeInfo->tm_mon+1,timeInfo->tm_year);
    char* s = strdup(temp);
    return s;
}