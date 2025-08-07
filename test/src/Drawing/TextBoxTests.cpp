#include <gtest/gtest.h>
#include <Drawing/TextBox.h>
#include <Drawing/DebugUtils.h>

class TextBoxTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        // Enable TextBox debugging for all tests
        // xit::Drawing::Debug::LayoutDiagnostics::EnableTextBoxDebuggingOnly();
        textBox = std::make_unique<xit::Drawing::TextBox>();
    }

    void TearDown() override
    {
        // Clean up after tests
        // xit::Drawing::Debug::LayoutDiagnostics::DisableAllDebugging();
        textBox.reset();
    }

    std::unique_ptr<xit::Drawing::TextBox> textBox;
};

// Test basic TextBox functionality
TEST_F(TextBoxTest, BasicTextOperations)
{
    // Test initial state
    EXPECT_FALSE(textBox->GetIsPassword());
    EXPECT_TRUE(textBox->GetText().empty());
    EXPECT_EQ(textBox->GetText().length(), 0);

    // Test setting text
    textBox->SetText("Hello World");
    EXPECT_EQ(textBox->GetText(), "Hello World");
    EXPECT_EQ(textBox->GetText().length(), 11);
}

// Test password mode functionality
TEST_F(TextBoxTest, PasswordModeBasic)
{
    // Set some initial text
    textBox->SetText("secret123");
    EXPECT_EQ(textBox->GetText(), "secret123");

    // Enable password mode
    textBox->SetIsPassword(true);
    EXPECT_TRUE(textBox->GetIsPassword());

    // Text should now show asterisks
    EXPECT_EQ(textBox->GetText(), "*********");
    EXPECT_EQ(textBox->GetText().length(), 9);

    // But internal password should remain the same
    EXPECT_EQ(textBox->GetPassword(), "secret123");
}

// Test password mode toggle
TEST_F(TextBoxTest, PasswordModeToggle)
{
    // Set text and enable password mode
    textBox->SetText("mypassword");
    textBox->SetIsPassword(true);

    // Should show asterisks
    EXPECT_EQ(textBox->GetText(), "**********");
    EXPECT_EQ(textBox->GetPassword(), "mypassword");

    // Disable password mode
    textBox->SetIsPassword(false);
    EXPECT_FALSE(textBox->GetIsPassword());

    // Should show actual text again
    EXPECT_EQ(textBox->GetText(), "mypassword");
    EXPECT_EQ(textBox->GetPassword(), "mypassword");

    // Re-enable password mode
    textBox->SetIsPassword(true);
    EXPECT_EQ(textBox->GetText(), "**********");
}

// Test setting text while in password mode
TEST_F(TextBoxTest, SetTextInPasswordMode)
{
    // Enable password mode first
    textBox->SetIsPassword(true);
    EXPECT_TRUE(textBox->GetIsPassword());

    // Set text while in password mode
    textBox->SetText("newpassword");

    // Should show asterisks
    EXPECT_EQ(textBox->GetText(), "***********");
    EXPECT_EQ(textBox->GetText().length(), 11);

    // Internal password should be correct
    EXPECT_EQ(textBox->GetPassword(), "newpassword");
}

// Test empty text scenarios
TEST_F(TextBoxTest, EmptyTextScenarios)
{
    // Test empty text in normal mode
    textBox->SetText("");
    EXPECT_TRUE(textBox->GetText().empty());
    EXPECT_EQ(textBox->GetText().length(), 0);

    // Test empty text in password mode
    textBox->SetIsPassword(true);
    EXPECT_TRUE(textBox->GetText().empty());
    EXPECT_EQ(textBox->GetText().length(), 0);

    // Add some text
    textBox->SetText("test");
    EXPECT_EQ(textBox->GetText(), "****");

    // Clear text while in password mode
    textBox->SetText("");
    EXPECT_TRUE(textBox->GetText().empty());
    EXPECT_EQ(textBox->GetText().length(), 0);

    // Debug call removed to avoid interference with subsequent tests
}

// Test character insertion in password mode
TEST_F(TextBoxTest, CharacterInsertionPasswordMode)
{
    // Start fresh - clear any existing text
    textBox->SetText("");
    textBox->SetIsPassword(true);

    // Insert characters one by one
    textBox->Insert(0, 'a');
    EXPECT_EQ(textBox->GetText(), "*");
    EXPECT_EQ(textBox->GetPassword(), "a");

    textBox->Insert(1, 'b');
    EXPECT_EQ(textBox->GetText(), "**");
    EXPECT_EQ(textBox->GetPassword(), "ab");

    textBox->Insert(2, 'c');
    EXPECT_EQ(textBox->GetText(), "***");
    EXPECT_EQ(textBox->GetPassword(), "abc");
}

// Test string insertion in password mode
TEST_F(TextBoxTest, StringInsertionPasswordMode)
{
    // Start fresh - clear any existing text
    textBox->SetText("");
    textBox->SetIsPassword(true);

    // Insert a string
    textBox->Insert(0, "hello");
    EXPECT_EQ(textBox->GetText(), "*****");
    EXPECT_EQ(textBox->GetPassword(), "hello");

    // Insert another string in the middle
    textBox->Insert(2, "XYZ");
    EXPECT_EQ(textBox->GetText(), "********");
    EXPECT_EQ(textBox->GetPassword(), "heXYZllo");
}

// Test character removal in password mode
TEST_F(TextBoxTest, CharacterRemovalPasswordMode)
{
    textBox->SetText("password123");
    textBox->SetIsPassword(true);

    EXPECT_EQ(textBox->GetText(), "***********");
    EXPECT_EQ(textBox->GetPassword(), "password123");

    // Remove some characters
    textBox->Remove(8, 3); // Remove "123"
    EXPECT_EQ(textBox->GetText(), "********");
    EXPECT_EQ(textBox->GetPassword(), "password");

    // Remove from beginning
    textBox->Remove(0, 4); // Remove "pass"
    EXPECT_EQ(textBox->GetText(), "****");
    EXPECT_EQ(textBox->GetPassword(), "word");
}

// Test invalidation after password mode changes
TEST_F(TextBoxTest, InvalidationAfterPasswordModeChanges)
{
    textBox->SetText("testtext");

    // Should be invalidated after setting text
    // Note: We can't directly test GetInvalidated() but we can test the behavior

    // Enable password mode - should trigger invalidation
    textBox->SetIsPassword(true);
    EXPECT_EQ(textBox->GetText(), "********");

    // Disable password mode - should trigger invalidation
    textBox->SetIsPassword(false);
    EXPECT_EQ(textBox->GetText(), "testtext");
}

// Test edge cases
TEST_F(TextBoxTest, EdgeCases)
{
    // Test very long password
    std::string longPassword(1000, 'x');
    textBox->SetIsPassword(true);
    textBox->SetText(longPassword);

    std::string expectedAsterisks(1000, '*');
    EXPECT_EQ(textBox->GetText(), expectedAsterisks);
    EXPECT_EQ(textBox->GetPassword(), longPassword);

    // Test single character
    textBox->SetText("a");
    EXPECT_EQ(textBox->GetText(), "*");
    EXPECT_EQ(textBox->GetPassword(), "a");

    // Test special characters
    textBox->SetText("!@#$%^&*()");
    EXPECT_EQ(textBox->GetText(), "**********");
    EXPECT_EQ(textBox->GetPassword(), "!@#$%^&*()");
}

// Test password character constant
TEST_F(TextBoxTest, PasswordCharacterConstant)
{
    // Test that the password character is correctly defined
    EXPECT_EQ(xit::Drawing::TextBox::PasswordCharacter, '*');

    // Test that it's used correctly
    textBox->SetIsPassword(true);
    textBox->SetText("test");

    // Should be 4 asterisks
    std::string expected(4, xit::Drawing::TextBox::PasswordCharacter);
    EXPECT_EQ(textBox->GetText(), expected);
}

// Comprehensive test with debug diagnostics
TEST_F(TextBoxTest, ComprehensivePasswordTest)
{
    // std::cout << "\n=== COMPREHENSIVE PASSWORD TEXTBOX TEST ===" << std::endl;

    // Test the complete workflow that was originally failing

    // 1. Initial state
    // std::cout << "1. Testing initial state..." << std::endl;
    EXPECT_FALSE(textBox->GetIsPassword());
    EXPECT_TRUE(textBox->GetText().empty());

    // 2. Set text
    // std::cout << "2. Setting text to 'test123'..." << std::endl;
    textBox->SetText("test123");
    EXPECT_EQ(textBox->GetText(), "test123");

    // 3. Enable password mode
    // std::cout << "3. Enabling password mode..." << std::endl;
    textBox->SetIsPassword(true);
    EXPECT_TRUE(textBox->GetIsPassword());
    EXPECT_EQ(textBox->GetText(), "*******");
    EXPECT_EQ(textBox->GetPassword(), "test123");

    // 4. Disable password mode
    // std::cout << "4. Disabling password mode..." << std::endl;
    textBox->SetIsPassword(false);
    EXPECT_FALSE(textBox->GetIsPassword());
    EXPECT_EQ(textBox->GetText(), "test123");
    EXPECT_EQ(textBox->GetPassword(), "test123");

    // 5. Test multiple toggles
    // std::cout << "5. Testing multiple toggles..." << std::endl;
    for (int i = 0; i < 3; i++)
    {
        textBox->SetIsPassword(true);
        EXPECT_EQ(textBox->GetText(), "*******");

        textBox->SetIsPassword(false);
        EXPECT_EQ(textBox->GetText(), "test123");
    }

    // std::cout << "=== COMPREHENSIVE TEST COMPLETE ===" << std::endl;
}
