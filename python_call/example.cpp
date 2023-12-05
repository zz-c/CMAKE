#include <Python.h>
#include <iostream>

void test0() {
    Py_Initialize();    // ��ʼ��
    PyRun_SimpleString("print('hello python')");
    Py_Finalize();      // �ͷ���Դ
}
void test1() {
    // 1����ʼ��python�ӿ�
    Py_Initialize();
    if (!Py_IsInitialized())
    {
        std::cout << "python init failed" << std::endl;
        return;
    }
    // 2����ʼ��pythonϵͳ�ļ�·������֤���Է��ʵ� .py�ļ�
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.path.append('G:/project/c/CMAKE/python_call/script')");

    // 3������python�ļ���������д��׺
    PyObject* module = PyImport_ImportModule("test1");
    if (module == nullptr)
    {
        std::cout << "module not found: test1" << std::endl;
        return;
    }
    // 4����ȡ��������
    PyObject* func = PyObject_GetAttrString(module, "say");
    if (!func || !PyCallable_Check(func))
    {
        std::cout << "function not found: say" << std::endl;
        return;
    }
    // 5�����ú���
    PyObject_CallObject(func, nullptr);
    // 6������python�ӿڳ�ʼ��
    Py_Finalize();
}
void test2() {
    Py_Initialize();
    if (!Py_IsInitialized())
    {
        std::cout << "python init failed" << std::endl;
        return;
    }

    // 2����ʼ��pythonϵͳ�ļ�·������֤���Է��ʵ� .py�ļ�
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.path.append('G:/project/c/CMAKE/python_call/script')");

    // 3������python�ļ���������д��׺
    PyObject* module = PyImport_ImportModule("test1");
    if (module == nullptr)
    {
        std::cout << "module not found: test1" << std::endl;
        return;
    }
    // 4�����ú���
    PyObject* func = PyObject_GetAttrString(module, "add");
    if (!func || !PyCallable_Check(func))
    {
        std::cout << "function not found: add" << std::endl;
        return;
    }

    // 5���� python ���ݲ���
    // �������õĲ������ݾ�����Ԫ�����ʽ�����, 2��ʾ��������
    // ���������ֻ��һ������ʱ��д1�Ϳ�����
    PyObject* args = PyTuple_New(2);

    // 0����һ������������ int ���͵�ֵ 1
    PyTuple_SetItem(args, 0, Py_BuildValue("i", 1));
    // 1���ڶ������������� int ���͵�ֵ 2
    PyTuple_SetItem(args, 1, Py_BuildValue("i", 2));

    // 6��ʹ��C++��python�ӿڵ��øú���
    PyObject* ret = PyObject_CallObject(func, args);

    // 7������python����õķ���ֵ
    int result;
    // i��ʾת����int�ͱ�����
    // ���������Ҫע����ǣ�PyArg_Parse�����һ��������������ϡ�&������
    PyArg_Parse(ret, "i", &result);
    std::cout << "return is " << result << std::endl;

    // 8������python�ӿڳ�ʼ��
    Py_Finalize();
}
void test3() {
    // 1����ʼ��python�ӿ�
    Py_Initialize();
    if (!Py_IsInitialized())
    {
        std::cout << "python init failed" << std::endl;
        return;
    }

    // 2����ʼ��pythonϵͳ�ļ�·������֤���Է��ʵ� .py�ļ�
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.path.append('G:/project/c/CMAKE/python_call/script')");

    // 3������python�ļ���������д��׺
    PyObject* module = PyImport_ImportModule("test1");
    if (module == nullptr)
    {
        std::cout << "module not found: test1" << std::endl;
        return;
    }
    // 4����ȡ��
    PyObject* cls = PyObject_GetAttrString(module, "Person");
    if (!cls)
    {
        std::cout << "class not found: Person" << std::endl;
        return;
    }

    // 5�����๹�캯�����ݲ���
    // �������õĲ������ݾ�����Ԫ�����ʽ�����, 2��ʾ��������
    // ���������ֻ��һ������ʱ��д1�Ϳ�����
    PyObject* args = PyTuple_New(2);

    // 0����һ������������ int ���͵�ֵ 1
    PyTuple_SetItem(args, 0, Py_BuildValue("s", "jack"));
    // 1���ڶ������������� int ���͵�ֵ 2
    PyTuple_SetItem(args, 1, Py_BuildValue("i", 18));

    // 6����������ʵ��������
    PyObject* obj = PyEval_CallObject(cls, args);

    // 7�����ݶ���õ���Ա����
    PyObject* func = PyObject_GetAttrString(obj, "foo");
    if (!func || !PyCallable_Check(func))
    {
        std::cout << "function not found: foo" << std::endl;
        return;
    }

    // 8��ʹ��C++��python�ӿڵ��øú���
    PyObject_CallObject(func, nullptr);

    // 9������python�ӿڳ�ʼ��
    Py_Finalize();
}
int main()
{
    test3();
    return 0;
}