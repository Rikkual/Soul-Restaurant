//
// Created by Rikkual on 2024/6/3.
//

#ifndef AboutWidget_H
#define AboutWidget_H

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class AboutWidget; }
QT_END_NAMESPACE

class AboutWidget : public QWidget {
Q_OBJECT

public:
    explicit AboutWidget(QWidget *parent = nullptr);

    ~AboutWidget() override;

private:
    Ui::AboutWidget *ui;
};


#endif // AboutWidget_H
