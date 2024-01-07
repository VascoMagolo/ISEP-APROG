/*
 * This is a program made for the final group project of the class APROG (Algorithms and Programming) of the 1st year of the degree in Electrical and Computer Engineering at ISEP.
 * This represents a ticket system for a company that repairs, returns and delivers electronic equipment.
 *
 */

// Libraries
#include <stdio.h>
#include <string.h>
#include <time.h>

// Function to pause the console until 'C' is pressed
int enterC() {
    printf("\nPress 'C' to Continue...\n");
    while (getchar() != 'C');
    return 0;
}

// Time Functions Begin

// Function to get the formatted date and time string
void getFormattedDateTime(char *timeString, size_t size) {
    time_t currentTime;
    struct tm *localTime; //Struct from the time.h library

    // Get the current time
    time(&currentTime);
    localTime = localtime(&currentTime);

    // Format date and time and store in the buffer
    strftime(timeString, size, "%d/%m/%Y %H:%M", localTime);
}

// Function to check if the current time is within the allowed working hours
int isWithinTimeRange() {
    time_t currentTime;
    struct tm *localTime; //Struct from the time.h library

    // Getting the current time
    time(&currentTime);
    localTime = localtime(&currentTime);

    // Extracting hours and minutes
    int hours = localTime->tm_hour;
    int minutes = localTime->tm_min;

    // Condtion to check if the current time is between 8:00 am and 9:59 pm
    if ((hours > 8 || (hours == 8 && minutes >= 0)) && (hours < 21 || (hours == 21 & minutes <= 59))) {
        return 1;  // In the time range
    }
    else {
        return 0;  // Not in the time range
    }
}

// Function to parse a date string into a struct tm
// This as the purpose of passing a string int a format that can be used to compare dates
int parseDate(const char *dateString, struct tm *timeStruct) {
    //using sscanf to pass the dateString(string) to the timeStruct(int)
    if (sscanf(dateString, "%d/%d/%d %d:%d",
               &timeStruct->tm_mday, &timeStruct->tm_mon, &timeStruct->tm_year,
               &timeStruct->tm_hour, &timeStruct->tm_min) != 5) {
        return 0;  // Parsing failed
    }

    // Adjust struct members for tm_mon (0-based) and tm_year (1900-based)
    timeStruct->tm_mon -= 1;
    timeStruct->tm_year -= 1900;

    return 1;  // Parsing successful
}

// Time Functions End

// Structs Begin
struct TicketR {
    int ticketID;
    int ticketNumberA;
    char dateGenerated[20];
    char dateCalled[20];
    int counter;
    char equipment[50];
    char mainFault[50];
    char observation[50];
};
struct TicketD {
    int ticketID;
    int ticketNumberA;
    char dateGenerated[20];
    char dateCalled[20];
    int counter;
    char equipment[50];
    char condition;
    int price;
};
// Structs End

// Declaring array of structures
struct TicketR ticketsR[100];
struct TicketD ticketsD[100];


// Structs Functions Begin

// Function to create a TicketR structure
struct TicketR fR(char *timestamp, int idRc, int atendnum) {
    struct TicketR ticket;
    ticket.ticketID = idRc;
    ticket.ticketNumberA = atendnum;
    strcpy(ticket.dateGenerated, timestamp);
    return ticket;
}
// Function to create a TicketD structure
struct TicketD fD(char *timestamp, int idDc, int atendnum) {
    struct TicketD ticket;
    ticket.ticketID = idDc;
    ticket.ticketNumberA = atendnum;
    strcpy(ticket.dateGenerated, timestamp);
    return ticket;
}
// Structs Functions End

// Functions to add the ticket to the array - BEGIN
// Function to add TicketR to the array
void addtoarrR(char *timeString, int idRc, int counter, int atendnum) {
    ticketsR[counter] = fR(timeString, idRc, atendnum);
    printf("Repair Ticket Number:%d created and added to the array.\n", ticketsR[counter].ticketID);
}
// Function to add TicketD to the array
void addtoarrD(char *timeString, int idDc, int counter, int atendnum) {
    ticketsD[counter] = fD(timeString, idDc, atendnum);
    printf("Delivery/Return Ticket Number:%d created and added to the array.\n", ticketsD[counter].ticketID);
}
// Functions to add the ticket to the array - END

// Function for employee to attend a TicketD
void attendD(struct TicketD *ticket, int counter, char *timeString) {
    ticket->counter = counter;

    printf("What is the equipment? ");
    scanf("%s", ticket->equipment);
    getchar();

    printf("What is the condition of the equipment? (A-New, B-Hardly Used, C-Used, D-Awful state)\n");
    scanf(" %c", &ticket->condition);
    getchar();

    printf("What is the price to pay? ");
    int price;
    scanf("%d", &price);
    if (price < 0) {// Validates if the input value is bigger than zero
        printf("Invalid price. Please enter a positive value.\n");
        return;
    }
    ticket->price = price;
    getchar();

    getFormattedDateTime(timeString, sizeof(ticket->dateCalled));
    strcpy(ticket->dateCalled, timeString);

    printf("Ticket D%d attended and updated.\n", ticket->ticketNumberA);
}
// Function for employee to attend a TicketR
void attendR(struct TicketR *ticket, int counter, char *timeString) {
    ticket->counter = counter;

    getFormattedDateTime(timeString, sizeof(ticket->dateCalled));
    strcpy(ticket->dateCalled, timeString);

    printf("What is the equipment? ");
    scanf("%s", ticket->equipment);
    getchar();

    printf("What is the main fault? ");
    scanf("%s", ticket->mainFault);
    getchar();

    printf("What is the observation? ");
    scanf("%s", ticket->observation);
    getchar();

    printf("Ticket R%d attended and updated.\n", ticket->ticketNumberA);
}

// Function to display all tickets
void displayAllTickets(int idRc, int idDc) {
    printf("\nAll Tickets:\n");

    for (int i = 0; i < idRc; i++) {
        printf("Ticket R%d\n", ticketsR[i].ticketNumberA);
        printf("Generated Date: %s\n", ticketsR[i].dateGenerated);
        printf("Called Date: %s\n", ticketsR[i].dateCalled);
        printf("Counter: %d\n", ticketsR[i].counter);
        printf("Equipment: %s\n", ticketsR[i].equipment);
        printf("Main Fault: %s\n", ticketsR[i].mainFault);
        printf("Observation: %s\n", ticketsR[i].observation);
        printf("------------------------\n");
    }

    for (int i = 0; i < idDc; i++) {
        printf("Ticket E%d\n", ticketsD[i].ticketNumberA);
        printf("Generated Date: %s\n", ticketsD[i].dateGenerated);
        printf("Called Date: %s\n", ticketsD[i].dateCalled);
        printf("Counter: %d\n", ticketsD[i].counter);
        printf("Equipment: %s\n", ticketsD[i].equipment);
        printf("Condition: %c\n", ticketsD[i].condition);
        printf("Price: %d\n", ticketsD[i].price);
        printf("------------------------\n");
    }
}
// Function to display the quantity of tickets attended by date
void displayAttendQuantityTicketsByDate(int idRc, int idDc) {
    // Variables to store the date for searching
    char date[20];
    printf("Enter the date for which you want to display average wait time (dd/mm/yyyy): ");
    scanf("%s", date);

    // Validate the date format (you may want to enhance this validation)
    if (strlen(date) != 10 || date[2] != '/' || date[5] != '/') {
        printf("Invalid date format. Please use dd/mm/yyyy.\n");
        return;
    }

    int count = 0;
    for (int i = 0; i < idRc; i++) {
        if (strstr(ticketsR[i].dateCalled, date) != NULL) {// strstr() is used to check if the date entered is the same as the date called, it searches the date entered on the date called
            count++;
        }
    }

    for (int i = 0; i < idDc; i++) {
        if (strstr(ticketsD[i].dateCalled, date) != NULL) {// strstr() is used to check if the date entered is the same as the date called, it searches the date entered on the date called
            count++;
        }
    }

    printf("\nThe quantity of tickets attended on %s is %d.\n", date, count);
}
void displayAverageWaitTimeByDate(int idRc, int idDc) {
    // Variables to store the date for searching
    char date[20];
    printf("Enter the date for which you want to display average wait time (dd/mm/yyyy): ");
    scanf("%s", date);

    // Validate the date format (you may want to enhance this validation)
    if (strlen(date) != 10 || date[2] != '/' || date[5] != '/') {
        printf("Invalid date format. Please use dd/mm/yyyy.\n");
        return;
    }

    // Create an array to store time differences
    double timeDifferences[200];
    int timeDifferencesCount = 0;

    // Extract attended dates and calculate time differences for TicketR
    for (int i = 0; i < idRc; i++) {
        if (strstr(ticketsR[i].dateCalled, date) != NULL) {// strstr() is used to check if the date entered is the same as the date called, it searches the date entered on the date called
            struct tm attendedTime;
            struct tm generatedTime;

            if (parseDate(ticketsR[i].dateCalled, &attendedTime) &&
                parseDate(ticketsR[i].dateGenerated, &generatedTime)) {
                double difference = difftime(mktime(&attendedTime), mktime(&generatedTime));
                timeDifferences[timeDifferencesCount++] = difference;
            }
        }
    }

    // Extract attended dates and calculate time differences for TicketD
    for (int i = 0; i < idDc; i++) {
        if (strstr(ticketsD[i].dateCalled, date) != NULL) {// strstr() is used to check if the date entered is the same as the date called, it searches the date entered on the date called
            struct tm attendedTime;
            struct tm generatedTime;

            if (parseDate(ticketsD[i].dateCalled, &attendedTime) &&
                parseDate(ticketsD[i].dateGenerated, &generatedTime)) {
                double difference = difftime(mktime(&attendedTime), mktime(&generatedTime));
                timeDifferences[timeDifferencesCount++] = difference;
            }
        }
    }

    // Calculate the average time difference
    if (timeDifferencesCount > 0) {
        double totalDifference = 0.0;
        for (int i = 0; i < timeDifferencesCount; i++) {
            totalDifference += timeDifferences[i];
        }

        double average = totalDifference / timeDifferencesCount;
        // Convert the average from seconds to hours, minutes, and seconds
        int hours = (int)(average / 3600);
        int minutes = (int)((average - hours * 3600) / 60);
        int seconds = (int)(average - hours * 3600 - minutes * 60);

        printf("\nThe average wait time between appointments on %s is %02d hour/s, %02d minute/s, %02d second/s\n", date, hours, minutes, seconds);
    } else {
        printf("\nNo tickets attended on %s.\n", date);
    }
}
void countCounterbyDate(int idRc, int idDc) {
    int C1 = 0, C2 = 0, C3 = 0, C4 = 0;

    // Variables to store the date for searching
    char date[20];
    printf("Enter the date for which you want to count tickets (dd/mm/yyyy): ");
    scanf("%s", date);

    // Validate the date format (you may want to enhance this validation)
    if (strlen(date) != 10 || date[2] != '/' || date[5] != '/') {
        printf("Invalid date format. Please use dd/mm/yyyy.\n");
        return;
    }

    // Count tickets for each counter based on the entered date
    for (int i = 0; i < idRc; i++) {
        if (strstr(ticketsR[i].dateCalled, date) != NULL) {// strstr() is used to check if the date entered is the same as the date called, it searches the date entered on the date called
            if (ticketsR[i].counter == 1) {
                C1++;
            } else if (ticketsR[i].counter == 2) {
                C2++;
            } else if (ticketsR[i].counter == 3) {
                C3++;
            } else if (ticketsR[i].counter == 4) {
                C4++;
            }
        }
    }

    for (int i = 0; i < idDc; i++) {
        if (strstr(ticketsD[i].dateCalled, date) != NULL) {// strstr() is used to check if the date entered is the same as the date called, it searches the date entered on the date called
            if (ticketsD[i].counter == 1) {
                C1++;
            } else if (ticketsD[i].counter == 2) {
                C2++;
            } else if (ticketsD[i].counter == 3) {
                C3++;
            } else if (ticketsD[i].counter == 4) {
                C4++;
            }
        }
    }

    // Determine the most productive counter
    printf("The most productive counter is: ");
    if (C1 > C2 && C1 > C3 && C1 > C4) {
        printf("Counter 1\n");
    } else if (C2 > C1 && C2 > C3 && C2 > C4) {
        printf("Counter 2\n");
    } else if (C3 > C1 && C3 > C2 && C3 > C4) {
        printf("Counter 3\n");
    } else if (C4 > C1 && C4 > C2 && C4 > C3) {
        printf("Counter 4\n");
    } else {
        printf("There is no most productive counter\n");
    }

    // Determine the least productive counter
    printf("The least productive counter is: ");
    if (C1 < C2 && C1 < C3 && C1 < C4) {
        printf("Counter 1\n");
    } else if (C2 < C1 && C2 < C3 && C2 < C4) {
        printf("Counter 2\n");
    } else if (C3 < C1 && C3 < C2 && C3 < C4) {
        printf("Counter 3\n");
    } else if (C4 < C1 && C4 < C2 && C4 < C3) {
        printf("Counter 4\n");
    } else {
        printf("There is no least productive counter\n");
    }
}
void displayrevenuebydate(int idDc) {
    char date[20];
    printf("Enter the date for which you want to calculate revenue (dd/mm/yyyy): ");
    scanf("%s", date);

    // Validate the date format, basically checking if the string has 10 characters and if the 3rd and 6th characters are '/'
    if (strlen(date) != 10 || date[2] != '/' || date[5] != '/') {
        printf("Invalid date format. Please use dd/mm/yyyy.\n");
        return;
    }


    double totalRevenue = 0.0;
    // Calculate the revenue for each ticketD delivered on the entered date
    for (int i = 0; i < idDc; i++) {
        if (strstr(ticketsD[i].dateCalled, date) != NULL) {// strstr() is used to check if the date entered is the same as the date called, it searches the date entered on the date called
            totalRevenue += ticketsD[i].price;
        }
    }

    // Display the calculated revenue
    printf("Revenue for products delivered on %s: $%.2f\n", date, totalRevenue);
}
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

        switch (userInput) {
            case 1:
                printf("\nCustomer Menu:\n");
                while (1) {
                    int choice;
                    printf("\nMenu:\n");
                    printf("1. Create a ticket\n");
                    printf("0. Leave Menu\n");
                    scanf("%d", &choice);

                    if (choice == 0) {
                        break;
                    }

                    switch (choice) {
                        case 1:

                            // Check if the current time is within the allowed range
                            if (isWithinTimeRange()) {
                                printf("\nCreate a ticket\n");
                                char timeString[20];
                                getFormattedDateTime(timeString, sizeof(timeString));
                                printf("Which ticket do you want? (0-R, 1-E)\n");
                                scanf("%d", &t);

                                if (t == 0) {
                                    addtoarrR(timeString, idRc, idRc, atendnum);
                                    atendnum++;
                                    idRc++;
                                } else if (t == 1) {
                                    addtoarrD(timeString, idDc, idDc, atendnum);
                                    atendnum++;
                                    idDc++;
                                } else {
                                    printf("Invalid Option\n");
                                }
                            }
                            else {
                                printf("\nTickets can only be generated between 8 am and 10 pm.\n");
                            }
                            enterC();
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
                while (1) {
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

                    switch (choice) {
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
                                        attendD(&ticketsD[i], counter, timeString);
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
                                            attendR(&ticketsR[i], counter, timeString);
                                            break;
                                        }
                                    }
                                } else if (type == 1) {
                                    for (int i = 0; i < idDc; i++) {
                                        if (ticketsD[i].counter == 0){
                                            attendD(&ticketsD[i], counter, timeString);
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
                            displayAllTickets(idRc, idDc);
                            break;
                        case 3:
                            printf("\nDisplay quantity of tickets attended by date\n");
                            displayAttendQuantityTicketsByDate(idRc, idDc);
                            break;
                        case 4:
                            printf("\nDisplay average wait time between appointments by date\n");
                            displayAverageWaitTimeByDate(idRc, idDc);
                            break;
                        case 5:
                            printf("\nDisplay the less and most productive counters by date\n");
                            countCounterbyDate(idRc, idDc);
                            break;
                        case 6:
                            printf("\nDisplay revenue of delivered products by date\n");
                            displayrevenuebydate(idDc);
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
