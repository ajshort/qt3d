/****************************************************************************
**
** Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/
**
** This file is part of the Qt3D module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this
** file. Please review the following information to ensure the GNU Lesser
** General Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU General
** Public License version 3.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of this
** file. Please review the following information to ensure the GNU General
** Public License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.
**
** Other Usage
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QQUICKMESH_H
#define QQUICKMESH_H

#include "qt3dquickglobal.h"

#include <QtCore/qobject.h>
#include <QtCore/qurl.h>
#include <QtQml/qqml.h>
#include <QtQml/qqmlengine.h>
#include <QtQml/qqmlparserstatus.h>

#include "qglscenenode.h"
#include "qglpainter.h"

QT_BEGIN_HEADER

QT_BEGIN_NAMESPACE

QT_MODULE(QtQuick3D)

class QQuickMeshPrivate;
class QGLAbstractScene;
class QGLMaterial;
class QGLSceneAnimation;

class Q_QT3D_QUICK_EXPORT QQuickMesh : public QObject, public QQmlParserStatus
{
    Q_OBJECT
    Q_INTERFACES(QQmlParserStatus)
    Q_PROPERTY(QUrl source READ source WRITE setSource NOTIFY dataChanged)
    Q_PROPERTY(QString meshName READ meshName WRITE setMeshName NOTIFY dataChanged)
    Q_PROPERTY(QString options READ options WRITE setOptions NOTIFY optionsChanged)
    Q_PROPERTY(QGLSceneNode *node READ getSceneObject NOTIFY nodeChanged)
    Q_PROPERTY(bool dumpInfo READ dumpInfo WRITE setDumpInfo NOTIFY dumpInfoChanged)

public:
    QQuickMesh(QObject *parent = 0);
    ~QQuickMesh();

    QUrl source() const;
    void setSource(const QUrl& value);

    QString meshName() const;
    void setMeshName(const QString& value);

    QString options() const;
    void setOptions(const QString &);

    bool dumpInfo() const;
    void setDumpInfo(bool);

    virtual void draw(QGLPainter *painter, int branchId);

    //The following functions relate to allocating the scene and its
    //respective objects, and acessing these nodes.
    void setScene(QGLAbstractScene *scene);
    void initSceneObjectList();
    void initAnimations();
    QStringList getSceneObjectNames();
    QGLSceneNode *getSceneObject();
    QGLSceneNode *getSceneObject(const QString &name);
    QList<QGLSceneAnimation *> getAnimations();

    //The following functions relate to splitting the main scene into sub-branches
    int nextSceneBranchId() const;
    int createSceneBranch(QString nodeName);
    int addSceneBranch(QGLSceneNode *rootSceneObject, QObject *previousParent=NULL);
    void restoreSceneBranch(int branchId);
    void resetSceneBranches();
    QGLSceneNode *getSceneBranch(int branchId) const;

    void ref();
    bool deref();

    Q_INVOKABLE QObject *material(const QString& nodeName, const QString& materialName);

    void classBegin();
    void componentComplete();

    void openglContextIsAboutToBeDestroyed();

Q_SIGNALS:
    void dataChanged();
    void animationsChanged();
    void loaded();
    void optionsChanged();
    void dumpInfoChanged();
    void nodeChanged();

private Q_SLOTS:
    void dataRequestFinished();

private:
    QQuickMeshPrivate *d;

};

QT_END_NAMESPACE

QML_DECLARE_TYPE(QQuickMesh)

QT_END_HEADER

#endif