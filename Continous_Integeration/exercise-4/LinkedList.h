#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <memory>
#include <optional>

class LinkedList
{
public:
    LinkedList() = default;
    ~LinkedList() { clear(); }

    // Delete copy constructor and copy assignment
    LinkedList(const LinkedList &) = delete;
    LinkedList &operator=(const LinkedList &) = delete;

    // Allow move constructor and move assignment
    LinkedList(LinkedList &&) noexcept = default;
    LinkedList &operator=(LinkedList &&) noexcept = default;

    bool insert(int value);
    size_t size() const;
    std::optional<size_t> search(int value) const;
    bool remove(int value);
    bool edit(int oldValue, int newValue);
    void clear();

private:
    struct Node
    {
        int data;
        std::unique_ptr<Node> next;
        Node(int val) : data(val), next(nullptr) {}
    };

    std::unique_ptr<Node> head = nullptr;
    size_t list_size = 0;

    void insertSorted(std::unique_ptr<Node> &node, int value);
    bool isUnique(int value) const;
};

#endif // LINKEDLIST_H
