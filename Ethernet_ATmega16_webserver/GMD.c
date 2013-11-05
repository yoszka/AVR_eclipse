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
#include "led.h"

// sensors
#include "sensors/ds1820.h"
#include "sensors/dht11.h"



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
            dat_p = fill_tcp_data_p(buf, 0, PSTR("HTTP/1.0 200 OK\r\nContent-Type: text/html\r\nPragma: no-cache\r\n\r\n"));
            dat_p = fill_tcp_data_p(buf, dat_p, PSTR("<h1>200 OK</h1>"));
            goto SENDTCP;
        }
        if (strncmp("/ ",(char *) & (buf[ dat_p + 4] ), 2) == 0 ){
            nAccessCount++;
            dat_p = fill_tcp_data_p(buf, 0, PSTR("HTTP/1.0 200 OK\r\nContent-Type: text/html\r\nPragma: no-cache\r\n\r\n"));
            // webcontent
            char szWebText[130] = {0};
            sprintf(szWebText,
                    "<b>ATmega8 Webserver / ENC28J60</b><br><br>Server stats:<br>Acc:%d Png:%d<br><br>(C) Radu Motisan 2012, www.pocketmagic.net<br/>Tomasz Jokiel",
                    nAccessCount, nPingCount);
            dat_p = fill_tcp_data(buf, dat_p, szWebText);
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
