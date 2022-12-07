#include <iostream>
#include <string>
#include <string.h>
#include <sstream>
#include <vector>
#include <fstream>
#include <math.h>
using namespace std;

struct Company
{
    string name;
    string profit_tax;
    string address;
};

void Clear_Company(Company& com)
{
    com.name = "";
    com.profit_tax = "";
    com.address = "";

}
vector<Company> readCompanyList(string file_name)
{
    fstream f;
    vector <Company> v;
    f.open(file_name, ios::in);

    if (!f.is_open())
    {
        cout << "Khong mo duoc file";
        return v;
    }

    string line;
    string temp;
    //Dong dau tien cua file
    getline(f, line);

    // Duyet txt
    while (!f.eof())
    {
        //Doc 1 dong
        getline(f, line);
        stringstream ss(line);

        Company com;

        //Ten cong ty
        getline(ss, temp, '|');
        com.name = temp;

        //MST
        getline(ss, temp, '|');
        com.profit_tax = temp;

        //Dia chi
        getline(ss, temp, '\n');
        com.address = temp;

        v.push_back(com);
    }

    f.close();
    return v;
}

long long hashString(string com_name)
{
    unsigned long long m = pow(10, 9) + 9;
    unsigned long long p = 31;
    long long sum = 0;

    // Cắt chuỗi cần tính từ 1 company name
    string hash_string;
    if (com_name.size() > 20)
        hash_string = com_name.substr(com_name.size() - 20, 20);
    else
        hash_string = com_name;

    // Hàm băm
    for (int i = 0; i < hash_string.size(); i++)
    {
        sum += int(hash_string[i]) * pow(p, i);
       
    }

    return sum % m;

}

Company* createHashTable(vector<Company> list_company)
{
    int n = 1500;
    Company* p = new Company[n];


    // Khoi tao mang rong
    for (int i = 0; i < n; i++)
        Clear_Company(p[i]);

    int com_value = 0;

    for (int i = 0; i < list_company.size(); i++)
    {
        // Tim vi tri cua 1 company
        com_value = hashString(list_company[i].name) % n;

        // Kiem tra xem vi tri co dc chon chua, khong thi dung do tuyen tinh
        while (p[com_value].name != "")
        {
            com_value++;
            if (com_value == 1500)
                com_value = 0;
        }

        // Sau khi da co vi tri rong, gan company vao
        p[com_value] = list_company[i];
    }

    return p;
}

void Hash_table_output(string file_name, Company* p)
{
    fstream f;
    f.open(file_name, ios::out);
    for (int i = 0; i < 1500; i++)
        f << p[i].name << " | " << p[i].profit_tax << " | " << p[i].address << endl;

    f.close();
}

void insert(Company* p, Company company)
{
    int com_value = hashString(company.name) % 150;
    //Kiem tra vi tri
    while (p[com_value].name != "")
    {
        com_value++;
        if (com_value == 150)
            com_value = 0;
    }

    p[com_value] = company;

}

Company* search(Company* p, string company_name)
{
    Company* com;

    int com_value = hashString(company_name) % 150;

    // Tim tuan tự và quay đầu, vị trí cuối cùng sẽ là value - 1
    int end = com_value - 1;
    int index = com_value;
    while (index != end)
    {
        if (company_name != p[index].name)
            index++;
        else
        {
            com = &p[index];
            return com;
        }

        if (index == 150)
            index = 0;
    }

    return NULL;
}
int main()
{
    vector <Company> v;
    v = readCompanyList("MST.txt");
    Company* p = createHashTable(v);
    Company tan;
    tan.name = "CONG TY CO PHAN MAT GOC FIT@HCMUS";
    tan.profit_tax = "21120145";
    tan.address = "My Xuyen Soc Trang";
    insert(p, tan);
    /*for (int i = 0; i < v.size(); i++)
        cout << hashString(v[i].name) << endl;*/
    Hash_table_output("hash_table_output.txt", p);

    Company temp;
    cout << "Enter name: ";
    getline(cin,temp.name);
    if (search(p, temp.name) != NULL) {
        cout << "This company has appeared in this List\n";
    }
    else cout << "NOT FOUND!\n";


    return 0;
}
