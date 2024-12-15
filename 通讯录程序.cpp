#include <iostream>
#include <string>
#include <iomanip>
#include <Windows.h>
#include <fstream>

using namespace std;

struct Contact
{
    string studentID;
    string name;
    int sex;
    string profession;
    string Class;
    string dormitory;
    string native;
    string phone;
    string QQ;
    string Wechat;
};

void showmenu()
{
    cout << "*******************************" << endl;
    cout << "**** 1、添加联系人         ****" << endl;
    cout << "**** 2、查询联系人         ****" << endl;
    cout << "**** 3、删除联系人         ****" << endl;
    cout << "**** 4、修改联系人信息     ****" << endl;
    cout << "**** 5、输出联系人列表     ****" << endl;
    cout << "**** 6、按学号排序         ****" << endl;
    cout << "**** 7、退出程序并保存数据 ****" << endl;
    cout << "**** 8、程序初始化         ****" << endl;
    cout << "**** 0. 退出程序           ****" << endl;
    cout << "*******************************" << endl;
    cout << "请选择您的操作： ";
}
void add(Contact *&contacts, int &size, int &capacity)
{
    if (size == capacity)
    {
        // 如果当前数组已满，需要重新分配更大的内存
        Contact *newContacts = new Contact[capacity * 2];
        // 迁移
        for (int i = 0; i < size; ++i)
        {
            newContacts[i] = contacts[i];
        }
        delete[] contacts;
        contacts = newContacts;
        capacity *= 2;
    }
    Contact newContact;
    cout << "学号：";
    cin >> newContact.studentID;
    cin.ignore();
    cout << "姓名：";
    cin >> newContact.name;
    cout << "性别（1-男  2-女)：";
    cin >> newContact.sex;
    cin.ignore();
    cout << "专业：";
    getline(cin, newContact.profession);
    cout << "班级：";
    getline(cin, newContact.Class);
    cout << "宿舍号：";
    getline(cin, newContact.dormitory);
    cout << "籍贯：";
    getline(cin, newContact.native);
    cout << "手机号：";
    getline(cin, newContact.phone);
    cout << "QQ：";
    getline(cin, newContact.QQ);
    cout << "微信号：";
    getline(cin, newContact.Wechat);
    contacts[size] = newContact;
    ++size;

    cout << "添加成功" << endl;
    system("pause");
    system("cls");
}

void displayContact(const Contact &contact)
{
    cout << "\n==================联系人信息==================" << endl;
    cout << "学号：" << contact.studentID << endl;
    cout << "姓名：" << contact.name << endl;
    cout << "性别：" << (contact.sex == 1 ? "男" : "女") << endl;
    cout << "专业：" << contact.profession << endl;
    cout << "班级：" << contact.Class << endl;
    cout << "宿舍号：" << contact.dormitory << endl;
    cout << "籍贯：" << contact.native << endl;
    cout << "手机号：" << contact.phone << endl;
    cout << "QQ：" << contact.QQ << endl;
    cout << "微信号：" << contact.Wechat << endl;
    cout << "=============================================" << endl;
}

void search(const Contact *contacts, int size)
{
    system("cls");
    if (size == 0)
    {
        cout << "通讯录为空！" << endl;
        system("pause");
        system("cls");
        return;
    }

    while (true)
    {
        cout << "******请选择查找方式******" << endl;
        cout << "*****1. 按学号查找   *****" << endl;
        cout << "*****2. 按姓名查找   *****" << endl;
        cout << "*****3. 返回主菜单   *****" << endl;
        cout << "**************************" << endl;
        cout << "请输入选择：";

        int choice;
        cin >> choice;

        if (choice == 3)
        {
            system("cls");
            break;
        }

        string searchTerm;
        bool found = false;

        switch (choice)
        {
        case 1:
        {
            cout << "请输入要查找的学号：";
            cin >> searchTerm;

            for (int i = 0; i < size; i++)
            {
                if (contacts[i].studentID == searchTerm)
                {
                    displayContact(contacts[i]);
                    found = true;
                }
            }
            break;
        }
        case 2:
        {
            cout << "请输入要查找的姓名：";
            cin >> searchTerm;

            for (int i = 0; i < size; i++)
            {
                if (contacts[i].name == searchTerm)
                {
                    displayContact(contacts[i]);
                    found = true;
                }
            }
            break;
        }
        default:
            cout << "无效的选择！" << endl;
            continue;
        }

        if (!found)
        {
            cout << "未找到匹配的联系人！" << endl;
        }

        system("pause");
        system("cls");
    }
}

void deleteContact(Contact *&contacts, int &size)
{
    system("cls");
    if (size == 0)
    {
        cout << "通讯录为空！" << endl;
        system("pause");
        system("cls");
        return;
    }

    while (true)
    {
        cout << "******请选择删除方式******" << endl;
        cout << "*****1. 按学号删除   *****" << endl;
        cout << "*****2. 按姓名删除   *****" << endl;
        cout << "*****3. 返回主菜单   *****" << endl;
        cout << "**************************" << endl;
        cout << "请输入选择：";

        int choice;
        cin >> choice;

        if (choice == 3)
        {
            system("cls");
            break;
        }

        string searchTerm;
        bool found = false;

        switch (choice)
        {
        case 1:
        {
            cout << "请输入要删除的学号：";
            cin >> searchTerm;

            for (int i = 0; i < size; i++)
            {
                if (contacts[i].studentID == searchTerm)
                {
                    // 显示要删除的联系人信息
                    cout << "\n将要删除以下联系人：" << endl;
                    cout << "姓名：" << contacts[i].name << endl;
                    cout << "学号：" << contacts[i].studentID << endl;

                    cout << "\n确认删除吗？(Y/N): ";
                    char confirm;
                    cin >> confirm;

                    if (confirm == 'Y' || confirm == 'y')
                    {
                        // 将后面的元素前移
                        for (int j = i; j < size - 1; j++)
                        {
                            contacts[j] = contacts[j + 1];
                        }
                        size--;
                        cout << "删除成功！" << endl;
                        found = true;
                    }
                    else
                    {
                        cout << "已取消删除。" << endl;
                        found = true;
                    }
                    break; // 找到并处理后退出循环
                }
            }
            break;
        }
        case 2:
        {
            cout << "请输入要删除的姓名：";
            cin >> searchTerm;

            for (int i = 0; i < size; i++)
            {
                if (contacts[i].name == searchTerm)
                {
                    // 显示要删除的联系人信息
                    cout << "\n将要删除以下联系人：" << endl;
                    cout << "姓名：" << contacts[i].name << endl;
                    cout << "学号：" << contacts[i].studentID << endl;

                    cout << "\n确认删除吗？(Y/N): ";
                    char confirm;
                    cin >> confirm;

                    if (confirm == 'Y' || confirm == 'y')
                    {
                        // 将后面的元素前移
                        for (int j = i; j < size - 1; j++)
                        {
                            contacts[j] = contacts[j + 1];
                        }
                        size--;
                        cout << "删除成功！" << endl;
                        found = true;
                    }
                    else
                    {
                        cout << "已取消删除。" << endl;
                        found = true;
                    }
                    break; // 找到并处理后退出循环
                }
            }
            break;
        }
        default:
            cout << "无效的选择！" << endl;
            continue;
        }

        if (!found)
        {
            cout << "未找到匹配的联系人！" << endl;
        }

        system("pause");
        system("cls");
    }
}

void showModifyMenu()
{
    cout << "=====请选择要修改的信息=====" << endl;
    cout << "1. 学号" << endl;
    cout << "2. 姓名" << endl;
    cout << "3. 性别" << endl;
    cout << "4. 专业" << endl;
    cout << "5. 班级" << endl;
    cout << "6. 宿舍号" << endl;
    cout << "7. 籍贯" << endl;
    cout << "8. 手机号" << endl;
    cout << "9. QQ" << endl;
    cout << "10. 微信号" << endl;
    cout << "0. 返回" << endl;
    cout << "==========================" << endl;
    cout << "请输入选择：";
}

void modifyContact(Contact *contacts, int size)
{
    system("cls");
    if (size == 0)
    {
        cout << "通讯录为空！" << endl;
        system("pause");
        system("cls");
        return;
    }

    while (true)
    {
        cout << "******请选择查找方式******" << endl;
        cout << "*****1. 按学号查找   *****" << endl;
        cout << "*****2. 按姓名查找   *****" << endl;
        cout << "*****3. 返回主菜单   *****" << endl;
        cout << "**************************" << endl;
        cout << "请输入选择：";

        int choice;
        cin >> choice;

        if (choice == 3)
        {
            system("cls");
            break;
        }

        string searchTerm;
        bool found = false;

        switch (choice)
        {
        case 1:
        {
            cout << "请输入要修改的联系人学号：";
            cin >> searchTerm;

            for (int i = 0; i < size; i++)
            {
                if (contacts[i].studentID == searchTerm)
                {
                    found = true;
                    while (true)
                    {
                        system("cls");
                        cout << "\n当前联系人信息：" << endl;
                        cout << "学号：" << contacts[i].studentID << endl;
                        cout << "姓名：" << contacts[i].name << endl;
                        cout << "性别：" << (contacts[i].sex == 1 ? "男" : "女") << endl;
                        cout << "专业：" << contacts[i].profession << endl;
                        cout << "班级：" << contacts[i].Class << endl;
                        cout << "宿舍号：" << contacts[i].dormitory << endl;
                        cout << "籍贯：" << contacts[i].native << endl;
                        cout << "手机号：" << contacts[i].phone << endl;
                        cout << "QQ：" << contacts[i].QQ << endl;
                        cout << "微信号：" << contacts[i].Wechat << endl;

                        showModifyMenu();
                        int modifyChoice;
                        cin >> modifyChoice;

                        if (modifyChoice == 0)
                        {
                            break;
                        }

                        switch (modifyChoice)
                        {
                        case 1:
                        {
                            string newID;
                            cout << "请输入新的学号：";
                            cin >> newID;
                            // 检查新学号是否已存在
                            bool idExists = false;
                            for (int j = 0; j < size; j++)
                            {
                                if (j != i && contacts[j].studentID == newID)
                                {
                                    idExists = true;
                                    break;
                                }
                            }
                            if (idExists)
                            {
                                cout << "该学号已存在，无法修改！" << endl;
                            }
                            else
                            {
                                contacts[i].studentID = newID;
                                cout << "修改成功！" << endl;
                            }
                            break;
                        }
                        case 2:
                            cout << "请输入新的姓名：";
                            cin >> contacts[i].name;
                            break;
                        case 3:
                            cout << "请输入新的性别（1-男 2-女）：";
                            cin >> contacts[i].sex;
                            while (contacts[i].sex != 1 && contacts[i].sex != 2)
                            {
                                cout << "输入错误，请重新输入（1-男 2-女）：";
                                cin >> contacts[i].sex;
                            }
                            break;
                        case 4:
                            cout << "请输入新的专业：";
                            cin >> contacts[i].profession;
                            break;
                        case 5:
                            cout << "请输入新的班级：";
                            cin >> contacts[i].Class;
                            break;
                        case 6:
                            cout << "请输入新的宿舍号：";
                            cin >> contacts[i].dormitory;
                            break;
                        case 7:
                            cout << "请输入新的籍贯：";
                            cin >> contacts[i].native;
                            break;
                        case 8:
                            cout << "请输入新的手机号：";
                            cin >> contacts[i].phone;
                            break;
                        case 9:
                            cout << "请输入新的QQ：";
                            cin >> contacts[i].QQ;
                            break;
                        case 10:
                            cout << "请输入新的微信号：";
                            cin >> contacts[i].Wechat;
                            break;
                        default:
                            cout << "无效的选择！" << endl;
                            break;
                        }
                        cout << "修改成功！" << endl;
                        system("pause");
                    }
                    break;
                }
            }
            break;
        }
        case 2:
        {
            cout << "请输入要修改的联系人姓名：";
            cin >> searchTerm;

            for (int i = 0; i < size; i++)
            {
                if (contacts[i].name == searchTerm)
                {
                    found = true;
                    while (true)
                    {
                        system("cls");
                        cout << "\n当前联系人信息：" << endl;
                        cout << "学号：" << contacts[i].studentID << endl;
                        cout << "姓名：" << contacts[i].name << endl;
                        cout << "性别：" << (contacts[i].sex == 1 ? "男" : "女") << endl;
                        cout << "专业：" << contacts[i].profession << endl;
                        cout << "班级：" << contacts[i].Class << endl;
                        cout << "宿舍号：" << contacts[i].dormitory << endl;
                        cout << "籍贯：" << contacts[i].native << endl;
                        cout << "手机号：" << contacts[i].phone << endl;
                        cout << "QQ：" << contacts[i].QQ << endl;
                        cout << "微信号：" << contacts[i].Wechat << endl;

                        showModifyMenu();
                        int modifyChoice;
                        cin >> modifyChoice;

                        if (modifyChoice == 0)
                        {
                            break;
                        }

                        switch (modifyChoice)
                        {
                        case 1:
                            cout << "请输入新的姓名：";
                            cin >> contacts[i].name;
                            break;
                        case 2:
                            cout << "请输入新的性别（1-男 2-女）：";
                            cin >> contacts[i].sex;
                            while (contacts[i].sex != 1 && contacts[i].sex != 2)
                            {
                                cout << "输入错误，请重新输入（1-男 2-女）：";
                                cin >> contacts[i].sex;
                            }
                            break;
                        case 3:
                            cout << "请输入新的专业：";
                            cin >> contacts[i].profession;
                            break;
                        case 4:
                            cout << "请输入新的班级：";
                            cin >> contacts[i].Class;
                            break;
                        case 5:
                            cout << "请输入新的宿舍号：";
                            cin >> contacts[i].dormitory;
                            break;
                        case 6:
                            cout << "请输入新的籍贯：";
                            cin >> contacts[i].native;
                            break;
                        case 7:
                            cout << "请输入新的手机号：";
                            cin >> contacts[i].phone;
                            break;
                        case 8:
                            cout << "请输入新的QQ：";
                            cin >> contacts[i].QQ;
                            break;
                        case 9:
                            cout << "请输入新的微信号：";
                            cin >> contacts[i].Wechat;
                            break;
                        default:
                            cout << "无效的选择！" << endl;
                            break;
                        }
                        cout << "修改成功！" << endl;
                        system("pause");
                    }
                    break;
                }
            }
            break;
        }
        default:
            cout << "无效的选择！" << endl;
            continue;
        }

        if (!found)
        {
            cout << "未找到匹配的联系人！" << endl;
            system("pause");
        }
        system("cls");
    }
}

void displayList(const Contact *contacts, int size)
{
    system("cls");
    if (size == 0)
    {
        cout << "通讯录为空！" << endl;
        system("pause");
        system("cls");
        return;
    }

    cout << "=======================================================通讯录列表=======================================================" << endl;
    cout << setw(12) << "学号"
         << setw(10) << "姓名"
         << setw(8) << "性别"
         << setw(15) << "专业"
         << setw(10) << "班级"
         << setw(10) << "宿舍号"
         << setw(10) << "籍贯"
         << setw(15) << "手机号"
         << setw(15) << "QQ"
         << setw(15) << "微信" << endl;
    cout << "========================================================================================================================" << endl;

    for (int i = 0; i < size; i++)
    {
        cout << setw(12) << contacts[i].studentID
             << setw(10) << contacts[i].name
             << setw(8) << (contacts[i].sex == 1 ? "男" : "女")
             << setw(15) << contacts[i].profession
             << setw(10) << contacts[i].Class
             << setw(10) << contacts[i].dormitory
             << setw(10) << contacts[i].native
             << setw(15) << contacts[i].phone
             << setw(15) << contacts[i].QQ
             << setw(15) << contacts[i].Wechat << endl;
    }

    cout << "\n总共有 " << size << " 位联系人" << endl;
    system("pause");
    system("cls");
}

void schedule()
{
    cout << "[";
    for (int i = 0; i < 20; i++)
    {
        cout << "=";
        Sleep(500);
    }
    cout << "]100%";
}
void sortContacts(Contact *contacts, int size)
{
    system("cls");
    if (size == 0)
    {
        cout << "通讯录为空！" << endl;
        system("pause");
        system("cls");
        return;
    }

    cout << "正在按学号排序...\n"
         << endl;
    schedule();
    // 冒泡排序
    bool swapped;
    for (int i = 0; i < size - 1; i++)
    {

        swapped = false;
        for (int j = 0; j < size - i - 1; j++)
        {
            if (contacts[j].studentID > contacts[j + 1].studentID)
            {
                swap(contacts[j], contacts[j + 1]);
                swapped = true;
            }
        }
        if (!swapped)
        {
            break;
        }
    }

    cout << "\n\n排序完成！" << endl;
    system("pause");
    system("cls");
}

void exportContacts(const Contact *contacts, int size)
{
    system("cls");
    if (size == 0)
    {
        cout << "通讯录为空，无数据可导出！" << endl;
        system("pause");
        system("cls");
        return;
    }

    // 使用固定的文件名
    const string filename = "contacts.txt";
    ofstream outFile(filename);
    if (!outFile)
    {
        cout << "无法创建文件！" << endl;
        system("pause");
        system("cls");
        return;
    }

    // 写入表头
    outFile << "学号,姓名,性别,专业,班级,宿舍号,籍贯,手机号,QQ,微信\n";

    // 写入数据
    for (int i = 0; i < size; i++)
    {
        outFile << contacts[i].studentID << ","
                << contacts[i].name << ","
                << (contacts[i].sex == 1 ? "男" : "女") << ","
                << contacts[i].profession << ","
                << contacts[i].Class << ","
                << contacts[i].dormitory << ","
                << contacts[i].native << ","
                << contacts[i].phone << ","
                << contacts[i].QQ << ","
                << contacts[i].Wechat << "\n";

        // 显示导出进度
        cout << "正在导出: " << (i + 1) << "/" << size << " 条记录\r";
        cout.flush();
    }

    outFile.close();
    cout << "\n\n导出完成！";
    cout << "共导出 " << size << " 条记录" << endl;

    system("pause");
    system("cls");
}

string getField(string &line, char delimiter)
{
    string field;
    size_t pos = line.find(delimiter);
    if (pos != string::npos)
    {
        field = line.substr(0, pos);
        line.erase(0, pos + 1);
    }
    else
    {
        field = line;
        line = "";
    }
    return field;
}

void importContacts(Contact *&contacts, int &size, int &capacity)
{
    system("cls");

    // 使用固定的文件名
    const string filename = "contacts_backup.txt";
    ifstream inFile(filename);
    if (!inFile)
    {
        cout << "未找到备份文件！" << endl;
        system("pause");
        system("cls");
        return;
    }

    cout << "正在从备份文件导入数据..." << endl;

    // 跳过表头行
    string header;
    getline(inFile, header);

    // 读取数据
    string line;
    int importCount = 0;
    int duplicateCount = 0;

    while (getline(inFile, line))
    {
        if (line.empty())
            continue;

        Contact newContact;
        string lineTemp = line;

        // 解析CSV行
        newContact.studentID = getField(lineTemp, ',');
        newContact.name = getField(lineTemp, ',');
        string sex = getField(lineTemp, ',');
        newContact.sex = (sex == "男" ? 1 : 2);
        newContact.profession = getField(lineTemp, ',');
        newContact.Class = getField(lineTemp, ',');
        newContact.dormitory = getField(lineTemp, ',');
        newContact.native = getField(lineTemp, ',');
        newContact.phone = getField(lineTemp, ',');
        newContact.QQ = getField(lineTemp, ',');
        newContact.Wechat = lineTemp; // 最后一个字段

        // 检查是否存在重复学号
        bool isDuplicate = false;
        for (int i = 0; i < size; i++)
        {
            if (contacts[i].studentID == newContact.studentID)
            {
                duplicateCount++;
                isDuplicate = true;
                break;
            }
        }

        if (!isDuplicate)
        {
            // 检查是否需要扩容
            if (size == capacity)
            {
                Contact *newContacts = new Contact[capacity * 2];
                for (int i = 0; i < size; i++)
                {
                    newContacts[i] = contacts[i];
                }
                delete[] contacts;
                contacts = newContacts;
                capacity *= 2;
            }

            contacts[size] = newContact;
            size++;
            importCount++;
        }

        // 显示导入进度
        cout << "正在导入数据... 已处理: " << importCount + duplicateCount << " 条记录\r";
        cout.flush();
    }

    inFile.close();

    cout << "\n\n导入完成！" << endl;
    cout << "成功导入: " << importCount << " 条记录" << endl;
    if (duplicateCount > 0)
    {
        cout << "跳过重复记录: " << duplicateCount << " 条" << endl;
    }

    system("pause");
    system("cls");
}


int main()
{
    Contact *contacts = new Contact[1];
    int size = 0;
    int capacity = 1;
    int select;
    while (true)
    {

        showmenu();
        cin >> select;

        switch (select)
        {
        case 1:
            add(contacts, size, capacity);
            break;
        case 2:
            search(contacts, size);
            break;
        case 3:
            deleteContact(contacts, size);
            break;
        case 4:
            modifyContact(contacts, size);
            break;
        case 5:
            displayList(contacts, size);
            break;
        case 6:
            sortContacts(contacts, size);
            break;
        case 7:
            exportContacts(contacts, size);
            exit(0);
            break;
        case 8:
            importContacts(contacts, size, capacity);
            break;
        case 0:
            exit(0);
        default:
            cout << "操作错误，请重新输入" << endl;
            system("pause");
            break;
        }
    }
    delete[] contacts;
    return 0;
}
