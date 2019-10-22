# Group 5_Restaurant-Data-Sorting
This mini project is created using Code Blocks and the functions that are used in this program are array, function, and header. 

Our program is about a data sorting program which is applied in restaurants. The program has two features which are to store the id card number and the amount of money stored in it, and to store the data of the ordered food of the customer. To store the card ID number and the amount of money in it, we use the fptr, fscanf, fopen, fclose and strtoken to keep and open the data from the txt file. 

![Screenshot (81)](https://serving.photos.photobox.com/22524907a01a77fcc18ab70abd9270ef1e4958ed4645a3938fd6961af7d8ed3de57cfa36.jpg)

There are two choices in the display menu program; Cashier and Booth.
1. Cashier
In this function there are are four functions
- newcard(); //to create a member card
- topup(); //to add the amount of cash inside the card
- refund(); //to refund the amount of cash stored in the card and to unregister/delete the card
- listcards(); //to show the list of cards which have been registered and stored in the txt file.

![Screenshot (82)](https://serving.photos.photobox.com/04163913bb315e8a428cd5bb9bcb0076463cb4c46e19b5307992e409d0a5cda353cd3fe4.jpg)

2. Booth
In the booth function we can order the choices of food that is offered in the restaurant. There are ten different food choices. The cool thing about this program is that if we want to order the selected item for an amount of 7, we can spam the number of the selected item in the program and it will keep on adding until we want the desired amount. After selecting the food, we will be directed to the payment function. There are three choices in the payment function; 
- Yes // to continue to the payment, entering the card ID number
- Back and add more // return to the food menu and add more food
- Back and reduce // return to the food menu and reduce the amount of food selected
![Screenshot (83)](https://serving.photos.photobox.com/323418027c6a995a664c2fe80c5d1440a9356a367397e3b05fbd49456e8098d756b117c8.jpg)

In the payment section we are required to enter the card id number the amount of cash inside the card will be reduced by the amount of cash which needs to be paid. If the amount of cash is not enough to pay the required amount of money, the program will ask the user to the cashier menu and top up the card. 

For the attractiveness of our program, we use API win32 for the graphical user interface (GUI). At the moment, we have successfully created the window for the program, but still unable to input the function of our main program, which is the restaurant data sorting. 
To make such a GUI, we first start by creating the window. In codeblocks, there is the library called windows.h to do so. Then, we follow the instruction from our reference on youtube (https://www.youtube.com/watch?v=8GCvZs55mEM&list=PLWzp0Bbyy_3i750dsUj7yq4JrPOIUR_NK), learn step by step how to make the submenu, buttons, and description in the window, then we modify the code to make the window to look just like the one that we make in the console  application.

![Screenshot (85)](https://imgur.com/oyNxfeN)

Thank You 

Anak Agung Krisna Ananda Kusuma (1806228146)
Rayhan Hanif Oetomo (1806187770)
