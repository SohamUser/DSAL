class HashNode:
    def __init__(self, key, value):
        self.key = key
        self.value = value

class Dictionary:
    def __init__(self, capacity=10):
        self.capacity = capacity
        self.table = [[] for _ in range(self.capacity)]  # chaining

    def hash_function(self, key):
        return hash(key) % self.capacity

    def insert(self, key, value):
        index = self.hash_function(key)
        # Check for existing key (unique keys only)
        for node in self.table[index]:
            if node.key == key:
                raise KeyError(f"Key '{key}' already exists.")
        self.table[index].append(HashNode(key, value))
        print(f"Inserted ({key}, {value}) at index {index}")

    def find(self, key):
        index = self.hash_function(key)
        for node in self.table[index]:
            if node.key == key:
                return node.value
        raise KeyError(f"Key '{key}' not found.")

    def delete(self, key):
        index = self.hash_function(key)
        for i, node in enumerate(self.table[index]):
            if node.key == key:
                del self.table[index][i]
                print(f"Deleted key '{key}' from index {index}")
                return
        raise KeyError(f"Key '{key}' not found.")

    def display(self):
        print("\nHash Table:")
        for i, chain in enumerate(self.table):
            print(f"Index {i}:", [(node.key, node.value) for node in chain])

# Example usage
if __name__ == "__main__":
    d = Dictionary()

    d.insert("apple", 100)
    d.insert("banana", 200)
    d.insert("orange", 300)
    d.insert("grape", 400)

    d.display()

    print("\nFind 'banana':", d.find("banana"))

    d.delete("banana")
    d.display()

    # Uncommenting this will raise error
    # d.insert("apple", 150)  # Key already exists
    # print(d.find("banana"))  # Key not found
