#include <stdio.h>
#include <time.h>

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
    char dateGenerated[20];
    char dateCalled[20];
    int counter;
    char equipment;
    char mainFault;
    char observation;
};
struct TicketE {
    int ticketID;
    char dateGenerated[20];
    char dateCalled[20];
    int counter;
    char equipment;
    char condition;
    int price;
};
// Structs End

// Structs Functions Begin
struct TicketR fR(char *timestamp, int idRc) {
    struct TicketR ticket;
    ticket.ticketID = idRc;
    strcpy(ticket.dateGenerated, timestamp);
    printf("%s", ticket.dateGenerated);
    return ticket;
}
struct TicketE fE(char *timestamp, int idEc) {
    struct TicketE ticket;
    ticket.ticketID = idEc;
    strcpy(ticket.dateGenerated, timestamp);
    printf("%d", ticket.ticketID);
    return ticket;
}
// Structs Functions End

// Declaring array of structures
struct TicketR ticketsR[100];
struct TicketE ticketsE[100];

// Functions to add the ticket to the array-BEGIN
void addtoarrR(char *timeString, int idRc,int counter) {
    ticketsR[counter] = fR(timeString, idRc);
}
void addtoarrE(char *timeString, int idEc,int counter) {
    ticketsE[counter] = fE(timeString, idEc);
}

//Main function that runs the programm
int main() {
    char userInput; // Variable to store the user input
    while (1) {
        // Prompt the user to enter a character
        printf("Enter a character (type 'P' to exit): ");

        // Read the user input
        scanf(" %c", &userInput);

        // Check if the user entered 'P'
        if (userInput == 'P' || userInput == 'p') {
            printf("Exiting the program.\n");
            break; // Exit the loop
        }
        int choice; // Variable to store the user choice
        // Prompt the user to enter a number
        printf("Menu:\n");
        printf("1. Create a ticket\n");
        printf("2. Search for a ticket\n");
        printf("3. Edit a ticket\n");
        printf("4. Delete a ticket\n");
        printf("5. Display all tickets\n");
        scanf("%d", &choice); // Read the user choice
        switch (choice) {
            case 1:
                printf("Create a ticket\n");


                // Buffer to store the formatted date and time
                char timeString[20]; // 20 bytes should be enough
                // Get the formatted date and time string
                getFormattedDateTime(timeString, sizeof(timeString) / sizeof(timeString[0]));//passing the string and the array size

                // Print the formatted date and time delete this line later
                printf("Formatted date and time: %s\n", timeString);

                // Declaring variables for the choice of the ticket and the ticket ID
                int t, idRc = 0, idEc = 0;

                // Asking the user which ticket he wants to create and storing the choice in the variable t
                printf("Which ticket do you want?(0-R,1-E)\n");
                scanf("%d", &t);

                //Just a break to make the console look better
                enterC();

                //Knowing which ticket the user choose and after creating it, adding it to the array
                if (t == 0) {
                    addtoarrR(timeString, idRc, idRc);
                    idRc++;
                } else if (t == 1) {
                    addtoarrE(timeString, idEc, idEc);
                    idEc++;
                } else {
                    printf("Invalid Option\n");
                }

                //printing the first element of the array for testing
                printf("%d", ticketsR[0].ticketID);
                printf("%s", ticketsR[0].dateGenerated);
                printf("%d", ticketsE[0].ticketID);
                enterC(); //Just a break to make the console look better
                break;
            case 2:
                printf("Search for a ticket\n");
                break;
            case 3:
                printf("Edit a ticket\n");
                break;
            case 4:
                printf("Delete a ticket\n");
                break;
            case 5:
                printf("Display all tickets\n");
                break;
            default:
                printf("Invalid option\n");
        }
    }
    return 0;
}   // Path: main.c
