/****************************************************************************
**
** Copyright (C) 2014 Klaralvdalens Datakonsult AB (KDAB).
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

#ifndef QT3D_RENDER_RENDERVIEW_H
#define QT3D_RENDER_RENDERVIEW_H

#include <Qt3DRenderer/renderer.h>

#include <QVector>

QT_BEGIN_NAMESPACE

namespace Qt3D {

class Renderer;
class RenderCamera;
class RenderPass; // TODO Split into front/back ends

namespace Render {

class RenderCommand;
class RenderPassFilter;
class TechniqueFilter;
class ViewportNode;

// This class is kind of analogous to RenderBin but I want to avoid trampling
// on that until we get this working
class RenderView
{
public:
    RenderView()
        : m_camera(0)
        , m_techniqueFilter(0)
        , m_passFilter(0)
        , m_viewport(0)
        , m_commands()
    {
    }

    ~RenderView();

    void setConfigFromFrameGraphLeafNode(FrameGraphNode *fgLeaf);

    // Called by the RenderThread to actually submit the commands to OpenGL
    void submit(Renderer *renderer);

    // TODO: Add a way to specify a sort predicate for the RenderCommands
    void sort();

    // These pointers define the configuration that needs to be
    // set for this RenderView before it's contained RenderCommands
    // can be submitted. If a pointer is null, that pice of state
    // does not need to be changed.
    // TODO: Add RenderTarget
    Qt3D::RenderCamera *m_camera;
    TechniqueFilter *m_techniqueFilter;
    RenderPassFilter *m_passFilter;
    ViewportNode *m_viewport;

    // We do not use pointers to RenderNodes or Drawable's here so that the
    // render aspect is free to change the drawables on the next frame whilst
    // the render thread is submitting these commands.
    QVector<RenderCommand *> m_commands;
};

} // namespace Render
} // namespace Qt3D

QT_END_NAMESPACE

#endif // QT3D_RENDER_RENDERVIEW_H