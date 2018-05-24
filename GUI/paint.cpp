#include "paint.h"
#include "ui_paint.h"
#include "readfile.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QDesktopWidget>

paint::paint(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::paint)
{
    ui->setupUi(this);

    createLanguageMenu();

    QRect screenGeometry = QApplication::desktop()->screenGeometry();
    int x = (screenGeometry.width() - this->width()) / 2;
    int y = (screenGeometry.height()-  this->height()) / 2;
    this->move(x, y);

    quadTree = new QuadTree(0, (float)ui->graphicsView->x(), (float)ui->graphicsView->y(), (float)ui->graphicsView->width() - 20);
    scene = new paintScene(quadTree);

    ui->graphicsView->setScene(scene);

    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &paint::slotTimer);
    timer->start(100);
}

paint::~paint()
{
    delete timer;
    delete scene;
    delete quadTree;
    delete ui;
}

void paint::slotTimer(){
    timer->stop();
    scene->setSceneRect(0,0,ui->graphicsView->width() - 20, ui->graphicsView->height() - 20);
}

void paint::resizeEvent(QResizeEvent *event){
    timer->start(100);
    QWidget::resizeEvent(event);
}

void switchTranslator(QTranslator& translator, const QString& filename)
{
    // remove the old translator
    qApp->removeTranslator(&translator);

    // load the new translator
    QString langFile = "/opt/quadgui/languages/" + filename;
    if(translator.load(langFile))
        qApp->installTranslator(&translator);
}

void paint::createLanguageMenu(void) {
    QActionGroup *langGroup = new QActionGroup(ui->menu_2);
    langGroup->setExclusive(true);

    connect(langGroup, SIGNAL(triggered(QAction*)), this, SLOT(slotLanguageChange(QAction*)));

    // format systems language
    QString defaultLocale = "en";

    m_langPath = "/opt/quadgui";
    m_langPath.append("/languages");
    QDir dir(m_langPath);
    QStringList fileNames = dir.entryList(QStringList("lang_*.qm"));

    for (int i = 0; i < fileNames.size(); ++i) {
        // get locale extracted by filename
        QString locale;
        locale = fileNames[i]; // "TranslationExample_de.qm"
        locale.truncate(locale.lastIndexOf('.')); // "TranslationExample_de"
        locale.remove(0, locale.indexOf('_') + 1); // "de"

        QString lang = QLocale::languageToString(QLocale(locale).language());

        QAction *action = new QAction(lang, this);
        action->setCheckable(true);
        action->setData(locale);

        ui->menu_2->addAction(action);
        langGroup->addAction(action);

        // set default translators and language checked
        if (defaultLocale == locale) {
            action->setChecked(true);
        }
     }
}

void paint::loadLanguage(const QString &rLanguage) {
    if(m_currLang != rLanguage) {
         m_currLang = rLanguage;
         QLocale locale = QLocale(m_currLang);
         QLocale::setDefault(locale);
         QString languageName = QLocale::languageToString(locale.language());
         switchTranslator(m_translator, QString("lang_%1.qm").arg(rLanguage));
         //switchTranslator(m_translatorQt, QString("qt_%1.qm").arg(rLanguage));
    }
}

void paint::slotLanguageChange(QAction *action) {
    if(action != 0) {
        // load the language dependant on the action content
        loadLanguage(action->data().toString());
        ui->retranslateUi(this);
    }
}

void paint::on_openFile_triggered()
{   
    ReadFile reader;
    std::vector<Point*> points;

    double maxSize = -1;


    QString filename =  QFileDialog::getOpenFileName(
          this,
          "Open file with points",
          QDir::currentPath(),
          "Txt files (*.txt)");

    if( !filename.isNull() ) {
        if (reader.reading(filename.toUtf8().constData(), &points) == 1) {
            if (points.size() == 0) maxSize = ui->graphicsView->width();

            for (int i = 0; i < points.size(); i++) {
                if (points[i]->X > maxSize) maxSize = points[i]->X + 5;
                if (points[i]->Y > maxSize) maxSize = points[i]->Y + 5;
            }
            this->setFixedWidth((int)maxSize + 20);
            this->setFixedHeight((int)maxSize + 60);
            this->ui->graphicsView->setFixedWidth((int)maxSize + 20);
            this->ui->graphicsView->setFixedHeight((int)maxSize + 20);
            quadTree->setQuad(quadTree->MakeQuad((double)ui->graphicsView->x(), (double)ui->graphicsView->y(), maxSize));

            for (int i = 0; i < points.size(); i++) {
                quadTree->Insert(points[i]);
            }

            scene->reDraw();
        }
        else {
            QMessageBox messageBox;
            messageBox.critical(0,"Error","Error reading file!");
            messageBox.setFixedSize(500,200);
        }
    }
}
