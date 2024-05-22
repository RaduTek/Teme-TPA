#include <iostream>
#include <fstream>
#include <limits>

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
        fill(data, data + 4 * n, numeric_limits<int>::min());
    }

    ~SegmentTree()
    {
        delete[] data;
    }

    void update(unsigned index, int value, unsigned node, unsigned left, unsigned right)
    {
        if (left == right)
        {
            data[node] = value;
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
            return numeric_limits<int>::min();

        if (qLeft <= left && right <= qRight)
            return data[node];

        unsigned middle = (left + right) / 2;
        int lQuery = query(2 * node, left, middle, qLeft, qRight);
        int rQuery = query(2 * node + 1, middle + 1, right, qLeft, qRight);

        return max(lQuery, rQuery);
    }
};

ifstream fin("arbint.in");
ofstream fout("arbint.out");

int main()
{
    unsigned n, m, a, b;
    int x;
    bool cmd;

    fin >> n >> m;

    SegmentTree st(n);

    // Read items into segment tree
    for (unsigned i = 0; i < n; i++)
    {
        fin >> x;
        st.update(i + 1, x, 1, 1, n);
    }

    // Process commands
    for (unsigned i = 0; i < m; i++)
    {
        fin >> cmd;
        if (cmd)
        {
            fin >> a >> x;
            st.update(a, x, 1, 1, n);
        }
        else
        {
            fin >> a >> b;
            fout << st.query(1, 1, n, a, b) << endl;
        }
    }

    fin.close();
    fout.close();

    return 0;
}