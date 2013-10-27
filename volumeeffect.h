/****************************************************************************
**
** Copyright (C) 2012 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the Qt3D module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef VolumeSHADERPROGRAM_H
#define VolumeSHADERPROGRAM_H

#include "qquickeffect.h"

#include <QFile>
#include <QDebug>

QT_BEGIN_NAMESPACE

class VolumeShaderProgramPrivate;
class QGLSceneNode;

class VolumeShaderProgram : public QQuickEffect
{
    Q_OBJECT
    Q_PROPERTY(QString vertexShader READ vertexShader WRITE setVertexShader NOTIFY shaderChanged)
    Q_PROPERTY(QString fragmentShader READ fragmentShader WRITE setFragmentShader NOTIFY shaderChanged)
    Q_PROPERTY(QString texture3D READ texture3D WRITE setTexture3D NOTIFY texture3DChanged)
    Q_PROPERTY(QString vertexShaderSource READ vertexShaderSource WRITE setVertexShaderSource NOTIFY vertexShaderSourceChanged)
    Q_PROPERTY(QString fragmentShaderSource READ fragmentShaderSource WRITE setFragmentShaderSource NOTIFY fragmentShaderSourceChanged)

public:
    VolumeShaderProgram(QObject *parent = 0);
    virtual ~VolumeShaderProgram();

    QString vertexShader() const;
    void setVertexShader(const QString& value);

    QString fragmentShader() const;
    void setFragmentShader(const QString& value);

    virtual void enableEffect(QGLPainter *painter);
    virtual void applyTo(QGLSceneNode *node);
    QString texture3D() const
    {
        return m_texture3D;
    }

    QString vertexShaderSource() const
    {
        return m_vertexShaderSource;
    }

    QString fragmentShaderSource() const
    {
        return m_fragmentShaderSource;
    }

public Q_SLOTS:
    void markAllPropertiesDirty();
    void markPropertyDirty(int property);
    void setTexture3D(QString arg)
    {
        if (m_texture3D != arg) {
            m_texture3D = arg;
            emit texture3DChanged(arg);
        }
    }

    void setVertexShaderSource(QString arg)
    {
        if (m_vertexShaderSource != arg) {
            m_vertexShaderSource = arg;
            QFile file(arg);
            QString vertexShaderFileContents;
            if (file.open(QIODevice::ReadOnly)) {
                vertexShaderFileContents = file.readAll();
            } else {
                qWarning() << "VolumeShaderProgram::setVertexShaderSource: could not open " << arg;
            }
            setVertexShader(vertexShaderFileContents);
            emit vertexShaderSourceChanged(arg);
        }
    }

    void setFragmentShaderSource(QString arg)
    {
        if (m_fragmentShaderSource != arg) {
            m_fragmentShaderSource = arg;
            QFile file(arg);
            QString fragmentShaderFileContents;
            if (file.open(QIODevice::ReadOnly)) {
                fragmentShaderFileContents = file.readAll();
            } else {
                qWarning() << "VolumeShaderProgram::setFragmentShaderSource: could not open " << arg;
            }
            setFragmentShader(fragmentShaderFileContents);
            emit fragmentShaderSourceChanged(arg);
        }
    }

Q_SIGNALS:
    void finishedLoading();
    void shaderChanged();
    void texture3DChanged(QString arg);

    void vertexShaderSourceChanged(QString arg);

    void fragmentShaderSourceChanged(QString arg);

private:
    VolumeShaderProgramPrivate *d;
    QString m_texture3D;
    //    int m_texture3DuniformValue;
    QString m_vertexShaderSource;
    QString m_fragmentShaderSource;
    int m_eyeLocation;
};

QT_END_NAMESPACE

QML_DECLARE_TYPE(VolumeShaderProgram)

#endif
