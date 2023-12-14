#include <stdio.h>
#include <time.h>
#include <string.h>
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

//Function to pause the console until 'C' is pressed
int enterC() {
    printf("Press 'C' to Continue\n");
    while (getchar() != 'C');
    return 0;
}

// Structs Begin
struct TicketR {
    int ticketID;
    int ticektnumberA;
    char dateGenerated[20];
    char dateCalled[20];
    int counter;
    char equipment;
    char mainFault;
    char observation;
};
struct TicketE {
    int ticketID;
    int ticektnumberA;
    char dateGenerated[20];
    char dateCalled[20];
    int counter;
    char *equipment;
    char condition;
    int price;
};
// Structs End

// Structs Functions Begin
struct TicketR fR(char *timestamp, int idRc, int atendnum) {
    struct TicketR ticket;
    ticket.ticketID = idRc;
    ticket.ticektnumberA = atendnum;
    strcpy(ticket.dateGenerated, timestamp);
    return ticket;
}
struct TicketE fE(char *timestamp, int idEc, int atendnum) {
    struct TicketE ticket;
    ticket.ticketID = idEc;
    ticket.ticektnumberA = atendnum;
    strcpy(ticket.dateGenerated, timestamp);
    return ticket;
}
// Structs Functions End

// Declaring array of structures
struct TicketR ticketsR[100];
struct TicketE ticketsE[100];

// Functions to add the ticket to the array-BEGIN
void addtoarrR(char *timeString, int idRc,int counter, int atendnum) {
    ticketsR[counter] = fR(timeString, idRc, atendnum);
}
void addtoarrE(char *timeString, int idEc,int counter, int atendnum) {
    ticketsE[counter] = fE(timeString, idEc, atendnum);
}
void attendE(struct TicketE *ticket, int counter, char *timeString) {
    ticket->counter = counter;

    printf("What is the equipment?");
    fgets(ticket->equipment, 50, stdin);
    printf("%s", ticket->equipment);

    printf("What is the condition of the equipment?(A-New, B-Hardly Used, C-Used, D-Awful state )\n");
    char condition;
    scanf(" %c", &condition);
    ticket->condition = condition;

    printf("What is the price of the equipment?\n");
    int price;
    scanf("%d", &price);
    ticket->price = price;

    getFormattedDateTime(timeString, sizeof(timeString) / sizeof(timeString[0]));
    strcpy(ticket->dateCalled, timeString);

}
void attendR(struct TicketR *ticket, int counter, char *timeString){
    ticket->counter = counter;

    getFormattedDateTime(timeString, sizeof(timeString) / sizeof(timeString[0]));
    strcpy(ticket->dateCalled, timeString);
}
//Main function that runs the program
int main() {
    int userInput; // Variable to store the user input
    int t, idRc = 0, idEc = 0, atendnum = 0; // Declaring variables for the choice of the ticket and the ticket ID

    int leaveProgram = 0; // Variable to control the program flow

    while (!leaveProgram) {
        // Prompt the user to enter a character to choose the type of user
        printf("1. Customer\n");
        printf("2. Employee\n");
        printf("0. Leave program\n");

        // Read the user input
        scanf(" %d", &userInput);

        switch (userInput) {
            case 1:
                printf("Customer Menu:\n");
                while (1) {
                    int choice; // Variable to store the user choice

                    // Prompt the user to enter a number
                    printf("Menu:\n");
                    printf("1. Create a ticket\n");
                    printf("0. Leave Menu\n");
                    scanf("%d", &choice); // Read the user choice

                    if (choice == 0) {
                        break;
                    }

                    switch (choice) {
                        case 1:
                            printf("Create a ticket\n");

                            // Buffer to store the formatted date and time
                            char timeString[20]; // 20 bytes should be enough
                            // Get the formatted date and time string
                            getFormattedDateTime(timeString, sizeof(timeString) / sizeof(timeString[0]));//passing the string and the array size

                            // Asking the user which ticket he wants to create and storing the choice in the variable t
                            printf("Which ticket do you want?(0-R,1-E)\n");
                            scanf("%d", &t);

                            // Knowing which ticket the user choose and after creating it, adding it to the array
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

                            enterC(); // Just a break to make the console look better
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

            case 2:
                printf("Employee Menu:\n");
                char timeString[20]; // 20 bytes should be enough
                while (1) {
                    int choice; // Variable to store the user choice
                    printf("1. Attend a ticket\n");
                    printf("2. Display all tickets by date\n");
                    printf("3. Edit a ticket\n");
                    printf("4. Delete a ticket\n");
                    printf("5. Display all tickets\n");
                    printf("0. Leave Menu\n");
                    scanf("%d", &choice); // Read the user choice

                    if (choice == 0) {
                        break;
                    }

                    switch (choice) {
                        case 1:
                            printf("Attend a ticket\n");
                            int choice;
                            printf("Which counter are you in?(1-4)\n");
                            scanf("%d", &choice);
                            if (choice==4){
                                for (int i = 0; i < idEc; i++) {
                                    attendE(&ticketsE[i], choice ,timeString);
                                }
                            }
                            else{
                                printf("Which type of ticket do you want to attend?(0-R,1-E)\n");
                                int type;
                                scanf("%d", &type);
                                if (type==0){
                                    for (int i = 0; i < idRc; i++) {
                                        attendR(&ticketsR[i], choice ,timeString);
                                    }
                                }
                                else if (type==1){
                                    for (int i = 0; i < idEc; i++) {
                                        attendE(&ticketsE[i], choice ,timeString);
                                    }
                                }
                                else{
                                    printf("Invalid Option\n");
                                }
                            }
                            break;
                        case 2:
                            printf("Display all tickets by date\n");
                            for (int i = 0; i < idRc; i++) {
                                printf("Ticket Number:%d\n", ticketsR[i].ticektnumberA);
                                printf("Ticket Generated Date%s\n", ticketsR[i].dateGenerated);
                            }
                            for (int i = 0; i < idEc; i++) {
                                printf("Ticket Number:%d\n", ticketsE[i].ticektnumberA);
                                printf("Ticket Generated Date%s\n", ticketsE[i].dateGenerated);
                            }
                            break;
                        case 3:
                            printf("Display quantity of attended tickets by date\n");
                            break;
                        case 4:
                            printf("Display average wait time between appointments by date\n");
                            break;
                        case 5:
                            printf("Display the less and most productives counters by date\n");
                            break;
                        case 6:
                            printf("Display revenue of delivered products by date\n");
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
} // Path: main.c