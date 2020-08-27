#include <QApplication>
#include <QDebug>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QMainWindow>
#include <QPushButton>
#include <QStyleFactory>
#include <QTableWidget>

int main(int argc, char **argv)
{
    QApplication::setApplicationName("Gitz");
    QApplication::setOrganizationName("Zeex");
    QApplication::setOrganizationDomain("zeex.github.io");

    QApplication app(argc, argv);

    QMainWindow mainWindow;
    mainWindow.setWindowTitle(QApplication::applicationName());
    mainWindow.setWindowIcon(QIcon(":/icons/git-icon.png"));
    mainWindow.resize(QSize(800, 600));
    mainWindow.setMinimumSize(QSize(400, 200));

    QWidget content;
    QHBoxLayout mainLayout;
    mainLayout.setContentsMargins(0, 0, 0, 0);
    content.setLayout(&mainLayout);

    QTableWidget table(1, 4, &mainWindow);
    table.setHorizontalHeaderLabels(QStringList({"Message", "Author", "Email", "Time"}));
    table.verticalHeader()->hide();
    mainLayout.addWidget(&table);

    mainWindow.setCentralWidget(&content);
    mainWindow.show();

    return app.exec();
}
