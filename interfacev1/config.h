//configuration for the interface:

long baudrate = 9600;//...............................................................serial port baudrate
byte pttdelay = 10;//.................................................................delay for ptt output before proceeding (inc 10ms)
byte acktime = 50;//..................................................................pulse time for ack outputs (inc 1ms)
char emergencystring[] = "EMERGENCY";//...............................................string to send over serial when emergency signal is received
char auxalarmstring[] = "AUXILIARY";//................................................string to send over serial port when aux alarm signal is received
int holdtoneinterval = 1000;//........................................................interval for sending priority channel tone (inc 10ms)
