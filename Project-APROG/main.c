#include <stdio.h>
#include <time.h>

int enterC() {
    printf("Press Enter to Continue\n");
    while( getchar() != '\n' );

    return 0;
}
struct TicketR{
    int ticketID;
    char dateGenerated;
    char dateCalled;
    int counter;
    char equipment;
    char mainFault;
    char observation;
};
struct TicketE{
    int ticketID;
    char dateGenerated;
    char dateCalled;
    int counter;
    char equipment;
    char condition;
    int price;
};
struct TicketR fR(char timestamp, int idRc){
    struct TicketR ticket;
    ticket.ticketID = idRc;
    ticket.dateGenerated = timestamp;
    printf("%time_t",ticket.dateGenerated);
    return ticket;
}
struct TicketE fE(char timestamp, int idEc){
    struct TicketE ticket;
    ticket.ticketID = idEc;
    ticket.dateGenerated = timestamp;
    printf("%d",ticket.ticketID);
    return ticket;
}
void getFormattedDateTime(char *timeString, size_t size) {
    time_t currentTime;
    struct tm *localTime;

    // Get the current time
    time(&currentTime);
    localTime = localtime(&currentTime);

    // Format date and time and store in the buffer
    strftime(timeString, size, "%d/%m/%Y %H:%M", localTime);
}
int main() {
    // Buffer to store the formatted date and time
    char timeString[20];

    // Get the formatted date and time string
    getFormattedDateTime(timeString, sizeof(timeString));

    // Print the formatted date and time
    printf("Formatted date and time: %s\n", timeString);

    int y,idRc=0,idEc=0;
    struct TicketR tickets[100];
    printf("Hello, World!\n");
    scanf("d",&y);
    if(y==0){
        fR(timeString,idRc);
        idRc++;
    }
    else if (y==1){
        fE(timeString,idEc);
        idEc++;
    }

    printf("Hello, World!\n");
    enterC();
    return 0;
}
