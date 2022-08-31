#include <stdio.h>
#include <stdlib.h>
#include "lists.h"

PATIENT *LIST_HEAD = NULL;
uint16_t TIME_SLOTS[6] = {};
const char *SLOTS_DICTIONARY[] = {"2:00 to 2:30", "2:30 to 3:00", "3:00 to 3:30", "3:30 to 4:00", "4:00 to 4:30",
                                  "4:30 to 5:00"};

uint16_t get_id() {
    uint16_t PATIENT_ID;
    do {
        printf("Please enter the patient's ID: ");
        VALIDITY_FLAG = scanf("%hu", &PATIENT_ID);
        if (VALIDITY_FLAG != TRUE) // Infinite Loop Guard In Case of Character Entry.
            fflush(stdin);
    } while (VALIDITY_FLAG != TRUE);
    return PATIENT_ID;
}

void add_patient() {
    PATIENT *PATIENT_DATA = malloc(sizeof(PATIENT));
    ID_ENTRY:
    do {
        printf("\nEnter Patient ID: ");
        VALIDITY_FLAG = scanf("%hu", &PATIENT_DATA->ID);
        if (VALIDITY_FLAG != TRUE) // Infinite Loop Guard In Case of Character Entry.
            fflush(stdin);
    } while (VALIDITY_FLAG != TRUE);

    if (ID_EXISTS(PATIENT_DATA->ID) == TRUE) {
        printf("ID Taken, Try Another ID.\n");
        goto ID_ENTRY;
    }

    printf("\nEnter Patient Name: ");
    fflush(stdin);
    fgets(PATIENT_DATA->name, MAX_NAME_SIZE, stdin);
    fflush(stdin);

    do {
        printf("\nEnter Patient Age: ");
        VALIDITY_FLAG = scanf("%hu", &PATIENT_DATA->age);
        if (VALIDITY_FLAG != TRUE) // Infinite Loop Guard In Case of Character Entry.
            fflush(stdin);
    } while (PATIENT_DATA->age > 100 || VALIDITY_FLAG != TRUE);
    fflush(stdin);

    printf("\nSelect Patient Gender: "
           "\n(1) Male"
           "\n(2) Female\n");
    do {
        printf("Selection: ");
        VALIDITY_FLAG = scanf("%hu", &PATIENT_DATA->gender);
        if (VALIDITY_FLAG != TRUE) // Infinite Loop Guard In Case of Character Entry.
            fflush(stdin);
    } while (PATIENT_DATA->gender < MALE || PATIENT_DATA->gender > FEMALE || VALIDITY_FLAG != TRUE);

    PATIENT_DATA->next = LIST_HEAD;
    LIST_HEAD = PATIENT_DATA;
}

uint8_t ID_EXISTS(uint16_t ID) {
    PATIENT *DATA_POINTER = LIST_HEAD;
    while (DATA_POINTER != NULL) {
        if (ID == DATA_POINTER->ID) {
            return TRUE;
        } else
            DATA_POINTER = DATA_POINTER->next;
    }
    return FALSE;
}

int8_t RESERVATION_EXISTS(uint16_t ID) {
    for (int8_t SLOT = 0; SLOT < 6; SLOT++) {
        if (TIME_SLOTS[SLOT] == ID) {
            return SLOT;
        }
    }
    return ERROR;
}


void view_all_data() {
    printf("\nCurrently entered data: \n");
    PATIENT *DATA_POINTER = LIST_HEAD;
    int counter = 1;
    while (DATA_POINTER != NULL) {
        // Print patient data
        printf("\n%u)Patient ID Number (%u): \n", counter, DATA_POINTER->ID);
        printf("\tPatient Name: %s", DATA_POINTER->name);
        printf("\tPatient Age: %u\n", DATA_POINTER->age);
        DATA_POINTER->gender == MALE ?
        printf("\tPatient Gender: Male\n") :
        printf("\tPatient Gender: Female\n");


        DATA_POINTER = DATA_POINTER->next;
        ++counter;
    }
    printf("\n");
    printf("List size is %u\n\n", counter - 1);
}

void view_patient_data(uint16_t SEARCH_ID) {
    PATIENT *DATA_POINTER = LIST_HEAD;
    uint8_t FOUND = FALSE;
    while (DATA_POINTER != NULL) {
        // Print patient data
        if (SEARCH_ID == DATA_POINTER->ID) {
            printf("\nPatient ID Number (%u): \n", DATA_POINTER->ID);
            printf("\tPatient Name: %s", DATA_POINTER->name);
            printf("\tPatient Age: %u\n", DATA_POINTER->age);
            DATA_POINTER->gender == MALE ?
            printf("\tPatient Gender: Male\n") :
            printf("\tPatient Gender: Female\n");
            FOUND = TRUE;
            break;
        } else
            DATA_POINTER = DATA_POINTER->next;
    }
    if (FOUND == FALSE)
        printf("No Patients With ID (%u) Exist\n", SEARCH_ID);
}

void add_reservation(uint16_t ID) {

    if (ID_EXISTS(ID) == FALSE) {
        printf("No Patients With ID (%u) Exist\n", ID);
        return;
    }

    int8_t RESERVED_SLOT = RESERVATION_EXISTS(ID);

    if (RESERVED_SLOT != ERROR) {
        printf("Patient ID (%u) Already Has a Reservation For Timeslot (%u) %s\n", ID, RESERVED_SLOT + 1,
               SLOTS_DICTIONARY[RESERVED_SLOT]);
        return;
    }

    view_reservations();
    uint16_t SLOT;
    printf("\nWhich Timeslot Would You Like To Reserve?\nChoose Between:\n");

    for (int TIME = TIME_2_TO_230; TIME <= TIME_430_TO_5; ++TIME)
        if (TIME_SLOTS[TIME] == 0)
            printf("\tSlot (%u) %s\n", TIME + 1, SLOTS_DICTIONARY[TIME]);

    do {
        printf("Selection: ");
        VALIDITY_FLAG = scanf("%hu", &SLOT);
        if (VALIDITY_FLAG != TRUE) // Infinite Loop Guard In Case of Character Entry.
            fflush(stdin);
    } while (VALIDITY_FLAG != TRUE || SLOT < 1 || SLOT > 6);

    if (TIME_SLOTS[SLOT - 1] == FREE) {
        TIME_SLOTS[SLOT - 1] = ID;
        printf("Time Slot (%u) %s Has Been Reserved For Patient ID (%u) Successfully.\n", SLOT,
               SLOTS_DICTIONARY[SLOT - 1], ID);
    } else
        printf("Slot Already Taken.\n");
}

void view_reservations() {
    printf("Timeslot List:\n");
    for (int TIME = TIME_2_TO_230; TIME <= TIME_430_TO_5; ++TIME) {
        printf("(%u)   %s\t", TIME + 1, SLOTS_DICTIONARY[TIME]);
        TIME_SLOTS[TIME] == 0 ? printf("FREE\n") : printf("Reserved by ID (%u)\n", TIME_SLOTS[TIME]);
    }
    printf("\n");
}

void edit_patient_data(uint16_t SEARCH_ID) {

    if (LIST_HEAD == NULL) {
        printf("There Are No Data Entries To Edit.\n");
        return;
    }

    PATIENT *DATA_POINTER = LIST_HEAD;
    uint8_t FOUND = FALSE;
    while (DATA_POINTER != NULL) {
        if (SEARCH_ID == DATA_POINTER->ID) {
            uint16_t OPTION = 0;
            do {
                printf("What Would You Like To Edit?\n"
                       "1.ID\n"
                       "2.Name\n"
                       "3.Age\n"
                       "4.Gender\n"
                       "5.All\n");
                VALIDITY_FLAG = scanf("%hu", &OPTION);
                if (VALIDITY_FLAG != TRUE) // Infinite Loop Guard In Case of Character Entry.
                    fflush(stdin);
            } while ((OPTION > 5 || OPTION < 1) && VALIDITY_FLAG != TRUE);

            switch (OPTION) {

                default:

                case ID: {
                    printf("\nOld Patient ID Number (%hu):\n", DATA_POINTER->ID);
                    uint16_t TEMP;
                    do {
                        printf("New Patient ID Number: ");
                        VALIDITY_FLAG = scanf("%hu", &TEMP);
                        if (VALIDITY_FLAG != TRUE) // Infinite Loop Guard In Case of Character Entry.
                            fflush(stdin);
                        if (TEMP == DATA_POINTER->ID)
                            break;
                    } while (ID_EXISTS(TEMP) == TRUE || VALIDITY_FLAG != TRUE);


                    // Adjust reservations with new ID instead of old ID.
                    for (int TIME = TIME_2_TO_230; TIME <= TIME_430_TO_5; ++TIME) {
                        if (TIME_SLOTS[TIME] == DATA_POINTER->ID) {
                            TIME_SLOTS[TIME] = TEMP;
                            break;
                        }
                    }

                    DATA_POINTER->ID = TEMP;


                    if (OPTION != ALL)
                        break;
                }

                case NAME: {
                    printf("\nOld Patient Name: %s", DATA_POINTER->name);
                    printf("New Patient Name: ");
                    fflush(stdin);
                    fgets(DATA_POINTER->name, MAX_NAME_SIZE, stdin);

                    if (OPTION != ALL)
                        break;
                }

                case AGE: {
                    printf("\nOld Patient Age: %hu\n", DATA_POINTER->age);
                    do {
                        printf("Enter New Patient Age: ");
                        VALIDITY_FLAG = scanf("%hu", &DATA_POINTER->age);
                        if (VALIDITY_FLAG != TRUE) // Infinite Loop Guard In Case of Character Entry.
                            fflush(stdin);
                    } while (DATA_POINTER->age > 100 || VALIDITY_FLAG != TRUE);
                    fflush(stdin);

                    if (OPTION != ALL)
                        break;
                }

                case GENDER: {
                    uint16_t SELECTION = 0;
                    (DATA_POINTER->gender == MALE) ?
                    printf("\nOld Patient Gender: Male") :
                    printf("\nOld Patient Gender: Female");
                    printf("\nSelect New Patient Gender: "
                           "\n(1) Male"
                           "\n(2) Female\n");
                    do {
                        printf("Selection: ");
                        VALIDITY_FLAG = scanf("%hu", &SELECTION);
                        if (VALIDITY_FLAG != TRUE) // Infinite Loop Guard In Case of Character Entry.
                            fflush(stdin);
                    } while (SELECTION < MALE || SELECTION > FEMALE || VALIDITY_FLAG != TRUE);
                    DATA_POINTER->gender = SELECTION;
                    break;
                }
            }
            FOUND = TRUE;
            break;
        } else
            DATA_POINTER = DATA_POINTER->next;
    }
    if (FOUND == FALSE)
        printf("No Patients With ID (%u) Exist\n", SEARCH_ID);
}

void cancel_reservation(uint16_t ID) {

    if (empty_reservation_list() == TRUE) {
        printf("There Are No Reservations Yet To Cancel.\n");
        return;
    }
    for (int TIME = TIME_2_TO_230; TIME <= TIME_430_TO_5; ++TIME) {
        if (TIME_SLOTS[TIME] == ID) {
            TIME_SLOTS[TIME] = 0;
            printf("Patient ID (%u) Reservation For Slot (%d) %s Cancelled Successfully.\n", ID, TIME + 1,
                   SLOTS_DICTIONARY[TIME]);
            return;
        }
    }

    printf("\nNo reservations with ID (%u) exist.\n", ID);
}

uint8_t empty_reservation_list() {
    for (int TIME = TIME_2_TO_230; TIME <= TIME_430_TO_5; ++TIME) {
        if (TIME_SLOTS[TIME] != 0)
            return FALSE;
    }
    return TRUE;
}


void delete_patient_data(uint16_t ID) {

    if (LIST_HEAD == NULL) {
        printf("There Are No Data Entries To Delete.\n");
        return;
    }

    if (ID_EXISTS(ID) == FALSE) {
        printf("No patients with ID (%u) exist.\n", ID);
        return;
    }

    for (int TIME = TIME_2_TO_230; TIME <= TIME_430_TO_5; ++TIME) {
        if (TIME_SLOTS[TIME] == ID) {
            TIME_SLOTS[TIME] = 0;
            break;
        }
    }

    PATIENT *DATA_POINTER = LIST_HEAD;

    if (LIST_HEAD->ID == ID) {
        PATIENT *temp;
        temp = LIST_HEAD;
        LIST_HEAD = LIST_HEAD->next;
        printf("Patient ID (%u) Data Removed Successfully\n", ID);
        free(temp);
        view_all_data();
        return;
    }

    while (DATA_POINTER != NULL) {
        if (DATA_POINTER->next->ID == ID) {
            PATIENT *temp;
            temp = DATA_POINTER->next;
            DATA_POINTER->next = DATA_POINTER->next->next;
            printf("Patient ID (%u) data has been removed successfully\n", ID);
            free(temp);
            view_all_data();
            return;
        }
        DATA_POINTER = DATA_POINTER->next;
    }
}