/* @project 
 * 
 * License to access, copy or distribute this file.
 * This file or any portions of it, is Copyright (C) 2012, Radu Motisan ,  http://www.pocketmagic.net . All rights reserved.
 * @author Radu Motisan, radu.motisan@gmail.com
 * 
 * This file is protected by copyright law and international treaties. Unauthorized access, reproduction 
 * or distribution of this file or any portions of it may result in severe civil and criminal penalties.
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * 
 * @purpose Eth interface for Atmega microcontrollers
 * http://www.pocketmagic.net/?p=2866
 */

/*
 * CS can be configured in hw_enc28j60.h
 * Configure mymac and myip below
 */

#include <avr/io.h>
#include <stdlib.h>
#include <string.h>
#include "timeout.h" // defines F_CPU
#include <avr/eeprom.h>

#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <util/delay.h>
// ethernet interf
#include "net/ip_arp_udp_tcp.h"
#include "net/enc28j60.h"
#include "net/net.h"

// sensors
#include "sensors/ds1820.h"
#include "sensors/dht11.h"

#include "led.h"

// HD44780 LCD Class

// enc28j60 Ethernet Class

// please modify the following two lines. mac and ip have to be unique
// in your local area network. You can not have the same numbers in
// two devices:

static uint8_t mymac_ee[6] EEMEM;
static uint8_t myip_ee[4] EEMEM;
static uint8_t myipext_ee[4] EEMEM;

//static uint8_t temp;
//static uint8_t temp_ee  EEMEM;

static uint8_t g_aucMyMac[6] = { 0x34, 0x35, 0x36, 0x37, 0x38, 0x39 };
static uint8_t g_aucMyIp[4] = { 192, 168, 0, 109 };
static uint8_t g_aucMyExtIp[4] = { 87, 105, 8, 91 }; //87.105.8.91
// listen port for tcp/www (max range 1-254)

// Auxiliary macros to turn numeric definition into string
#define STRINGIZE_(x)   #x
#define STRINGIZE(x)    STRINGIZE_(x)

#define MYWWWPORT       80
#define MYWWWPORT_STR   STRINGIZE(MYWWWPORT)
// working buffer
//#define BUFFER_SIZE 500
#define BUFFER_SIZE 800
static uint8_t buf[BUFFER_SIZE + 1];
// servers counters
static int nPingCount = 0, nAccessCount = 0;
// Objects

// http://192.168.0.109:1235/?par=0&ip1=192&ip2=168&ip3=0&ip4=108
// http://192.168.0.109:1235/?par=0&mac1=52&mac2=53&mac3=54&mac4=55&mac5=56&mac6=57

int getParameter(char *pcUrlData, char *pcParameter, char *pcOutput, int iOutputSize);
void storeIpToEeprom(uint8_t ip[4]);
void readIpFromEeprom(uint8_t ip[4]);
void storeIpExtToEeprom(uint8_t ip[4]);
void readIpExtFromEeprom(uint8_t ip[4]);
void storeMacToEeprom(uint8_t mac[6]);
void readMacFromEeprom(uint8_t mac[6]);
void updateIpIfNeeded(uint8_t* paucResponse);
void updateIpExtIfNeeded(uint8_t* paucResponse);
void updateMacIfNeeded(uint8_t* paucResponse);

void PingCallback(uint8_t *ip) {
    nPingCount++;
}

/*
 * Main entry point
 */
int main(void) {

    ledOn();

    DDRD &= ~_BV(3); // S1
    DDRD &= ~_BV(4); // S2

    // read values from eeprom
    //storeIpToEeprom(g_aucMyIp);
    readIpFromEeprom(g_aucMyIp);
    readIpExtFromEeprom(g_aucMyExtIp);
    readMacFromEeprom(g_aucMyMac);

    //=====setup eth interface
//    uint16_t plen = 0;
    uint16_t dat_p = 0;
    //initialize enc28j60
    enc28j60Init(g_aucMyMac);

    _delay_ms(100);

    // Magjack leds configuration, see enc28j60 datasheet, page 11 
    // LEDB=yellow LEDA=green
    // 0x476 is PHLCON LEDA=links status, LEDB=receive/transmit
    // enc28j60PhyWrite(PHLCON,0b0000 0100 0111 01 10);
    enc28j60PhyWrite(PHLCON, 0x476);

    _delay_ms(100);

    //init the ethernet/ip layer:

    init_udp_or_www_server(g_aucMyMac, g_aucMyIp);
    www_server_port(MYWWWPORT);
    register_ping_rec_callback(PingCallback);

    while (1) {

        // handle ping and wait for a tcp packet:
        dat_p = packetloop_arp_icmp_tcp(buf, enc28j60PacketReceive(BUFFER_SIZE, buf));

        // dat_p will be unequal to zero if there is a valid http get
        if (dat_p == 0) {
            // do nothing
            continue;
        }
        char szWebText[500] = { 0 };

        // tcp port 80 begin
//        if (strncmp("GET ", (char *) &(buf[dat_p]), strlen("GET ")) != 0) {
//            dat_p = fill_tcp_data_p(buf, 0, PSTR("HTTP/1.0 200 OK\r\nContent-Type: text/html\r\nPragma: no-cache\r\n\r\n")); // HTTP header
//            dat_p = fill_tcp_data_p(buf, dat_p, PSTR("<h1>200 OK</h1>"));
//            goto SENDTCP;
//        }
        if (strncmp("/ ", (char *) &(buf[dat_p + 4]), 2) == 0) {
            nAccessCount++;

            // HTTP header
            dat_p = fill_tcp_data_p(buf, 0, PSTR("HTTP/1.0 200 OK\r\nContent-Type: text/html\r\nPragma: no-cache\r\n\r\n"));
            // webcontent
            sprintf(szWebText,
                    "<html><body><b>Arduino UNO Webserver / ENC28J60</b><br><br>Server stats:<br>Acc:%d Png:%d<br>%d:%d:%d:%d<br>%#02x:%#02x:%#02x:%#02x:%#02x:%#02x<br>",
                    nAccessCount, nPingCount, g_aucMyIp[0], g_aucMyIp[1], g_aucMyIp[2], g_aucMyIp[3],
                    g_aucMyMac[0], g_aucMyMac[1], g_aucMyMac[2], g_aucMyMac[3], g_aucMyMac[4], g_aucMyMac[5]);
            dat_p = fill_tcp_data(buf, dat_p, szWebText);
            dat_p = fill_tcp_data_p(buf, dat_p, PSTR("<script type=\"text/javascript\">function f(p){var x=null;x=new XMLHttpRequest();x.open(\"GET\",\"http://"));
            sprintf(szWebText,"%d.%d.%d.%d",g_aucMyExtIp[0],g_aucMyExtIp[1],g_aucMyExtIp[2],g_aucMyExtIp[3]);
            dat_p = fill_tcp_data(buf, dat_p, szWebText);
            dat_p = fill_tcp_data_p(buf, dat_p, PSTR(":"MYWWWPORT_STR"/?par=\"+p,true);x.send(null);}</script><button onclick=\"f(1)\">ON</button><button onclick=\"f(0)\">OFF</button>"));
            dat_p = fill_tcp_data_p(buf, dat_p, PSTR("<br/>Tomasz Jokiel</body></html>"));
            //
            goto SENDTCP;
        }
        if (strncmp("GET /config1 ", (char *) &(buf[dat_p]), strlen("GET /config1 ")) == 0) {
            readIpFromEeprom(g_aucMyIp);

            dat_p = fill_tcp_data_p(buf, 0, PSTR("HTTP/1.0 200 OK\r\nContent-Type: text/html\r\nPragma: no-cache\r\n\r\n")); // HTTP header
            dat_p = fill_tcp_data_p(buf, dat_p, PSTR("<form method=post action=\"http://"));
            sprintf(szWebText, "%d.%d.%d.%d",g_aucMyIp[0],g_aucMyIp[1],g_aucMyIp[2],g_aucMyIp[3]);
            dat_p = fill_tcp_data(buf, dat_p, szWebText);
            dat_p = fill_tcp_data_p(buf, dat_p, PSTR("/config\">IP int.<input type=text name=ip1 maxlength=3 value="));
            sprintf(szWebText, "%d",g_aucMyIp[0]);
            dat_p = fill_tcp_data(buf, dat_p, szWebText);
            dat_p = fill_tcp_data_p(buf, dat_p, PSTR(" />.<input type=text name=ip2 maxlength=3 value="));
            sprintf(szWebText, "%d",g_aucMyIp[1]);
            dat_p = fill_tcp_data(buf, dat_p, szWebText);
            dat_p = fill_tcp_data_p(buf, dat_p, PSTR(" />.<input type=text name=ip3 maxlength=3 value="));
            sprintf(szWebText, "%d",g_aucMyIp[2]);
            dat_p = fill_tcp_data(buf, dat_p, szWebText);
            dat_p = fill_tcp_data_p(buf, dat_p, PSTR(" />.<input type=text name=ip4 maxlength=3 value="));
            sprintf(szWebText, "%d",g_aucMyIp[3]);
            dat_p = fill_tcp_data(buf, dat_p, szWebText);
            dat_p = fill_tcp_data_p(buf, dat_p, PSTR(" /><br>"));
            dat_p = fill_tcp_data_p(buf, dat_p, PSTR("port<input type=text name=port maxlength=5 value="));
            sprintf(szWebText, "%d",MYWWWPORT);
            dat_p = fill_tcp_data(buf, dat_p, szWebText);
            dat_p = fill_tcp_data_p(buf, dat_p, PSTR(" /><br><input type=submit value=Update></button></form>"));

            goto SENDTCP;

        }
        if (strncmp("GET /config2 ", (char *) &(buf[dat_p]), strlen("GET /config2 ")) == 0) {
            readIpExtFromEeprom(g_aucMyExtIp);

            dat_p = fill_tcp_data_p(buf, 0, PSTR("HTTP/1.0 200 OK\r\nContent-Type: text/html\r\nPragma: no-cache\r\n\r\n")); // HTTP header
            dat_p = fill_tcp_data_p(buf, dat_p, PSTR("<form method=post action=\"http://"));
            sprintf(szWebText, "%d.%d.%d.%d",g_aucMyIp[0],g_aucMyIp[1],g_aucMyIp[2],g_aucMyIp[3]);
            dat_p = fill_tcp_data(buf, dat_p, szWebText);
            dat_p = fill_tcp_data_p(buf, dat_p, PSTR("/config\">IP ext.<input type=text name=ipe1 maxlength=3 value="));
            sprintf(szWebText, "%d",g_aucMyExtIp[0]);
            dat_p = fill_tcp_data(buf, dat_p, szWebText);
            dat_p = fill_tcp_data_p(buf, dat_p, PSTR(" />.<input type=text name=ipe2 maxlength=3 value="));
            sprintf(szWebText, "%d",g_aucMyExtIp[1]);
            dat_p = fill_tcp_data(buf, dat_p, szWebText);
            dat_p = fill_tcp_data_p(buf, dat_p, PSTR(" />.<input type=text name=ipe3 maxlength=3 value="));
            sprintf(szWebText, "%d",g_aucMyExtIp[2]);
            dat_p = fill_tcp_data(buf, dat_p, szWebText);
            dat_p = fill_tcp_data_p(buf, dat_p, PSTR(" />.<input type=text name=ipe4 maxlength=3 value="));
            sprintf(szWebText, "%d",g_aucMyExtIp[3]);
            dat_p = fill_tcp_data(buf, dat_p, szWebText);
            dat_p = fill_tcp_data_p(buf, dat_p, PSTR(" /><br><input type=submit value=Update></button></form>"));

            goto SENDTCP;
        }
        if (strncmp("GET /config3 ", (char *) &(buf[dat_p]), strlen("GET /config3 ")) == 0) {
            readMacFromEeprom(g_aucMyMac);

            dat_p = fill_tcp_data_p(buf, 0, PSTR("HTTP/1.0 200 OK\r\nContent-Type: text/html\r\nPragma: no-cache\r\n\r\n")); // HTTP header
            dat_p = fill_tcp_data_p(buf, dat_p, PSTR("<form method=post action=\"http://"));
            sprintf(szWebText, "%d.%d.%d.%d",g_aucMyIp[0],g_aucMyIp[1],g_aucMyIp[2],g_aucMyIp[3]);
            dat_p = fill_tcp_data(buf, dat_p, szWebText);
            dat_p = fill_tcp_data_p(buf, dat_p, PSTR("/config\">MAC<input type=text name=mac1 maxlength=2 value="));
            sprintf(szWebText, "%02x",g_aucMyMac[0]);
            dat_p = fill_tcp_data(buf, dat_p, szWebText);
            dat_p = fill_tcp_data_p(buf, dat_p, PSTR(" />.<input type=text name=mac2 maxlength=2 value="));
            sprintf(szWebText, "%02x",g_aucMyMac[1]);
            dat_p = fill_tcp_data(buf, dat_p, szWebText);
            dat_p = fill_tcp_data_p(buf, dat_p, PSTR(" />.<input type=text name=mac3 maxlength=2 value="));
            sprintf(szWebText, "%02x",g_aucMyMac[2]);
            dat_p = fill_tcp_data(buf, dat_p, szWebText);
            dat_p = fill_tcp_data_p(buf, dat_p, PSTR(" />.<input type=text name=mac4 maxlength=2 value="));
            sprintf(szWebText, "%02x",g_aucMyMac[3]);
            dat_p = fill_tcp_data(buf, dat_p, szWebText);
            dat_p = fill_tcp_data_p(buf, dat_p, PSTR(" />.<input type=text name=mac5 maxlength=2 value="));
            sprintf(szWebText, "%02x",g_aucMyMac[4]);
            dat_p = fill_tcp_data(buf, dat_p, szWebText);
            dat_p = fill_tcp_data_p(buf, dat_p, PSTR(" />.<input type=text name=mac6 maxlength=2 value="));
            sprintf(szWebText, "%02x",g_aucMyMac[5]);
            dat_p = fill_tcp_data(buf, dat_p, szWebText);
            dat_p = fill_tcp_data_p(buf, dat_p, PSTR(" /><br><input type=submit value=Update></button></form>"));

            goto SENDTCP;
        }
        if (strncmp("POST /config ", (char *) &(buf[dat_p]), strlen("POST /config ")) == 0) {
            char *szURLData = (char *) &(buf[dat_p]);

            updateIpIfNeeded((uint8_t*) szURLData);
            updateIpExtIfNeeded((uint8_t*) szURLData);
            updateMacIfNeeded((uint8_t*) szURLData);

            dat_p = fill_tcp_data_p(buf, 0, PSTR("HTTP/1.0 200 OK\r\nContent-Type: text/html\r\nPragma: no-cache\r\n\r\n")); // HTTP header
            dat_p = fill_tcp_data_p(buf, dat_p, PSTR("STORED"));

            readIpFromEeprom(g_aucMyIp);
            readIpExtFromEeprom(g_aucMyExtIp);
            readMacFromEeprom(g_aucMyMac);

            goto SENDTCP;
        }
        if (strncmp("GET /?", (char *) &(buf[dat_p]), strlen("GET /?")) == 0) { // Request with parameter, i.e. http://192.168.0.109/?par=5
            /*

             GET /?par=20 HTTP/1.1
             Host: 192.168.0.109
             Connection<b>Arduino UNO Webserver / ENC28J60</b><br><br>Server stats:<br>Acc:0 Png:0<br>parameter=20<br/>Tomasz Jokiel

             */
            nAccessCount++;

            // check for parameters. Test by enter: http://192.168.0.109/?par=5
            char *szURLData = (char *) &(buf[dat_p]);
            char szParam1[20] = { 0 };

            int parExist = getParameter(szURLData, "par=", szParam1, 20);

            updateIpIfNeeded((uint8_t*) szURLData);
            updateMacIfNeeded((uint8_t*) szURLData);

            dat_p = fill_tcp_data_p(buf, 0, PSTR("HTTP/1.0 200 OK\r\nContent-Type: text/html\r\nPragma: no-cache\r\n\r\n")); // HTTP header
            if (parExist) {

                sprintf(szWebText,
                        "<b>Arduino UNO Webserver / ENC28J60</b><br><br>Server stats:<br>Acc:%d Png:%d<br>parameter=%s<br>%d:%d:%d:%d<br/>",
                        nAccessCount, nPingCount, szParam1, g_aucMyIp[0], g_aucMyIp[1], g_aucMyIp[2], g_aucMyIp[3]);
                dat_p = fill_tcp_data(buf, dat_p, szWebText);
                dat_p = fill_tcp_data_p(buf, dat_p, PSTR("<script type=\"text/javascript\">function f(p){var x=null;x=new XMLHttpRequest();x.open(\"GET\",\"http://"));
                sprintf(szWebText,"%d.%d.%d.%d",g_aucMyExtIp[0],g_aucMyExtIp[1],g_aucMyExtIp[2],g_aucMyExtIp[3]);
                dat_p = fill_tcp_data_p(buf, dat_p, PSTR(":"MYWWWPORT_STR"/?par=\"+p,true);x.send(null);}</script><button onclick=\"f(1)\">ON</button><button onclick=\"f(0)\">OFF</button>"));
                dat_p = fill_tcp_data_p(buf, dat_p, PSTR("<br/>Tomasz Jokiel</body></html>"));

                if (atoi(szParam1)) {
                    ledOn();
                } else {
                    ledOff();
                }
            } else {
                // webcontent
                sprintf(szWebText, "<b>Arduino UNO Webserver / ENC28J60</b><br><br>Server stats:<br>Acc:%d Png:%d<br>Unknown parameter<br/>", nAccessCount, nPingCount);
                dat_p = fill_tcp_data(buf, dat_p, szWebText);
                dat_p = fill_tcp_data_p(buf, dat_p, PSTR("<script type=\"text/javascript\">function f(p){var x=null;x=new XMLHttpRequest();x.open(\"GET\",\"http://"));
                sprintf(szWebText,"%d.%d.%d.%d",g_aucMyExtIp[0],g_aucMyExtIp[1],g_aucMyExtIp[2],g_aucMyExtIp[3]);
                dat_p = fill_tcp_data(buf, dat_p, szWebText);
                dat_p = fill_tcp_data_p(buf, dat_p, PSTR(":"MYWWWPORT_STR"/?par=\"+p,true);x.send(null);}</script><button onclick=\"f(1)\">ON</button><button onclick=\"f(0)\">OFF</button>"));
                dat_p = fill_tcp_data_p(buf, dat_p, PSTR("<br/>Tomasz Jokiel</body></html>"));
            }
            //
            goto SENDTCP;
        }

        // all other URLs:
        //dat_p = fill_tcp_data_p(buf, 0, PSTR("HTTP/1.0 401 Unauthorized\r\nContent-Type: text/html\r\n\r\n<h1>401 Unauthorized</h1>"));

        SENDTCP: www_server_reply(buf, dat_p); // send web page data

    }

    return (0);
}

/*
 * Helper function to check a string for a given parameter
 * @param pcUrlData     pointer to data to parse
 * @param pcParameter   pointer to string of parameter
 * @param pcOutput      pointer to output data buffer (parameter value)
 * @param iOutputSize   size of output data buffer
 * @return number different than zero if parameter was found, zero otherwise
 */
int getParameter(char *pcUrlData, char *pcParameter, char *pcOutput, int iOutputSize) {
    // check for valid input parameters
    if (!pcUrlData || !pcParameter || !pcOutput || !iOutputSize) {
        return 0;
    }
    // clear output
    memset(pcOutput, 0, iOutputSize);

    char *occ = strstr(pcUrlData, pcParameter);

    if (occ) {
        occ += strlen(pcParameter); //skip the parameter itself
//        if(*occ == ' '){
//            // parameter hasn't value but is present
//            return 1;
//        }
        int i = 0;
        while (*occ && *occ != ' ' && *occ != '&' && i < iOutputSize) {
            pcOutput[i++] = *(occ++);
        }
        return i;
    } else {
        // given parameter not found
        return 0;
    }
}

/**
 * Store 4 byte array of IP
 */
void storeIpToEeprom(uint8_t ip[4]) {
    eeprom_write_block(ip, myip_ee, sizeof(myip_ee));
    eeprom_busy_wait();
}

/**
 * Return 4 byte array of IP and put it to "ip"
 */
void readIpFromEeprom(uint8_t ip[4]) {
    eeprom_read_block(ip, myip_ee, sizeof(myip_ee));
    eeprom_busy_wait();
}

/**
 * Store 4 byte array of external IP
 */
void storeIpExtToEeprom(uint8_t ip[4]) {
    eeprom_write_block(ip, myipext_ee, sizeof(myipext_ee));
    eeprom_busy_wait();
}

/**
 * Return 4 byte array of external IP and put it to "ip"
 */
void readIpExtFromEeprom(uint8_t ip[4]) {
    eeprom_read_block(ip, myipext_ee, sizeof(myipext_ee));
    eeprom_busy_wait();
}

/**
 * Store 6 byte array of MAC
 */
void storeMacToEeprom(uint8_t mac[6]) {
    eeprom_write_block(mac, mymac_ee, sizeof(mymac_ee));
    eeprom_busy_wait();
}

/**
 * Return 6 byte array of MAC and put it to "mac"
 */
void readMacFromEeprom(uint8_t mac[6]) {
    eeprom_read_block(mac, mymac_ee, sizeof(mymac_ee));
    eeprom_busy_wait();
}

/**
 * Check for IP parameters to update and update if some - can update partially
 */
void updateIpIfNeeded(uint8_t* paucResponse) {
    uint8_t acIpBuffer[4] = { 0 };
    char acBuffer[] = "255";
    char acParameter[] = "ip1=";

    memcpy(acIpBuffer, g_aucMyIp, sizeof(acIpBuffer));

    for (uint8_t i = 0; i < 4; i++) {
        sprintf(acParameter, "ip%d=", i + 1);
        int pos = getParameter((char*) paucResponse, acParameter, acBuffer,
                sizeof(acBuffer));
        if (pos) {
            acIpBuffer[i] = atoi(acBuffer);
        }
    }

    storeIpToEeprom(acIpBuffer);
}

/**
 * Check for external IP parameters to update and update if some - can update partially
 */
void updateIpExtIfNeeded(uint8_t* paucResponse) {
    uint8_t acIpBuffer[4] = { 0 };
    char acBuffer[] = "255";
    char acParameter[] = "ipe1=";

    memcpy(acIpBuffer, g_aucMyExtIp, sizeof(acIpBuffer));

    for (uint8_t i = 0; i < 4; i++) {
        sprintf(acParameter, "ipe%d=", i + 1);
        int pos = getParameter((char*) paucResponse, acParameter, acBuffer,
                sizeof(acBuffer));
        if (pos) {
            acIpBuffer[i] = atoi(acBuffer);
        }
    }

    storeIpExtToEeprom(acIpBuffer);
}

/**
 * Check for MAC parameters to update and update if some - can update partially
 */
void updateMacIfNeeded(uint8_t* paucResponse) {
    uint8_t acMacBuffer[6] = { 0 };
    char acBuff[] = "255";
    char acParameter[] = "mac1=";

    memcpy(acMacBuffer, g_aucMyMac, sizeof(acMacBuffer));

    for (uint8_t i = 0; i < 6; i++) {
        sprintf(acParameter, "mac%d=", i + 1);
        int pos = getParameter((char*) paucResponse, acParameter, acBuff,
                sizeof(acBuff));
        if (pos) {
            acMacBuffer[i] = atoi(acBuff);
        }
    }

    storeMacToEeprom(acMacBuffer);
}
