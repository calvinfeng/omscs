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

## Multiplexing vs Demultiplexing

Process can have one or more sockets, doors through which data passes from network to the process
and through which data passes from the process to the network. Transport layer in in the receiving
host does not actually deliver data directly to a process, but instead to an intermediary socket.

The job of delivery the data in a transport-layer segment to the correct socket is called
**demultiplexing**. The job of gathering data chunk with header information to create segments, and
passing the segments to the network layer is called **multiplexing**.

## UDP

Todo

## Principles of Reliable Data Transfer

Todo

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
