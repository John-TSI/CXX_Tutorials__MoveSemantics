#include<iostream>
#include<string>


struct C
{
    int myInt = 0;
    char myChar = 'c';
    std::string myString = "string";

    // Ref-qualified methods
    void FuncRef()& { std::cout << "FuncRef() called.\n"; }
    void FuncRRef()&& { std::cout << "FuncRRef() called.\n"; }
    void FuncConstRef() const& { std::cout << "FuncConstRef() called.\n"; }
    void FuncConstRRef() const&& { std::cout << "FuncConstRRef() called.\n"; }
};

// --- overloaded foo() ---
void foo(const std::string& arg) // const lvalue ref (string)
{
    std::cout << "const lvalue ref foo() was called.\n";
}
void foo(std::string& arg) // lvalue ref (string)
{
    std::cout << "lvalue ref foo() was called.\n";
}
void foo(std::string&& arg) // rvalue ref (string)
{
    std::cout << "rvalue ref foo() was called.\n";
    std::string foo_str = arg;
}
void foo(const std::string&& arg) // const rvalue ref (string)
{
    std::cout << "const rvalue ref foo() was called.\n";
}

void foo(const float& arg) // const lvalue ref (float)
{
    std::cout << "const lvalue ref foo() was called.\n";
}
void foo(float& arg) // lvalue ref (float)
{
    std::cout << "lvalue ref foo() was called.\n";
}
void foo(float&& arg) // rvalue ref (float)
{
    std::cout << "rvalue ref foo() was called.\n";
}
void foo(const float&& arg) // const rvalue ref (float)
{
    std::cout << "const rvalue ref foo() was called.\n";
}


int main()
{
    system("cls");

    // --- basic moves ---
    {
    C obj;
    int newInt = std::move(obj.myInt);
    char newChar = std::move(obj.myChar);
    std::string newString = std::move(obj.myString);
    std::cout << "[] " << obj.myInt << "\n";
    std::cout << "[] " << obj.myChar << "\n";
    std::cout << "[] " << obj.myString << "\n\n";

    std::string long_str = "what a nice long string this is!";
    std::string str = "small";

    std::string long_str2 = std::move(long_str);
    std::string str2 = std::move(str);

    std::cout << "address of long_str: " << &long_str << ", address of long_str2: " << &long_str2 << "\n";
    //std::cout << "[...] " << long_str << "\n";
    std::cout << "address of str: " << &str << ", address of str2: " << &str2 << "\n";
    //std::cout << "[...] " << str << "\n";

    for(int i=0; i<3; i++)
    {
        std::string str = "strrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr" + std::to_string(i);
        std::string str2 = std::move(str);
        //std::cout << "[]" << str << "\n";
    }

    }
    std::cout << "\n###############################################\n\n";


    // --- overloading ---
    {
    const std::string str3 = "str3";
    std::string str4 = "str4";
    const float const_fl = 3.5;
    float fl = 2.7;

    foo(str3);
    foo(str4);
    foo(std::move(str3));
    foo(std::move(str4));
    foo("tmp_str");
    std::cout << "\n-------------------------\n";
    foo(const_fl);
    foo(fl);
    foo(std::move(const_fl));
    foo(std::move(fl));
    foo(5.1);

    }
    std::cout << "\n###############################################\n\n";

    
    // --- Ref-qualified functions ---
    C obj, obj2;

    obj.FuncRef(); // FuncRef only callable from an lvalue instance
    
    obj.FuncConstRef(); // FuncConstRef callable from either lvalue/rvalue instance
    C().FuncConstRef(); // FuncConstRef callable from either lvalue/rvalue instance

    C().FuncRRef();  // FuncRRef only callable from an rvalue instance
    C().FuncConstRRef();  // FuncConstRRef only callable from an rvalue instance

    std::move(obj2).FuncConstRef();
    std::move(obj2).FuncRRef();
    std::move(obj2).FuncConstRRef();

    std::move(C()).FuncRRef();


    C* pHeapObj = new C;
    pHeapObj->FuncRef();
    pHeapObj->FuncConstRef();
    delete pHeapObj;

    //C* pObj = &C();
    C* pObj = &obj;
    pObj->FuncRef();
    pObj->FuncConstRef();
    (*pObj).FuncRef();
    (*pObj).FuncConstRef();


    return 0;
}