#include <stdint.h>

#define MAX_NAME_SIZE 90
#ifndef _LISTS_H
#define _LISTS_H

extern uint8_t VALIDITY_FLAG;

typedef struct Patient_Data {
    uint16_t ID;
    uint16_t age;
    uint16_t gender;
    char name[MAX_NAME_SIZE];
    struct Patient_Data *next;
} PATIENT;

enum READABILITY {
    ERROR = -1,
    ADMIN_PIN = 1234,
    USER = 1,
    ADMIN,
    EXIT,
    ADD_PATIENT = 1,
    DELETE_PATIENT_DATA,
    EDIT_PATIENT,
    VIEW_ALL_RECORDS,
    ADD_RESERVATION,
    CANCEL_RESERVATION,
    VIEW_ALL_RESERVATIONS,
    SWITCH_USER,
    ADMIN_EXIT,
    VIEW_PATIENT_RECORD = 1,
    VIEW_RESERVATIONS,
    SWITCH_ADMIN,
    USER_EXIT
};


enum TIME_SLOTS {
    TIME_2_TO_230,
    TIME_430_TO_5 = 5,
    FREE = 0
};

enum OPTIONS {
    ID = 1,
    NAME,
    AGE,
    GENDER,
    ALL
};

enum BOOL {
    FALSE,
    TRUE,
    MALE = 1,
    FEMALE
};

void add_patient();

void view_reservations();

void view_all_data();

uint16_t get_id();

uint8_t empty_reservation_list();

uint8_t ID_EXISTS(uint16_t ID);

int8_t RESERVATION_EXISTS(uint16_t ID);

void view_patient_data(uint16_t ID);

void delete_patient_data(uint16_t ID);

void edit_patient_data(uint16_t ID);

void add_reservation(uint16_t ID);

void cancel_reservation(uint16_t ID);

#endif



