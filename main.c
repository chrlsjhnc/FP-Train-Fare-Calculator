#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_STATIONS 50
typedef struct {
char station1[30];
char station2[30];
int distance;
} Segment;
// LRT1, LRT2, and MRT segments (not shown for brevity)
// LRT1 segments
Segment lrt1Segments[] = {
{"Baclaran", "EDSA", 588},
{"EDSA", "Libertad", 1010},
{"Libertad", "Gil Puyat", 730},
{"Gil Puyat", "Vito Cruz", 1061},
{"Vito Cruz", "Quirino", 827},
{"Quirino", "Pedro Gil", 794},
{"Pedro Gil", "United Nations", 754},
{"United Nations", "Central Terminal", 1214},
{"Central Terminal", "Carriedo", 725},
{"Carriedo", "Doroteo Jose", 685},
{"Doroteo Jose", "Bambang", 648},
{"Bambang", "Tayuman", 618},
{"Tayuman", "Blumentritt", 671},
{"Blumentritt", "Abad Santos", 927},
{"Abad Santos", "R. Papa", 660},
{"R. Papa", "5th Avenue", 954},
{"5th Avenue", "Monumento", 1087},
{"Monumento", "Balintawak", 2250},
{"Balintawak", "Roosevelt", 1870}
};
// LRT2 segments
Segment lrt2Segments[] = {
{"Recto", "Legarda", 1050},
{"Legarda", "Pureza", 1389},
{"Pureza", "V. Mapa", 1350},
{"V. Mapa", "J. Ruiz", 1357},
{"J. Ruiz", "Gilmore", 928},
{"Gilmore", "Betty Go-Belmonte", 1075},
{"Betty Go-Belmonte", "Araneta Center-Cubao", 1164},
{"Araneta Center-Cubao", "Anonas", 955},
{"Anonas", "Katipunan", 438},
{"Katipunan", "Santolan", 1970}
};
// MRT segments
Segment mrtSegments[] = {
{"North Avenue", "Quezon Avenue", 1090},
{"Quezon Avenue", "GMA Kamuning", 1200},
{"GMA Kamuning", "Cubao", 1350},
{"Cubao", "Santolan-Annapolis", 1040},
{"Santolan-Annapolis", "Ortigas", 1280},
{"Ortigas", "Shaw Boulevard", 1090},
{"Shaw Boulevard", "Boni", 1150},
{"Boni", "Guadalupe", 1210},
{"Guadalupe", "Buendia", 1540},
{"Buendia", "Ayala", 870},
{"Ayala", "Magallanes", 1300},
{"Magallanes", "Taft Avenue", 1420}
};
int total_fare = 0;
int total_distance = 0;
char user_card_type[20] = "";
int beepBalance = 0;
int singleJourneyBalance = 0;
// LRT1, LRT2, and MRT3 fare matrices and stations (not shown for brevity)
int lrt1_fare_matrix[20][20] = {
{13, 14, 15, 16, 17, 18, 19, 20, 22, 23, 23, 24, 25, 26, 27, 28, 29, 30, 33, 35},
{14, 13, 15, 15, 17, 18, 19, 20, 21, 22, 23, 24, 24, 25, 26, 27, 28, 29, 32, 34},
{15, 15, 13, 14, 15, 16, 17, 18, 20, 21, 22, 22, 23, 24, 25, 26, 27, 28, 31, 33},
{16, 15, 14, 13, 15, 16, 17, 17, 19, 20, 21, 21, 22, 23, 24, 25, 26, 27, 30, 32},
{17, 17, 15, 15, 13, 14, 15, 16, 18, 19, 19, 20, 21, 22, 23, 24, 25, 26, 29, 31},
{18, 18, 16, 16, 14, 13, 14, 15, 17, 18, 18, 19, 20, 21, 22, 23, 24, 25, 28, 30},
{19, 19, 17, 17, 15, 14, 13, 14, 16, 17, 17, 18, 19, 20, 21, 22, 23, 24, 27, 29},
{20, 20, 18, 17, 16, 15, 14, 13, 15, 16, 16, 17, 18, 19, 20, 21, 22, 23, 26, 28},
{22, 21, 20, 19, 18, 17, 16, 15, 13, 14, 15, 16, 17, 17, 18, 19, 20, 22, 24, 27},
{23, 22, 21, 20, 19, 18, 17, 16, 14, 13, 14, 15, 16, 16, 17, 18, 19, 20, 23, 26},
{23, 23, 22, 21, 19, 18, 17, 16, 15, 14, 13, 14, 15, 16, 16, 17, 18, 19, 22, 25},
{24, 24, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 14, 15, 16, 16, 17, 18, 21, 24},
{25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 14, 15, 16, 17, 18, 21, 23},
{26, 25, 24, 23, 22, 21, 20, 19, 17, 16, 16, 15, 14, 13, 14, 15, 16, 17, 20, 22},
{27, 26, 25, 24, 23, 22, 21, 20, 18, 17, 16, 16, 15, 14, 13, 14, 15, 16, 19, 21},
{28, 27, 26, 25, 24, 23, 22, 21, 19, 18, 17, 16, 16, 15, 14, 13, 14, 15, 18, 20},
{29, 28, 27, 26, 25, 24, 23, 22, 20, 19, 18, 17, 16, 16, 15, 14, 13, 14, 17, 19},
{30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 16, 18},
{33, 32, 31, 30, 29, 28, 27, 26, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 13, 16},
{35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 16, 13}
};
char* lrt1_stations[20] = {
"Roosevelt", "Balintawak", "Monumento", "5th Avenue", "R. Papa",
"Abad Santos", "Blumentritt", "Tayuman", "Bambang", "Doroteo Jose",
"Carriedo", "Central Terminal", "United Nations", "Pedro Gil", "Quirino",
"Vito Cruz", "Gil Puyat", "Libertad", "EDSA", "Baclaran"
};
int lrt2_fare_matrix[13][13] = {
{13, 15, 16, 18, 19, 21, 22, 23, 25, 26, 28, 31, 33},
{15, 13, 15, 17, 18, 19, 21, 22, 24, 25, 27, 29, 32},
{16, 15, 13, 15, 16, 18, 19, 20, 22, 23, 26, 28, 30},
{18, 17, 15, 13, 15, 16, 17, 19, 20, 22, 24, 26, 29},
{19, 18, 16, 15, 13, 14, 16, 17, 19, 20, 22, 24, 27},
{21, 19, 18, 16, 14, 13, 15, 16, 18, 19, 21, 23, 26},
{22, 21, 19, 17, 16, 15, 13, 15, 16, 18, 20, 22, 25},
{23, 22, 20, 19, 17, 16, 15, 13, 15, 16, 19, 21, 23},
{25, 24, 22, 20, 19, 18, 16, 15, 13, 14, 17, 19, 22},
{26, 25, 23, 22, 20, 19, 18, 16, 14, 13, 16, 18, 21},
{28, 27, 26, 24, 22, 21, 20, 19, 17, 16, 13, 15, 18},
{31, 29, 28, 26, 24, 23, 22, 21, 19, 18, 15, 13, 16},
{33, 32, 30, 29, 27, 26, 25, 23, 22, 21, 18, 16, 13}
};
char* lrt2_stations[13] = {
"Recto", "Legarda", "Pureza", "V. Mapa", "J. Ruiz",
"Gilmore", "Betty Go-Belmonte", "Cubao", "Anonas", "Katipunan", "Santolan", "Marikina",
"Antipolo"
};
int mrt3_fare_matrix[13][13] = {
{13, 15, 17, 18, 20, 21, 23, 24, 26, 27, 29, 30, 32},
{15, 13, 15, 17, 19, 20, 22, 23, 25, 26, 28, 29, 31},
{17, 15, 13, 15, 16, 18, 19, 20, 22, 23, 25, 26, 28},
{18, 17, 15, 13, 15, 16, 18, 19, 21, 22, 24, 25, 27},
{20, 19, 17, 15, 13, 14, 16, 18, 20, 21, 23, 24, 26},
{21, 20, 18, 16, 14, 13, 15, 17, 19, 20, 22, 23, 25},
{23, 22, 19, 18, 16, 15, 13, 15, 17, 18, 20, 21, 23},
{24, 23, 20, 19, 18, 17, 15, 13, 16, 17, 19, 20, 22},
{26, 25, 22, 21, 20, 19, 17, 16, 13, 15, 17, 18, 20},
{27, 26, 23, 22, 21, 20, 18, 17, 15, 13, 15, 16, 18},
{29, 28, 25, 24, 23, 22, 20, 19, 17, 15, 13, 14, 16},
{30, 29, 26, 25, 24, 23, 21, 20, 18, 16, 14, 13, 15},
{32, 31, 28, 27, 26, 25, 23, 22, 20, 18, 16, 15, 13}
};
char* mrt3_stations[13] = {
"North Avenue", "Quezon Avenue", "Kamias", "Santolan", "Pasig",
"Shaw Boulevard", "Ortigas", "Boni", "Guadalupe", "Buendia",
"Ayala", "Magallanes", "Taft"
};
int lrt1_svt[20][20] = {
{13, 14, 15, 16, 17, 18, 19, 20, 22, 23, 23, 24, 25, 26, 27, 28, 29, 30, 33, 35},
{14, 13, 15, 15, 16, 18, 19, 20, 21, 22, 23, 24, 24, 25, 26, 27, 28, 29, 32, 34},
{15, 15, 13, 14, 15, 16, 17, 18, 20, 21, 22, 22, 23, 24, 25, 26, 27, 28, 31, 33},
{16, 15, 14, 13, 15, 16, 17, 17, 19, 20, 21, 21, 22, 23, 24, 25, 26, 27, 30, 32},
{17, 16, 15, 15, 13, 14, 15, 16, 18, 19, 20, 20, 21, 22, 23, 24, 25, 26, 29, 31},
{18, 18, 16, 16, 14, 13, 14, 15, 17, 18, 18, 19, 20, 21, 22, 23, 24, 25, 28, 30},
{19, 19, 17, 17, 15, 14, 13, 14, 16, 17, 17, 18, 19, 20, 21, 22, 23, 24, 27, 29},
{20, 20, 18, 17, 16, 15, 14, 13, 15, 16, 16, 17, 18, 19, 20, 21, 22, 23, 26, 28},
{22, 21, 20, 19, 18, 17, 16, 15, 13, 14, 15, 16, 17, 17, 18, 19, 20, 22, 24, 27},
{23, 22, 21, 20, 19, 18, 17, 16, 14, 13, 14, 15, 16, 16, 18, 18, 20, 21, 24, 26},
{23, 23, 22, 21, 20, 18, 17, 16, 15, 14, 13, 14, 15, 15, 17, 18, 19, 20, 23, 25},
{24, 24, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 14, 15, 16, 17, 18, 19, 22, 24},
{25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 14, 15, 16, 17, 18, 21, 23},
{26, 25, 24, 23, 22, 21, 20, 19, 17, 16, 15, 15, 14, 13, 15, 16, 18, 20, 23, 23},
{27, 26, 25, 24, 23, 22, 21, 20, 18, 18, 17, 16, 15, 15, 13, 14, 15, 17, 20, 22},
{28, 27, 26, 25, 24, 23, 22, 21, 19, 18, 18, 17, 16, 16, 14, 13, 14, 16, 18, 21},
{29, 28, 27, 26, 25, 24, 23, 22, 20, 20, 19, 18, 17, 18, 15, 14, 13, 15, 17, 20},
{30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 20, 17, 16, 15, 13, 16, 18},
{33, 32, 31, 30, 29, 28, 27, 26, 24, 24, 23, 22, 21, 23, 20, 18, 17, 16, 13, 16},
{35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 23, 22, 21, 20, 18, 16, 13}
};
int lr2_svt[13][13] = {
{13, 15, 16, 18, 19, 21, 22, 23, 25, 26, 28, 31, 33},
{15, 13, 15, 17, 18, 19, 21, 22, 24, 25, 27, 29, 32},
{16, 15, 13, 15, 16, 18, 19, 20, 22, 23, 26, 28, 30},
{18, 17, 15, 13, 15, 16, 17, 19, 20, 22, 24, 26, 29},
{19, 18, 16, 15, 13, 14, 16, 17, 19, 20, 22, 24, 27},
{21, 19, 18, 16, 14, 13, 15, 16, 18, 19, 21, 23, 26},
{22, 21, 19, 17, 16, 15, 13, 15, 16, 18, 20, 22, 25},
{23, 22, 20, 19, 17, 16, 15, 13, 15, 16, 19, 21, 23},
{25, 24, 22, 20, 19, 18, 16, 15, 13, 14, 17, 19, 22},
{26, 25, 23, 22, 20, 19, 18, 16, 14, 13, 16, 18, 21},
{28, 27, 26, 24, 22, 21, 20, 19, 17, 16, 13, 15, 18},
{31, 29, 28, 26, 24, 23, 22, 21, 19, 18, 15, 13, 16},
{33, 32, 30, 29, 27, 26, 25, 23, 22, 21, 18, 16, 13}
};
char ticket_type[20] = "";
void topupCard() {
int topupAmount;
printf("Your current Beep card balance is: ₱%d\n", beepBalance);
while (1) {
printf("Enter the amount you would like to top up (in pesos): ");
if (scanf("%d", &topupAmount) == 1 && topupAmount > 0) {
break;
} else {
printf("Invalid input. Please enter a positive integer value.\n");
// Clear the input buffer
while (getchar() != '\n');
}
}
beepBalance += topupAmount;
printf("Your new Beep card balance is: ₱%d\n", beepBalance);
}
void topupSingleJourney() {
int topupAmount;
printf("Your current single journey balance is: ₱%d\n", singleJourneyBalance);
while (1) {
printf("Enter the amount you would like to top up (in pesos): ");
if (scanf("%d", &topupAmount) == 1 && topupAmount > 0) {
break;
} else {
printf("Invalid input. Please enter a positive integer value.\n");
// Clear the input buffer
while (getchar() != '\n');
}
}
singleJourneyBalance += topupAmount;
printf("Your new single journey balance is: %d\n", singleJourneyBalance);
}
void getTicketType() {
char temp_ticket_type[20];
do {
printf("What type of ticket are you using? (single/beep): ");
scanf("%19s", temp_ticket_type);
if (strcasecmp(temp_ticket_type, "single") == 0) {
strcpy(ticket_type, "single");
printf("You have selected a single journey ticket.\n");
printf("Your current balance is: %d\n", singleJourneyBalance);
break;
} else if (strcasecmp(temp_ticket_type, "beep") == 0) {
strcpy(ticket_type, "beep");
strcpy(user_card_type, "Regular");
printf("You have selected a Beep card. Your current balance is: %d\n", beepBalance);
break;
} else {
printf("Invalid ticket type. Please enter 'single' or 'beep'.\n");
}
} while (1);
}
int isValidCardType(const char* cardType) {
return (strcasecmp(cardType, "Regular") == 0 ||
strcasecmp(cardType, "Student") == 0 ||
strcasecmp(cardType, "PWD") == 0 ||
strcasecmp(cardType, "Senior") == 0);
}
void getCardType() {
char temp_card_type[20];
do {
printf("What type of card are you using? (Regular, Student, PWD/Senior): ");
scanf("%s", temp_card_type);
if (!isValidCardType(temp_card_type)) {
printf("Invalid card type. Please enter 'Regular', 'Student', or 'PWD/Senior' \n");
}
} while (!isValidCardType(temp_card_type));
// Convert to proper case before storing
if (strcasecmp(temp_card_type, "Regular") == 0) {
strcpy(user_card_type, "Regular");
} else if (strcasecmp(temp_card_type, "Student") == 0) {
strcpy(user_card_type, "Student");
} else if (strcasecmp(temp_card_type, "PWD") == 0) {
strcpy(user_card_type, "PWD");
} else if (strcasecmp(temp_card_type, "Senior") == 0) {
strcpy(user_card_type, "Senior");
}
}
void displayStations(char* stations[], int size, const char* line_name) {
printf("%s Stations:\n", line_name);
for (int i = 0; i < size; i++) {
printf("%d. %s\n", i + 1, stations[i]);
}
printf("\n");
}
int getStationIndex(const char* prompt, int maxOption) {
int choice;
int result;
while (1) {
printf("%s(Enter -1 to stop || -2 to go back): ", prompt);
// Use scanf and check if it successfully reads an integer
result = scanf("%d", &choice);
// Clear input buffer if the input was not an integer
if (result != 1) {
printf("Invalid input. Please enter a valid integer.\n");
while (getchar() != '\n'); // Clear the input buffer
continue;
}
if (choice == -1) {
return -1; // Indicates stop
} else if (choice == -2) {
return -2; // Indicates go back
} else if (choice > 0 && choice <= maxOption) {
return choice - 1; // Valid station index (zero-based)
} else {
printf("Invalid choice. Please enter a number between 1 and %d.\n", maxOption);
}
}
}
void calculateFare(int* fareMatrix, int* svtMatrix, int matrixSize, char* stations[], int origin, int
destination) {
int fare;
if (strcmp(ticket_type, "beep") == 0 && svtMatrix != NULL) {
fare = svtMatrix[origin * matrixSize + destination];
printf("\nCurrent Beep card balance: ₱%d\n", beepBalance);
if (beepBalance - fare < 0) { //25 - 13
printf("Insufficient balance on your Beep card. The required fare is: ₱%d\n", fare);
while (beepBalance - fare < 0) {
printf("\n1. Top up your card\n");
printf("2. Cancel journey\n");
int choice;
printf("Enter your choice: ");
scanf("%d", &choice);
if (choice == 1) {
topupCard();
} else if (choice == 2) {
printf("Journey cancelled due to insufficient balance.\n");
return;
}
}
}
beepBalance -= fare;
printf("Remaining Beep card balance: ₱%d\n", beepBalance);
} else if (strcmp(ticket_type, "single") == 0) {
fare = fareMatrix[origin * matrixSize + destination];
printf("\nCurrent Single Journey balance: ₱%d\n", singleJourneyBalance);
if (singleJourneyBalance < fare) {
printf("Insufficient balance for your single journey ticket. The required fare is: ₱%d\n",
fare);
while (singleJourneyBalance < fare) {
printf("\n1. Top up Single Journey\n");
printf("2. Cancel journey\n");
int choice;
printf("Enter your choice: ");
scanf("%d", &choice);
if (choice == 1) {
topupSingleJourney();
} else if (choice == 2) {
printf("Journey cancelled due to insufficient balance.\n");
return;
}
}
}
singleJourneyBalance -= fare;
printf("Remaining Single Journey balance: ₱%d\n", singleJourneyBalance);
}
int original_fare = fare;
if (strcmp(user_card_type, "Student") == 0) {
fare = (int)(original_fare * 0.8 + 0.5); // 20% discount for students with rounding
} else if (strcmp(user_card_type, "PWD") == 0 || strcmp(user_card_type, "Senior") == 0) {
fare = (int)(original_fare * 0.7 + 0.5); // 30% discount for PWD/Seniors with rounding
}
printf("The fare from %s to %s is: %d", stations[origin], stations[destination], original_fare);
if (fare != original_fare) {
printf(" (discounted to %d)", fare);
}
printf("\n");
total_fare += fare;
}
int calculateDistance(Segment segments[], int size, int origin, int destination) {
int distance = 0;
int start = (origin < destination) ? origin : destination;
int end = (origin < destination) ? destination : origin;
for (int i = start; i < end; i++) {
distance += segments[i].distance;
}
total_distance += distance;
return distance;
}
int isTransferStation(int line, int station) {
if (line == 1 && strcmp(lrt1_stations[station], "Doroteo Jose") == 0) return 1;
if (line == 1 && strcmp(lrt1_stations[station], "EDSA") == 0) return 1;
if (line == 2 && strcmp(lrt2_stations[station], "Recto") == 0) return 1;
if (line == 2 && strcmp(lrt2_stations[station], "Cubao") == 0) return 1;
if (line == 3 && strcmp(mrt3_stations[station], "Cubao") == 0) return 1;
if (line == 3 && strcmp(mrt3_stations[station], "Taft") == 0) return 1;
return 0;
}
void transferStations(int* current_line, int* current_station) {
if (!isTransferStation(*current_line, *current_station)) {
printf("You are not at a transfer station. Continuing on the current line.\n");
return;
}
printf("\nTransfer Options:\n");
if (*current_line == 1 && strcmp(lrt1_stations[*current_station], "Doroteo Jose") == 0) {
printf("1. Transfer to LRT-2 Recto\n");
printf("2. No transfer (continue on current line)\n");
} else if (*current_line == 2 && strcmp(lrt2_stations[*current_station], "Recto") == 0) {
printf("1. Transfer to LRT-1 Doroteo Jose\n");
printf("2. No transfer (continue on current line)\n");
} else if (*current_line == 2 && strcmp(lrt2_stations[*current_station], "Cubao") == 0) {
printf("1. Transfer to MRT-3 Cubao\n");
printf("2. No transfer (continue on current line)\n");
} else if (*current_line == 3 && strcmp(mrt3_stations[*current_station], "Cubao") == 0) {
printf("1. Transfer to LRT-2 Cubao\n");
printf("2. No transfer (continue on current line)\n");
} else if (*current_line == 1 && strcmp(lrt1_stations[*current_station], "EDSA") == 0) {
printf("1. Transfer to MRT-3 Taft\n");
printf("2. No transfer (continue on current line)\n");
} else if (*current_line == 3 && strcmp(mrt3_stations[*current_station], "Taft") == 0) {
printf("1. Transfer to LRT-1 EDSA\n");
printf("2. No transfer (continue on current line)\n");
}
int transfer_choice;
while (1) {
printf("Enter your transfer choice: ");
int result = scanf("%d", &transfer_choice);
// Check if input is a valid integer
if (result != 1) {
printf("Invalid input. Please enter 1 or 2.\n");
while (getchar() != '\n'); // Clear invalid input from buffer
continue;
}
// Check if choice is within range
if (transfer_choice >= 1 && transfer_choice <= 2) {
break;
} else {
printf("Invalid choice. Please enter 1 or 2.\n");
}
}
if (transfer_choice == 1) {
switch (*current_line) {
case 1:
if (strcmp(lrt1_stations[*current_station], "Doroteo Jose") == 0) {
*current_line = 2;
*current_station = 0; // Index of Recto station in LRT-2
printf("Transferred to LRT-2 Recto Station\n");
} else if (strcmp(lrt1_stations[*current_station], "EDSA") == 0) {
*current_line = 3;
*current_station = 12; // Index of Taft station in MRT-3
printf("Transferred to MRT-3 Taft Station\n");
}
break;
case 2:
if (strcmp(lrt2_stations[*current_station], "Recto") == 0) {
*current_line = 1;
*current_station = 9; // Index of Doroteo Jose station in LRT-1
printf("Transferred to LRT-1 Doroteo Jose Station\n");
} else if (strcmp(lrt2_stations[*current_station], "Cubao") == 0) {
*current_line = 3;
*current_station = 3; // Index of Cubao station in MRT-3
printf("Transferred to MRT-3 Cubao Station\n");
}
break;
case 3:
if (strcmp(mrt3_stations[*current_station], "Cubao") == 0) {
*current_line = 2;
*current_station = 7; // Index of Cubao station in LRT-2
printf("Transferred to LRT-2 Cubao Station\n");
} else if (strcmp(mrt3_stations[*current_station], "Taft") == 0) {
*current_line = 1;
*current_station = 18; // Index of EDSA station in LRT-1
printf("Transferred to LRT-1 EDSA Station\n");
}
break;
}
} else {
printf("Continuing on the current line\n");
}
}
void rideLine(int current_line, int current_station) {
int* fare_matrix;
int* svt_matrix;
char** stations;
Segment* segments;
int size;
const char* line_name;
int matrix_size;
while (1) {
// Show current balance at the start of each leg
if (strcmp(ticket_type, "beep") == 0) {
printf("\nCurrent Beep card balance: ₱%d\n", beepBalance);
} else {
printf("\nCurrent Single Journey balance: ₱%d\n", singleJourneyBalance);
}
switch (current_line) {
case 1:
fare_matrix = &lrt1_fare_matrix[0][0];
svt_matrix = &lrt1_svt[0][0];
stations = lrt1_stations;
segments = lrt1Segments;
size = sizeof(lrt1Segments) / sizeof(lrt1Segments[0]);
line_name = "LRT-1";
matrix_size = 20;
break;
case 2:
fare_matrix = &lrt2_fare_matrix[0][0];
svt_matrix = &lr2_svt[0][0];
stations = lrt2_stations;
segments = lrt2Segments;
size = sizeof(lrt2Segments) / sizeof(lrt2Segments[0]);
line_name = "LRT-2";
matrix_size = 13;
break;
case 3:
fare_matrix = &mrt3_fare_matrix[0][0];
svt_matrix = &mrt3_fare_matrix[0][0];
stations = mrt3_stations;
segments = mrtSegments;
size = sizeof(mrtSegments) / sizeof(mrtSegments[0]);
line_name = "MRT-3";
matrix_size = 13;
break;
}
printf("You are currently at %s Station on %s\n", stations[current_station], line_name);
// Display stations
printf("%s Stations:\n", line_name);
for (int i = 0; i < matrix_size; i++) {
printf("%d. %s\n", i + 1, stations[i]);
}
printf("\n");
int destination = getStationIndex("Enter your destination station number (or 'stop' to end the
ride): ", matrix_size);
if (destination == -2) {
printf("Returning to line selection...\n");
printf("Total fare for this journey: ₱%d\n", total_fare);
printf("Total distance traveled: %d meters\n", total_distance);
break;
} else if (destination == -1) {
printf("Ride terminated.\n");
printf("Total fare for this journey: ₱%d\n", total_fare);
printf("Total distance traveled: %d meters\n", total_distance);
break;
} else if (destination == current_station) {
printf("You're already at this station. Please choose a different destination or 'stop' to end
the ride.\n");
continue;
}
calculateFare(fare_matrix, svt_matrix, matrix_size, stations, current_station, destination);
int leg_distance = calculateDistance(segments, size, current_station, destination);
printf("Distance traveled in this leg: %d meters\n", leg_distance);
current_station = destination;
transferStations(&current_line, &current_station);
}
}
int main() {
// ANSI Color codes
const char* CYAN = "\033[1;36m";
const char* GREEN = "\033[1;32m";
const char* YELLOW = "\033[1;33m";
const char* RESET = "\033[0m";
printf("%s╔════════════════════════════════╗\n", CYAN);
printf("║ Welcome to the Metro Fare ║\n");
printf("║ Calculator! ║\n");
printf("╚════════════════════════════════╝%s\n\n", RESET);
while (1) {
printf("%s\n═══════ Initial Menu ═══════%s\n", YELLOW, RESET);
printf("%s[1]%s Top up Beep Card\n", GREEN, RESET);
printf("%s[2]%s Top up Single Journey\n", GREEN, RESET);
printf("%s[3]%s Start Journey\n", GREEN, RESET);
printf("%s[4]%s Exit\n", GREEN, RESET);
int initial_choice;
printf("\n%sEnter your choice: %s", CYAN, RESET);
if (scanf("%d", &initial_choice) != 1) {
printf("\033[1;31mInvalid input. Please enter a number between 1 and 4.\033[0m\n");
while (getchar() != '\n');
continue;
}
// Rest of your switch case remains the same
switch (initial_choice) {
case 1:
topupCard();
strcpy(ticket_type, "beep");
strcpy(user_card_type, "Regular");
getCardType();
goto start_journey;
break;
case 2:
topupSingleJourney();
strcpy(ticket_type, "single");
getCardType();
goto start_journey;
break;
case 3:
getTicketType();
if (strcmp(ticket_type, "single") == 0) {
getCardType();
} else {
strcpy(user_card_type, "Regular");
}
goto start_journey;
case 4:
printf("%sExiting...%s\n", YELLOW, RESET);
return 0;
default:
printf("\033[1;31mInvalid choice. Please enter a number between 1 and 4.\033[0m\n");
break;
}
}
start_journey:
while (1) {
// Rest of your existing main menu code here
// Show current balance based on ticket type
if (strcmp(ticket_type, "beep") == 0) {
printf("\nCurrent Beep card balance: ₱%d\n", beepBalance);
} else {
printf("\nCurrent Single Journey balance: ₱%d\n", singleJourneyBalance);
}
printf("\nMain Menu\n");
printf("1. LRT-1\n");
printf("2. LRT-2\n");
printf("3. MRT-3\n");
printf("4. Exit Train\n");
printf("5. Change Ticket Type\n\n");
int choice;
do {
printf("Enter your choice: ");
if (scanf("%d", &choice) != 1) {
printf("Invalid choice. Please enter a number between 1 and 5.\n");
while (getchar() != '\n');
choice = 0;
} else if (choice < 1 || choice > 5) {
printf("Invalid choice. Please enter a number between 1 and 5.\n");
}
} while (choice < 1 || choice > 5);
if (choice == 5) {
getTicketType();
// After changing ticket type, ask if they want to top up
char topup_choice;
printf("\nWould you like to add balance to your ticket? (y/n): ");
scanf(" %c", &topup_choice);
if (topup_choice == 'y' || topup_choice == 'Y') {
if (strcmp(ticket_type, "beep") == 0) {
topupCard();
} else {
topupSingleJourney();
}
}
continue; // Go back to main menu after changing ticket type
} else if (choice == 4) {
printf("Exiting...\n");
printf("Your total fare for the entire journey: ₱%d\n", total_fare);
printf("Total distance traveled: %d meters\n", total_distance);
return 0;
}
int starting_station; // Declare once before switch
switch (choice) {
case 1:
displayStations(lrt1_stations, 20, "LRT-1");
starting_station = getStationIndex("Enter your starting station number ", 20);
if (starting_station == -1) {
printf("Exiting...\n");
printf("Your total fare for the entire journey: ₱%d\n", total_fare);
printf("Total distance traveled: %d meters\n", total_distance);
return 0;
} else if (starting_station == -2) {
continue; // Go back to line selection
}
rideLine(choice, starting_station);
break;
case 2:
displayStations(lrt2_stations, 13, "LRT-2");
starting_station = getStationIndex("Enter your starting station number ", 13);
if (starting_station == -1) {
printf("Exiting...\n");
printf("Your total fare for the entire journey: ₱%d\n", total_fare);
printf("Total distance traveled: %d meters\n", total_distance);
return 0;
} else if (starting_station == -2) {
continue; // Go back to line selection
}
rideLine(choice, starting_station);
break;
case 3:
displayStations(mrt3_stations, 13, "MRT-3");
starting_station = getStationIndex("Enter your starting station number ", 13);
if (starting_station == -1) {
printf("Exiting...\n");
printf("Your total fare for the entire journey: ₱%d\n", total_fare);
printf("Total distance traveled: %d meters\n", total_distance);
return 0;
} else if (starting_station == -2) {
continue; // Go back to line selection
}
rideLine(choice, starting_station);
break;
default:
printf("Unexpected error.\n");
break;
}
}
return 0;
}
