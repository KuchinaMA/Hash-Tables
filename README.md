# Хэш-таблицы: сравнение различных хэш-функций, используемых для реализации хэш-таблиц и оптимизация хэш-таблицы
## Цель
Цель данной практической работы - сравнить, насколько равномерно разные хэш-функции распределяют элементы по ячейкам хэш-таблицы, а также найти "узкие" места программы, работающие долго и ускорить их работу с помощью различных оптимизаций.

## Хэш-таблица
В данной работе реализована хэш-таблица с прямой адресацией, в которой коллизии решаются методом цепочек. При такой реализации в каждой ячейке хранится указатель на список (храним именно списки для решения коллизий: ситуаций, в которых в одну и ту же ячейку хэш-таблицы попадет несколько различных элементов). Для добавления элемента в таблицу с помощью хэш-функции рассчитаем индекс ячейки, в которой он будет находиться и добавим элемент в список, хранящийся в этой ячейке, если такого элемента в списке ещё нет. 

Будем вставлять в таблицу слова из романа О. Уайльда "Портрет Дориана Грея". Текст предварительно отфильтруем следующим образом: уберём цифры, знаки препинания и напишем каждое слово с новой строчки. В полученном тексте ≈10000 различных слов. Для исследовния хэш-таблицы "перегрузим" её, сделав load-фактор ≈5. То есть её размер сделаем ≈2000 (возьмём простое чило, близкое к 2000 - 2011). 

## Часть 1: сравнение хэш-фунций
Производительность написанной хэш-таблицы зависит от того, как хэш-функция распределяет ключи по ячейкам.
Реализуем несколько различных хэш-функций и сравним, как они насколько равномерно они распределяют элементы по ячейкам хэш-таблицы.

Рассматриваемые хэш-функции:
1. [const_hash](#const-hash) - вегда возвращает одно и то же значение;
2. first_letter_hash - возвращает ASCII-код первой буквы строки
3. ASCII_sum_hash - возвращает сумму ASCII-кодов букв строки 
4. strlen_hash - возвращает длину строки
5. rol_hash - возвращает значение, полученное при помощи функции rol - битового вращения влево 
6. ror_hash - возвращает значение, полученное при помощи функции rol - битового вращения вправо
7. crc32_hash - возвращает значение, полученное при помощи алгоритма crc32

Сравнение распределения элементов по ячейкам хэш-таблицы производится слеующим образом:
1. Графически, с помощью построения гистограмм, в которых высота столбца, соответствующего каждой ячейке хэш-таблицы, равна количеству элементов в списке из этой ячейки
2. Количественно, с помощью подсчёта дисперсии длины списка. 

### const_hash {id="const-hash"}
Эта хэш-функция для любого аргумента возвращает 1.
```
uint32_t const_hash(const char* str) {

    return 1;

}
```
Гистограмма выглядит следующим образом:

Все столбцы, кроме одного, имеют нулевую высоту, высота оставшегося столбца равна количесту различных слов в исходном тексте.