#include "tree/Tree.hpp"

#include <vector>

[[nodiscard]] bool AVL::contains(int value) const noexcept {
    return search(value, root) != nullptr;
}

bool AVL::insert(int value) {
    if (contains(value))
        return false;
    root = insert(value, root);
    ++sz;
    return true;
}

bool AVL::remove(int value) {
    if (!contains(value))
        return false;
    root = remove(value, root);
    --sz;
    return true;
}

[[nodiscard]] std::size_t AVL::size() const noexcept {
    return sz;
}

[[nodiscard]] bool AVL::empty() const noexcept {
    return sz == 0;
}

[[nodiscard]] std::vector<int> AVL::values() const noexcept {
    std::vector<int> res;
    values(root, res);
    return res;
}

AVL::~AVL() {
    clear(root);
}

int AVL::height(Node* node) noexcept {
    return node ? node->height : 0;
}

int AVL::balance_factor(Node* node) noexcept {
    return height(node->right) - height(node->left);
}

void AVL::fix_height(Node* node) noexcept {
    node->height = std::max(height(node->left), height(node->right)) + 1;
}

AVL::Node* AVL::rotate_right(Node* p) noexcept {
    Node* q  = p->left;
    p->left  = q->right;
    q->right = p;
    fix_height(p);
    fix_height(q);
    return q;
}

AVL::Node* AVL::rotate_left(Node* q) noexcept {
    Node* p  = q->right;
    q->right = p->left;
    p->left  = q;
    fix_height(q);
    fix_height(p);
    return p;
}

AVL::Node* AVL::balance(Node* p) noexcept {
    fix_height(p);
    if (balance_factor(p) == 2) {
        if (balance_factor(p->right) < 0)
            p->right = rotate_right(p->right);
        return rotate_left(p);
    }
    if (balance_factor(p) == -2) {
        if (balance_factor(p->left) > 0)
            p->left = rotate_left(p->left);
        return rotate_right(p);
    }
    return p;
}

AVL::Node* AVL::insert(int k, Node* p) {
    if (!p)
        return new Node(k);
    if (k < p->key)
        p->left = insert(k, p->left);
    else
        p->right = insert(k, p->right);
    return balance(p);
}

AVL::Node* AVL::find_min(Node* p) const noexcept {
    return p->left ? find_min(p->left) : p;
}

AVL::Node* AVL::remove_min(Node* p) {
    if (p->left == nullptr)
        return p->right;
    p->left = remove_min(p->left);
    return balance(p);
}

AVL::Node* AVL::remove(int k, Node* p) {
    if (!p)
        return nullptr;
    if (k < p->key)
        p->left = remove(k, p->left);
    else if (k > p->key)
        p->right = remove(k, p->right);
    else {
        Node* q = p->left;
        Node* r = p->right;
        delete p;
        if (!r)
            return q;
        Node* min  = find_min(r);
        min->right = remove_min(r);
        min->left  = q;
        return balance(min);
    }
    return balance(p);
}

AVL::Node* AVL::search(int k, Node* p) noexcept {
    while (p) {
        if (k == p->key)
            return p;
        if (k < p->key)
            p = p->left;
        else
            p = p->right;
    }
    return nullptr;
}

void AVL::values(Node* p, std::vector<int>& res) const noexcept {
    if (!p)
        return;
    values(p->left, res);
    res.push_back(p->key);
    values(p->right, res);
}

void AVL::clear(Node* p) noexcept {
    if (p) {
        clear(p->left);
        clear(p->right);
        delete p;
    }
}
