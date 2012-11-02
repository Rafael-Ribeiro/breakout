#include <QWidget>
#include <QDialog>
#include <QFormLayout>
#include <QSpinBox>
#include <QPushButton>

#ifndef GAMEOFLIFERESIZEDIALOG_HPP
#define GAMEOFLIFERESIZEDIALOG_HPP

class GameOfLifeResizeDialog : public QDialog
{
	Q_OBJECT

public:
	typedef QDialog super;

	GameOfLifeResizeDialog(QWidget *parent = NULL);

private:
	QFormLayout layout;
	QSpinBox width;
	QSpinBox height;
	QPushButton ok_btn;

private slots:
	void ok_clicked();

signals:
	void ok(const size_t &width, const size_t &height);
};

#endif