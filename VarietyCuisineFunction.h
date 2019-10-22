
#include "VarietyCuisineFunction.c"

int displayMenu(char[], char[][20], char[], int);

void cashier();
void newCard();
void topupCard();
void refundCard();
void listCard();

void booth();

/* getAmount of credit in a cashcard
 * param id: id of cashcard
 * return: amount of credit or -1 not found
*/

int getAmount(int);

/* updateBalance of the credit in a cashcard
 * param id: id of cashcard
 * param amount: the amount of change to the credit
 *               positif means topup, negative means deduce/payment
 * return: success=0, fail =-1
*/
int updateBalance(int, int);
