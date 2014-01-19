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
static uint8_t mymac[6] = {0x34,0x35,0x36,0x37,0x38,0x39};
static uint8_t myip[4] = {192,168,0,109};
// listen port for tcp/www (max range 1-254)
#define MYWWWPORT 80
// working buffer
#define BUFFER_SIZE 500
static uint8_t buf[BUFFER_SIZE+1];
// servers counters
static int nPingCount = 0, nAccessCount = 0;
// Objects


int GetParameter(char *url, char *parameter, char *output, int outputsize);

void PingCallback(uint8_t *ip) {
    nPingCount++;
}


/*
 * Main entry point
 */
int main(void) {

    //=====init green led
    LEDInit();
    LEDSet(1);

    //=====setup eth interface
    uint16_t plen = 0,  dat_p = 0;
    //initialize enc28j60
    enc28j60Init(mymac);



    _delay_ms(100);

    // Magjack leds configuration, see enc28j60 datasheet, page 11 
    // LEDB=yellow LEDA=green
    // 0x476 is PHLCON LEDA=links status, LEDB=receive/transmit
    // enc28j60PhyWrite(PHLCON,0b0000 0100 0111 01 10);
    enc28j60PhyWrite(PHLCON,0x476);


    _delay_ms(100);

    //init the ethernet/ip layer:
    init_udp_or_www_server(mymac,myip);
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
        // tcp port 80 begin
        if (strncmp("GET ",(char *)&(buf[dat_p]),4)!=0){
            dat_p = fill_tcp_data_p(buf, 0, PSTR("HTTP/1.0 200 OK\r\nContent-Type: text/html\r\nPragma: no-cache\r\n\r\n"));    // HTTP header
            dat_p = fill_tcp_data_p(buf, dat_p, PSTR("<h1>200 OK</h1>"));
            goto SENDTCP;
        }
        if (strncmp("/ ",(char *) & (buf[ dat_p + 4] ), 2) == 0 ){
            nAccessCount++;
            dat_p = fill_tcp_data_p(buf, 0, PSTR("HTTP/1.0 200 OK\r\nContent-Type: text/html\r\nPragma: no-cache\r\n\r\n"));    // HTTP header
            // webcontent
            char szWebText[130] = {0};
            sprintf(szWebText,
                    "<b>Arduino UNO Webserver / ENC28J60</b><br><br>Server stats:<br>Acc:%d Png:%d<br>%d<br/>Tomasz Jokiel",
                    nAccessCount, nPingCount);
            dat_p = fill_tcp_data(buf, dat_p, szWebText);
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
            int p1 = GetParameter(szURLData, "par=", szParam1, 20);
            dat_p = fill_tcp_data_p(buf, 0, PSTR("HTTP/1.0 200 OK\r\nContent-Type: text/html\r\nPragma: no-cache\r\n\r\n"));    // HTTP header
            if (p1) {
                // webcontent
                char szWebText[130] = {0};
                sprintf(szWebText,
                        "<b>Arduino UNO Webserver / ENC28J60</b><br><br>Server stats:<br>Acc:%d Png:%d<br>parameter=%s<br/>Tomasz Jokiel",
                        nAccessCount, nPingCount, szParam1);
                dat_p = fill_tcp_data(buf, dat_p, szWebText);
            } else {
                // webcontent
                char szWebText[130] = {0};
                sprintf(szWebText,
                        "<b>Arduino UNO Webserver / ENC28J60</b><br><br>Server stats:<br>Acc:%d Png:%d<br>Unknown parameter<br/>Tomasz Jokiel",
                        nAccessCount, nPingCount, szParam1);
                dat_p = fill_tcp_data(buf, dat_p, szWebText);
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
int GetParameter(char *url, char *parameter, char *output, int outputsize) {
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

