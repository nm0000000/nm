#СОЗДАНИЕ МУЛЬТИСПИСКА НА ЯЗЫКЕ PYTHON
groups = [['яблоки', 'груши', 'бананы'], ['чай', 'кофе', 'сок'], ['шоколад', 'конфеты', 'пирожные']]
names = []
for group in groups:
    for name in group:
        names.append(name)
print(names)



#СОЗДАНИЕ ОЧЕРЕДИ НА ЯЗЫКЕ PYTHON
from queue import Queue 
q = Queue() 
q.put(5) 
q.put(10) 
q.put(15) 
while not q.empty(): 
    print(q.get())



#СОЗДАНИЕ ДЕКА НА ЯЗЫКЕ PYTHON
from collections import deque
tasks = deque()
# Добавляем задачи в очередь
tasks.append("5")
tasks.append("10")
tasks.append("15")
# Обработка задач в порядке FIFO
while tasks:
    current_task = tasks.popleft()
    print(f"Выполняется: {current_task}")



#СОЗДАНИЕ ПРИОРИТЕТНОЙ ОЧЕРЕДИ НА ЯЗЫКЕ PYTHON (вариант 1)
from queue import PriorityQueue
# Создать приоритетную очередь
q = PriorityQueue()
# Добавить элементы в очередь с приоритетом
q.put((2, 'mid-priority item')) 
q.put((1, 'high-priority item')) 
q.put((3, 'low-priority item'))
# Удалить и вывести элементы в порядке приоритета
while not q.empty(): 
    item = q.get()
    print(item)
    
#СОЗДАНИЕ ПРИОРИТЕТНОЙ ОЧЕРЕДИ НА ЯЗЫКЕ PYTHON (вариант 2)
import heapq   
customers =   
heapq.heappush(customers, (2, "яблоко")) 
heapq.heappush(customers, (3, "груша")) 
heapq.heappush(customers, (1, "арбуз")) 
heapq.heappush(customers, (4, "банан")) 
while customers: 
    print(heapq.heappop(customers))
