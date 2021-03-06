/*
 * Copyright (C) 2014 Canonical, Ltd.
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

#ifndef UNITY_SHELL_SCOPES_SCOPEINTERFACE_H
#define UNITY_SHELL_SCOPES_SCOPEINTERFACE_H

#include <unity/SymbolExport.h>

#include <QObject>
#include <QVariantMap>

namespace unity
{
namespace shell
{
namespace scopes
{

class CategoriesInterface;
class PreviewModelInterface;
class NavigationInterface;
class SettingsModelInterface;
class FiltersInterface;
class FilterBaseInterface;

/**
 * @brief Object representing scope instance, which exposes model(s) with results.
 */
class UNITY_API ScopeInterface : public QObject
{
    Q_OBJECT

    /**
     * @brief Id of the scope.
     */
    Q_PROPERTY(QString id READ id NOTIFY idChanged)

    /**
     * @brief Display name of the scope.
     */
    Q_PROPERTY(QString name READ name NOTIFY nameChanged)

    /**
     * @brief URI to scope's icon.
     */
    Q_PROPERTY(QString iconHint READ iconHint NOTIFY iconHintChanged)

    /**
     * @brief Description of the scope.
     */
    Q_PROPERTY(QString description READ description NOTIFY descriptionChanged)

    /**
     * @brief Hint to display in the search field.
     */
    Q_PROPERTY(QString searchHint READ searchHint NOTIFY searchHintChanged)

    /**
     * @brief Boolean specifying whether a search is currently running.
     */
    Q_PROPERTY(bool searchInProgress READ searchInProgress NOTIFY searchInProgressChanged)

    /**
     * @brief Boolean specifying whether an activation request is currently running.
     */
    Q_PROPERTY(bool activationInProgress READ activationInProgress NOTIFY activationInProgressChanged)

    /**
     * @brief Boolean specifying whether the scope is favourited.
     */
    Q_PROPERTY(bool favorite READ favorite WRITE setFavorite NOTIFY favoriteChanged)
    /**
     * @brief Keyboard shortcut used to summon the scope.
     */
    Q_PROPERTY(QString shortcut READ shortcut NOTIFY shortcutChanged)

    /**
     * @brief Categories model for scope's results.
     */
    Q_PROPERTY(unity::shell::scopes::CategoriesInterface* categories READ categories NOTIFY categoriesChanged)

    /**
     * @brief Settings model for the scope.
     */
    Q_PROPERTY(unity::shell::scopes::SettingsModelInterface* settings READ settings NOTIFY settingsChanged)

    /**
     * @brief
     */
    Q_PROPERTY(unity::shell::scopes::FilterBaseInterface* primaryNavigationFilter READ primaryNavigationFilter NOTIFY primaryNavigationFilterChanged)

    /**
     * @brief Current search query.
     *
     * Writing to this property issues a new search to the scope.
     */
    Q_PROPERTY(QString searchQuery READ searchQuery WRITE setSearchQuery NOTIFY searchQueryChanged)

    /**
     * @brief Message to display when there are no results after a search.
     */
    Q_PROPERTY(QString noResultsHint READ noResultsHint WRITE setNoResultsHint NOTIFY noResultsHintChanged)

    /**
     * @brief Form factor which is sent with search queries.
     *
     * Form factor is one of scope inputs and be used by it to fine-tune the results.
     *
     * TODO Document the supported for factors
     */
    Q_PROPERTY(QString formFactor READ formFactor WRITE setFormFactor NOTIFY formFactorChanged)

    /**
     * @brief Boolean specifying whether the scope is currently active.
     */
    Q_PROPERTY(bool isActive READ isActive WRITE setActive NOTIFY isActiveChanged)

    /**
     * @brief String specifying currently selected department
     */
    Q_PROPERTY(QString currentNavigationId READ currentNavigationId NOTIFY currentNavigationIdChanged)

    /**
     * @brief Boolean specifying whether current query has departments.
     */
    Q_PROPERTY(bool hasNavigation READ hasNavigation NOTIFY hasNavigationChanged)

    /**
     * @brief VariantMap with customization properties
     */
    Q_PROPERTY(QVariantMap customizations READ customizations NOTIFY customizationsChanged)

    /**
     * @brief Enum representing the status of the scope.
     */
    Q_PROPERTY(unity::shell::scopes::ScopeInterface::Status status READ status NOTIFY statusChanged)

    /**
     * @brief Filters model for the scope.
     */
    Q_PROPERTY(unity::shell::scopes::FiltersInterface* filters READ filters NOTIFY filtersChanged)

    /**
     * @brief Label for the currently active top level navigation (department or primary filter).
     */
    Q_PROPERTY(QString primaryNavigationTag READ primaryNavigationTag NOTIFY primaryNavigationTagChanged)

    /**
     * @brief The number of currently selected filters.
     */
    Q_PROPERTY(int activeFiltersCount READ activeFiltersCount NOTIFY activeFiltersCountChanged)

protected:
    /// @cond
    explicit ScopeInterface(QObject* parent = 0) : QObject(parent) { }
    /// @endcond

public:
    /**
     * @brief Status info code following the last operation
     */
    enum class Status
    {
        Okay,                           // Everything is fine
        NoInternet,                     // No Internet access
        NoLocationData,                 // No location data available
        Unknown,                        // A code unknown to the run-time was used
    };
    Q_ENUM(Status)

    // @cond
    virtual QString id() const = 0;
    virtual QString name() const = 0;
    virtual QString iconHint() const = 0;
    virtual QString description() const = 0;
    virtual QString searchHint() const = 0;
    virtual QString shortcut() const = 0;
    virtual bool searchInProgress() const = 0;
    virtual bool activationInProgress() const = 0;
    virtual bool favorite() const = 0;
    virtual CategoriesInterface* categories() const = 0;
    virtual SettingsModelInterface* settings() const = 0;
    virtual FilterBaseInterface* primaryNavigationFilter() const = 0;
    virtual QString searchQuery() const = 0;
    virtual QString noResultsHint() const = 0;
    virtual QString formFactor() const = 0;
    virtual bool isActive() const = 0;
    virtual QString currentNavigationId() const = 0;
    virtual bool hasNavigation() const = 0;
    virtual Status status() const = 0;
    virtual QVariantMap customizations() const = 0;
    virtual FiltersInterface* filters() const = 0;
    virtual QString primaryNavigationTag() const = 0;
    virtual int activeFiltersCount() const = 0;

    /* setters */
    virtual void setSearchQuery(const QString& search_query) = 0;
    virtual void setNoResultsHint(const QString& hint) = 0;
    virtual void setFormFactor(const QString& form_factor) = 0;
    virtual void setActive(const bool) = 0;
    virtual void setFavorite(const bool) = 0;
    // @endcond

    /**
     * @brief Method used to activate a result.
     */
    Q_INVOKABLE virtual void activate(QVariant const& result, QString const& categoryId) = 0;

    /**
     * @brief Method used to preview a result.
     *
     * Returns a new PreviewModelInterface instance. It's caller's responsibility
     * to free it.
     */
    Q_INVOKABLE virtual unity::shell::scopes::PreviewModelInterface* preview(QVariant const& result, QString const& categoryId) = 0;

    /**
     * @brief Cancels the current activation.
     */
    Q_INVOKABLE virtual void cancelActivation() = 0;

    /**
     * @brief Closes the temporary scope which got opened when openScope was emitted.
     */
    Q_INVOKABLE virtual void closeScope(unity::shell::scopes::ScopeInterface* scope) = 0;

    /**
     * @brief Get a NavigationInterface instance for the passed navigationId.
     */
    Q_INVOKABLE virtual unity::shell::scopes::NavigationInterface* getNavigation(QString const& navigationId) = 0;

    /**
     * @brief Request change to the current navigation id.
     */
    Q_INVOKABLE virtual void setNavigationState(QString const& navId) = 0;

    /**
     * @brief Execute canned query.
     */
    Q_INVOKABLE virtual void performQuery(QString const& cannedQuery) = 0;

    /**
     * @brief Force refresh of the scope contents.
     */
    Q_INVOKABLE virtual void refresh() = 0;

    /**
     * @brief Reset primary navigation filter and its tag in the search bar.
     */
    Q_INVOKABLE virtual void resetPrimaryNavigationTag() = 0;

    /**
     * @brief Reset filters to default values.
     */
    Q_INVOKABLE virtual void resetFilters() = 0;

    /*
     * @brief Method used to activate an action of a result.
     */
    Q_INVOKABLE virtual void activateAction(QVariant const& result, QString const& categoryId, QString const& actionId) = 0;

Q_SIGNALS:
    // @cond
    void idChanged();
    void nameChanged();
    void iconHintChanged();
    void descriptionChanged();
    void searchHintChanged();
    void searchInProgressChanged();
    void activationInProgressChanged();
    void favoriteChanged();
    void shortcutChanged();
    void categoriesChanged();
    void settingsChanged();
    void searchQueryChanged();
    void noResultsHintChanged();
    void formFactorChanged();
    void isActiveChanged();
    void hasNavigationChanged();
    void currentNavigationIdChanged();
    void customizationsChanged();
    void statusChanged();
    void detailsChanged();
    void filtersChanged();
    void primaryNavigationTagChanged();
    void activeFiltersCountChanged();
    void primaryNavigationFilterChanged();
    // @endcond

    // signals triggered by activate(..) or preview(..) requests.
    /**
     * @brief Signal requesting to show the dash.
     *
     * This signal is usually emitted after activating a result.
     */
    void showDash();

    /**
     * @brief Signal requesting to hide the dash.
     *
     * This signal is usually emitted after activating a result.
     */
    void hideDash();

    /**
     * @brief Signal requesting to open a uri.
     *
     * This signal is usually emitted after activating a result.
     */
    void gotoUri(QString const& uri);

    /**
     * @brief Signal requesting to preview a result.
     *
     * This signal is usually emitted after activating a result.
     */
    void previewRequested(QVariant const& result);

    /**
     * @brief Signal requesting to change the currently focused scope.
     */
    void gotoScope(QString const& scopeId);

    /**
     * @brief Signal requesting to show a temporary scope.
     */
    void openScope(unity::shell::scopes::ScopeInterface* scope);
};

}
}
}

Q_DECLARE_METATYPE(unity::shell::scopes::ScopeInterface*)

#endif
