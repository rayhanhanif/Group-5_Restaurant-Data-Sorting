#include <string.h>
#include <stdio.h>
#include <stdlib.h>

FILE *fptr;
int cardNumber[1000],i,n;
char *token;
char cardnumber[1000];

FILE *fptr2;
int cardAmount[1000] = {0},j,m;
char *token2;
char cardamount[1000];

typedef struct cashcard {
    int id;
    int amount;
} cashcard;
cashcard validCards[1000];
int lastCardIndex=0;

void cashier() {
    //TO DO display menu
    //handle
    int userSelectValue=-1;
    char menu[4][20]={"New Card", "Top Up Card","Refund", "List Cards"};
    while (userSelectValue != 0)
    {
        userSelectValue = displayMenu("Variety Cuisine Cashier",menu,"Please select Operation!",4);
        switch (userSelectValue)
        {
            case 1: newCard(); break;
            case 2: topupCard(); break;
            case 3: refundCard(); break;
            case 4: listCard(); break;
        }
    }
}

void systemUpdate() {
    fptr = fopen("VarietyCuisineDataTemp.txt","w");
    fptr2 = fopen("VarietyCuisineMoneyTemp.txt","w");
    for(i = 0; i < lastCardIndex; i++) {
        fprintf(fptr, "%d,", validCards[i].id);
        fprintf(fptr2, "%d,", validCards[i].amount);
    }
    fclose(fptr);
    fclose(fptr2);
    remove("VarietyCuisineData.txt");
    remove("VarietyCuisineMoney.txt");
    rename("VarietyCuisineDataTemp.txt", "VarietyCuisineData.txt");
    rename("VarietyCuisineMoneyTemp.txt", "VarietyCuisineMoney.txt");
    printf("System has succesfully updated!");
}


    void newCard(){
/////////////////////////////////////////////////
    cashcard newCard = { 0, 0};
    fptr = fopen("VarietyCuisineData.txt","a+");
    fptr2 = fopen("VarietyCuisineMoney.txt","a+");
    if(fptr == NULL) {
        printf("Error Opening File");
        return -1;
    }
    if(fptr2 == NULL) {
        printf("Error Opening File");
        return -1;
    }
    fscanf(fptr,"%s",cardnumber);
    fscanf(fptr2,"%s",cardamount);
    token = strtok(cardnumber, ","); //stringtoken function is to tokenize a string into substring
//    token2 = strtok(cardamount, ","); --->> DO NOT PUT HERE!! READ THE STRTOK FUNCTION WORKS

    i = 0;
    while (token != NULL) {
        cardNumber[i] = atoi(token);
        token = strtok(NULL, ",");
        i++;
    }
    token2 = strtok(cardamount,","); // --->> SHOULD BE PUT RIGHT HERE FOR THE STRTOK FUNCTION
    j = 0;
    while (token2 != NULL) {
        cardAmount[j] = atoi(token2);
        token2 = strtok(NULL, ",");
        j++;
    }
    n = i;
    lastCardIndex = i;
    for(i=0; i<n; i++ ) {
        validCards[i].id = cardNumber[i];
        validCards[i].amount = cardAmount[i];
        printf("%d\t",validCards[i].amount);
        printf("%d\n",validCards[i].id);
    }


    printf("Enter Card ID Number:");
    scanf("%d", &newCard.id);

    //checking from the assign validCards
    for(i=0; i<n; i++ ) {
        if(newCard.id == validCards[i].id) goto there;
    }


    if ( getAmount(newCard.id) < 0 ) {
        validCards[lastCardIndex++].id = newCard.id;
        printf("Card ID %d is now registered.",newCard.id);
        fprintf(fptr2, "%d,", newCard.amount);
        fprintf(fptr, "%d,",newCard.id);

        }
    else {
        there:
        printf("Card ID %d has already been registered \
               with current amount of Rp. %7d,-.\n",
                newCard.id, getAmount(newCard.id));
    }

    fclose(fptr);
    fclose(fptr2);
    system("pause");
}

int getAmount(int id) {
    int i;
    for ( i=0; i<lastCardIndex; i++) {
        if (validCards[i].id == id) {
            return validCards[i].amount;
        }
    }
    return -3;
}

void payment(int a) {
    int i,answer;
    int exit = 1;
    while(exit != 0) {
        cashcard newCard = { 0, 0};
        printf("\nEnter your card ID number:");
        scanf("%d", &newCard.id);
        for(i=0;i<lastCardIndex;i++) {
            if(validCards[i].id == newCard.id ) {
                printf("You are going to purchase for the item listed above. Proceed?\n");
                printf("1. Yes\n2. Cancel\n");
                printf("Answer:");
                scanf("%d",&answer);
                if(answer == 1) {
                    validCards[i].id = newCard.id;
                    validCards[i].amount -= a;
                    if(validCards[i].amount < 0) {
                        printf("sorry, your balance is not enough\n");
                        printf("Please top up your balance first in the cashier option\n");
                        validCards[i].amount += a;
                        system("pause");
                        exit = 0;
                    }
                    printf("The card ID %d balance is now %d\n\n",validCards[i].id,validCards[i].amount);
                    system("pause");
                    exit = 0;
                }
                else {
                    printf("You have canceled your order");
                    exit = 0;
                }
            }
        }
    }
}

void topupCard(){
    int id=0, amount=0;

    printf("Enter Card ID Number:");
    scanf("%d", &id);
    if (getAmount(id) >= 0) {
        //topup
        printf("Current amount of Card ID %d is Rp. %7d,-.\n",
                id, getAmount(id));
        printf("Enter Top Up Amount: ");
        scanf("%d", &amount);
        updateBalance(id, amount);
        printf("Current amount of Card ID %d is Rp. %7d,-.\n",
                id, getAmount(id));
    } else {
        // Refuse
        printf ("Card ID %d is not registered.\n", id);
    }
    system("pause");
}

int updateBalance(int id, int amount) {

    int i;
    for ( i=0; i<lastCardIndex; i++) {
        if (validCards[i].id == id) {
            validCards[i].amount += amount;
            cardAmount[i] = validCards[i].amount;
            return 1;
        }
    }

    return 0;
}


void refundCard(){
    int id=0; int answer;
    printf("Enter Card ID Number:");
    scanf("%d", &id);
    if (getAmount(id) >= 0) {
        printf("Current amount of Card ID %d is Rp. %7d,-.\n",id, getAmount(id));
        printf("Refund (1=Yes)? ");
        scanf("%d", &answer);
        if (answer == 1) {
            //search for id location in array
            int i;
            for (i=0; i<lastCardIndex; i++) {
                if (validCards[i].id == id) {
                    int j;
                    for ( j=i; j < (lastCardIndex-1);j++)
                        validCards[j] = validCards[j+1];
                        --lastCardIndex;
                    break;
                }
            }
            printf("Card is unregistered, please proceed with refund.\n");
        }
    }
    else {
        // Refuse
        printf ("Card ID %d is not registered.\n", id);
    }
    systemUpdate();
    system("pause");

}

void listCard() {
    printf("List of Registered Cards:\n");
    int p;
    for ( p=0; p<lastCardIndex; p++) {
        printf("Card ID: %10d, Amount: Rp.%7d,-\n",
               validCards[p].id,validCards[p].amount);
    }
    system("pause");
}

void booth() {
    int cardID;
    int totalPrice=0;
    int mp1=0,mp2=0,mp3=0,mp4=0,mp5=0,mp6=0,mp7=0,mp8=0,mp9=0,mp10=0;
    int food;
    int repeat=-1;
    int answer,i,maxMenuNumber=5;
    int userSelectValue =-1;
    char menu[10][20] = {"Onion\tRp15k","Garlic\tRp20k","Brocoli\tRp5k","Eggplant\tRp10k","Peanut\tRp1k","Fish\t\tRp10k",
    "Chicken\tRp20k","Spinach\tRp5k","Banana\tRp2k","Noodle\tRp30k"};
    while(userSelectValue!=0) {//initial while
        userSelectValue = displayMenu("Variety Cousine Booth", menu, "Select your food", 10);
        switch(userSelectValue) {
            case 1: totalPrice+=15000; mp1 +=1; break;
            case 2: totalPrice+=20000; mp2 +=1; break;
            case 3: totalPrice+=5000; mp3 +=1; break;
            case 4: totalPrice+=10000; mp4 +=1; break;
            case 5: totalPrice+=1000; mp5 +=1; break;
            case 6: totalPrice+=10000; mp6 +=1; break;
            case 7: totalPrice+=20000; mp7 +=1; break;
            case 8: totalPrice+=5000; mp8 +=1; break;
            case 9: totalPrice+=2000; mp9 +=1; break;
            case 10: totalPrice+=30000; mp10 +=1; break;
        }   repeat+=1;

    }
    printf("\n\nYou purchased %d item for Rp%d\n",repeat,totalPrice);
    printf("Proceed to the payment?\n1. Yes\n2. Back and add more\n3. Back and reduce\nAnswer:");
    scanf("%d",&answer);
while(answer != 1) { //big while
    while (answer == 2) { //small while
        userSelectValue=-1;
        repeat-=1;
        while(userSelectValue!=0) {
            userSelectValue = displayMenu("Variety Cousine Booth", menu, "Select your food you want to add", 10);
            switch(userSelectValue) {
            case 1: totalPrice+=15000; mp1 +=1; break;
            case 2: totalPrice+=20000; mp2 +=1; break;
            case 3: totalPrice+=5000; mp3 +=1; break;
            case 4: totalPrice+=10000; mp4 +=1; break;
            case 5: totalPrice+=1000; mp5 +=1; break;
            case 6: totalPrice+=10000; mp6 +=1; break;
            case 7: totalPrice+=20000; mp7 +=1; break;
            case 8: totalPrice+=5000; mp8 +=1; break;
            case 9: totalPrice+=2000; mp9 +=1; break;
            case 10: totalPrice+=30000; mp10 +=1; break;
        }
            repeat+=1;
        }
            printf("\n\nYou purchased %d item for Rp%d\n",repeat,totalPrice);
            printf("Proceed to the payment?\n1. Yes\n2. Back and add more\n3. Back and reduce\nAnswer:");
            scanf("%d",&answer);
        }
    while (answer == 3) {//small while
        userSelectValue=-1;
        repeat+=1;
        while(userSelectValue!=0) {
            userSelectValue = displayMenu("Variety Cousine Booth", menu, "Select your food you want to reduce", 10);
            switch(userSelectValue) {
            case 1: {if(mp1<=0) {printf("Your selected food amount has already reached 0!\n"); repeat+=1; system("pause"); break;} else {totalPrice-=15000; mp1 -=1; break;}}
            case 2: {if(mp2<=0) {printf("Your selected food amount has already reached 0!\n"); repeat+=1; system("pause"); break;}else {totalPrice-=20000; mp2 -=1; break;}}
            case 3: {if(mp3<=0) {printf("Your selected food amount has already reached 0!\n"); repeat+=1; system("pause"); break;}else {totalPrice-=5000; mp3 -=1; break;}}
            case 4: {if(mp4<=0) {printf("Your selected food amount has already reached 0!\n"); repeat+=1; system("pause"); break;}else {totalPrice-=10000; mp4 -=1; break;}}
            case 5: {if(mp5<=0) {printf("Your selected food amount has already reached 0!\n"); repeat+=1; system("pause"); break;}else {totalPrice-=1000; mp5 -=1; break;}}
            case 6: {if(mp6<=0) {printf("Your selected food amount has already reached 0!\n"); repeat+=1; system("pause"); break;}else {totalPrice-=10000; mp6 -=1; break;}}
            case 7: {if(mp7<=0) {printf("Your selected food amount has already reached 0!\n"); repeat+=1; system("pause"); break;}else {totalPrice-=20000; mp7 -=1; break;}}
            case 8: {if(mp8<=0) {printf("Your selected food amount has already reached 0!\n"); repeat+=1; system("pause"); break;}else {totalPrice-=5000; mp8 -=1; break;}}
            case 9: {if(mp9<=0) {printf("Your selected food amount has already reached 0!\n"); repeat+=1; system("pause"); break;}else {totalPrice-=2000; mp9 -=1; break;}}
            case 10: {if(mp10<=0) {printf("Your selected food amount has already reached 0!\n"); repeat+=1; system("pause"); break;}else {totalPrice-=30000; mp10 -=1; break;}}
            }
            repeat-=1;
        }
            printf("\n\nYou purchased %d item for Rp%d\n",repeat,totalPrice);
            printf("Proceed to the payment?\n1. Yes\n2. Back and add more\n3. Back and reduce\nAnswer:");
            scanf("%d",&answer);
        }
}
        system("cls");
        printf("Receipt\n");
        printf("--------------------\n");
        purchase(mp1,mp2,mp3,mp4,mp5,mp6,mp7,mp8,mp9,mp10);
        payment(totalPrice);
    }

int displayMenu(char title[],char menu[][20],char instruction[],int maxMenuNumber) {
    int userInput;
    int i;
    for (i=0; i<24; i++) printf("\n");
    printf("%s\n", title);
    for (i=0; i<maxMenuNumber; i++){
        printf("%d: %s\n", i+1, menu[i]);
    }
    printf("\n0: Exit/Back\n");
    printf("%s\n", instruction);
    scanf("%d",&userInput);
    while ( userInput<0 || userInput > maxMenuNumber)
    {
        printf("Please enter the correct number!\n");
        scanf("%d",&userInput);
    }

    return userInput;
}


void purchase(int q, int w, int e, int r, int t, int y, int u, int i, int o, int p) {
    printf("Onion\tRp15k\tamount: %d\n",q);
    printf("Garlic\tRp20k\tamount: %d\n",w);
    printf("Brocoli\tRp5k\tamount: %d\n",e);
    printf("EggplantRp10k\tamount: %d\n",r);
    printf("Peanut\tRp1k\tamount: %d\n",t);
    printf("Fish\tRp10k\tamount: %d\n",y);
    printf("Chicken\tRp20k\tamount: %d\n",u);
    printf("Spinach\tRp5k\tamount: %d\n",i);
    printf("Banana\tRp2k\tamount: %d\n",o);
    printf("Noodle\tRp30k\tamount: %d\n",p);


}



