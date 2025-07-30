#include <Drawing/Pages/LoginPageBase.h>
#include <Account/AccountManager.h>
#include <Security/Protector.h>
#include <Input/InputHandler.h>
#include <cmath>

namespace xit::Drawing::Pages
{
    using namespace xit::Security;

    const std::string LoginPageBase::Start = "START";
    const std::string LoginPageBase::Download = "CREATE ACCOUNT";
    const std::string LoginPageBase::Abort = "EXIT";

    const std::string LoginPageBase::RememberAccount = "Remember account";
    const std::string LoginPageBase::RememberPassword = "Remember password";
    const std::string LoginPageBase::AutoLogin = "Auto login";

    const std::string LoginPageBase::AccountHint = "Account";
    const std::string LoginPageBase::Password = "Password";

    const std::string LoginPageBase::AccountNotFound = "Account selection error!";
    const std::string LoginPageBase::AccountNotFoundDetails = "Last account with name [%s] not found in accounts path";

    const std::string LoginPageBase::AccountListEmpty = "No accounts found";
    const std::string LoginPageBase::AccountListEmptyDetails = "Enter account name and a password and press \"Create Account\"";

    const std::string LoginPageBase::AccountNameEmpty = "Account name must not be empty";
    const std::string LoginPageBase::AccountNameValid = "Account name valid";
    const std::string LoginPageBase::AccountNameValidDetails = "Enter a password and press \"Create Account\"";

    const std::string LoginPageBase::AutoLoginInfo = "Auto login!";
    const std::string LoginPageBase::EnterPasswordInfo = "Please enter your password";

    const std::string LoginPageBase::InvalidEmailInfo = "Invalid email address";
    const std::string LoginPageBase::InvalidEmailDetails = "Must be of kind xxx@yyy.zz";

    const std::string LoginPageBase::PasswordEmptyInfo = "Password must not be empty";
    const std::string LoginPageBase::WrongPasswordInfo = "Wrong password";

    void LoginPageBase::SetInfoHeaderTextSource(const std::string &value) { infoHeaderText.SetText(value); }
    void LoginPageBase::SetInfoDetailsTextSource(const std::string &value) { infoDetailsText.SetText(value); }

    void LoginPageBase::SetLoginButtonTextSource(const std::string &value) { loginButton.SetText(value); }
    void LoginPageBase::SetAbortButtonTextSource(const std::string &value) { abortButton.SetText(value); }

    bool LoginPageBase::GetIsAutoLoginVisible() { return false; } // TODO autoLogin.GetIsVisible(); }
    void LoginPageBase::SetIsAutoLoginVisible(bool value) { /* TODO autoLogin.SetIsVisible(value); */ }

    bool LoginPageBase::GetIsLoginButtonEnabled() { return loginButton.GetEnabled(); }
    void LoginPageBase::SetIsLoginButtonEnabled(bool value) { loginButton.SetEnabled(value); }

    void LoginPageBase::InitializeTextSources()
    {
        // TextSource::AddSource(nameof(Start), "START " + App::Name);
        // TextSource::AddSource(nameof(Download), "CREATE ACCOUNT");
        // TextSource::AddSource(nameof(Abort), "EXIT");

        // TextSource::AddSource(nameof(RememberAccount), "Remember account");
        // TextSource::AddSource(nameof(RememberPassword), "Remember password");
        // TextSource::AddSource(nameof(AutoLogin), "Auto login");

        // TextSource::AddSource(nameof(AccountHint), "Account");
        // TextSource::AddSource(nameof(PasswordHint), "Password");

        // TextSource::AddSource(nameof(AccountNotFound), "Account selection error!");
        // TextSource::AddSource(nameof(AccountNotFoundDetails), "Last account with name [%s] not found in accounts path");
        // TextSource::AddSource(nameof(AccountListEmpty), "No accounts found");
        // TextSource::AddSource(nameof(AccountListEmptyDetails), "Enter account name and a password and press \"Create Account\"");
        // TextSource::AddSource(nameof(AccountNameEmpty), "Account name must not be empty");
        // TextSource::AddSource(nameof(AccountNameValid), "Account name valid");
        // TextSource::AddSource(nameof(AccountNameValidDetails), "Enter a password and press \"Create Account\"");

        // TextSource::AddSource(nameof(AutoLoginInfo), "Auto start!");
        // TextSource::AddSource(nameof(EnterPasswordInfo), "Please enter your password");
        // // TextSource::AddSource(nameof(EnterToStart), "Press enter to start.");
        // // TextSource::AddSource(nameof(PleaseLoginInfo), "Please enter account name and password.");

        // TextSource::AddSource(nameof(InvalidEmailInfo), "Invalid email address");
        // TextSource::AddSource(nameof(InvalidEmailDetails), "Must be of kind xxx@yyy.zz");
        // TextSource::AddSource(nameof(PasswordEmptyInfo), "Password must not be empty");
        // TextSource::AddSource(nameof(WrongPasswordInfo), "Wrong password");
    }

    LoginPageBase::LoginPageBase()
    {
        InitializeTextSources();
        // App::ReportProgress.Add(&LoginPageBase::SetProgressBar, this);

        // try
        {
            AccountManager::Initialize();
        }
        // catch (Exception ex)
        {
            // Logger::Log("LoginPage", ex);
            // MessageBox.Show(nameof(AccountManager.Initialize) + " failed.\n" + ex.Message);
            // Close();
        }

        SetLayoutGroup("LoginPage");
        SetName("LoginPageBase");

        canCreateAccount = true;
        canPreload = true;
        forcePassword = true;
        isEmailAccount = false;
        isLoginSuccess = false;  // Initialize isLoginSuccess

        SetZIndex(1);

        SetColumns("*,*,350,*,*");
        SetColumnSpacing(UIDefaults::ColumnSpacing);

        SetRows("25,Auto,Auto,Auto,Auto,Auto,Auto,25,Auto,Auto,25");
        SetRowSpacing(UIDefaults::HalfRowSpacing);

        //******************************************************************************
        // #region InitializeComponent
        //******************************************************************************

        size_t row = 1;

        //******************************************************************************
        // #region infoText
        //******************************************************************************

        infoHeaderText.SetName(nameof(LoginPage) + nameof(infoHeaderText));
        infoHeaderText.SetText(AccountListEmpty);
        infoHeaderText.SetFontSize(24);
        infoHeaderText.SetHorizontalAlignment(HorizontalAlignment::Center);
        infoHeaderText.SetGrid(1, row++, 3);
        AddChild(&infoHeaderText);

        infoDetailsText.SetName(nameof(LoginPage) + nameof(infoDetailsText));
        infoDetailsText.SetText(AccountListEmptyDetails);
        infoDetailsText.SetHorizontalAlignment(HorizontalAlignment::Center);
        infoDetailsText.SetVerticalAlignment(VerticalAlignment::Top);
        infoDetailsText.SetGrid(1, row++, 3);
        AddChild(&infoDetailsText);

        //******************************************************************************
        // #region Account
        //******************************************************************************

        accountValue.SetName(nameof(LoginPage) + nameof(accountValue));
        accountValue.SetIsEditable(true);
        accountValue.SetHintText(AccountHint);
        accountValue.SetTextAlignment(HorizontalAlignment::Center);
        accountValue.SetGrid(2, row, 1);
        accountValue.KeyDown.Add(&LoginPageBase::AccountValue_KeyDown, this);
        accountValue.TextChanged.Add(&LoginPageBase::AccountValue_TextChanged, this);
        accountValue.SelectionChanged.Add(&LoginPageBase::AccountValue_SelectionChanged, this);
        AddChild(&accountValue);

        rememberAccount.SetText(RememberAccount);
        rememberAccount.SetGrid(3, row, 2);
        AddChild(&rememberAccount);
        row++;

        //******************************************************************************
        // #region Password
        //******************************************************************************

        passwordValue.SetName(nameof(LoginPage) + nameof(passwordValue));
        passwordValue.SetIsPassword(true);
        passwordValue.SetTextAlignment(HorizontalAlignment::Center);
        passwordValue.SetHintText(Password);
        passwordValue.SetGrid(2, row, 1);
        passwordValue.KeyDown.Add(&LoginPageBase::PasswordValue_KeyDown, this);
        passwordValue.TextChanged.Add(&LoginPageBase::PasswordValue_TextChanged, this);
        AddChild(&passwordValue);

        rememberPassword.SetText(nameof(RememberPassword));
        rememberPassword.SetGrid(3, row, 2);
        AddChild(&rememberPassword);
        row++;

        //******************************************************************************
        // #region Switches
        //******************************************************************************

        autoLogin.SetText(AutoLogin);
        autoLogin.SetVerticalAlignment(VerticalAlignment::Top);
        autoLogin.SetGrid(3, row, 2);
        AddChild(&autoLogin);

        //******************************************************************************
        // #region Buttons
        //******************************************************************************

        loginButton.SetName(nameof(LoginPage) + nameof(loginButton));
        loginButton.SetEnabled(false);
        loginButton.SetText(Download);
        loginButton.SetGrid(2, row++, 1);
        loginButton.Click.Add(&LoginPageBase::LoginButton_Click, this);
        AddChild(&loginButton);

        abortButton.SetName(nameof(LoginPage) + nameof(abortButton));
        abortButton.SetText(Abort);
        abortButton.SetGrid(2, row++, 1);
        abortButton.Click.Add(&LoginPageBase::AbortButton_Click, this);
        AddChild(&abortButton);

        //******************************************************************************
        // #region ProgressBar
        //******************************************************************************

        // got one empty row here
        row++;

        progressValue.SetText("Waiting...");
        progressValue.SetGrid(2, row, 1);
        progressValue.SetName(nameof(LoginPage) + nameof(progressValue));
        progressValue.SetHorizontalAlignment(HorizontalAlignment::Center);
        AddChild(&progressValue);

        row++;

        progressBar.SetName(nameof(LoginPage) + nameof(ProgressBar));
        progressBar.SetGrid(2, row++, 1);
        AddChild(&progressBar);

        //******************************************************************************

        //******************************************************************************

        if (!App::Settings().GetLastAccount().empty())
        {
            AccountManager::Load(App::Settings().GetLastAccount(), isEmailAccount);
        }

        InitializeAccountData();

        if (App::ForegroundProgress == 100)
            SetProgressBar(100);
    }
    LoginPageBase::~LoginPageBase() {}

    void LoginPageBase::SetProgressBar(float value)
    {
        // Syncronizer::Invoke(() = >
        //{
        float rounded = (float)((int)std::round(value));
        progressBar.SetValue(rounded);
        progressValue.SetText("Loading " + std::to_string(rounded) + "%");

        CheckLogin();
        //});
    }

    bool LoginPageBase::CheckAccount(bool createNow)
    {
        passwordValue.SetIsError(false);

        std::string accountText = accountValue.GetText();

        if (isEmailAccount && !Protector::IsEmailValid(accountText))
        {
            SetInfoHeaderTextSource(InvalidEmailInfo);
            SetInfoDetailsTextSource(InvalidEmailDetails);

            if (!accountValue.GetIsFocused())
            {
                accountValue.SetIsError(true);
                accountValue.Focus();
            }
            return false;
        }
        else if (!isEmailAccount && accountText.empty())
        {
            SetInfoHeaderTextSource(AccountNameEmpty);
            SetInfoDetailsTextSource("");

            if (!accountValue.GetIsFocused())
            {
                accountValue.SetIsError(true);
                accountValue.Focus();
            }
            return false;
        }

        accountValue.SetIsError(false);

        if (AccountManager::AccountExists(accountText))
        {
            if (AccountManager::GetAccount() == nullptr)
            {
                AccountManager::Load(accountText, isEmailAccount);
            }
            else if (AccountManager::GetAccount()->GetName() == accountText)
            {
                AccountManager::Load(accountText, isEmailAccount);
            }

            // check again to be sure we do not change text until we have a valid account
            if (AccountManager::GetAccount())
            {
                SetInfoHeaderTextSource(EnterPasswordInfo);
                SetInfoDetailsTextSource("");

                SetLoginButtonTextSource(Start);
            }
        }
        else if (canCreateAccount)
        {
            if (createNow)
            {
                AccountManager::Create(accountText, passwordValue.GetPassword(), isEmailAccount);
            }
            else
            {
                SetInfoHeaderTextSource(AccountNameValid);
                SetInfoDetailsTextSource(AccountNameValidDetails);

                SetLoginButtonTextSource(Download);
            }
        }
        else
        {
            SetInfoHeaderTextSource(AccountNameValid);
            SetInfoDetailsTextSource(AccountNameValidDetails);
        }

        App::Settings().SetLastAccount(accountText);

        return true;
    }
    void LoginPageBase::CheckLogin()
    {
        if (isLoginSuccess && progressBar.GetValue() == 100)
        {
            EventArgs e;
            LoginSuccess(e);
        }
    }

    void LoginPageBase::PasswordValue_KeyDown(InputContent &sender, KeyEventArgs &e)
    {
        if (e.Key == CKey::Enter)
        {
            EventArgs e1;
            LoginButton_Click(loginButton, e1);
            e.Handled = true;
            Invalidate();
        }
        // else if (e.Key == Key.Tab)
        //{
        //     loginButton.Focus();
        //     e.Handled = true;
        // }
    }
    void LoginPageBase::PasswordValue_TextChanged(TextChangedEventArgs &e)
    {
        bool hasText = !passwordValue.GetText().empty();
        loginButton.SetEnabled(hasText);
        if (!hasText)
            passwordValue.SetIsError(true);
    }

    void LoginPageBase::AccountValue_SelectionChanged(const std::string& e)
    {
        if (CheckAccount(false))
        {
            passwordValue.SetIsError(true);
            passwordValue.Focus();
        }
    }
    void LoginPageBase::AccountValue_TextChanged(TextChangedEventArgs& e)
    {
        CheckAccount(false);
    }
    void LoginPageBase::AccountValue_KeyDown(InputContent& sender, KeyEventArgs& e)
    {
        if (e.Key == CKey::Enter || e.Key == CKey::Tab)
        {
            passwordValue.Focus();
            e.Handled = true;
        }
    }

    void LoginPageBase::AbortButton_Click(InputContent &sender, EventArgs &e)
    {
        isLoginSuccess = false;
        progressBar.SetValue(0);

        if (!accountValue.GetText().empty())
        {
            App::Settings().SetLastAccount(accountValue.GetText());
            App::Settings().Save();
        }

        App::Close();
    }
    void LoginPageBase::LoginButton_Click(InputContent &sender, EventArgs &e)
    {
#ifdef DEBUG
        if (InputHandler::IsShift())
        {
            // if (MainWindow == nullptr)
            //{
            //     MainWindow = new T();
            // }
            isLoginSuccess = true;
            CheckLogin();
            return;
        }
#endif
        // First check if input is valid
        if (!CheckAccount(true))
        {
            return;
        }

        if (forcePassword)
        {
            if (passwordValue.GetPassword().empty())
            {
                SetInfoHeaderTextSource(PasswordEmptyInfo);
                SetInfoDetailsTextSource("");

                passwordValue.Focus();
                return;
            }
            else if (AccountManager::GetAccount())
            {
                if (!AccountManager::GetAccount()->CheckPassword(passwordValue.GetPassword()))
                {
                    SetInfoHeaderTextSource(WrongPasswordInfo);
                    SetInfoDetailsTextSource("");

                    passwordValue.SetIsError(true);
                    passwordValue.Focus();
                    return;
                }
                passwordValue.SetIsError(false);
            }
            else
            {
                return;
            }
        }

        passwordValue.Erase();
        passwordValue.SetEnabled(false);

        loginButton.SetEnabled(false);

        if (OnAccountCheckPassed())
        {
            isLoginSuccess = true;
            CheckLogin();
        }
    }

    void LoginPageBase::InitializeAccountData()
    {
        passwordValue.Erase();

        // rememberAccountSwitch.IsActiveSetting = App.Settings[nameof(App::Settings().SaveAccount)];
        // rememberPasswordSwitch.IsActiveSetting = App.Settings[nameof(App::Settings().SavePassword)];
        // autoLoginSwitch.SetIsActiveSetting(App::Settings()[nameof(App::Settings().AutoLogin)]);

        // rememberAccountSwitch.TextSource = RememberAccount;
        SetLoginButtonTextSource(Download);

        passwordValue.SetEnabled(true);

        accountValue.SetItems(&AccountManager::Accounts);

        if (App::Settings().GetLastAccount().empty())
        {
            // if completely emty data
            if (AccountManager::Accounts.size() == 0)
            {
                SetInfoHeaderTextSource(AccountListEmpty);
                SetInfoDetailsTextSource(AccountListEmptyDetails);

                accountValue.Focus();
            }
            else
            {
                accountValue.SetSelectedValue(*AccountManager::Accounts.begin());
            }
        }
        else
        {
            if (!AccountManager::AccountExists(App::Settings().GetLastAccount()))
            {
                SetInfoHeaderTextSource(AccountNotFound);
                SetInfoDetailsTextSource("");

                char buffer[256] = {0};
                // std::string text = Languages::Active()[AccountNotFoundDetails]->Text;
                sprintf(buffer, AccountNotFoundDetails.c_str(), App::Settings().GetLastAccount());
                // text = String::Format(text, );
                infoDetailsText.SetText(buffer);

                accountValue.Focus();
            }
            else
            {
                CheckAccount(false);

                SetInfoHeaderTextSource(EnterPasswordInfo);
                SetInfoDetailsTextSource("");

                accountValue.SetSelectedValue(App::Settings().GetLastAccount());
                passwordValue.Focus();

                OnInitializeAccountData();
            }
        }

        // if (CanPreload && MainWindow == nullptr)
        //{
        //     MainWindow = new T();
        // }
        // CheckAccount(false);

        // OnInitializeAccountData();
    }
    void LoginPageBase::OnInitializeAccountData() {}
}
