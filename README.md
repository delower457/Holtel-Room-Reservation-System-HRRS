# 🏨 Hotel Reservation Management System
###  Programming and Problem Solving Lab Project – 5th Dimension

---
## 1. Executive Summary

The **Hotel Reservation Management System (HRMS)** is a console-based hotel management application developed in **ANSI C** as part of the **CSE114: Programming and Problem Solving Lab** course at **Daffodil International University (DIU)**.

The **Hotel Reservation Management System** is a lightweight, terminal-based application that allows hotel staff to manage up to **10 rooms**. It supports real-time booking with date-time overlap detection, guest search, and booking cancellation — all stored persistently in a text file.

---
## 2. Group Information
**Group Name:** 5th Dimension  
**Leader:** * Md. Delower Sarker(251-15-457)

**Members:**
* Labiba Tasneem (251-15-484)
* Rizia Karim (251-15-485)
* Aminul Islam (251-15-163)
* Ankita Baral (251-15-246)


---


## 3. Academic Information
* **Program:** Bachelor of Science in Computer Science and Engineering (CSE)
* **Course Code:** CSE114
* **Course Title:** Programming and Problem Solving Lab
* **Semester:** Summer 2025
* **Section:** 68_A1
* **Course Instructor:** Mr. Mehadi Hasan (Lecturer)
* **University:** Daffodil International University (DIU)

---

## 4. Features

- 🛏️ **Room Initialization** — Auto-creates 10 rooms on first run
- 📅 **Date-Time Booking** — Book rooms with check-in/check-out date and time (`DD/MM/YYYY HH:MM`)
- 🔁 **Overlap Detection** — Prevents double-booking for the same date-time range
- ❌ **Cancel Booking** — Instantly frees up a booked room
- 🔍 **Guest Search** — Search by guest name or room number
- 📋 **View All Rooms** — Displays full status of all rooms
- 💾 **File-Based Storage** — Data persists across sessions via `rooms.txt`
- ✅ **Leap Year Validation** — Accurately validates February dates

---

## 5. Technologies Used

| Technology | Detail                  |
|------------|-------------------------|
| Language   | C (Standard C99)        |
| Storage    | File I/O (`rooms.txt`)  |
| Compiler   | GCC                     |
| Platform   | Windows / Linux / macOS |

---

## 6. Data Structure

```c
typedef struct {
    int roomNo;         // Room number (1–10)
    char status[20];    // "Available" or "Booked"
    char name[50];      // Guest name
    char nid[20];       // National ID
    char phone[20];     // Phone number
    long long checkIn;  // Format: YYYYMMDDHHMM
    long long checkOut; // Format: YYYYMMDDHHMM
} Room;
```

---

## 7. File Structure

```plaintext
├── hotel_reservation.c     # Main source file
├── rooms.txt               # Auto-generated room data file
└── README.md               # Project documentation
```

---

## 8. How to Run

### Step 1 — Compile

```bash
gcc hotel_reservation.c -o hotel
```

### Step 2 — Run

```bash
./hotel
```

> **Windows:** `hotel.exe`

---

## 9. Menu Options

```
--- Hotel Reservation Menu ---
1. Show All Rooms
2. Book Room
3. Cancel Booking
4. Search Guest by Name/Room Number
5. Exit
```

| Option | Description                          |
|--------|--------------------------------------|
| 1      | Display all rooms with full details  |
| 2      | Book a room with guest info & dates  |
| 3      | Cancel an existing booking           |
| 4      | Search guest by name or room number  |
| 5      | Exit the program                     |

---

## 10. Example Workflow

### 10.1 Booking a Room

* Select **option 2** from the menu
* Enter room number (`1–10`)
* Enter guest name, NID, and phone number
* Enter check-in date/time: `DD/MM/YYYY HH:MM`
* Enter check-out date/time: `DD/MM/YYYY HH:MM`
* System validates dates and checks for overlapping bookings
* Confirmation message displayed on success

### 10.2 Cancelling a Booking

* Select **option 3** from the menu
* Enter the room number to cancel
* Room status reverts to `Available`

### 10.3 Searching a Guest

* Select **option 4** from the menu
* Enter guest name **or** room number
* Matching booking details are displayed

---

## 11. Contributors


Developed collaboratively by **5th Diension**, ensuring aligned teamwork,
structured development, and comprehensive testing across all modules.

---
## 12. License


Copyright (c) 2026 Md. Delower Sarker

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.


---


## 13. Acknowledgements

Special thanks to **Mehadi Hasan Sir**, Course Instructor,
for his continuous guidance, structured feedback, and academic
support throughout the project lifecycle.

---

