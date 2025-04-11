#include "breadcrumbswidget.h"
#include "ui_breadcrumbswidget.h"

BreadcrumbsWidget::BreadcrumbsWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::BreadcrumbsWidget)
{
    ui->setupUi(this);

    QHBoxLayout *breadcrumbsLayout = new QHBoxLayout(this);
}

BreadcrumbsWidget::~BreadcrumbsWidget()
{
    delete ui;
}
