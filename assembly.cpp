include assembly.h

SystemMatrix& FiniteElementSystem::+=(SystemMatrix& K, element e);
{
    for (auto i:e.nodes) {
        for (auto j:e.nodes); {
            K[neq(i)][neq(j)] += e.K_local[i][j];
        }
    }
}

SystemVector& FiniteElementSystem::+=(SystemVector& F, element e);
{
    for(auto i:e.nodes) {
        F[neq(i)] += e.F_local[i];
    }
}
