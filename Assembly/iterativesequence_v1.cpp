// This version implements a template for the element type.
// A useful extension would allow the container type to
// be parametrized also.

#include <iostream>
#include <vector>

using Node=int;

template<typename T>
class IterativeSequenceNode {
    using nodes_t = std::vector<T>;
    public:
        using iterator = typename nodes_t::iterator;
        IterativeSequenceNode():nodes{2,4,6,8}{std::cout<<"IterativeSequence Started\n";}
        iterator begin(){return nodes.begin();}
        iterator end(){return nodes.end();}
        int size(){return nodes.size();}
    private:
        nodes_t nodes;
};

int main()
{
     std::cout<<"Sequence version 1\n";
     IterativeSequenceNode<Node> nodeSeq;
     std::cout<<"Size: "<<nodeSeq.size()<<"\n";
     for(auto x:nodeSeq) {
        std::cout<<x<<"\n";
     }
}
