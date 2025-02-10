#include "LinkedList.h"

bool LinkedList::insert(int value)
{
    if (!isUnique(value))
        return false;
    insertSorted(head, value);
    ++list_size;
    return true;
}

size_t LinkedList::size() const
{
    return list_size;
}

std::optional<size_t> LinkedList::search(int value) const
{
    size_t position = 1;
    for (Node *current = head.get(); current; current = current->next.get())
    {
        if (current->data == value)
            return position;
        ++position;
    }
    return std::nullopt;
}

bool LinkedList::remove(int value)
{
    Node *prev = nullptr;
    Node *current = head.get();
    while (current)
    {
        if (current->data == value)
        {
            if (prev)
            {
                prev->next = std::move(current->next);
            }
            else
            {
                head = std::move(current->next);
            }
            --list_size;
            return true;
        }
        prev = current;
        current = current->next.get();
    }
    return false;
}

bool LinkedList::edit(int oldValue, int newValue)
{
    if (!isUnique(newValue) || !remove(oldValue))
        return false;
    insert(newValue);
    return true;
}

void LinkedList::clear()
{
    while (head)
    {
        head = std::move(head->next);
    }
    list_size = 0;
}

void LinkedList::insertSorted(std::unique_ptr<Node> &node, int value)
{
    if (!node || node->data > value)
    {
        auto newNode = std::make_unique<Node>(value);
        newNode->next = std::move(node);
        node = std::move(newNode);
    }
    else
    {
        insertSorted(node->next, value);
    }
}

bool LinkedList::isUnique(int value) const
{
    return !search(value).has_value();
}
