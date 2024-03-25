#ifndef FUNCTIONS_H
#define FUNCTIONS_H

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
// Array of structures
extern struct TicketR ticketsR[100];
extern struct TicketD ticketsD[100];

// Declaring headers of functions
int EnterC();
void GetFormattedDateTime(char *timeString, size_t size);
int IsWithinTimeRange();
int ParseDate(const char *dateString, struct tm *timeStruct);
struct TicketR CreateTicketR(char *timestamp, int idRc, int atendnum);
struct TicketD CreateTicketD(char *timestamp, int idDc, int atendnum);
void AddToArrR(char *timeString, int idRc, int counter, int atendnum);
void AddToArrD(char *timeString, int idDc, int counter, int atendnum);
void AttendD(struct TicketD *ticket, int counter, char *timeString);
void AttendR(struct TicketR *ticket, int counter, char *timeString);
void DisplayAllTickets(int idRc, int idDc);
void DisplayAttendQuantityTicketsByDate(int idRc, int idDc);
void DisplayAverageWaitTimeByDate(int idRc, int idDc);
void CountCounterByDate(int idRc, int idDc);
void DisplayRevenueByDate(int idDc);

#endif