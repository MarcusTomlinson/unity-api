/*
 * Copyright (C) 2015 Canonical, Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef MOCKFILTERS_H
#define MOCKFILTERS_H

#include <unity/shell/scopes/FiltersInterface.h>
#include <unity/shell/scopes/FilterBaseInterface.h>
#include <unity/shell/scopes/ScopeInterface.h>

#include <QList>

class MockFiltersModel : public unity::shell::scopes::FiltersInterface
{
    Q_OBJECT

public:
    explicit MockFiltersModel(unity::shell::scopes::ScopeInterface *parent = 0);

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;

private:
    QList<unity::shell::scopes::FilterBaseInterface*> m_filters;
};

#endif // MOCKDEPARTMENT_H
