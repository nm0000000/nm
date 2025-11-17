// РЕАЛИЗАЦИЯ ДЕРЕВЬЕВ НА JAVA

// 1. Внутренний класс вершины дерева
private class Node {
    public int key;
    public Node left;
    public Node right;

    public Node(int key) {
        this.key = key;
    }
}

// 2. Основной класс дерева
class Tree {
    private static class Node {
        int key;
        Node left;
        Node right;
    }

    private Node root;

    // 3. Метод добавления элемента в дерево
    // Рекурсивная реализация
    public void insert(int x) {
        root = doInsert(root, x);
    }

    private static Node doInsert(Node node, int x) {
        if (node == null) {
            return new Node(x);
        }
        if (x < node.key) {
            node.left = doInsert(node.left, x);
        } else if (x > node.key) {
            node.right = doInsert(node.right, x);
        }
        return node;
    }

    // Нерекурсивная реализация
    public void insertIterative(int x) {
        Node parent = null;
        Node node = root;
        while (node != null) {
            parent = node;
            if (x < node.key) {
                node = node.left;
            } else if (x > node.key) {
                node = node.right;
            } else {
                return; // Элемент уже существует
            }
        }
        Node newNode = new Node(x);
        if (parent == null) {
            root = newNode;
        } else if (x < parent.key) {
            parent.left = newNode;
        } else if (x > parent.key) {
            parent.right = newNode;
        }
    }
}
