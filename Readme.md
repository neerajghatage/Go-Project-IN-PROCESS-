Aggregation Trees

Overview

Aggregation Trees are an efficient way to compute statistics on raw data. Instead of visiting every record in a dataset for each computation, the tree structure allows us to aggregate data incrementally, making operations much faster. This implementation uses an n-ary tree structure where nodes represent distinct values in a dataset's hierarchical columns (e.g., fname, bnum, and os).

The key innovation is that common nodes are shared among parents. This shared structure minimizes redundancy and maximizes efficiency during aggregation and lookup operations.

----------------------------------------------------------------------------------------------------------------------------------------------------------------

Features

1.Tree Structure: The tree is built from JSON records, with each node representing a unique value for a specific attribute (e.g., fname, bnum, or os).

2.Dynamic Aggregation: Each node maintains the cumulative sum (pr_sum) of the pr values of all records passing through that node.

3.Group By Operation: A computeGroupby function calculates statistics for any specified column (fname, bnum, or os) efficiently by traversing the tree.

4.Shared Nodes: Nodes with the same value and type are reused across the tree, significantly reducing memory usage and computation overhead.


-----------------------------------------------------------------------------------------------------------------------------------------------------------------


Code Overview

Classes and Functions

1.Record** Struct**:
Represents a single record in the dataset with fields fname, bnum, os, and pr.

2.TreeNode** Class**:

Represents a node in the tree.

Stores the node's value, type (e.g., fname, bnum, os), aggregated pr_sum, and child nodes.

3.StatisticsTree** Class**:

Manages the entire tree structure.

insert: Inserts a record into the tree, updating pr_sum values as necessary.

computeGroupby: Computes aggregated statistics for a specified column by traversing relevant nodes.

4.main** Function**:

Demonstrates the tree's functionality by inserting sample records and computing group-by statistics for fname, bnum, and os.


----------------------------------------------------------------------------------------------------------------------------------------------------------------


Advantages of the N-ary Tree Approach

Efficiency: By aggregating values at each node, repeated computations are avoided, significantly speeding up statistics queries.

Shared Nodes: Common nodes are reused for different parents, reducing memory usage and ensuring efficient updates.

Scalability: The tree structure can handle large datasets efficiently, as insertions and queries operate at the node level.

Flexibility: Supports group-by operations for multiple attributes without requiring schema changes.


-----------------------------------------------------------------------------------------------------------------------------------------------------------------


Sample Input

The input is a JSON array of records:

[
    {"fname": "sam", "bnum": "batch-1", "os": "iOS", "pr": 23},
    {"fname": "john", "bnum": "batch-2", "os": "iOS", "pr": 14},
    {"fname": "sam", "bnum": "batch-2", "os": "win", "pr": 15},
    {"fname": "sam", "bnum": "batch-1", "os": "linux", "pr": 22}
]


-----------------------------------------------------------------------------------------------------------------------------------------------------------------------


Sample Output

After processing the above input, the following group-by statistics are generated:

Group by fname

sam: 60
john: 14

Group by bnum

batch-1: 45
batch-2: 29

Group by os

iOS: 37
win: 15
linux: 22