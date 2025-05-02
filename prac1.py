class LinearProbingHashTable:
    def __init__(self, size):
        self.size = size
        self.table = [None] * size

    def hash(self, key):
        return key % self.size

    def insert(self, key, value):
        index = self.hash(key)
        original_index = index
        while self.table[index] is not None:
            index = (index + 1) % self.size
            if index == original_index:
                print("⚠️ Hash table is full!")
                return
        self.table[index] = (key, value)

    def search(self, key):
        comparisons = 1
        index = self.hash(key)
        while self.table[index] is not None:
            if self.table[index][0] == key:
                return self.table[index][1], comparisons
            index = (index + 1) % self.size
            comparisons += 1
        return None, comparisons


class ChainingHashTable:
    def __init__(self, size):
        self.size = size
        self.table = [[] for _ in range(size)]

    def hash(self, key):
        return key % self.size

    def insert(self, key, value):
        index = self.hash(key)
        self.table[index].append((key, value))

    def search(self, key):
        index = self.hash(key)
        comparisons = 0
        for k, v in self.table[index]:
            comparisons += 1
            if k == key:
                return v, comparisons
        return None, comparisons


# Example usage
clients = {
    1001: "9876543210",
    1002: "9845123456",
    1003: "9123456780",
    1004: "9001234567",
    1005: "9765432109"
}

size = 7
lp_table = LinearProbingHashTable(size)
ch_table = ChainingHashTable(size)

# Insert records
for client_id, phone in clients.items():
    lp_table.insert(client_id, phone)
    ch_table.insert(client_id, phone)

# Search and compare
print("🔍 Search comparisons:")
for cid in clients.keys():
    _, lp_comparisons = lp_table.search(cid)
    _, ch_comparisons = ch_table.search(cid)
    print(f"Client {cid}: Linear Probing = {lp_comparisons}, Chaining = {ch_comparisons}")
