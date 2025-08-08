#include <bits/stdc++.h>
using namespace std;
#define ll long long

struct Node
{
    Node *links[26];
    int arr[26]; // to store word index
    bool flag = false;
    int flag_track = 0; // to store the word index

    Node();  // Constructor
    ~Node(); // Destructor
    Node *moveNext(char ch);
    bool contains(char ch);
    bool valid(char ch, int mx);
};

Node::Node()
{
    for (int i = 0; i < 26; ++i)
        links[i] = nullptr;
    memset(arr, 0, sizeof(arr));
}

Node::~Node()
{
    for (int i = 0; i < 26; ++i)
        delete links[i];
}

Node *Node::moveNext(char ch)
{
    return links[ch - 'a'];
}

bool Node::contains(char ch)
{
    return (links[ch - 'a'] != NULL);
}

bool Node::valid(char ch, int mx)
{
    return (arr[ch - 'a'] <= mx);
}

class Trie
{

private:
    Node *root;

public:
    Trie();  // Constructor
    ~Trie(); // Destructor
    void Insert(string &s, int track);
    void BuildAns(string &s, int mx, string &tmp);
};

Trie::Trie()
{
    root = new Node();
}

Trie::~Trie()
{
    delete root;
}

void Trie::Insert(string &s, int track)
{
    Node *t = root;
    int n = s.size();
    for (int i = 0; i < n; i++)
    {
        char ch = s[i];
        if (!t->contains(ch))
        {
            t->links[ch - 'a'] = new Node();
            t->arr[ch - 'a'] = track;
        }
        t = t->moveNext(ch);
    }
    if (t->flag == false)
    {
        t->flag = true;
        t->flag_track = track;
    }
}

void Trie::BuildAns(string &s, int mx, string &tmp)
{
    Node *t = root;
    int n = s.size();
    for (int i = 0; i < n; i++)
    {
        char ch = s[i];
        if (t->contains(ch) && t->valid(ch, mx))
        {
            tmp.push_back(ch);
            t = t->moveNext(ch);
        }
        else
        {
            break;
        }
    }

    char ch;
    while (true)
    {
        if (t->flag == true && t->flag_track <= mx)
            return;

        for (ch = 'a'; ch <= 'z'; ch++)
        {
            if (t->contains(ch) && t->valid(ch, mx))
            {
                tmp.push_back(ch);
                t = t->moveNext(ch);
                break;
            }
        }
        if (t->flag == true && t->flag_track <= mx)
            return;
        if (!t->contains('a'))
            break; // No further valid characters
    }
}

int main()
{

    Trie trie;
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        string s;
        cin >> s;
        trie.Insert(s, i);
    }
    int q;
    cin >> q;
    while (q--)
    {
        int mx;
        cin >> mx;
        string s;
        cin >> s;
        string tmp;
        trie.BuildAns(s, mx, tmp);
        cout << tmp << "\n";
    }
}
