/*
 * Copyright (C) 2017 Damir Porobic <https://github.com/damirporobic>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#ifndef PAINTERTEXT_H
#define PAINTERTEXT_H

#include <QTimer>
#include <QTextLayout>
#include <QTextDocument>
#include <QTextBlock>
#include <QApplication>
#include <QClipboard>

#include "PainterBaseItem.h"

class PainterText : public QObject, public PainterBaseItem
{
    Q_OBJECT
private:
    enum CursorPos {
        Next,
        Previous,
        Up,
        Down
    };

public:
    PainterText(const QPointF &pos, const QPen &attributes, const QFont &font);
    ~PainterText();
    virtual QRectF boundingRect() const override;
    virtual void moveTo(const QPointF &newPos) override;
    virtual void addPoint(const QPointF &pos, bool modifier = 0) override;
    virtual bool containsRect(const QPointF &topLeft, const QSize &size) const override;
    virtual bool isValid() const override;
    bool isEditable() const;
    QFont font() const;
    void setFont(const QFont &font);

protected:
    virtual void keyPressEvent(QKeyEvent *event) override;
    virtual void focusOutEvent(QFocusEvent *event) override;

private:
    QRectF        mRect;
    QString       mText;
    QFont         mFont;
    QFontMetrics *mFontMetric;
    QTimer       *mCursorBlinkTimer;
    bool          mEditable;
    int           mCursorPos;
    bool          mCursorVisible;

    virtual void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *) override;
    void moveCursor(CursorPos direction);
    void insertChar(const QString &c);
    void removeChar(CursorPos direction);
    void finishEditing();
    void updateRect();
    void pasteClipboard();

};

#endif // PAINTERTEXT_H