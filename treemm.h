#ifndef TREEMULTIMAP_INCLUDED
#define TREEMULTIMAP_INCLUDED

#include <vector>

template <typename KeyType, typename ValueType>
class TreeMultimap
{
    struct Node;
  public:
    class Iterator
    {
      public:
        Iterator() //will be used as the invalid interator case
        {
            m_index = 0;
            isValid = false;
            m_values = nullptr;
        }
        
        Iterator(std::vector<ValueType>* values) //otherwise if an Iterator is valid, this constructor will be used
        {
            m_index = 0;
            m_values = values;
            isValid = true;
        }

        ValueType& get_value() const
        {
            return m_values->at(m_index);
        }

        bool is_valid() const
        {
            
            if (m_values == nullptr || m_index >= m_values->size() || isValid == false)
            {
                return false;
            }
            return true;
        }

        void advance()
        {
            m_index++;
        }

      private:
        int m_index;
        std::vector<ValueType>* m_values;
        bool isValid = false;
        
    };

    TreeMultimap()
    {
        m_root = nullptr; //by default
    }

    ~TreeMultimap()
    {
        clearNodes(m_root);
    }
    
    void insert(const KeyType& key, const ValueType& value) //runs O(log N) with the help of recursion
    {
        if (m_root == nullptr)
        {
            m_root = new Node(key, value);
            return;
        }
        
        return insertHelper(key, value, m_root);
        
    }

    Iterator find(const KeyType& key) const //runs O(log N) with the help of recursion
    {
        if (m_root->key == key)
        {
            return Iterator(&m_root->node_value);
        }
        return findHelper(key, m_root);
    }

  private:
    
//    template <typename KeyType, typename ValueType>
    struct Node
    {
        Node(const KeyType newKey, ValueType value)
        {
            key = newKey;
            node_value.push_back(value);
            left = right = nullptr;
        }

        KeyType key;
        std::vector<ValueType> node_value;
        Node* left;
        Node* right;
    };
    
    Node* m_root;
    
    void insertHelper(const KeyType& key, const ValueType& value, Node* &current)
    {
        if (current->key == key) {
            current->node_value.push_back(value);
            return;
        }
        
        else if (current->left == nullptr && current->key > key) {
            Node* newNode = new Node(key, value);
            current->left = newNode;
            return;
        }
        
        else if (current->right == nullptr && current->key < key) {
            Node* newNode = new Node(key, value);
            current->right = newNode;
            return;
        }
        
        else if (current->key < key) {
            insertHelper(key, value, current->right);
            return;
        }
        else if (current->key > key) {
            insertHelper(key, value, current->left);
            return;
        }
    }
    
    Iterator findHelper(const KeyType& key, Node* current) const
    {
        if(current == nullptr) return Iterator();
        
        if (current->key == key) {
            return Iterator(&current->node_value);
        }
        
        else if (current->key < key) {
            return findHelper(key, current->right);
        }
        else if (current->key > key) {
            return findHelper(key, current->left);
        }

        return Iterator();
    }
    
    void clearNodes(Node* node) //function to recursively delete all nodes, gets called in the destructor
    {
        if (node == nullptr) {return;}
        
        clearNodes(node->left);
        clearNodes(node->right);
        
        delete node;
        node = nullptr;
        
    }
    
};

#endif // TREEMULTIMAP_INCLUDED

