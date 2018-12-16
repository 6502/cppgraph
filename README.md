# cppgraph
dynamic C++ graph data structure

![diagram](/graph.png "Simplified diagram")

This code is an example of a data structure able to represent dynamic graphs
(where you can add or remove edges and vertices efficiently):

- Adding a node is O(1)
- Adding an edge is O(1) (given the two nodes addresses)
- Removing an edge is O(1)
- Removing a node is O(deg(x))
- Querying for incoming or outgoing edges is O(answer size)

The graph is directed and supports multiple links between the same pair of
nodes and loops (a node connected to itself).

The picture shows the internal links used by two nodes linked unidirectionally
to a third one (links for the global lists of nodes and edges are not shown).

Written as an example for https://stackoverflow.com/a/5493656/320726
