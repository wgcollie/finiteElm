// clang++ -std=c++11 -stdlib=libc++ -Weverything -Wno-c++98-compat elementsequence.cpp


#include <iostream>
#include <vector>
#include <cstdarg>

using index_t=unsigned long;

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
    };
    return o;
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
class IterativeSequenceNodeNumbers {
    using nodenumbers_t = std::vector<T>;
    public:
        using iterator = typename nodenumbers_t::iterator;
        IterativeSequenceNodeNumbers(const nodenumbers_t nn){nodenumbers = nn;}
        iterator begin(){return nodenumbers.begin();}
        iterator end(){return nodenumbers.end();}
        size_t size(){return nodenumbers.size();}
    private:
        nodenumbers_t nodenumbers;
};

class LocalMatrix {
    public:
        LocalMatrix(size_t dim...);
        float& operator()(index_t dim...);        
    private:
        size_t dimension;
        size_t storesize;
        std::vector<index_t> extents;
        std::vector<size_t> blocksizes;
        std::vector<float> elements;
};

LocalMatrix::LocalMatrix(size_t dim...)
{
    va_list ap;
    va_start(ap,dim);
    dimension = dim;
    storesize = 1;  
    for(size_t i=0;i<dimension;i++) {
        index_t k = va_arg(ap,index_t);
        extents.push_back(k);
        blocksizes.push_back(storesize);
        storesize *= k;
    }
    va_end(ap);

    elements.reserve(storesize);
}

float& LocalMatrix::operator()(index_t ...)
{
    va_list ap;
   // va_start(ap,args);
    index_t idx = 0;
    for(size_t i=0;i<dimension;i++) {
        i = va_arg(ap,index_t);
        idx += blocksizes[i]*i;
    }
    va_end(ap);
    return elements[idx];
}

class Element {
    using nodesequence_t = IterativeSequenceNodeNumbers<Node>;
    public:
        Element(const nodesequence_t nn):nodes(nn){}
    private:
        nodesequence_t nodes;
};

int main()
{
     std::vector<Node> vv{{101,0.0,NodeType::fixed},{102,0.5,NodeType::free},{103,1.0,NodeType::fixed},{104,1.5,NodeType::fixed}};
     std::vector<Node*> elementNodes{&vv[1],&vv[2]};
     std::cout<<"Sequence version 1\n";
     IterativeSequenceNodeNumbers<Node*> nodeSeq(elementNodes);
     std::cout<<"Size: "<<nodeSeq.size()<<"\n";
     for(auto x:nodeSeq) {
        std::cout<<*x<<"\n";
     }
}
