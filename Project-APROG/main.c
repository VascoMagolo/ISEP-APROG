#include <stdio.h>
#include <string.h>
#include <time.h>

int parseDate(const char *dateString, struct tm *timeStruct) {
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
// Function to get the formatted date and time string
void getFormattedDateTime(char *timeString, size_t size) {
    time_t currentTime;
    struct tm *localTime;

    // Get the current time
    time(&currentTime);
    localTime = localtime(&currentTime);

    // Format date and time and store in the buffer
    strftime(timeString, size, "%d/%m/%Y %H:%M", localTime);
}

// Function to pause the console until 'C' is pressed
int enterC() {
    printf("\nPress 'C' to Continue...\n");
    while (getchar() != 'C');
    return 0;
}

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

struct TicketE {
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

// Structs Functions Begin
// Function to create a TicketR structure
struct TicketR fR(char *timestamp, int idRc, int atendnum) {
    struct TicketR ticket;
    ticket.ticketID = idRc;
    ticket.ticketNumberA = atendnum;
    strcpy(ticket.dateGenerated, timestamp);
    return ticket;
}

// Function to create a TicketE structure
struct TicketE fE(char *timestamp, int idEc, int atendnum) {
    struct TicketE ticket;
    ticket.ticketID = idEc;
    ticket.ticketNumberA = atendnum;
    strcpy(ticket.dateGenerated, timestamp);
    return ticket;
}
// Structs Functions End

// Declaring array of structures
struct TicketR ticketsR[100];
struct TicketE ticketsE[100];

// Functions to add the ticket to the array - BEGIN
// Function to add TicketR to the array
void addtoarrR(char *timeString, int idRc, int counter, int atendnum) {
    ticketsR[counter] = fR(timeString, idRc, atendnum);
    printf("Ticket R%d created and added to the array.\n", ticketsR[counter].ticketNumberA);
}

// Function to add TicketE to the array
void addtoarrE(char *timeString, int idEc, int counter, int atendnum) {
    ticketsE[counter] = fE(timeString, idEc, atendnum);
    printf("Ticket E%d created and added to the array.\n", ticketsE[counter].ticketNumberA);
}
// Functions to add the ticket to the array - END

// Function for employee to attend a TicketE
void attendE(struct TicketE *ticket, int counter, char *timeString) {
    ticket->counter = counter;

    printf("What is the equipment? ");
    scanf("%s", ticket->equipment);

    printf("What is the condition of the equipment? (A-New, B-Hardly Used, C-Used, D-Awful state)\n");
    scanf(" %c", &ticket->condition);

    printf("What is the price to pay? ");
    scanf("%d", &ticket->price);

    getFormattedDateTime(timeString, sizeof(ticket->dateCalled));
    strcpy(ticket->dateCalled, timeString);

    printf("Ticket E%d attended and updated.\n", ticket->ticketNumberA);
}

// Function for employee to attend a TicketR
void attendR(struct TicketR *ticket, int counter, char *timeString) {
    ticket->counter = counter;

    getFormattedDateTime(timeString, sizeof(ticket->dateCalled));
    strcpy(ticket->dateCalled, timeString);

    printf("What is the equipment? ");
    scanf("%s", ticket->equipment);

    printf("What is the main fault? ");
    scanf("%s", ticket->mainFault);

    printf("What is the observation? ");
    scanf("%s", ticket->observation);

    printf("Ticket R%d attended and updated.\n", ticket->ticketNumberA);
}

// Function to display all tickets
void displayAllTickets(int idRc, int idEc) {
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

    for (int i = 0; i < idEc; i++) {
        printf("Ticket E%d\n", ticketsE[i].ticketNumberA);
        printf("Generated Date: %s\n", ticketsE[i].dateGenerated);
        printf("Called Date: %s\n", ticketsE[i].dateCalled);
        printf("Counter: %d\n", ticketsE[i].counter);
        printf("Equipment: %s\n", ticketsE[i].equipment);
        printf("Condition: %c\n", ticketsE[i].condition);
        printf("Price: %d\n", ticketsE[i].price);
        printf("------------------------\n");
    }
}

// Function to display the quantity of tickets attended by date
void displayAttendQuantityTicketsByDate(int idRc, int idEc) {
    //This function is not working properly
    char date[20];
    printf("\nEnter the date to search (dd/mm/yyyy hh:mm): ");
    scanf("%s", date);
    getchar();

    if (strlen(date) != 16) {
        printf("Invalid date model.\n");
        return;
    }

    int count = 0;
    for (int i = 0; i < idRc; i++) {
        if (strcmp(ticketsR[i].dateCalled, date) == 0) {
            count++;
        }
    }

    for (int i = 0; i < idEc; i++) {
        if (strcmp(ticketsE[i].dateCalled, date) == 0) {
            count++;
        }
    }

    printf("\nThe quantity of tickets attended on %s is %d.\n", date, count);
}

    //this function displays the average wait time between appointments
    //it gets the attended date from all the tickets and calculates the median time between attendances
    //it then displays the median time
    void displayAverageWaitTime(int idRc, int idEc) {
        // Create an array to store time differences
        double timeDifferences[200];
        int timeDifferencesCount = 0;

        // Extract attended dates and calculate time differences for TicketR
        for (int i = 0; i < idRc; i++) {
            struct tm attendedTime;
            struct tm generatedTime;

            if (parseDate(ticketsR[i].dateCalled, &attendedTime) &&
                parseDate(ticketsR[i].dateGenerated, &generatedTime)) {
                double difference = difftime(mktime(&attendedTime), mktime(&generatedTime));
                timeDifferences[timeDifferencesCount++] = difference;
            }
        }

            // Extract attended dates and calculate time differences for TicketE
            for (int i = 0; i < idEc; i++) {
                struct tm attendedTime;
                struct tm generatedTime;

                if (parseDate(ticketsE[i].dateCalled, &attendedTime) &&
                    parseDate(ticketsE[i].dateGenerated, &generatedTime)) {
                    double difference = difftime(mktime(&attendedTime), mktime(&generatedTime));
                    timeDifferences[timeDifferencesCount++] = difference;
                }}

                // Calculate the average time difference
                if (timeDifferencesCount > 0) {
                    double totalDifference = 0.0;
                    for (int i = 0; i < timeDifferencesCount; i++) {
                        totalDifference += timeDifferences[i];
                    }

                    double average = totalDifference / timeDifferencesCount;

                    printf("\nThe average wait time between all appointments is %.2f seconds.\n", average);
                } else {
                    printf("\nNo tickets attended.\n");
                }
            }

    void countcounter(int idRc, int idEc){

        int C1 = 0, C2 = 0, C3 = 0, C4 = 0;
        for (int i = 0; i < idRc; i++) {
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

        for (int i = 0; i < idEc; i++) {
            if (ticketsE[i].counter == 1) {
                C1++;
            } else if (ticketsE[i].counter == 2) {
                C2++;
            } else if (ticketsE[i].counter == 3) {
                C3++;
            } else if (ticketsE[i].counter == 4) {
                C4++;
            }
        }
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
        printf("The less productive counter is: ");
        if (C1 < C2 && C1 < C3 && C1 < C4) {
            printf("Counter 1\n");
        } else if (C2 < C1 && C2 < C3 && C2 < C4) {
            printf("Counter 2\n");
        } else if (C3 < C1 && C3 < C2 && C3 < C4) {
            printf("Counter 3\n");
        } else if (C4 < C1 && C4 < C2 && C4 < C3) {
            printf("Counter 4\n");
        } else {
            printf("There is no less productive counter\n");
        }
    }

// Main function that runs the program
int main() {
    int userInput;
    int t, idRc = 0, idEc = 0, atendnum = 0;
    int leaveProgram = 0;

    while (!leaveProgram) {
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
                                addtoarrE(timeString, idEc, idEc, atendnum);
                                atendnum++;
                                idEc++;
                            } else {
                                printf("Invalid Option\n");
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
                                for (int i = 0; i < idEc; i++) {
                                    if (ticketsE[i].counter == 0) {
                                        attendE(&ticketsE[i], counter, timeString);
                                        break;
                                    }
                                }
                            } else {
                                printf("Which type of ticket do you want to attend? (0-R, 1-E)\n");
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
                                    for (int i = 0; i < idEc; i++) {
                                        if (ticketsE[i].counter == 0){
                                            attendE(&ticketsE[i], counter, timeString);
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
                            displayAllTickets(idRc, idEc);
                            break;
                        case 3:
                            printf("\nDisplay quantity of tickets attended by date\n");
                            displayAttendQuantityTicketsByDate(idRc, idEc);
                            break;
                        case 4:
                            printf("\nDisplay average wait time between appointments by date\n");
                            displayAverageWaitTime(idRc, idEc);
                            break;
                        case 5:
                            printf("\nDisplay the less and most productive counters by date\n");
                            countcounter(idRc, idEc);
                            break;
                        case 6:
                            printf("\nDisplay revenue of delivered products by date\n");
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
