/* Declare libraries */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>
#define STRING_LEN 200

/* Global variables */
char string[STRING_LEN], pinFind[STRING_LEN], ch, choice[STRING_LEN], option, one='1', two='2'; 
static const char * listing[] = {"Name", "Date of Birth", "ID card number", "Phone number", "Address", "Account", "Fixed", "Amount", "Pin code"};
char * lineOne = NULL, *pinFound = NULL, *numbers[9];

/* Storing file locations */
char tempFile[STRING_LEN] = "tempfile.csv", 
tDepositRecord[STRING_LEN] = "tdr.csv", 
tWithdrawRecord[STRING_LEN] = "twr.csv",

file[STRING_LEN] = "file.csv",
depositRecord[STRING_LEN] = "dr.csv",
withdrawRecord[STRING_LEN] = "wr.csv";

int allDigits(char *s)
{
    for(; *s != 0; s++)
    {
        if(!isdigit(*s)){						/* Check alphabets or numbers */
	    /* Alphabets */
	    return 0; 
	}
    }
    /* Numbers */
    return 1;
}

typedef struct{
    char datestr[STRING_LEN];
    unsigned dateval;
} datestrval;
datestrval max = {.datestr = ""};					/* Show the maximum value */																																		

int checkDeposit(char *buf)
{
    do{
        unsigned day, mon, yr, recorded = 0;
	char *p = strrchr(buf, ','), tmpstr[STRING_LEN] = "";		/* strrchr finds the last comma */

	if(!p)
	    continue;

	if(sscanf(p + 1, "%d-%d-%4d", &day, &mon, &yr) != 3)		/* Starting 1 char after ',' split into day mo yr */
	    continue;

	sprintf(tmpstr, "%4d%2d%2d", yr, mon, day);			/* Put it together in tmpstr */						
	if(sscanf(tmpstr, "%d", &recorded) != 1)			/* Convert tmpstr to unsigned in recorded */
	    continue;

	if(recorded > max.dateval){					/* if recorded greater than current max val */
	    max.dateval = recorded;					/* update struct with new max and string */
	    strcpy(max.datestr, p + 1);
	    max.datestr[strcspn(max.datestr, "\n")] = 0;		/* trim '\n' from string */
	}
    }while(0);
    return max.dateval;
}

int askPin(char *pin)
{
    printf("Enter your Pin Code: ");
    scanf("%s", pin);

    if(strlen(pin) != 4){
        printf("Sorry, wrong data entered\n");
    }
    else if(!allDigits(pin)){
        printf("Sorry, wrong data entered\n");
    }
    return 0;
}

int read(FILE * fname, char * findPin)
{
    if(fgets(string, STRING_LEN, fname))
    {
        lineOne = strtok(string, "\n");
	pinFound = strstr(lineOne, findPin);
	numbers[0] = strtok(lineOne, ",");
	for(int i = 1; i < 9; i++)
	    numbers[i] = strtok(NULL, ",");
	    return true;
    }
    else{
        return false;
    }
}

int copying(FILE * fFile, FILE * tFile){
    ch = getc(fFile);
    while(ch != EOF){
        putc(ch, tFile);
	ch = getc(fFile);
    }
}
							/* __________Choice #1: Make new Account________ */
int newAccount(FILE * fp1)
{
    char data[9][STRING_LEN];
    do{
        for(int i=0; i<9; i++)
	{
	    printf("Enter your %s: ", listing[i]);
	    fgets(data[i], sizeof data, stdin);

	    while(strcmp(data[i], "\n") == 0){				/* Find the newline */
	        fgets(data[i], sizeof data, stdin);	
	    }
	    /* Remove newline */
	    data[i][strlen(data[i]) - 1] = '\0';
	}
	
	fprintf(fp1, "%s,%s,%s,%s,%s,%s,%s,%s,%s\n", data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7], data[8]);
	printf("Do you want to create again [y/n]: ");
	scanf("%c", &option);

    }while(option == 'y');
    return 0;
}
							/* __________Choice #2: Update the account Information_________ */
int updateAccount(FILE * fp2, FILE * ft1)
{
    /* Local variables */
    int opt;
    char updatedPhone[STRING_LEN], updatedAddress[STRING_LEN], updatedPin[STRING_LEN];
    do 									/* Loop stops all details to work at once */
    {
        askPin(pinFind);
	/* Validate account for reading */
	while(read(fp2, pinFind))
	{
	    if(pinFound)						/* If pin code is present in the file */
	    {
	        /* Show the data */
		printf("Here is your Pin code: %s\n", numbers[8]);
		printf("Here is your Phone number: %s\n", numbers[3]);
		printf("Here is your Address: %s\n", numbers[4]);

		printf("1. Your Pin Code\n");
		printf("2. Your Phone number\n");
		printf("3. Your Address\n");

		printf("Enter your choice to update: ");		/* Select the desired option */
		scanf("%d", &opt);
		    
		while(pinFound)						/* Continue reading until the pin code found */
		{
		    if(opt == 1)
		    {							
		        printf("Enter another Pin code to update: ");
			getchar();
			fgets(updatedPin, sizeof(updatedPin), stdin);

			size_t len = strlen(updatedPin);					
			if(len > 0 && updatedPin[len - 1] == '\n'){	
			    updatedPin[--len] = '\0';					
			    fprintf(ft1, "%s,%s,%s,%s,%s,%s,%s,%s,%s\n", numbers[0], numbers[1], numbers[2], numbers[3], numbers[4], numbers[5], numbers[6], numbers[7], updatedPin);
			    printf("Your Pin code is successfully updated\n");
			    break;
			}	
		    }
		    if(opt == 2)
		    {
			printf("Enter another Phone number to update: ");
			getchar();
			fgets(updatedPhone, sizeof(updatedPhone), stdin);

			size_t len = strlen(updatedPhone);		/* Find the length of new pin code */				
			if(len > 0 && updatedPhone[len - 1] == '\n'){	/* Subtract 1 from pin code length that is 5 */
			    updatedPhone[--len] = '\0';			/* --len decrements the newline */		
			    fprintf(ft1, "%s,%s,%s,%s,%s,%s,%s,%s,%s\n", numbers[0], numbers[1], numbers[2], updatedPhone, numbers[4], numbers[5], numbers[6], numbers[7], numbers[8]);
			    printf("Your Phone number is successfully updated\n");
			    break;
			}
		    }
		    if(opt == 3)
		    {
			printf("Enter another Address to update: ");
			getchar();
			fgets(updatedAddress, sizeof(updatedAddress), stdin);

			size_t len = strlen(updatedAddress);					
			if(len > 0 && updatedAddress[len - 1] == '\n'){	
				updatedAddress[--len] = '\0';					
				fprintf(ft1, "%s,%s,%s,%s,%s,%s,%s,%s,%s\n", numbers[0], numbers[1], numbers[2], numbers[3], updatedAddress, numbers[5], numbers[6], numbers[7], numbers[8]);
				printf("Your Address is successfully updated\n");
				break;
			}
		    }
		}
	    }
	    /* All the Remaining accounts */
	    if(!pinFound){
		fprintf(ft1, "%s,%s,%s,%s,%s,%s,%s,%s,%s\n", numbers[0], numbers[1], numbers[2], numbers[3], numbers[4], numbers[5], numbers[6], numbers[7], numbers[8]);
	    }
	}
	fclose(fp2);
	fclose(ft1);

	/* Delete data from permanent file */
	fp2 = fopen(file, "w");
	fclose(fp2);	

	/* Copy data from the temporary file to the permanent file */
	ft1 = fopen(tempFile, "r");
	fp2 = fopen(file, "a");

	copying(ft1, fp2);
	fclose(fp2);
	fclose(ft1);

	/* Delete data from the temporary file */
	ft1 = fopen(tempFile, "w");
	fclose(ft1);

    }while(0);
    return 0;
}
							/* __________Choice #3: Transaction of Account_________ */

int userTransaction(FILE * fp3, FILE * fp4, FILE * fp5, FILE * ft1)
{
    int deposit, withdraw, addedAmount, subtractedAmount, x, saved;
    do
    {
        askPin(pinFind);
        while(read(fp3, pinFind)){
            if(pinFound)
	    {
	        while(choice[0] != two)
	        {
		    printf("Your total balance is: %s\n", numbers[7]);
		    printf("%c. Deposit the amount\n", one);
		    printf("%c. Withdraw the amount\n", two);

		    printf("Enter your choice: ");
		    getchar();
		    fgets(choice, sizeof(choice), stdin);

		    saved = strtol(choice, NULL, 10);			/* Convert string into integer */
		    if(saved <= 0 || saved >= 3){
		        printf("Sorry, wrong choice entered\n");
		        exit(0);
	            }
	            else
	            {
	                x = strtol(numbers[7], NULL, 10);
	                if(choice[0] == one)
	                {
	                    printf("Enter the amount to deposit: ");
		            scanf("%d", &deposit);

		            if(deposit <= 0){
		            printf("Sorry, wrong amount entered\n");
		            exit(0);
		        }			
	                else
		        {   /* Update the amount */
		            addedAmount = x + deposit;	
		            fprintf(ft1, "%s,%s,%s,%s,%s,%s,%s,%d,%s\n", numbers[0], numbers[1], numbers[2], numbers[3], numbers[4], numbers[5], numbers[6], addedAmount, numbers[8]);
		            printf("Your present balance is: %d\n", addedAmount);
			    /* Show the system time */	
		            time_t now = time(NULL);	
		            struct tm t = *localtime(&now);
		            printf("%d rupees is deposited on %d-%d-%d\n", deposit, t.tm_mday, t.tm_mon+1, t.tm_year+1900);
		            fprintf(fp4, "%s,%s,%s,%s,%d,%d-%d-%d\n", numbers[0], numbers[2], numbers[3], numbers[8], deposit, t.tm_mday, t.tm_mon+1, t.tm_year+1900);
		            break;
		        }			
	            }
	            if(choice[0] == two)
	            {
		        printf("Enter the amount to withdraw: ");
		        scanf("%d", &withdraw);

		        if(withdraw <= 0){
		            printf("Sorry, wrong amount entered\n");
		            exit(0);
		        }			
		        else
		        {
		            subtractedAmount = x - withdraw;
		            fprintf(ft1, "%s,%s,%s,%s,%s,%s,%s,%d,%s\n", numbers[0], numbers[1], numbers[2], numbers[3], numbers[4], numbers[5], numbers[6], subtractedAmount, numbers[8]);
		            printf("Your present balance is: %d\n", subtractedAmount);

		            time_t now = time(NULL);
		            struct tm t = *localtime(&now);
		            printf("%d rupees is withdrawn on %d-%d-%d\n", withdraw, t.tm_mday, t.tm_mon+1, t.tm_year+1900);
		            fprintf(fp5, "%s,%s,%s,%s,%d,%d-%d-%d\n", numbers[0], numbers[2], numbers[3], numbers[8], withdraw, t.tm_mday, t.tm_mon+1, t.tm_year+1900);
		            break;
		        }			
	            }
	        }
            }
        }
        /* All the remaining accounts */
        if(!pinFound){
            fprintf(ft1, "%s,%s,%s,%s,%s,%s,%s,%s,%s\n", numbers[0], numbers[1], numbers[2], numbers[3], numbers[4], numbers[5], numbers[6], numbers[7], numbers[8]);
        }
    }	
    fclose(ft1);
    fclose(fp3);

    /* Delete the data from original file */
    fp3 = fopen(file, "w");
    fclose(fp3);

    /* Copy the data from temporary file to original file */
    ft1 = fopen(tempFile, "r");
    fp3 = fopen(file, "a");

    copying(ft1, fp3);	
    fclose(ft1);
    fclose(fp3);

    /* Delete the data from the temporary file */
    ft1 = fopen(tempFile, "w");
    fclose(ft1);

    }while(0);
    return 0;
}

							/* __________Choice #4: Show the account Information_________ */

int accountInfo(FILE * fp6, FILE * fp7)
{
    do
    {
	askPin(pinFind);
	while(read(fp6, pinFind)){
	    if(pinFound)
 	        for(int i=0; i<9; i++)
		    printf("Here is your %s: %s\n",listing[i], numbers[i]);
	}
	while(fgets(string, STRING_LEN, fp7))
	{
	    lineOne = strtok(string, "\n");
	    pinFound = strstr(lineOne, pinFind);		
	    if(pinFound){
		checkDeposit(string);						/* Get the actual data record */
	    }		
	}
	printf("Here is your last Deposit Date: %s\n", max.datestr);	/* Print the last Deposit Date */

    }while(0);
    return 0;
}

							/* __________Choice #5: Remove an account_________ */
int accountRemoval(FILE * fp6, FILE * fp7, FILE * fp8, FILE * ft1, FILE * ft2, FILE * ft3)
{
    do
    {
        askPin(pinFind);
	printf("Confirm it [y/n]: ");					/* Confirm to delete */
	getchar();
	scanf("%c", &option);

	if(option == 'y')
        {
	    while(read(fp6, pinFind)){
	        if(!pinFound){
		    fprintf(ft1, "%s,%s,%s,%s,%s,%s,%s,%s,%s\n", numbers[0], numbers[1], numbers[2], numbers[3], numbers[4], numbers[5], numbers[6], numbers[7], numbers[8]);
	        }
	    }
	    while(read(fp7, pinFind)){
		if(!pinFound){
		    fprintf(ft2, "%s,%s,%s,%s,%s,%s\n", numbers[0], numbers[1], numbers[2], numbers[3], numbers[4], numbers[5]);
		}
	    }
	    while(read(fp8, pinFind)){
		if(!pinFound){
		    fprintf(ft3, "%s,%s,%s,%s,%s,%s\n", numbers[0], numbers[1], numbers[2], numbers[3], numbers[4], numbers[5]);
		}
	    }
	    printf("Your account is deleted\n");
	    break;
        }
	else if(option == 'n'){
	    printf("Your account is not deleted\n");
	    exit(0);
	}

    }while(0);
    fclose(fp6);
    fclose(fp7);
    fclose(fp8);
    fclose(ft1);
    fclose(ft2);
    fclose(ft3);

    /* Delete the data from original file */
    fp6 = fopen(file, "w");
    fp7 = fopen(depositRecord, "w");
    fp8 = fopen(withdrawRecord, "w");
    fclose(fp6);
    fclose(fp7);
    fclose(fp8);

    /* Copy the data from temporary file to original file */
    ft1 = fopen(tempFile, "r");
    fp6 = fopen(file, "a");

    ft2 = fopen(tDepositRecord, "r");
    fp7 = fopen(depositRecord, "a");

    ft3 = fopen(tWithdrawRecord, "r");
    fp8 = fopen(withdrawRecord, "a");

    copying(ft1, fp6);
    copying(ft2, fp7);
    copying(ft3, fp8);
    fclose(fp6);
    fclose(fp7);
    fclose(fp8);
    fclose(ft1);
    fclose(ft2);
    fclose(ft3);

    /* Delete the data from temporary file */
    ft1 = fopen(tempFile, "w");
    ft2 = fopen(tDepositRecord, "w");
    ft3 = fopen(tWithdrawRecord, "w");	
    fclose(ft1);
    fclose(ft2);
    fclose(ft3);

    return 0;
}
							/* __________Choice #6: Main Function_________ */

int main()
{
    /* Temporary files */
    FILE * ft1 = fopen(tempFile, "a");
    FILE * ft2 = fopen(tDepositRecord, "a");
    FILE * ft3 = fopen(tWithdrawRecord, "a");
	
    /* Permanent files */
    FILE * fp1 = fopen(file, "a");
    FILE * fp2 = fopen(file, "r");
    FILE * fp3 = fopen(file, "r");
    FILE * fp4 = fopen(depositRecord, "a");
    FILE * fp5 = fopen(withdrawRecord, "a");
    FILE * fp6 = fopen(file, "r");
    FILE * fp7 = fopen(depositRecord, "r");
    FILE * fp8 = fopen(withdrawRecord, "r");

    /* Show the Main menu */
    printf("BANKING MANAGEMENT SYSTEM\n");
    printf("\nWELCOME TO THE MAIN MENU\n");

    printf("1. Create new account\n");
    printf("2. Update existing account\n");
    printf("3. For Transactions\n");
    printf("4. Show the details of account\n");
    printf("5. Removal of account\n");
    printf("6. Exit\n");

    /* Give choice to select */
    printf("Enter your choice: ");
    fgets(choice, sizeof(choice), stdin);
   
    switch(choice[0])
    {
        case '1':
		newAccount(fp1);
		break;
	case '2':
		updateAccount(fp2, ft1);
		break;
	case '3':
		userTransaction(fp3, fp4, fp5, ft1);
		break;
	case '4':
		accountInfo(fp6, fp7);
		break;
	case '5':
		accountRemoval(fp6, fp7, fp8, ft1, ft2, ft3);
		break;
	case '6':
		printf("Okay, Good Bye!\n");
		break;
	default:
		printf("Sorry, wrong option\n");
		break;
    }
    return 0;
}
