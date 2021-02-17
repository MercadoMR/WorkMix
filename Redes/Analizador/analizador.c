#include <stdio.h>
#include <stdlib.h>

void analiza_trama(unsigned char []);
void analiza_llc(unsigned char []);
void analiza_arp(unsigned char []);
void analiza_ip(unsigned char []);
void analiza_icmp(unsigned char [],unsigned char);
void analiza_tcp(unsigned char [],unsigned char);
void analiza_udp(unsigned char [],unsigned char);
void puertos_tcp(unsigned short int);
void puertos_udp(unsigned short int);
void hacer_checksum(unsigned char [],unsigned char );

unsigned char S[][5] = { "RR", "RNR", "RES", "SRES" };
unsigned char MC[][6] = { "UI", "SIM" , "NR0", "SARM","UP","-","-","SABM",
                          "DISC","-","NR2","SARME","SM","AC0","-","SABME","SNRM",
                          "-","NR1","RSET","-","-","-","XID","-","CFGR","NR3","SABME","TEST",
                          "AC1","-","-" };

unsigned char MR[][6] = { "UI", "RIM" , "NR0", "DM","-","-","-","-",
                          "RD","-","NR2","-","UA","AC0","-","-","-",
                          "FRMR","NR1","-","-","-","-","XID","-","CFGR","NR3","SNRME","TEST",
                          "AC1","-","BCN" };

int
main(void)
{
 unsigned char T[][200]=
	{ 
	    {0x00,0x02,0xb3,0x9c,0xae,0xba,0x00,0x02,0xb3,0x9c,0xdf,0x1b,0x00,0x03,0xf0,0xf0,
	     0x7f,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	     0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	     0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x43,0x05,0x90,0x6d}, //trama1
	    {0x00,0x02,0xb3,0x9c,0xdf,0x1b,0x00,0x02,0xb3,0x9c,0xae,0xba,0x00,0x03,0xf0,0xf1,
	     0x73,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	     0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	     0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x54,0x90,0x6d}, //trama2
	    {0x00,0x02,0xb3,0x9c,0xae,0xba,0x00,0x02,0xb3,0x9c,0xdf,0x1b,0x00,0x04,0xf0,0xf0,
		 0x01,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x41,0xa3,0x90,0x6d}, //trama3
		{0x00,0x02,0xb3,0x9c,0xdf,0x1b,0x00,0x02,0xb3,0x9c,0xae,0xba,0x00,0x04,0xf0,0xf1,
		 0x01,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xf2,0x90,0x6d}, //trama4
		{0x00,0x02,0xb3,0x9c,0xae,0xba,0x00,0x02,0xb3,0x9c,0xdf,0x1b,0x00,0x12,0xf0,0xf0,
		 0x00,0x01,0x0e,0x00,0xff,0xef,0x19,0x8f,0xbc,0x05,0x7f,0x00,0x23,0x00,0x7f,0x23,
		 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x41,0x91,0x6d}, //trama5
		{0x00,0x02,0xb3,0x9c,0xdf,0x1b,0x00,0x02,0xb3,0x9c,0xae,0xba,0x00,0x12,0xf0,0xf0,
		 0x00,0x03,0x0e,0x00,0xff,0xef,0x17,0x81,0xbc,0x05,0x23,0x00,0x7f,0x00,0x23,0x7f,
		 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x90,0x91,0x6d}, //trama6
		{0x00,0x02,0xb3,0x9c,0xdf,0x1b,0x00,0x02,0xb3,0x9c,0xae,0xba,0x00,0x04,0xf0,0xf1,
		 0x01,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xdf,0x91,0x6d}, //trama7
		{0x00,0x02,0xb3,0x9c,0xae,0xba,0x00,0x02,0xb3,0x9c,0xdf,0x1b,0x00,0x04,0xf0,0xf1,
		 0x01,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0xac,0x92,0x6d}, //trama8
		{0x00,0x02,0xb3,0x9c,0xae,0xba,0x00,0x02,0xb3,0x9c,0xdf,0x1b,0x00,0xac,0xf0,0xf0,
		 0x02,0x02,0x0e,0x00,0xff,0xef,0x16,0x04,0x00,0x00,0x00,0x00,0x28,0x00,0x7f,0x23,
		 0xff,0x53,0x4d,0x42,0x72,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x82,0x09,
		 0x00,0x77,0x00,0x02,0x50,0x43,0x20,0x4e,0x45,0x54,0x57,0x4f,0x52,0x4b,0x20,0x50,
		 0x52,0x4f,0x47,0x52,0x41,0x4d,0x20,0x31,0x2e,0x30,0x00,0x02,0x4d,0x49,0x43,0x52,
		 0x4f,0x53,0x4f,0x46,0x54,0x20,0x4e,0x45,0x54,0x57,0x4f,0x52,0x4b,0x53,0x20,0x33,
		 0x2e,0x30,0x00,0x02,0x44,0x4f,0x53,0x20,0x4c,0x4d,0x31,0x2e,0x32,0x58,0x30,0x30,
		 0x32,0x00,0x02,0x44,0x4f,0x53,0x20,0x4c,0x41,0x4e,0x4d,0x41,0x4e,0x32,0x2e,0x31,
		 0x00,0x02,0x57,0x69,0x6e,0x64,0x6f,0x77,0x73,0x20,0x66,0x6f,0x72,0x20,0x57,0x6f,
		 0x72,0x6b,0x67,0x72,0x6f,0x75,0x70,0x73,0x20,0x33,0x2e,0x31,0x61,0x00,0x02,0x4e,
		 0x54,0x20,0x4c,0x4d,0x20,0x30,0x2e,0x31,0x32,0x00,0x00,0xfb,0x92,0x6d,0x86,0xdf}, //trama9
		{0x00,0x02,0xb3,0x9c,0xdf,0x1b,0x00,0x02,0xb3,0x9c,0xae,0xba,0x00,0x04,0xf0,0xf1,
		 0x01,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7b,0x93,0x6d}, //trama10
		{0x00,0x02,0xb3,0x9c,0xdf,0x1b,0x00,0x02,0xb3,0x9c,0xae,0xba,0x00,0x5f,0xf0,0xf0,
		 0x02,0x04,0x0e,0x00,0xff,0xef,0x16,0x0c,0x00,0x00,0x28,0x00,0x28,0x00,0x23,0x7f,
		 0xff,0x53,0x4d,0x42,0x72,0x00,0x00,0x00,0x00,0x80,0x00,0x00,0x00,0x00,0x00,0x00,
		 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x82,0x09,
		 0x11,0x05,0x00,0x02,0x02,0x00,0x01,0x00,0x68,0x0b,0x00,0x00,0x00,0x00,0x01,0x00,
		 0x7f,0x07,0x00,0x80,0x03,0x02,0x00,0x00,0x00,0xe5,0xfe,0x29,0x25,0x7c,0xc2,0x01,
		 0x2c,0x01,0x08,0x08,0x00,0x7f,0x07,0x00,0x80,0x32,0x3e,0xb9,0x3d,0x00,0xca,0x93}, //trama11
		{0x00,0x02,0xb3,0x9c,0xae,0xba,0x00,0x02,0xb3,0x9c,0xdf,0x1b,0x00,0x04,0xf0,0xf1,
		 0x01,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7c,0x94,0x6d}, //trama12
		{0x00,0x02,0xb3,0x9c,0xae,0xba,0x00,0x02,0xb3,0x9c,0xdf,0x1b,0x00,0x91,0xf0,0xf0,
		 0x04,0x04,0x0e,0x00,0xff,0xef,0x16,0x0c,0x00,0x00,0x28,0x00,0x28,0x00,0x7f,0x23,
		 0xff,0x53,0x4d,0x42,0x73,0x00,0x00,0x00,0x00,0x10,0x00,0x00,0x00,0x00,0x00,0x00,
		 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x82,0x09,
		 0x0d,0x75,0x00,0x5d,0x00,0x68,0x0b,0x02,0x00,0x00,0x00,0x7f,0x07,0x00,0x80,0x00,
		 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x20,0x00,0x00,0x00,0x45,
		 0x53,0x43,0x4f,0x4d,0x00,0x57,0x69,0x6e,0x64,0x6f,0x77,0x73,0x20,0x34,0x2e,0x30,
		 0x00,0x57,0x69,0x6e,0x64,0x6f,0x77,0x73,0x20,0x34,0x2e,0x30,0x00,0x04,0xff,0x00,
		 0x00,0x00,0x02,0x00,0x02,0x00,0x17,0x00,0x20,0x00,0x5c,0x5c,0x50,0x52,0x4f,0x47,
		 0x59,0x44,0x45,0x53,0x41,0x5c,0x49,0x50,0x43,0x24,0x00,0x49,0x50,0x43,0x00,0x00}, //trama13
		{0x00,0x02,0xb3,0x9c,0xdf,0x1b,0x00,0x02,0xb3,0x9c,0xae,0xba,0x00,0x04,0xf0,0xf1,
		 0x01,0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x32,0x95,0x6d}, //trama14
		{0x00,0x02,0xb3,0x9c,0xdf,0x1b,0x00,0x02,0xb3,0x9c,0xae,0xba,0x00,0x46,0xf0,0xf0,
		 0x04,0x06,0x0e,0x00,0xff,0xef,0x16,0x0c,0x00,0x00,0x28,0x00,0x28,0x00,0x23,0x7f,
		 0xff,0x53,0x4d,0x42,0x73,0x00,0x00,0x00,0x00,0x90,0x00,0x00,0x00,0x00,0x00,0x00,
		 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0xc0,0x00,0x00,0x00,0x00,0x82,0x09,
		 0x03,0x75,0x00,0x29,0x00,0x00,0x00,0x00,0x00,0x02,0xff,0x00,0x00,0x00,0x04,0x00,
		 0x49,0x50,0x43,0x00,0x00,0x81,0x95,0x6d,0x86,0xcb,0x94,0x6d,0x86,0x0d,0x09,0x0e}, //trama15
		{0x00,0x02,0xb3,0x9c,0xae,0xba,0x00,0x02,0xb3,0x9c,0xdf,0x1b,0x00,0x04,0xf0,0xf1,
		 0x01,0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x96,0x6d}, //trama16
		{0x00,0x02,0xb3,0x9c,0xae,0xba,0x00,0x02,0xb3,0x9c,0xdf,0x1b,0x00,0x7e,0xf0,0xf0,
		 0x06,0x06,0x0e,0x00,0xff,0xef,0x16,0x0c,0x00,0x00,0x28,0x00,0x28,0x00,0x7f,0x23,
		 0xff,0x53,0x4d,0x42,0x25,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0xc0,0x00,0x00,0x00,0x00,0x82,0x0a,
		 0x0e,0x20,0x00,0x00,0x00,0x08,0x00,0x00,0x10,0x00,0x00,0x00,0x00,0x88,0x13,0x00,
		 0x00,0x00,0x00,0x20,0x00,0x4c,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x2d,0x00,0x5c,
		 0x50,0x49,0x50,0x45,0x5c,0x4c,0x41,0x4e,0x4d,0x41,0x4e,0x00,0x68,0x00,0x57,0x72,
		 0x4c,0x65,0x68,0x44,0x7a,0x00,0x42,0x31,0x36,0x42,0x42,0x44,0x7a,0x00,0x01,0x00,
		 0x00,0x10,0xff,0xff,0xff,0xff,0x45,0x53,0x43,0x4f,0x4d,0x00,0x00,0x6f,0x96,0x6d}, //trama17
		{0x00,0x02,0xb3,0x9c,0xdf,0x1b,0x00,0x02,0xb3,0x9c,0xae,0xba,0x00,0x04,0xf0,0xf1,
		 0x01,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xbe,0x96,0x6d}, //trama18
		{0x00,0x02,0xb3,0x9c,0xae,0xba,0x00,0x02,0xb3,0x9c,0xdf,0x1b,0x00,0x04,0xf0,0xf1,
		 0x01,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x5d,0x97,0x6d}, //trama19
		{0x00,0x02,0xb3,0x9c,0xae,0xba,0x00,0x02,0xb3,0x9c,0xdf,0x1b,0x00,0x7e,0xf0,0xf0,
		 0x08,0x08,0x0e,0x00,0xff,0xef,0x16,0x0c,0x00,0x00,0x28,0x00,0x28,0x00,0x7f,0x23,
		 0xff,0x53,0x4d,0x42,0x25,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0xc0,0x00,0x00,0x00,0x00,0x02,0x0b,
		 0x0e,0x20,0x00,0x00,0x00,0x08,0x00,0x00,0x10,0x00,0x00,0x00,0x00,0x88,0x13,0x00,
		 0x00,0x00,0x00,0x20,0x00,0x4c,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x2d,0x00,0x5c,
		 0x50,0x49,0x50,0x45,0x5c,0x4c,0x41,0x4e,0x4d,0x41,0x4e,0x00,0x68,0x00,0x57,0x72,
		 0x4c,0x65,0x68,0x44,0x7a,0x00,0x42,0x31,0x36,0x42,0x42,0x44,0x7a,0x00,0x01,0x00,
		 0x00,0x10,0x00,0x00,0x00,0x80,0x45,0x53,0x43,0x4f,0x4d,0x00,0x00,0xac,0x97,0x6d}, //trama20
		{0x00,0x02,0xb3,0x9c,0xdf,0x1b,0x00,0x02,0xb3,0x9c,0xae,0xba,0x00,0x04,0xf0,0xf1,
		 0x01,0x0a,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xfb,0x97,0x6d}, //trama21
		{0x00,0x02,0xb3,0x9c,0xae,0xba,0x00,0x02,0xb3,0x9c,0xdf,0x1b,0x00,0x04,0xf0,0xf1,
		 0x01,0x0a,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x4a,0x98,0x6d}, //trama22
		{0x00,0x02,0xb3,0x9c,0xae,0xba,0x00,0x02,0xb3,0x9c,0xdf,0x1b,0x00,0x12,0xf0,0xf0,
		 0x0a,0x0b,0x0e,0x00,0xff,0xef,0x14,0x00,0x00,0x00,0x28,0x00,0x00,0x00,0x7f,0x23,
		 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x99,0x98,0x6d}, //trama23
		{0x00,0x02,0xb3,0x9c,0xdf,0x1b,0x00,0x02,0xb3,0x9c,0xae,0xba,0x00,0x04,0xf0,0xf1,
		 0x01,0x0d,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x45,0x99,0x6d}, //trama24
		{0x03,0x00,0x00,0x00,0x00,0x01,0x00,0x04,0xac,0x44,0x4d,0x02,0x00,0x8b,0xf0,0xf0,
		 0x03,0x2c,0x00,0xff,0xef,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x42,0x34,0x20,
		 0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x1b,0x49,0x42,0x4d,
		 0x53,0x45,0x52,0x56,0x45,0x52,0x20,0x20,0x20,0x20,0x20,0x20,0x00,0xff,0x53,0x4d,
		 0x42,0x25,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x11,0x00,0x00,
		 0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xe8,0x03,0x00,0x00,0x00,0x00,
		 0x00,0x00,0x00,0x00,0x06,0x00,0x56,0x00,0x03,0x00,0x01,0x00,0x01,0x00,0x02,0x00,
		 0x17,0x00,0x5c,0x4d,0x41,0x49,0x4c,0x53,0x4c,0x4f,0x54,0x5c,0x42,0x52,0x4f,0x57,
		 0x53,0x45,0x00,0x09,0x04,0x33,0x17,0x00,0x00,0x00,0x9b,0x99,0x6d,0x86,0x99,0x98}, //trama25
		{0x00,0x02,0xb3,0x9c,0xae,0xba,0x00,0x02,0xb3,0x9c,0xdf,0x1b,0x00,0x35,0xf0,0xf0,
		 0x0c,0x0a,0x0e,0x00,0xff,0xef,0x16,0x04,0x00,0x00,0x00,0x00,0x28,0x00,0x7f,0x23,
		 0xff,0x53,0x4d,0x42,0x71,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,
		 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0xc0,0x00,0x00,0x00,0x00,0x01,0x50,
		 0x00,0x00,0x00,0x45,0xf1,0x99,0x6d,0x86,0x45,0x99,0x6d,0x86,0x1f,0x09,0x52,0x5b}, //trama26
		{0x00,0x02,0xb3,0x9c,0xdf,0x1b,0x00,0x02,0xb3,0x9c,0xae,0xba,0x00,0x35,0xf0,0xf0,
		 0x0a,0x0e,0x0e,0x00,0xff,0xef,0x16,0x0c,0x00,0x00,0x28,0x00,0x28,0x00,0x23,0x7f,
		 0xff,0x53,0x4d,0x42,0x71,0x00,0x00,0x00,0x00,0x80,0x01,0x00,0x00,0x00,0x00,0x00,
		 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0xc0,0x00,0x00,0x00,0x00,0x01,0x50,
		 0x00,0x00,0x00,0x00,0x40,0x9a,0x6d,0x86,0x9b,0x99,0x6d,0x86,0x20,0x09,0x75,0x5b}, //trama27
		{0x00,0x02,0xb3,0x9c,0xae,0xba,0x00,0x02,0xb3,0x9c,0xdf,0x1b,0x00,0x12,0xf0,0xf0,
		 0x0e,0x0d,0x0e,0x00,0xff,0xef,0x14,0x00,0x00,0x00,0x28,0x00,0x00,0x00,0x7f,0x23,
		 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x8f,0x9a,0x6d}, //trama28
		{0x00,0x02,0xb3,0x9c,0xdf,0x1b,0x00,0x02,0xb3,0x9c,0xae,0xba,0x00,0x04,0xf0,0xf1,
		 0x01,0x11,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xde,0x9a,0x6d}, //trama29
		{0x00,0x02,0xb3,0x9c,0xae,0xba,0x00,0x02,0xb3,0x9c,0xdf,0x1b,0x00,0x12,0xf0,0xf0,
		 0x10,0x0d,0x0e,0x00,0xff,0xef,0x18,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7f,0x23,
		 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x2d,0x9b,0x6d}, //trama30
		{0x00,0x02,0xb3,0x9c,0xdf,0x1b,0x00,0x02,0xb3,0x9c,0xae,0xba,0x00,0x04,0xf0,0xf1,
		 0x01,0x13,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7c,0x9b,0x6d}, //trama31
		{0x00,0x02,0xb3,0x9c,0xae,0xba,0x00,0x02,0xb3,0x9c,0xdf,0x1b,0x00,0x03,0xf0,0xf0,
		 0x53,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xcb,0x9b,0x6d}, //trama32
		{0x00,0x02,0xb3,0x9c,0xdf,0x1b,0x00,0x02,0xb3,0x9c,0xae,0xba,0x00,0x03,0xf0,0xf1,
		 0x73,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x77,0x9c,0x6d},
		 
/* Trama 33 */	{0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x23,0x8b,0x46,0xe9,0xad,0x08,0x06,0x00,0x04, 
		 0x08,0x00,0x06,0x04,0x00,0x01,0x00,0x23,0x8b,0x46,0xe9,0xad,0x94,0xcc,0x39,0xcb, 
		 0x00,0x00,0x00,0x00,0x00,0x00,0x94,0xcc,0x39,0xfe }, /*Trama a */

/* Trama 34 */	{0x00,0x23,0x8b,0x46,0xe9,0xad,0x00,0x1f,0x45,0x9d,0x1e,0xa2,0x08,0x06,0x00,0x01,
		 0x08,0x00,0x06,0x04,0x00,0x02,0x00,0x1f,0x45,0x9d,0x1e,0xa2,0x94,0xcc,0x39,0xfe,
		 0x00,0x23,0x8b,0x46,0xe9,0xad,0x94,0xcc,0x39,0xcb,0x00,0x00,0x00,0x00,0x00,0x00,
		 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 }, /* Trama b*/
		
/* Trama 35 */	{0x00,0x1f,0x45,0x9d,0x1e,0xa2,0x00,0x23,0x8b,0x46,0xe9,0xad,0x08,0x00,0x46,0x00,
		 0x80,0x42,0x04,0x55,0x34,0x11,0x80,0x11,0x6b,0xf0,0x94,0xcc,0x39,0xcb,0x94,0xcc, 
		 0x67,0x02,0xaa,0xbb,0xcc,0xdd,0x04,0x0c,0x00,0x35,0x00,0x2e,0x85,0x7c,0xe2,0x1a,
		 0x01,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x77,0x77,0x77,0x03,0x69,
		 0x73,0x63,0x05,0x65,0x73,0x63,0x6f,0x6d,0x03,0x69,0x70,0x6e,0x02,0x6d,0x78,0x00,
		 0x00,0x1c,0x00,0x01}, /* Trama c */

/* Trama 36 */	{0xff,0xff,0xff,0xff,0xff,0xff,0x12,0x12,0x12,0xaa,0xaa,0xaa,0x08,0x06,0x00,0x01,
		 0x08,0x00,0x06,0x04,0x00,0x01,0x12,0x12,0x12,0xaa,0xaa,0xaa,0xc0,0x94,0x01,0x02,
		 0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x02,0x03,0x04}, /* Trama d */

/* Trama 37 */	{0x12,0x12,0x12,0xaa,0xaa,0xaa,0x22,0x22,0x22,0x22,0x22,0x22,0x08,0x06,0x00,0x01,
		 0x08,0x00,0x06,0x04,0x00,0x02,0x22,0x22,0x22,0x22,0x22,0x22,0xc0,0x94,0x01,0xfe,
		 0x12,0x12,0x12,0xaa,0xaa,0xaa,0xc0,0x94,0x01,0x02}, /* Trama e */

/* Trama 38 */	{0xff,0xff,0xff,0xff,0xff,0xff,0x12,0x12,0x12,0x12,0x12,0x12,0x08,0x06,0x00,0x01,
		 0x08,0x00,0x06,0x04,0x00,0x01,0x12,0x12,0x12,0x12,0x12,0x12,0xc0,0x94,0x01,0x45,
		 0x00,0x00,0x00,0x00,0x00,0x00,0xc0,0x94,0x01,0x02}, /* Trama f */

/* Trama 39 */	{0x12,0x12,0x12,0x12,0x12,0x12,0x12,0x12,0x12,0xaa,0xaa,0xaa,0x08,0x06,0x00,0x01,
		 0x08,0x00,0x06,0x04,0x00,0x02,0x12,0x12,0x12,0xaa,0xaa,0xaa,0xc0,0x94,0x01,0x02,
		 0x12,0x12,0x12,0x12,0x12,0x12,0xc0,0x94,0x01,0x45}, /* Trama g */

/* Trama 40 */	{0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x23,/* .......# */
		0x8b, 0x46, 0xe9, 0xad, 0x08, 0x06, 0x00, 0x04, /* .F...... */
		0x08, 0x00, 0x06, 0x04, 0x00, 0x01, 0x00, 0x23, /* .......# */
		0x8b, 0x46, 0xe9, 0xad, 0x94, 0xcc, 0x39, 0xcb, /* .F....9. */
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x94, 0xcc, /* ........ */
		0x39, 0xfe },                                   /* 9. */

/* Trama 41 */	{0x00, 0x23, 0x8b, 0x46, 0xe9, 0xad, 0x00, 0x1f,/* .#.F.... */
		0x45, 0x9d, 0x1e, 0xa2, 0x08, 0x06, 0x00, 0x01, /* E....... */
		0x08, 0x00, 0x06, 0x04, 0x00, 0x02, 0x00, 0x1f, /* ........ */
		0x45, 0x9d, 0x1e, 0xa2, 0x94, 0xcc, 0x39, 0xfe, /* E.....9. */
		0x00, 0x23, 0x8b, 0x46, 0xe9, 0xad, 0x94, 0xcc, /* .#.F.... */
		0x39, 0xcb, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 9....... */
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* ........ */
		0x00, 0x00, 0x00, 0x00},                        /* .... */

/* Trama 42 */	{0x00, 0x1f, 0x45, 0x9d, 0x1e, 0xa2, 0x00, 0x23, /* ..E....# */
		0x8b, 0x46, 0xe9, 0xad, 0x08, 0x00, 0x46, 0x00, /* .F....F. */
		0x80, 0x42, 0x04, 0x55, 0x34, 0x11, 0x80, 0x11, /* .B.U4... */
		0x6b, 0xf0, 0x94, 0xcc, 0x39, 0xcb, 0x94, 0xcc, /* k...9... */
		0x67, 0x02, 0xaa, 0xbb, 0xcc, 0xdd, 0x04, 0x0c, /* g....... */
		0x00, 0x35, 0x00, 0x2e, 0x85, 0x7c, 0xe2, 0x1a, /* .5...|.. */
		0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, /* ........ */
		0x00, 0x00, 0x03, 0x77, 0x77, 0x77, 0x03, 0x69, /* ...www.i */
		0x73, 0x63, 0x05, 0x65, 0x73, 0x63, 0x6f, 0x6d, /* sc.escom */
		0x03, 0x69, 0x70, 0x6e, 0x02, 0x6d, 0x78, 0x00, /* .ipn.mx. */
		0x00, 0x1c, 0x00, 0x01},                          /* .... */

/* Trama 43 */	{0x00, 0x02, 0xb3, 0x9c, 0xdf, 0x1b, 0x00, 0x02, /* ........ */
		0xb3, 0x9c, 0xae, 0xba, 0x00, 0x04, 0xf0, 0xf1, /* ........ */
		0x09, 0x8d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* ........ */
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* ........ */
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* ........ */
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* ........ */
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* ........ */
		0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x9b, 0x6d },  /* .....|.m */

/* Trama 44 */	{0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x23, /* .......# */
		0x8b, 0x46, 0xe9, 0xad, 0x08, 0x06, 0x00, 0x10, /* .F...... */
		0x08, 0x00, 0x06, 0x04, 0x00, 0x03, 0x00, 0x23, /* .......# */
		0x8b, 0x46, 0xe9, 0xad, 0x94, 0xcc, 0x39, 0xcb, /* .F....9. */
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x94, 0xcc, /* ........ */
		0x3a, 0xe1},                                     /* :. */
{
0x00, 0x23, 0x8b, 0x46, 0xe9, 0xad, 0x00, 0x1f, /* .#.F.... */
0x45, 0x9d, 0x1e, 0xa2, 0x08, 0x06, 0x00, 0x10, /* E....... */
0x08, 0x00, 0x06, 0x04, 0x00, 0x04, 0x00, 0x1f, /* ........ */
0x45, 0x9d, 0x1e, 0xa2, 0x94, 0xcc, 0x3a, 0xe1, /* E.....:. */
0x00, 0x23, 0x8b, 0x46, 0xe9, 0xad, 0x94, 0xcc, /* .#.F.... */
0x39, 0xcb, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 9....... */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* ........ */
0x00, 0x00, 0x00, 0x00                          /* .... */
},
{
0x00, 0x23, 0x8b, 0x46, 0xe9, 0xad, 0x00, 0x1f, /* .#.F.... */
0x45, 0x9d, 0x1e, 0xa2, 0x08, 0x00, 0x45, 0x00, /* E.....E. */
0x00, 0x6f, 0x90, 0x30, 0x40, 0x00, 0xfb, 0x11, /* .o.0@... */
0x24, 0xe7, 0x94, 0xcc, 0x67, 0x02, 0x94, 0xcc, /* $...g... */
0x39, 0xcb, 0x00, 0x35, 0x04, 0x0c, 0x00, 0x5b, /* 9..5...[ */
0xe8, 0x60, 0xe2, 0x1a, 0x85, 0x80, 0x00, 0x01, /* .`...... */
0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x03, 0x77, /* .......w */
0x77, 0x77, 0x03, 0x69, 0x73, 0x63, 0x05, 0x65, /* ww.isc.e */
0x73, 0x63, 0x6f, 0x6d, 0x03, 0x69, 0x70, 0x6e, /* scom.ipn */
0x02, 0x6d, 0x78, 0x00, 0x00, 0x1c, 0x00, 0x01, /* .mx..... */
0xc0, 0x14, 0x00, 0x06, 0x00, 0x01, 0x00, 0x00, /* ........ */
0x0e, 0x10, 0x00, 0x21, 0x04, 0x64, 0x6e, 0x73, /* ...!.dns */
0x31, 0xc0, 0x1a, 0x03, 0x74, 0x69, 0x63, 0xc0, /* 1...tic. */
0x1a, 0x77, 0xec, 0xdf, 0x29, 0x00, 0x00, 0x2a, /* .w..)..* */
0x30, 0x00, 0x00, 0x0e, 0x10, 0x00, 0x12, 0x75, /* 0......u */
0x00, 0x00, 0x00, 0x2a, 0x30                    /* ...*0 */
},
{
0x00, 0x1f, 0x45, 0x9d, 0x1e, 0xa2, 0x00, 0x23, /* ..E....# */
0x8b, 0x46, 0xe9, 0xad, 0x08, 0x00, 0x45, 0x00, /* .F....E. */
0x00, 0x42, 0x04, 0x56, 0x00, 0x00, 0x80, 0x11, /* .B.V.... */
0x6b, 0xef, 0x94, 0xcc, 0x39, 0xcb, 0x94, 0xcc, /* k...9... */
0x67, 0x02, 0x04, 0x0c, 0x00, 0x35, 0x00, 0x2e, /* g....5.. */
0xff, 0x87, 0x68, 0x2a, 0x01, 0x00, 0x00, 0x01, /* ..h*.... */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x77, /* .......w */
0x77, 0x77, 0x03, 0x69, 0x73, 0x63, 0x05, 0x65, /* ww.isc.e */
0x73, 0x63, 0x6f, 0x6d, 0x03, 0x69, 0x70, 0x6e, /* scom.ipn */
0x02, 0x6d, 0x78, 0x00, 0x00, 0x01, 0x00, 0x01  /* .mx..... */
},
{
0x00, 0x1f, 0x45, 0x9d, 0x1e, 0xa2, 0x00, 0x23, /* ..E....# */
0x8b, 0x46, 0xe9, 0xad, 0x08, 0x00, 0x45, 0x00, /* .F....E. */
0x00, 0x3c, 0x04, 0x57, 0x00, 0x00, 0x80, 0x01, /* .<.W.... */
0x98, 0x25, 0x94, 0xcc, 0x39, 0xcb, 0x94, 0xcc, /* .%..9... */
0x3a, 0xe1, 0x08, 0x00, 0x49, 0x5c, 0x03, 0x00, /* :...I\.. */
0x01, 0x00, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, /* ..abcdef */
0x67, 0x68, 0x69, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e, /* ghijklmn */
0x6f, 0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, /* opqrstuv */
0x77, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, /* wabcdefg */
0x68, 0x69                                      /* hi */
},
{
0x00, 0x23, 0x8b, 0x46, 0xe9, 0xad, 0x00, 0x1f, /* .#.F.... */
0x45, 0x9d, 0x1e, 0xa2, 0x08, 0x00, 0x45, 0x00, /* E.....E. */
0x00, 0x3c, 0x01, 0xb5, 0x00, 0x00, 0x3f, 0x01, /* .<....?. */
0xdb, 0xc7, 0x94, 0xcc, 0x3a, 0xe1, 0x94, 0xcc, /* ....:... */
0x39, 0xcb, 0x00, 0x00, 0x51, 0x5c, 0x03, 0x00, /* 9...Q\.. */
0x01, 0x00, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, /* ..abcdef */
0x67, 0x68, 0x69, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e, /* ghijklmn */
0x6f, 0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, /* opqrstuv */
0x77, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, /* wabcdefg */
0x68, 0x69                                      /* hi */
},
{
0x00, 0x1f, 0x45, 0x9d, 0x1e, 0xa2, 0x00, 0x1c, /* ..E..... */
0xc0, 0x7b, 0x35, 0xa1, 0x08, 0x00, 0x48, 0x00, /* .{5...H. */
0x00, 0x48, 0x5c, 0x7d, 0x00, 0x00, 0x80, 0x01, /* .H\}.... */
0x6c, 0x88, 0x94, 0xcc, 0x39, 0xc3, 0x94, 0xcc, /* l...9... */
0x00, 0x49, 0x07, 0x0b, 0x04, 0x00, 0x00, 0x00, /* .I...... */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, /* ........ */
0x3b, 0x5c, 0x02, 0x00, 0x10, 0x00, 0x61, 0x62, /* ;\....ab */
0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6a, /* cdefghij */
0x6b, 0x6c, 0x6d, 0x6e, 0x6f, 0x70, 0x71, 0x72, /* klmnopqr */
0x73, 0x74, 0x75, 0x76, 0x77, 0x61, 0x62, 0x63, /* stuvwabc */
0x64, 0x65, 0x66, 0x67, 0x68, 0x69              /* defghi */
},
{
0x00, 0x23, 0x8b, 0x46, 0xe9, 0xad, 0x00, 0x1f, /* .#.F.... */
0x45, 0x9d, 0x1e, 0xa2, 0x80, 0x35, 0x00, 0x01, /* E....5.. */
0x08, 0x00, 0x06, 0x04, 0x00, 0x03, 0x00, 0x1f, /* ........ */
0x45, 0x9d, 0x1e, 0xa2, 0x94, 0xcc, 0x3a, 0xe1, /* E.....:. */
0x00, 0x23, 0x8b, 0x46, 0xe9, 0xad, 0x94, 0xcc, /* .#.F.... */
0x39, 0xcb, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 9....... */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* ........ */
0x00, 0x00, 0x00, 0x00, 0xd8, 0xee, 0xdf, 0xb0  /* ........ */
},
{
0x00, 0x02, 0xb3, 0x9c, 0xae, 0xba, 0x00, 0x02, /* ........ */
0xb3, 0x9c, 0xdf, 0x1b, 0x00, 0x03, 0xf0, 0xf0, /* ........ */
0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* ........ */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* ........ */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* ........ */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* ........ */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* ........ */
0x00, 0x00, 0x00, 0x00, 0x43, 0x05, 0x90, 0x6d  /* ....C..m */
},
{
0x02, 0xff, 0x53, 0xc3, 0xe9, 0xab, 0x00, 0xff, /* ..S..... */
0x66, 0x7f, 0xd4, 0x3c, 0x08, 0x00, 0x45, 0x00, /* f..<..E. */
0x00, 0x30, 0x2c, 0x00, 0x40, 0x00, 0x80, 0x06, /* .0,.@... */
0x4b, 0x74, 0xc0, 0xa8, 0x01, 0x02, 0xc0, 0xa8, /* Kt...... */
0x01, 0x01, 0x04, 0x03, 0x00, 0x15, 0x00, 0x3b, /* .......; */
0xcf, 0x44, 0x00, 0x00, 0x00, 0x00, 0x50, 0x20, /* .D....p  */
0x20, 0x00, 0x0c, 0x34, 0x00, 0x00, 0x02, 0x04, /*  ..4.... */
0x05, 0xb4, 0x01, 0x01, 0x04, 0x02              /* ...... */
},
{
0x00, 0xff, 0x66, 0x7f, 0xd4, 0x3c, 0x02, 0xff, /* ..f..<.. */
0x53, 0xc3, 0xe9, 0xab, 0x08, 0x00, 0x45, 0x00, /* S.....E. */
0x00, 0x30, 0x05, 0xc4, 0x40, 0x00, 0x80, 0x06, /* .0..@... */
0x71, 0xb0, 0xc0, 0xa8, 0x01, 0x01, 0xc0, 0xa8, /* q....... */
0x01, 0x02, 0x00, 0x15, 0x04, 0x03, 0x21, 0x5d, /* ......!] */
0x3a, 0x44, 0x00, 0x3b, 0xcf, 0x45, 0x70, 0x12, /* :D.;.Ep. */
0x44, 0x70, 0x8c, 0x11, 0x00, 0x00, 0x02, 0x04, /* Dp...... */
0x05, 0xb4, 0x01, 0x01, 0x04, 0x02              /* ...... */
},
{
0x00, 0x02, 0xb3, 0x9c, 0xae, 0xba, 0x00, 0x02, /* ........ */
0xb3, 0x9c, 0xdf, 0x1b, 0x00, 0x12, 0xf0, 0xf0, /* ........ */
0x0a, 0x0b, 0x0e, 0x00, 0xff, 0xef, 0x14, 0x00, /* ........ */
0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x7f, 0x23, /* ..(....# */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* ........ */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* ........ */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* ........ */
0x00, 0x00, 0x00, 0x00, 0x01, 0x99, 0x98, 0x6d  /* .......m */
}


};
   unsigned char i;
   for( i = 0; i < 56;i++)
   {
      printf("\n****** Analizando trama %d*******\n",i+1);
      analiza_trama(T[i]);
      printf("\n****** Fin de trama %d*******\n",i+1);
   } 
   /*
   unsigned char prueba[] = {0x45,0x00,0x80,0x42,0x04,0x55,0x11,0xcc, 0xff};
   hacer_checksum(&prueba[0],9);
   */
   return 0;
}

void 
analiza_trama(unsigned char trama[])
{
  printf("\n------ CABECERA ETHERNET ------\n");
  printf("MAC destino: %.2x:%.2x:%.2x:%.2x:%.2x:%.2x\n",trama[0],trama[1],
  trama[2],trama[3],trama[4],trama[5]);
  printf("MAC origen: %.2x:%.2x:%.2x:%.2x:%.2x:%.2x\n",trama[6],trama[7],
  trama[8],trama[9],trama[10],trama[11]);
  unsigned short int ToT = (trama[12]<<8) | (trama[13]);
  if(ToT <= 1500)
  {
    printf("Tipo LLC. Tamanio %d bytes\n",ToT);
    analiza_llc(trama);
  }else if(ToT == 2048){
    printf("Tipo IP.\n");
    analiza_ip(trama);
  }else if(ToT == 2054){ 
    printf("Tipo ARP.\n");
    analiza_arp(trama);
  }else
  {
    printf("Tipo otro.\n");
  }
 return;
}

void 
analiza_llc(unsigned char trama[])
{
  printf("------ CABECERA LLC ------\n");
  printf("SAP destino:%d\n",trama[14]);
  printf("SAP origen:%d\n",trama[15]);
  switch(trama[16] & 0x03)
  {
    case 0: 
    /* Trama de tipo I */
    printf("T-I, N(s):%d ,N(r):%d",trama[16]>>1,trama[17]>>1);
    if(trama[17]&0x01)
    {
      printf(",P/F:1,");
      if(trama[15]&0x01)
      {
        printf("Tipo F\n");
      }else
      {
        printf("Tipo P\n");
      }
    }
    break;
    case 1:
    /* Trama de tipo S */
    printf("T-S, %s , N(r):%d",S[(trama[16]>>2 & 0x03)],trama[17]>>1);
    if(trama[17]&0x01)
    {
      printf(",P/F:1,");
      if(trama[15]&0x01)
      {
        printf("Tipo F\n");
      }else
      {
        printf("Tipo P\n");
      }
    }
    break;
    case 2:
    /* Trama de tipo I */
    printf("T-I, N(s):%d ,N(r):%d",trama[16]>>1,trama[17]>>1);
    if(trama[17]&0x01)
    {
      printf(",P/F:1, ");
      if(trama[15]&0x01)
      {
        printf("Tipo F\n");
      }else
      {
        printf("Tipo P\n");
      }
    }
    break;
    case 3:
    /* Trama de tipo U */
    if(trama[16] & 0x10)
    {
      if(trama[15]&0x01)
      {
        printf("T-U Response:%s,P/F:1,Tipo F\n",MR[((trama[16]>>2)&0x03)|((trama[16]>>3)&0x1c)]); 
      }else
      {
        printf("T-U Command:%s\n",MC[((trama[16]>>2)&0x03)|((trama[16]>>3)&0x1c)]); 
      }  
    }
    break;
    default:
    printf("Tipo de trama no valido...\n");
    return;
    break;
  }
}

void 
analiza_arp(unsigned char T[])
{
   printf("------ CABECERA ARP------\n");
   printf("Tipo de direccion de hardware:");
   switch( (T[14]<<8) | T[15])
   {
    case 1:
    printf("Ethernet.\n");
    break;
    case 4:
    printf("Token Ring.\n");
    break;
    case 6:
    printf("IEEE 802 LAN.\n");
    break;
    case 15:
    printf("Frame Relay.\n");
    break;
    case 16:
    printf("ATM.\n");
    break;
   }
   printf("Tipo de direccion de protocolo:");
   if( ((T[16]<<8) | T[17]) == 2048 )
   {
     printf("IPv4.\n");
   }
   printf("Tamanio de direcciones de hardware:");
   if( T[18] == 6 )
   {
     printf("6 bytes. Ethernet/IEEE 802.\n");
   }
   printf("Tamanio de direcciones de protocolo:");
   if( T[19] == 4 )
   {
     printf("4 bytes. IPv4.\n");
   }
   printf("Tipo de Operacion:");
   switch( (T[20]<<8) | T[21] )
   {
     case 1:
     printf("Request.\n");
     break;
     case 2:
     printf("Reply.\n");
     break;
     case 3:
     printf("Inverse request.\n");
     break;
     case 4:
     printf("Inverse reply.\n");
     break;
     case 8:
     printf("Inverse request.\n");
     break;
     case 9:
     printf("Inverse reply.\n");
     break;
     default:
     printf("No valida.\n");
     break;
   }
   printf("Direccion hardware origen: %.2x:%.2x:%.2x:%.2x:%.2x:%.2x\n",
           T[22],T[23],T[24],T[25],T[26],T[27]);
   printf("Direccion de protocolo origen: %d.%d.%d.%d\n",
           T[28],T[29],T[30],T[31]);
   printf("Direccion hardware destino: %.2x:%.2x:%.2x:%.2x:%.2x:%.2x\n",
           T[32],T[33],T[34],T[35],T[36],T[37]);
   printf("Direccion de protocolo destino: %d.%d.%d.%d\n",
           T[38],T[39],T[40],T[41]);

}

void 
analiza_ip(unsigned char T[])
{
   printf("------ CABECERA IP------\n");
   if( (T[14]>>4) == 4 )
   {
      printf("Version:IPv4.\n");
   }
   unsigned char ihl = (T[14] & 0x0F);
   printf("Tamanio de la cabecera(IHL):%d palabras.\n",ihl);
   ihl = ihl * 4;
   if( T[15] & 0x10 )
   {
     printf("Bandera D (Minimize delay) activada.\n");
   }else if(T[15] & 0x08){
     printf("Bandera T (Maximize throughout) activada.\n");
   }else if(T[15] & 0x04){
     printf("Bandera R (Maximize reliability) activada.\n");
   }else if(T[15] & 0x02)
   {
     printf("Bandera C (Minimize cost) activada.\n");
   }
   printf("Longitud total:%d.\n", (T[16]<<8|T[17]) );
   printf("Identificacion:%d.\n", (T[18]<<8|T[19]) );
   printf("Desplazamiento de fragmentos:\n");
   if(T[20]&0x20)
   {
    printf("Bandera M(More fragments) activada.\n");
    printf("Posicion del fragmento en el datagrama original:");
    short int posicion = ((T[20] & 0x1f) << 8) | ( T[21]);
    printf("%d bytes desplazado.\n", (posicion*8));
   }else if(T[20]&0x40)
   {
    printf("Bandera D (Do not fragment) activada.\n");
   }
   printf("Tiempo de vida:%d saltos.\n",T[22]);
   printf("Protocolo:");
   switch(T[23])
   {
      case 1:
      printf("ICMP.\n");
      break;
      case 6:
      printf("TCP.\n");
      break;
      case 17:
      printf("UDP.\n");
      break;
      default:
      printf("Otro.\n");
      break;
   }
   printf("Suma de comprobacion:%d\n",((T[24]<<8) | T[25]));
   printf("Direccion origen: %d.%d.%d.%d\n",T[26],T[27],T[28],T[29]);
   printf("Direccion destino: %d.%d.%d.%d\n",T[30],T[31],T[32],T[33]);
   if(ihl > 20)
   {
      printf("Opciones:");
      switch(T[34])
      {
         case 0:
         printf("End of option.\n");
         break;
         case 1:
         printf("No operation (pad).\n");
         break;
         case 7:
         printf("Record route.\n");
         break;
         case 68:
         printf("Timestamp.\n");
         break;
         case 131:
         printf("Loose source route.\n");
         break;
         case 137:
         printf("Strict source route.\n");
         break;
         default:
         printf("Valor:%d\n",T[34]);
         printf("Undefined.\n");
         break;
      }
   }
   printf("Debe terminar en T[%d]\n",13+ihl);
   hacer_checksum(&T[14],ihl);
   switch(T[23])
   {
      case 1:
      analiza_icmp(T,ihl);
      break;
      case 6:
      analiza_tcp(T,ihl);
      break;
      case 17:
      analiza_udp(T,ihl);
      break;
   }
  
}

void 
hacer_checksum(unsigned char T[],unsigned char tamanio)
{
  printf("---- Realizando la suma de comprobacion ----\n");
  unsigned int acumulador = 0;
  unsigned char i;
  for(i = 0; i < (tamanio-1); i += 2)
  {
    printf("Tomando posiciones del arreglo T[%d]=%x y T[%d]=%x\n",i,T[i]<<8,i+1,T[i+1]);
    acumulador += (T[i]<<8) + T[i+1];
    printf("La suma ahora tiene:%x\n",acumulador);
  }
  if(tamanio & 0x01) /* Si es impar sumar el faltante */
  {
    acumulador += (T[i]<<8);
  }
  unsigned short int suma = (acumulador >> 16) + (acumulador & 0xffff);
  printf("La suma da:%x\n",suma);
  suma = ~suma;
  printf("La comprobacion arrojo:%x\n",suma);
  if(!suma)
  {
    printf("Todo bien =)\n\n");
  }else
  {
    printf("Por corregir =(\n\n");
  }
     
}

void 
analiza_icmp(unsigned char T[], unsigned char ihl)
{
 printf("------ CABECERA ICMP ------\n");
 printf("Iniciando en la posicion T[%d]=%x\n",14+ihl,T[14+ihl]); 
 printf("Tipo:%d.\n",T[14+ihl]); 
 printf("Codigo:%d.\n",T[15+ihl]);
 printf("Suma de comprobacion:%d.\n",(T[16+ihl]<<8|T[17+ihl]));
 printf("Otra informacion:%d.\n",(T[18+ihl]<<24|T[19+ihl]<<16|T[20+ihl]<<8|T[21+ihl]));
 /* hacer_checksum(&T[14+ihl],8); */
}

void
analiza_tcp(unsigned char T[], unsigned char ihl)
{
 printf("------ CABECERA TCP ------\n");
 printf("Iniciando en la posicion T[%d]=%x\n",14+ihl,T[14+ihl]); 
 printf("Puerto origen:%d. ",(T[14+ihl]<<8|T[15+ihl])); 
 puertos_tcp((T[14+ihl]<<8 | T[15+ihl]));
 printf("Puerto destino:%d. ",(T[16+ihl]<<8|T[17+ihl])); 
 puertos_tcp((T[16+ihl]<<8 | T[17+ihl]));
 printf("Numero de secuencia:%d\n",(T[18+ihl]<<24|T[19+ihl]<<16|T[20+ihl]<<8|T[21+ihl]));
 printf("Numero de acuse:%d\n",(T[22+ihl]<<24|T[23+ihl]<<16|T[24+ihl]<<8|T[25+ihl]));
 unsigned char offset = T[26+ihl]>>4;
 printf("Offset:%d palabras.\n",offset);
 offset = offset*4;
 printf("Banderas:%d.\n",T[27+ihl]);
 printf("Ventana:%d.\n",(T[28+ihl]<<8|T[29+ihl]));
 printf("Suma de comprobacion:%d\n",(T[30+ihl]<<8|T[31+ihl]));
 printf("Apuntador urgente:%d\n",(T[32+ihl]<<8|T[33+ihl]));
 printf("Termina en la posicion T[%d]=%x\n",33+ihl,T[33+ihl]);
 printf("Debe terminar en T[%d]\n",13+offset+ihl);
 /* hacer_checksum(&T[14+ihl],offset); */
}

void 
puertos_tcp(unsigned short int puerto)
{
  switch(puerto)
  {
    case 7:
    printf("Echo.\n");
    break;
    case 19:
    printf("Chargen.\n");
    break;
    case 20:
    printf("Ftp-data.\n");
    break;
    case 21:
    printf("Ftp-control.\n");
    break;
    case 22:
    printf("SSH.\n");
    break;
    case 23:
    printf("Telnet.\n");
    break;
    case 25:
    printf("Smtp.\n");
    break;
    case 53:
    printf("Domain.\n");
    break;
    case 79:
    printf("Finger.\n");
    break;
    case 80:
    printf("Http.\n");
    break;
    case 110:
    printf("pop3.\n");
    break;
    case 111:
    printf("sunrpc.\n");
    break;
    case 119:
    printf("nntp.\n");
    break;
    case 139:
    printf("netbios-ssn.\n");
    break;
    case 143:
    printf("imap.\n");
    break;
    case 179:
    printf("bgp.\n");
    break;
    case 389:
    printf("ldap.\n");
    break;
    case 443:
    printf("https(ssl).\n");
    break;
    case 445:
    printf("microsoft-ds.\n");
    break;
    case 1080:
    printf("Socks.\n");
    break;
    default:
    printf("\n");
    break;
  }

}

void
analiza_udp(unsigned char T[], unsigned char ihl)
{
 printf("------ CABECERA UDP ------\n");
 printf("Iniciando en la posicion T[%d]\n",14+ihl); 
 printf("Puerto origen:%d. ",(T[14+ihl]<<8|T[15+ihl]));
 puertos_udp((T[14+ihl]<<8|T[15+ihl]));
 printf("Puerto destino:%d. ",(T[16+ihl]<<8|T[17+ihl])); 
 puertos_udp((T[16+ihl]<<8|T[17+ihl]));
 unsigned short int longitud = (T[18+ihl]<<8) | T[19+ihl];
 printf("Longitud:%d.\n", longitud); 
 printf("Suma de comprobacion:%d.\n",(T[20+ihl]<<8|T[21+ihl])); 
 /* hacer_checksum(&T[14+ihl], longitud); */
}


void 
puertos_udp(unsigned short int puerto)
{
  switch(puerto)
  {
    case 7:
    printf("Echo.\n");
    break;
    case 19:
    printf("Chargen.\n");
    break;
    case 37:
    printf("Time.\n");
    break;
    case 53:
    printf("Domain.\n");
    break;
    case 67:
    printf("Bootps (DHCP)\n");
    break;
    case 68:
    printf("Bootpc (DHCP).\n");
    break;
    case 69:
    printf("Tftp.\n");
    break;
    case 137:
    printf("Netbios-ns.\n");
    break;
    case 138:
    printf("Netbios-dgm.\n");
    break;
    case 161:
    printf("Snmp.\n");
    break;
    case 162:
    printf("Snmp-trap.\n");
    break;
    case 500:
    printf("Isakmp.\n");
    break;
    case 514:
    printf("Syslog.\n");
    break;
    case 520:
    printf("Rip.\n");
    break;
    case 33434:
    printf("Traceroute.\n");
    break;
    default:
    printf("\n");
    break;
  }
}

