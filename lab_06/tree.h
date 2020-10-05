#ifndef D_TREE_H
#define D_TREE_H

#include <vector>

class IdTree {
public:
    IdTree() = default;

    ~IdTree() {
        delete_node(head_);
    }

    bool contains(int id) {
        TreeNode* temp = head_;
        while(temp != nullptr) {
            if (temp->id_ == id) {
                break;
            }
            if (id > temp->id_) {
                temp = temp->right;
            }
            if (id < temp->id_) {
                temp = temp->left;
            }
        }
        return temp != nullptr;
    }

    void insert(int id) {
        if (head_ == nullptr) {
            head_ = new TreeNode(id);
            return;
        }
        TreeNode* temp = head_;
        while(temp != nullptr) {
            if (id == temp->id_) {
                break;
            }
            if (id < temp->id_) {
                if (temp->left == nullptr) {
                    temp->left = new TreeNode(id);
                    break;
                }
                temp = temp->left;
            }
            if (id > temp->id_) {
                if (temp->right == nullptr) {
                    temp->right = new TreeNode(id);
                    break;
                }
                temp = temp->right;
            }
        }
    }

    void erase(int id) {
        TreeNode* prev_id = nullptr;
        TreeNode* temp = head_;
        while (temp != nullptr) {
            if (id == temp->id_) {
                if (prev_id == nullptr) {
                    head_ = nullptr;
                } else {
                    if (prev_id->left == temp) {
                        prev_id->left = nullptr;
                    } else {
                        prev_id->right = nullptr;
                    }
                }
                delete_node(temp);

            } else if (id < temp->id_) {
                prev_id = temp;
                temp = temp->left;
            } else if (id > temp->id_) {
                prev_id = temp;
                temp = temp->right;
            }
        }
    }

    std::vector<int> get_nodes() const {
        std::vector<int> result;
        get_nodes(head_, result);
        return result;
    }

private:

    struct TreeNode {
        TreeNode(int id) : id_(id) {}
        int id_;
        TreeNode* left = nullptr;
        TreeNode* right = nullptr;
    };

    void get_nodes(TreeNode* node, std::vector<int>& v) const {
        if (node == nullptr) {
            return;
        }
        get_nodes(node->left,v);
        v.push_back(node->id_);
        get_nodes(node->right, v);
    }

    void delete_node(TreeNode* node) {
        if (node == nullptr) {
            return;
        }
        delete_node(node->right);
        delete_node(node->left);
        delete node;
    }

    TreeNode* head_ = nullptr;
};
#endif