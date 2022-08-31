#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "lists.h"

uint16_t MODE = 0;
uint8_t VALIDITY_FLAG;

int main() {
    while (MODE != EXIT) {
        /////////////////////////////////////////////////////////
        // Mode Selection Segment
        ////////////////////////////////////////////////////////
        if (MODE == 0) {
            printf("Enter (1) for User Mode, or (2) for Admin Mode\n");
            do {
                printf("Selected Mode: ");
                VALIDITY_FLAG = scanf("%hu", &MODE);
                if (VALIDITY_FLAG != TRUE) // Infinite Loop Guard In Case of Character Entry.
                    fflush(stdin);
            } while ((MODE != USER && MODE != ADMIN) || VALIDITY_FLAG != TRUE); // Force Valid Entry.
        }

        /////////////////////////////////////////////////////////
        // Login Segment
        ////////////////////////////////////////////////////////

        if (MODE == ADMIN) {
            printf("You have selected Admin Mode, please enter your 4 digit pin.\n");
            uint8_t TRIES_REMAINING = 3;
            uint16_t PIN = 0;
            while (TRIES_REMAINING > 0) {
                do {
                    printf("Pin: ");
                    VALIDITY_FLAG = scanf("%hu", &PIN);
                    if (VALIDITY_FLAG != TRUE) // Infinite Loop Guard In Case of Character Entry.
                        fflush(stdin);
                } while (PIN != ADMIN_PIN && VALIDITY_FLAG != TRUE); // Force Valid Entry.
                printf("\n");
                if (PIN == ADMIN_PIN) {
                    printf("Welcome Admin\n\n");
                    break;
                } else {
                    if (--TRIES_REMAINING > 0)
                        TRIES_REMAINING == 1 ?
                        printf("Wrong Password! %d Trial Left.\n", TRIES_REMAINING) :
                        printf("Wrong Password! %d Trials Left.\n", TRIES_REMAINING);
                    else {
                        printf("Wrong Password. No More Trials.\n");
                        printf("You have failed to verify as an admin, switching to user mode..\n");
                        MODE = USER;
                        system("pause");
                        printf("\n");
                    }
                }
            }

            /////////////////////////////////////////////////////////
            // Admin Control Segment
            ////////////////////////////////////////////////////////
            if (MODE == ADMIN) {  // If Condition mainly for upcoming loops, to check for any switching in modes.
                do {
                    uint16_t ADMIN_SELECTED_OPTION = 0;

                    printf("Please select an option:\n"
                           "(1) Add Patient Data.\n"
                           "(2) Delete Patient Data\n"
                           "(3) Edit Existing Patient's Data.\n"
                           "(4) View All Patient Data\n"
                           "(5) Reserve a Timeslot\n"
                           "(6) Cancel an Existing Reservation\n"
                           "(7) View All Reservation Data\n"
                           "(8) Switch to User Mode\n"
                           "(9) Exit\n");

                    do {
                        printf("Option: ");
                        VALIDITY_FLAG = scanf("%hu", &ADMIN_SELECTED_OPTION);
                        if (VALIDITY_FLAG != TRUE) // Infinite Loop Guard In Case of Character Entry.
                            fflush(stdin);
                    } while (ADMIN_SELECTED_OPTION == 0 ||
                             ADMIN_SELECTED_OPTION > 9 || VALIDITY_FLAG != TRUE); // Force Valid Entry.

                    switch (ADMIN_SELECTED_OPTION) {
                        case ADD_PATIENT:
                            add_patient();
                            break;

                        case EDIT_PATIENT:
                            edit_patient_data(get_id());
                            break;

                        case ADD_RESERVATION: {
                            add_reservation(get_id());
                            break;
                        }

                        case CANCEL_RESERVATION: {
                            cancel_reservation(get_id());
                            break;
                        }

                        case DELETE_PATIENT_DATA: {
                            delete_patient_data(get_id());
                            break;
                        }

                        case VIEW_ALL_RECORDS:
                            view_all_data();
                            break;

                        case VIEW_ALL_RESERVATIONS:
                            view_reservations();
                            break;

                        case SWITCH_USER:
                            printf("\nSwitching to user mode..\n");
                            MODE = USER;
                            break;

                        case ADMIN_EXIT:
                            printf("Goodbye!\n");
                            MODE = EXIT;
                            system("exit");
                            break;

                        default:
                            break;

                    }
                    system("pause");
                    printf("\n");
                } while (MODE == ADMIN); // Check Admin Hasn't Switched Modes.
            }
        }

        if (MODE == USER) {
            printf("You are logged in as a user.\n");
            do {
                uint16_t USER_SELECTED_OPTION = 0;
                printf("\nPlease select an option:\n"
                       "(1) View a Patient's Records.\n"
                       "(2) View Reservations.\n"
                       "(3) Switch to Admin.\n"
                       "(4) Exit.\n");

                do {
                    printf("Option: ");
                    VALIDITY_FLAG = scanf("%hu", &USER_SELECTED_OPTION);
                    if (VALIDITY_FLAG != TRUE) // Infinite Loop Guard In Case of Character Entry.
                        fflush(stdin);
                } while (MODE == USER && USER_SELECTED_OPTION > 4 || USER_SELECTED_OPTION == 0 ||
                         VALIDITY_FLAG != TRUE); // Force Valid Entry.

                switch (USER_SELECTED_OPTION) {

                    case VIEW_PATIENT_RECORD:
                        view_patient_data(get_id());
                        break;

                    case VIEW_RESERVATIONS:
                        view_reservations();
                        break;

                    case SWITCH_ADMIN:
                        MODE = ADMIN;
                        break;

                    case USER_EXIT:
                        MODE = EXIT;
                        printf("Goodbye!\n");
                        system("pause");
                        break;

                    default:
                        break;
                }
            } while (MODE == USER);
        }
    }
}