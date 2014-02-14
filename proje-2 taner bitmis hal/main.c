#include <stdio.h>
#include <stdlib.h>
struct ogrenci//ogrenci bilgilerinin tutuldugu struct
{
    int ogr_no;
    char ad_soyad[30];
    int sinif;
    int kredi;
    float not_ortalamasi;
    struct ogrenci *sonraki;
};
struct no_not//dersler dizisine baglanan notlarin tutuldugu struct
{
    int ogr_no;
    int ogr_not;
    struct no_not *noya_gore_sonraki;
    struct no_not *nota_gore_sonraki;
    struct no_not *nota_gore_onceki;
};
struct ders//derslerin bilgilerini tutmaya yarayan struct
{
    int ders_kodu;
    char ders_adi[25];
    int kredi;
    int ogr_sayisi;
    float genel_not_ort;
    struct no_not *sonraki;//dersler dizisine notlar structini bagliyor
};

int sayi_al(int,int);
int  ogrenci_ara(struct ogrenci *liste_basi_ptr, int aranan_no,int hash1);
void ogrenci_ekle_sirali(struct ogrenci **ilk,struct ogrenci *yeni);
int donem_bul(struct ders *dersler[90]);
void ders_ekle(struct ders **ilk_ptr, struct ders *yeni);
void dairesel_sirali_ekle(struct no_not **liste_basi_ptr, struct no_not *yeni);
void d_cift_sirali_ekle(struct no_not **liste_basi_ptr, struct no_not *yeni);
void ogrenci_bilgileri_listele(struct ogrenci *liste_basi_ptr, int aranan_no);
void ogrenci_ara_guncelle(struct ogrenci **liste_basi_ptr, int aranan_no, int yeni_kredi, int note , int hash1);
int derslerde_ogrenci_ara(struct no_not **liste_basi_ptr,int aranan_no,struct ogrenci **head,int kredi);
void d_cift_baglidan_dugum_cikar(struct no_not *cikarilacak);
void sinifa_gore_listele(struct ogrenci *hash[100],int say[100]);
void dersten_listele(struct ders *dersler[90],int say[100],struct ogrenci *hash[100]);
void ders_ogrencilerinden_not_ust_olanlari_listele(struct ders *dersler[90],struct ogrenci *hash[100]);
void ders_ogrencilerinden_not_alt_olanlari_listele(struct ders *dersler[90],struct ogrenci *hash[100]);
struct ogrenci *sil_gitsin(struct ogrenci **liste_basi_ptr, int silinecek);
void ogrenci_sil(struct ogrenci *hash[100],struct ders *dersler[90],int say[100]);
void dersten_ogrenci_sil(struct ders *dersler[90],int silinecek);

int main()
{
    int i;
    int secim,ders_kodu;
    int hash1;
    char okunan_deger;
    struct ogrenci *yeni_ogrenci;
    struct ders *dersler[90];
    struct ogrenci *hash[100];
    struct no_not *derse_girilirken_eklenen_ogr;
    int ogrenci_no;
    int bulunan_ders_no;
    struct ders *yeni_ders;
    int ders_kredisi;
    struct no_not *gecici;
    int toplam_not;
    int donem_no;
    int kredi_say=0;
    static int say[100]= {0};
    float yeni_not;
    for(i=0; i<100; i++) //hash dizimizi ilkledik
    {
        hash[i]=NULL;
    }
    for(i=0; i<90; i++)//dersler dizisini ilkledik
    {
        dersler[i]=NULL;
    }
    do
    {
        printf("------------------------>OGRENCI-DERS TAKIP SISTEMI 2<------------------------\n");
        printf("1. Yeni bir ogrencinin eklenmesi\n");
        printf("2. Yeni bir dersin eklenmesi\n");
        printf("3. Bir dersi alan ogrencilerin notlarinin eklenmesi\n");
        printf("4. Bir dersi alan bir ogrencinin notunun guncellenmesi\n");
        printf("5. Bir ogrencinin silinmesi\n");
        printf("6. Bir dersin bilgilerinin ve o dersi alan ogrencilerin listelenmesi\n");
        printf("7. Bir dersi alan ogrencilerden, notu belirli bir notun ustunde olan\n   ogrencilerin listelenmesi\n");
        printf("8. Bir dersi alan ogrencilerden, notu belirli bir notun altinda olan\n   ogrencilerin listelenmesi\n");
        printf("9. Bir donemin derslerinin listelenmesi\n");
        printf("10. Bir ogrencinin bilgilerinin listelenmesi\n");
        printf("11. Bir ogrencinin bilgilerinin ve aldigi derslerin listelenmesi\n");
        printf("12. Bir sinifta okuyan ogrencilerin listelenmesi\n");
        printf("13. Cikis\n\n");
        printf("     Seciminizi giriniz:");
        scanf("%d",&secim);
        switch(secim)
        {
        case 1:
            printf("\nLutfen yeni ogrencinin numarasi icin ");
            ogrenci_no=sayi_al(1,10000);
            hash1=(ogrenci_no-1)/100;//hash degeri elde edilmesi
            if(ogrenci_ara(hash[hash1],ogrenci_no,say[hash1])==1)
                printf("Bu numarada ogrenci var!\n");
            else //ogrenci varsa
            {
                yeni_ogrenci=malloc(sizeof(struct ogrenci)); // bellekte yer ayýrýlmasý
                yeni_ogrenci->ogr_no=ogrenci_no;
                yeni_ogrenci->kredi=0;
                yeni_ogrenci->not_ortalamasi=0;
                printf("Lutfen ogrencinin ad ve soyadini giriniz:\n");
                fflush(stdin);
                gets(yeni_ogrenci->ad_soyad);
                printf("Lutfen ogrencinin sinifi icin \n");
                yeni_ogrenci->sinif=sayi_al(1,4);
                ogrenci_ekle_sirali(&hash[hash1],yeni_ogrenci);
                say[hash1]++;//hashin hangi satirinda kac eleman oldugunu tutuyor
            }
            break;
        case 2:
            bulunan_ders_no=donem_bul(dersler);
            yeni_ders=malloc(sizeof(struct ders));//yeni ders icin bellekte yer ayrilmasi
            yeni_ders->ders_kodu=bulunan_ders_no;
            printf("Lutfen dersin adini giriniz:\n");
            fflush(stdin);
            gets(yeni_ders->ders_adi);
            printf("Lutfen dersin kredisini giriniz:\n");
            scanf("%d",&yeni_ders->kredi);
            yeni_ders->ogr_sayisi=0;
            yeni_ders->genel_not_ort=0;
            ders_ekle(&dersler[bulunan_ders_no],yeni_ders);//ders ekle fonk.una gonderilme
            break;
        case 3:
            printf("Lutfen islem yapmak istediginiz dersin kodu icin \n");
            ders_kodu=sayi_al(10,89);
            if(dersler[ders_kodu]!=NULL)//boyle bir ders olup olmadigini kontrol ediyor
            {
                ders_kredisi=dersler[ders_kodu]->kredi;//guncellerken fonk.a gonderilecek
                do
                {
                    printf("Lutfen notunu girmek istediginiz ogrenci icin \n");
                    ogrenci_no=sayi_al(1,10000);
                    hash1=(ogrenci_no-1)/100;
                    if(ogrenci_ara(hash[hash1],ogrenci_no,say[hash1])==0)
                        printf("Bu numarada ogrenci yok!\n");
                    else//ogrenci varsa
                    {
                        derse_girilirken_eklenen_ogr=malloc(sizeof(struct no_not));//dersler dizisine baglanmasý icin yer ayriliyor
                        derse_girilirken_eklenen_ogr->ogr_no=ogrenci_no;
                        printf("Ogrencinin notu icin ");
                        derse_girilirken_eklenen_ogr->ogr_not=sayi_al(0,100);
                        dairesel_sirali_ekle(&dersler[ders_kodu]->sonraki,derse_girilirken_eklenen_ogr);//tek bagli dairesele baglanma
                        d_cift_sirali_ekle(&dersler[ders_kodu]->sonraki,derse_girilirken_eklenen_ogr);//cift bagli dairesele baglanma
                        ogrenci_ara_guncelle(&hash[hash1],ogrenci_no,ders_kredisi,derse_girilirken_eklenen_ogr->ogr_not,say[hash1]);
                        toplam_not=dersler[ders_kodu]->genel_not_ort*dersler[ders_kodu]->ogr_sayisi;
                        toplam_not=toplam_not+derse_girilirken_eklenen_ogr->ogr_not;
                        dersler[ders_kodu]->ogr_sayisi++;
                        dersler[ders_kodu]->genel_not_ort=(float)toplam_not/dersler[ders_kodu]->ogr_sayisi;
                    }
                    printf("Baska ogrenci bilgisi girerek devam etmek ister misiniz?(Evet E/e Hayir H/h)\n");
                    do
                    {
                        scanf("%c",&okunan_deger);
                        okunan_deger=getchar();
                    }
                    while(okunan_deger!='H' && okunan_deger!='h' && okunan_deger!='E' && okunan_deger!='e');
                }
                while(okunan_deger=='E' || okunan_deger=='e');
            }
            else
            {
                printf("Boyle bir ders mevcut degil!\n\n");
            }

            break;
        case 4:
            printf("Lutfen guncellemek istediginiz ders kodu icin ");
            ders_kodu=sayi_al(10,89);
            if(dersler[ders_kodu]!=NULL)
            {
                printf("lutfen notunu degistirmek istediginiz ogrecinin numarasi icin ");
                ogrenci_no=sayi_al(1,10000);
                hash1=(ogrenci_no-1)/100;
                yeni_not=derslerde_ogrenci_ara(&dersler[ders_kodu]->sonraki,ogrenci_no,&hash[hash1],dersler[ders_kodu]->kredi);
                if(yeni_not!=-1)//ogrenci varsa
                    dersler[ders_kodu]->genel_not_ort=((dersler[ders_kodu]->genel_not_ort*dersler[ders_kodu]->ogr_sayisi)+yeni_not)/dersler[ders_kodu]->ogr_sayisi;
            }
            break;
        case 5: ogrenci_sil(hash,dersler,say);
                break;
        case 6: dersten_listele(dersler,say,hash);
        break;
        case 7:
            ders_ogrencilerinden_not_ust_olanlari_listele(dersler,hash);
            break;
        case 8:
            ders_ogrencilerinden_not_alt_olanlari_listele(dersler,hash);
            break;
        case 9:
            printf("Lutfen derslerini goruntulemek istediginiz donem icin ");
            donem_no=sayi_al(1,8);
            printf("Ders Kodu  Ders Adi                   Kredi  Ogrenci Say  Not Ort\n");
            printf("---------  -------------------------  -----  -----------  -------\n");
            for(i=donem_no*10; i<(donem_no+1)*10; i++)//alt limit-ust limit arasý donuyor
            {
                if(dersler[i]!=NULL)
                {
                    printf("%-9d  %-25s  %-5d  %-11d  %-7.2f\n",dersler[i]->ders_kodu,dersler[i]->ders_adi,dersler[i]->kredi,dersler[i]->ogr_sayisi,dersler[i]->genel_not_ort);
                    kredi_say=kredi_say+dersler[i]->kredi;
                }
            }
            printf("Derslerin kredileri toplami :%d\n",kredi_say);
            break;

        case 10:
            printf("Lutfen goruntulemek istediginiz ogrencinin numarasi icin\n");
            ogrenci_no=sayi_al(1,10000);
            hash1=(ogrenci_no-1)/100;
            ogrenci_bilgileri_listele(hash[hash1],ogrenci_no);
            break;
        case 11:
            printf("Lutfen goruntulemek istediginiz ogrencinin numarasi icin\n");
            ogrenci_no=sayi_al(1,10000);
            hash1=(ogrenci_no-1)/100;
            ogrenci_bilgileri_listele(hash[hash1],ogrenci_no);
            printf("Aldigi dersler\n");
            printf("Ders Kodu  Ders Adi                   Kredi  Notu\n");
            printf("---------  -------------------------  -----  ----\n");
            for(i=10; i<90; i++)//dersler dizisinde donuluyor
            {
                if(dersler[i]!=NULL)//ders varsa
                {
                    if(dersler[i]->sonraki!=dersler[i]->sonraki->noya_gore_sonraki)
                    {
                        gecici=dersler[i]->sonraki;
                        do
                        {
                            if(dersler[i]->sonraki->ogr_no==ogrenci_no)
                                printf("%-9d  %-30s  %-5d  %-4d\n",dersler[i]->ders_kodu,dersler[i]->ders_adi,dersler[i]->kredi,dersler[i]->sonraki->ogr_not);
                            dersler[i]->sonraki=dersler[i]->sonraki->noya_gore_sonraki;
                        }
                        while(gecici!=dersler[i]->sonraki);
                    }
                }
            }
            break;
        case 12:
            sinifa_gore_listele(hash,say);
            break;
        }
    }
    while(secim!=13);
    return 0;
}

int sayi_al(int alt_sinir,int ust_sinir)//girilen aralik kontrol ediliyor
{
    int sayi;
    printf("%d - %d araliginda deger giriniz:\n",alt_sinir,ust_sinir);
    do
    {
        scanf("%d",&sayi);
        if(sayi<alt_sinir || sayi>ust_sinir)
            printf("Yanlis aralikta deger girdiniz!\n");
    }
    while(sayi<alt_sinir || sayi>ust_sinir);
    return sayi;
}

void ogrenci_ekle_sirali(struct ogrenci **ilk,struct ogrenci *yeni)//hash dizisine ogrenci ekliyor
{
    struct ogrenci *onceki ,*gecici;
    if(*ilk==NULL)//liste bossa
    {
        yeni->sonraki=NULL;
        *ilk=yeni;


    }
    else if((*ilk)->ogr_no > yeni->ogr_no)
    {
        yeni->sonraki=*ilk;
        *ilk=yeni;
    }
    else
    {
        onceki=*ilk;
        gecici=(*ilk)->sonraki;
        while(gecici!=NULL  && (gecici->ogr_no < yeni->ogr_no))
        {
            onceki=gecici;
            gecici=gecici->sonraki;
        }
        yeni->sonraki=gecici;
        onceki->sonraki=yeni;
    }
}

int  ogrenci_ara(struct ogrenci *liste_basi_ptr, int aranan_no,int hash1)//ogrenci listede bulunursa 1 dondurulur, bulunamazsa 0 dondurulur
{
    struct ogrenci *gecici;
    int bulundu=0;
    int i=0;
    gecici=liste_basi_ptr;
    if(gecici==NULL)
        bulundu=0;
    while (i<hash1)
    {
        if (gecici->ogr_no==aranan_no)
        {
            bulundu=1;
            break;
        }
        gecici=gecici->sonraki;
        i++;
    }
    return bulundu;
}

int donem_bul(struct ders *dersler[])
{
    int donem;
    int alt_sinir;
    int ust_sinir;
    int tutan_sayi;
    printf("\nLutfen eklemek istediginiz dersin donemi icin ");
    donem=sayi_al(1,8);
    alt_sinir=donem*10;
    ust_sinir=(donem+1)*10;
    while(alt_sinir<ust_sinir)//1 donemde ders kodu olabilecek tum sayilar taraniyor bosluk bulunup ataniyor
    {
        if(dersler[alt_sinir]==NULL)
        {
            tutan_sayi=alt_sinir;
            break;
        }
        alt_sinir++;
    }
    printf("Donem kodu:%d\n",tutan_sayi);
    return tutan_sayi;
}

void ders_ekle(struct ders **ilk_ptr, struct ders *yeni)//eklenmis derse head baglaniyor
{
    struct no_not *head;
    head=malloc(sizeof(struct no_not));
    head->noya_gore_sonraki=head;//head in ilklenmesi
    head->nota_gore_sonraki=head;
    head->nota_gore_onceki=head;
    yeni->sonraki=head;
    *ilk_ptr=yeni;
}

void d_cift_sirali_ekle(struct no_not **liste_basi_ptr, struct no_not *yeni)//cift bagli listeye eklenme yapilmasi
{
    struct no_not *gecici;

    gecici=(*liste_basi_ptr)->nota_gore_sonraki;
    while (gecici!=*liste_basi_ptr && gecici->ogr_not<yeni->ogr_not)
        gecici=gecici->nota_gore_sonraki;

    yeni->nota_gore_sonraki=gecici;
    yeni->nota_gore_onceki=gecici->nota_gore_onceki;
    gecici->nota_gore_onceki->nota_gore_sonraki=yeni;
    gecici->nota_gore_onceki=yeni;
}

void dairesel_sirali_ekle(struct no_not **liste_basi_ptr, struct no_not *yeni)//tek bagli dairesel listeye eklenme
{
    struct no_not *onceki, *gecici;

    onceki=*liste_basi_ptr;
    gecici=(*liste_basi_ptr)->noya_gore_sonraki;
    while(gecici!=*liste_basi_ptr && gecici->ogr_no<yeni->ogr_no)
    {
        onceki=gecici;
        gecici=gecici->noya_gore_sonraki;
    }

    yeni->noya_gore_sonraki=gecici;
    onceki->noya_gore_sonraki=yeni;
}

void ogrenci_bilgileri_listele(struct ogrenci *liste_basi_ptr, int aranan_no)
{
    struct ogrenci *gecici;
    int bulundu=0;
    gecici=liste_basi_ptr;
    while (gecici!=NULL)//boyle bir ogrenci varsa donme
    {
        if (gecici->ogr_no==aranan_no)
        {
            printf("Ogrenci Bilgileri:\n");
            printf("Ogr No  Ad Soyad                        Sinif  Kredi Say  Not Ort\n");
            printf("------  ------------------------------  -----  ---------  -------\n");
            printf("%-6d  %-30s  %-5d  %-9d  %-7.2f\n",gecici->ogr_no,gecici->ad_soyad,gecici->sinif,gecici->kredi,gecici->not_ortalamasi);
            bulundu=1;
            break;
        }
        gecici=gecici->sonraki;
    }
    if(bulundu==0)
        printf("Boyle bir ogrenci yok!\n");
}

void ogrenci_ara_guncelle(struct ogrenci **liste_basi_ptr, int aranan_no, int kredi, int note,int hash1)
{
    struct ogrenci *gecici;
    int not_toplam;
    int i=0;
    gecici=*liste_basi_ptr;
    while (i<hash1)//hash dizisinde bagli eleman kadar donuluyor
    {
        if (gecici->ogr_no==aranan_no)
        {
            break;
        }
        gecici=gecici->sonraki;
        i++;
    }
    not_toplam=gecici->not_ortalamasi*gecici->kredi + note*kredi;
    gecici->kredi=kredi+gecici->kredi;//kredi ve notlar guncelleniyor
    gecici->not_ortalamasi=(float)not_toplam/gecici->kredi;
}

int derslerde_ogrenci_ara(struct no_not **liste_basi_ptr,int aranan_no,struct ogrenci **head,int kredi)
{
    struct no_not *gecici;
    struct ogrenci *oteki_gecici;
    int ogrenci_not;
    int bulundu=0;
    int eski_not=101;
    int debug;
    int debug1;
    gecici=*liste_basi_ptr;

    do
    {//listede donuyoruz en basa varana kadar
        if(gecici->ogr_no==aranan_no)
        {
            printf("Lutfen bu ogrencinin yeni notu icin ");
            ogrenci_not=sayi_al(1,100);
            eski_not=gecici->ogr_not;
            gecici->ogr_not=ogrenci_not;
            bulundu=1;

            oteki_gecici=*head;
            debug1=oteki_gecici->ogr_no;

            debug=oteki_gecici->ogr_no;
            if(debug==aranan_no)
            {
                oteki_gecici->not_ortalamasi=(oteki_gecici->not_ortalamasi*oteki_gecici->kredi - eski_not*kredi+ogrenci_not*kredi)/oteki_gecici->kredi;
                d_cift_baglidan_dugum_cikar(gecici);//once ogrenciyi listeden cikar (ama yok etme)
                d_cift_sirali_ekle(liste_basi_ptr,gecici);//sonra ogrenciyi tekrar listenin uygun yerine ekle
                break;
            }
            do
            {
                oteki_gecici=oteki_gecici->sonraki;
                debug=oteki_gecici->ogr_no;
                if(debug==aranan_no)
                {
                    oteki_gecici->not_ortalamasi=(oteki_gecici->not_ortalamasi*oteki_gecici->kredi - eski_not*kredi+ogrenci_not*kredi)/oteki_gecici->kredi;
                    d_cift_baglidan_dugum_cikar(gecici);//once ogrenciyi listeden cikar (ama yok etme)
                    d_cift_sirali_ekle(liste_basi_ptr,gecici);//sonra ogrenciyi tekrar listenin uygun yerine ekle
                    break;
                }
            }
            while (oteki_gecici->ogr_no!=aranan_no);
            break;
        }
        gecici=gecici->noya_gore_sonraki;
    }
    while(*liste_basi_ptr!=gecici);
    if(bulundu==0)
    {
        printf("Bu ogrenci bu dersi almiyor!\n");
        return -1;
    }
    else if(eski_not<=100)
        return (float)ogrenci_not-eski_not;

}
void d_cift_baglidan_dugum_cikar(struct no_not *cikarilacak)//adresi verilen dugumu listeden cikarir ama yok etmez
{
    cikarilacak->nota_gore_onceki->nota_gore_sonraki=cikarilacak->nota_gore_sonraki;
    cikarilacak->nota_gore_sonraki->nota_gore_onceki=cikarilacak->nota_gore_onceki;
}
void sinifa_gore_listele(struct ogrenci *hash[],int say[])
{
    int i,j=0;
    int yil_no;
    int ogrenci_sayisi=0;
    int not_toplam=0;
    int atmis_alti_say=0;
    struct ogrenci *gecici;
    printf("Lutfen goruntulemek istediginiz sinif icin ");
    yil_no=sayi_al(1,4);
    printf("Ogr No  Ad Soyad                        Sinif  Kredi Say  Not Ort\n");
    printf("------  ------------------------------  -----  ---------  -------\n");
    for(i=0; i<100; i++)//hash dizisi bastan sona gidiliyor
    {
        if(hash[i]!=NULL)//o hash degerinde ogrenci olup olmadigi kontrol ediliyor
        {
            gecici=hash[i];
            j=0;
            while(j<say[i])//o hash degerindeki ogrenci sayisi kadar donuluyor
            {
                if(gecici->sinif==yil_no)
                {
                    printf("%-6d  %-30s  %-5d  %-9d  %-7.2f\n",gecici->ogr_no,gecici->ad_soyad,gecici->sinif,gecici->kredi,gecici->not_ortalamasi);
                    not_toplam=gecici->not_ortalamasi+not_toplam;
                    ogrenci_sayisi++;

                    if(gecici->not_ortalamasi<60)
                        atmis_alti_say++;

                }

                gecici=gecici->sonraki;
                j++;

            }
        }
    }
    printf("Ogrenci sayisi: %d\n",ogrenci_sayisi);
    if(ogrenci_sayisi!=0)
    {
        printf("Not ortalamasi :%.2f\n",(float)not_toplam/ogrenci_sayisi);
        printf("Not ortalamasi 60'in altinda olan ogrenci sayisi ve yuzdesi: %d   %.2f\n",atmis_alti_say,(float)atmis_alti_say*100/ogrenci_sayisi);
    }
    else
    {
        printf("Not ortalamasi :0\n");
        printf("Not ortalamasi 60'in altinda olan ogrenci sayisi ve yuzdesi: 0 ve 0\n");
    }
}
void dersten_listele(struct ders *dersler[],int say[],struct ogrenci *hash[])
{
    int ders_kodu;
    struct no_not *gecici;
    struct ogrenci *diger_gecici;
    int j=0;
    int i;
    printf("Lutfen ders kodunu icin ");
    ders_kodu=sayi_al(10,89);

    if(dersler[ders_kodu]!=NULL)//boyle bir ders olup olmadigi kontrol ediliyor
    {
        printf("Ders Kodu  Ders Adi                   Kredi  Ogrenci Say  Not Ort\n");
        printf("---------  -------------------------  -----  -----------  -------\n");
        printf("%-9d  %-25s  %-5d  %-11d  %-7.2f \n",dersler[ders_kodu]->ders_kodu,dersler[ders_kodu]->ders_adi,dersler[ders_kodu]->kredi,dersler[ders_kodu]->ogr_sayisi,dersler[ders_kodu]->genel_not_ort);
        gecici=dersler[ders_kodu]->sonraki;
        if(dersler[ders_kodu]->sonraki!=NULL)
        {
            printf("Ogr No  Ad Soyad                        Sinif  Notu\n");
            printf("------  ------------------------------  -----  ----\n");
            for(i=0; i<100; i++)//hash dizisinde o ogrenciyi bulmak icin
            {
                j=0;
                if(hash[i]!=NULL)
                {
                    diger_gecici=hash[i];
                    while(j<say[i])
                    {
                        if(diger_gecici->ogr_no==dersler[ders_kodu]->sonraki->ogr_no)
                        {
                            printf("%-6d  %-30s  %-5d  %-4d\n",dersler[ders_kodu]->sonraki->ogr_no,diger_gecici->ad_soyad,diger_gecici->sinif,dersler[ders_kodu]->sonraki->ogr_not);
                        }
                        diger_gecici=diger_gecici->sonraki;
                        j++;

                    }
                }
            }
        }
        dersler[ders_kodu]->sonraki=dersler[ders_kodu]->sonraki->noya_gore_sonraki;
        while(gecici!=dersler[ders_kodu]->sonraki)
        {
            j=0;

            for(i=0; i<100; i++)//hash dizisinde o ogrenciyi bulmak icin
            {
                j=0;
                if(hash[i]!=NULL)
                {
                    diger_gecici=hash[i];
                    while(j<say[i])
                    {
                        if(diger_gecici->ogr_no==dersler[ders_kodu]->sonraki->ogr_no)
                        {
                            printf("%-6d  %-30s  %-5d  %-4d\n",dersler[ders_kodu]->sonraki->ogr_no,diger_gecici->ad_soyad,diger_gecici->sinif,dersler[ders_kodu]->sonraki->ogr_not);
                        }
                        diger_gecici=diger_gecici->sonraki;
                        j++;

                    }
                }
            }
        dersler[ders_kodu]->sonraki=dersler[ders_kodu]->sonraki->noya_gore_sonraki;
        }
    }
    else
    printf("Boyle bir ders acilmamistir!\n");
}

void ders_ogrencilerinden_not_ust_olanlari_listele(struct ders *dersler[],struct ogrenci *hash[]){
    int ders_kodu, baraj_not, hashx;
    struct no_not *head,*oncekieleman;
    struct ogrenci *ara_deger;
    int  limit_say=0;
    printf("Lutfen islem yapmak istediginiz dersin kodu icin\n");
    ders_kodu=sayi_al(10,89);
    if(dersler[ders_kodu]!=NULL){//boyle bir ders vars
            head=dersler[ders_kodu]->sonraki;
            oncekieleman=head->nota_gore_onceki;
            printf("Lutfen not baraji icin ");
            baraj_not=sayi_al(0,100);
            if(head->nota_gore_onceki->ogr_not>baraj_not){
                printf("Notu Yuksek Olan Ogrenciler:\n");
                printf("Ogr No  Ad Soyad                        Sinif  Notu\n");
                printf("------  ------------------------------  -----  ----\n");
                while(oncekieleman!=head){ //oncekinin head olma/onu gorme sarti
                    if(oncekieleman->ogr_not>baraj_not){ //Not baraj notundan buyukse
                        hashx=((oncekieleman->ogr_no)-1)/100;
                        ara_deger=hash[hashx];
                        if(ara_deger->ogr_no==oncekieleman->ogr_no){
                                printf("%-6d  %-30s  %-5d  %-4d\n",oncekieleman->ogr_no,ara_deger->ad_soyad,ara_deger->sinif,oncekieleman->ogr_not);
                                limit_say++;//istatistik icin sayiliyor
                            }
                        while(ara_deger->ogr_no!=oncekieleman->ogr_no){
                            ara_deger=ara_deger->sonraki;
                            if(ara_deger->ogr_no==oncekieleman->ogr_no){
                                printf("%-6d  %-30s  %-5d  %-4d\n",oncekieleman->ogr_no,ara_deger->ad_soyad,ara_deger->sinif,oncekieleman->ogr_not);
                                limit_say++;//istatistik icin sayiliyor
                            }
                        }
                    }
                    else
                        break;
                    oncekieleman=oncekieleman->nota_gore_onceki;
                }
                 printf("notu %d'nin uzerinde olan ogrenci sayisi:%d ve yuzdesi:%.2f\n",baraj_not,limit_say,(float)limit_say*100/dersler[ders_kodu]->ogr_sayisi);
            }

            else
                printf("%d baraj notundan daha buyuk bir ogrenci notu bulunamadi!\n",baraj_not);
    }
    else
        printf("Boyle bir ders bulunamadi!\n");
}

void ders_ogrencilerinden_not_alt_olanlari_listele(struct ders *dersler[],struct ogrenci *hash[]){
    int ders_kodu, baraj_not, hashx, limit_say=0;
    struct no_not *head,*sonrakieleman;
    struct ogrenci *ara_deger;
    printf("Lutfen islem yapmak istediginiz dersin kodu icin\n");
    ders_kodu=sayi_al(10,89);
    if(dersler[ders_kodu]!=NULL){//boyle bir ders varsa
            head=dersler[ders_kodu]->sonraki;
            sonrakieleman=head->nota_gore_sonraki;
            printf("Lutfen not baraji icin ");
            baraj_not=sayi_al(0,100);
            if(head->nota_gore_sonraki->ogr_not<baraj_not){
                printf("Notu Dusuk Olan Ogrenciler:\n");
                printf("Ogr No  Ad Soyad                        Sinif  Notu\n");
                printf("------  ------------------------------  -----  ----\n");
                while(sonrakieleman!=head){ //sonrakinin head olma/onu gorme sarti
                    if(sonrakieleman->ogr_not<baraj_not){ //Not baraj notundan kucukse
                        hashx=((sonrakieleman->ogr_no)-1)/100;
                        ara_deger=hash[hashx];
                        if(ara_deger->ogr_no==sonrakieleman->ogr_no){
                                printf("%-6d  %-30s  %-5d  %-4d\n",sonrakieleman->ogr_no,ara_deger->ad_soyad,ara_deger->sinif,sonrakieleman->ogr_not);
                                limit_say++;
                            }
                        while(ara_deger->ogr_no!=sonrakieleman->ogr_no){
                            ara_deger=ara_deger->sonraki;
                            if(ara_deger->ogr_no==sonrakieleman->ogr_no){
                                printf("%-6d  %-30s  %-5d  %-4d\n",sonrakieleman->ogr_no,ara_deger->ad_soyad,ara_deger->sinif,sonrakieleman->ogr_not);
                                limit_say++;
                            }
                        }
                    }
                    else
                        break;
                    sonrakieleman=sonrakieleman->nota_gore_sonraki;
                }
                printf("notu %d'nin altinda olan ogrenci sayisi:%d ve yuzdesi:%.2f\n",baraj_not,limit_say,(float)limit_say*100/dersler[ders_kodu]->ogr_sayisi);
            }
            else
                printf("%d baraj notundan daha kucuk bir ogrenci notu bulunamadi!\n",baraj_not);
    }
    else
        printf("Boyle bir ders bulunamadi!\n");
}
void ogrenci_sil(struct ogrenci *hash[],struct ders *dersler[],int say[])
{
    int ogrenci_no;
    int hash1;
    int dongu_say;
    struct ogrenci *silinecek;
    printf("Lutfen ogrenci numarasi icin ");
    ogrenci_no=sayi_al(1,10000);
    hash1=(ogrenci_no-1)/100;
    dongu_say=say[hash1];
    if(ogrenci_ara(hash[hash1],ogrenci_no,dongu_say)==1){//boyle bir ogrenci varsa
        silinecek=sil_gitsin(&hash[hash1],ogrenci_no);
        if(silinecek!=NULL)
            say[hash1]--;
        free(silinecek);//dugum yok ediliyor
        dersten_ogrenci_sil(dersler,ogrenci_no);
    }
    else
        printf("Boyle bir ogrenci yok\n");
}

struct ogrenci *sil_gitsin(struct ogrenci **liste_basi_ptr, int silinecek)//silinecek deger gonderiliyor baglar kuruluyor
{
    struct ogrenci *onceki, *gecici;

    onceki=*liste_basi_ptr;
    gecici=(*liste_basi_ptr)->sonraki;
    if(onceki->ogr_no==silinecek){//hash dizisinin o elemaninda ilk dugum silinecekse
    *liste_basi_ptr=gecici;
    return onceki;
    }
    else{
    while(gecici!=*liste_basi_ptr && gecici->ogr_no != silinecek)
    {
        onceki=gecici;
        gecici=gecici->sonraki;
    }

    if(gecici==*liste_basi_ptr)
        return NULL;//ogrenci yoksa NULL dondur
    else {//ogrenci varsa
        onceki->sonraki=gecici->sonraki;//ogrenci koduna gore olan listeden cikar ama yok etme
        return gecici;//ve cikarilanin isaretcisini dondur
    }
    }
}

void dersten_ogrenci_sil(struct ders **dersler,int silinecek){
    struct no_not *onceki,*gecici,*liste_basi_ptr;
    int i;
    int degisti=0;
    int silinen_not;

    for(i=10;i<90;i++)//dersler taraniyor
    {
        degisti=0;
        if(dersler[i]!=NULL)//boyle bir ders varsa
        {
            liste_basi_ptr=dersler[i]->sonraki;
            onceki=liste_basi_ptr;
            gecici=liste_basi_ptr->noya_gore_sonraki;
            while(gecici!=liste_basi_ptr && gecici->ogr_no < silinecek){
                onceki=gecici;
                gecici=gecici->noya_gore_sonraki;
            }
            if(gecici!=liste_basi_ptr){
                onceki->noya_gore_sonraki=gecici->noya_gore_sonraki;
                gecici->nota_gore_onceki->nota_gore_sonraki=gecici->nota_gore_sonraki;
                gecici->nota_gore_sonraki->nota_gore_onceki=gecici->nota_gore_onceki;
                degisti=1;
                silinen_not=gecici->ogr_not;
            }
            //degisikligin neden oldugu seyler bu satirda degiscek
             if(degisti==1)
             {
               dersler[i]->genel_not_ort=(float)(dersler[i]->genel_not_ort*dersler[i]->ogr_sayisi-silinen_not)/(dersler[i]->ogr_sayisi-1);
                 dersler[i]->ogr_sayisi--;
            free(gecici);
             }
        }
        else
            break;
    }
}
