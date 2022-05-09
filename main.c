/******************************************************************/
/*   Authors     : Abdelrahman Tarek - Aya Hany - Lauren Safwat   */
/*   Description : IMT Bank System                                */
/*   Date        : 8 May 2022                                     */
/*   Version     : V1.0                                           */
/******************************************************************/


#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>


#define atoa(x) #x


typedef struct bank_account{
    char *full_name;            // must enter at least first four names
    char *address;
    char national_id[15];       //national id must consist of 14 digit numbers
    int age;
    char bank_acc_id[11];
    char guardian_nat_id[15];   // guardian national id must consist of 14 digits numbers
    char status[11];
    float balance;
    char *password;             //Random Password will be generated for each account during creation of it
}Bank_Account;




/****************************************/
/*         Functions Prototypes         */
/****************************************/

void gotoxy(int x, int y);
void displayMainMenu();
void displayAdminMainMenu();
void displayClientMainMenu();
//int getLatestBankID();
//void saveLatestBankID(int id);
char* bankIDGenerator();
char* randomPasswordGenerator(int N);
int no_of_spaces(char *name);
int isNumber(char s[]);
Bank_Account createNewAccount();
Bank_Account openExistingAccount();
void saveAccount(Bank_Account acc);




/****************************************/
/*            Main Function             */
/****************************************/

int main()
{
    int window_choice, admin_choice, client_choice, choice;
    Bank_Account acc;

    home:
        system("cls");
        displayMainMenu();
        scanf("%d", &window_choice);

        main_menu:
            system("cls");
            gotoxy(55, 0);
            printf("IMT Bank System");
            gotoxy(55, 1);
            printf("---------------");

            switch(window_choice){
            case 1:
                displayAdminMainMenu();
                scanf("%d", &admin_choice);

                system("cls");
                gotoxy(55, 0);
                printf("IMT Bank System");
                gotoxy(55, 1);
                printf("---------------");

                switch(admin_choice){
                case 1:
                    acc = createNewAccount();
                    saveAccount(acc);
                    printf("\n\nPress any key to return to the main menu...");
                    getch();
                    goto main_menu;
                    break;

                case 2:
                    printf("Press any key to return to the main menu...");
                    getch();
                    goto main_menu;
                    break;

                default:
                    goto home;
                }

                break;

            case 2:
                displayClientMainMenu();
                scanf("%d", &client_choice);

                switch(client_choice) {
                case 1:
                    printf("Press any key to return to the main menu...");
                    getch();
                    goto main_menu;
                    break;

                case 2:
                    printf("Press any key to return to the main menu...");
                    getch();
                    goto main_menu;
                    break;

                case 3:
                    printf("Press any key to return to the main menu...");
                    getch();
                    goto main_menu;
                    break;

                case 4:
                    printf("Press any key to return to the main menu...");
                    getch();
                    goto main_menu;
                    break;

                default:
                    goto home;
                }
                break;

            default:
                exit(0);
            }
}


//int main_func()
//{
//    int option,choice;
//    Bank_Account acc;
//    char filename[15] , bank_account_id[11], national_id[15];
//    float amount;
//    FILE *fptr, *fptr;
//
//    if (option == 2){
//        system("cls");
//
//		if(fptr == NULL){
//            printf("Account not registered");
//		}
//		else{
//		    fread(&acc,sizeof(acc),1,fptr);
//			fclose(fptr);
//            printf("Account registered\n");
////            //printf("%d",acc.age);
//            printf("\n1.Make transaction");
//            printf("\n2.Change Account Status");
//            printf("\n3.Get Cash");
//            printf("\n4.Deposite in Account");
//            printf("\n5.Return to Main Menu\n");
//            printf("\nEnter choice ");     //how
//            scanf("%d",&choice);
//            system("cls");
//            if (choice == 1){
//                printf("\nMake transaction");
//                printf("\nEnter Bank Account ID to transfer to");
//                scanf("%s",national_id);
//                printf("\nEnter the transfer amount");
//                scanf("%f",&amount);
//                if (acc.balance < amount){
//                    printf("\nNot enough money to transfer");
//                }
//
////                else{
////                    fptr = fopen(strcat(national_id, ".dat","r"));     //ctr shift c
////                    if(fptr == Null){
////                        printf()
////                    }
////                }
//            }
//
//	}
//
//    }
//    else if (option == 3){
//        exit(0);
//    }
//
//    return 0;
//}




/****************************************/
/*        Functions Definitions         */
/****************************************/

void gotoxy(int x, int y)
{
   COORD coord;
   coord.X = x;
   coord.Y = y;
   SetConsoleCursorPosition(GetStdHandle ( STD_OUTPUT_HANDLE ), coord);
}


void displayMainMenu()
{
    gotoxy(50, 0);
    printf("Welcome to IMT Bank System");
    gotoxy(50, 1);
    printf("--------------------------");
    gotoxy(2, 3);
    printf("1- Login as an admin");
    gotoxy(2, 4);
    printf("2- Login as a client");
    gotoxy(2, 5);
    printf("3- Exit the System");
    gotoxy(2, 7);
    printf("Enter your choice: ");
}


void displayAdminMainMenu()
{
    gotoxy(2, 3);
    printf("- Admin Main Menu:");
    gotoxy(2, 4);
    printf("------------------");
    gotoxy(4, 5);
    printf("1- Create New Account");
    gotoxy(4, 6);
    printf("2- Open Existing Account");
    gotoxy(4, 7);
    printf("3- Log out");
    gotoxy(4, 9);
    printf("Enter your choice: ");
}


void displayClientMainMenu()
{
    gotoxy(2, 3);
    printf("- Client Main Menu:");
    gotoxy(2, 4);
    printf("-------------------");
    gotoxy(4, 5);
    printf("1- Make Transaction");
    gotoxy(4, 6);
    printf("2- Change Account Password");
    gotoxy(4, 7);
    printf("3- Get Cash");
    gotoxy(4, 8);
    printf("4- Deposit in Account");
    gotoxy(4, 9);
    printf("5- Log out");
    gotoxy(4, 11);
    printf("Enter your choice: ");
}



/**********************************************************/


char* bankIDGenerator(){
    char initial_bankID[11];
    int bankID;
    char snum[11];
    char *last_line;
    FILE *fptr;
    char filename[15];
    *filename = "bank_ids";
    *initial_bankID = "1000000000";
    fptr=fopen(strcat(filename,".dat"),"w");
    fwrite(&initial_bankID,sizeof(initial_bankID),1,fptr);

    static const long max_len = 55+ 1;  // define the max length of the line to read
    char buff[max_len + 1];             // define the buffer and allocate the length

    if ((fptr = fopen(filename, "rb")) != NULL)  {      // open fptr. I omit error checks

        fseek(fptr, -max_len, SEEK_END);            // set pointer to the end of fptr minus the length you need. Presumably there can be more than one new line caracter
        fread(buff, max_len-1, 1, fptr);            // read the contents of the fptr starting from where fseek() positioned us
        fclose(fptr);                               // close the fptr

        buff[max_len-1] = '\0';                   // close the string
        char *last_newline = strrchr(buff, '\n'); // find last occurrence of newlinw
        *last_line = last_newline+1;
    }
    if (last_line != initial_bankID){
        bankID = atoi(last_line) + 1;
 //       itoa(bankID, snum, 22);
        *snum = atoa(bankID);
        fptr=fopen(strcat(filename,".dat"),"w");
        fwrite(&snum,sizeof(snum),1,fptr);
    }
    return last_line;
}


char* randomPasswordGenerator(int N)
{
    int i = 0;
    int randomizer = 0;

    // Seed the random-number generator with current time so that the numbers will be different every time
    srand((unsigned int)(time(NULL)));

    char numbers[] = "0123456789";
    char letters[] = "abcdefghijklmnoqprstuvwyzx";
    char LETTERS[] = "ABCDEFGHIJKLMNOQPRSTUYWVZX";

    char *password = malloc(N+1);

    for (i = 0; i < N; i++) {
        randomizer = rand() % 3;
        switch (randomizer) {
            case 0:
                password[i] = numbers[rand() % 10];
                break;
            case 1:
                password[i] = letters[rand() % 26];
                break;
            case 2:
                password[i] = LETTERS[rand() % 26];
                break;
        }
    }

    password[N] = '\0';
    return password;
}


int no_of_spaces(char *name){
    int spaces = 0;
    for(int i = 0; name[i] != '\0'; i++)
        if (name[i] == ' ')
            spaces++;
    return spaces;
}


int isNumber(char s[])
{
    for (int i = 0; s[i]!= '\0'; i++)
        if (!isdigit(s[i]))
            return 0;
    return 1;
}


Bank_Account createNewAccount()
{
    Bank_Account acc;

    printf("\n Creating New Account:");
    printf("\n ---------------------\n\n");

    /*Full Name*/
    do {
        if(!acc.full_name || acc.full_name[0])
            printf("\x1b[A\x1b[A    *You must enter at least first four names");
        fflush(stdin);
        printf("\n\33[2K    Full Name: ");
        gets(acc.full_name);
    } while(no_of_spaces(acc.full_name) < 3);

    /*Full Address*/
    fflush(stdin);
    printf("\n\n    Full Address: ");
    gets(acc.address);
//    printf("%s", acc.address);

    /*Age*/
    printf("\n\n    Age: ");
    scanf("%d", &acc.age);
    printf("\n");

    /*National ID*/
    stpcpy(acc.national_id, "0");
    do {
        if(strlen(acc.national_id) > 1)
            printf("\x1b[A\x1b[A\33[2K    *National ID must consist of 14-digit Number");
        fflush(stdin);
        printf("\n\33[2K    National ID: ");
        scanf("%s", acc.national_id);
    } while((strlen(acc.national_id) != 14) || (!isNumber(acc.national_id)));
    printf("\n\n");

    /*Guardian National ID*/
    stpcpy(acc.guardian_nat_id, "0");
    if (acc.age < 21){
        do {
            if(strlen(acc.guardian_nat_id) > 1)
                printf("\x1b[A\x1b[A    *National ID must consist of 14-digit Number\n");
            fflush(stdin);
            printf("\33[2K    Guardian National ID: ");
            scanf("%s", acc.guardian_nat_id);
        } while((strlen(acc.guardian_nat_id) != 14) || (!isNumber(acc.guardian_nat_id)));
    }

    /*Balance*/
    printf("\n\n    Balance: ");
    scanf("%f", &acc.balance);

    printf("\n\n Your automatically generated Bank Account Credentials:");

    stpcpy(acc.bank_acc_id, bankIDGenerator());
    printf("\n    Bank Account ID: %s", acc.bank_acc_id);

    acc.password = randomPasswordGenerator(8);
    printf("\n    Password: %s", acc.password);

    /*Account Status*/
    stpcpy(acc.status, "Active");

    return acc;
}


void saveAccount(Bank_Account acc)
{
    char filename[11];
    FILE *fptr;

    stpcpy(filename, acc.bank_acc_id);
    fptr = fopen(strcat(filename, ".dat"), "w");
    fwrite(&acc, sizeof(acc), 1, fptr);
    if(fwrite != 0){
        printf("\n\n Registered Succesfully");
    }
}


Bank_Account openExistingAccount()
{
    Bank_Account acc;
    char bank_account_id[11];
    FILE *fptr;

    printf("\n Enter Bank Account ID: ");
    scanf("%s", bank_account_id);

    fptr = fopen(strcat(bank_account_id,".dat"), "r");
    if(fptr == NULL)
        printf("\n Account not registered!");
    else
        fread(&acc, sizeof(acc), 1, fptr);
    fclose(fptr);
    return acc;
}
