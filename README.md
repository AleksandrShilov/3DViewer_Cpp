# 3DViewer
![base](/materials/3DViewer.png)

## Общая информация

`3DViewer` - программа для визуализации модели в трехмерном пространстве.
Для декомпозиции был использовани паттерн MVC (Model-View-Controller, Модель-Представление-Контроллер) представляет из себя схему разделения модулей приложения на три отдельных макрокомпонента: модель, содержащую в себе бизнес-логику, представление - форму пользовательского интерфейса для осуществления взаимодействия с программой и контроллер, осуществляющий модификацию модели по действию пользователя.

- Программа разработана на языке C++ стандарта C++17.
- Выполнено полное покрытие unit-тестами модулей, связанных с загрузкой моделей и аффинными преобразованиями, c помощью библиотеки *GTest*.
- Для реализации графического интерфейса была использована технология *Qt*.
- Для реализации *gif* была использована стороняя библиотека *gifimage*.
- В один момент времени может быть отображена только одна модель на экране.

## Сборка программы

- Сборка программы выполняется с помощью Makefile.
    - для установки программы в командной строке следует прописать `make` (требуется наличие установленного cmake, glut (для установки введите данные команды в консоль: `sudo apt-get install freeglut3-dev`, `sudo apt-get install libgl1-mesa-dev`)).
    - для запуска программы перейдите в папку `build` и запустите ярлык с именем `3DViewer`.
    - для удаления программы в командной строке следует прописать `uninstall`.
    - для запуска тестов в командной строке следует прописать `make test`.
    - для запуска тестов и проверки покрытия в командной строке следует прописать `make gcov_report`.

## Возможности `3DViewer`

- Загружает модель из файла формата `obj` (поддержка списка вершин, поверхностей и нормалей).
- Перемещает модель на заданное расстояние относительно осей *X, Y, Z*.
- Поворачивает модель на заданный угол относительно своих осей *X, Y, Z*.
- Масштабирует модель на заданное значение.
- Переключает тип отображения объекта: *каркасная модель*, *плоское затенение*, *мягкое затенение*.
- Задает источник освещения, его базовую интенсивность (через три компоненты: R, G, B) и положение.
- Программа позволяет настраивать тип проекции (параллельная и центральная).
- Программа позволяет настраивать тип (сплошная, пунктирная), цвет и толщину ребер.
- Способ отображения (отсутствует, круг, квадрат), цвет и размер вершин.
- Программа позволяет выбирать цвет фона.
- Программа позволяет выбирать базовый цвет фона.
- Настройки сохраняются между перезапусками программы.
- Программа позволяет сохранять полученные ("отрендеренные") изображения в файл в форматах bmp и jpeg.
- Программа позволяет по специальной кнопке записывать небольшие "скринкасты" - текущие пользовательские аффинные преобразования загруженного объекта в gif-анимацию.

