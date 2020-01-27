UDP Broadcast Relay for Linux / FreeBSD / pfSense /OPNsense
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
./udp-broadcastrelay \
    -id id \
    --port <udp-port> \
    --dev eth0 \
    [--dev eth1...] \
    [--multicast 224.0.0.251] \
    [-s <spoof_source_ip>]
```

- udpbroadcastrelay must be run as root to be able to create a raw
  socket (necessary) to send packets as though they originated from the
  original sender.
- `id` must be unique number between instances. This is used to set the TTL of
  outgoing packets to determine if a packet is an echo and should be discarded.
- Multicast groups can be joined and relayed with
  `--multicast <group address>`.
- The source address for all packets can be modified with `-s <ip>`. This
  is unusual.
- A special source ip of `-s 1.1.1.1` can be used to set the source ip
  to the address of the outgoing interface.
- `-f` will fork the application to the background. It will also generate a
  pid file in /var/run with the name udpbroadcastrelay_id.pid, where ID is the id
  is that set as the instance id.

EXAMPLE
-------

#### mDNS / Multicast DNS (Chromecast Discovery + Bonjour + More)
`./udpbroadcastrelay --id 1 --port 5353 --dev eth0 --dev eth1 --multicast 224.0.0.251 -s 1.1.1.1`

(Chromecast requires broadcasts to originate from an address on its subnet)

#### SSDP (Roku Discovery + More)
`./udpbroadcastrelay --id 1 --port 1900 --dev eth0 --dev eth1 --multicast 239.255.255.250`

#### Lifx Bulb Discovery
`./udpbroadcastrelay --id 1 --port 56700 --dev eth0 --dev eth1`

#### Broadlink IR Emitter Discovery
`./udpbroadcastrelay --id 1 --port 80 --dev eth0 --dev eth1`

#### Warcraft 3 Server Discovery
`./udpbroadcastrelay --id 1 --port 6112 --dev eth0 --dev eth1`

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
