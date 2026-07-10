# Hello PSP Game

Простая PSP homebrew игра, написанная на C с использованием PSPSDK.

## Что делает игра

- Выводит текст "Hello PSP Game" на экран
- При нажатии кнопки **O** показывает разноцветные прямоугольники
- При нажатии кнопки **X** выходит из игры

## Как собрать

### Локально (с PSPSDK)

```bash
make
```

### Через GitHub Actions

Нажмите "Build PSP Game" → Actions → скачайте EBOOT.PBP или game.iso из Artifacts.

## Установка на PSP

1. Скопируйте `EBOOT.PBP` в `/PSP/GAME/hello_psp/` на вашей Memory Stick
2. Запустите из меню Game → Memory Stick

## Используемые библиотеки

- `libpspgu` — графика
- `libpspdisplay` — дисплей
- `libpspctrl` — управление
- `libpspkernel` — ядро PSP
- `libpsppower` — управление питанием

## Структура проекта

```
├── main.c              # Основной код игры
├── Makefile            # Сборка через PSPSDK
├── .github/workflows/
│   └── build.yml       # GitHub Actions CI/CD
└── README.md
```
