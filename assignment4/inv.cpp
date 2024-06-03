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
        if (qLeft <= left && right <= qRight)
            return data[node];

        if (qLeft > right || qRight < left)
            return 0;

        unsigned middle = (left + right) / 2;
        int lQuery = query(2 * node, left, middle, qLeft, qRight);
        int rQuery = query(2 * node + 1, middle + 1, right, qLeft, qRight);

        return lQuery + rQuery;
    }

    int inversions(int start)
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
    unsigned count = 0;

    // Read items into segment tree
    for (unsigned i = 0; i < n; i++)
    {
        fin >> x;
        original[i] = x;

        st.update(i, x, 1, 1, n);

        count += st.inversions(i);
    }

    fout << count % 9917 << endl;

    fin.close();
    fout.close();

    return 0;
}