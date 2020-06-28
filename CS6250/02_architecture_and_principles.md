# Architecture and Principles

## Brief History of the Internet

Early networks were developed for academic purposes. They connected mainframes from various campuses
across the nation. Here's ARPANET (Advanced Research Projects Agency Network) in 1974.

![ARPANET](https://upload.wikimedia.org/wikipedia/commons/thumb/0/00/Arpanet_1974.svg/1280px-Arpanet_1974.svg.png)

In 1973, the system started migrating toward TCP/IP protocol. It became standardized in 1978 to 1981.
On January 1st, 1983, the internet had one of its flag days where ARPANET completed its transition 
to TCP/IP. 

The internet continued to grow but the exponential growth of host machines lifted off in the mid 90s.
On August 1995, there were around 10 million hosts on the internet and 5 years later, there were
100 million hosts on the internet. 

- 1982 Roll out of DNS, a distributed host lookup system
- 1988 TCP congestion control system
- 1989 NSF net and BGP routing
- 1992 Audio and video streaming began
- 1993 World wide web was invented
- 1995 First search engine was introduced, AltaVista
- 2000 P2P file sharing

## Problems and Growing Pains

There are on-going problems with the internet.

1. Running out of addresses, only 32 bit addresses (about 4 billion IP addresses)
2. Congestion control has insufficient dynamic range, it doesn't work well with flaky wireless links
  and high speed intercontinental paths.
3. Routing has poor security, ease of misconfiguration, poor convergences and non-determinism.
4. Security is another concern. Although we have good encryption and authentication methods, it is
  not easy to enforce it across the network.
5. Denial of service remains a problem.

There's a common theme to the problems above. In order to address them all, we actually need a
change to the basic infrastructure which is why it is so difficult to solve.

## Architectural Design Principles

[Design of the DARPA Internet Protocols](http://ccr.sigcomm.org/archive/1995/jan95/ccr-9501-clark.pdf)

The fundamental design goal of the internet was multiplexed utilization of existing interconnected
networks. There are two important aspects to this goal. 

- Share use of a single communication channel
- Interconnection of existing networks

Statistical multiplexing or packet switching was invented to solve the sharing problem. The "narrow
wasit" was designed to solve the problem of interconnecting networks.

### Packet Switching

The information of forwarding traffic is contained in destination address of the packet. There is no
state in network ahead of time. There are very assumptions made about the level of service that the
network provides. Mulitple senders send network traffic or packets over the same set of shared
network links. This is in contrast to the phone network. If you were to make a phone call, the
resources for the path between you and the recipient are dedicated and are allocated until the call
ends.

- Internet uses packet switching
  - Advantage is resiliency
  - Disadvantage is variable delay and potential of lost packets
- Phone uses circuit switching
  - Advantage is resource control
  - Disadvantage is no sharing of resources

### Narrow Waist

Interconnection has a design goal of interconnecting many existing networks meanwhile hiding the
underlying technology from applications.

![Narrow Waist](https://slideplayer.com/slide/7597601/25/images/6/Narrow+Waist+for+Internet+Hourglass.jpg)

Every internet device must speak IP or have an IP stack. The narrow waist part is called the network
layer. The network layer provides guarantees to the layer above, for instance, TCP and UDP transport
layer. Another layer above is the application layer which has HTTP for web and SMTP for email
services.

> The most important aspect of this design is that the network layer only has one real protocol in
> use, and that is IP.

### Additional Goals

- Survivability: Network works even if some devices fail.
- Heterogeneity: Allows many different transport protocol to provide varying degrees of guarantees.
- Distributed Management: No central owner of the internet.

Notice the design did not discuss *security*, *availability*, *mobility*, and *scaling*.

## End-to-End Argument

[End to End Arguments in System Design](https://dl.acm.org/doi/pdf/10.1145/357401.357402)

The authors argued that intelligence should be implemented on endpoints of the network. The network
should have little intelligence to keep design simple and flexibile for all needs. Many people argue
that the end to end argument allowed the internet to grow rapidly, because innovation took place at
the edge applications and services, rather than in the middle of the network.

> The function in question can completely and correctly be implemented only with the knowledge and
> help of the application standing at teh endpoints of the communication system. Therefore,
> providing that questioned function as a feature of the communication system itself is not
> possible. (Sometimes an incomplete version of the function provided by the communication system
> may be useful as a performance enhancement.)
