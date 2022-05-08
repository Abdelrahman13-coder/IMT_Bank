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



typedef struct bank_account{
    char *full_name;
    char *address;
    char national_id[15];  //national id must consist of 14 digit numbers
    int age;
    char bank_acc_id[11];
    char guardian_nat_id[15];   // guardian national id must consist of 14 digits numbers
    char *status;
    float balance;
    char *password;  //Random Password will be generated for each account during creation of it
}Bank_Account;




/****************************************/
/*         Functions Prototypes         */
/****************************************/

void gotoxy(int x, int y);
void displayMainMenu();
void displayAdminMainMenu();
void displayClientMainMenu();
char* randomPasswordGeneration(int N);
Bank_Account createNewAccount();




/****************************************/
/*            Main Function             */
/****************************************/

int main()
{
    int window_choice, admin_choice, client_choice, choice;
    char filename[15] , bank_account_id[11], national_id[15];
    float amount;
    FILE *fp, *fptr;
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
                    // create filename based on national id just for now
                    stpcpy(filename, acc.national_id);  // todo change to bank account id
                    printf("\n\n%s", filename);
                    fp = fopen(strcat(filename, ".dat"), "w");
                    printf("\nOpened");
                    fwrite(&acc, sizeof(acc), 1, fp);
                    if(fwrite != 0){
                        printf("Registered Succesfully\n");
                    }
                    printf("\nPress any key to return to the main menu...");
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


int main_func()
{
    int option,choice;
    Bank_Account acc;
    char filename[15] , bank_account_id[11], national_id[15];
    float amount;
    FILE *fp, *fptr;

    if (option == 2){
        system("cls");
        printf("\nEnter Bank Account ID\n");
        //scanf("%s",bank_account_id);
        scanf("%s",national_id);     //todo change to bank account id
        fp = fopen(strcat(national_id,".dat"),"r");
		if(fp == NULL){
            printf("Account not registered");
		}
		else{
		    fread(&acc,sizeof(acc),1,fp);
			fclose(fp);
            printf("Account registered\n");
//            //printf("%d",acc.age);
            printf("\n1.Make transaction");
            printf("\n2.Change Account Status");
            printf("\n3.Get Cash");
            printf("\n4.Deposite in Account");
            printf("\n5.Return to Main Menu\n");
            printf("\nEnter choice ");     //how
            scanf("%d",&choice);
            system("cls");
            if (choice == 1){
                printf("\nMake transaction");
                printf("\nEnter Bank Account ID to transfer to");
                scanf("%s",national_id);
                printf("\nEnter the transfer amount");
                scanf("%f",&amount);
                if (acc.balance < amount){
                    printf("\nNot enough money to transfer");
                }

//                else{
//                    fptr = fopen(strcat(national_id, ".dat","r"));     //ctr shift c
//                    if(fptr == Null){
//                        printf()
//                    }
//                }
            }

	}

    }
    else if (option == 3){
        exit(0);
    }

    return 0;
}




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

// Function to randomly generate password of length N
char* randomPasswordGeneration(int N)
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


Bank_Account createNewAccount()
{
    Bank_Account acc;

    printf("\n Creating New Account:");
    printf("\n ---------------------");

    fflush(stdin);
    printf("\n    Full Name: ");
    gets(acc.full_name);
    printf("%s", acc.full_name);

    fflush(stdin);
    printf("\n    Full Address: ");
    gets(acc.address);
    printf("%s", acc.address);

    printf("\n    Age: ");
    scanf("%d", &acc.age);
    printf("%d", acc.age);

    printf("\n    National ID: ");
    scanf("%s", acc.national_id);
    printf("%s", acc.national_id);

    if (acc.age < 21){
        fflush(stdin);
        printf("\n    Guardian National ID: ");
        scanf("%s", acc.guardian_nat_id);
        printf("%s", acc.guardian_nat_id);
    }

    printf("\n    Balance: ");
    scanf("%f", &acc.balance);
    printf("%f", acc.balance);

    acc.status = "Active";

    printf("\n\n Your automatically generated Bank Account Credentials:");

    printf("\n    Bank Account ID: ");

    acc.password = randomPasswordGeneration(8);
    printf("\n    Password: %s", acc.password);

    return acc;
}
