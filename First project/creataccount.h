#ifndef __LITE_QUEUE_h__
#define __LITE_QUEUE_h__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct clientData
{
	int acctNum;
	char Name[15];
	int phoneNumber;
	double balance;
};
typedef struct _accountData
{
	char username[16];
	char password[16];


} accountData, *accountDataptr;
void CreateAccount(char, char);
void CreateAdministrator(char, char);
void LoginAccount(char, char);
void loginAdministrator(char, char);
void textFile(FILE *);
void updateRecord(FILE *);
void newRecord(FILE *);
void deleteRecord(FILE *);
void findRecord(FILE *);
void displayRecord(FILE*);
void modifyRecord(FILE *);
int regularuserbusiness();
int Administratorbusiness();
char accountChoice(void);
char Choice(void);
char bussinessChoice(void);
char modify_AdminChoice(void);
char modify_Choice(void);
char LoginChoice(void);
#endif