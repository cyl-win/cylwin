#ifndef STUDENTINFO_H
#define STUDENTINFO_H
#include <QString>

class StudentInfo
{
public:
    QString name,id;
    int  math, english, languageC;
    double avg;
public:
    StudentInfo();
    StudentInfo(QString tname, QString tid, int tmath, int tenglish, int tlanguageC){
        name = tname;
        id = tid;
        math = tmath;
        english = tenglish;
        languageC = tlanguageC;
        avg = (tmath + tenglish + tlanguageC) / 3.0;
    }
    QString getId(){
        return id;
    }
    QString getName(){
        return name;
    }
    int getMath(){
        return math;
    }
    int getEnglish(){
        return english;
    }
    int getLanguageC(){
        return languageC;
    }
    double getAvg(){
        return avg;
    }
    void setId(QString tid){
        id = tid;
    }
    void setName(QString tname){
        name = tname;
    }
    void setMath(int tmath){
        math = tmath;
        avg = (math + english + languageC) / 3.0;
    }
    void setEnglish(int tenglish){
        english = tenglish;
        avg = (math + english + languageC) / 3.0;
    }
    void setLanguageC(int tlanguageC){
        languageC = tlanguageC;
        avg = (math + english + languageC) / 3.0;
    }
};


#endif // STUDENTINFO_H
