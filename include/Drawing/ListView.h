#pragma once

#include <Drawing/ScrollViewer.h>
#include <Drawing/ListItem.h>
#include <Drawing/SelectionMode.h>

namespace xit::Drawing
{
    enum class ListViewType
    {
        Text,
        Image,
        ImageText
    };

    class ListView : public ScrollViewer
    {
    private:
        std::vector<std::thread> threads;
        std::thread updateThread;
        int headerItemCount;
        std::list<std::string> visibleItems;
        const std::list<std::string> *items;

        bool isSelectionChanging;
        std::list<ListItem *> selectedChildren;
        std::string selectedValue;
        int selectedIndex;

        std::list<std::string> *itemsSource;
        SelectionMode selectionMode;

        bool canSort;
        const std::vector<std::string> *filter;
        ListViewType listViewType;

        void ListViewItem_ActiveChanged(IsActiveProperty &sender, EventArgs &e);

        void UpdateListViewType();
        void SingleSelect(int index);

        void HandleSelectionChanged(std::list<ListItem *> *items);

    protected:
        virtual void OnSelectionChanged(const std::string &selectedValue);

        virtual ListItem *GetContainerForItemOverride();

        void OnKeyDown(KeyEventArgs &e) override;

        bool FilterItem(const std::string &value);
        void ApplyFilter();

    public:
        __always_inline const std::string &GetSelectedValue() const { return selectedValue; }
        void SetSelectedValue(const std::string &value);

        __always_inline int GetSelectedIndex() const { return selectedIndex; }
        void SetSelectedIndex(int value);

        __always_inline const std::list<std::string> *GetItems() { return items; }
        void SetItems(const std::list<std::string> *value);

        __always_inline SelectionMode GetSelectionMode() const { return selectionMode; }
        void SetSelectionMode(Drawing::SelectionMode value);

        __always_inline bool GetCanSort() const { return canSort; }
        void SetCanSort(bool value);

        __always_inline ListViewType GetListViewType() const { return listViewType; }
        void SetListViewType(ListViewType value);

        void SetFilter(const std::vector<std::string> *value);

        Event<const std::string &> SelectionChanged;

        ListView();
        ~ListView();

        void UpdateList();

        void AddHeaderColumn(const std::string &headerTextSource, const std::string &headerDefaultText, const std::string &columnSize);

        void ScrollItemIntoView();

        void Refresh();
    };
}
using namespace xit::Drawing;
