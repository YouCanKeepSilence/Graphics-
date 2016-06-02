/*!
 * \mainpage
 * \brief Титульная страница по проекту программы для создания графиков
 * ------------------------------------------------------------------------
 *
 *Пользователь обладает возможностью указывать координаты точек как с помощью ввода значений с клавиатуры, так и с помощью нажатия мышью в определенном месте на главном
 * поле для построения. Все действия отображаются в toolbar главного окна программы.
Пользователь имеет возможность добавлять кривые, указав название, цвет, толщину. Но главное – есть возможность построения нескольких кривых на одном графике. Название, цвет
 кривых указываются в легенде главного поля. Чтобы выбрать с какой кривой работать, пользователь имеет возможность обратиться к одной из созданных в combobox. Также можно
удалять кривую, выбрав в MenuBar опцию удаления. Удалять пользователь может и по одной точке. Для этого необходимо выбрать точку для удаления при помощи стрелок перемещения по
графику. На главном окне программы присутствует меню для открытия, сохраниние файла. Сохранение файла производится в файлы двух расширений: .doc / .txt по выбору. Открытие также
реализовано для двух форматов. Для ориентации по документации есть меню слева.\n
Основные возможности:\n
1) создавать управляемые прямые\n
2) определять координаты выбранной точки путем нажатия на график\n
3) сохранять прямые в файлы разных форматов\n
4) загружать прямые из файлов разных форматов\n
5) возможность выбрать ближайшую точку активной кривой путем нажатия на график рядом с этой точкой\n
6) реализован GUI\n
\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n
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
#include "workwithfiles.h"

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
    ///Указатель на прямую , которая в итоге рисуется
    QwtPlotCurve *curva;
    /// Имя этой прямой
    QString name;
    ///Вектор, содержащий все точки прямой
    QVector<QPointF> tchk;
    ///Цвет прямой в формате RGB
    int red;
    ///Цвет прямой в формате RGB
    int green;
    ///Цвет прямой в формате RGB
    int blue;
    ///Толщина прямой
    double pen;
    ///Функция, отвечающая за сортировку точек по координате x , с заменой точек с одинаковыми значениями новой
    void MoveFromBackWithout();
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
 * Класс главного окна через которое происходит управление программой и в
 * котором рисуются графики
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    QVector <graph> FromFile;
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
    void on_OneL_clicked();
    ///Сдвиг точки для удаления вправо по графику на 1
    void on_OneR_clicked();
    ///Сдвиг на 10 точек вправо
    void on_TWoR_clicked();
    ///Свдиг на 10 точек влево
    void on_TwoL_clicked();
    ///Нажатие Edit->New Curve
    void on_actionNew_curve_triggered();
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
    ///Прикрепляет точки к графику после чтения из файла
    void SetTchk();
    ///Добавляет одну кривую вместе с точками
    void AppendCurve(graph &buf);
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
