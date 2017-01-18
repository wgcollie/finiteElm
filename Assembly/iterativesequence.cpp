// This version implements a template for the element type.
// A useful extension would allow the container type to
// be parametrized also.

#include <iostream>
#include <vector>

enum class NodeType {fixed,free};

inline std::ostream& operator<<(std::ostream& o, const NodeType& t)
{
    switch (t) {
        case NodeType::fixed:
           o << "fixed";
           break;
        case NodeType::free: 
           o << "free";
           break;
        default: 
           o << (int) t;
           break;
    }
}

struct NodeBasic {
    int id;
    float coordinate;
    NodeType type;     
};

inline std::ostream& operator<<(std::ostream& o, const NodeBasic& nn)
{
    o << "Node: " << nn.id << "," << nn.coordinate << "," << nn.type << " /Node";
    return o; 
}

using Node=NodeBasic;

template<typename T>
class IterativeSequenceNode {
    using nodes_t = std::vector<T>;
    public:
        using iterator = typename nodes_t::iterator;
        IterativeSequenceNode(const nodes_t nn){nodes = nn;}
        iterator begin(){return nodes.begin();}
        iterator end(){return nodes.end();}
        int size(){return nodes.size();}
    private:
        nodes_t nodes;
};

int main()
{
     std::vector<Node> vv{{101,0.0,NodeType::fixed},{102,0.5,NodeType::free},{103,1.0,NodeType::fixed}};
     std::cout<<"Sequence version 1\n";
     IterativeSequenceNode<Node> nodeSeq(vv);
     std::cout<<"Size: "<<nodeSeq.size()<<"\n";
     for(auto x:nodeSeq) {
        std::cout<<x<<"\n";
     }
}
