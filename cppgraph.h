#if !defined(CPPGRAPH_H_INCLUDED)
#define CPPGRAPH_H_INCLUDED

#include <vector>
#include <memory>

template<typename ND, typename LD>
struct Graph {
    struct Link;

    struct Node {
        ND data;
        Graph& graph;
        Node *prev, *next;
        Link *firstIn, *lastIn, *firstOut, *lastOut;

        Node(ND data, Graph& graph)
            : data(std::move(data)),
              graph(graph),
              prev(graph.lastNode), next(nullptr),
              firstIn(nullptr), lastIn(nullptr),
              firstOut(nullptr), lastOut(nullptr)
        {
            if (prev) prev->next = this; else graph.firstNode = this;
            graph.lastNode = this;
        }

        Node(Graph& graph)
            : Node(ND(), graph)
        {}

        ~Node() {
            while (lastIn) delete lastIn;
            while (lastOut) delete lastOut;
            if (prev) prev->next = next; else graph.firstNode = next;
            if (next) next->prev = prev; else graph.lastNode = prev;
        }

        std::vector<Link *> outLinks() {
            std::vector<Link *> res;
            for (Link *x=firstOut; x; x=x->nextInFrom) {
                res.push_back(x);
            }
            return res;
        }

        std::vector<Link *> inLinks() {
            std::vector<Link *> res;
            for (Link *x=firstIn; x; x=x->nextInTo) {
                res.push_back(x);
            }
            return res;
        }
    };

    struct Link {
        LD data;
        Node *from, *to;
        Link *prev, *next, *prevInFrom, *nextInFrom, *prevInTo, *nextInTo;
        Link(LD data, Node *from, Node *to)
            : data(std::move(data)),
              from(from), to(to),
              prev(from->graph.lastLink), next(nullptr),
              prevInFrom(from->lastOut), nextInFrom(nullptr),
              prevInTo(to->lastIn), nextInTo(nullptr)
        {
            if (&from->graph != &to->graph) {
                throw std::runtime_error("Cannot link nodes from different graphs");
            }
            if (prev) prev->next = this; else from->graph.firstLink = this;
            from->graph.lastLink = this;
            if (prevInFrom) prevInFrom->nextInFrom = this; else from->firstOut = this;
            from->lastOut = this;
            if (prevInTo) prevInTo->nextInTo = this; else to->firstIn = this;
            to->lastIn = this;
        }

        Link(Node *from, Node *to)
            : Link(LD(), from, to)
        {}

        ~Link() {
            if (prevInTo) prevInTo->nextInTo = nextInTo; else to->firstIn = nextInTo;
            if (nextInTo) nextInTo->prevInTo = prevInTo; else to->lastIn = prevInTo;
            if (prevInFrom) prevInFrom->nextInFrom = nextInFrom; else from->firstOut = nextInFrom;
            if (nextInFrom) nextInFrom->prevInFrom = prevInFrom; else from->lastOut = prevInFrom;
            if (prev) prev->next = next; else from->graph.firstLink = next;
            if (next) next->prev = prev; else from->graph.lastLink = prev;
        }

        Link(const Link&) = delete;
        Link(Link&&) = delete;
        Link& operator=(const Link&) = delete;
    };

    Node *firstNode, *lastNode;
    Link *firstLink, *lastLink;

    Graph()
        : firstNode(nullptr), lastNode(nullptr),
          firstLink(nullptr), lastLink(nullptr)
    {}

    ~Graph() {
        while (lastNode) delete lastNode;
    }

    Graph(const Graph&) = delete;
    Graph(Graph&&) = delete;
    Graph& operator=(const Graph&) = delete;

    Node *addNode(ND data) { return new Node(data, *this); }
    Link *addLink(LD data, Node *from, Node *to) { return new Link(data, from, to); }
    Node *addNode() { return new Node(*this); }
    Link *addLink(Node *from, Node *to) { return new Link(from, to); }
};

#endif
