/*
 * This is a program made for the final group project of the class APROG (Algorithms and Programming) of the 1st year of the degree in Electrical and Computer Engineering at ISEP.
 * This represents a ticket system for a company that repairs, returns and delivers electronic equipment.
 *
 */

// Libraries
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "functions.h"

// Main function that runs the program
int main() {
    int userInput;
    int t, idRc = 0, idDc = 0, atendnum = 0;
    int leaveProgram = 0;

    while (!leaveProgram) {// Main loop to keep the program running until the user chooses to leave
        printf("\nMenu:\n");
        printf("1. Customer\n");
        printf("2. Employee\n");
        printf("0. Leave program\n");

        scanf("%d", &userInput);

        switch (userInput) {//Switch case for the user to choose between the customer menu, employee menu or leave the program
            case 1:
                printf("\nCustomer Menu:\n");
                while (1) { // Loop to keep the customer menu running until the user chooses to leave
                    int choice;
                    printf("\nMenu:\n");
                    printf("1. Create a ticket\n");
                    printf("0. Leave Menu\n");
                    scanf("%d", &choice);

                    if (choice == 0) {
                        break;
                    }

                    switch (choice) { //Switch case for the user to choose between creating a ticket or leaving the menu
                        case 1:

                            // Check if the current time is within the allowed range
                            if (IsWithinTimeRange()) {
                                printf("\nCreate a ticket\n");
                                char timeString[20];
                                GetFormattedDateTime(timeString, sizeof(timeString));
                                printf("Which ticket do you want? (0-Repair, 1-Delivery)\n");
                                scanf("%d", &t);

                                if (t == 0) {
                                    AddToArrR(timeString, idRc, idRc, atendnum);
                                    atendnum++;
                                    idRc++;
                                } else if (t == 1) {
                                    AddToArrD(timeString, idDc, idDc, atendnum);
                                    atendnum++;
                                    idDc++;
                                } else {
                                    printf("Invalid Option\n");
                                }
                            }
                            else {
                                printf("\nTickets can only be generated between 8:00 am and 9:59 pm.\n");
                            }
                            EnterC();
                            break;
                        case 0:
                            leaveProgram = 1;
                            break;
                        default:
                            printf("Invalid option\n");
                            break;
                    }
                }
                break;

            case 2:
                printf("\nEmployee Menu:\n");
                char timeString[20];
                while (1) { // Loop to keep the employee menu running until the user chooses to leave
                    int choice;
                    printf("\nMenu:\n");
                    printf("1. Attend a ticket\n");
                    printf("2. Display all tickets\n");
                    printf("3. Display quantity of attended tickets by date\n");
                    printf("4. Display average wait time between appointments by date\n");
                    printf("5. Display the less and most productive counters by date\n");
                    printf("6. Display revenue of delivered products by date\n");
                    printf("0. Leave Menu\n");
                    scanf("%d", &choice);

                    if (choice == 0) {
                        break;
                    }

                    switch (choice) { //Switch case for the user to choose between attending a ticket, displaying all tickets, displaying quantity of attended tickets by date, displaying average wait time between appointments by date, displaying the less and most productive counters by date, displaying revenue of delivered products by date or leaving the menu
                        case 1:
                            printf("\nAttend a ticket\n");
                            int counter;
                            printf("Which counter are you in? (1-4)\n");
                            scanf("%d", &counter);
                            if (counter < 1 || counter > 4) {
                                printf("Invalid counter. Please choose a counter between 1 and 4.\n");
                                break;
                            }

                            if (counter == 4) {
                                for (int i = 0; i < idDc; i++) {
                                    if (ticketsD[i].counter == 0) {
                                        AttendD(&ticketsD[i], counter, timeString);
                                        break;
                                    }
                                }
                            } else {
                                printf("Which type of ticket do you want to attend? (0-Repair, 1-Delivery)\n");
                                int type;
                                scanf("%d", &type);

                                if (type == 0) {
                                    for (int i = 0; i < idRc; i++) {
                                        if (ticketsR[i].counter == 0) {
                                            AttendR(&ticketsR[i], counter, timeString);
                                            break;
                                        }
                                    }
                                } else if (type == 1) {
                                    for (int i = 0; i < idDc; i++) {
                                        if (ticketsD[i].counter == 0){
                                            AttendD(&ticketsD[i], counter, timeString);
                                            break;
                                        }
                                    }
                                } else {
                                    printf("Invalid Option\n");
                                }
                            }
                            break;
                        case 2:
                            printf("\nDisplay all tickets\n");
                            DisplayAllTickets(idRc, idDc);
                            break;
                        case 3:
                            printf("\nDisplay quantity of tickets attended by date\n");
                            DisplayAttendQuantityTicketsByDate(idRc, idDc);
                            break;
                        case 4:
                            printf("\nDisplay average wait time between appointments by date\n");
                            DisplayAverageWaitTimeByDate(idRc, idDc);
                            break;
                        case 5:
                            printf("\nDisplay the less and most productive counters by date\n");
                            CountCounterByDate(idRc, idDc);
                            break;
                        case 6:
                            printf("\nDisplay revenue of delivered products by date\n");
                            DisplayRevenueByDate(idDc);
                            break;
                        case 0:
                            // Set the variable to leave the outer loop
                            leaveProgram = 1;
                            break;
                        default:
                            printf("Invalid option\n");
                            break;
                    }
                }
                break;

            case 0:
                printf("Leaving program\n");
                return 0;

            default:
                printf("Invalid option\n");
                break;
        }
    }

    return 0;
}
