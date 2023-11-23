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

int main() {
    // Buffer to store the formatted date and time
    char timeString[20]; // Specify the size of the array
    // Get the formatted date and time string
    getFormattedDateTime(timeString, sizeof(timeString) / sizeof(timeString[0]));//passing the string and the array size
    // Print the formatted date and time
    printf("Formatted date and time: %s\n", timeString);

    // Declaring variables for the choice of the ticket and the ticket ID
    int t, idRc = 0, idEc = 0;

    // Declaring array of structures
    struct TicketR tickets[100];
    printf("Which ticket do you want?(0-R,1-E)\n");
    scanf("%d", &t);
    printf("");
    enterC();
    if (t == 0) {
        fR(timeString, idRc);
        idRc++;
    } else if (t == 1) {
        fE(timeString, idEc);
        idEc++;
    } else {
        printf("Invalid Option\n");
    }

    enterC();
    return 0;
}
