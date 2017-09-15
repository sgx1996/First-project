#include "creataccount.h"
int main()
{
	FILE *cfPtr;
	char account[16] = { "" };
	char data[16] = { "" };
	char acctchoice;
	char choice;
	if ((cfPtr = fopen("store.dat", "r+")) == NULL)
	{
		printf("\t\tFile could not be opened.\n");
	}
	else 
	{
		while ((acctchoice = accountChoice()) != '4')
		{
			switch (acctchoice)
			{
			case '1':
			{
				CreateAdministrator(account[16], data[16]);
				break;
			}
			case '2':
			{
				CreateAccount(account[16], data[16]);
				break;
			}
			case '3':
			{
				while ((choice = LoginChoice()) != '3')
				{
					switch (choice)
					{
					case '1':
					{
						loginAdministrator(account[16], data[16]);
						Administratorbusiness();
						break;
					}
					case '2':
					{
						LoginAccount(account[16], data[16]);
						regularuserbusiness();
						break;
					}
					}
				}
				break;
			}
			}
		}
		fclose(cfPtr);
	}
			return 0;
}
int regularuserbusiness()
{
	FILE *cfPtr;
	char menuchoice;
	if ((cfPtr = fopen("store.dat", "r+")) == NULL)
	{
		printf("\t\tFile could not be opened.\n");
	}
	else
	{
		while ((menuchoice = Choice()) != '4')
		{
			switch (menuchoice)
			{
			case '1':
			{
				textFile(cfPtr);
				break;
			}
			case '2':
			{
				findRecord(cfPtr);
				break;
			}
			case '3':
			{
				updateRecord(cfPtr);
				break;
			}
			}
		}
		
	}
	fclose(cfPtr);
	return 0;
}
int Administratorbusiness()
{
	FILE *cfPtr;
	char opechoice;
	if ((cfPtr = fopen("store.dat", "r+")) == NULL)
	{
		printf("\t\tFile could not be opened.\n");
	}
	else
	{
		while ((opechoice = bussinessChoice()) != '7')
		{
			switch (opechoice)
			{
			case '1':
			{
				textFile(cfPtr);
				break;
			}
			case '2':
			{
				modifyRecord(cfPtr);
				break;
			}
			case '3':
			{
				newRecord(cfPtr);
				break;
			}
			case '4':
			{
				deleteRecord(cfPtr);
				break;
			}
			case '5':
			{
				displayRecord(cfPtr);
				break;
			}
			case '6':
			{
				findRecord(cfPtr);
				break;
			}
			}
		}

	}
	fclose(cfPtr);
	return 0;
}
void textFile(FILE *readPtr)
{
	FILE *writePtr;
	struct clientData client = { 0, "", 0, 0.0 };

	if ((writePtr = fopen("customerinformation.txt", "w+")) == NULL)
	{
		printf("\t\tFile could not be opened.\n");
	}
	else
	{
		rewind(readPtr);
		fprintf(writePtr, "%-6s%-16s%-11s%10s\n",
			"Acct", " Name", "Phone Name", "Balance");

		while (!feof(readPtr))
		{
			
			size_t ret = fread(&client, sizeof( clientData), 1,
				readPtr);
			if (ret != 1)
			{
				break;
			}
			if (client.acctNum != 0)
			{
				fprintf(writePtr, "%-6d%-16s%-11d%10.2f\n",
					client.acctNum, client.Name,
					client.phoneNumber, client.balance);
			}
		}
	}
	fclose(writePtr);
}
void updateRecord(FILE *fPtr)
{
	int account;
	double transaction;
	char newname[16];
	int phone;
	struct clientData client = { 0, "", 0, 0.0 };

	printf("\n\t\t   Enter account to update ( 1 - 100 ): "
	       "\n\t\t   -----");
	scanf("%d", &account);
	
	rewind(fPtr);

	for (int i = 1;i <= 100;i++)
	{

		fread(&client, sizeof(struct clientData), 1, fPtr);
		if (client.acctNum == account)
		{
			printf("\n\t\t   ---%-6d%-16s%-11d%10.2f\n\n",
				client.acctNum, client.Name,
				client.phoneNumber, client.balance);
			char modichoice;
			while ((modichoice = modify_AdminChoice()) != '3')
			{
				switch (modichoice)
				{
				case '1':
				{
					printf("\n\t\t   please enter the new name :"
					"\n\t\t   *** ");
					scanf("%16s", newname);
					memcpy(client.Name, newname, sizeof(newname));
					break;
				}
				case '2':
				{
					printf("\n\t\t   please enter the new phone number :"
					"\n\t\t   *** ");
					scanf("%11d", &phone);
					memcpy(&client.phoneNumber, &phone, sizeof(phone));
					break;
				}
				}
			}
			printf("\n\t\t   ---%-6d%-16s%-11d%10.2f\n",
				client.acctNum, client.Name,
				client.phoneNumber, client.balance);
			fseek(fPtr, (i - 1) * sizeof(struct clientData),
				SEEK_SET);
			fwrite(&client, sizeof(struct clientData), 1,
				fPtr);
			break;
		}
	}

}
void deleteRecord(FILE *fPtr)
{
	struct clientData client,
		blankClient = { 0, "", 0, 0 };
	int accountNum;

	printf("\t\t   Enter account number to  delete ( 1 - 100 ): "
	       "\n\t\t----- ");
	scanf("%d", &accountNum);
	rewind(fPtr);
	for (int i = 1;i <= 100;i++)
	{
		fseek(fPtr, (i - 1) * sizeof(struct clientData),
			SEEK_SET);
		fread(&client, sizeof(struct clientData), 1, fPtr);
		if (client.acctNum == accountNum)
		{

			fseek(fPtr, (i - 1) * sizeof(struct clientData),
				SEEK_SET);
			fwrite(&blankClient,
				sizeof(struct clientData), 1, fPtr);
			break;
		}
	}
	if (client.acctNum != accountNum)
	{
		printf("\n\t\t   No information found !");
	}
}
void newRecord(FILE *fPtr)
{
	struct clientData client = { 0, "", 0, 0.0 };
	int accountNum;
	printf("\n\t\t   Enter new account number ( 1 - 100 ): "
	       "\n\t\t   ----- ");
	scanf("%d", &accountNum);
	rewind(fPtr);
	for (int i = 1;i <= 100;i++)
	{
		fseek(fPtr, (i - 1) * sizeof(struct clientData), SEEK_SET);
		fread(&client, sizeof(struct clientData), 1, fPtr);
		if (client.acctNum == accountNum)
		{
			printf("\t\t   Account #%d already contains information.\n",
				client.acctNum);
			break;
		}
		else
		{

			if (fread(&client, sizeof(struct clientData), 1, fPtr) == NULL)
			{
				printf("\t\t   Enter name, phonenumber, balance\n "
					"\t\t   -----");
				scanf("%s%d%lf", &client.Name, &client.phoneNumber,
					&client.balance);
				client.acctNum = accountNum;

				fwrite(&client,
					sizeof(struct clientData), 1, fPtr);
				break;
			}
		}
	}
}
void findRecord(FILE *fPtr)
{
	struct clientData client = { 0, "", 0, 0 };
	int accountNum = 0;
	printf("\t\t   Enter account number to \n"
	"\t\t   -----");
	scanf("%d", &accountNum);
	rewind(fPtr);
	for (int i = 1;i <= 100;i++)
	{
		fseek(fPtr, (i - 1) * sizeof(struct clientData),
			SEEK_SET);
		fread(&client, sizeof(struct clientData), 1, fPtr);
		if (client.acctNum == accountNum)
		{
			printf("\n\t\t----- %d\t%s\t%d\t%lf -----\n", client.acctNum,
				client.Name, client.phoneNumber, client.balance);
			break;
		}
	}
	if (client.acctNum != accountNum)
	{
		printf("\n\t\t   No information found !\n");
	}

}
void CreateAccount(char account, char data)
{

	FILE *writePtr = fopen("Administratoraccounts.dat", "r+");
	accountDataptr accountdata = (accountData*)malloc(sizeof(accountData));
	memset(accountdata, 0, sizeof(accountData));
	char newpassword[16];
	char secondpassword[16];
	char username[16];
	printf("\n\t\t   please enter a new username:\n"
	"\n\t\t   *** ");
	scanf("%s", username);
	if (writePtr == NULL)
	{
		printf("\n\t\t   please enter a new password (less than 16 characters):\n"
		"\n\t\t   ----- ");
		scanf("%s", accountdata->password);
		printf("\n\t\t   please confirm your new password:\n"
		"\n\t\t   ----- ");
		scanf("%s", newpassword);
	}
	else
	{
		rewind(writePtr);
		while (!feof(writePtr))
		{
			for (int i = 1;i < 100;i++)
			{
				fseek(writePtr, (i - 1) * sizeof(accountData), SEEK_SET);
				fread(accountdata, sizeof(accountData), 1, writePtr);
				if (strcmp(accountdata->username, username) == 0)
				{
					printf("\n\t\t   User name already exists !\n");
					printf("\t\t   please enter a new username:\n"
					"\n\t\t   *** ");
					scanf("%s", username);
					break;
				}
			}

			{
				printf("\n\t\t   please enter a new password (less than 16 characters):\n"
				"\n\t\t   ----- ");
				scanf("%s", accountdata->password);
				printf("\n\t\t   please confirm your new password:\n"
				"\n\t\t   ----- ");
				scanf("%s", newpassword);
				break;
			}
		}
	}
	while (1)
	{

		if (strcmp(newpassword, accountdata->password) == 0)
		{
			printf("\n\t\t __Creating a successful__ \n");
			memcpy(accountdata->username, username, sizeof(username));
			fseek(writePtr, sizeof(accountData), SEEK_END);
			fwrite(accountdata, sizeof(accountData), 1, writePtr);
			break;
		}
		else
		{
			printf("\n\t\t   Not in accordance with the input password !\n");
			printf("\t\t   please confirm your new password:\n"
			"\n\t\t   ----- ");
			scanf("%s", &secondpassword);
			for (int i = 0;i < 16;i++)
			{
				newpassword[i] = secondpassword[i];
			}
		}
	}
	fclose(writePtr);
}
void CreateAdministrator(char account, char data)
{
	accountDataptr Admindata = (accountData*)malloc(sizeof(accountData));
	memset(Admindata, 0, sizeof(accountData));
	char Adpassword[16] = { "" };
	char newpassword[16] = { "00000" };
	int time = 1;
	printf("\n\t\t   please enter a Administratorpassword:\n"
	"\n\t\t   ----- ");
	scanf("%s", Adpassword);
	while (time<=4)
	{
		if (strcmp(Adpassword, newpassword) == 0)
		{
			CreateAccount(Admindata->username[16], Admindata->password[16]);
			break;
		}
		else
		{
			printf("\n\t\t   Administrator password error !\n");
			printf("\n\t\t   please retype your Administrator password:\n"
			"\n\t\t   ----- ");
			scanf("%s", newpassword);
			for (int i = 0;i < 16;i++)
			{
				Adpassword[i] = newpassword[i];
			}
		}
		time++;
	}
	if (time > 4)
	{
		printf("\n\t\t   Run out of time !");
	}
}
void LoginAccount(char account, char data)
{
	FILE *writePtr = fopen("Administratoraccounts.dat", "r+");
	accountDataptr logdata = (accountData*)malloc(sizeof(accountData));
	memset(logdata, 0, sizeof(accountData));
	char name[16];
	char word[16];
	char newword[16];
	char acctchoice;
	int time = 1;
	printf("\n\t\t   username :\n"
	"\n\t\t   ***");
	scanf("%s", &name);
	printf("\n\t\t   password :\n"
	"\n\t\t   -----");
	scanf("%s", &word);
	rewind(writePtr);
	while (!feof(writePtr))
	{
		for (int i = 1;i < 100;i++)
		{
			fseek(writePtr, (i - 1) * sizeof(accountData), SEEK_SET);
			fread(logdata, sizeof(accountData), 1, writePtr);
			if (strcmp(logdata->username, name) == 0)
			{
				while (time <= 4)
				{
					if (strcmp(logdata->password, word) == 0)
					{
						printf("\n\t\t   Login  a successful !\n");
						break;
					}
					else
					{
						printf("\n\t\t   Not in accordance with the input password !\n");
						printf("\n\t\t   please confirm your new password:\n"
						"\n\t\t   -----");
						scanf("%s", &newword);
						memcpy(word, newword, sizeof(newword));
					}
					time++;
				}
				if (time > 4)
				{
					printf("\n\t\t  ___Run out of time___");
				}
				break;
			}
		}
		if (strcmp(logdata->username, name) != 0)
		{
			printf("\n\t\t   User name does not exist !\n");
			printf("\n\t\t   Please register !\n");
			while ((acctchoice = accountChoice()) != '4')
			{
				switch (acctchoice)
				{
				case '1':
				{
					CreateAdministrator(name[16], word[16]);
					break;
				}
				case '2':
				{
					CreateAccount(name[16], word[16]);
					break;
				}
				case '3':
				{
					LoginAccount(name[16], word[16]);
					break;
				}
				}
			}
		}
		break;
	}
	fclose(writePtr);
}
void loginAdministrator(char account, char data)
{
	char newpassword[16] = { "00000" };
	char Adpassword[16] = {""};
	int time = 1;
	printf("\n\t\t   please enter a Administratorpassword:\n"
		"\n\t\t   ----- ");
	scanf("%s", Adpassword);
	while (time <= 4)
	{
		if (strcmp(Adpassword, newpassword) == 0)
		{
			LoginAccount( account,  data);
			break;
		}
		else
		{
			printf("\n\t\t   Administrator password error !\n");
			printf("\n\t\t   please retype your Administrator password:\n"
				"\n\t\t   ----- ");
			scanf("%s", newpassword);
			for (int i = 0;i < 16;i++)
			{
				Adpassword[i] = newpassword[i];
			}
		}
		time++;
	}
	if (time > 4)
	{
		printf("\n\t\t   Run out of time !");
	}
}
void modifyRecord(FILE *fPtr)
{
	int account;
	double transaction;
	int phone;
	char newname[16];
	struct clientData client = { 0, "", 0, 0.0 };

	printf("\n\t\t   Enter account to update ( 1 - 100 ): "
		"\n\t\t   -----");
	scanf("%d", &account);

	rewind(fPtr);

	for (int i = 1;i <= 100;i++)
	{

		fread(&client, sizeof(struct clientData), 1, fPtr);
		if (client.acctNum == account)
		{
			printf("\t\t   ---%-6d%-16s%-11d%10.2f\n\n",
				client.acctNum, client.Name,
				client.phoneNumber, client.balance);
			char modichoice;
			while ((modichoice = modify_AdminChoice()) != '4')
			{
				switch (modichoice)
				{
				case '1':
				{
					printf("\n\t\t   please enter the new name :"
					       "\n\t\t   *** ");
					scanf("%16s", newname);
					memcpy(client.Name, newname, sizeof(newname));
					break;

				}
				case '2':
				{
					printf("\n\t\t   please enter the new phone number :"
					"\n\t\t   *** ");
					scanf("%11d", &phone);
					client.phoneNumber = phone;
					break;
				}
				case '3':
				{
					printf("\n\t\t   Enter charge ( + ) or payment ( - ): "
					"\n\t\t   *** ");
					scanf("%lf", &transaction);
					client.balance += transaction;
					break;
				}
				}
			}
			printf("\t\t   ---%-6d%-16s%-11d%10.2f\n",
				client.acctNum, client.Name,
				client.phoneNumber, client.balance);
			fseek(fPtr, (i - 1) * sizeof(struct clientData),
				SEEK_SET);
			fwrite(&client, sizeof(struct clientData), 1,
				fPtr);
			break;
		}
	}
}
char modify_AdminChoice(void)
{
	char menuChoice[256];
	printf("\t\t\t   -----Registration-----\n"
		"\t\t   * * * * * * * * * * * * * * * * * * *\n"
		"\t\t   *\t\t\t\t       *\n"
		"\t\t   * 1 - Modify the name               *\n"
		"\t\t   *\t\t\t\t       *\n"
		"\t\t   *        Modify the phonenumber - 2 *\n"
		"\t\t   *\t\t\t\t       *\n"
		"\t\t   * 3 - Modify the balance            *\n"
		"\t\t   *\t\t\t\t       *\n"
		"\t\t   *         4 - end program           *\n"
		"\t\t   *\t\t\t\t       *\n"
		"\t\t   * * * * * * * * * * * * * * * * * * *\n\n");
	printf("\t\t   choice:  ");
	scanf("%s", menuChoice);
	if (menuChoice[0] >= '0'&&menuChoice[0] <= '9'&&strlen(menuChoice) == 1)
	{
		return menuChoice[0];
	}
	else
	{
		printf("\n\t\t   Input error !\n");
	}
}
char modify_Choice(void)
{
	char menuChoice[256];

	printf("\t\t\t   -----Registration-----\n"
		"\t\t   * * * * * * * * * * * * * * * * * * *\n"
		"\t\t   *\t\t\t\t       *\n"
		"\t\t   * 1 - Modify the name               *\n"
		"\t\t   *\t\t\t\t       *\n"
		"\t\t   *        Modify the phonenumber - 2 *\n"
		"\t\t   *\t\t\t\t       *\n"
		"\t\t   * 3 - end program                   *\n"
		"\t\t   *\t\t\t\t       *\n"
		"\t\t   * * * * * * * * * * * * * * * * * * *\n\n");
	printf("\t\t   choice:  ");
	scanf("%s", menuChoice);
	if (menuChoice[0] >= '0'&&menuChoice[0] <= '9'&&strlen(menuChoice) == 1)
	{
		return menuChoice[0];
	}
	else
	{
		printf("\n\t\t   Input error !\n");
	}
}
char bussinessChoice(void)
{
	char menuChoice[256];

	printf("\n\t\t\t-----Choose a business-----\n"
		"\t\t   * * * * * * * * * * * * * * * * * * *\n"
		"\t\t   *\t\t\t\t       *\n"
		"\t\t   * 1 - save the changes              *\n"
		"\t\t   *\t\t\t\t       *\n"
		"\t\t   *             update an account - 2 *\n"
		"\t\t   *\t\t\t\t       *\n"
		"\t\t   *3 - add a new account              *\n"
		"\t\t   *\t\t\t\t       *\n"
		"\t\t   *             delete an account - 4 *\n"
		"\t\t   *\t\t\t\t       *\n"
		"\t\t   *5 -  displayRecord                 *\n"
		"\t\t   *\t\t\t\t       *\n"
		"\t\t   *             query information - 6 *\n"
		"\t\t   *\t\t\t\t       *\n"
		"\t\t   *            7 - end                *\n"
		"\t\t   *\t\t\t\t       *\n"
		"\t\t   * * * * * * * * * * * * * * * * * * *\n\n");
	printf("\t\t   choice:  ");
	scanf("%s", menuChoice);

	if (menuChoice[0] >= '0'&&menuChoice[0] <= '9'&&strlen(menuChoice) == 1)
	{
		return menuChoice[0];
	}
	else
	{
		printf("\n\t\t   Input error !\n");
	}
}
char accountChoice(void)
{
	char menuChoice[256];
	printf("\t\t\t  -----Registration or login -----\n"
		"\t\t   * * * * * * * * * * * * * * * * * * *\n"
		"\t\t   *\t\t\t\t       *\n"
		"\t\t   * 1 - Create the administrator user *\n"
		"\t\t   *\t\t\t\t       *\n"
		"\t\t   * 2 - Create the regular user       *\n"
		"\t\t   *\t\t\t\t       *\n"
		"\t\t   * 3 - login account                 *\n"
		"\t\t   *\t\t\t\t       *\n"
		"\t\t   * 4 - end program                   *\n"
		"\t\t   *\t\t\t\t       *\n"
		"\t\t   * * * * * * * * * * * * * * * * * * *\n\n");
	printf("\t\t   choice:  ");
	scanf("%s", menuChoice);
	if (menuChoice[0] >= '0'&&menuChoice[0] <= '9'&&strlen(menuChoice)==1)
	{
		return menuChoice[0];
	}
	else
	{
		printf("\n\t\t   Input error !\n");
	}
	
}
char Choice(void)
{
	char menuChoice[256];

	printf("\t\t\t   -----Choose a business-----\n"
		"\t\t   * * * * * * * * * * * * * * * * * * *\n"
		"\t\t   *\t\t\t\t       *\n"
		"\t\t   * 1 - save the changes              *\n"
		"\t\t   *\t\t\t\t       *\n"
		"\t\t   *             query information - 2 *\n"
		"\t\t   *\t\t\t\t       *\n"
		"\t\t   * 3 - modify information            *\n"
		"\t\t   *\t\t\t\t       *\n"
		"\t\t   *            4 - end                *\n"
		"\t\t   *\t\t\t\t       *\n"
		"\t\t   * * * * * * * * * * * * * * * * * * *\n\n");
	printf("\t\t   choice:  ");
	scanf("%s", menuChoice);
	if (menuChoice[0] >= '0'&&menuChoice[0] <= '9'&&strlen(menuChoice) == 1)
	{
		return menuChoice[0];
	}
	else
	{
		printf("\n\t\t   Input error !\n");
	}
}
char LoginChoice(void)
{
	char menuChoice[256];
	printf("\t\t\t   -----LoginChoice-----\n"
		"\t\t   * * * * * * * * * * * * * * * * * * *\n"
		"\t\t   *\t\t\t\t       *\n"
		"\t\t   * 1 - Login the Administrator       *\n"
		"\t\t   *\t\t\t\t       *\n"
		"\t\t   * 2 - Login the regular user        *\n"
		"\t\t   *\t\t\t\t       *\n"
		"\t\t   * 3 - end program                   *\n"
		"\t\t   *\t\t\t\t       *\n"
		"\t\t   * * * * * * * * * * * * * * * * * * *\n\n");
	printf("\t\t   choice:  ");
	scanf("%s", menuChoice);
	if (menuChoice[0] >= '0'&&menuChoice[0] <= '9'&&strlen(menuChoice) == 1)
	{
		return menuChoice[0];
	}
	else
	{
		printf("\n\t\t   Input error !\n");
	}
}
void displayRecord(FILE *)
{
	printf("\t\t   Current account information:\n");
	FILE *file = fopen("D:\\VS\\project\\First project\\First project\\customerinformation.txt", "r+");

	char buffer[256] = { 0 };
	while (fgets(buffer, 256, file) != 0)
	{
		printf("\n\t\t");
		fputs(buffer, stdout);
	}
	fclose(file);
}
