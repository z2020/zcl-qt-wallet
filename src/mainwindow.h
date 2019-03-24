#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "precompiled.h"
#include "logger.h"

// Forward declare to break circular dependency.
class RPC;
class Settings;
class WSServer;
class WormholeClient;

using json = nlohmann::json;

// Struct used to hold destination info when sending a Tx. 
struct ToFields {
    QString addr;
    double  amount;
    QString txtMemo;
    QString encodedMemo;
};

// Struct used to represent a Transaction. 
struct Tx {
    QString         fromAddr;
    QList<ToFields> toAddrs;
    double          fee;
};

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void updateLabelsAutoComplete();
    RPC* getRPC() { return rpc; }

    QString doSendTxValidations(Tx tx);
    void setDefaultPayFrom();

    void replaceWormholeClient(WormholeClient* newClient);
    bool isWebsocketListening();
    void createWebsocket(QString wormholecode);
    void stopWebsocket();

    void balancesReady();
    void payZClassicURI(QString uri = "");

    void updateLabels();
    void updateTAddrCombo(bool checked);
    void updateFromCombo();

    Ui::MainWindow*     ui;

    QLabel*             statusLabel;
    QLabel*             statusIcon;
    QLabel*             loadingLabel;
    QWidget*            zclassicdtab;

    Logger*      logger;

    void doClose();

private:    
    void closeEvent(QCloseEvent* event);

    void setupSendTab();
    void setupTransactionsTab();
    void setupRecieveTab();
    void setupBalancesTab();
    void setupZClassicdTab();

    void setupTurnstileDialog();
    void setupSettingsModal();
    void setupStatusBar();

    void removeExtraAddresses();

    Tx   createTxFromSendPage();
    bool confirmTx(Tx tx);

    void turnstileDoMigration(QString fromAddr = "");
    void turnstileProgress();

    void cancelButton();
    void sendButton();
    void inputComboTextChanged(int index);
    void addAddressSection();
    void maxAmountChecked(int checked);

    void editSchedule();

    void addressChanged(int number, const QString& text);
    void amountChanged (int number, const QString& text);

    void addNewZaddr(bool sapling);
    std::function<void(bool)> addZAddrsToComboList(bool sapling);

    void memoButtonClicked(int number, bool includeReplyTo = false);
    void setMemoEnabled(int number, bool enabled);
    
    void donate();
    void addressBook();
    void postToZBoard();
    void importPrivKey();
    void exportAllKeys();
    void exportKeys(QString addr = "");
    void backupWalletDat();
    void exportTransactions();

    void doImport(QList<QString>* keys);

    void restoreSavedStates();
    bool eventFilter(QObject *object, QEvent *event);

    bool            uiPaymentsReady    = false;
    QString         pendingURIPayment;

    WSServer*       wsserver = nullptr;
    WormholeClient* wormhole = nullptr;

    RPC*         rpc  = nullptr;
    QCompleter*  labelCompleter = nullptr;

    QMovie*      loadingMovie;
};

#endif // MAINWINDOW_H
