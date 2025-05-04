#include <Drawing/MainMenu.h>

namespace xit::Drawing
{
    void MainMenu::SetDockType(DockType value)
    {
        if (dockType != value)
        {
            dockType = value;
            UpdateDock();
        }
    }

    void MainMenu::SetMenuOrientationDirection(const OrientationDirection &value)
    {
        if (menuOrientationDirection != value)
        {
            menuOrientationDirection = value;
            UpdateMenuOrientationDirection();
        }
    }

    MainMenu::MainMenu()
        : mainMenuSettings(nullptr),
          // dockTypeSetting(nullptr),
          // menuOrientationSetting(nullptr),
          // menuOrientationDirectionSetting(nullptr)
          menuOrientationDirection(OrientationDirection::Normal),
          dockType(DockType::Top),
          isInitialized(false),
          isUpdating(false),
          mainMenuItemCount(0)
    {
        mainMenuToggleButtonGroup.SetBrushGroup("MainMenu");
        mainMenuToggleButtonGroup.SetLayoutGroup("MainMenu");
        mainMenuToggleButtonGroup.SetColumns("Auto");
        mainMenuToggleButtonGroup.SetRows("Auto,*");
        mainMenuToggleButtonGroup.SetHorizontalAlignment(HorizontalAlignment::Stretch);
        mainMenuToggleButtonGroup.SetVerticalAlignment(VerticalAlignment::Top);
        mainMenuToggleButtonGroup.SetHorizontalContentAlignment(HorizontalAlignment::Center);

        mainMenuToggleButtonGroup.ToggleButtonChecked.Add(&MainMenu::MainMenuToggleButtonGroup_ToggleButtonChecked, this);
        mainMenuToggleButtonGroup.GroupClosed.Add(&MainMenu::MainMenuToggleButtonGroup_GroupClosed, this);
        SetPanel1(&mainMenuToggleButtonGroup);

        mainMenuContentContainer.SetBrushGroup("MainMenuContent");
        mainMenuContentContainer.SetHorizontalAlignment(HorizontalAlignment::Center);
        mainMenuContentContainer.SetVerticalAlignment(VerticalAlignment::Top);

        mainMenuContentContainer.SetMinWidth(700);
        mainMenuContentContainer.SetMaxWidth(1400);
        mainMenuContentContainer.SetVisibility(Visibility::Collapsed);
        mainMenuContentContainer.SetRow(1);
        // mainMenuContentContainer.SetMargin(UIDefaults::ContainerPadding);
        SetPanel2(&mainMenuContentContainer);

        // InstanceHandler<MainMenuSettings>::RequestInstance(&MainMenu::InstanceRequestComplete, this);
    }

    void MainMenu::InstanceRequestComplete(MainMenuSettings *requestedInstance)
    {
        mainMenuSettings = requestedInstance;

        // menuOrientationSetting = mainMenuSettings->GetMenuOrientation();
        // menuOrientationSetting->ValueChanged.Add(&MainMenu::MenuOrientationSetting_ValueChanged, this);
        // SetOrientation(menuOrientationSetting->Value());

        // menuOrientationDirectionSetting = mainMenuSettings->GetMenuOrientationDirection();
        // menuOrientationDirectionSetting->ValueChanged.Add(&MainMenu::MenuOrientationDirectionSetting_ValueChanged, this);
        // SetMenuOrientationDirection(menuOrientationDirectionSetting->Value());

        // dockTypeSetting = mainMenuSettings->GetMenuDockType();
        // dockTypeSetting->ValueChanged.Add(&MainMenu::DockTypeSetting_ValueChanged, this);
        // SetDockType(dockTypeSetting->Value());

        isInitialized = true;

        OnSetMainMenuSettings(mainMenuSettings);

        UpdateDock();
    }

    // void MenuOrientationSetting_ValueChanged(const Orientation &newValue)
    // {
    //     SetOrientation(newValue);
    // }
    // void MenuOrientationDirectionSetting_ValueChanged(const OrientationDirection &newValue)
    // {
    //     SetMenuOrientationDirection(newValue);
    // }
    // void DockTypeSetting_ValueChanged(const DockType &newValue)
    // {
    //     SetDockType(newValue);
    // }

    void MainMenu::UpdateDock()
    {
        if (isUpdating || !isInitialized)
        {
            return;
        }

        isUpdating = true;
        std::string columnsOrRows = "Auto";
        for (int i = 1; i < mainMenuItemCount; i++)
        {
            columnsOrRows += ",Auto";
        }

        // Set similar things first
        switch (dockType)
        {
        // Attention: Orientation is the orientation of the Split Container which is the base class not the orientation of the menu
        case DockType::Top:
            // Menu Top centered

            SetOrientation(Orientation::Vertical);
            SetOrientationDirection(OrientationDirection::Normal);

            mainMenuToggleButtonGroup.SetOrientation(Orientation::Horizontal);
            mainMenuToggleButtonGroup.SetVerticalContentAlignment(VerticalAlignment::Stretch);
            mainMenuToggleButtonGroup.SetHorizontalContentAlignment(HorizontalAlignment::Center);

            GetPanel1()->SetBorderThickness(0, 0, 0, 1);

            // MainMenuContentContainer.SetHorizontalAlignment(HorizontalAlignment::Center);
            // MainMenuContentContainer.SetVerticalAlignment(VerticalAlignment::Top);
            break;

        case DockType::Bottom:
            // Menu Bottom centered

            SetOrientation(Orientation::Vertical);
            SetOrientationDirection(OrientationDirection::Inverted);

            mainMenuToggleButtonGroup.SetOrientation(Orientation::Horizontal);
            mainMenuToggleButtonGroup.SetVerticalContentAlignment(VerticalAlignment::Stretch);
            mainMenuToggleButtonGroup.SetHorizontalContentAlignment(HorizontalAlignment::Center);

            GetPanel1()->SetBorderThickness(0, 1, 0, 0);

            // MainMenuContentContainer.SetHorizontalAlignment(HorizontalAlignment::Center);
            // MainMenuContentContainer.SetVerticalAlignment(VerticalAlignment::Bottom);
            break;

        case DockType::Left:
            // Menu Left centered

            SetOrientation(Orientation::Horizontal);
            SetOrientationDirection(OrientationDirection::Normal);

            mainMenuToggleButtonGroup.SetOrientation(Orientation::Vertical);
            mainMenuToggleButtonGroup.SetHorizontalContentAlignment(HorizontalAlignment::Left);
            mainMenuToggleButtonGroup.SetVerticalContentAlignment(VerticalAlignment::Center);

            GetPanel1()->SetBorderThickness(0, 0, 1, 0);

            // MainMenuContentContainer.SetVerticalAlignment(VerticalAlignment::Center);
            // MainMenuContentContainer.SetHorizontalAlignment(HorizontalAlignment::Left);
            break;

        case DockType::Right:
            // Menu Right centered

            SetOrientation(Orientation::Horizontal);
            SetOrientationDirection(OrientationDirection::Inverted);

            mainMenuToggleButtonGroup.SetOrientation(Orientation::Vertical);
            mainMenuToggleButtonGroup.SetHorizontalContentAlignment(HorizontalAlignment::Right);
            mainMenuToggleButtonGroup.SetVerticalContentAlignment(VerticalAlignment::Center);

            GetPanel1()->SetBorderThickness(1, 0, 0, 0);

            // MainMenuContentContainer.SetVerticalAlignment(VerticalAlignment::Center);
            // MainMenuContentContainer.SetHorizontalAlignment(HorizontalAlignment::Right);
            break;

        case DockType::TopLeftCorner:
            switch (Orientation())
            {
            case Orientation::Horizontal:
                // Menu Top Left to Bottom Left

                SetOrientationDirection(OrientationDirection::Normal);

                mainMenuToggleButtonGroup.SetOrientation(Orientation::Vertical);
                mainMenuToggleButtonGroup.SetHorizontalContentAlignment(HorizontalAlignment::Stretch);
                mainMenuToggleButtonGroup.SetVerticalContentAlignment(VerticalAlignment::Top);

                GetPanel1()->SetBorderThickness(0, 0, 1, 0);
                break;

            case Orientation::Vertical:
                // Menu Top Left to Top Right

                SetOrientationDirection(OrientationDirection::Normal);

                mainMenuToggleButtonGroup.SetOrientation(Orientation::Horizontal);
                mainMenuToggleButtonGroup.SetHorizontalContentAlignment(HorizontalAlignment::Left);
                mainMenuToggleButtonGroup.SetVerticalContentAlignment(VerticalAlignment::Stretch);

                GetPanel1()->SetBorderThickness(0, 0, 0, 1);
                break;
            }
            break;

        case DockType::TopRightCorner:
            switch (Orientation())
            {
            case Orientation::Horizontal:
                // Menu Top Right to Bottom Right
                SetOrientationDirection(OrientationDirection::Inverted);

                mainMenuToggleButtonGroup.SetOrientation(Orientation::Vertical);
                mainMenuToggleButtonGroup.SetHorizontalContentAlignment(HorizontalAlignment::Stretch);
                mainMenuToggleButtonGroup.SetVerticalContentAlignment(VerticalAlignment::Top);

                GetPanel1()->SetBorderThickness(1, 0, 0, 0);
                break;

            case Orientation::Vertical:
                // Menu Top Right to Top left

                SetOrientationDirection(OrientationDirection::Normal);

                mainMenuToggleButtonGroup.SetOrientation(Orientation::Horizontal);
                mainMenuToggleButtonGroup.SetHorizontalContentAlignment(HorizontalAlignment::Right);
                mainMenuToggleButtonGroup.SetVerticalContentAlignment(VerticalAlignment::Stretch);

                GetPanel1()->SetBorderThickness(0, 0, 0, 1);
                break;
            }
            break;

        case DockType::BottomLeftCorner:
            switch (Orientation())
            {
            case Orientation::Horizontal:
                // Menu Bottom Left to Top Left

                SetOrientationDirection(OrientationDirection::Normal);

                mainMenuToggleButtonGroup.SetOrientation(Orientation::Vertical);
                mainMenuToggleButtonGroup.SetHorizontalContentAlignment(HorizontalAlignment::Stretch);
                mainMenuToggleButtonGroup.SetVerticalContentAlignment(VerticalAlignment::Bottom);

                GetPanel1()->SetBorderThickness(0, 0, 1, 0);
                break;

            case Orientation::Vertical:
                // Menu Bottom Left to Bottom Right

                SetOrientationDirection(OrientationDirection::Inverted);

                mainMenuToggleButtonGroup.SetOrientation(Orientation::Horizontal);
                mainMenuToggleButtonGroup.SetHorizontalContentAlignment(HorizontalAlignment::Left);
                mainMenuToggleButtonGroup.SetVerticalContentAlignment(VerticalAlignment::Stretch);

                GetPanel1()->SetBorderThickness(0, 1, 0, 0);
                break;
            }
            break;

        case DockType::BottomRightCorner:

            switch (Orientation())
            {
            case Orientation::Horizontal:
                // Menu Bottom Right to Top Right

                SetOrientationDirection(OrientationDirection::Inverted);

                mainMenuToggleButtonGroup.SetOrientation(Orientation::Vertical);
                mainMenuToggleButtonGroup.SetHorizontalContentAlignment(HorizontalAlignment::Stretch);
                mainMenuToggleButtonGroup.SetVerticalContentAlignment(VerticalAlignment::Bottom);

                GetPanel1()->SetBorderThickness(1, 0, 0, 0);
                break;

            case Orientation::Vertical:
                // Menu Bottom Right to Bottom Left

                SetOrientationDirection(OrientationDirection::Inverted);

                mainMenuToggleButtonGroup.SetOrientation(Orientation::Horizontal);
                mainMenuToggleButtonGroup.SetHorizontalContentAlignment(HorizontalAlignment::Right);
                mainMenuToggleButtonGroup.SetVerticalContentAlignment(VerticalAlignment::Stretch);

                GetPanel1()->SetBorderThickness(0, 1, 0, 0);
                break;
            }

            break;

        case DockType::Fill:
        default:
            break;
        }

        // now only the unique ones
        switch (dockType)
        {
            // case DockType::TopLeftCorner:
            //     switch (Orientation)
            //     {
            //         case Orientation::Horizontal:
            //             MainMenuContentContainer.SetHorizontalAlignment(HorizontalAlignment::Left;
            //             MainMenuContentContainer.SetVerticalAlignment(VerticalAlignment::Top;
            //             break;

            //        case Orientation::Vertical:
            //            MainMenuContentContainer.SetVerticalAlignment(VerticalAlignment::Top;
            //            MainMenuContentContainer.SetHorizontalAlignment(HorizontalAlignment::Left;
            //            break;
            //    }
            //    break;

            // case DockType::BottomLeftCorner:

            //    switch (Orientation)
            //    {
            //        case Orientation::Horizontal:
            //            MainMenuContentContainer.SetHorizontalAlignment(HorizontalAlignment::Left;
            //            MainMenuContentContainer.SetVerticalAlignment(VerticalAlignment::Bottom;
            //            break;

            //        case Orientation::Vertical:
            //            MainMenuContentContainer.SetVerticalAlignment(VerticalAlignment::Bottom;
            //            MainMenuContentContainer.SetHorizontalAlignment(HorizontalAlignment::Left;
            //            break;
            //    }

            //    break;

            // case DockType::TopRightCorner:
            //     switch (Orientation)
            //     {
            //         case Orientation::Horizontal:
            //             MainMenuContentContainer.SetHorizontalAlignment(HorizontalAlignment::Right;
            //             MainMenuContentContainer.SetVerticalAlignment(VerticalAlignment::Top;
            //             break;

            //        case Orientation::Vertical:
            //            MainMenuContentContainer.SetVerticalAlignment(VerticalAlignment::Top;
            //            MainMenuContentContainer.SetHorizontalAlignment(HorizontalAlignment::Right;
            //            break;
            //    }
            //    break;

            // case DockType::BottomRightCorner:

            //    switch (Orientation)
            //    {
            //        case Orientation::Horizontal:
            //            MainMenuContentContainer.SetHorizontalAlignment(HorizontalAlignment::Right;
            //            MainMenuContentContainer.SetVerticalAlignment(VerticalAlignment::Bottom;
            //            break;

            //        case Orientation::Vertical:
            //            MainMenuContentContainer.SetVerticalAlignment(VerticalAlignment::Bottom;
            //            MainMenuContentContainer.SetHorizontalAlignment(HorizontalAlignment::Right;
            //            break;
            //    }

            //    break;

        case DockType::Fill:
        default:
            break;
        }

        UpdateMenuOrientationDirection();

        isUpdating = false;
    }

    void MainMenu::UpdateMenuOrientationDirection()
    {
        mainMenuToggleButtonGroup.SetOrientationDirection(menuOrientationDirection);
    }

    void MainMenu::MainMenuToggleButtonGroup_ToggleButtonChecked(Container &sender)
    {
        EventArgs e;
        OnMenuOpened(e);
        SetPanel2(&mainMenuContentContainer);
    }
    void MainMenu::MainMenuToggleButtonGroup_GroupClosed(ToggleButtonGroup &sender)
    {
        EventArgs e;
        OnMenuClosed(e);
    }

    // void MainMenu::OnOrientationChanged() override
    // {
    //     // check if initialized
    //     if (GetMainMenuContentContainer() != nullptr)
    //     {
    //         UpdateDock();
    //     }

    //     if (menuOrientationSetting != nullptr)
    //     {
    //         menuOrientationSetting->SetValue(Orientation());
    //     }

    //     SplitContainer::OnOrientationChanged();
    // }

    void MainMenu::OnMenuOpened(EventArgs &e)
    {
        // TODO handle ...
        MenuOpened(e);
    }
    void MainMenu::OnMenuClosed(EventArgs &e)
    {
        MenuClosed(e);
    }

    MainMenuButton *MainMenu::AddButton(const std::string &name, const std::string &defaultText, const std::string &defaultToolTip, Visual *target)
    {
        MainMenuButton *button = new MainMenuButton();
        button->SetName(name);
        button->SetColumn(mainMenuItemCount++);

        // button->SetTextSource(name);
        button->SetText(defaultText);
        button->SetToolTip(defaultToolTip);

        std::string tmp = defaultText;
        // std::replace(tmp.begin(), tmp.end(), " ", "");
        //  std::string tmp = String::ReplaceAll(defaultText, " ", "");
        button->SetImageSource("Resources/Images/Menu/" + tmp + ".png");

        if (target)
        {
            target->SetIsVisible(false);
            button->SetTarget(target);
        }

        if (Orientation() == Orientation::Horizontal)
        {
            mainMenuToggleButtonGroup.SetColumns(mainMenuToggleButtonGroup.GetColumns() + ",Auto");
        }
        else
        {
            mainMenuToggleButtonGroup.SetRows(mainMenuToggleButtonGroup.GetRows() + ",Auto");
        }

        mainMenuToggleButtonGroup.AddChild(button);

        if (target)
        {
            mainMenuContentContainer.AddChild(target);
            target->SetGrid(0, 1);
        }

        return button;
    }

    void MainMenu::OnSetMainMenuSettings(MainMenuSettings *mainMenuSettings)
    {
        for (Visual *content : mainMenuToggleButtonGroup.GetChildren())
        {
            MainMenuButton *button = dynamic_cast<MainMenuButton *>(content);

            if (button)
                button->SetMainMenuSettings(mainMenuSettings);
        }
    }

    // void MainMenu::ToggleButton(int index)
    // {
    //     if (index < MainMenuToggleButtonGroup.GetChildren().size())
    //     {
    //         Visual *content = MainMenuToggleButtonGroup.Children[index];
    //         MainMenuButton *button = dynamic_cast<MainMenuButton *>(content);

    //         if (button && button->GetIsVisible())
    //         {
    //             button->SetIsActive(!button->GetIsActive());
    //         }
    //     }
    // }
}