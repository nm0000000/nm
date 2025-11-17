# АЛГОРИТМЫ РЕАЛИЗАЦИИ ДЕРЕВЬЕВ НА PYTHON

# 1. Класс вершины дерева
class Node(object):
    def __init__(self, key):
        self.key = key
        self.left = None
        self.right = None


# 2. Класс дерева
class Tree(object):
    def __init__(self):
        self.root = None


# 3. Поиск ключа в дереве

# Рекурсивная реализация
def search_recursively(v, x):
    if v is None or v.key == x:
        return v
    elif x < v.key:
        return search_recursively(v.left, x)
    else:  # x > v.key
        return search_recursively(v.right, x)

# Нерекурсивная реализация
def search_iteratively(root, x):
    v = root
    while v is not None:
        if v.key == x:
            return v
        elif x < v.key:
            v = v.left
        else:  # x > v.key
            v = v.right
    return None


# 4. Добавление ключа в дерево

# Рекурсивная реализация
def insert_recursively(v, x):
    if v is None:
        return Node(x)
    if x < v.key:
        v.left = insert_recursively(v.left, x)
    elif x > v.key:
        v.right = insert_recursively(v.right, x)
    # v.key == x (ничего не делаем, если ключ уже присутствует)
    return v

tree.root = insert_recursively(tree.root, x)

# Нерекурсивная реализация
def insert_iteratively(x):
    parent = None
    v = tree.root
    while v is not None:
        parent = v
        if x < v.key:
            v = v.left
        elif x > v.key:
            v = v.right
        else:  # x == v.key
            return
    w = Node(x)
    if parent is None:
        tree.root = w
    elif x < parent.key:
        parent.left = w
    elif x > parent.key:
        parent.right = w

# 5. Удаление из дерева.

# Рекурсивная реализация
def delete_recursively(v, x):
    if v is None:
        return None
    if x < v.key:
        v.left = delete_recursively(v.left, x)
        return v
    elif x > v.key:
        v.right = delete_recursively(v.right, x)
        return v
    # v.key == x
    if v.left is None:
        return v.right
    elif v.right is None:
        return v.left
    else:
        # Both subtrees are present
        min_key = find_min(v.right).key
        v.key = min_key
        v.right = delete_recursively(v.right, min_key)
        return v

def find_min(v):
    if v.left is not None:
        return find_min(v.left)
    else:
        return v

# Нерекурсивная реализация
def replace_child(parent, old, new):
    if parent is None:
        tree.root = new
    elif parent.left == old:
        parent.left = new
    elif parent.right == old:
        parent.right = new

def delete_iteratively(x):
    parent = None
    v = tree.root
    while True:
        if v is None:
            return
        if x < v.key:
            parent = v
            v = v.left
        elif x > v.key:
            parent = v
            v = v.right
        else:  # x == v.key
            break
    result = None
    if v.left is None:
        result = v.right
    elif v.right is None:
        result = v.left
    else:
        min_node_parent = v
        min_node = v.right
        while min_node.left is not None:
            min_node_parent = min_node
            min_node = min_node.left
        result = v
        v.key = min_node.key
        replace_child(min_node_parent, min_node, min_node.right)
    replace_child(parent, v, result)
