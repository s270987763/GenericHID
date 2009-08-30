#ifndef TESTWIDGET_H
#define TESTWIDGET_H

#include <QWidget>
#include "columnlayout.h"
#include "testitem.h"
#include "hiddatathread.h"

class TestWidget : public QWidget
{
    Q_OBJECT

public:
    TestWidget(QWidget *parent);
    ~TestWidget();
    void Activate();
    void Deactivate();

public slots:
    void onDevicesIndexChanged( int index );
    void onRefreshPressed();
    void onNewData( QVector<byte> data );
    void onValueChanged(int);

private:
    void DisplayDevice( class HIDDevice *pDevice );
    void StartListening();
    void StopListening();

    Logger m_Logger;
    QComboBox *m_cboDevices;
    QPushButton *m_btnRefresh;
    class HIDDevices *m_pDevices;
    class HIDDevice *m_pActiveDevice;
    ColumnLayout *m_pDeviceLayout;
    bool m_bLoading;
    QList<TestItem *> m_pTestItems;
    HIDDataThread *m_pThread;
    QString m_sLastDevice;
};

#endif // TESTWIDGET_H
