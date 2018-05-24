#ifndef PAINT_H
#define PAINT_H

#include <QMainWindow>
#include <QTimer>
#include <QResizeEvent>
#include <QTranslator>
#include "quadtree.h"

#include <paintscene.h>
namespace Ui {
class paint;
}

class paint : public QMainWindow
{
    Q_OBJECT

public:
    explicit paint(QWidget *parent = 0);
    ~paint();

private:
    Ui::paint *ui;
    QTimer *timer;      /* Определяем таймер для подготовки актуальных размеров
                            * графической сцены
                            * */
    paintScene *scene;
    QuadTree *quadTree;

    /* Переопределяем событие изменения размера окна
         * для пересчёта размеров графической сцены
         * */
    void resizeEvent(QResizeEvent * event);

    void loadLanguage(const QString& rLanguage);
    void createLanguageMenu(void);

    QTranslator m_translator; // contains the translations for this application
    QTranslator m_translatorQt; // contains the translations for qt
    QString m_currLang; // contains the currently loaded language
    QString m_langPath; // Path of language files. This is always fixed to /languages.

private slots:
    void slotTimer();
    void on_openFile_triggered();
    void slotLanguageChange(QAction *action);
};

#endif // PAINT_H
