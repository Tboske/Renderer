#pragma once

template <typename T>
class Singleton 
{
public:
    virtual ~Singleton() = default;
    
protected:
    static T& Instance()
    {
        static T instance{};
        return instance;
    }
    Singleton() = default;
    Singleton(const Singleton&) = delete;
    Singleton(Singleton&&) noexcept  = delete;
    Singleton& operator=(const Singleton&) = delete;
    Singleton& operator=(Singleton&&) noexcept  = delete;    
};