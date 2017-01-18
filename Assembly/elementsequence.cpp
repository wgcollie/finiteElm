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
        LocalMatrix(size_t cols, size_t rows):storesize{cols*rows},blocksize{cols};
        LocalMatrix(std::initializer_list<std::initializer_list<float>> mm);
    private:
        size_t cols,rows;
        size_t storesize;
        size_t blocksize;
        std::vector<float> elements;
        friend float& operator()(index_t i, index_t j);        
};

inline std::ostream& operator<<(std::ostream& o, const LocalMatrix& mm)
{
    for(size_t i=0; i<mm.cols; i++) {
        size_t block = i*mm.blocksize;
        for(size_t j=0; j<mm.rows; j++) {
            size_t idx = block + j;
            o<<mm.elements[idx];
        }
        o<<'\n';
    }
}

LocalMatrix::LocalMatrix(std::initializer_list<std::initializer_list<float>> mm)
{
    storesize = cols*rows;
    blocksize = cols;
    elements.reserve(storesize);
    for(size_t i=0;i<cols;i++) {
        size_t block = i*blocksize;
        for(size_t j=0;j<rows;j++) {
            index_t k = block + j;
            elements[k] = xx[i][j];
        }
    }
}

float& LocalMatrix::operator()(index_t i, index_t j)
{
    index_t idx = i*blocksize + j;
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
     float** aa = {{1.0,2.0},{3.0,4.0},{5.0,6.0}};
     LocalMatrix mm(2,3,aa);
     std::cout<<mm;

     std::vector<Node> vv{{101,0.0,NodeType::fixed},{102,0.5,NodeType::free},{103,1.0,NodeType::fixed},{104,1.5,NodeType::fixed}};
     std::vector<Node*> elementNodes{&vv[1],&vv[2]};
     std::cout<<"Sequence version 1\n";
     IterativeSequenceNodeNumbers<Node*> nodeSeq(elementNodes);
     std::cout<<"Size: "<<nodeSeq.size()<<"\n";
     for(auto x:nodeSeq) {
        std::cout<<*x<<"\n";
     }
}
