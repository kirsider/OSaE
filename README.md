# OSaE
Operations Systems and Environments labs (6th semester)

## ЛР №1
**1.3.3.** С клавиатуры вводятся расширение имени для поиска файлов (например, `txt`) и имя файла результата. Необходимо найти все файлы с этим расширением и сохранить их имена в результирующем файле. В случае если файл для хранения результата уже существует, его старое содержимое должно быть сохранено, а новые записи надо добавлять в конец файла.

## ЛР №2
**2.3.2.** При помощи анализа цепочек выяснить, какой из файлов корневого каталога занимает наибольшее число кластеров. Имя этого файла показать на экране.

## ЛР №3
**3.3.3.** Создать двоичное дерево, хранящее числа. Каждый элемент дерева должен хранить число и «левую» и «правую» ссылки на нижестоящие элементы. Необходимо реализовать алгоритмы добавления числа в двоичное дерево и удаления числа из него. Пользователю должны быть доступны следующие функции: добавить число, удалить число, очистить дерево, показать содержимое дерева на экране. При выводе на экран показывать дерево в виде строки вида: содержимое родителя (содержимое левой ветви, содержимое правой ветви); для каждой из ветвей функция вывода должна быть вызвана рекурсивно.

## ЛР №4
**4.3.1.** Перекрыть прерывание клавиатуры и сделать так, чтобы одна из букв (например, `a`) подменялась другой (например `b`).

## ЛР №5
Запрограммировать клавиатурный шпион. Данная программа должна накапливать у себя в памяти вводимые пользователем символы и с заданной периодичностью (например 20 с.) сохранять их в файл spy.txt. Перехватываемые прерывания – клавиатура и таймер.
Должна быть обязательная проверка занятости DOS и данные должны сохраняться только когда система свободна. Должны быть решены проблемы повторного вхождения в прерывания DOS. Должна быть реализована возможность корректного удаления обработчика (допустимо не удалять резидент полностью, а заменять обработчик заглушкой). Должна также выполняться проверка повторной установки (предлагается использовать при помощи мультиплексного прерывания).
