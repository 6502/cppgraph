# cppgraph
dynamic C++ graph data structure

This code is an example of a data structure able to represent dynamic graphs
(where you can add or remove nodes and vertices efficiently):

- Adding a node is O(1)
- Adding a link is O(1) (given the two nodes addresses)
- Removing a link is O(1)
- Removing a node is O(deg(x))
- Querying for incoming or outgoing links is O(answer size)

The graph is directed and supports multiple links between the same pair of
nodes and loops (a node linked to itself).

Written as support for https://stackoverflow.com/a/5493656/320726