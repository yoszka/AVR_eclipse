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
static uint8_t myip_ee[4]  EEMEM;

//static uint8_t temp;
//static uint8_t temp_ee  EEMEM;

static uint8_t g_aucMyMac[6] = {0x34,0x35,0x36,0x37,0x38,0x39};
static uint8_t g_aucMyIp[4] = {192,168,0,109};
// listen port for tcp/www (max range 1-254)

// Auxiliary macros to turn numeric definition into string
#define STRINGIZE_(x)   #x
#define STRINGIZE(x)    STRINGIZE_(x)

#define MYWWWPORT       1235
#define MYWWWPORT_STR   STRINGIZE(MYWWWPORT)
// working buffer
//#define BUFFER_SIZE 500
#define BUFFER_SIZE 800
static uint8_t buf[BUFFER_SIZE+1];
// servers counters
static int nPingCount = 0, nAccessCount = 0;
// Objects

// http://192.168.0.109:1235/?par=0&ip1=192&ip2=168&ip3=0&ip4=108
// http://192.168.0.109:1235/?par=0&mac1=52&mac2=53&mac3=54&mac4=55&mac5=56&mac6=57

int  getParameter      (char *url, char *parameter, char *output, int outputsize);
void storeIpToEeprom   (uint8_t ip[4]);
void readIpFromEeprom  (uint8_t ip[4]);
void storeMacToEeprom  (uint8_t mac[6]);
void readMacFromEeprom (uint8_t mac[6]);
void updateIpIfNeeded  (uint8_t* paucResponse);
void updateMacIfNeeded (uint8_t* paucResponse);

void PingCallback(uint8_t *ip) {
    nPingCount++;
}


/*
 * Main entry point
 */
int main(void) {

    ledOn();

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
    enc28j60PhyWrite(PHLCON,0x476);


    _delay_ms(100);

    //init the ethernet/ip layer:
    // read values from eeprom
    readIpFromEeprom(g_aucMyIp);
    readMacFromEeprom(g_aucMyMac);

    init_udp_or_www_server(g_aucMyMac,g_aucMyIp);
    www_server_port(MYWWWPORT);
    register_ping_rec_callback(PingCallback);


    while(1){

        // handle ping and wait for a tcp packet:
        dat_p = packetloop_arp_icmp_tcp(buf, enc28j60PacketReceive(BUFFER_SIZE, buf));

        // dat_p will be unequal to zero if there is a valid http get
        if(dat_p==0){
            // do nothing
            continue;
        }
        char szWebText[500] = {0};

        // tcp port 80 begin
        if (strncmp("GET ",(char *)&(buf[dat_p]),4)!=0){
            dat_p = fill_tcp_data_p(buf, 0, PSTR("HTTP/1.0 200 OK\r\nContent-Type: text/html\r\nPragma: no-cache\r\n\r\n"));    // HTTP header
            dat_p = fill_tcp_data_p(buf, dat_p, PSTR("<h1>200 OK</h1>"));
            goto SENDTCP;
        }
        if (strncmp("/ ",(char *) & (buf[ dat_p + 4] ), 2) == 0 ){
            nAccessCount++;
            uint8_t ip[4] = {0};
            uint8_t mac[6] = {0};
            readIpFromEeprom(ip);
            readMacFromEeprom(mac);

//            eeprom_read_block();

            // HTTP header
            dat_p = fill_tcp_data_p(buf, 0, PSTR("HTTP/1.0 200 OK\r\nContent-Type: text/html\r\nPragma: no-cache\r\n\r\n"));
            // webcontent
            sprintf(szWebText,
                    "<html><body><b>Arduino UNO Webserver / ENC28J60</b><br><br>Server stats:<br>Acc:%d Png:%d<br>%d:%d:%d:%d<br>%#02x:%#02x:%#02x:%#02x:%#02x:%#02x<br>",
                    nAccessCount, nPingCount, ip[0], ip[1], ip[2], ip[3], mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
            dat_p = fill_tcp_data(buf, dat_p, szWebText);
            dat_p = fill_tcp_data_p(buf, dat_p, PSTR("<script type=\"text/javascript\">function f(p){var x=null;x=new XMLHttpRequest();x.open(\"GET\",\"http://78.8.132.9:"MYWWWPORT_STR"/?par=\"+p,true);x.send(null);}</script><button onclick=\"f(1)\">ON</button><button onclick=\"f(0)\">OFF</button>"));
            dat_p = fill_tcp_data_p(buf, dat_p, PSTR("<br/>Tomasz Jokiel</body></html>"));
            //
            goto SENDTCP;
        }
        if (strncmp("GET /?",(char *) & (buf[dat_p] ), 6) == 0 ) {              // Request with parameter, i.e. http://192.168.0.109/?par=5
            /*

            GET /?par=20 HTTP/1.1
            Host: 192.168.0.109
            Connection<b>Arduino UNO Webserver / ENC28J60</b><br><br>Server stats:<br>Acc:0 Png:0<br>parameter=20<br/>Tomasz Jokiel

            */
            nAccessCount++;

            // check for parameters. Test by enter: http://192.168.0.109/?par=5
            char *szURLData = (char *)&(buf[dat_p]);
            char szParam1[20] = {0};
            int p1 = getParameter(szURLData, "par=", szParam1, 20);

            updateIpIfNeeded((uint8_t*)szURLData);
            updateMacIfNeeded((uint8_t*)szURLData);

            dat_p = fill_tcp_data_p(buf, 0, PSTR("HTTP/1.0 200 OK\r\nContent-Type: text/html\r\nPragma: no-cache\r\n\r\n"));    // HTTP header
            if (p1) {
                // webcontent
//                char szWebText[400] = {0};
//                sprintf(szWebText,
//                        "<b>Arduino UNO Webserver / ENC28J60</b><br><br>Server stats:<br>Acc:%d Png:%d<br>parameter=%s<br/>"
//                        "<form method=\"get\"action=\"http://192.168.0.109\"><input type=\"hidden\"name=\"par\"value=\"0\"/><button onclick=\"this.form.par.value=1;this.form.submit();\">ON</button><button onclick=\"this.form.par.value=0;this.form.submit();\">OFF</button></form>"
//                        "<br/>Tomasz Jokiel",
//                        nAccessCount, nPingCount, szParam1);
//                dat_p = fill_tcp_data(buf, dat_p, szWebText);


                sprintf(szWebText,
                        "<b>Arduino UNO Webserver / ENC28J60</b><br><br>Server stats:<br>Acc:%d Png:%d<br>parameter=%s<br>%d:%d:%d:%d<br/>",
                        nAccessCount, nPingCount, szParam1, g_aucMyIp[0], g_aucMyIp[1], g_aucMyIp[2], g_aucMyIp[3]);
                dat_p = fill_tcp_data(buf, dat_p, szWebText);
                dat_p = fill_tcp_data_p(buf, dat_p, PSTR("<script type=\"text/javascript\">function f(p){var x=null;x=new XMLHttpRequest();x.open(\"GET\",\"http://78.8.132.9:"MYWWWPORT_STR"/?par=\"+p,true);x.send(null);}</script><button onclick=\"f(1)\">ON</button><button onclick=\"f(0)\">OFF</button>"));
                dat_p = fill_tcp_data_p(buf, dat_p, PSTR("<br/>Tomasz Jokiel</body></html>"));

                if(atoi(szParam1)) {
                    ledOn();
                } else {
                    ledOff();
                }
            } else {
                // webcontent
//                char szWebText[400] = {0};
                sprintf(szWebText,
                        "<b>Arduino UNO Webserver / ENC28J60</b><br><br>Server stats:<br>Acc:%d Png:%d<br>Unknown parameter<br/>",
                        nAccessCount, nPingCount);
                dat_p = fill_tcp_data(buf, dat_p, szWebText);
                dat_p = fill_tcp_data_p(buf, dat_p, PSTR("<script type=\"text/javascript\">function f(p){var x=null;x=new XMLHttpRequest();x.open(\"GET\",\"http://78.8.132.9:"MYWWWPORT_STR"/?par=\"+p,true);x.send(null);}</script><button onclick=\"f(1)\">ON</button><button onclick=\"f(0)\">OFF</button>"));
                dat_p = fill_tcp_data_p(buf, dat_p, PSTR("<br/>Tomasz Jokiel</body></html>"));
            }
            //
            goto SENDTCP;
        }

        // all other URLs:
        dat_p = fill_tcp_data_p(buf, 0, PSTR("HTTP/1.0 401 Unauthorized\r\nContent-Type: text/html\r\n\r\n<h1>401 Unauthorized</h1>"));

        SENDTCP:
        www_server_reply(buf, dat_p); // send web page data


    }

    return (0);
} 

/*
 * Helper function to check a string for a given parameter, and return parameter value
 */
int getParameter(char *url, char *parameter, char *output, int outputsize) {
    // check for valid input parameters
    if (!url || !parameter || !output || !outputsize) return 0;

    char *occ = strstr(url, parameter);
    if (occ) {
        occ+=strlen(parameter); //skip the parameter itself
        int i =0;
        while(*occ &&  *occ!=' ' && *occ!='&' && i<outputsize) {
            output[i] = *occ;
            i++;
            occ++;
        }
        output[i] = 0;
        return i;
    } else { // given url parameter not found
        output[0] = 0;
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
    uint8_t acIpBuffer[4] = {0};
    char acBuffer[]       = "255";
    char acParameter[]    = "ip1=";

    memcpy(acIpBuffer, g_aucMyIp, sizeof(acIpBuffer));

    for(uint8_t i = 0; i < 4; i++){
        sprintf(acParameter, "ip%d=", i+1);
        int pos = getParameter((char*)paucResponse, acParameter, acBuffer, sizeof(acBuffer));
        if (pos) {
            acIpBuffer[i] = atoi(acBuffer);
        }
    }

    storeIpToEeprom(acIpBuffer);
}

/**
 * Check for MAC parameters to update and update if some - can update partially
 */
void updateMacIfNeeded(uint8_t* paucResponse) {
    uint8_t acMacBuffer[6] = {0};
    char acBuff[]          = "255";
    char acParameter[]     = "mac1=";

    memcpy(acMacBuffer, g_aucMyMac, sizeof(acMacBuffer));

    for(uint8_t i = 0; i < 6; i++){
        sprintf(acParameter, "mac%d=", i+1);
        int pos = getParameter((char*)paucResponse, acParameter, acBuff, sizeof(acBuff));
        if (pos) {
            acMacBuffer[i] = atoi(acBuff);
        }
    }

    storeMacToEeprom(acMacBuffer);
}
