# About keetf 📚
keeft is a TCP/IP file transfer tool. It sends/receives files over networks (eg.: LAN, Internet, ...).

## Its very simple to use 😉!

#### sending a file 📤

_Send the file helloworld.txt to a keeft receiver in the localhost:_

> keeft -S helloworld.txt  

#### receiving a file 📥

_Receive a file from an keeft sender:_

> keeft -R

## Here are some keeft options 📋:

##### -H 
To get a list of all keeft options with their descriptions.

> keeft -H

##### -P _Port_
If there are many keeft receivers running in the machine at the same time, it will be necessary to specify (with a port) the target receiver. the port needs to be the same for both (sender and receiver).

_setting the port (9001) to send the file helloworld.txt:_  

> keeft -S helloworld.txt -P 9001 

_setting the port (9001) to receive from:_

> keeft -R -P 9001 

##### -K _Key_ 
A key (aka password) is used to grant more security at the authentication phase.

_setting a key on receiver_

> keeft -R -K bananas21

_setting a key on sender_

> keeft -S helloworld.txt -K bananas21

