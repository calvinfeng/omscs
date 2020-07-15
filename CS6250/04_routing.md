# Routing

The internet is not a single network, but rather a collection of tens of thousands of independently
operated networks, or **autonomous systems**. We will call it AS for short. Networks such as Comcast,
Georgia Tech, and Google are different types of AS and operating independent of each other. The AS
could be an internet service provider, a content provider, or a campus network.

For each network request, the traffic actually traverses through multiple autonomous systems. This
proces of internet routing actually involves two distinct types of routing.

- Intra-domain Routing occurs within the same AS
- Inter-domain Rounting occurs across multiple AS

## Intra-domain Routing

A topology inside an AS consists of ndoes and edges. The nodes are called points of presence or pops.
A pop is typically located in a dense population center. The edges between pops are typically
constrained by the location of fiber optic path.

Here's an example of a single AS topology, with nodes across the country. It's the Abilene Network,
which is a research network.

![Abilene Network](https://www.researchgate.net/profile/Filippo_Menczer/publication/221022686/figure/fig1/AS:670037010575392@1536760680923/Typical-activity-levels-between-core-routers-in-the-Abilene-network-The-numbers-refer-to.jpg)

Each node is considered a pop and each pop may have one or more edges between them. Georgia Tech is
an AS that connects at the Atlanta pop of the Abilene Network.

The topology of a network defines the graph structure. It is the AS' responsibility to compute paths
over the topology, a process called routing. Routing is a process by which nodes discover where to
forward traffic so that it reaches a certain node.

### Distance-Vector Routing

In distance-vector routing, each node sends multiple distance vectors to each of its neighbors. It's
essentially sending a copy of its routing table to its neighbors. Routers then compute the cost to
each destination based on shortest available path. Each node receives a copy of their neighbors'
routing table. Each node updates its routing table according to the Bellman-Ford equation.

> The cost and shortest available path computation is based on Bellman-Ford algorithm.

$$
d_x(y) = \text{min}_v \{ Cost(x, v) + d_v(y) \}
$$

For example, I have 3 nodes, each node has a routing cost table to begin with.

| Node ID | X | Y | Z |
|---------|---|---|---|
| X       | 0 | 1 | 5 |
| Y       | data missing | data missing | data missing |
| Z       | data missing | data missing | data missing |

| Node ID | X | Y | Z |
|---------|---|---|---|
| X       | data missing | data missing | data missing |
| Y       | 1 | 0 | 2 |
| Z       | data missing | data missing | data missing |

| Node ID | X | Y | Z |
|---------|---|---|---|
| X       | data missing | data missing | data missing |
| Y       | data missing | data missing | data missing |
| Z       | 5 | 2 | 0 |

When node `X` learns `Y`'s distance vectors, it realizes that it could reach `Z` at a lower cost.
The distance from `X` to `Z` will be computed as the minimum of the sums of all distances to `Z`
through any intermediate node.

In this case,

$$
Cost(x, y) = 1
$$

and,

$$
d_y(z) = 2
$$

Therefore, `X` can update its shortest cost distasnce to `Z` as 3 instead of 5. The same logic will
continue for all other nodes.

### Link State Routing

In link state routing, each node distributes a network map to every other node in the network. And
then, each node performs a shorest path computation between itself and all other nodes in the
network.

Initially, each node adds the cost of its immediate neighbor `D(v)` and every other distance to a
node that is infinite. Then each node floods the cost between node `u` and `v` to all of its
neighbors. The distance to any node `v` becomes the minimum of the cost between `u` and `w` plus the
cost to `w`.

> The shorest path computation in this case uses Dijkstra's algorithm.

One problem with link state protocol is that the time complexity grows `n^3` where `n` is the number
of nodes in the network. To solve this problem, people have partitioned networks into hiearchy. The
networks' routers are dvided into levels or areas. Each shortest path computation occurs locally
within one area. The global path planning applies to distance between areas instead of node. To find
the shorest path across area is simply stitching the solutions together.
