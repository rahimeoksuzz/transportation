#include <iostream>
#include <array>
#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <stdexcept>

using namespace std;

class AracTuru
{
	
public:
	AracTuru(vector<char>& aracTuruInput) :aracTuru{ aracTuruInput }
	{

	}
	
	friend ostream& operator <<(ostream& out, Arac &arac)
	{
		AracTuru temp{ arac.getAracTuru() };
		for (int i{ 0 }; i < temp.aracTuru.size(); i++)
		{
			out << temp.aracTuru[i];
		}
		return out;
	}

private:
	vector<char>aracTuru;
};

class SorumluSofor
{
public:
	SorumluSofor(string adInput, string soyadInput) :
		ad{ adInput }, soyad{ soyadInput }
	{

	}

	string getAd()
	{
		return ad;
	}

	string getSoyad()
	{
		return soyad;
	}

private:
	string ad;
	string soyad;

};

class Plaka
{
public:
	Plaka(string plakaInput)
	{
		if (plakaInput.size() > 8)
			throw out_of_range("AŞIRI YÜKLEME!!!");
		else
		{
			if (plakaInput[0] > 0 && plakaInput[0] < 8)
			{
				plaka[0] = plakaInput[0];
				if (plakaInput[1] >= 0 && plakaInput[1] <= 9)
					plaka[1] = plakaInput[1];
			}
			else if (plakaInput[0] == 0)
			{
				plaka[0] = plakaInput[0];
				if (plakaInput[1] == 1)
					plaka[1] = plakaInput[1];
			}
			else if (plakaInput[0] == 8)
			{
				plaka[0] = plakaInput[0];
				if (plakaInput[1] == 0 || plakaInput[1] == 1)
					plaka[1] = plakaInput[1];
			}
			else
				throw invalid_argument("HATALI DEGER!!!");

			if (plakaInput[2] >= 'A' && plakaInput[2] <= 'Z')
				plaka[2] = plakaInput[2];
			else
				throw invalid_argument("HATALI DEGER!!!");

			for (int i{ 3 }; i < 6; ++i) {
				if (plakaInput[i] >= 'A' && plakaInput[i] <= 'Z')
					plaka[i] = plakaInput[i];
				else if (plakaInput[i] >= 0 && plakaInput[i] <= 9)
					plaka[i] = plakaInput[i];
				else
					throw invalid_argument("HATALI DEGER!!!");
			}
			for (int i{ 6 }; i < 8; ++i) {
				if (plakaInput[i] >= 0 && plakaInput[i] <= 9)
					plaka[i] = plakaInput[i];
				else
					throw invalid_argument("HATALI DEGER!!!");
			}
		}
	}

	string getPlakaTemp() //overloadda kullanılacak getter fonksiyonu
	{
		return plaka;
	}

private:
	string plaka;
};


enum class YukTuru {
	KURU_YUK,
	GIDA,
	KIMYASAL
};

ostream& operator <<(ostream& out, const YukTuru& yukturu)
{
	switch (yukturu) {
	case YukTuru::KURU_YUK: out << "KURU_YUK"; break;
	case YukTuru::GIDA: out << "GIDA"; break;
	case YukTuru::KIMYASAL: out << "KIMYASAL"; break;

	}
	return out;
}

class YukBilgisi
{
public:

	YukBilgisi(YukTuru yukTuruInput, const string& yukIsmiInput, int yukKapasitesiInput, int yukHacmiInput) :
		yukIsmi{ yukIsmiInput }, yukTuru{ yukTuruInput }
	{
		setYukKapasitesi(yukKapasitesiInput);
		setYukHacmi(yukHacmiInput);
	}

	int getYukKapasitesi()const {
		return yukKapasitesi;
	}

	void setYukKapasitesi(int yukKapasitesiIn) {
		if (yukKapasitesiIn >= 0)
			yukKapasitesi = yukKapasitesiIn;
		else
			throw invalid_argument("0 DAN KUCUK OLMAZ!!!");
	}

	int getYukHacmi()const {
		return yukHacmi;
	}

	void setYukHacmi(int yukHacmiInput) {
		if (yukHacmiInput >= 0)
			yukHacmi = yukHacmiInput;
		else
			throw invalid_argument("0 DAN KUCUK OLMAZ!!!");
	}

	YukTuru getYukTuru() const {
		return yukTuru;
	}

	void setYukTuru(YukTuru yukTipiInput) {
		yukTuru = yukTipiInput;
	}

	string getYukIsmi()const {
		return yukIsmi;
	}
	void setYukIsmi(const string& yukIsmiInput) {
		yukIsmi = yukIsmiInput;
	}

	bool operator >(const YukBilgisi& yukKapasite) const
	{
		return yukKapasitesi < yukKapasite.yukKapasitesi;
	}

	bool operator <(const YukBilgisi& yukHacim) const
	{
		return yukHacmi < yukHacim.yukHacmi;
	}
	/*
	bool operator <(const Yuk& yukIsim) const
	{
		return yukIsmi < yukIsim.yukIsmi;
	}
	*/

private:
	int yukKapasitesi;
	int yukHacmi;
	string yukIsmi;
	YukTuru yukTuru;
};


class Arac
{
	friend ostream& operator <<(ostream& out, const Arac& arac)
	{
		out << "Arac Turu:" << arac.getAracTuru() << endl;
		out << "Plaka: " << arac.getPlaka().getPlakaTemp() << endl;
		out << "Sofor" << arac.getAracSofor().getAd() << " " << arac.getAracSofor().getSoyad() << endl;

		for (const YukBilgisi& yuk : arac.yukListesi)
		{
			out << "Yuk Turu" << yuk.getYukTuru() << endl;
			out << "Yuk Adi" << yuk.getYukIsmi() << endl;
			out << "Yuk Agirligi" << yuk.getYukKapasitesi() << endl;
			out << "Yuk Hacmi" << yuk.getYukHacmi() << endl;

		}
		return out;
	}

public:

	Arac(Plaka aracPlakaInput, SorumluSofor aracSoforInput, list<YukBilgisi> yukListesiInput, AracTuru aracTuruInput) :
		aracPlaka{ aracPlakaInput },
		aracSofor{ aracSoforInput },
		aracTuru{ aracTuruInput }
	{
		setYukListesi(yukListesiInput);
	}
	virtual ~Arac();

	virtual AracTuru getAracTuru() const {
		return aracTuru;
	}

	virtual void setAracTuru(AracTuru aracTuruInput) {
		aracTuru = aracTuruInput;
	}

	virtual Plaka getPlaka() const {
		return aracPlaka;
	}

	virtual void setPlaka(Plaka aracPlakaInput) {
		aracPlaka = aracPlakaInput;
	}

	virtual SorumluSofor getAracSofor() const {
		return aracSofor;
	}

	virtual void setAracSofor(SorumluSofor aracSoforInput) {
		aracSofor = aracSoforInput;
	}

	virtual list<YukBilgisi> getYukListesi() const {
		return yukListesi;
	}

	virtual void setYukListesi(list<YukBilgisi> yukListesiInput) {
		yukListesi = yukListesiInput;
	}

	virtual void yukEkle(YukBilgisi yukInput) {
		yukListesi.push_back(yukInput);
	}

	virtual void yukBosalt(YukBilgisi yukInput) {
		yukListesi.remove(yukInput);
	}

	virtual void yukleriBosalt() { //tüm yükleri tek seferde boşaltan fonksiyon 
		yukListesi.clear();
	}

	virtual bool doluMu() { //Aracın yüklü olup olmadığını öğrenen fonksiyon
		return yukListesi.empty();
	}

	Arac& operator+=(Arac& aracInput) //araca yük eklenmesini sağlayan fonksiyon
	{
		for (YukBilgisi& yuk : aracInput.yukListesi)
		{
			this->yukListesi.push_back(yuk);
		}
		return *this;
	}

	Arac& operator-=(Arac& aracInput) //aractana yük çıkarılmasını sağlayan fonksiyon
	{
		for (YukBilgisi& yuk : aracInput.yukListesi)
		{
			this->yukListesi.remove(yuk);
		}
	}

	void siralamaKapasite(list<YukBilgisi> input)
	{

		input.sort([](const YukBilgisi& yuk1, const YukBilgisi& yuk2)
		{
			if (yuk1.getYukKapasitesi() == yuk2.getYukKapasitesi())
				return yuk1 > yuk2;
			return yuk1.getYukKapasitesi() > yuk2.getYukKapasitesi();
		});
	}

	void siralamaHacim(list<YukBilgisi> input)
	{

		input.sort([](const YukBilgisi& yuk1, const YukBilgisi& yuk2)
		{
			if (yuk1.getYukHacmi() == yuk2.getYukHacmi())
				return yuk1 < yuk2;
			return yuk1.getYukHacmi() < yuk2.getYukHacmi();
		});
	}

	void siralamaAlfabetik(list<YukBilgisi> input)
	{

		input.sort([](const YukBilgisi& yuk1, const YukBilgisi& yuk2)
		{
			if (yuk1.getYukIsmi() == yuk2.getYukIsmi())
				return yuk1 < yuk2;
			return yuk1.getYukIsmi() < yuk2.getYukIsmi();
		});
	}

	virtual double kapasiteToplami()
	{
		double kapasiteToplam;
		for (YukBilgisi& yuk : yukListesi)
		{
			kapasiteToplam += yuk.getYukKapasitesi();
		}
		return kapasiteToplam;
	}

	virtual double hacimToplami()
	{
		double hacimToplam;
		for (YukBilgisi& yuk : yukListesi)
		{
			hacimToplam += yuk.getYukHacmi();
		}
		return hacimToplam;
	}

private:
	AracTuru aracTuru;
	Plaka aracPlaka;
	SorumluSofor aracSofor;
	list<YukBilgisi> yukListesi;
};

class Kamyon :public Arac {
public:

	Kamyon(Plaka plakaInput, SorumluSofor soforInput, list<YukBilgisi> yukListesiInput, AracTuru aracTuruInput, double maksimum) :
		Arac(plakaInput, soforInput, yukListesiInput, aracTuruInput)
	{
		setMaxAgirlik();
	}

	double getMaksimumKapasite()
	{
		return maksimumKapasite;
	}

	void setMaxAgirlik()
	{
		double maksimumKapasiteInput = kapasiteToplami();
		if (maksimumKapasiteInput >= 2000 && maksimumKapasiteInput <= 10000)
			maksimumKapasite = maksimumKapasiteInput;
		else
			throw out_of_range("HATALI YUKLEME!!!");
	}

private:
	double maksimumKapasite;
};


class Kamyonet :public Arac
{
public:
	Kamyonet(Plaka plakaInput, SorumluSofor soforInput, list<YukBilgisi> yukListesiInput, AracTuru aracTuruInput) :
		Arac(plakaInput, soforInput, yukListesiInput, aracTuruInput)
	{

	}

	double getMaksimumKapasite()const {
		return maksimumKapasite;
	}

	void setMaksimumKapasite()
	{
		double maksimumKapasiteInput = kapasiteToplami();
		if (maksimumKapasiteInput >= 1500 && maksimumKapasiteInput <= 3000)
			maksimumKapasite = maksimumKapasiteInput;
		else
			throw out_of_range("HATALI YUKLEME!!!");
	}

private:
	double maksimumKapasite;
};

class AcikKasaKamyonet :public Kamyonet
{
public:
	AcikKasaKamyonet(Plaka plakaInput, SorumluSofor soforInput, list<YukBilgisi> yukListesiInput, AracTuru aracTuruInput, int maksimum) :
		Kamyonet(plakaInput, soforInput, yukListesiInput, aracTuruInput)
	{

	}

private:

};

class KapaliKasaKamyonet :public Kamyonet
{
public:
	KapaliKasaKamyonet(Plaka plakaInput, SorumluSofor soforInput, list<YukBilgisi> yukListesiInput, AracTuru aracTuruInput, int maksimumKapasite, int maksimumHacim) :
		Kamyonet(plakaInput, soforInput, yukListesiInput, aracTuruInput)
	{

	}

	void setMaksimumHacim()
	{
		double maksimumHacimInput = hacimToplami();
		if (maksimumHacimInput >= 10 && maksimumHacimInput <= 30)
			maksimumHacim = maksimumHacimInput;
		else
			throw out_of_range("HATALI YUKLEME!!!");
	}

private:
	double maksimumHacim;
};

class SogutmaliKasaKamyonet :public KapaliKasaKamyonet
{
public:
	SogutmaliKasaKamyonet(Plaka plakaInput, SorumluSofor soforInput, list<YukBilgisi> yukListesiInput, AracTuru aracTuruInput, int maksimumKapasite, int maksimumHacim, int sicaklik) :
		KapaliKasaKamyonet(plakaInput, soforInput, yukListesiInput, aracTuruInput, maksimumKapasite, maksimumHacim)
	{
		if (sicaklik > -10 || sicaklik < -40)
			throw out_of_range("VERILEN SICAKLIK DEGERLERI ARASINDA DEGIL!!!");
		else
			maksimumSicaklik = sicaklik;
	}

private:
	double maksimumSicaklik;
};

class TIR : public Arac
{
public:
	TIR(Plaka plakaInput, SorumluSofor soforInput, list<YukBilgisi> yukListesiInput, AracTuru aracTuruInput, char*dorse, int maksimumHacim) :
		Arac(plakaInput, soforInput, yukListesiInput, aracTuruInput), dorse{ dorse }
	{

	}

	void setMaxHacim()
	{
		double maksimumHacimInput = hacimToplami();
		if (maksimumHacimInput >= 30 && maksimumHacimInput <= 40)
			maksimumHacim = maksimumHacimInput;
		else
			throw out_of_range("HATALI YUKLEME!!!");
	}

	char getDorse() {
		return *dorse;
	}

	void setDorse(char) {

	}

private:
	double maksimumHacim;
	char* dorse{ NULL };
};


int main() {

	list <YukBilgisi> yukList;

	char* dorse = new char[20];

	Plaka plaka("34AB134");
	SorumluSofor sofor("Leo", "Mess");
	YukBilgisi yuk1(YukTuru::KURU_YUK, "mercimek", 0, 27);
	YukBilgisi yuk2(YukTuru::GIDA, "domates", 0, 28);
	yukList.push_back(yuk1);
	yukList.push_back(yuk2);

	vector <char> aracIsmi{ 'T', 'I', 'R' };
	AracTuru arac(aracIsmi);

	TIR t(plaka, sofor, yukList, arac, dorse, 35);

	return 0;

}
