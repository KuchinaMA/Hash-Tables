# Хэш-таблицы: сравнение различных хэш-функций, используемых для реализации хэш-таблиц и оптимизация хэш-таблицы
## Цель
Цель данной практической работы - сравнить, насколько равномерно разные хэш-функции распределяют элементы по ячейкам хэш-таблицы, а также найти "узкие" места программы, работающие долго и ускорить их работу с помощью различных оптимизаций.

## Хэш-таблица
В данной работе реализована хэш-таблица с прямой адресацией, в которой коллизии решаются методом цепочек. При такой реализации в каждой ячейке хранится указатель на список (храним именно списки для решения коллизий: ситуаций, в которых в одну и ту же ячейку хэш-таблицы попадет несколько различных элементов). Для добавления элемента в таблицу с помощью хэш-функции рассчитаем индекс ячейки, в которой он будет находиться и добавим элемент в список, хранящийся в этой ячейке, если такого элемента в списке ещё нет. 

Будем вставлять в таблицу слова из романа О. Уайльда "Портрет Дориана Грея". Для удобства дальнейшей работы текст предварительно отфильтруем следующим образом: уберём цифры, знаки препинания, заменим буквы верхнего регистра на буквы нижнего регистра и напишем каждое слово с новой строчки. В полученном тексте ≈10000 различных слов. Для исследовния хэш-таблицы "перегрузим" её, сделав load-фактор ≈5. То есть её размер сделаем ≈2000 (возьмём простое чило, близкое к 2000 - 2011). 

## Часть 1: сравнение хэш-фунций
Производительность написанной хэш-таблицы зависит от того, как хэш-функция распределяет ключи по ячейкам.
Реализуем несколько различных хэш-функций и сравним, как они насколько равномерно они распределяют элементы по ячейкам хэш-таблицы.

Рассматриваемые хэш-функции:
1. [const_hash](#const-hash) - вегда возвращает одно и то же значение;
2. [first_letter_hash](#first-letter-hash)- возвращает ASCII-код первой буквы строки;
3. [ASCII_sum_hash](#ASCII-sum-hash) - возвращает сумму ASCII-кодов букв строки; 
4. [strlen_hash](#strlen-hash) - возвращает длину строки;
5. [rol_hash](#rol-hash) - возвращает значение, полученное при помощи функции rol - битового вращения влево; 
6. [ror_hash](#rol-hash) - возвращает значение, полученное при помощи функции rol - битового вращения вправо;
7. [crc32_hash](#crc32-hash) - возвращает значение, полученное при помощи алгоритма crc32.

Сравнение распределения элементов по ячейкам хэш-таблицы производится слеующим образом:
1. Графически, с помощью построения гистограмм, в которых высота столбца, соответствующего каждой ячейке хэш-таблицы, равна количеству элементов в списке из этой ячейки
2. Количественно, с помощью подсчёта дисперсии длины списка. 

<a name="const-hash"></a>
### 1. const_hash 
Эта хэш-функция для любого аргумента возвращает 1.
```
uint32_t const_hash(const char* str) {

    return 1;

}
```
Гистограмма выглядит следующим образом:

Все столбцы, кроме одного, имеют нулевую высоту, высота оставшегося столбца равна количесту различных слов в исходном тексте.


<a name="first-letter-hash"></a>
### 2. first_letter_hash
Данная хэш-функция возвращает ASCII-код первой буквы слова.
```
uint32_t first_letter_hash(const char* str) {

    return (uint32_t)str[0];

}
```
В этом случае распределение лучше, чем в предыдущем, но всё равно не очень хорошее, так как всегда заполняется ограниченное колиество ячеек: от ячейки с номером 97 (ASCII-код буквы "a") до ячейки с номером 122 (ASCII-код буквы "z").

<a name="ASCII-sum-hash"></a>
### 3. ASCII_sum_hash
Эта хэш-функция возвращает сумму ASCII-кодов всех букв в слове.
```
uint32_t ASCII_sum_hash(const char* str) {

    int str_length = strlen(str);
    uint32_t hash_sum = 0;

    for (int i = 0; i < str_length; i++) {
        hash_sum += (uint32_t)str[i];
    }

    return hash_sum;
}
```
<a name="strlen-hash"></a>
### 4. strlen_hash
Эта хэш-функция в качестве значения возвращает длину слова.
```
uint32_t strlen_hash(const char* str) {

    return (uint32_t)strlen(str);

}
```


Она также имеет не очень хорошее распределение в силу того, что заполняются далеко не все ячейки. Известно, что самое длинное слово в англйском языке - "pneumonoultramicroscopicsilicovolcanoconiosis" - состоит из 45-ти букв, значит, ячейки с номером больше 45 не могут быть заполнены (из построенной гистограммы видно, что ...)


<a name="rol-hash"></a>
### 5. rol_hash
Эта функция считает хэш строки по следующей формуле: $h(n) = rol(h(n-1)) xor str[n]$, где $rol$ - битовое вращение влево, $str[n]$ - n-ая буква строки, $h(0) = 0$. 
```
uint32_t rol_hash(const char* str) {

    uint32_t hash_sum = 0;

    size_t len = strlen(str);

    for (size_t i = 0; i < len; i++) {

        hash_sum = rol(hash_sum) ^ str[i]; 
                                                           
    }
    return hash_sum;

}
```
Для реализации этой хэш-функции была написана вспомогательная функция:
```
inline uint32_t rol(uint32_t value) {

    return ((value << 1)) | (value >> 31);

}
```
Посмотрим, как компилятор преобразовывает эту функцию в ассемблерный код

С флагом `-O0`:

<img src = "Pictures/Снимок экрана (1015).png" width="800">
Заметим, что компилятор смог распознать инструкцию `rol`, но оставил вызов функции.

С флагом `-O3`:

<img src = "Pictures/Снимок экрана (1016).png" width="800">
В этом случае компилятор также использует ассемблерную инструкцию `rol`, но помимо этого избавился от вызова функции.

Гистограмма распределения элементов по ячейкам:

<img src = "Pictures/RolHash.png" width="800">

<a name="ror-hash"></a>
### 6. ror_hash



<a name="crc32-hash"></a>
### 7. crc32_hash
