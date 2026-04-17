
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int roomNo;
    char status[20];
    char name[50];
    char nid[20];
    char phone[20];
    long long checkIn;   // YYYYMMDDHHMM
    long long checkOut;  // YYYYMMDDHHMM
} Room;

int isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

long long makeDateTimeInt(int d, int m, int y, int hh, int mm) {
    // YYYYMMDDHHMM
    return (long long)y * 100000000LL + (long long)m * 1000000LL + (long long)d * 10000LL + (long long)hh * 100LL + mm;
}

int isValidDate(int d, int m, int y) {
    if (y < 2025 || m < 1 || m > 12 || d < 1) return 0;
    int daysInMonth[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
    if (m == 2 && isLeapYear(y)) {
        if (d > 29) return 0;
    } else {
        if (d > daysInMonth[m]) return 0;
    }
    return 1;
}

void initializeRooms() {
    FILE *fp = fopen("rooms.txt", "r");
    if (fp == NULL) {
        fp = fopen("rooms.txt", "w");
        for (int i = 1; i <= 10; i++) {
            fprintf(fp, "%d Available - - - 0 0\n", i);
        }
        fclose(fp);
        printf("Room list initialized.\n");
    } else {
        fclose(fp);
    }
}

int isOverlap(long long in1, long long out1, long long in2, long long out2) {
    // in1<out2 && out1>in2 হলে overlap
    if (in1 < out2 && out1 > in2) return 1;
    return 0;
}

void printDateTime(long long dateTime) {
    if (dateTime == 0) {
        printf("-");
        return;
    }
    int y = dateTime / 100000000LL;
    int m = (dateTime / 1000000LL) % 100;
    int d = (dateTime / 10000LL) % 100;
    int hh = (dateTime / 100LL) % 100;
    int mm = dateTime % 100;
    printf("%02d/%02d/%04d %02d:%02d", d, m, y, hh, mm);
}

void showAllRooms() {
    FILE *fp = fopen("rooms.txt", "r");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }
    Room r;
    printf("\nRoom Status:\n");
    while (fscanf(fp, "%d %s %s %s %s %lld %lld",
                  &r.roomNo, r.status, r.name, r.nid, r.phone, &r.checkIn, &r.checkOut) != EOF) {
        printf("Room %d: %s | Guest: %s | NID: %s | Phone: %s | In: ",
               r.roomNo, r.status, r.name, r.nid, r.phone);
        printDateTime(r.checkIn);
        printf(" | Out: ");
        printDateTime(r.checkOut);
        printf("\n");
    }
    fclose(fp);
}

void bookRoom() {
    int roomNo, d1, m1, y1, hh1, mm1, d2, m2, y2, hh2, mm2;
    char name[50], nid[20], phone[20];

    printf("Enter room number (1-10): ");
    scanf("%d", &roomNo);

    if (roomNo < 1 || roomNo > 10) {
        printf("Room does not exist!\n");
        return;
    }

    printf("Enter Guest Name: ");
    scanf("%s", name);
    printf("Enter NID: ");
    scanf("%s", nid);
    printf("Enter Phone: ");
    scanf("%s", phone);

    printf("Enter Check-in (DD/MM/YYYY HH:MM): ");
    scanf("%d/%d/%d %d:%d", &d1, &m1, &y1, &hh1, &mm1);
    if (!isValidDate(d1, m1, y1)) {
        printf("Invalid check-in date!\n");
        return;
    }
    long long checkIn = makeDateTimeInt(d1, m1, y1, hh1, mm1);

    printf("Enter Check-out (DD/MM/YYYY HH:MM): ");
    scanf("%d/%d/%d %d:%d", &d2, &m2, &y2, &hh2, &mm2);
    if (!isValidDate(d2, m2, y2)) {
        printf("Invalid check-out date!\n");
        return;
    }
    long long checkOut = makeDateTimeInt(d2, m2, y2, hh2, mm2);

    if (checkOut <= checkIn) {
        printf("Check-out must be after check-in!\n");
        return;
    }

    FILE *fp = fopen("rooms.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    Room r;
    int booked = 0;

    while (fscanf(fp, "%d %s %s %s %s %lld %lld",
                  &r.roomNo, r.status, r.name, r.nid, r.phone, &r.checkIn, &r.checkOut) != EOF) {
        if (r.roomNo == roomNo) {
            if (strcmp(r.status, "Booked") == 0 && isOverlap(checkIn, checkOut, r.checkIn, r.checkOut)) {
                printf("Room already booked in this date-time range!\n");
                fprintf(temp, "%d %s %s %s %s %lld %lld\n",
                        r.roomNo, r.status, r.name, r.nid, r.phone, r.checkIn, r.checkOut);
            } else {
                fprintf(temp, "%d Booked %s %s %s %lld %lld\n",
                        roomNo, name, nid, phone, checkIn, checkOut);
                booked = 1;
            }
        } else {
            fprintf(temp, "%d %s %s %s %s %lld %lld\n",
                    r.roomNo, r.status, r.name, r.nid, r.phone, r.checkIn, r.checkOut);
        }
    }

    fclose(fp);
    fclose(temp);
    remove("rooms.txt");
    rename("temp.txt", "rooms.txt");

    if (booked) printf("Room %d booked successfully!\n", roomNo);
}

void cancelBooking() {
    int roomNo;
    printf("Enter room number to cancel: ");
    scanf("%d", &roomNo);

    if (roomNo < 1 || roomNo > 10) {
        printf("Room does not exist!\n");
        return;
    }

    FILE *fp = fopen("rooms.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    Room r;
    int cancelled = 0;

    while (fscanf(fp, "%d %s %s %s %s %lld %lld",
                  &r.roomNo, r.status, r.name, r.nid, r.phone, &r.checkIn, &r.checkOut) != EOF) {
        if (r.roomNo == roomNo && strcmp(r.status, "Booked") == 0) {
            fprintf(temp, "%d Available - - - 0 0\n", r.roomNo);
            cancelled = 1;
        } else {
            fprintf(temp, "%d %s %s %s %s %lld %lld\n",
                    r.roomNo, r.status, r.name, r.nid, r.phone, r.checkIn, r.checkOut);
        }
    }

    fclose(fp);
    fclose(temp);
    remove("rooms.txt");
    rename("temp.txt", "rooms.txt");

    if (cancelled) printf("Room %d booking cancelled!\n", roomNo);
    else printf("No booking found for Room %d.\n", roomNo);
}

void searchGuest() {
    char input[50];
    printf("Enter Guest Name or Room Number: ");
    scanf("%s", input);

    FILE *fp = fopen("rooms.txt", "r");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    Room r;
    int found = 0;
    while (fscanf(fp, "%d %s %s %s %s %lld %lld",
                  &r.roomNo, r.status, r.name, r.nid, r.phone, &r.checkIn, &r.checkOut) != EOF) {
        if ((strcmp(r.name, input) == 0 || atoi(input) == r.roomNo) && strcmp(r.status, "Booked") == 0) {
            printf("Found Guest: %s | Room: %d | NID: %s | Phone: %s | In: ",
                   r.name, r.roomNo, r.nid, r.phone);
            printDateTime(r.checkIn);
            printf(" | Out: ");
            printDateTime(r.checkOut);
            printf("\n");
            found = 1;
        }
    }
    fclose(fp);

    if (!found) printf("No guest found with given info.\n");
}

int main() {
    initializeRooms();
    int choice;
    while (1) {
        printf("\n--- Hotel Reservation Menu ---\n");
        printf("1. Show All Rooms\n");
        printf("2. Book Room\n");
        printf("3. Cancel Booking\n");
        printf("4. Search Guest by Name/Room Number\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: showAllRooms(); break;
            case 2: bookRoom(); break;
            case 3: cancelBooking(); break;
            case 4: searchGuest(); break;
            case 5: exit(0);
            default: printf("Invalid choice!\n");
        }
    }
    return 0;
}

