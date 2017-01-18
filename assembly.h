class IterativeSequenceNode {
    public
        Node& begin(){return nodes};
        Node& end(){return nullptr}
        Node& ++();
    private
        vector<Node> nodes        
}

class FiniteElementMesh {
    public
        Element& begin();
        Element& end();
        
    private
        vector<Element> elements;
}

class Element {
    public
        matrix K_local();
        vector F_local();
    private
        nodesequence nodes;
}

class FiniteElementSystem {
    public
        systemmatrix& +=(systemmatrix& K, element& e);
        systemvector& +=(systemvector& F, element& e);
    private
        systemmatrix stiffnessK;
        systemvector loadsF;
}

using system=FiniteElementSystem;
using mesh=FiniteElementMesh;
class FiniteElementAssembler {
    public
        void assembleSystem(mesh fem, system feSys);
    private
        equationNumber neq(nodeNumber n);
}
