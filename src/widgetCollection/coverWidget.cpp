/********************************************************************
**  Nulloy Music Player, http://nulloy.com
**  Copyright (C) 2010-2014 Sergey Vlasov <sergey@vlasov.me>
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

#include "coverWidget.h"
#include "coverReaderInterface.h"
#include "pluginLoader.h"

#include <QResizeEvent>

NCoverWidget::NCoverWidget(QWidget *parent) : QLabel(parent)
{
	m_coverReader = NPluginLoader::coverReaderPlugin();

	hide();

	setScaledContents(TRUE);
}

void NCoverWidget::setSource(const QString &file)
{
	if (!m_coverReader)
		return;

	hide();
	init();

	m_coverReader->setSource(file);
	QPixmap pixmap = QPixmap::fromImage(m_coverReader->getImage());
	m_sourceSize = pixmap.size();

	if (!pixmap.isNull()) { // first scale, then show
		setPixmap(pixmap);
		fitToHeight(height());
		show();
	}
}

void NCoverWidget::init()
{
	setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Ignored);

	setMinimumWidth(0);
	setMinimumHeight(0);
	setMaximumWidth(QWIDGETSIZE_MAX);
	setMaximumHeight(QWIDGETSIZE_MAX);
}

void NCoverWidget::resizeEvent(QResizeEvent *event)
{
	fitToHeight(event->size().height());
}

void NCoverWidget::fitToHeight(int height)
{
	QSize fixedAspect(m_sourceSize);
	fixedAspect.scale(parentWidget()->width() / 2, height, Qt::KeepAspectRatio);

	setMaximumWidth(fixedAspect.width());
	setMinimumWidth(fixedAspect.width());

	if (fixedAspect.width() >= parentWidget()->width() / 2) // stop scaling, leave space for waveform slider
		setMaximumHeight(fixedAspect.height());
	else
		setMaximumHeight(QWIDGETSIZE_MAX);
}

