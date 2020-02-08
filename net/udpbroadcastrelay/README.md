UDP Broadcast Relay for Linux / FreeBSD / pfSense / OPNsense
==========================

This program listens for packets on a specified UDP broadcast port. When
a packet is received, it sends that packet to all specified interfaces
but the one it came from as though it originated from the original
sender.

The primary purpose of this is to allow devices or game servers on separated
local networks (Ethernet, WLAN, VLAN) that use udp broadcasts to find each
other to do so.

INSTALL
-------

    make
    cp udpbroadcastrelay /some/where

USAGE
-----

```
./udpbroadcastrelay \
    -id id \
    --port <udp-port> \
    --dev eth0 --dev eth1
    [--dev ethx...] \
    [--multicast 224.0.0.251] \
    [-s <spoof_source_ip>]
    [-t|--ttl-id] [-d] [-f]
    [-h|--help]
```

- udpbroadcastrelay must be run as root to be able to create a raw
  socket (necessary) to send packets as though they originated from the
  original sender.
- `id` must be unique number between instances with range 1 - 63. This is
  used to set the DSCP of outgoing packets to determine if a packet is an
  echo and should be discarded.
- `udp-port` Destination udp port to listen to. Range 1 - 65535.
  Example values for common services are given below.
- `-dev <ethx>` specifies the name of an interface to receive and
  transmit packets on. This option needs to be specified at least twice
  for 2 separate interfaces otherwise this tool won't actually do
  anything!
- The tool can listen for and relay packets using multicast groups
  with
  `--multicast <group address>`.
- The source address for all packets can be modified with `-s <ip>`. This
  is unusual.
- A special source ip of `-s 1.1.1.1` can be used to set the source ip
  to the address of the outgoing interface and the source UDP port to the
  same as the destination port. '-s 1.1.1.2' does the same but leaves
  the UDP ports unchanged. These values are notably required to cater
  for the Chromecast system.
- The original version of this tool marked the TTL of outgoing relayed
  packets to detect echos and preserved DSCP. This original behavior can
  be restored by setting the [-t|--ttl-id] parameter.
- `-d` will enable debugging output.
- `-f` will fork the application to the background and create a pid file
  at /var/run/udpbroadcastrelay_ID.pid
- `-h|--help` Display a detailed help dialog.

EXAMPLE
-------

#### mDNS / Multicast DNS (Chromecast Discovery + Bonjour + More)
`./udpbroadcastrelay --id 1 --port 5353 --dev eth0 --dev eth1 --multicast 224.0.0.251 -s 1.1.1.1`

(Chromecast requires broadcasts to originate from an address on its subnet)

#### SSDP (Roku Discovery, DLNA Media, Sonos, UPnP + More)
`./udpbroadcastrelay --id 1 --port 1900 --dev eth0 --dev eth1 --multicast 239.255.255.250`

#### Lifx Bulb Discovery
`./udpbroadcastrelay --id 1 --port 56700 --dev eth0 --dev eth1`

#### Broadlink IR Emitter Discovery
`./udpbroadcastrelay --id 1 --port 80 --dev eth0 --dev eth1`

#### Warcraft 3 Server Discovery
`./udpbroadcastrelay --id 1 --port 6112 --dev eth0 --dev eth1`

#### Windows Network Neighborhood Discovery
 NetBIOS Name Service (137), SMB Browser (138) and SSDP (1900).
 Windows Network Discovery across networks relies on relaying
 these three protocols all at once.
 To requires that three separate instances of udpbroadcastrelay
 run simultaneously so in this example we execute the command
 with the "-f" parameter in order to run the tool in the
 background.
`./udpbroadcastrelay --id 1 --port 137 --dev eth0 --dev eth1 -f`
`./udpbroadcastrelay --id 2 --port 138 --dev eth0 --dev eth1 -f`
`./udpbroadcastrelay --id 3 --port 1900 --dev eth0 --dev eth1 --multicast 239.255.255.250 -f`

#### Syncthing Discovery
`./udpbroadcastrelay --id 1 --port 21027 --dev eth0 --dev eth1`

#### Raknet Discovery (Minecraft)
`./udpbroadcastrelay --id 1 --port 19132 --dev eth0 --dev eth1`


Note about firewall rules
---

If you are running udpbroadcastrelay on a router, it can be an easy
way to relay broadcasts between VLANs. However, beware that these broadcasts
will not establish a RELATED firewall relationship between the source and
destination addresses.

This means if you have strict firewall rules, the recipient may not be able
to respond to the broadcaster. For instance, the SSDP protocol involves
sending a broadcast packet to port 1900 to discover devices on the network.
The devices then respond to the broadcast with a unicast packet back to the
original sender. You will need to make sure that your firewall rules allow
these response packets to make it back to the original sender.
