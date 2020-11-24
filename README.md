![Allegro 5 program in C screenshot](screenshot.png)

# Эксперименты с Allegro 5 на Си и Обероне

*See English below*

## Установка (Дебиан)
```
sudo add-apt-repository ppa:allegro/5.2
sudo apt-get install -y liballegro*5.2 liballegro*5-dev
```
или смотри [инструкцию](https://github.com/liballeg/allegro_wiki/wiki/Quickstart).

### Установка под Windows
Смотри раздел «Windows» в [следующей инструкции](https://github.com/liballeg/allegro_wiki/wiki/Quickstart).

## Компиляция и запуск
```
cd 1_simplest
make run
```

*Список примеров см. внизу*

-----------

# Allegro 5 experiments in C and Oberon

## Setup (Debian)
```
sudo apt-get install gcc make libx11-dev
```
or check out [the tutorial](https://github.com/liballeg/allegro_wiki/wiki/Quickstart).

## Compile & Run
```
cd 1_simplest
make run
```

### Setup on Windows
See “Windows” section of [this tutorial](https://github.com/liballeg/allegro_wiki/wiki/Quickstart).

*See the list of examples below*

-----------

## Примеры / Examples

| Имя / Name | Описание / Description |
| --------- | ----------- |
| [1\_simplest](1_simplest/simplest.c) | Создаёт окно с надписью. Creates a window with a sign. |
| [2\_lines](2_lines/lines.c) | Рисует фигуру, которая движется по щелчку мыши. Draws a figure, that moves right upon mouse click. |
| [3\_windows](3_windows/windows.c) | Открывает несколько окон. Opens multiple windows. |
