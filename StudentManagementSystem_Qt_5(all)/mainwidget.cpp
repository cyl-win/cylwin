#include "mainwidget.h"
#include "ui_mainwidget.h"

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);

    menuwidget = new MenuWidget;
    addstudentwidget = new AddStudentWidget;
    selectwidget = new SelectWidget;
    modifywidget = new ModifyWidget;
    sortwidget = new SortWidget;
    Searchnoclear=new searchnoclear;
    Fenxi=new fenxi;
    Tongji=new tongji;
    stackLayout = new QStackedLayout;


    stackLayout->addWidget(menuwidget);
    stackLayout->addWidget(addstudentwidget);
    stackLayout->addWidget(selectwidget);
    stackLayout->addWidget(modifywidget);
    stackLayout->addWidget(sortwidget);
    stackLayout->addWidget(Searchnoclear);
    stackLayout->addWidget(Fenxi);
    stackLayout->addWidget(Tongji);
    setLayout(stackLayout);

    connect(menuwidget, &MenuWidget::display, stackLayout, &QStackedLayout::setCurrentIndex);
    connect(addstudentwidget, &AddStudentWidget::display, stackLayout, &QStackedLayout::setCurrentIndex);
    connect(selectwidget, &SelectWidget::display, stackLayout, &QStackedLayout::setCurrentIndex);
    connect(modifywidget, &ModifyWidget::display, stackLayout, &QStackedLayout::setCurrentIndex);
    connect(sortwidget, &SortWidget::display, stackLayout, &QStackedLayout::setCurrentIndex);
    connect(Searchnoclear,&searchnoclear::display,stackLayout,&QStackedLayout::setCurrentIndex);
    connect(Fenxi,&fenxi::display,stackLayout,&QStackedLayout::setCurrentIndex);
    connect(Tongji,&tongji::display,stackLayout,&QStackedLayout::setCurrentIndex);

}

MainWidget::~MainWidget()
{
    delete ui;
}
