import logging
logging.getLogger("scapy.runtime").setLevel(logging.ERROR)
from scapy.all import *
import time
import sys
current_seconds_time = lambda: int((time.time()))
def tracerout():
    ip=IP()
    ip.dst=sys.argv[1]
    udp=UDP()
    udp.sport=33434
    udp.dport=33434
    i=1
    while True:
	ip.ttl=i  
	start = time.time()
	result=sr1(ip/udp/"deii",verbose=False,timeout=2) # confirm the meaning of timeout 
	end = time.time()
	if result is None:
		print i,"\t" , "*"			
	else:	
		print i,"\t",result[IP].src, " ",(end-start)*1000, "\bms" # RTT doesn't match with traceroute, verify
  		if result[ICMP].type==3:
    			break
	i=i+1
if __name__=="__main__":
  tr=tracerout()
