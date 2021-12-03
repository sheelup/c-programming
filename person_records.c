#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

typedef struct Country{
    char countryname[20];
    int countryId;
}Country;

typedef struct State{
    char stateName[20];
    int stateId;
    struct Country* country;
}State;

typedef struct District{
    char districtName[20];
    int districtId;
    struct State* state;
    struct Country* country;
}District;

void showAllCountries();
void addNewDistrict();
void showStates();
Country* readCountrySelection();
State* readStateSelectionForCountry(Country* country);
void showStateForCountry(Country* country);

Country* countries[100];
int countriesLen = 0;

State* states[100];
int statelen = 0;

District* districts[100];
int districtlen = 0;

State* readStateSelectionForCountry(Country* country){
    while(true){
        int sId;
        showStateForCountry(country);
        printf("Choose State id: ");
        scanf("%d",&sId);
        for(int i=0; i<statelen; i++){
            if(country->countryId == states[i]->country->countryId) {
                if(sId== states[i]->stateId){
                    return states[i];
                }
            }
        }
        printf("invalid Input !!!!!Try Again\n");
    }
}

State* readStateSelection(){
    while(true){
        int sId;
        printf("Choose State id: ");
        scanf("%d",&sId);
        for(int i=0; i<statelen; i++){
            if(sId== states[i]->stateId){
                return states[i];
            }
            
        }
        printf("invalid Input !!!!!Try Again\n");
    }
}


void scanDistrictName(char* ptr, int stateId){
    char districtName[20];
    while (true){
        printf("Enter District Name: ");
        scanf("%s",districtName);
        bool isDuplicate = false;
        for(int i=0; i<districtlen; i++){
            if(districts[i]->state->stateId == stateId){
                if(strcmp(districtName, districts[i]->districtName)==0){
                    isDuplicate = true;
                    break;
                }
            }
        }
        if(!isDuplicate){
            strcpy(ptr,districtName);
            return;
        }
        printf("District name is already exist !!! Try again\n");
    }
}
void scanDistrictId(int* id){
    while (true){
        bool isFound = false;
        printf("Enter District Id: ");
        scanf("%d", id);
        for(int i=0; i<districtlen; i++){
            if(*id == districts[i]->districtId){
                isFound = true;
                break;
            }
        }
        if(!isFound){
            return;
        }
        printf("District id is already exist!!!!!\n");
    }  
}

void addNewDistrict(){
    District* d = (District*)malloc(sizeof(District));
    d->country = readCountrySelection();
    d->state = readStateSelectionForCountry(d->country);
    scanDistrictName(d->districtName, d->state->stateId);
    scanDistrictId(&d->districtId);
    districts[districtlen] = d;
    districtlen++;
    return;
}
void showDistrictsForState(State* state){
    printf("\n********District of State %s ********\n",state->stateName);
    for(int i=0; i<districtlen; i++){
        if(districts[i]->state->stateId == state->stateId){
            printf("%d  %s\n",districts[i]->districtId, districts[i]->districtName);
        }
    }
    printf("\n***************\n");
}

void showDistrict(){
    if(districtlen==0){
        printf("No District Added yet\n");
        return;
    }
    State* state = readStateSelection();
    showDistrictsForState(state);
}

Country* readCountrySelection(){
    while (true){
        int cId;
        showAllCountries();
        printf("Choose country id: ");
        scanf("%d",&cId);
        int i;
        for(int i=0; i<countriesLen; i++){
            if(cId == countries[i]->countryId){
                return countries[i];
            }
        }  
        printf("Invalid Input!!!  Please try again\n");  
    }
    
}
void scanStateName(char* ptr, int countryId){
    while (true){
        char enteredStateName[20];
        printf("Enter State Name: ");
        scanf("%s",enteredStateName);
        bool isDuplicateName = false;
        for(int i=0; i<statelen; i++){
            if(states[i]->country->countryId == countryId){
                if(strcmp(enteredStateName, states[i]->stateName) == 0){
                    isDuplicateName = true;
                    break;
                }
            }
        }
        if(!isDuplicateName){
            strcpy(ptr, enteredStateName);
            return;
        }
        printf("State name is already exist ! Please try again \n");
    }
}
void scanStateId(int* ptr){
    bool isFound = false;
    while (true){
        printf("Enter State Id: ");
        scanf("%d", ptr);
        for(int i=0; i<statelen; i++){
            if(*ptr == states[i]->stateId){
                isFound = true;
                break;
            }
        }
        if(!isFound){
            return;
        }
        printf("State id is already exist!! Please try again\n");
    }  
}
void showStates(){
    if(statelen == 0) {
        printf("No states regsitered yet!!!\n");
        return;
    }
    Country* country = readCountrySelection();
    showStateForCountry(country);
}
void addNewState(){
    if(countriesLen == 0) {
        printf("\nPlease add country first!!!\n");
        return;
    }
    State* s = (State*)malloc(sizeof(State));
    s->country = readCountrySelection();
    scanStateName(s->stateName, s->country->countryId);
    scanStateId(&s->stateId);
    states[statelen] = s;
    statelen++;
}


void showStateForCountry(Country* country) {
    printf("\n******** states of %s **********\n", country->countryname);
    for(int i=0; i<statelen; i++){
        if(states[i]->country->countryId == country->countryId) {
            printf("%d  %s\n", states[i]->stateId, states[i]->stateName);
        }
    }
    printf("\n****************************\n");
}

void scanCountryName(char* ptr) {
    while(true) {
        char enteredName[20];
        printf("Enter country Name: ");
        scanf("%s", enteredName);
        bool isFound = false;
        int i = 0;
        for (i = 0; i<countriesLen; i++) {
            if(strcmp(enteredName, countries[i]->countryname) == 0) {
                isFound = true;
                break;
            }
        }
        if(!isFound) {
            strcpy(ptr, enteredName);
            break;
        }
        printf("Country name already exist! Please try again.\n");
    }
}

void scanCountryId(int* ptr) {
    while(true) {
        printf("Enter Country Id: ");
        scanf("%d", ptr);
        bool isFound = false;
        int i = 0;
        for (i = 0; i<countriesLen; i++) {
            if(countries[i]->countryId == *ptr) {
                isFound = true;
                break;
            }
        }
        if(!isFound) {
            break;
        }
        printf("Country id already exist! Please try again.\n");
    }
}

void addNewCountry() {
    Country* c = (Country*) malloc(sizeof(Country));
    scanCountryName(c->countryname);
    scanCountryId(&c->countryId);
    countries[countriesLen] = c;
    countriesLen++;
    printf("\n*********Added new country successfully***********\n\n");
}

int showMenuAndReadSelection() {
    printf("1.  Add new country\n");
    printf("2.  Show all countries\n");
    printf("3.  Add new State:\n");
    printf("4.  Show States\n");
    printf("5.  add new District:\n");
    printf("6.  show Districts\n");
    printf("99. Exit\n");
    printf("Please enter option: ");

    
    int selectedOption;
    scanf("%d", &selectedOption);
    return selectedOption;
}

void showAllCountries() {
    if(countriesLen == 0) {
        printf("\nNo country registered yet!!!\n");
        return;
    }
    int i = 0;
    printf("\n********* Countries **********\n");
    for (i = 0; i < countriesLen; i++) {
        printf("%d  %s\n", countries[i]->countryId, countries[i]->countryname);
    }
    printf("\n*******************************\n\n");
}

int main(){
    while (true)
    {
        int selectedOption = showMenuAndReadSelection();
        switch(selectedOption) {
            case 1: addNewCountry(); break;
            case 2: showAllCountries(); break;
            case 3: addNewState(); break;
            case 4: showStates(); break;
            case 5: addNewDistrict(); break;
            case 6: showDistrict(); break;
            case 99: exit(0);
        }
    }
    return 0;
}
// #statename;
// #stateid;
// #contryid;