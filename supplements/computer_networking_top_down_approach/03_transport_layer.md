# Transport Layer

## Transport vs Network Layers

A transport layer protocol provides logical communication between application processes running on
different hosts. By logical communication, we mean that from an application's perspective., it is
as if the hosts running the processes were directly connected; in reality, the hosts may be on
opposite sides of the planet.

Application processes use the logical communication provided by the transport layer to send messages
to each other, free from th worry of the details of the physical infrastructure used to carry these
messages.

Transport layer lies above the network layer in the protocol stack. Whereas a transport layer
protocol provides logical communication between **processes** running on different hosts, a network
layer protocol provides logical communication between **hosts**.

Common applications and their underlying transport protocols.

| Application | Application-Layer Protocol | Transport Protocol |
|-------------|----------------------------|--------------------|
| Electronic Mail | SMTP | TCP |
| Remote Terminal Access | Telnet | TCP |
| Web | HTTP | TCP |
| File Transfer | FTP | TCP |
| Remote File Server | NFS | UDP |
| Streaming Multimedia | typically proprietary | UDP or TCP |
| Internet Telephony | typically proprietary | UDP or TCP |
| Network Management | SNMP | UDP |
| Routing Protocol | RIP | UDP |
| Name Translation | DNS | UDP |

## Multiplexing vs Demultiplexing

Process can have one or more sockets, doors through which data passes from network to the process
and through which data passes from the process to the network. Transport layer in in the receiving
host does not actually deliver data directly to a process, but instead to an intermediary socket.

The job of delivery the data in a transport-layer segment to the correct socket is called
**demultiplexing**. The job of gathering data chunk with header information to create segments, and
passing the segments to the network layer is called **multiplexing**.

## UDP

UDP, defined in RFC 768, does just about as little as a transport protocol can do. Aside from the
multiplexing/demultiplexing function and some light error checking, it adds nothing to IP. In fact,
if the application developer chooses UDP instead of TCP, then the application is almost directly
talking with IP.

UDP takes messasges from the application process, attaches source and destination port number fields
for the multiplexing/demultiplexing service, adds two other fields, and passes the resulting
segment to the network layer.

The network layer encapsulates the transport-layer segment into an IP datagram and then makes a best
effort attempt to deliver the segment to the receiving host.

UDP does not perform handshake, thus it is said to be connectionless.

![UDP](https://media.geeksforgeeks.org/wp-content/uploads/UDP-header.png)

Although it is unreliable data transfer, there are couple benefits to UDP.

- Finer application-level control over what data is sent and when is sent.
- No connection needed, therefore no delay introduced.
- No connection state, less memory footprint, thus supporting more clients at once.
- Small packet header overhead. It's 8 bytes UDP segment vs 20 bytes TCP segment.

## TCP

TCP is said to be connection oriented because before one application process can begin to send data
to another, the two processes must first "handshake" with each other - that is, they must send some
preliminary segments to each other to establish the parameters of the ensuing data transfer.

A TCP connection provides a full-duplex service. If there is a TCP connection between process A on
one host and process B on another host, then application layer data can flow from A to B at the same
time as application data from B to A. A TCP connection is always point-point, that is, between a
single sender and a single receiver.

Suppose a process running in one host wants to initiate a connection with another process in another
host. The process that is initiating the connection is called the client process, while the other
process is called the server process.

- Client first sends a special TCP segment
- Server responds with a second sepcial TCP csegment
- Client responds again with a third special segment

This is referred to as a three-way handshake.
