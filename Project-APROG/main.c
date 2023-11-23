#include <stdio.h>
#include <time.h>

int enterC() {
    printf("Press Enter to Continue\n");
    while( getchar() != '\n' );

    return 0;
}
struct TicketR{
    int ticketID;
    time_t dateGeneratad;
    time_t dateCalled;
    int counter;
    char equipment;
    char mainFault;
    char observation;
};
struct TicketE{
    int ticketID;
    time_t dateGeneratad;
    time_t dateCalled;
    int counter;
    char equipment;
    char condition;
    int price;
};
struct TicketR fR(time_t timestamp, int idRc){
    struct TicketR ticket;
    ticket.ticketID = idRc;
    ticket.dateGeneratad = time(&timestamp);
    printf("%d",ticket.ticketID);
    return ticket;
}
struct TicketE fE(time_t timestamp, int idEc){
    struct TicketE ticket;
    ticket.ticketID = idEc;
    ticket.dateGeneratad = time(&timestamp);
    printf("%d",ticket.ticketID);
    return ticket;
}

int main() {
    time_t t;// not a primitive datatype
    time(&t);
    int y,idRc=0,idEc=0;
    struct TicketR tickets[100];
    printf("Hello, World!\n");
    scanf("d",&y);
    if(y==0){
        fR(t,idRc);
        idRc++;
    }
    else if (y==1){
        fE(t,idEc);
        idEc++;
    }

    printf("Hello, World!\n");
    enterC();
    return 0;
}
