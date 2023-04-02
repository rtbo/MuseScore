/*
 * SPDX-License-Identifier: GPL-3.0-only
 * MuseScore-CLA-applies
 *
 * MuseScore
 * Music Composition & Notation
 *
 * Copyright (C) 2021 MuseScore BVBA and others
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#include "restoreprevioustemposettingsmodel.h"

#include "dataformatter.h"

#include "translation.h"

using namespace mu::inspector;

RestorePreviousTempoSettingsModel::RestorePreviousTempoSettingsModel(QObject* parent, IElementRepositoryService* repository)
    : AbstractInspectorModel(parent, repository)
{
    setModelType(InspectorModelType::TYPE_RESTORE_PREVIOUS_TEMPO);
    setTitle(qtrc("inspector", "Restore previous tempo (a tempo)"));
    setIcon(ui::IconCode::Code::METRONOME);
    createProperties();
}

void RestorePreviousTempoSettingsModel::createProperties()
{
    m_isDefaultTempoForced
        = buildPropertyItem(mu::engraving::Pid::TEMPO_FOLLOW_TEXT, [this](const mu::engraving::Pid pid, const QVariant& newValue) {
        onPropertyValueChanged(pid, newValue);

        emit requestReloadPropertyItems();
    });

    m_tempo = buildPropertyItem(mu::engraving::Pid::TEMPO);
}

void RestorePreviousTempoSettingsModel::requestElements()
{
    m_elementList = m_repository->findElementsByType(mu::engraving::ElementType::TEMPO_TEXT);
}

void RestorePreviousTempoSettingsModel::loadProperties()
{
    loadPropertyItem(m_isDefaultTempoForced);
    loadPropertyItem(m_tempo, formatDoubleFunc);
}

void RestorePreviousTempoSettingsModel::resetProperties()
{
    m_isDefaultTempoForced->resetToDefault();
    m_tempo->resetToDefault();
}

PropertyItem* RestorePreviousTempoSettingsModel::isDefaultTempoForced() const
{
    return m_isDefaultTempoForced;
}

PropertyItem* RestorePreviousTempoSettingsModel::tempo() const
{
    return m_tempo;
}
