#pragma once

#include <Drawing/Window.h>
#include <Drawing/UIDefaults.h>
#include <Drawing/TextBox.h>
#include <Drawing/ListView.h>
#include <Drawing/Buttons/Button.h>

namespace xit::Drawing
{
    class FileDialog : protected Window
    {
    private:
        static WindowSettings windowSettings;

        // this is the main container to hold our elements
        Container mainContainer;

        // this is to select folders on the left side
        ListView folderListView;

        // this is to select files or the current folder on the right side
        ListView itemListView;

        // this is to enter the file name or folder name
        TextBox fileNameTextBox;

        // store the selected item
        std::string selectedItem;

        // this is to select the file type
        // DropDown extensionList;

        Button okButton;
        Button cancelButton;

        FileDialog() = default;
        ~FileDialog() = default;
        FileDialog(const FileDialog &) = delete;
        FileDialog &operator=(const FileDialog &) = delete;

        void OnOkButtonClick(InputContent &content, EventArgs &e)
        {
            SetVisibility(Visibility::Hidden);
        }

        void OnCancelButtonClick(InputContent &content, EventArgs &e)
        {
            SetVisibility(Visibility::Hidden);
        }

    protected:
        virtual void OnInitializeComponent() override
        {
            SetPadding(UIDefaults::ContainerPadding);
            mainContainer.SetColumns("250,*");
            mainContainer.SetRows("*,36");
            mainContainer.SetColumnSpacing(UIDefaults::ColumnSpacing);
            mainContainer.SetRowSpacing(UIDefaults::RowSpacing);

            folderListView.SetGrid(0, 0);
            mainContainer.AddChild(&folderListView);

            itemListView.SetGrid(1, 0);
            mainContainer.AddChild(&itemListView);

            fileNameTextBox.SetGrid(0, 1, 2);
            fileNameTextBox.SetHorizontalAlignment(HorizontalAlignment::Stretch);
            mainContainer.AddChild(&fileNameTextBox);

            // okButton.SetText("OK");
            // okButton.SetGrid(0, 2);
            // okButton.SetHorizontalAlignment(HorizontalAlignment::Stretch);
            // okButton.Click.Add(&FileDialog::OnOkButtonClick, this);
            // mainContainer.AddChild(&okButton);

            // cancelButton.SetText("Cancel");
            // cancelButton.SetGrid(1, 2);
            // cancelButton.SetHorizontalAlignment(HorizontalAlignment::Stretch);
            // cancelButton.Click.Add(&FileDialog::OnCancelButtonClick, this);
            // mainContainer.AddChild(&cancelButton);

            SetContent(&mainContainer);
        }

    public:
        static std::string OpenFolderDialog(const std::string &title, const std::string &path)
        {
            // this is the window instance
            static FileDialog instance;
            instance.Initialize(windowSettings, title);
            instance.okButton.SetText("OK");
            instance.okButton.SetToolTip("Select folder");
            instance.fileNameTextBox.SetText(path);
            instance.Show();
            return instance.selectedItem;
        }
        static std::string OpenFileDialog(const std::string &title, const std::string &path)
        {
            // this is the window instance
            static FileDialog instance;
            instance.Initialize(windowSettings, title);
            instance.okButton.SetText("Open");
            instance.okButton.SetToolTip("Select file");
            instance.fileNameTextBox.SetText(path);
            instance.Show();
            return instance.selectedItem;
        }
        static std::string SaveFileDialog(const std::string &title, const std::string &path)
        {
            // this is the window instance
            static FileDialog instance;
            instance.Initialize(windowSettings, title);
            instance.okButton.SetText("Save");
            instance.okButton.SetToolTip("Save file");
            instance.fileNameTextBox.SetText(path);
            instance.Show();
            return instance.selectedItem;
        }
        static std::string SaveFileDialog(const std::string &title, const std::string &path, const std::string &extension)
        {
            // this is the window instance
            static FileDialog instance;
            instance.Initialize(windowSettings, title);
            instance.okButton.SetText("Save");
            instance.okButton.SetToolTip("Save file");
            instance.fileNameTextBox.SetText(path);
            instance.fileNameTextBox.SetText(extension);
            instance.Show();
            return instance.selectedItem;
        }
    };

    WindowSettings FileDialog::windowSettings = WindowSettings("FileDialog", 800, 600, WindowState::Normal);
}
