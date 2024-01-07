//Libraries
#include <stdio.h>
#include <string.h>
#include <time.h>

// Function to pause the console until 'C' is pressed
int EnterC() {
    printf("\nPress 'C' to Continue...\n");
    while (getchar() != 'C');
    return 0;
}

// Time Functions Begin

// Function to get the formatted date and time string
void GetFormattedDateTime(char *timeString, size_t size) {
    time_t currentTime;
    struct tm *localTime; //Struct from the time.h library

    // Get the current time
    time(&currentTime);
    localTime = localtime(&currentTime);

    // Format date and time and store in the buffer
    strftime(timeString, size, "%d/%m/%Y %H:%M", localTime);
}

// Function to check if the current time is within the allowed working hours
int IsWithinTimeRange() {
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
int ParseDate(const char *dateString, struct tm *timeStruct) {
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
struct TicketR CreateTicketR(char *timestamp, int idRc, int atendnum) {
    struct TicketR ticket;
    ticket.ticketID = idRc;
    ticket.ticketNumberA = atendnum;
    strcpy(ticket.dateGenerated, timestamp);
    return ticket;
}
// Function to create a TicketD structure
struct TicketD CreateTicketD(char *timestamp, int idDc, int atendnum) {
    struct TicketD ticket;
    ticket.ticketID = idDc;
    ticket.ticketNumberA = atendnum;
    strcpy(ticket.dateGenerated, timestamp);
    return ticket;
}
// Structs Functions End

// Functions to add the ticket to the array - BEGIN
// Function to add TicketR to the array
void AddToArrR(char *timeString, int idRc, int counter, int atendnum) {
    ticketsR[counter] = CreateTicketR(timeString, idRc, atendnum);
    printf("Repair Ticket Number:%d created and added to the array.\n", ticketsR[counter].ticketID);
}
// Function to add TicketD to the array
void AddToArrD(char *timeString, int idDc, int counter, int atendnum) {
    ticketsD[counter] = CreateTicketD(timeString, idDc, atendnum);
    printf("Delivery/Return Ticket Number:%d created and added to the array.\n", ticketsD[counter].ticketID);
}
// Functions to add the ticket to the array - END

// Function for employee to attend a TicketD
void AttendD(struct TicketD *ticket, int counter, char *timeString) {
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

    GetFormattedDateTime(timeString, sizeof(ticket->dateCalled));
    strcpy(ticket->dateCalled, timeString);

    printf("Delivery Ticket Number:%d attended and updated.\n", ticket->ticketNumberA);
}
// Function for employee to attend a TicketR
void AttendR(struct TicketR *ticket, int counter, char *timeString) {
    ticket->counter = counter;

    GetFormattedDateTime(timeString, sizeof(ticket->dateCalled));
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

    printf("Repair Ticket Number:%d attended and updated.\n", ticket->ticketNumberA);
}

// Function to display all tickets
void DisplayAllTickets(int idRc, int idDc) {
    printf("\nAll Tickets:\n");

    for (int i = 0; i < idRc; i++) {
        printf("Repair Ticket Number:%d\n", ticketsR[i].ticketID);
        printf("Generated Date: %s\n", ticketsR[i].dateGenerated);
        printf("Called Date: %s\n", ticketsR[i].dateCalled);
        printf("Counter: %d\n", ticketsR[i].counter);
        printf("Equipment: %s\n", ticketsR[i].equipment);
        printf("Main Fault: %s\n", ticketsR[i].mainFault);
        printf("Observation: %s\n", ticketsR[i].observation);
        printf("------------------------\n");
    }

    for (int i = 0; i < idDc; i++) {
        printf("Delivery Ticket Number:%d\n", ticketsD[i].ticketID);
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
void DisplayAttendQuantityTicketsByDate(int idRc, int idDc) {
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
void DisplayAverageWaitTimeByDate(int idRc, int idDc) {
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
    double timeDifference[200];
    int timeDifferencesCount = 0;

    // Extract attended dates and calculate time differences for TicketR
    for (int i = 0; i < idRc; i++) {
        if (strstr(ticketsR[i].dateCalled, date) != NULL) {// strstr() is used to check if the date entered is the same as the date called, it searches the date entered on the date called
            struct tm attendedTime;
            struct tm generatedTime;

            if (ParseDate(ticketsR[i].dateCalled, &attendedTime) &&
                ParseDate(ticketsR[i].dateGenerated, &generatedTime)) {
                double difference = difftime(mktime(&attendedTime), mktime(&generatedTime));
                timeDifference[timeDifferencesCount++] = difference;
            }
        }
    }

    // Extract attended dates and calculate time differences for TicketD
    for (int i = 0; i < idDc; i++) {
        if (strstr(ticketsD[i].dateCalled, date) != NULL) {// strstr() is used to check if the date entered is the same as the date called, it searches the date entered on the date called
            struct tm attendedTime;
            struct tm generatedTime;

            if (ParseDate(ticketsD[i].dateCalled, &attendedTime) &&
                ParseDate(ticketsD[i].dateGenerated, &generatedTime)) {
                double difference = difftime(mktime(&attendedTime), mktime(&generatedTime));
                timeDifference[timeDifferencesCount++] = difference;
            }
        }
    }

    // Calculate the average time difference
    if (timeDifferencesCount > 0) {
        double totalDifference = 0.0;
        for (int i = 0; i < timeDifferencesCount; i++) {
            totalDifference += timeDifference[i];
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
void CountCounterByDate(int idRc, int idDc) {
    int counters[4] = {0};  // Array to store the count for each counter

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
        if (strstr(ticketsR[i].dateCalled, date) != NULL) {
            counters[ticketsR[i].counter - 1]++;
        }
    }

    for (int i = 0; i < idDc; i++) {
        if (strstr(ticketsD[i].dateCalled, date) != NULL) {
            counters[ticketsD[i].counter - 1]++;
        }
    }

    // Determine the most productive counter
    printf("The most productive counter is: ");
    int mostProductiveCounter = 0;
    for (int i = 1; i < 4; i++) {
        if (counters[i] > counters[mostProductiveCounter]) {
            mostProductiveCounter = i;
        }
    }

    if (counters[mostProductiveCounter] > 0) {
        printf("Counter %d\n", mostProductiveCounter + 1);
    } else {
        printf("There is no most productive counter\n");
    }

    // Determine the least productive counter
    printf("The least productive counter is: ");
    int leastProductiveCounter = 0;
    for (int i = 1; i < 4; i++) {
        if (counters[i] < counters[leastProductiveCounter]) {
            leastProductiveCounter = i;
        }
    }

    if (counters[leastProductiveCounter] > 0) {
        printf("Counter %d\n", leastProductiveCounter + 1);
    } else {
        printf("There is no least productive counter\n");
    }
}

void DisplayRevenueByDate(int idDc) {
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