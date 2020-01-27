CONTRIBUTORS
-----------------

(Reverse chronological)

-   [Martin Wasley](https://github.com/marjohn56) forked to
    udpbroadcastrelay, added support for pid generation with id when in
    backround mode.
-   [Michael Morrison](https://github.com/sonicsnes) forked to
    udp-broadcast-relay-redux, refactored the code, added support for
    FreeBSD / pfSense, multicast packets, and interface source address.
-   udp-broadcast-relay-redux was based on udp-broadcast-relay by
    [Joachim Breitner](https://github.com/nomeata).
-   Patrick Huesmann submitted a patch to make udp-broadcast-relay send
    the packes to those NICs it did not recieve it from, based on the
    actual socket, not the broadcast IP. This is useful if more than one
    physical networks share the same broadcast range.
-   Савченко В. М. submitted an `ip-up.local` an `ip-down.local` file to
    automatically restart udp-broadcast-relay when new ppp-interfaces
    come up, see `ppp-if.up-local` for details.
-   Roman Hoog Antink contributed the option `-s` to spoof the source IP of
    forwarded packages.
- udp-broadcast-relay was based on
  [udp_broadcast_fw](http://www.serverquery.com/udp_broadcast_fw/)
  by Nathan O'Sullivan.
- Arny <cs6171@scitsc.wlv.ac.uk> (public domain UDP spoofing code)
- http://www.netfor2.com/ip.htm (IP/UDP packet formatting info)

Thanks to all contributors!
