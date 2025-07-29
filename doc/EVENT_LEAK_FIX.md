# Event Memory Leak Fix

## Problem
Large memory leak in Event<> template caused by lambda function storage.

## Solution
The issue is likely in how Event lambdas are stored. Here's a fix pattern:

```cpp
// Current problematic pattern (from stack trace):
Event<xit::Drawing::Visual&, xit::EventArgs&>::Add<void, xit::Drawing::ContentContainer, xit::Drawing::ContentContainer*>

// This creates persistent lambda captures that aren't properly cleaned up

// FIX 1: Use weak_ptr for object references in lambdas
class ContentContainer {
private:
    std::weak_ptr<ContentContainer> weak_self;
    
public:
    void setupEvents() {
        // Instead of capturing 'this' directly:
        someEvent.Add([this](Visual& v, EventArgs& e) { /* BAD - strong reference */ });
        
        // Use weak_ptr:
        auto weak = weak_self;
        someEvent.Add([weak](Visual& v, EventArgs& e) {
            if (auto self = weak.lock()) {
                self->handleEvent(v, e);
            }
        });
    }
};

// FIX 2: Ensure event handlers are properly removed
class Visual {
public:
    ~Visual() {
        // Remove all event handlers before destruction
        removeAllEventHandlers();
    }
    
private:
    void removeAllEventHandlers() {
        // Clear all event subscriptions
        onSizeChanged.Clear();
        onVisibilityChanged.Clear();
        // etc...
    }
};

// FIX 3: Use RAII for event subscriptions
class EventSubscription {
private:
    std::function<void()> unsubscribe;
    
public:
    EventSubscription(std::function<void()> unsub) : unsubscribe(std::move(unsub)) {}
    ~EventSubscription() { if (unsubscribe) unsubscribe(); }
    
    // Non-copyable, movable
    EventSubscription(const EventSubscription&) = delete;
    EventSubscription& operator=(const EventSubscription&) = delete;
    EventSubscription(EventSubscription&&) = default;
    EventSubscription& operator=(EventSubscription&&) = default;
};
```
