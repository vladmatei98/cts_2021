#include <iostream>
#include <string.h>

using namespace std;
#pragma warning(disable : 4996)

/*
Modificari:
-formatare cod (ex: stergere spatii inutile, aranjare acolade)
-redenumire nume variabile (ex: nr_studenti/nr_Studenti -> nrStudenti)
-redenumire nume functii (ex: getnume -> getNume)
-reordonarea functiilor de intrare-iesire in functie de clasa de care apartin
*/

class Student {
    const int cod;
    static int nrStudenti;
    int anNastere;
    string nume;
    float medieBac;
    int nrNote; 
    float* note;

public:

    Student(int anNastere) : cod(anNastere/12) 
    {
        this->anNastere = anNastere;
        this->nume = "";
        this->medieBac = 0;
        this->nrNote = 0;
        this->note = NULL;

        nrStudenti++;
    }

    Student() : cod(anNastere / 12)
    {
        anNastere = 0;
        nume = "";
        medieBac = 0;
        nrNote = 0;
        note = NULL;

        nrStudenti++;    
    }

    Student(int anNastere, string nume, int nrNote) : cod(anNastere / 12)
    {   
        this->anNastere = anNastere;
        this->nume = nume;
        this->nrNote = nrNote;
        this->medieBac = 0;
        this->note = NULL;

        nrStudenti++;    
    }

    Student(int anNastere, string nume, int nrNote, float* note, float medieBac) : cod(anNastere / 12)
    {        
        this->anNastere = anNastere;
        this->nume = nume;
        this->medieBac = medieBac;
        this->nrNote = nrNote;
        this->note = new float[nrNote];
        for (int i = 0; i < nrNote; i++) {
            this->note[i] = note[i];
        }

        nrStudenti++;
    }

    Student(const Student& sursa) : cod(sursa.cod)
    {
        anNastere = sursa.anNastere;
        nume = sursa.nume;
        medieBac = sursa.medieBac;
        nrNote = sursa.nrNote;
        note = new float[nrNote];
        if(sursa.note != NULL)
            for (int i = 0; i < nrNote; i++) 
            {
                note[i] = sursa.note[i];
            }
        else
            for (int i = 0; i < nrNote; i++)
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
        s.anNastere = x + 1;
        return s;
    }

    int getAnNastere()
    {
        return anNastere;
    }

    void setAnNastere(int anNastere)
    {
        if (anNastere > 1900)
            this->anNastere = anNastere;
    }

    string getNume()
    {
        return nume;
    }

    void setNume(string nume)
    {
        if (nume != "")
            this->nume = nume;
    }

    static int getNrStudenti()
    {
        return nrStudenti;
    }

    void calculeazaMedieBac()
    {
        if (nrNote != 0) {
            float sumaNote = 0;

            for (int i = 0; i < nrNote; i++)
            {
                sumaNote += note[i];
            }
            medieBac = sumaNote / nrNote;
        }
    }

    Student& operator=(const Student& sursa)
    {
        delete[] note;

        anNastere = sursa.anNastere;
        nume = sursa.nume;
        medieBac = sursa.medieBac;
        nrNote = sursa.nrNote;
        note = new float[nrNote];
        for (int i = 0; i < nrNote; i++) {
            note[i] = sursa.note[i];
        }

        return *this;
    }

    Student operator+(int valoare)
    {
        Student copie = *this;

        for (int i = 0; i < nrNote; i++)
            copie.note[i] += valoare;

        return copie;
    }

    Student& operator++()
    {
        anNastere++;
        return *this;
    }

    Student operator++(int)
    {
        Student copie = *this;
        anNastere++;
        return copie;
    }

    bool operator==(Student s)
    {
        return anNastere == s.anNastere;
    }

    Student& operator+=(float nota)
    {
        float sumaNote = 0;
        float* note_noi = new float[nrNote + 1];

        for (int i = 0; i < nrNote; i++)
        {
            note_noi[i] = note[i];
            sumaNote += note_noi[i];
        }

        nrNote++;
        note_noi[nrNote - 1] = nota;
        sumaNote += nota;
        medieBac = sumaNote / nrNote;

        delete[] note;

        note = note_noi;

        return *this;
    }

    Student& operator-=(float valoare)
    {
        float sumaNote = 0;
        for (int i = 0; i < nrNote; i++)
        {
            note[i] -= valoare;
            sumaNote += note[i];
        }

        medieBac = sumaNote / nrNote;

        return *this;
    }

    float& operator [](int index)
    {
        if (index >= 0 && index < nrNote)
            return note[index];
        else
            throw - 1; 
    }

    operator float()
    {
        return medieBac;
    }

    friend ostream& operator <<(ostream& out, Student s);
    friend istream& operator >>(istream& in, Student& s);
};

//Operator intrare Student
istream& operator >>(istream& in, Student& s)
{
    float sumaNote = 0;

    cout << "Nume student:";
    in >> s.nume;

    cout << "Anul nasterii:";
    in >> s.anNastere;
    
    cout << "Nr note:";
    in >> s.nrNote;

    delete[] s.note;

    s.note = new float[s.nrNote];

    cout << "Vector note:";
    for (int i = 0; i < s.nrNote; i++) {
        in >> s.note[i];
        sumaNote += s.note[i];
    }

    s.medieBac = sumaNote / s.nrNote;

    return in;
}

//Operator iesire Student
ostream& operator <<(ostream& out, Student s)
{
    out << s.cod << " " << s.nume << " " << s.anNastere << " " << s.nrNote << endl;
    if (s.note != NULL)
    {
        for (int i = 0; i < s.nrNote; i++)
            cout << s.note[i] << " ";
        out << endl;
    }
    out << s.medieBac << endl;

    return out;
}

class StudentStrain : public Student
{
protected:
    string taraProvenienta;
    string sedere;
    float* taxe;

public:
    StudentStrain() : taraProvenienta(""), sedere(""), taxe(NULL) {
    }

    StudentStrain(int anNastere, string nume, int nrNote, float* note, float medieBac, string taraProvenienta, string sedere, float* taxe)
        : Student(anNastere, nume, nrNote, note, medieBac), taraProvenienta(taraProvenienta), sedere(sedere), taxe(taxe) {
    }

    ~StudentStrain() {
        delete[] taxe;
    }

    StudentStrain(const StudentStrain& sursa) : Student(sursa)
    {
        taraProvenienta = sursa.taraProvenienta;
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

        taraProvenienta = sursa.taraProvenienta;
        sedere = sursa.sedere;
        taxe = new float[3];
        for (int i = 0; i < 3; i++) {
            taxe[i] = sursa.taxe[i];
        }

        Student::operator=(sursa);

        return *this;
    }

    string getTaraProvenienta()
    {
        return taraProvenienta;
    }

    void setTaraProvenienta(string taraProvenienta)
    {
        if (taraProvenienta != "")
            this->taraProvenienta = taraProvenienta;
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

//operator intrare StudentStrain
istream& operator >>(istream& in, StudentStrain& ss) {
    in >> (Student&)ss;
    cout << "Tara provenienta: ";
    in >> ss.taraProvenienta;
    cout << "Tip sedere: ";
    in >> ss.sedere;
    delete[] ss.taxe;
    cout << "Introduceti taxele aferente celor 3 semestre: ";
    for (int i = 0; i < 3; i++)
        in >> ss.taxe[i];
    return in;
}

//operator iesire StudentStrain
ostream& operator <<(ostream& out, StudentStrain ss) {
    out << (Student)ss;
    out << "Tara provenienta: " << ss.taraProvenienta << "Tip sedere: " << ss.sedere << endl;
    out << "Taxele aferente celor 3 semestre: ";
    for (int i = 0; i < 3; i++)
        out << ss.taxe[i] << " ";
    return out;
}

int Student::nrStudenti = 0;
/*
int main()
{
    cout<< "Nr initial studenti: " << Student::getNrStudenti() << endl;

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

    ss2.getTaraProvenienta();
    ss2.getSedere();
    ss2.getTaxe();

    float taxe2[] = { 5000, 4000, 3000 };
    ss2.setTaraProvenienta("Italia");
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
    s2.setAnNastere(2000);
    s2.setNume("Matei");
    cout << s2;

    s3 = s2;
    s3.setNume("Ionut");
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
    s6.calculeazaMedieBac();
    cout << s6;
    
    cout << "Nr final studenti: " << Student::getNrStudenti() << endl;
    
    _CrtDumpMemoryLeaks();
}*/