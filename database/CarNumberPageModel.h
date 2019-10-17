#ifndef CARNUMBERPAGEMODEL_H
#define CARNUMBERPAGEMODEL_H

#include <QAbstractListModel>

#include "CarNumberInfoModel.h"
#include "CarNumberInfoMapper.h"

class CarNumberPageModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int count READ rowCount NOTIFY countChanged)

public:
    explicit CarNumberPageModel(QObject *parent = nullptr);

    enum Roles {
        CarNumberModel = Qt::UserRole + 1
    };

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void search(const QString &number);

    Q_INVOKABLE CarNumberInfoModel *at(int index);

    void clear();

signals:
    void countChanged();
    void searchCompleted(bool isSearch);

private:
    QList<CarNumberInfoModel *> data_;
    CarNumberInfoMapper mapper_;
};

#endif // CARNUMBERPAGEMODEL_H
