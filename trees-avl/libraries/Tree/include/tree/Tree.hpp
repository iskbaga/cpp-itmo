#ifndef TREE_HPP
#define TREE_HPP

#include <cstddef>
#include <cstdint>
#include <vector>

class AVL {
public:
    AVL() : root(nullptr), sz(0) {}
    [[nodiscard]] bool contains(int value) const noexcept;
    bool insert(int value);
    bool remove(int value);

    [[nodiscard]] std::size_t size() const noexcept;
    [[nodiscard]] bool empty() const noexcept;
    [[nodiscard]] std::vector<int> values() const noexcept;
    ~AVL();

private:
    struct Node;
    Node* root;
    std::size_t sz;
    static int height(Node* node) noexcept;
    static int balance_factor(Node* node) noexcept;
    static void fix_height(Node* node) noexcept;
    static Node* rotate_right(Node* p) noexcept;
    static Node* rotate_left(Node* q) noexcept;
    static Node* balance(Node* p) noexcept;
    Node* insert(int k, Node* p);
    Node* find_min(Node* p) const noexcept;
    Node* remove_min(Node* p);
    Node* remove(int k, Node* p);
    static Node* search(int k, Node* p) noexcept;
    void values(Node* p, std::vector<int>& res) const noexcept;
    void clear(Node* p) noexcept;

    struct Node {
        int key;
        int height;
        Node* left;
        Node* right;
        explicit Node(int k) : key(k), height(1), left(nullptr), right(nullptr) {}
    };
};

#endif
