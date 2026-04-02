#ifndef __HC06_H
#define __HC06_H	 

#define HC05_NAME									"LZH"
#define HC05_PWD									"0000"
#define HC05_Baund								"9600"

void HC05_SetName(void);
void HC05_SetPassword(void);
void HC05_SetBaud(void);
void HC05_init(void);
void HC05_AT(void);

#endif
