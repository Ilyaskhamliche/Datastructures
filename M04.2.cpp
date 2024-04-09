#include <iostream>
#include <chrono>
#include <vector>
#include <random>

using namespace std;
using namespace std::chrono;

// Node structure for linked list
struct Node {
    int data;
    Node* next;
    Node(int x) : data(x), next(nullptr) {}
};

// Linked List class
class LinkedList {
private:
    Node* head;

public:
    LinkedList() : head(nullptr) {}

    // Append a new node to the end of the list
    void append(int data) {
        Node* new_node = new Node(data);
        if (head == nullptr) {
            head = new_node;
            return;
        }
        Node* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = new_node;
    }

    // Selection sort
    void selection_sort() {
        Node* current = head;
        while (current != nullptr) {
            Node* min_node = current;
            Node* temp = current->next;
            while (temp != nullptr) {
                if (temp->data < min_node->data) {
                    min_node = temp;
                }
                temp = temp->next;
            }
            int min_data = min_node->data;
            min_node->data = current->data;
            current->data = min_data;
            current = current->next;
        }
    }

    // Merge sort
    void merge_sort() {
        head = merge_sort_helper(head);
    }

private:
    Node* merge_sort_helper(Node* head) {
        if (head == nullptr || head->next == nullptr) {
            return head;
        }

        Node* middle = get_middle(head);
        Node* next_to_middle = middle->next;
        middle->next = nullptr;

        Node* left = merge_sort_helper(head);
        Node* right = merge_sort_helper(next_to_middle);

        return merge(left, right);
    }

    Node* get_middle(Node* head) {
        if (head == nullptr) {
            return head;
        }
        Node* slow = head;
        Node* fast = head;
        while (fast->next != nullptr && fast->next->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }
        return slow;
    }

    Node* merge(Node* left, Node* right) {
        Node* result = nullptr;
        if (left == nullptr) {
            return right;
        }
        if (right == nullptr) {
            return left;
        }
        if (left->data <= right->data) {
            result = left;
            result->next = merge(left->next, right);
        } else {
            result = right;
            result->next = merge(left, right->next);
        }
        return result;
    }

public:
    // Print the linked list
    void print_list() {
        Node* current = head;
        while (current != nullptr) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    // Destructor
    ~LinkedList() {
        Node* current = head;
        while (current != nullptr) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
    }
};

// Function to generate a random list of given size
vector<int> generate_list(int size) {
    vector<int> lst;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 1000);
    for (int i = 0; i < size; i++) {
        lst.push_back(dis(gen));
    }
    return lst;
}

// Function to test sorting algorithms
void test_sorts(const vector<int>& sizes) {
    for (int size : sizes) {
        cout << "List Size: " << size << endl;
        vector<int> lst = generate_list(size);

        // Selection Sort
        LinkedList ll_selection;
        for (int num : lst) {
            ll_selection.append(num);
        }
        auto start = high_resolution_clock::now();
        ll_selection.selection_sort();
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(end - start).count();
        cout << "Selection Sort Time (ms): " << duration << endl;

        // Merge Sort
        LinkedList ll_merge;
        for (int num : lst) {
            ll_merge.append(num);
        }
        start = high_resolution_clock::now();
        ll_merge.merge_sort();
        end = high_resolution_clock::now();
        duration = duration_cast<milliseconds>(end - start).count();
        cout << "Merge Sort Time (ms): " << duration << endl;
    }
}

int main() {
    vector<int> list_sizes = {1, 10, 100, 1000};
    test_sorts(list_sizes);
    return 0;
}
