from itertools import chain


def rotateL(xs, n=1):
    return xs[n:] + xs[:n]

def sortedT(*xs):
    return tuple(sorted(xs))


corners = ['A', 'C', 'I', 'G']
middles = ['B', 'F', 'H', 'D']
centers = ['E']

walls = list(chain.from_iterable(zip(corners, middles)))
vertices = corners + middles + centers


# An undirected, irreflexive graph represented as a set of edges (u, v) where u < v
# with optional dependencies `k`:
# if `k` is a dependency and `k` is not yet in the graph walk,
#    then its corresponding edge `(u, v)` is not available for traversal
edges = {
    (u, v): None
    for u in vertices
    for v in vertices
    if u < v
}

# horizontal & vertical dependencies between corners
edges.update({
    sortedT(u, v): k
    for (u, v, k) in
    zip(
        corners,
        rotateL(corners, n=1),
        middles,
    )
})

# diagonal dependencies between all vertices surrounding the center (the "walls")
edges.update({
    sortedT(u, v): centers[0]
    for (u, v) in
    zip(
        walls,
        rotateL(walls, n=4),
    )
})


def dfs(u, n, available):
    if n == 0:
        return 0
    if n == 1:
        return 1
    return sum(
        dfs(v, n-1, available - {u})
        for v in vertices
        if u != v
        if v in available
        if edges[sortedT(u, v)] not in available
    )


def count_patterns_from(firstPoint, length):
    return dfs(firstPoint, length, set(vertices))
