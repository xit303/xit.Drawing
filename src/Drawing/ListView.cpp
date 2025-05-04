#include <Drawing/ListView.h>
#include <Threading/Dispatcher.h>

namespace xit::Drawing
{
    void ListView::SetSelectedValue(const std::string &value)
    {
        if (items == nullptr)
        {
            return;
        }

        if (selectedValue != value)
        {
            auto it = std::find(items->begin(), items->end(), value);
            if (it != items->end())
            {
                int index = std::distance(items->begin(), it);
                selectedIndex = index;
                selectedValue = value;
                SingleSelect(selectedIndex);
            }
        }
    }

    void ListView::SetSelectedIndex(int value)
    {
        if (items == nullptr)
        {
            return;
        }
        if ((selectedIndex != value) && (value >= 0) && (value < (int)items->size()))
        {
            selectedIndex = value;
            selectedValue = *std::next(items->begin(), value);
            SingleSelect(selectedIndex);
        }
    }

    void ListView::SetItems(const std::list<std::string> *value)
    {
        // if (items != value)
        {
            if (items != nullptr)
            {
                visibleItems.clear();
                UpdateList();
                updateThread.join();
            }

            int lastSelectedIndex = selectedIndex;

            SetSelectedIndex(-1);
            items = value;

            if (items != nullptr)
            {
                UpdateList();
                if (lastSelectedIndex != -1)
                    SetSelectedIndex(lastSelectedIndex);
            }
        }
    }

    void ListView::SetSelectionMode(Drawing::SelectionMode value)
    {
        if (selectionMode != value)
        {
            selectionMode = value;
        }
    }

    void ListView::SetCanSort(bool value)
    {
        if (canSort != value)
        {
            canSort = value;
            // TODO UpdateCanSort();
        }
    }

    void ListView::SetListViewType(ListViewType value)
    {
        if (listViewType != value)
        {
            listViewType = value;
            UpdateListViewType();
        }
    }

    void ListView::SetFilter(const std::vector<std::string> *value)
    {
        this->filter = value;
        Refresh();
    }

    ListView::ListView()
    {
        headerItemCount = 0;
        isSelectionChanging = false;
        items = nullptr;
        itemsSource = nullptr;
        filter = nullptr;
        listViewType = ListViewType::Text;

        SetClipToBounds(true);
        SetRowSpacing(UIDefaults::MinimumRowSpacing);

        SetBrushGroup("List");
        SetLayoutGroup("List");

        selectionMode = SelectionMode::Single;

        SetRows("Auto");
        canSort = true;

        selectedIndex = -1;
    }

    ListView::~ListView()
    {
        if (updateThread.joinable())
        {
            updateThread.join();
        }
        for (std::thread &thread : threads)
        {
            if (thread.joinable())
                thread.join();
        }
    }

    void ListView::ListViewItem_ActiveChanged(IsActiveProperty &sender, EventArgs &e)
    {
        ListItem *listItem = dynamic_cast<ListItem *>(&sender);

        if (listItem->GetIsActive())
        {
            if (std::find(selectedChildren.begin(), selectedChildren.end(), listItem) == selectedChildren.end())
            {
                int index = GetChildIndex(listItem);

                if (selectionMode == SelectionMode::Single)
                {
                    SetSelectedIndex(index);
                }
                else
                {
                    selectedChildren.push_back(listItem);
                    selectedIndex = index;
                    selectedValue = listItem->GetText();
                    HandleSelectionChanged(&selectedChildren);
                }
            }
        }
    }

    void ListView::UpdateList()
    {
        if (updateThread.joinable())
        {
            updateThread.join();
        }
        for (std::thread &thread : threads)
        {
            if (thread.joinable())
            {
                thread.join();
            }
        }
        threads.clear();

        // updateThread = std::thread([this]
        //                            {
        if (items != nullptr)
        {
            size_t childCount = GetChildCount() - headerItemCount;
            size_t i = 0;

            for (std::string item : *items)
            {
                ListItem *listItem;

                if (i >= childCount)
                {
                    listItem = GetContainerForItemOverride();
                    listItem->SetShowImage(ListViewType::Image == listViewType || ListViewType::ImageText == listViewType);
                    listItem->SetShowLabel(ListViewType::ImageText == listViewType || ListViewType::Text == listViewType);

                    InsertChild(i, listItem);

                    while (GetNumberOfRows() < GetChildCount())
                    {
                        SetRows(GetRows() + ",Auto");
                    }
                }
                else
                {
                    listItem = (ListItem *)GetChildAt(i);
                    if (listItem == nullptr)
                    {
                        continue;
                    }

                    listItem->IsActiveChanged.Remove(&ListView::ListViewItem_ActiveChanged, this);
                }

                listItem->SetRow(i);
                listItem->SetText(item);

                if (ListViewType::Image == listViewType)
                    listItem->SetToolTip(item);

                if (FilterItem(item))
                {
                    listItem->SetVisibility(Visibility::Visible);
                    listItem->IsActiveChanged.Add(&ListView::ListViewItem_ActiveChanged, this);

                    if (std::find(visibleItems.begin(), visibleItems.end(), item) == visibleItems.end())
                    {
                        visibleItems.push_back(item);
                    }
                }
                else
                {
                    if (i == (size_t)selectedIndex)
                    {
                        selectedIndex++;
                    }

                    listItem->SetVisibility(Visibility::Collapsed);
                    visibleItems.remove(item);
                }

                if (i == (size_t)selectedIndex)
                {
                    selectedValue = item;
                    SingleSelect(i);
                }

                threads.push_back(std::thread([this, listItem]
                                              {
                    if (App::IsClosing)
                    {
                        return;
                    }
                    listItem->SetImageSource(listItem->GetText()); 
                    Invalidate(); }));

                i++;
            }

            i = 0;

            for (std::thread &thread : threads)
            {
                if (thread.joinable())
                {
                    thread.join();
                }
            }
            threads.clear();

            if (selectedIndex >= (int)items->size())
            {
                int index = selectedIndex = items->size() - 1;
                selectedValue = index == -1 ? std::string() : *std::next(items->begin(), index);
                SingleSelect(index);
            }
        }

        for (size_t i = items->size(); i < GetChildCount(); i++)
        {
            ListItem *listItem = (ListItem *)GetChildAt(i);

            if (listItem != nullptr)
            {
                // if item is active we have to deactivate it now
                if (listItem->GetIsActive())
                {
                    listItem->SetIsActive(false);
                }

                listItem->IsActiveChanged.Remove(&ListView::ListViewItem_ActiveChanged, this);
                listItem->SetVisibility(Visibility::Collapsed);
                visibleItems.remove(listItem->GetText());
            }
        }

        ApplyFilter();
        needHeightRecalculation = true;

        Invalidate();
        // });
    }

    void ListView::UpdateListViewType()
    {
        // this version should be faster than the commented one
        std::vector<Visual *> &children = GetChildren();
        for (Visual *content : children)
        {
            ListItem *listItem = dynamic_cast<ListItem *>(content);
            if (listItem != nullptr)
            {
                listItem->SetShowImage(ListViewType::Image == listViewType || ListViewType::ImageText == listViewType);
                listItem->SetShowLabel(ListViewType::ImageText == listViewType || ListViewType::Text == listViewType);
            }
        }
    }

    void ListView::SingleSelect(int index)
    {
        if (isSelectionChanging)
        {
            return;
        }
        isSelectionChanging = true;

        // TODO inform clients that current item(s) are no longer selected
        // but create a new event for removed items
        // if (selectedChildren.size() > 0)
        // {
        //     HandleSelectionChanged(&selectedChildren);

        //     // int selectedIndex = this->selectedIndex;
        //     // SelectedIndex = -1;

        //     // SelectedIndex = selectedIndex;
        // }

        for (ListItem *listItem : selectedChildren)
        {
            listItem->SetIsActive(false);
        }

        selectedChildren.clear();

        if (index != -1)
        {
            int childIndex = index + headerItemCount;

            ListItem *listItem = (ListItem *)GetChildAt(childIndex);
            if (listItem == nullptr)
            {
                isSelectionChanging = false;
                return;
            }
            listItem->SetIsActive(true);
            selectedChildren.push_back(listItem);
            listItem->Focus();

            HandleSelectionChanged(&selectedChildren);
        }

        isSelectionChanging = false;
        Invalidate();
    }

    void ListView::HandleSelectionChanged(std::list<ListItem *> *items)
    {
        SelectionChanged(selectedValue);
        OnSelectionChanged(selectedValue);
    }

    void ListView::OnSelectionChanged(const std::string &selectedValue)
    {
        ScrollItemIntoView();
    }

    ListItem *ListView::GetContainerForItemOverride()
    {
        return new ListItem();
    }

    void ListView::OnKeyDown(KeyEventArgs &e)
    {
        // TODO this event is no loger called. Check why!

        if (e.Key == CKey::Up)
        {
            SetSelectedIndex(selectedIndex > 0 ? selectedIndex - 1 : 0);
            e.Handled = true;
        }
        else if (e.Key == CKey::Down)
        {
            SetSelectedIndex(selectedIndex < (int)items->size() - 1 ? selectedIndex + 1 : (int)items->size() - 1);
            e.Handled = true;
        }

        if (!e.Handled)
        {
            ScrollViewer::OnKeyDown(e);
        }
        else
        {
            ScrollItemIntoView();
        }
    }

    bool ListView::FilterItem(const std::string &value)
    {
        if (!filter || filter->size() == 0)
            return true;

        std::string lowerValue = value;
        std::transform(lowerValue.begin(), lowerValue.end(), lowerValue.begin(), [](unsigned char c)
                       { return std::tolower(c); });

        for (std::string filterValue : *filter)
        {
            std::transform(filterValue.begin(), filterValue.end(), filterValue.begin(), [](unsigned char c)
                           { return std::tolower(c); });

            // TODO tolower should not be done all the time (even if this method is not called very often)
            // a possible solution would be to create a copy of the list where all items are already set tolower

            // item should be shown
            if (lowerValue.find(filterValue) != std::string::npos)
                return true;
        }

        // item should not be shown
        return false;
    }

    void ListView::ApplyFilter()
    {
        if (filter != nullptr)
        {
            visibleItems.clear();

            int i = 0;
            for (std::string item : *items)
            {
                ListItem *listItem = (ListItem *)GetChildAt(i++);

                if (FilterItem(item))
                {
                    listItem->SetVisibility(Visibility::Visible);
                    visibleItems.push_back(item);
                }
                else
                {
                    listItem->SetVisibility(Visibility::Collapsed);

                    if ((int)i == selectedIndex)
                    {
                        SetSelectedIndex(-1);
                    }
                }
            }

            if (visibleItems.size() > 0 && !selectedValue.empty())
            {
                if (std::find(visibleItems.begin(), visibleItems.end(), selectedValue) == visibleItems.end())
                {
                    SetSelectedValue(*(visibleItems.begin()));
                    ScrollItemIntoView();
                }
            }
        }
    }

    void ListView::AddHeaderColumn(const std::string &headerTextSource, const std::string &headerDefaultText, const std::string &columnSize)
    {
        headerItemCount++;

        SetColumns(GetColumns() + columnSize);

        if (GetNumberOfRows() == 0)
        {
            SetRows("Auto");
        }

        Label *label = new Label();
        // label->SetTextSource(headerTextSource);
        label->SetText(headerDefaultText);
        label->SetColumn(GetNumberOfColumns() - 1);

        AddChild(label);
    }

    void ListView::ScrollItemIntoView()
    {
        if (GetExtentHeight() <= GetActualHeight())
        {
            return;
        }

        auto it = std::find(visibleItems.begin(), visibleItems.end(), selectedValue);

        if (it != visibleItems.end())
        {
            int index = std::distance(visibleItems.begin(), it);
            double itemHeight = GetChildAt(0)->GetActualHeight();
            double itemTop = (itemHeight * index) + (GetRowSpacing() * index);
            double itemBottom = itemTop + itemHeight;

            if (itemTop < GetVerticalOffset())
            {
                ScrollToVerticalOffset(itemTop);
            }
            else if (itemBottom > (GetVerticalOffset() + GetActualHeight()))
            {
                ScrollToVerticalOffset(itemBottom - GetActualHeight() + GetBorderThickness().GetHeight() + GetPadding().GetHeight());
            }
        }
        Invalidate();
    }

    void ListView::Refresh()
    {
        if (items == nullptr)
        {
            return;
        }

        int i = 0;
        for (std::string item : *items)
        {
            ListItem *listItem = (ListItem *)GetChildAt(i++);
            listItem->SetText(item);
        }

        ApplyFilter();
    }
}
