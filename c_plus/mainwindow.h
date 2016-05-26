/*!
 * \mainpage
 * \brief Титульная страница по проекту программы для создания графиков
 * ------------------------------------------------------------------------
 *
 * Особенность данного проекта состоит в обучении создания GUI при помощи средств QtCreator. Для ориентации по документации есть меню слева.\n\n\n\n\n\n\n\n\n
 * За сим откланяюсь.\n
 * С уважением, Silence\n
 *
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H
/*!

  \file
  \brief Загловочный файл содержащий класс прямой и главное окно , в котором и рисуются прямые

  Содержит описание класса графиков, главного окна
  */
#include "mydialogcurve.h"
#include <QMainWindow>
#include <qwt_plot.h>
#include <qwt_plot_grid.h>
#include <qwt_legend.h>
#include <qwt_plot_curve.h>
#include <qwt_symbol.h>
#include <qwt_plot_magnifier.h>
#include <qwt_plot_panner.h>
#include <qwt_plot_picker.h>
#include <qwt_picker_machine.h>
#include <QMainWindow>
#include <QVector>
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>

namespace Ui {
class MainWindow;
}
class MyNewCurve;
class MyDeleteCurve;
/*!
 * \brief The graph class
 *
 * Класс , содержащий все данные об одной прямой
 */

class graph{
public:
    /// конструктор выделяет память под прямую QwtPlotCurve
    graph();
    //по моим наблюдениям каждому QwtPlotCurve *
    //может соответствовать только одна кривая
    ///Указатель на прямую , которая в итоге рисуется
    QwtPlotCurve *curva;
    /// Имя этой прямой
    QString name;
    //сортировку для QPolygonF я не нашел
    //поэтому решил использовать свой вектор из QPointF
    ///Вектор, содержащий все точки прямой
    QVector<QPointF> tchk;
    ///Цвет прямой в формате RGB
    int red;
    ///Цвет прямой в формате RGB
    int green;
    ///Цвет прямой в формате RGB
    int blue;
    ///Толщина прямой
    double pen;//толщина
    //предполагается что новый элемент tchk добавлен в конец
    //поэтому двигаем с конца элемент до своего места
     //одна и таже
    ///Функция, отвечающая за сортировку точек по координате x , с заменой точек с одинаковыми значениями новой
    void MoveFromBackWithout();
    //Возращает индекс точки ближайшей к передаваемым координатам
    /*!
     * \brief Функция возвращающая индекс ближайшей точки к области клика
     *
     * Индекс находится через наименьшую гипотенузу по теореме Пифагора
     * \param coordX , coordY координты точки клика
     * \return индекс ближайшей точки
     */
    int FindNear(double coordX,double coordY);
};

/*!
 * \brief The MainWindow class
 *
 * Класс главного окна через которое происходит управление программой и в котором рисуются графики
 * Содержит так же функции чтения и записи файлов, разборщик форматов и т.д.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private Q_SLOTS:
    ///Возвращает координаты клика по сетке
    void click_on_canvas( const QPoint &pos );
    ///Добавить точку на активный график
    void on_add_clicked();
    ///Удаление точки с активного графика
    void on_free_clicked();
    ///Сдвиг точки для удаления влево по графику на 1
    void on_OneL_clicked();// pushbutton <
    ///Сдвиг точки для удаления вправо по графику на 1
    void on_OneR_clicked();// pushbutton >
    ///Сдвиг на 10 точек вправо
    void on_TWoR_clicked();// pushbutton >>
    ///Свдиг на 10 точек влево
    void on_TwoL_clicked();// pushbutton <<
    //Открыть окно добавления графика
    ///Нажатие Edit->New Curve
    void on_actionNew_curve_triggered();

    //При измениении содержимого ввода провереем на заполненовсть
    //и делаем возможным или невозможным нажатее кнопки add
    ///Контроль непустого поля для добавления точки
    void on_lineEditX_textChanged(const QString &arg1);
    ///Контроль непустого поля для добавления точки
    void on_lineEditY_textChanged(const QString &arg1);
    ///Получения индекса активной прямой
    void on_UserCurve_currentIndexChanged(int index);
    ///Нажатие Edit->Delete Curve
    void on_actionDelete_curve_triggered();
    ///Нажатие Menu->Open
    void on_actionOpen_file_triggered();
    ///Нажатие Menu->Save as
    void on_actionSave_File_as_triggered();
    ///Нажатие Menu->Save
    void on_actionSave_File_triggered();
    ///Добавляет одну прямую из начала выбранного файла
    void on_actionOpen_one_curve_triggered();
    ///Сохраняет одну прямую в конце текущего активного файла
    void on_actionSave_current_curve_triggered();
    /*! brief Сохраняет одну активную прямую в конец выбранного файла
     *
     * \warning Не обращайте внимания на вопрос о замене файла, ничего не будет заменено.
    */
    void on_actionSave_current_curve_as_triggered();

private:
    /*!
     * \brief SaveToTxt
     *
     * Сохраняет в .txt формат
     * \warning Важен определнный порядок расположения данных , а именно : \n
     * Имя прямой\n
     * Красный цвет\n
     * Зелеый цвет\n
     * Синий цвет\n
     * Толщина\n
     * Координата по x\n
     * Координата по y\n
     * \param flag определяет удачна ли была запись 1 - да 0 - нет
     * \param file ссылка на файл
     */
    void SaveToTxt(bool &flag, QFile &file);
    /*!
     * \brief AppendToTxt
     *
     * Записывает текущую прямую в конец уже использованно файла
     * \param flag показатель записи 1 - записано 0 -нет
     * \param file ссылка на файл
     */
    void AppendToTxt(bool &flag, QFile &file);
    /*!
     * \brief AppendToDoc
     *
     * Записывает текущую прямую в конец уже использованно файла
     * \param flag показатель записи 1 - записано 0 -нет
     * \param file ссылка на файл
     */
    void AppendToDoc(bool &flag, QFile &file);
    /*!
     * \brief SaveToDoc
     *
     * Сохраняет в .doc формат
     * \warning Важен определенный формат расположения , а именно : \n
     * Имя прямой 'TAB' Красный цвет 'TAB' Зеленый цвет 'TAB' Синий цвет 'TAB' Толщина\n
     * Координата x 'TAB' Координата y
     * \param flag определяет удачна ли была запись 1 - да 0 - нет
     * \param file ссылка на файл
     */
    void SaveToDoc(bool &flag, QFile &file);
    /*!
     * \brief ReadOneFromTxt
     *
     * Читает ОДНУ ПРЯМУЮ из .txt формата
     * \warning Читает ПЕРВУЮ прямую
     * \param flag удачно ли было проведено чтение 1 - да 0 -нет
     * \param file ссылка на файл
     */
    void ReadOneFromTxt(bool &flag, QFile &file);
    /*!
     * \brief ReadFromTxt
     *
     * Читает список прямых из .txt формата
     * \warning Прямые должны быть оформлены соответственно.\n
     * смотрите SaveToTxt();
     * \param flag удачно ли было проведено чтение 1 - да 0 -нет
     * \param file ссылка на файл
     */
    void ReadFromTxt(bool &flag, QFile &file);
    /*!
     * \brief ReadOneFromDoc
     *
     * Читает ОДНУ ПРЯМУЮ из .doc формата
     * \warning Читает ПЕРВУЮ прямую
     * \param flag удачно ли было проведено чтение 1 - да 0 -нет
     * \param file ссылка на файл
     */
    void ReadOneFromDoc(bool &flag, QFile &file);
    /*!
     * \brief ReadFromDoc
     *
     * Читает список прямых из .doc формата
     * \warning Прямые должны быть оформлены соответственно.\n
     * смотрите SaveToDoc();
     * \param flag удачно ли было проведено чтение 1 - да 0 -нет
     * \param file ссылка на файл
     */
    void ReadFromDoc(bool &flag, QFile &file);

    ///Проверяет есть ли существующие прямые при открытии файла.\n Если есть то предлагает их удалить и удаляет иначе открытие не произойдет
    void CheckVector(bool &okay);
    ///Содержит все прямые
    QVector<graph> base;//База с прямыми пользователя
    ///Указатель на форму главного окна
    Ui::MainWindow *ui;
    ///Указатель на окно добавления новой прямой
    MyNewCurve *litwin;
    ///Указатель на окно удаления прямой
    MyDeleteCurve *DelWin;
    ///Строка содержащая имя файла для функции Menu->Save
    QString NameOfFile;
    ///Индекс текущей точки для удаления
    int free_index;//точка для ->
    ///Прямая из одной точки, по сути подсвечивает активную точку для удаления
    QwtPlotCurve *free_tchk;
    ///Добавляет график
    void addPlot();//поле графика
    ///Добавляет сетку
    void addPlotGrid();//сетка
    ///Добавление прямой из одной точки для подсветки активно
    void addfreeCurve();
    /*!
     * \brief addCurve
     *
     * Добавляет новою прямую в вектор из прямых
     * \param buf ссылка по которой находится данные о прямой
     */
    void addCurve(graph &buf);
    ///Используется для перезагрузки поля графиков, т.е. для отрисовки новых прямых
    void reshow();
    ///Активация приближения по колесику мыши
    void enableMagnifier();
    ///Активирует передвижение по сетке правой кнопкой мыши
    void enableMovingOnPlot();
    ///переводит координаты клика в полле ввода
    void enablePicker();
};


#endif // MAINWINDOW_H
