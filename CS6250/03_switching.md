# Switching

## Networking Two Hosts

Suppose we have 2 machines, each with a single interface to each other. Host 1 and Host 2 would be
connecteds by two ethernet adapters or network interfaces. Each adapter would have a MAC address.

> The main difference between MAC and IP address is that, MAC Address is used to ensure the physical
  address of computer. It uniquely identifies the devices on a network. While IP address are used to
  uniquely identifies the connection of network with that device take part in a network.

If Host 1 wants to send a datagram to Host 2, it can simply send that datagram via its eternet
adapter with a destination MAC address of Host 2. Typically a host knows a DNS name or an IP but it
does not know the MAC address of another host. We need a protocol to help Host 1 to learn the MAC
address of Host 2.

![Multi Layer Encapsulation](https://4.bp.blogspot.com/-EpBS818VfpU/VMD2pzFKhOI/AAAAAAAAAdI/t0gR5ct3m9I/s1600/01fig05-100277629-orig.jpg)

### ARP - Address Resolution Protocol

In ARP, a host queries with an IP address, broadcasting that query to every other node on the
network. That query will be of a form, _"who has IP address xxx.xxx.xxx.xx?"_ A particular host who
has that IP address on the LAN will respond with the appropriate MAC address. When query receives a
reply, the sender host will start to build an ARP table that maps each IP address in the local area
network to the corresponding MAC address.

Using the original example, Host 1 wants to send a packet to Host 2. Host 1 will use its ARP table
and wrap its IP packet with an eternet frame that encapsulates the destination MAC address.

## Switch

A switch breaks the subnet into multiple LAN segments. Typically a frame that is bound for a host in
the same part or segment of the LAN is not forwarded to other segments. For example, if we had a
network with 3 hubs, all connected by a switch, then each of these would be its own broadcast domain.

If a host wants to send a frame to another host within the same segment, then that frame would be
broadcast within that domain. The switch would recognize the destination was in the same segment. It
would not forward that packet to other segments.

![Network Diagram](https://conceptdraw.com/How-To-Guide/picture/Network-diagram-System-design.png)

### Learning Switch

A learning switch maintains a table between destination addresses and output ports on the switch.
When it receives a frame destinted for a particular place, it knows what output port to forward the
frame.

Initially, the forwarding table is empty, so if there's no entry in the forwarding table, the switch
will simply flood. Flooding means it will send the frame to all ports. Because the frame has a
source address, say A, and it arrives on input port 1. Now the switch can now make an association
between address A and port 1. In the future, when the switch sees frames destined for host A, it no
longer needs to perform a flood.

| Destination | Port |
|-------------|------|
| A           | 1    |

### Spanning Tree

Flooding has one issues. If the network topology is a cyclic graph, the flooding can become an
infinite loop of frame forwarding.

> A spanning tree is a subst of graph G, which has all the vertices covered with minimum possible
  number of edges. Hence, a spanning tree does not have cycles and it cannot be disconnected.

In order to address this problem, the network needs to be constructed as a spanning tree. Each node
would only broadcast to the links that belong to the spanning tree (excluding the link which
it receives the frame from.) 

The switches within the network need to perform the following steps,

1. Elect a root (of the tree) by selecting the switch with smallest ID.
2. Each switch excludes link if it is not a shortest path to root.

Initially, every node thinks it is the root. As time progresses, each node updates its view of the
root and compute distance to the new root. In order to execute this protocol, the switches/nodes
just need to broadcast a payload indicating, `claimed_root`, `distance` and `origin_root`. Each node
can carry out logic to determine who's the real root and which link provides the shortest distance
to the root.

![Spanning Tree Protocol](https://upload.wikimedia.org/wikipedia/commons/thumb/b/bb/Spanning_tree_protocol_at_work_5.svg/1280px-Spanning_tree_protocol_at_work_5.svg.png)

## Switch vs Router

Switches are on layer 2 with eternet cables. 

- It is capable of auto-configuring, like the example above
- Forwarding tends to be fast

Routers are on layer 3 with IP.

- Not restricted to spanning tree, a single packet could be sent along one of multiple possible
  paths in the underlying router level.
