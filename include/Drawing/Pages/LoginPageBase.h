#pragma once

#include <Drawing/Pages/Page.h>
#include <Drawing/ProgressBar.h>
#include <Drawing/Label.h>
#include <Drawing/ComboBox.h>
#include <Drawing/Switch.h>
#include <Drawing/TextBox.h>
#include <Drawing/Buttons/Button.h>
// #include <Drawing/Buttons/TextButton.h>

namespace xit::Drawing::Pages
{
    class LoginPageBase : public Page
    {
    private:
#define nameof(x) std::string(#x)

        Label infoHeaderText;
        Label infoDetailsText;

        ComboBox accountValue;
        TextBox passwordValue;

        Button loginButton;
        Button abortButton;

        ProgressBar progressBar;
        Label progressValue;

        Switch rememberAccount;
        Switch rememberPassword;
        Switch autoLogin;

        bool isLoginSuccess;

        void SetProgressBar(float value);

        bool CheckAccount(bool createNow);
        void CheckLogin();

        void PasswordValue_KeyDown(InputContent &sender, KeyEventArgs &e);
        void PasswordValue_TextChanged(TextChangedEventArgs &e);

        void AccountValue_SelectionChanged(const std::string &e);
        void AccountValue_TextChanged(TextChangedEventArgs &e);
        void AccountValue_KeyDown(InputContent &sender, KeyEventArgs &e);

        void AbortButton_Click(InputContent &sender, EventArgs &e);

        void LoginButton_Click(InputContent &sender, EventArgs &e);
        void InitializeAccountData();

    protected:
        bool canCreateAccount;
        bool canPreload;
        bool forcePassword;
        bool isEmailAccount;

        virtual void OnInitializeAccountData();
        virtual bool OnAccountCheckPassed() = 0;

        static const std::string Start;
        static const std::string Download;
        static const std::string Abort;

        static const std::string RememberAccount;
        static const std::string RememberPassword;
        static const std::string AutoLogin;

        static const std::string AccountHint;
        static const std::string Password;

        static const std::string AccountNotFound;
        static const std::string AccountNotFoundDetails;

        static const std::string AccountListEmpty;
        static const std::string AccountListEmptyDetails;

        static const std::string AccountNameEmpty;
        static const std::string AccountNameValid;
        static const std::string AccountNameValidDetails;

        static const std::string AutoLoginInfo;
        static const std::string EnterPasswordInfo;

        static const std::string InvalidEmailInfo;
        static const std::string InvalidEmailDetails;

        static const std::string PasswordEmptyInfo;
        static const std::string WrongPasswordInfo;

        static void InitializeTextSources();

    public:
        bool GetCanCreateAccount() const { return canCreateAccount; }
        void SetCanCreateAccount(bool value) { canCreateAccount = value; }

        bool GetCanPreload() const { return canPreload; }
        void SetCanPreload(bool value) { canPreload = value; }

        bool GetForcePassword() const { return forcePassword; }
        void SetForcePassword(bool value) { forcePassword = value; }

        bool GetIsEmailAccount() const { return isEmailAccount; }
        void SetIsEmailAccount(bool value) { isEmailAccount = value; }

        void SetInfoHeaderTextSource(const std::string &value);
        void SetInfoDetailsTextSource(const std::string &value);
        void SetLoginButtonTextSource(const std::string &value);
        void SetAbortButtonTextSource(const std::string &value);

        bool GetIsAutoLoginVisible();
        void SetIsAutoLoginVisible(bool value);

        bool GetIsLoginButtonEnabled();
        void SetIsLoginButtonEnabled(bool value);

        Event<EventArgs &> LoginSuccess;

        LoginPageBase();
        virtual ~LoginPageBase();
    };
}
