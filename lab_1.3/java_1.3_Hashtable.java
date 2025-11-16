// СОЗДАНИЕ ХЭШ-ТАБЛИЦЫ НА JAVA

import java.util.Hashtable;

class GFG {
    public static void main(String[] args) {
        // Создаем хэш-таблицу с ключами типа String и значениями типа Integer
        Hashtable<String, Integer> ht = new Hashtable<>();
        
        // Добавляем элементы в хэш-таблицу
        ht.put("Ten", 10);
        ht.put("Six", 6);
        ht.put("Two", 2);
        
        // Выводим элементы хэш-таблицы
        System.out.println("Hashtable Elements: " + ht);
    }
}
