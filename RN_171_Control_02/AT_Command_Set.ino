/*
AT SET COMMANDS USED TO PUT THE RN-171 INTO USEFUL MODES

//    COMMM PARAMETERS
// set comm remote 0\r
#define COMM_REMOTE 0x0
// set comm idle 10\r
#define COMM_IDLE 10
// set comm match 0x3E '>'  // when UART sees '>' it sends the packet
#define COMM_MATCH 0X3E  
// set comm size 1420  // IP packet is sent whenever this many bytes are received (largest size please)
#define COMM_SIZE 1420  
// set comm time 10  // sends the IP packet if no additional bytes are sent in x milliseconds
#define COMM_TIME 10   
//    DNS PARAMETERS
// set dns address <string> // used to create a static IP for RN module
// set dns name api.pachube.com  // set the name of the host for TCP/IP connections
#define DNS_NAME  api.pachube.com
// set dns backup <string>  // used to create a backup host
//    IP PARAMETERS
// set ip address <addr>  // sets IP address for RN-171
// set ip backup <addr>  // sets a secondary host IP address
// set ip dhcp 1  // get IP address and gateway from AP
#define IP_DHCP 1
// set ip flags <value>  // set TCP/IP functions. bitmapped. default is 0x7 see user guide
// set ip gateway <addr>  // sets gateway IP address. if DHCP is on, this gets overwritten
// set ip host 216.52.233.122  // sets the remote host IP address
#define IP_HOST  216.52.233.122
// set ip localport <num>
// set ip netmask <value>
// set ip protocol 18  // sets the IP protocol to TCP Server & Client, and HTTP client
#define IP_PROTOCOL  18
// set ip remote 80  // sets the remote host port number
#define IP_REMOTE  80
// set ip tcp-mode <mask>  // ??
//    OPTIONAL PARAMETERS
// set opt jointmr <msec>  // time in mS join function waits for association. default 1000
// set opt format <value>  // settings for HTTP client/webserver. bitmapped. default is 0
// set opt replace <string>  // character used in place of space " ". default is 0x24 "$"
// set opt deviceid <string>  // used to store product name/serial number. max size is 32 bytes
// set opt password <string>  // TCP connection password for minimal security. default is 0, no pass
//     SYSTEM PARAMETERS
// set sys autoconn <value>  // sets the auto connect timer in TCP mode 
#define SYS_AUTOCON  1  // connect to the stored hose immediately upon power up or wake from sleep
// set sys autosleep <value>  // sets the auto sleep timer in UDP mode
// set sys iofunc <value>  // sets the IO port alternate funcitons RTDS
// set sys mask <mask>  // sets the IO port direction mask RTDS
// set sys printlvl <value> // controls debub print messages default is 1 = all status messages
#define SYS_PRINTLVL  0  // quiet mode no messages printed on wake up or power up
// set sys output <value><mask>  // sets GPIO pins to HIGH or LOW. RTDS
// set sys sleep <sec>  // sets time the module is awake. MUST SET WAKE TIMER OR MODULE NEVER WAKES UP!
#define SYS_SLEEP  10  // stay awake for 10 seconds
// set sys trigger <value>  // wake the module from sleep via sensor input pins RTDS
// set sys value <hex>  // set default GPIO outputs on power up RTDS
// set sys wake <sec>  // sets time the module is alseep in seconds 
#define SYS_WAKE  60  // module sleeps for 60 seconds
//      TIME SERVER PARAMETERS
// set time address <addr>  // sets the time server address (sNTP servers)
// set time port <num>  // sets time server port number
// set time enable <value>  // 0=disable; 1=get time on power up; >1=get time every <value> minutes
#define TIME_ENABLE  1
// set time raw <value>  // enables setting RTC value from console. sets RTC in seconds
//      UART PARAMETERS
//  

  





*/
