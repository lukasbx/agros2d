#ifndef LOCALVALUE_H
#define LOCALVALUE_H

#include <QtGui/QDockWidget>
#include <QtGui/QTreeWidget>

#include "util.h"
#include "scene.h"

class Scene;

class LocalPointValue;
class LocalPointValueElectrostatic;
class LocalPointValueMagnetostatic;
class LocalPointValueHeat;
class LocalPointValueCurrent;
class LocalPointValueElasticity;

LocalPointValue *localPointValueFactory(Point &point, Scene *scene);
QStringList localPointValueHeaderFactory(PhysicField physicField);

class LocalPointValueView : public QDockWidget
{
    Q_OBJECT

public slots:
    void doShowPoint(LocalPointValue *localPointValue);

public:
    LocalPointValueView(Scene *scene, QWidget *parent = 0);

private:
    Scene *m_scene;

    QTreeWidget *trvWidget;

    QAction *actPoint;

    QMenu *mnuInfo;

    void createActions();
    void createMenu();

    void addValue(QTreeWidgetItem *parent, QString name, QString text, QString unit);

    void showElectrostatic(LocalPointValueElectrostatic *localPointValueElectrostatic);
    void showMagnetostatic(LocalPointValueMagnetostatic *localPointValueMagnetostatic);
    void showHeat(LocalPointValueHeat *localPointValueHeat);
    void showElasticity(LocalPointValueElasticity *localPointValueElasticity);
    void showCurrent(LocalPointValueCurrent *localPointValueCurrent);

private slots:
    void doPoint();
    void doContextMenu(const QPoint &pos);
};


class LocalPointValue
{
public:
    Point point;

    LocalPointValue(Point &point, Scene *scene);

    inline Scene *scene() { return m_scene; }
    virtual double variableValue(PhysicFieldVariable physicFieldVariable, PhysicFieldVariableComp physicFieldVariableComp) = 0;
    virtual QStringList variables() = 0;

protected:
    Scene *m_scene;
    Vectorizer m_vec;
};

class LocalPointValueElectrostatic : public LocalPointValue
{
public:
    double charge_density;
    double permittivity;
    double potential;
    Point E;
    Point D;
    double we;

    LocalPointValueElectrostatic(Point &point, Scene *scene);
    double variableValue(PhysicFieldVariable physicFieldVariable, PhysicFieldVariableComp physicFieldVariableComp);
    QStringList variables();
};

class LocalPointValueMagnetostatic : public LocalPointValue
{
public:
    double current_density;
    double permeability;
    double potential;
    Point H;
    Point B;
    double wm;

    LocalPointValueMagnetostatic(Point &point, Scene *scene);
    double variableValue(PhysicFieldVariable physicFieldVariable, PhysicFieldVariableComp physicFieldVariableComp);
    QStringList variables();
};

class LocalPointValueHeat : public LocalPointValue
{
public:
    double volume_heat;
    double thermal_conductivity;
    double temperature;
    Point F;
    Point G;

    LocalPointValueHeat(Point &point, Scene *scene);
    double variableValue(PhysicFieldVariable physicFieldVariable, PhysicFieldVariableComp physicFieldVariableComp);
    QStringList variables();
};

class LocalPointValueCurrent : public LocalPointValue
{
public:
    double conductivity;
    double losses;
    double potential;
    Point J;
    Point E;

    LocalPointValueCurrent(Point &point, Scene *scene);
    double variableValue(PhysicFieldVariable physicFieldVariable, PhysicFieldVariableComp physicFieldVariableComp);
    QStringList variables();
};

class LocalPointValueElasticity : public LocalPointValue
{
public:
    double young_modulus;
    double poisson_ratio;
    double von_mises_stress;

    LocalPointValueElasticity(Point &point, Scene *scene);
    double variableValue(PhysicFieldVariable physicFieldVariable, PhysicFieldVariableComp physicFieldVariableComp);
    QStringList variables();
};

#endif // LOCALVALUE_H
