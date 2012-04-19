/********************************************************************
**  Nulloy Music Player, http://nulloy.com
**  Copyright (C) 2010-2011 Sergey Vlasov <sergey@vlasov.me>
**
**  This program can be distributed under the terms of the GNU
**  General Public License version 3.0 as published by the Free
**  Software Foundation and appearing in the file LICENSE.GPL3
**  included in the packaging of this file.  Please review the
**  following information to ensure the GNU General Public License
**  version 3.0 requirements will be met:
**
**  http://www.gnu.org/licenses/gpl-3.0.html
**
*********************************************************************/

#include "scriptPrototypes.h"

#include <QPushButton>
#include <QDialog>
#include <QScriptValue>
#include <QScriptEngine>

#include <QDebug>

Q_DECLARE_METATYPE(QWidget *)
Q_DECLARE_METATYPE(QLayout *)
Q_DECLARE_METATYPE(QDialog *)
Q_DECLARE_METATYPE(QPushButton *)
Q_DECLARE_METATYPE(QMargins)


NWidgetPrototype::NWidgetPrototype(QObject *parent) : QObject(parent) {}

void NWidgetPrototype::setParent(QWidget *parent)
{
	QWidget *widget = qscriptvalue_cast<QWidget *>(thisObject());
	if (widget)
		widget->setParent(parent);
}

int NWidgetPrototype::windowFlags()
{
	QWidget *widget = qscriptvalue_cast<QWidget *>(thisObject());
	if (widget)
		return (int)widget->windowFlags();
	else
		return 0;
}

void NWidgetPrototype::setWindowFlags(int flags)
{
	QWidget *widget = qscriptvalue_cast<QWidget *>(thisObject());
	if (widget)
		widget->setWindowFlags((Qt::WindowFlags)flags);
}

void NWidgetPrototype::setAttribute(int attribute, bool enable)
{
	QWidget *widget = qscriptvalue_cast<QWidget *>(thisObject());
	if (widget)
		widget->setAttribute((Qt::WidgetAttribute)attribute, enable);
}

QWidget* NWidgetPrototype::parentWidget()
{
	QWidget *widget = qscriptvalue_cast<QWidget *>(thisObject());
	if (widget)
		return widget->parentWidget();
	else
		return NULL;
}

void NWidgetPrototype::move(int x, int y)
{
	QWidget *widget = qscriptvalue_cast<QWidget *>(thisObject());
	if (widget)
		widget->move(x, y);
}

void NWidgetPrototype::resize(int w, int h)
{
	QWidget *widget = qscriptvalue_cast<QWidget *>(thisObject());
	if (widget)
		widget->resize(w, h);
}

void NWidgetPrototype::setStandardIcon(QString name, QString fallback)
{
	QPushButton *button = qscriptvalue_cast<QPushButton *>(thisObject());
	if (button)
		button->setIcon(QIcon::fromTheme(name, QIcon(fallback)));
}

void NWidgetPrototype::setSizeGripEnabled(bool enabled)
{
	QDialog *dialog = qscriptvalue_cast<QDialog *>(thisObject());
	if (dialog)
		dialog->setSizeGripEnabled(enabled);
}

void NWidgetPrototype::setFontSize(int size)
{
	QWidget *widget = qscriptvalue_cast<QWidget *>(thisObject());
	if (widget) {
		QFont font = widget->font();
		font.setPixelSize(size);
		widget->setFont(font);
	}
}

QLayout* NWidgetPrototype::layout()
{
	QWidget *widget = qscriptvalue_cast<QWidget *>(thisObject());
	return widget->layout();
}

NLayoutPrototype::NLayoutPrototype(QObject *parent) : QObject(parent) {}

QMargins NLayoutPrototype::contentsMargins()
{
	QLayout *layout = qscriptvalue_cast<QLayout *>(thisObject());
	return layout->contentsMargins();
}

void NLayoutPrototype::setContentsMargins(int left, int top, int right, int bottom)
{
	QLayout *layout = qscriptvalue_cast<QLayout *>(thisObject());
	if (layout)
		layout->setContentsMargins(left, top, right, bottom);
}

void NLayoutPrototype::setContentsMargins(QMargins margins)
{
	QLayout *layout = qscriptvalue_cast<QLayout *>(thisObject());
	if (layout)
		layout->setContentsMargins(margins);
}

void NLayoutPrototype::setSpacing(int spacing)
{
	QLayout *layout = qscriptvalue_cast<QLayout *>(thisObject());
	if (layout)
		layout->setSpacing(spacing);
}

void NLayoutPrototype::setSpacingAt(int index, int spacing)
{
	QLayout *layout = qscriptvalue_cast<QLayout *>(thisObject());
	if (layout) {
		layout->removeItem(layout->itemAt(index));
		dynamic_cast<QBoxLayout *>(layout)->insertSpacing(index, spacing);
	}
}

void NLayoutPrototype::insertWidget(int index, QWidget *widget)
{
	QLayout *layout = qscriptvalue_cast<QLayout *>(thisObject());
	if (layout)
		dynamic_cast<QBoxLayout *>(layout)->insertWidget(index, widget);
}

QScriptValue NMarginsPrototype::toScriptValue(QScriptEngine *engine, const QMargins &m)
{
	QScriptValue obj = engine->newObject();
	obj.setProperty("bottom", m.bottom());
	obj.setProperty("left", m.left());
	obj.setProperty("right", m.right());
	obj.setProperty("top", m.top());
	return obj;
}

void NMarginsPrototype::fromScriptValue(const QScriptValue &obj, QMargins &m)
{
	m.setBottom(obj.property("bottom").toInt32());
	m.setLeft(obj.property("left").toInt32());
	m.setRight(obj.property("right").toInt32());
	m.setTop(obj.property("top").toInt32());
}

/* vim: set ts=4 sw=4: */