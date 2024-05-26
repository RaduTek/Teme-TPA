#include <iostream>
#include <fstream>

using namespace std;

class SegmentTree
{
private:
    unsigned n;
    int *data;

public:
    SegmentTree(unsigned items)
    {
        n = items;
        data = new int[4 * n];
        if (data == NULL)
        {
            perror("Memory allocation error");
            return;
        }
        fill(data, data + 4 * n, 0);
    }

    ~SegmentTree()
    {
        delete[] data;
    }

    void update(unsigned index, int value, unsigned node, unsigned left, unsigned right)
    {
        if (left == right)
        {
            data[node] += value;
            return;
        }

        unsigned middle = (left + right) / 2;
        if (index <= middle)
            update(index, value, 2 * node, left, middle);
        else
            update(index, value, 2 * node + 1, middle + 1, right);

        data[node] = max(data[2 * node], data[2 * node + 1]);
    }

    int query(unsigned node, unsigned left, unsigned right, unsigned qLeft, unsigned qRight)
    {
        if (qLeft > right || qRight < left)
            return 0;

        if (qLeft <= left && right <= qRight)
            return data[node];

        unsigned middle = (left + right) / 2;
        int lQuery = query(2 * node, left, middle, qLeft, qRight);
        int rQuery = query(2 * node + 1, middle + 1, right, qLeft, qRight);

        return max(lQuery, rQuery);
    }

    // unsigned inversions(int value, unsigned node, unsigned left, unsigned right)
    // {
    //     if (data[node] < value)
    //         return 1;

    //     unsigned count = 0;
    //     unsigned middle = (left + right) / 2;

    //     count += inversions(value, 2 * node, left, middle);
    //     count += inversions(value, 2 * node + 1, middle + 1, right);

    //     return count;
    // }

    int inversions(int start, int value)
    {
        return query(1, 1, n, start + 1, n);
    }
};

ifstream fin("inv.in");
ofstream fout("inv.out");

int main()
{
    unsigned n;
    int x;

    fin >> n;

    SegmentTree st(n);
    int *original = new int[n];

    // Read items into segment tree
    for (unsigned i = 0; i < n; i++)
    {
        fin >> x;
        original[i] = x;
        st.update(i + 1, x, 1, 1, n);
    }

    unsigned count = 0;
    // for (unsigned i = 0; i < n; i++)
    // {
    //     count += st.inversions(i, original[i]);
    // }

    for (int i = n - 1; i >= 0; --i)
    {
        if (original[i] > 1)
        {
            count += st.query(1, 1, n, 1, original[i] - 1);
        }
        st.update(original[i], 1, 1, 1, n);
    }

    fout << count % 9917 << endl;

    fin.close();
    fout.close();

    return 0;
}