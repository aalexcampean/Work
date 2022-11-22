from Model.Constants import INITIAL_CAPACITY
from Model.Node import Node


class SymbolTable:
    def __init__(self):
        self.__capacity = INITIAL_CAPACITY
        self.__size = 0
        self.__buckets = [None] * self.__capacity

    @property
    def capacity(self):
        return self.__capacity

    @property
    def size(self):
        return self.__size

    @property
    def buckets(self):
        return self.__buckets

    def __hash(self, key):
        hashsum = 0

        # For each character in the key
        for character in key:
            hashsum += ord(character)

        return hashsum % self.__capacity

    def __rehash(self):
        self.__capacity *= 2

        new_buckets = [None] * self.__capacity
        for index in range(self.__capacity // 2):
            node = self.__buckets[index]
            while node is not None:
                # Compute hash value of key
                new_index = self.__hash(node.key)

                # Go to the node corresponding to the hash
                new_node = new_buckets[new_index]

                # If bucket is empty
                if new_node is None:
                    # Create node, add it, return
                    new_buckets[new_index] = Node(node.key)
                else:
                    # Otherwise, we have a collision
                    # Iterate to the end of the linked list at provided index
                    new_prev = new_node
                    while new_node is not None:
                        new_prev = new_node
                        new_node = new_node.next

                    # Add a new node at the end of the list with provided key/value
                    new_prev.next = Node(node.key)

                node = node.next

        self.__buckets = new_buckets

    def insert(self, key):
        # Compute hash value of key
        index = self.__hash(key)

        # Go to the node corresponding to the hash
        node = self.__buckets[index]

        # If bucket is empty
        if node is None:
            # Create node, add it, return
            self.__buckets[index] = Node(key)
            # Increment the size
            self.__size += 1
        else:
            # Otherwise, we have a collision
            # Iterate to the end of the linked list at provided index
            prev = node
            while node is not None:
                # If the key already exists we don't do anything
                if prev.key == key:
                    return
                prev = node
                node = node.next

            # Add a new node at the end of the list with provided key/value
            prev.next = Node(key)

            # Increment the size
            self.__size += 1

        if self.__size / self.__capacity >= 0.7:
            self.__rehash()

    def remove(self, key):
        # Compute hash value of key
        index = self.__hash(key)
        node = self.__buckets[index]
        prev = None

        # Go to the first node in list at the computed index
        while node is not None and node.key != key:
            prev = node
            node = node.next

        # Now the node is either the requested key/value pair or None
        if node is None:
            # The given key was not found
            return None
        else:
            # The given key was found
            self.__size -= 1
            result = node.value

            # Delete this element from the linked list
            if prev is None:
                # The element is the head of the linked list
                self.__buckets[index] = None
            else:
                # The element is inside the linked list
                prev.next = node.next

            # Return the deleted value
            return result

    def getPosition(self, key):
        # Compute hash value of key
        index = self.__hash(key)

        # Initialize the position in the list
        position = 0

        # Go to the first node in list at the computed index
        node = self.__buckets[index]

        # Parse the linked list at this node
        while node is not None and node.key != key:
            node = node.next
            position += 1

        # Now the node is either the requested key/value pair or None
        if node is None:
            # Not found
            return -1, -1
        else:
            # Found - return the data value
            return index, position

    def __contains__(self, key):
        # Compute hash value of key
        index = self.__hash(key)

        # Go to the first node in list at the computed index
        node = self.__buckets[index]

        # Parse the linked list at this node
        while node is not None and node.key != key:
            node = node.next

        # Now the node is either the requested key/value pair or None
        return node is not None

    def __getitem__(self, index):
        return self.__buckets[index]

    def __str__(self):
        return str(self.__buckets)


if __name__ == "__main__":
    st = SymbolTable()
    st.insert('dgg')
    st.insert('dfg')
    st.insert('cvkt')
    print(st[0].key)
    assert(st[0].key == 'dfg')