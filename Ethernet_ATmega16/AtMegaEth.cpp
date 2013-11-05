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
#include <avr/pgmspace.h>

#include "ip_arp_udp_tcp.h"
#include "avr_compat.h"
#include "net.h"
#include "aux_globals.h"

// HD44780 LCD Class
#include "HD44780.h"
// enc28j60 Ethernet Class
#include "ENC28J60.h"

// please modify the following two lines. mac and ip have to be unique
// in your local area network. You can not have the same numbers in
// two devices:
static uint8_t mymac[6] = {0x34,0x35,0x36,0x37,0x38,0x39};
//static uint8_t myip[4] = {192,168,2,24};
static uint8_t myip[4] = {192,168,0,109};
// listen port for tcp/www (max range 1-254)
#define MYWWWPORT 80
// working buffer
#define BUFFER_SIZE 450
static uint8_t buf[BUFFER_SIZE+1];
// Global counters
static int nPingCount = 0, nAccessCount = 0;
// Objects
HD44780 lcd;
ENC28J60 eth;



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

/*
 * Main entry point
 */
int main(void) {



    lcd.lcd_init();                              // init the LCD screen
    lcd.lcd_clrscr();                            // initial screen cleanup
    lcd.lcd_home();
//    lcd.lcd_setline(0);
    lcd.lcd_string("Tomasz");
    lcd.lcd_setline(1);
    lcd.lcd_string_format("Jokiel 1");
//    while(true);


    uint16_t plen;
    uint16_t dat_p;


    /* enable PD2/INT0, as input */
//    DDRD &= ~(1<<DDD2);
    // enable PD3/INT1, as input
    DDRD &= ~(1<<DDD3);

    /*initialize enc28j60*/
    eth.m_enc28j60Init(mymac);
//    fcpu_delay_ms(20);
    fcpu_delay_ms(100);

    /* Magjack leds configuration, see enc28j60 datasheet, page 11 */
    // LEDB=yellow LEDA=green
    // 0x476 is PHLCON LEDA=links status, LEDB=receive/transmit
    // enc28j60PhyWrite(PHLCON,0b0000 0100 0111 01 10);
    eth.m_init_leds();
//    fcpu_delay_ms(20);
    fcpu_delay_ms(100);

    //init the ethernet/ip layer:
    eth.m_init_ip_arp_udp_tcp(mymac,myip,MYWWWPORT);

    while(1){
        lcd.lcd_setline(0);
        lcd.lcd_string_format("%d.%d.%d.%d    \neth rdy.Pngs:%d   ",myip[0], myip[1], myip[2],myip[3], nPingCount);
        // get the next new packet:
        plen = eth.m_enc28j60PacketReceive(BUFFER_SIZE, buf);

        /*plen will ne unequal to zero if there is a valid
         * packet (without crc error) */
        if(plen==0) continue;


        // arp is broadcast if unknown but a host may also
        // verify the mac address by sending it to
        // a unicast address.
        if(eth.m_eth_type_is_arp_and_my_ip(buf,plen)){
            make_arp_answer_from_request(buf);
            continue;
        }

        // check if ip packets are for us:
        if(eth.m_eth_type_is_ip_and_my_ip(buf,plen)==0){
            continue;
        }

        if(buf[IP_PROTO_P]==IP_PROTO_ICMP_V && buf[ICMP_TYPE_P]==ICMP_TYPE_ECHOREQUEST_V){
            // a ping packet, let's send reply
            eth.m_make_echo_reply_from_request(buf,plen);
            nPingCount ++;
            continue;
        }
        // tcp port www start, compare only the lower byte
        if (buf[IP_PROTO_P]==IP_PROTO_TCP_V&&buf[TCP_DST_PORT_H_P]==0&&buf[TCP_DST_PORT_L_P]==MYWWWPORT){
            if (buf[TCP_FLAGS_P] & TCP_FLAGS_SYN_V){
                eth.m_make_tcp_synack_from_syn(buf);
                // make_tcp_synack_from_syn does already send the syn,ack
                continue;
            }
            if (buf[TCP_FLAGS_P] & TCP_FLAGS_ACK_V) {
                eth.m_init_len_info(buf); // init some data structures
                // we can possibly have no data, just ack:
                dat_p = eth.m_get_tcp_data_pointer();
                if (dat_p==0) {
                    if (buf[TCP_FLAGS_P] & TCP_FLAGS_FIN_V){
                        // finack, answer with ack
                        eth.m_make_tcp_ack_from_any(buf);
                    }
                    // just an ack with no data, wait for next packet
                    continue;
                }
                // count page requests
                nAccessCount++;

                // check parameters
                char *szURLData = (char *)&(buf[dat_p]);
                char szParam1[20] = {0};
                int p1 = GetParameter(szURLData, "cmd=", szParam1, 20);
                if (p1>0) {
                    int cmd = atoi(szParam1);
                    char szReplyHTML[255];// = "<body>hello</body>";
                    sprintf(szReplyHTML,
                            "<b>Server Stats:</b><br>"\
                            "Address: %d.%d.%d.%d<br>Pings: %d<br>Access: %d<br><br>"\
                            "<b>Sensors:</b><br>"\
                            "",
                            myip[0],myip[1],myip[2],myip[3], nPingCount,nAccessCount);

                    plen=eth.m_fill_tcp_data_p(buf,0,PSTR("HTTP/1.0 200 OK\r\nContent-Type: text/html\r\n\r\n"));
                    plen=eth.m_fill_tcp_data(buf,plen,szReplyHTML );
                }



                eth.m_make_tcp_ack_from_any(buf); // send ack for http get
                eth.m_make_tcp_ack_with_data(buf,plen); // send data

            }

        }
        // tcp port www end

    }
    return (0);
} 
