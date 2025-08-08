
#include <bits/stdc++.h>
using namespace std;

class NumArray
{

    vector<int> seg;
    int n;

    void buildTree(vector<int> &nums, int pos, int left, int right)
    {
        if (left == right)
        {
            seg[pos] = nums[left];
            return;
        }
        int mid = (left + right) / 2;
        buildTree(nums, 2 * pos + 1, left, mid);
        buildTree(nums, 2 * pos + 2, mid + 1, right);
        seg[pos] = seg[2 * pos + 1] + seg[2 * pos + 2];
    }

    // Function to update a node in the segment tree
    // When a node is updated, then the change in the node value has to be
    // propagated to the root left, right -> represents the range of the node of
    // segment tree. (Ex: [0, n-1] -> root) pos       -> represents "position"
    // in the segment tree data structure (Ex: 0 -> root) Using left, right and
    // pos -> we have all the information on the segment tree Node at 'pos' in
    // segment tree will have children at 2pos+1(left) and 2pos+2(right)

    // If index is less than left or more than right, then it is out of bound
    //      for this node's range so we ignore it and return (This makes the
    //      algo O(logn))
    // If left==right==index, then we found the index,
    //      update the value of the segment tree node & return
    // Otherwise, we need to find the index and we do this by checking child
    // nodes (2pos+1, 2pos+2)
    //      update the segment tree pos with the updated child values' sum.
    //      This would help propagate the updated value of the chid indexes to
    //      the parent (through recursion)

    // in worst case O(logN) nodes will be affected in the segment tree for a
    // single update query

    void updateUtil(int pos, int left, int right, int index, int val)
    {
        // no overlap
        if (index < left || index > right)
            return;

        // total overlap
        if (left == right)
        {
            if (left == index)
                seg[pos] = val;
            return;
        }

        // partial overlap
        int mid = (left + right) / 2;
        updateUtil(2 * pos + 1, left, mid, index, val);      // left child
        updateUtil(2 * pos + 2, mid + 1, right, index, val); // right child
        seg[pos] = seg[2 * pos + 1] + seg[2 * pos + 2];
    }

    // Function to get the sum from the range [qlow, qhigh]
    // low, high -> represents the range of the node of segment tree. (Ex: [0,
    // n-1] -> root) pos       -> represents "position" in the segment tree data
    // structure (Ex: 0 -> root) Using low, high and pos -> we have all the
    // information on the segment tree Node at 'pos' in segment tree will have
    // children at 2pos+1(left) and 2pos+2(right)

    // While searching for the range, there will be three cases: (Ex: arr: [-1,
    // 4, 2, 0])
    //  - Total Overlap:    Return the value. (Ex: qlow, qhigh: 0,3 and low,
    //  high: 1,2)
    //  - No Overlap:       Return 0. (Ex: qlow, qhigh: 0,1 and low, high: 2,3)
    //  - Partial Overlap:  Search for it in both the child nodes and their
    //  ranges.
    //                      (Ex: Searching for 1,2 and node range is 0,1)

    //  int rangeUtil(int qlow, int qhigh, int low, int high, int pos){
    //     if (qlow <= low && qhigh>= high){ // total overlap
    //         return seg[pos];
    //     }
    //     if (qlow > high || qhigh < low) { // no overlap
    //         return 0;
    //     }
    //     // partial overlap
    //     int mid = (high+low)/2;
    //     return (rangeUtil(qlow, qhigh, low, mid, 2*pos+1) + rangeUtil(qlow,
    //     qhigh, mid+1, high, 2*pos+2));
    // }

    int rangeUtil(int left, int right, int qleft, int qRight, int pos)
    {
        // complete overlap
        if (qleft <= left && qRight >= right)
        {
            return seg[pos];
        }

        if (qleft > right || qRight < left)
        {
            return 0;
        }

        int mid = (left + right) / 2;
        int ans = rangeUtil(left, mid, qleft, qRight, 2 * pos + 1) +
                  rangeUtil(mid + 1, right, qleft, qRight, 2 * pos + 2);

        return ans;
    }

public:
    // Constructor for initializing the variables.
    NumArray(vector<int> &nums)
    {
        n = nums.size();
        seg.resize(4 * n, 0); // Maximum size of a segment tree for an array
                              // of size n is 4n
        buildTree(nums, 0, 0, n - 1);
    }

    // Update the segment Tree recurively using updateUtil
    void update(int index, int val) { updateUtil(0, 0, n - 1, index, val); }

    // Get the sum for a specific range for the segment Tree
    int sumRange(int left, int right)
    {
        return rangeUtil(0, n - 1, left, right, 0);
    }
};
