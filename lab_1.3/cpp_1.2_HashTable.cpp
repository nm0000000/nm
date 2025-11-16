// РЕАЛИЗАЦИЯ ХЭШ-ТАБЛИЦЫ НА C++

#include <iostream>
#include <list>
#include <string>

using namespace std;

template<typename K, typename V>
class HashTable {
private:
    static constexpr unsigned int TABLE_SIZE = 100; // размер таблицы (можно изменить)
    
    // Узел пары ключ-значение
    class Entry {
    public:
        K key;
        V value;
        Entry(K k, V v) : key(k), value(v) {}
    };

    // Массив списков (цепочка коллизий)
    list<Entry> table[TABLE_SIZE];

    // Простая хеш-функция (рекомендуется заменить более качественной функцией)
    unsigned int hash(const K &key) const {
        return key % TABLE_SIZE;
    }

public:
    // Вставляем пару ключ-значение
    void put(const K &key, const V &value) {
        unsigned int idx = hash(key);
        for(auto &entry : table[idx]) {
            if(entry.key == key) {
                entry.value = value; // обновляем значение, если ключ существует
                return;
            }
        }
        table[idx].push_back({key, value}); // иначе добавляем новую запись
    }

    // Получаем значение по ключу
    V get(const K &key) const {
        unsigned int idx = hash(key);
        for(const auto &entry : table[idx]) {
            if(entry.key == key) {
                return entry.value;
            }
        }
        throw out_of_range("No such key in the hash table");
    }

    // Проверяем наличие ключа
    bool contains(const K &key) const {
        unsigned int idx = hash(key);
        for(const auto &entry : table[idx]) {
            if(entry.key == key) {
                return true;
            }
        }
        return false;
    }

    // Удаляем пару по ключу
    void remove(const K &key) {
        unsigned int idx = hash(key);
        for(auto it = table[idx].begin(); it != table[idx].end(); ++it) {
            if((*it).key == key) {
                table[idx].erase(it);
                return;
            }
        }
    }

    // Отображаем содержимое хеш-таблицы
    void display() const {
        for(unsigned int i = 0; i < TABLE_SIZE; ++i) {
            if(!table[i].empty()) {
                cout << "Bucket [" << i << "]:\\n";
                for(const auto &entry : table[i]) {
                    cout << "\\tKey: " << entry.key << ", Value: " << entry.value << '\\n';
                }
            }
        }
    }
};

int main() {
    HashTable<string, string> ht;

    ht.put("apple", "яблоко");
    ht.put("banana", "банан");
    ht.put("grape", "виноград");

    try {
        cout << "Значение 'apple': " << ht.get("apple") << '\\n'; // яблоко
        cout << "Значение 'banana': " << ht.get("banana") << '\\n'; // банан
    } catch(out_of_range e) {
        cerr << e.what() << '\\n';
    }

    ht.display();

    ht.remove("banana");
    cout << "После удаления banana:\\n";
    ht.display();

    return 0;
}
