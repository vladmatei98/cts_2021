#include <iostream>
#include <string.h>

using namespace std;
#pragma warning(disable : 4996)

class Student {
    const int cod;
    static int nr_Studenti;
    int an_nastere;
    string nume;
    float medie_bac;
    int nr_note; float* note;

public:

    
    Student(int an_nastere) : cod(an_nastere/12) {
        this->an_nastere = an_nastere;
        this->nume = "";
        this->medie_bac = 0;
        this->nr_note = 0;
        this->note = NULL;

        nr_Studenti++;
    }

    
    Student() : cod(an_nastere / 12)    {
        an_nastere = 0;
        nume = "";
        medie_bac = 0;
        nr_note = 0;
        note = NULL;
        nr_Studenti++;    }

    
    Student(int an_nastere, string nume, int nr_note) : cod(an_nastere / 12)
    {   this->an_nastere = an_nastere;
        this->nume = nume;
        this->nr_note = nr_note;
        this->medie_bac = 0;
        this->note = NULL;
        nr_Studenti++;    }

    
    Student(int an_nastere, string nume, int nr_note, float* note, float medie_bac) : cod(an_nastere / 12)
    {        this->an_nastere = an_nastere;
        this->nume = nume;
        this->medie_bac = medie_bac;
        this->nr_note = nr_note;
        this->note = new float[nr_note];
        for (int i = 0; i < nr_note; i++) {
            this->note[i] = note[i];
        }
        nr_Studenti++;
    }

    
    Student(const Student& sursa) : cod(sursa.cod)
    {
        an_nastere = sursa.an_nastere;
        nume = sursa.nume;
        medie_bac = sursa.medie_bac;
        nr_note = sursa.nr_note;
        note = new float[nr_note];
        if(sursa.note != NULL)
            for (int i = 0; i < nr_note; i++) 
            {
                note[i] = sursa.note[i];
            }
        else
            for (int i = 0; i < nr_note; i++)
            {
                note[i] = 0;
            }


    }

    ~Student()
    {
        delete[] note;
        cout << "Destructor" << endl;
    }



    Student operator()(int x) {
        Student s;
        s.an_nastere = x + 1;
        return s;
    }

    
    int getannastere()
    {
        return an_nastere;
    }

    void setannastere(int an_nastere)
    {
        if (an_nastere > 1900)
            this->an_nastere = an_nastere;
    }

    string getnume()
    {
        return nume;
    }

    void setnume(string nume)
    {
        if (nume != "")
            this->nume = nume;
    }

    static int getnr_Studenti()
    {
        return nr_Studenti;
    }

    void calculeaza_medie_bac()
    {
        if (nr_note != 0) {
            float sumaNote = 0;

            for (int i = 0; i < nr_note; i++)
            {
                sumaNote += note[i];
            }
            medie_bac = sumaNote / nr_note;
        }
    }

    
        Student& operator=(const Student& sursa)
    {
        delete[] note;

        an_nastere = sursa.an_nastere;
        nume = sursa.nume;
        medie_bac = sursa.medie_bac;
        nr_note = sursa.nr_note;
        note = new float[nr_note];
        for (int i = 0; i < nr_note; i++) {
            note[i] = sursa.note[i];
        }

        return *this;
    }

    
    Student operator+(int valoare)
    {
        Student copie = *this;

        for (int i = 0; i < nr_note; i++)
            copie.note[i] += valoare;

        return copie;
    }

    
    Student& operator++()
    {
        an_nastere++;
        return *this;
    }

    
    Student operator++(int)
    {
        Student copie = *this;
        an_nastere++;
        return copie;
    }

    
    bool operator==(Student s)
    {
        return an_nastere == s.an_nastere;
    }

    
    Student& operator+=(float nota)
    {
        float sumaNote = 0;
        float* note_noi = new float[nr_note + 1];

        for (int i = 0; i < nr_note; i++)
        {
            note_noi[i] = note[i];
            sumaNote += note_noi[i];
        }

        nr_note++;
        note_noi[nr_note - 1] = nota;
        sumaNote += nota;
        medie_bac = sumaNote / nr_note;

        delete[] note;

        note = note_noi;

        return *this;
    }

    
    Student& operator-=(float valoare)
    {
        float sumaNote = 0;
        for (int i = 0; i < nr_note; i++)
        {
            note[i] -= valoare;
            sumaNote += note[i];
        }

        medie_bac = sumaNote / nr_note;

        return *this;
    }

    
    float& operator [](int index)
    {
        if (index >= 0 && index < nr_note)
            return note[index];
        else
            throw - 1; 
    }

    
    operator float()
    {
        return medie_bac;
    }

    friend ostream& operator <<(ostream& out, Student s);
    friend istream& operator >>(istream& in, Student& s);

};

class StudentStrain : public Student
{
protected:
    string taraprovenienta;
    string sedere;
    float* taxe;
public:
    StudentStrain() : taraprovenienta(""), sedere(""), taxe(NULL) {

    }

    StudentStrain(int an_nastere, string nume, int nr_note, float* note, float medie_bac, string taraprovenienta, string sedere, float* taxe)
        : Student(an_nastere, nume, nr_note, note, medie_bac), taraprovenienta(taraprovenienta), sedere(sedere), taxe(taxe) {

    }

    ~StudentStrain() {
        delete[] taxe;
    }

    StudentStrain(const StudentStrain& sursa) : Student(sursa)
    {
        taraprovenienta = sursa.taraprovenienta;
        sedere = sursa.sedere;
        taxe = new float[3];
        for (int i = 0; i < 3; i++) {
            taxe[i] = sursa.taxe[i];
        }
        *this = sursa;
    }

    StudentStrain& operator=(const StudentStrain& sursa)
    {
        delete[] taxe;

        taraprovenienta = sursa.taraprovenienta;
        sedere = sursa.sedere;
        taxe = new float[3];
        for (int i = 0; i < 3; i++) {
            taxe[i] = sursa.taxe[i];
        }

        Student::operator=(sursa);

        return *this;
    }

    string gettaraprovenienta()
    {
        return taraprovenienta;
    }

    void settaraprovenienta(string taraprovenienta)
    {
        if (taraprovenienta != "")
            this->taraprovenienta = taraprovenienta;
    }

    string getSedere()
    {
        return sedere;
    }

    void setSedere(string sedere)
    {
        if (sedere != "")
            this->sedere = sedere;
    }

    void getTaxe() {
        for (int i = 0; i < 3; i++)
            cout << taxe[i] << " ";
        cout << endl;
    }

    void setTaxe(float* taxe) {
        this->taxe = taxe;
    }

    friend istream& operator >>(istream& in, StudentStrain& ss);
    friend ostream& operator <<(ostream& out, StudentStrain ss);

};

istream& operator >>(istream& in, StudentStrain& ss) {
    in >> (Student&)ss;
    cout << "Tara provenienta: ";
    in >> ss.taraprovenienta;
    cout << "Tip sedere: ";
    in >> ss.sedere;
    delete[] ss.taxe;
    cout << "Introduceti taxele aferente celor 3 semestre: ";
    for (int i = 0; i < 3; i++)
        in >> ss.taxe[i];
    return in;
}

ostream& operator <<(ostream& out, StudentStrain ss) {
    out << (Student)ss;
    out << "Tara provenienta: " << ss.taraprovenienta << "Tip sedere: " << ss.sedere << endl;
    out << "Taxele aferente celor 3 semestre: ";
    for (int i = 0; i < 3; i++)
        out << ss.taxe[i] << " ";
    return out;
}

//Operator intrare
istream& operator >>(istream& in, Student& s)
{
    float sumaNote = 0;

    cout << "Nume student:";
    in >> s.nume;

    cout << "Anul nasterii:";
    in >> s.an_nastere;
    
    cout << "Nr note:";
    in >> s.nr_note;

    delete[] s.note;

    s.note = new float[s.nr_note];

    cout << "Vector note:";
    for (int i = 0; i < s.nr_note; i++) {
        in >> s.note[i];
        sumaNote += s.note[i];
    }

    s.medie_bac = sumaNote / s.nr_note;

    return in;
}

//Operator iesire
ostream& operator <<(ostream& out, Student s)
{
    out << s.cod << " " << s.nume << " " << s.an_nastere << " " << s.nr_note << endl;
    if (s.note != NULL)
    {
        for (int i = 0; i < s.nr_note; i++)
            cout << s.note[i] << " ";
        out << endl;
    }
    out << s.medie_bac << endl;

    return out;
}

int Student::nr_Studenti = 0;
/*
int main()
{
    cout<< "Nr initial studenti: " << Student::getnr_Studenti() << endl;

    StudentStrain ss1;
    cin >> ss1;
    cout << ss1;

    Student s1;

    float note[] = { 9, 9, 7 };
    float taxe[] = { 4000, 4000, 3500 };
    StudentStrain ss2(2001, "Gigel", 3, note, 0, "Germania", "permanenta", taxe);

    StudentStrain ss3 = ss2;

    cout << ss3;

    ss1 = ss2;
    cout << ss1;

    ss2.gettaraprovenienta();
    ss2.getSedere();
    ss2.getTaxe();

    float taxe2[] = { 5000, 4000, 3000 };
    ss2.settaraprovenienta("Italia");
    ss2.setSedere("temporara");
    ss2.setTaxe(taxe2);

    Student* s;
    s = &ss1;

    Student* sv[3];

    sv[0] = &s1;//adresa obiect baza
    sv[1] = &ss2;//adresa obiect derivat
    sv[2] = new StudentStrain;
    /*
    Student s1, s3, s5;

    cin>>s1;
    s1 -= 1;
    cout<<s1;

    Student s2 = s1;
    s2.setannastere(2000);
    s2.setnume("Matei");
    cout << s2;

    s3 = s2;
    s3.setnume("Ionut");
    cout << s3;

    if (s1 == s2)
        cout << "Acelasi an al nasterii" << endl;
    else
        cout << "An al nasterii diferit" << endl;

    cout << float(s1) << endl;

    s5 = s1(2000);
    cout << s5;

    Student s4(2001, "Gigel", 3);
    cout << s4;

    float note[] = { 9, 9, 7 };
    Student s6(2001, "Gigel", 3, note, 0);
    s6.calculeaza_medie_bac();
    cout << s6;
    
    cout << "Nr final studenti: " << Student::getnr_Studenti() << endl;
    
    _CrtDumpMemoryLeaks();
}*/