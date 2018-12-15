#include <stdio.h>
#include "cppgraph.h"

int main() {
    typedef Graph<char, int> Graph;
    Graph g;
    auto a = g.addNode('a'), b = g.addNode('b'), c = g.addNode('c'), x = g.addNode('x');
    g.addLink(1, a, b);
    g.addLink(2, b, c);
    g.addLink(3, c, a);
    g.addLink(4, a, x);
    g.addLink(5, x, a);
    g.addLink(6, b, x);
    g.addLink(7, x, b);
    g.addLink(8, c, x);
    g.addLink(9, x, c);

    auto dump = [&](){
                    g.forEachNode([&](Graph::Node *n){
                                      printf("Node '%c'\n", n->data);
                                      n->forEachOutgoingLink([&](Graph::Link *L){
                                                                 printf(" %i → '%c'\n", L->data, L->to->data);
                                                                 return true;
                                                             });
                                      n->forEachIncomingLink([&](Graph::Link *L){
                                                                 printf(" %i ← '%c'\n", L->data, L->from->data);
                                                                 return true;
                                                             });
                                      return true;
                                  });
                };
    printf("Before ---------\n");
    dump();
    delete a;
    printf("After ----------\n");
    dump();

    return 0;
}
