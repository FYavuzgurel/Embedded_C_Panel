#include <main.h>
#use delay(clock=4000000)
#define LCD_RS_PIN PIN_D0
#define LCD_RW_PIN PIN_D1
#define LCD_ENABLE_PIN PIN_D2
#define LCD_DATA4 PIN_D3
#define LCD_DATA5 PIN_D4
#define LCD_DATA6 PIN_D5
#define LCD_DATA7 PIN_D6
#fuses XT,NOWDT,NOPROTECT,NOBROWNOUT,NOLVP,NOPUT,NOWRT,NODEBUG,NOCPD
#include<lcd.c>
#use fast_io(b)
#use fast_io(d)

#use rs232(baud=9600, xmit=pin_c6, rcv=pin_c7, parity=N, stop=1)
char sifre[131]={};
int gunler(void);
void pazartesi1(int a);void sali1(int a);
void carsamba1(int a);void persembe1(int a);
void cuma1(int a);void cumartesi1(int a);void pazar1(int a);

void pazartesi2(int a);void sali2(int a);
void carsamba2(int a);void persembe2(int a);
void cuma2(int a);void cumartesi2(int a);void pazar2(int a);
void gun(int k);
void clock2 (int k);
void kontrol(void);
void sifreleme(int v,int z );
void clock (int k);
char harf(int e);


char dene[1];
int zaman[2]={},bugun[2]={};
int ptesibas[2]={};int ptesibit[2]={};   //0.deger saat / 1.deger dakika
int salibas[2]={};int salibit[2]={};
int carbas[2]={};int carbit[2]={};
int perbas[2]={};int perbit[2]={};
int cumabas[2]={};int cumabit[2]={};
int ctesibas[2]={};int ctesibit[2]={};
int pazarbas[2]={};int pazarbit[2]={};

int ptesibas2[2]={};int ptesibit2[2]={};   //0.deger saat / 1.deger dakika
int salibas2[2]={};int salibit2[2]={};
int carbas2[2]={};int carbit2[2]={};
int perbas2[2]={};int perbit2[2]={};
int cumabas2[2]={};int cumabit2[2]={};
int ctesibas2[2]={};int ctesibit2[2]={};
int pazarbas2[2]={};int pazarbit2[2]={};


int key1,key2,key3,key4,key5,key6,key7,key8,key9,key10,key11,key12,key13,key14;
signed int i;
int j;
int saat=12,saat1=12;
int dakika=0,dakika1=0;
char c1,c2;
int f=0;
int yan;
int t=1;


void main()
{
   port_b_pullups(TRUE);
   // setup_psp(PSP_DISABLED);
   setup_adc_ports(NO_ANALOGS);
   setup_adc(ADC_OFF);
   setup_CCP1(CCP_OFF);
   setup_CCP2(CCP_OFF);   
   set_tris_b(0xFF);
   output_b(0X00);
   set_tris_d(0x00);
   output_d(0X00);
   disable_interrupts(GLOBAL);
   lcd_init();
   i=0;
while(TRUE)
{
   if(input(pin_b3)==0)//                    GUNLERI YUKARI SAY BUTONU
   {  
      delay_ms(20);
      while(input(pin_b3)==0);
      i++;
      if(i==9)
      {i=1;}
   }
   if(input(pin_b4)==0)//                    GUNLERI ASAGI SAY BUTONU
   {
      delay_ms(20);
      while(input(pin_b4)==0);
      i--;
      if(i==0)
      {i=8;}
      if(i<0)
      {i=0;}
   }

   if(i==0)//                             ILK ACILIS EKRANI                                     
   {
      printf(lcd_putc,"\f");
      lcd_gotoxy(6,1);//LCD belirtilen satýr ve sütuna git komutu
      printf(lcd_putc,"NEHIR AIR");
      delay_ms(100);
   }
  
//************************************************* PAZARTESI  MAIN FONKSIYONU*******************************************      
   if(i==1)//                            PAZARTESI 1 DEGERI
   {     
      if(f==0)//                          PAZARTESI 1 FONKSIYONUNA GIRISI
      {
         lcd_gotoxy(4,1);//LCD belirtilen satýr ve sütuna git komutu
         printf(lcd_putc,"\f PAZARTESI");
         delay_ms(100);
      }
         
      if(input(pin_b5)==0)//OKEY VERILIRSE PAZARTESI 1  AYARLARINA GIR
      {   
         delay_ms(20);
         while(input(pin_b5)==0);
         pazartesi1(0);//******************************** PAZARTESI 1  FONKSIYONU CAGRILIR 
         
         if(ptesibas[0]>=ptesibit[0])// baslangýç saatibitiþ saatinden büyükse ertesi güne sarkar
         {
            sali2(0);
            sifreleme(4,1);
         }
         else
         {
            sifreleme(4,0);// SALI 2 GUNU KAPALI SIFRELEME-SOL GUN KODU-SAG ACIK/KAPALI KODU
            delay_ms(20);
         }           
         delay_ms(100); 
      }
         
      if(f==1)//                        PAZARTESI 1 FONKSIYONUNDAN CIKISI                
      {  
         sifreleme(1,1);//ilk deger gün kodu 2. deger acýk/kapalý kodu, 0 kapalý/1 acik
         f=0;
         i=2;  
      } 
   }
               
//************************************************* SALI  MAIN FONKSIYONU*******************************************      
      
   if(i==2)//                            SALI 1 DEGERI
   {     
      if(f==0)//                          SALI 1 FONKSIYONUNA GIRISI
      {
         lcd_gotoxy(4,1);//LCD belirtilen satýr ve sütuna git komutu
         printf(lcd_putc,"\f SALI");
         delay_ms(100);
      }
         
      if(input(pin_b5)==0)//OKEY VERILIRSE SALI 1  AYARLARINA GIR
      {   
         delay_ms(20);
         while(input(pin_b5)==0);
         sali1(0);//******************************** SALI 1  FONKSIYONU CAGRILIR 

         if(salibas[0]>=salibit[0])// baslangýç saatibitiþ saatinden büyükse ertesi güne sarkar
         {
            carsamba2(0);
            sifreleme(6,1);
         }
         else
         {
            sifreleme(6,0);// CARSAMBA 2 GUNU KAPALI SIFRELEME-SOL GUN KODU-SAG ACIK/KAPALI KODU
            delay_ms(20);
         }           
         delay_ms(100); 
      }
         
      if(f==1)//                        SALI 1 FONKSIYONUNDAN CIKISI                
      {  
         sifreleme(3,1);//ilk deger gün kodu 2. deger acýk/kapalý kodu, 0 kapalý/1 acik
         f=0;
         i=3;  
      }   
   }  
     
//************************************************* CARSAMBA  MAIN FONKSIYONU*******************************************      
      
   if(i==3)//                            CARSAMBA 1 DEGERI
   {   
      if(f==0)//                          CARSAMBA 1 FONKSIYONUNA GIRISI
      {
         lcd_gotoxy(4,1);//LCD belirtilen satýr ve sütuna git komutu
         printf(lcd_putc,"\f CARSAMBA");
         delay_ms(100);
      }
         
      if(input(pin_b5)==0)//OKEY VERILIRSE CARSAMBA 1  AYARLARINA GIR
      {   
         delay_ms(20);
         while(input(pin_b5)==0);
         carsamba1(0);//******************************** CARSAMBA 1  FONKSIYONU CAGRILIR 
            
         if(carbas[0]>=carbit[0])// baslangýç saatibitiþ saatinden büyükse ertesi güne sarkar
         {
            persembe2(0);
            sifreleme(8,1);
         }
         else
         {
            sifreleme(8,0);// PERSEMBE 2 GUNU KAPALI SIFRELEME-SOL GUN KODU-SAG ACIK/KAPALI KODU
            delay_ms(20);
         }           
            delay_ms(100); 
      }
         
      if(f==1)//                        CARSAMBA 1 FONKSIYONUNDAN CIKISI                
      {  
         sifreleme(5,1);//ilk deger gün kodu 2. deger acýk/kapalý kodu, 0 kapalý/1 acik
         f=0;
         i=4;  
      }   
   }  
                
//************************************************* PERSEMBE  MAIN FONKSIYONU*******************************************      
      
   if(i==4)//                            PERSEMBE 1  DEGERI
   {   
      if(f==0)//                          PERSEMBE 1  FONKSIYONUNA GIRISI
      {
         lcd_gotoxy(4,1);//LCD belirtilen satýr ve sütuna git komutu
         printf(lcd_putc,"\f PERSEMBE ");
         delay_ms(100);
      }
         
      if(input(pin_b5)==0)//OKEY VERILIRSE CARSAMBA 1  AYARLARINA GIR
      {   
         delay_ms(20);
         while(input(pin_b5)==0);
         persembe1(0);//******************************** CARSAMBA 1  FONKSIYONU CAGRILIR 
         
         if(perbas[0]>=perbit[0])// baslangýç saatibitiþ saatinden büyükse ertesi güne sarkar
         {
            cuma2(0);
            sifreleme(10,1);
         }
         else
         {
            sifreleme(10,0);// CUMA 2 GUNU KAPALI SIFRELEME-SOL GUN KODU-SAG ACIK/KAPALI KODU
            delay_ms(20);
         }           
            delay_ms(100); 
      }
         
      if(f==1)//                        PERSEMBE 1  FONKSIYONUNDAN CIKISI                
      {  
         sifreleme(7,1);//ilk deger gün kodu 2. deger acýk/kapalý kodu, 0 kapalý/1 acik
         f=0;
         i=5;  
      }  
   }  
         
//************************************************* CUMA  MAIN FONKSIYONU*******************************************
      
   if(i==5)//                            CUMA 1  DEGERI
   {  
      if(f==0)//                          CUMA 1  FONKSIYONUNA GIRISI
      {
         lcd_gotoxy(4,1);//LCD belirtilen satýr ve sütuna git komutu
         printf(lcd_putc,"\f CUMA ");
         delay_ms(100);
      }
         
      if(input(pin_b5)==0)//OKEY VERILIRSE CARSAMBA 1  AYARLARINA GIR
      {   
         delay_ms(20);
         while(input(pin_b5)==0);
         cuma1(0);//******************************** CARSAMBA 1  FONKSIYONU CAGRILIR 
         
         if(cumabas[0]>=cumabit[0])// baslangýç saatibitiþ saatinden büyükse ertesi güne sarkar
         {
            cumartesi2(0);
            sifreleme(12,1);
         }
         else
         {
            sifreleme(12,0);// CUMARTESI 2 GUNU KAPALI SIFRELEME-SOL GUN KODU-SAG ACIK/KAPALI KODU
            delay_ms(20);
         }           
          delay_ms(100); 
      }
      
      if(f==1)//                        CUMA 1  FONKSIYONUNDAN CIKISI                
      {  
         sifreleme(9,1);//ilk deger gün kodu 2. deger acýk/kapalý kodu, 0 kapalý/1 acik
         f=0;
         i=6;  
      }    
   } 
            
//************************************************* CUMARTESI  MAIN FONKSIYONU*******************************************
      
   if(i==6)//                            CUMARTESI 1  DEGERI
   {  
      if(f==0)//                          CUMARTESI 1  FONKSIYONUNA GIRISI
      {
         lcd_gotoxy(4,1);//LCD belirtilen satýr ve sütuna git komutu
         printf(lcd_putc,"\f CUMARTESI ");
         delay_ms(100);
      }
         
      if(input(pin_b5)==0)//OKEY VERILIRSE CARSAMBA 1  AYARLARINA GIR
      {   
         delay_ms(20);
         while(input(pin_b5)==0);
         cumartesi1(0);//******************************** CARSAMBA 1  FONKSIYONU CAGRILIR 
         
         if(ctesibas[0]>=ctesibit[0])// baslangýç saatibitiþ saatinden büyükse ertesi güne sarkar
         {
            pazar2(0);
            sifreleme(14,1);
         }
         else
         {
            sifreleme(14,0);// PAZAR 2 GUNU KAPALI SIFRELEME-SOL GUN KODU-SAG ACIK/KAPALI KODU
            delay_ms(20);
         }           
         delay_ms(100); 
      }
         
      if(f==1)//                        CUMARTESI 1  FONKSIYONUNDAN CIKISI                
      {  
         sifreleme(11,1);//ilk deger gün kodu 2. deger acýk/kapalý kodu, 0 kapalý/1 acik
         f=0;
         i=7;  
      }   
   } 
            
//************************************************* PAZAR  MAIN FONKSIYONU*******************************************
      
   if(i==7)//                            PAZAR 1  DEGERI
   {   
      if(f==0)//                          PAZAR 1  FONKSIYONUNA GIRISI
      {
         lcd_gotoxy(4,1);//LCD belirtilen satýr ve sütuna git komutu
         printf(lcd_putc,"\f PAZAR  ");
         delay_ms(100);
      }
         
      if(input(pin_b5)==0)//OKEY VERILIRSE PAZAR 1  AYARLARINA GIR
      {   
         delay_ms(20);
         while(input(pin_b5)==0);
         pazar1(0);//******************************** PAZAR 1  FONKSIYONU CAGRILIR 

         if(pazarbas[0]>=pazarbit[0])// baslangýç saatibitiþ saatinden büyükse ertesi güne sarkar
         {
            pazartesi2(0);
            sifreleme(2,1);
         }
         else
         {
            sifreleme(2,0);// PAZARTESI 2 GUNU KAPALI SIFRELEME-SOL GUN KODU-SAG ACIK/KAPALI KODU
            delay_ms(20);
         }           
         delay_ms(100); 
      }
         
      if(f==1)//                        PAZAR 1  FONKSIYONUNDAN CIKISI                
      {  
         sifreleme(13,1);//ilk deger gün kodu 2. deger acýk/kapalý kodu, 0 kapalý/1 acik
         f=0;
         i=8;  
      }    
   } 
       
//  *************************************************** GUN - SAAT AYARI ***************************************************************
   
   if(i==8)
   {
      if(f==0)//                          GUN - SAAT AYARI  FONKSIYONUNA GIRISI
      {
         printf(lcd_putc,"\f");
         lcd_gotoxy(6,1);//LCD belirtilen satýr ve sütuna git komutu
         printf(lcd_putc,"GUN AYARI");
         delay_ms(100);
      }
     
     if(input(pin_b5)==0)//OKEY VERILIRSE GUN  AYARLARINA GIR
      {   
         delay_ms(20);
         while(input(pin_b5)==0);
         gun(0);
      }
      
     if(f==1)
     {
         printf(lcd_putc,"\f");
         lcd_gotoxy(3,1);//LCD belirtilen satýr ve sütuna git komutu
         printf(lcd_putc,"SAAT AYARI");
         delay_ms(100);
         clock2(0);
         
         for(int x=0;x<2;x++)
         {
            bugun[x]=zaman[x];
         }
         sifreleme(15,1);
         
         f=0;
         i=9;
     } 
   }
   
   if(i==9)// SIFREYI GONDER BUTONU
   {    
      printf(lcd_putc,"\f");
      lcd_gotoxy(6,1);//LCD belirtilen satýr ve sütuna git komutu
      printf(lcd_putc,"GONDER");
      delay_ms(100);
      if(input(pin_b0)==0)//GONDER BUTONU
      {  
         delay_ms(20);
         while(input(pin_b1)==0);
         kontrol();
         printf(lcd_putc,"\f");
         lcd_gotoxy(2,1);//LCD belirtilen satýr ve sütuna git komutu
         printf(lcd_putc,"GONDERILIYOR");
         delay_ms(20);
         while(input(pin_b0)==0);
         for(int data=0;data<131;data++)
         {
            putc(sifre[data]);
            delay_ms(60);
         }
         printf(lcd_putc,"\f");
         lcd_gotoxy(3,1);//LCD belirtilen satýr ve sütuna git komutu
         printf(lcd_putc,"GONDERILDI");
         delay_ms(600);
         key1=0,key2=0,key3=0,key4=0,key5=0,key6=0,key7=0,key8=0,key9=0,key10=0,key11=0,key12=0,key13=0,key14=0;
         i=0;//GUNLER KISMINA GERI DONER
      }    
   }  
}
}    // MAIN FONKSIYONU
 

//******************************************************************************************** PAZARTESI 1 FONKSIYONU***************************************************************************

void pazartesi1(int a)
{  
   while(a==0)///////////////////BU FONKSIYNA GIRIYOR ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
   {  
      lcd_gotoxy(3,2);//LCD belirtilen satýr ve sütuna git komutu
      printf(lcd_putc,"ACIK/KAPALI");
      delay_ms(100);

      if(input(pin_a0)==0)//ACIK BUTONUNA BASILINCA++++++++++++++++++++++++++++++++++++++++++++++++++++++++
      {  
         delay_ms(20);
         while(input(pin_a0)==0);
      
         key1=1;
         printf(lcd_putc,"\f");
         lcd_gotoxy(4,1);//LCD belirtilen satýr ve sütuna git komutu
         printf(lcd_putc,"PAZARTESI");
         
         lcd_gotoxy(6,2);//LCD belirtilen satýr ve sütuna git komutu
         printf(lcd_putc,"ACIK");         
         delay_ms(700);
         
         printf(lcd_putc,"\f");// \f komutu ile LCD silinir
         lcd_gotoxy(1,1);//LCD belirtilen satýr ve sütuna git komutu
         printf(lcd_putc,"BASLANGIC SAATI");
         delay_ms(5);
         
         //**************************************** CLOCK 1
         
         clock (0);//BASLANGIC SAATI ICIN GONDERILDI
         delay_ms(300);
         
         for(int x=0;x<2;x++)//baslangýc saatý genel dýzýden aktarýlýyor
         {
            ptesibas[x]=zaman[x];//pazartesi baslangic degerleri kaydedildi
         }
           
         lcd_gotoxy(1,1);//LCD belirtilen satýr ve sütuna git komutu
         printf(lcd_putc,"\f BITIS SAATI");
         delay_ms(20);
         
         //***************************************** CLOCK 2
         
         clock (0);//BITIS SAATI ICIN GONDERILDI

         for(int y=0;y<2;y++)//baslangýc saatý genel diziden aktarýlýyor
         {
            ptesibit[y]=zaman[y];//pazartesi bitis degerleri kaydedildi
         }  

           a=1;
           f=1;   
      } 
      
      if(input(pin_a1)==0)//KAPALI BUTONUNA BASILINCA 
      {
         delay_ms(20);
         while(input(pin_a1)==0);
         
         key1=0;
         printf(lcd_putc,"\f");
         lcd_gotoxy(1,2);//LCD belirtilen satýr ve sütuna git komutu
         printf(lcd_putc,"KAPALI");
         delay_ms(500);
         sifreleme(1,0);// PAZARTESI 1 GUNU KAPALI SIFRELEME-SOL GUN KODU-SAG ACIK/KAPALI KODU
         delay_ms(20);
         a=1;
         i=2;
         f=0;
      }
   }
}

//******************************************************************************************** PAZARTESI 2 FONKSIYONU***************************************************************************
void pazartesi2(int a)
{  
   while(a==0)///////////////////BU FONKSIYNA GIRIYOR ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
   {  
      ptesibit2[0]=pazarbit[0];
      ptesibit2[1]=pazarbit[1];
      pazarbit[0]=23;
      pazarbit[1]=59;
      ptesibas2[0]=0;
      ptesibas2[1]=0;
      a=1;  
   }
}

//******************************************************************************************** SALI 1 FONKSIYONU***************************************************************************

void sali1(int a)
{  
   while(a==0)///////////////////BU FONKSIYNA GIRIYOR ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
   {  
      lcd_gotoxy(3,2);//LCD belirtilen satýr ve sütuna git komutu
      printf(lcd_putc,"ACIK/KAPALI");
      delay_ms(100);
           
      if(input(pin_a0)==0)//ACIK BUTONUNA BASILINCA++++++++++++++++++++++++++++++++++++++++++++++++++++++++
      {  
         delay_ms(20);
         while(input(pin_a0)==0);
      
         key3=1;
         printf(lcd_putc,"\f");
         lcd_gotoxy(4,1);//LCD belirtilen satýr ve sütuna git komutu
         printf(lcd_putc,"SALI 1");
         
         lcd_gotoxy(6,2);//LCD belirtilen satýr ve sütuna git komutu
         printf(lcd_putc,"ACIK");         
         delay_ms(700);
         
         tekrar3://*****************************************************baslangic saati bitis saatinden buyukse basa doner
         
         printf(lcd_putc,"\f");// \f komutu ile LCD silinir
         lcd_gotoxy(1,1);//LCD belirtilen satýr ve sütuna git komutu
         printf(lcd_putc,"BASLANGIC SAATI");
         delay_ms(5);
         
         //**************************************** CLOCK 1
         
         clock (0);//BASLANGIC SAATI ICIN GONDERILDI
         delay_ms(300);
         
         for(int x=0;x<2;x++)//baslangýc saatý genel dýzýden aktarýlýyor
         {
            salibas[x]=zaman[x];//pazartesi 2 baslangic degerleri kaydedildi
         }

         lcd_gotoxy(1,1);//LCD belirtilen satýr ve sütuna git komutu
         printf(lcd_putc,"\f BITIS SAATI");
         delay_ms(20);
         
         //***************************************** CLOCK 2

         clock (0);//BITIS SAATI ICIN GONDERILDI

         for(int y=0;y<2;y++)//baslangýc saatý genel diziden aktarýlýyor
         {
            salibit[y]=zaman[y];//pazartesi bitis degerleri kaydedildi
         }  
           a=1;
           f=1;
      } 
      
      if(input(pin_a1)==0)//KAPALI BUTONUNA BASILINCA
      {
         delay_ms(20);
         while(input(pin_a1)==0);
         
         key3=0;
         printf(lcd_putc,"\f");
         lcd_gotoxy(1,2);//LCD belirtilen satýr ve sütuna git komutu
         printf(lcd_putc,"KAPALI");
         delay_ms(500);
         sifreleme(3,0);// SALI 1  GUNU KAPALI SIFRELEME-SOL GUN KODU-SAG ACIK/KAPALI KODU
         delay_ms(20);
         a=1;
         i=3;
         f=0;
      }
   }
}

//******************************************************************************************** SALI 2FONKSIYONU***************************************************************************

void sali2(int a)
{  
   while(a==0)///////////////////BU FONKSIYNA GIRIYOR ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
   {  
      salibit2[0]=ptesibit[0];
      salibit2[1]=ptesibit[1];
      ptesibit[0]=23;
      ptesibit[1]=59;
      salibas2[0]=0;
      salibas2[1]=0;
      a=1;  
   }
}

//******************************************************************************************** CARSAMBA 1 FONKSIYONU***************************************************************************

void carsamba1 (int a)
{  
   while(a==0)///////////////////BU FONKSIYNA GIRIYOR ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
   {  
      lcd_gotoxy(3,2);//LCD belirtilen satýr ve sütuna git komutu
      printf(lcd_putc,"ACIK/KAPALI");
      delay_ms(100);
         
         
      if(input(pin_a0)==0)//ACIK BUTONUNA BASILINCA++++++++++++++++++++++++++++++++++++++++++++++++++++++++
      {  
         delay_ms(20);
         while(input(pin_a0)==0);
         
         key5=1;
         printf(lcd_putc,"\f");
         lcd_gotoxy(4,1);//LCD belirtilen satýr ve sütuna git komutu
         printf(lcd_putc,"CARSAMBA 1");
         
         lcd_gotoxy(6,2);//LCD belirtilen satýr ve sütuna git komutu
         printf(lcd_putc,"ACIK");         
         delay_ms(700);
         
         tekrar5://*****************************************************baslangic saati bitis saatinden buyukse basa doner
         
         printf(lcd_putc,"\f");// \f komutu ile LCD silinir
         lcd_gotoxy(1,1);//LCD belirtilen satýr ve sütuna git komutu
         printf(lcd_putc,"BASLANGIC SAATI");
         delay_ms(5);
         
         //**************************************** CLOCK 1
         
         clock (0);//BASLANGIC SAATI ICIN GONDERILDI
         delay_ms(300);
         
         for(int x=0;x<2;x++)//baslangýc saatý genel dýzýden aktarýlýyor
         {
            carbas[x]=zaman[x];//pazartesi 2 baslangic degerleri kaydedildi
         }
           
         lcd_gotoxy(1,1);//LCD belirtilen satýr ve sütuna git komutu
         printf(lcd_putc,"\f BITIS SAATI");
         delay_ms(20);
         
         //***************************************** CLOCK 2
         
         clock (0);//BITIS SAATI ICIN GONDERILDI

         for(int y=0;y<2;y++)//baslangýc saatý genel diziden aktarýlýyor
         {
            carbit[y]=zaman[y];//pazartesi bitis degerleri kaydedildi
         }  
   
           a=1;
           f=1;
      } 
      
      if(input(pin_a1)==0)//KAPALI BUTONUNA BASILINCA 
      {
         delay_ms(20);
         while(input(pin_a1)==0);
         
         key5=0;
         printf(lcd_putc,"\f");
         lcd_gotoxy(1,2);//LCD belirtilen satýr ve sütuna git komutu
         printf(lcd_putc,"KAPALI");
         delay_ms(500);
         sifreleme(5,0);// CARSAMBA 1  GUNU KAPALI SIFRELEME-SOL GUN KODU-SAG ACIK/KAPALI KODU
         delay_ms(20);
         a=1;
         i=3;
         f=0;
      }
   }
}

//******************************************************************************************** CARSAMBA 2 FONKSIYONU***************************************************************************
void carsamba2 (int a)
{  
   while(a==0)///////////////////BU FONKSIYNA GIRIYOR ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
   {  
      carbit2[0]=salibit[0];
      carbit2[1]=salibit[1];
      salibit[0]=23;
      salibit[1]=59;
      carbas2[0]=0;
      carbas2[1]=0;
      a=1;  
   } 
}

//******************************************************************************************** PERSEMBE 1 FONKSIYONU***************************************************************************
void persembe1 (int a)
{  
   while(a==0)///////////////////BU FONKSIYNA GIRIYOR ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
   {  
      lcd_gotoxy(3,2);//LCD belirtilen satýr ve sütuna git komutu
      printf(lcd_putc,"ACIK/KAPALI");
      delay_ms(100);
          
      if(input(pin_a0)==0)//ACIK BUTONUNA BASILINCA++++++++++++++++++++++++++++++++++++++++++++++++++++++++
      {  
         delay_ms(20);
         while(input(pin_a0)==0);
         
         key7=1;
         printf(lcd_putc,"\f");
         lcd_gotoxy(4,1);//LCD belirtilen satýr ve sütuna git komutu
         printf(lcd_putc,"PERSEMBE 1");
         
         lcd_gotoxy(6,2);//LCD belirtilen satýr ve sütuna git komutu
         printf(lcd_putc,"ACIK");         
         delay_ms(700);
         
         tekrar7://*****************************************************baslangic saati bitis saatinden buyukse basa doner
         
         printf(lcd_putc,"\f");// \f komutu ile LCD silinir
         lcd_gotoxy(1,1);//LCD belirtilen satýr ve sütuna git komutu
         printf(lcd_putc,"BASLANGIC SAATI");
         delay_ms(5);
         
         //**************************************** CLOCK 1
         
         clock (0);//BASLANGIC SAATI ICIN GONDERILDI
         delay_ms(300);
         
         for(int x=0;x<2;x++)//baslangýc saatý genel dýzýden aktarýlýyor
         {
            perbas[x]=zaman[x];//pazartesi 2 baslangic degerleri kaydedildi
         }
 
         lcd_gotoxy(1,1);//LCD belirtilen satýr ve sütuna git komutu
         printf(lcd_putc,"\f BITIS SAATI");
         delay_ms(20);

         //***************************************** CLOCK 2

         clock (0);//BITIS SAATI ICIN GONDERILDI

         for(int y=0;y<2;y++)//baslangýc saatý genel diziden aktarýlýyor
         {
            perbit[y]=zaman[y];//pazartesi bitis degerleri kaydedildi
         }  
         
           a=1;
           f=1;
      } 
      if(input(pin_a1)==0)//KAPALI BUTONUNA BASILINCA 
      {
         delay_ms(20);
         while(input(pin_a1)==0);
         
         key7=0;
         printf(lcd_putc,"\f");
         lcd_gotoxy(1,2);//LCD belirtilen satýr ve sütuna git komutu
         printf(lcd_putc,"KAPALI");
         delay_ms(500);
         sifreleme(7,0);// CARSAMBA 1  GUNU KAPALI SIFRELEME-SOL GUN KODU-SAG ACIK/KAPALI KODU
         delay_ms(20);
         a=1;
         i=4;
         f=0;
   
      }
   }
}


//******************************************************************************************** PERSEMBE 2 FONKSIYONU***************************************************************************
void persembe2 (int a)
{  
   while(a==0)///////////////////BU FONKSIYNA GIRIYOR ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
   {  
         perbit2[0]=carbit[0];
         perbit2[1]=carbit[1];
         carbit[0]=23;
         carbit[1]=59;
         perbas2[0]=0;
         perbas2[1]=0;
         a=1;  
   } 
}


//******************************************************************************************** CUMA 1 FONKSIYONU***************************************************************************
void cuma1 (int a)
{  
   while(a==0)///////////////////BU FONKSIYNA GIRIYOR ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
   {  
      lcd_gotoxy(3,2);//LCD belirtilen satýr ve sütuna git komutu
      printf(lcd_putc,"ACIK/KAPALI");
      delay_ms(100);
            
      if(input(pin_a0)==0)//ACIK BUTONUNA BASILINCA++++++++++++++++++++++++++++++++++++++++++++++++++++++++
      {  
         delay_ms(20);
         while(input(pin_a0)==0);
         
         key9=1;
         printf(lcd_putc,"\f");
         lcd_gotoxy(4,1);//LCD belirtilen satýr ve sütuna git komutu
         printf(lcd_putc,"CUMA 1");
         
         lcd_gotoxy(6,2);//LCD belirtilen satýr ve sütuna git komutu
         printf(lcd_putc,"ACIK");         
         delay_ms(700);
         
         tekrar9://*****************************************************baslangic saati bitis saatinden buyukse basa doner
         
         printf(lcd_putc,"\f");// \f komutu ile LCD silinir
         lcd_gotoxy(1,1);//LCD belirtilen satýr ve sütuna git komutu
         printf(lcd_putc,"BASLANGIC SAATI");
         delay_ms(5);
         
         //**************************************** CLOCK 1
         
         clock (0);//BASLANGIC SAATI ICIN GONDERILDI
         delay_ms(300);
         
         for(int x=0;x<2;x++)//baslangýc saatý genel dýzýden aktarýlýyor
         {
            cumabas[x]=zaman[x];//cuma 2 baslangic degerleri kaydedildi
         }
           
         lcd_gotoxy(1,1);//LCD belirtilen satýr ve sütuna git komutu
         printf(lcd_putc,"\f BITIS SAATI");
         delay_ms(20);
         
         //***************************************** CLOCK 2

         clock (0);//BITIS SAATI ICIN GONDERILDI

         for(int y=0;y<2;y++)//baslangýc saatý genel diziden aktarýlýyor
         {
            cumabit[y]=zaman[y];//pazartesi bitis degerleri kaydedildi
         }  

           a=1;
           f=1;
      } 
      if(input(pin_a1)==0)//KAPALI BUTONUNA BASILINCA 
      {
         delay_ms(20);
         while(input(pin_a1)==0);
         
         key9=0;
         printf(lcd_putc,"\f");
         lcd_gotoxy(1,2);//LCD belirtilen satýr ve sütuna git komutu
         printf(lcd_putc,"KAPALI");
         delay_ms(500);
         sifreleme(9,0);// CARSAMBA 1  GUNU KAPALI SIFRELEME-SOL GUN KODU-SAG ACIK/KAPALI KODU
         delay_ms(20);
         a=1;
         i=5;
         f=0;
      }
   }
}

//******************************************************************************************** CUMA 2 FONKSIYONU***************************************************************************
void cuma2 (int a)
{  
   while(a==0)///////////////////BU FONKSIYNA GIRIYOR ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
   {       
      cumabit2[0]=perbit[0];
      cumabit2[1]=perbit[1];
      perbit[0]=23;
      perbit[1]=59;
      cumabas2[0]=0;
      cumabas2[1]=0;
      a=1;  
   } 
}



//******************************************************************************************** CUMARTESI 1 FONKSIYONU***************************************************************************
void cumartesi1 (int a)
{  
   while(a==0)///////////////////BU FONKSIYNA GIRIYOR ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
   {  
      lcd_gotoxy(3,2);//LCD belirtilen satýr ve sütuna git komutu
      printf(lcd_putc,"ACIK/KAPALI");
      delay_ms(100);
            
      if(input(pin_a0)==0)//ACIK BUTONUNA BASILINCA++++++++++++++++++++++++++++++++++++++++++++++++++++++++
      {  
         delay_ms(20);
         while(input(pin_a0)==0);
         
         key11=1;
         printf(lcd_putc,"\f");
         lcd_gotoxy(4,1);//LCD belirtilen satýr ve sütuna git komutu
         printf(lcd_putc,"CUMARTESI 1");
         
         lcd_gotoxy(6,2);//LCD belirtilen satýr ve sütuna git komutu
         printf(lcd_putc,"ACIK");         
         delay_ms(700);
         
         tekrar11://*****************************************************baslangic saati bitis saatinden buyukse basa doner
         
         printf(lcd_putc,"\f");// \f komutu ile LCD silinir
         lcd_gotoxy(1,1);//LCD belirtilen satýr ve sütuna git komutu
         printf(lcd_putc,"BASLANGIC SAATI");
         delay_ms(5);
         
         //**************************************** CLOCK 1
         
         clock (0);//BASLANGIC SAATI ICIN GONDERILDI
         delay_ms(300);
         
         for(int x=0;x<2;x++)//baslangýc saatý genel dýzýden aktarýlýyor
         {
            ctesibas[x]=zaman[x];//cuma 2 baslangic degerleri kaydedildi
         }
           
         lcd_gotoxy(1,1);//LCD belirtilen satýr ve sütuna git komutu
         printf(lcd_putc,"\f BITIS SAATI");
         delay_ms(20);
         
         //***************************************** CLOCK 2

         clock (0);//BITIS SAATI ICIN GONDERILDI

         for(int y=0;y<2;y++)//baslangýc saatý genel diziden aktarýlýyor
         {
            ctesibit[y]=zaman[y];//pazartesi bitis degerleri kaydedildi
         }  
           a=1;
           f=1;
      } 
      if(input(pin_a1)==0)//KAPALI BUTONUNA BASILINCA 
      {
         delay_ms(20);
         while(input(pin_a1)==0);
         
         key11=0;
         printf(lcd_putc,"\f");
         lcd_gotoxy(1,2);//LCD belirtilen satýr ve sütuna git komutu
         printf(lcd_putc,"KAPALI");
         delay_ms(500);
         sifreleme(11,0);// CARSAMBA 1  GUNU KAPALI SIFRELEME-SOL GUN KODU-SAG ACIK/KAPALI KODU
         delay_ms(20);
         a=1;
         i=6;
         f=0;
      }
   }
}

//******************************************************************************************** CUMARTESI 2 FONKSIYONU***************************************************************************
void cumartesi2 (int a)
{  
   while(a==0)///////////////////BU FONKSIYNA GIRIYOR ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
   {       
      ctesibit2[0]=cumabit[0];
      ctesibit2[1]=cumabit[1];
      cumabit[0]=23;
      cumabit[1]=59;
      ctesibas2[0]=0;
      ctesibas2[1]=0;
      a=1;  
   } 
}

void pazar1 (int a)
{  
   while(a==0)///////////////////BU FONKSIYNA GIRIYOR ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
   {  
      lcd_gotoxy(3,2);//LCD belirtilen satýr ve sütuna git komutu
      printf(lcd_putc,"ACIK/KAPALI");
      delay_ms(100);
  
      if(input(pin_a0)==0)//ACIK BUTONUNA BASILINCA++++++++++++++++++++++++++++++++++++++++++++++++++++++++
      {  
         delay_ms(20);
         while(input(pin_a0)==0);
         
         key13=1;
         printf(lcd_putc,"\f");
         lcd_gotoxy(4,1);//LCD belirtilen satýr ve sütuna git komutu
         printf(lcd_putc,"PAZAR 1");
         
         lcd_gotoxy(6,2);//LCD belirtilen satýr ve sütuna git komutu
         printf(lcd_putc,"ACIK");         
         delay_ms(700);
         
         tekrar13://*****************************************************baslangic saati bitis saatinden buyukse basa doner
         
         printf(lcd_putc,"\f");// \f komutu ile LCD silinir
         lcd_gotoxy(1,1);//LCD belirtilen satýr ve sütuna git komutu
         printf(lcd_putc,"BASLANGIC SAATI");
         delay_ms(5);
         
         //**************************************** CLOCK 1
         
         clock (0);//BASLANGIC SAATI ICIN GONDERILDI
         delay_ms(300);
         
         for(int x=0;x<2;x++)//baslangýc saatý genel dýzýden aktarýlýyor
         {
            pazarbas[x]=zaman[x];//cuma 2 baslangic degerleri kaydedildi
         }
  
         lcd_gotoxy(1,1);//LCD belirtilen satýr ve sütuna git komutu
         printf(lcd_putc,"\f BITIS SAATI");
         delay_ms(20);
         
         //***************************************** CLOCK 2

         clock (0);//BITIS SAATI ICIN GONDERILDI

         for(int y=0;y<2;y++)//baslangýc saatý genel diziden aktarýlýyor
         {
            pazarbit[y]=zaman[y];//pazartesi bitis degerleri kaydedildi
         }  
         
           a=1;
           f=1;
      } 
      if(input(pin_a1)==0)//KAPALI BUTONUNA BASILINCA 
      {
         delay_ms(20);
         while(input(pin_a1)==0);
         
         key13=0;
         printf(lcd_putc,"\f");
         lcd_gotoxy(1,2);//LCD belirtilen satýr ve sütuna git komutu
         printf(lcd_putc,"KAPALI");
         delay_ms(500);
         sifreleme(13,0);// CARSAMBA 1  GUNU KAPALI SIFRELEME-SOL GUN KODU-SAG ACIK/KAPALI KODU
         delay_ms(20);
         a=1;
         i=7;
         f=0;
      }
   }
}


void pazar2 (int a)
{  
   while(a==0)///////////////////BU FONKSIYNA GIRIYOR ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
   {       
      pazarbit2[0]=ctesibit[0];
      pazarbit2[1]=ctesibit[1];
      ctesibit[0]=23;
      ctesibit[1]=59;
      pazarbas2[0]=0;
      pazarbas2[1]=0;
      a=1;  
   } 
}




//******************************************************************************************** CLOCK FONKSIYONU*********************************************************************************

void clock (int b)// k DEGERI 1 GELIRSE O GUN AKTIF 0 ISE PASIF OLACAK
{     
   j=1;//her fonksiyona girdiðinde imleç sol saat tarafýnda olacak.
     
   while(b==0)
   { 
      lcd_gotoxy(8,2);//LCD belirtilen sütun ve satýra git komutu
      printf(lcd_putc,":");
      delay_ms(5);
      if(saat<10)//Tek haneli rakamlarda ekranda basa 0 ATAR
      {
         lcd_gotoxy(6,2);//LCD belirtilen sütun ve satýra git komutu
         printf(lcd_putc,"%02d",saat);  
         if(j==1)
         {
            lcd_gotoxy(7,2);
            lcd_send_byte(0x00,0x0F);
            delay_ms(40);
            lcd_send_byte(0x00,0x0C);
         }
      
         delay_ms(5); 
      }
      if(saat>=10)//Cift haneli rakamlarda ekranda basa 0 ATMAZ
      {
         lcd_gotoxy(6,2);//LCD belirtilen sütun ve satýra git komutu
     
         printf(lcd_putc,"%2d",saat);
         if(j==1)
         {
            lcd_gotoxy(7,2);
            lcd_send_byte(0x00,0x0F);
            delay_ms(40);
            lcd_send_byte(0x00,0x0C);
         }
      }
      
      if(dakika<10)//Tek haneli rakamlarda ekranda basa 0 ATAR
      {
         lcd_gotoxy(10,2);//LCD belirtilen sütun ve satýra git komutu
         printf(lcd_putc,"%02d",dakika); 
         if(j==2)
         {
            lcd_gotoxy(11,2);
            lcd_send_byte(0x00,0x0F);
            delay_ms(40);
            lcd_send_byte(0x00,0x0C);
         }
      }
      if(dakika>=10)//Cift haneli rakamlarda ekranda basa 0 ATMAZ
      {
         lcd_gotoxy(10,2);//LCD belirtilen sütun ve satýra git komutu
         printf(lcd_putc,"%2d",dakika);
         if(j==2)
         {
            lcd_gotoxy(11,2);
            lcd_send_byte(0x00,0x0F);
            delay_ms(40);
            lcd_send_byte(0x00,0x0C);
         }    
      }
      
      if(input(pin_b1)==0)//SOL TARAFA GECIS saat tarafý------------------------------RB1
      {
         delay_ms(20);
         while(input(pin_b1)==0);
         j--;
         if(j==0)
         {j=1;}
      }
   
      if(input(pin_b2)==0)//SAG TARAFA GECIS saat tarafý-----------------------------RB2
      {
         delay_ms(20);
         while(input(pin_b2)==0);
         j++;
         if(j==3)
         {j=2;}
      }
     
      if(j==1)//SOL TARAF BASLANGIC - BITIS SAAT AYARI
      {
         if(input(pin_b3)==0)// SAATI YUKARI SAYMA
         {
            delay_ms(20);
            while(input(pin_b3)==0);
            saat++;
            if(saat==24)
            {saat=0;}
         }
         if(input(pin_b4)==0)// SAATI ASAGI SAYMA
         {
            delay_ms(20);
            while(input(pin_b4)==0);
            saat--;
            if(saat==-1)
            {saat=23;}
         }
      }
  
      if(j==2)// SAG TARAF BASLANGIC- BITIS DAKIKA AYARI
      {
         if(input(pin_b3)==0)// DAKIKA YUKARI SAYMA
         {
            delay_ms(20);
            while(input(pin_b3)==0);
            dakika++; 
            if(dakika==60)
            {dakika=0;}           
         }
         if(input(pin_b4)==0)// DAKIKA ASAGI SAYMA
         {
            delay_ms(20);
            while(input(pin_b4)==0);
            dakika--;
            if(dakika==-1)
            {dakika=59;}
         }
      }

      if(input(pin_b5)==0)//OKEY BUTONUNA BASINCA FONKSIYONDAN CIKILIR ve GUN ICERISINDEKI CLOCK FONK. GERI DONER
      {
         delay_ms(20);
         while(input(pin_b5)==0);
         zaman[0]=saat;
         zaman[1]=dakika;  
         saat=12;
         dakika=0;
         b=1;// clock fonk. içindeki while() döngüsünden çýkaran deger
      }
   }
}


void sifreleme(int v,int z ) // günlerin belirlendiði ana fonksiyondaki i degeri buraya v olarak girer z degeri ise o günün kapalý olup olmadýgýný bildirir.
{
   if(v==1)  //************************* PAZARTESI 1 ********************************************** 
   {     
      if(z==1) //ACIK
      {  
         sifre[0]='d';//ilk basamak acik kodu--yani pazartesi acik
         //*******************  baslangic saati  ***************
         if(ptesibas[0]<10)
         { 
            sifre[1]= 'c';
            c2= harf(ptesibas[0]%10);
            sifre[2]=c2;
         }
         if(ptesibas[0]>=10)
         {  
            c1= harf((ptesibas[0]-(ptesibas[0]%10))/10);
            sifre[1]=c1;
            c2= harf(ptesibas[0]%10);
            sifre[2]=c2;
         } 
         //*******************  baslangic dakikasi ***************
         if(ptesibas[1]<10)
         {
            sifre[3]='c';
            c1=harf(ptesibas[1]%10);
            sifre[4]=c1;
         }
         if(ptesibas[1]>=10)
         {  
            c1=harf((ptesibas[1]-(ptesibas[1]%10))/10);
            sifre[3]=c1;
            c2=harf(ptesibas[1]%10);
            sifre[4]=c2;
         }
         //***************  bitis saati  **************************
         
         if(ptesibit[0]<10)
         {
            sifre[5]='c';
            c1=harf(ptesibit[0]%10);
            sifre[6]=c1;
         }
         if(ptesibit[0]>=10)
         {
            c1=harf((ptesibit[0]-(ptesibit[0]%10))/10);
            sifre[5]=c1;
            c2=harf(ptesibit[0]%10);
            sifre[6]=c2;
         } 
         
         //*******************  bitis dakikasi   ***************
         if(ptesibit[1]<10)
         {
            sifre[7]='c';
            c1=harf(ptesibit[1]%10);
            sifre[8]=c1;
         }
         if(ptesibit[1]>=10)
         {
            c1=harf((ptesibit[1]-(ptesibit[1]%10))/10);
            sifre[7]=c1;
            c2=harf(ptesibit[1]%10);
            sifre[8]=c2;
         } 
      }
      
      if(z==0) //KAPALI
      {  
         for(int kap=0;kap<9;kap++)
         {
            sifre[kap]='c';
         }
      }
   }
   
   if(v==2)  //************************* PAZARTESI 2 ********************************************** 
   {     
      if(z==1) //ACIK
      {  
         sifre[9]='d';//ilk basamak acik kodu--yani pazartesi acik
         //*******************  baslangic saati  ***************
         if(ptesibas2[0]<10)
         { 
            sifre[10]= 'c';
            c2= harf(ptesibas2[0]%10);
            sifre[11]=c2;
         }
         if(ptesibas2[0]>=10)
         {  
            c1= harf((ptesibas2[0]-(ptesibas2[0]%10))/10);
            sifre[10]=c1;
            c2= harf(ptesibas2[0]%10);
            sifre[11]=c2;
         } 
         //*******************  baslangic dakikasi ***************
         if(ptesibas2[1]<10)
         {
            sifre[12]='c';
            c1=harf(ptesibas2[1]%10);
            sifre[13]=c1;
         }
         if(ptesibas2[1]>=10)
         {  
            c1=harf((ptesibas2[1]-(ptesibas2[1]%10))/10);
            sifre[12]=c1;
            c2=harf(ptesibas2[1]%10);
            sifre[13]=c2;
         }
         //***************  bitis saati  **************************
         
         if(ptesibit2[0]<10)
         {
            sifre[14]='c';
            c1=harf(ptesibit2[0]%10);
            sifre[15]=c1;
         }
         if(ptesibit2[0]>=10)
         {
            c1=harf((ptesibit2[0]-(ptesibit2[0]%10))/10);
            sifre[14]=c1;
            c2=harf(ptesibit2[0]%10);
            sifre[15]=c2;
         } 
         
         //*******************  bitis dakikasi   ***************
         if(ptesibit2[1]<10)
         {
            sifre[16]='c';
            c1=harf(ptesibit2[1]%10);
            sifre[17]=c1;
         }
         if(ptesibit2[1]>=10)
         {
            c1=harf((ptesibit2[1]-(ptesibit2[1]%10))/10);
            sifre[16]=c1;
            c2=harf(ptesibit2[1]%10);
            sifre[17]=c2;
         } 
      }
      
      if(z==0) //KAPALI
      {  
         for(int kap=9;kap<18;kap++)
         {
            sifre[kap]='c';
         }
      }
   }
   
   if(v==3)  //************************* SALI 1 **********************************************
   {     
      if(z==1) //ACIK
      {  
         sifre[18]='d';//ilk basamak acik kodu--yani pazartesi acik
         //*******************  baslangic saati  ***************
         if(salibas[0]<10)
         { 
            sifre[19]= 'c';
            c2= harf(salibas[0]%10);
            sifre[20]=c2;
         }
         if(salibas[0]>=10)
         {  
            c1= harf((salibas[0]-(salibas[0]%10))/10);
            sifre[19]=c1;
            c2= harf(salibas[0]%10);
            sifre[20]=c2;
         } 
         //*******************  baslangic dakikasi ***************
         if(salibas[1]<10)
         {
            sifre[21]='c';
            c1=harf(salibas[1]%10);
            sifre[22]=c1;
         }
         if(salibas[1]>=10)
         {  
            c1=harf((salibas[1]-(salibas[1]%10))/10);
            sifre[21]=c1;
            c2=harf(salibas[1]%10);
            sifre[22]=c2;
         }
         //***************  bitis saati  **************************
         
         if(salibit[0]<10)
         {
            sifre[23]='c';
            c1=harf(salibit[0]%10);
            sifre[24]=c1;
         }
         if(salibit[0]>=10)
         {
            c1=harf((salibit[0]-(salibit[0]%10))/10);
            sifre[23]=c1;
            c2=harf(salibit[0]%10);
            sifre[24]=c2;
         } 
         
         //*******************  bitis dakikasi   ***************
         if(salibit[1]<10)
         {
            sifre[25]='c';
            c1=harf(salibit[1]%10);
            sifre[26]=c1;
         }
         if(salibit[1]>=10)
         {
            c1=harf((salibit[1]-(salibit[1]%10))/10);
            sifre[25]=c1;
            c2=harf(salibit[1]%10);
            sifre[26]=c2;
         } 
      }
      
      if(z==0) //KAPALI
      {  
         for(int kap=18;kap<27;kap++)
         {
            sifre[kap]='c';
         }
      }
   }  
   
   if(v==4)  //************************* SALI 2 **********************************************
   {     
      if(z==1) //ACIK
      {  
         sifre[27]='d';//ilk basamak acik kodu--yani pazartesi acik
         //*******************  baslangic saati  ***************
         if(salibas2[0]<10)
         { 
            sifre[28]= 'c';
            c2= harf(salibas2[0]%10);
            sifre[29]=c2;
         }
         if(salibas2[0]>=10)
         {  
            c1= harf((salibas2[0]-(salibas2[0]%10))/10);
            sifre[28]=c1;
            c2= harf(salibas2[0]%10);
            sifre[29]=c2;
         } 
         //*******************  baslangic dakikasi ***************
         if(salibas2[1]<10)
         {
            sifre[30]='c';
            c1=harf(salibas2[1]%10);
            sifre[31]=c1;
         }
         if(salibas2[1]>=10)
         {  
            c1=harf((salibas2[1]-(salibas2[1]%10))/10);
            sifre[30]=c1;
            c2=harf(salibas2[1]%10);
            sifre[31]=c2;
         }
         //***************  bitis saati  **************************
         
         if(salibit2[0]<10)
         {
            sifre[32]='c';
            c1=harf(salibit2[0]%10);
            sifre[33]=c1;
         }
         if(salibit2[0]>=10)
         {
            c1=harf((salibit2[0]-(salibit2[0]%10))/10);
            sifre[32]=c1;
            c2=harf(salibit2[0]%10);
            sifre[33]=c2;
         } 
         
         //*******************  bitis dakikasi   ***************
         if(salibit2[1]<10)
         {
            sifre[34]='c';
            c1=harf(salibit2[1]%10);
            sifre[35]=c1;
         }
         if(salibit2[1]>=10)
         {
            c1=harf((salibit2[1]-(salibit2[1]%10))/10);
            sifre[34]=c1;
            c2=harf(salibit2[1]%10);
            sifre[35]=c2;
         }      
      }
      
      if(z==0) //KAPALI
      {  
         for(int kap=27;kap<36;kap++)
         {
            sifre[kap]='c';
         }
      }
   }  
   
   
   if(v==5)  //************************* CARSAMBA 1 **********************************************
   {     
      if(z==1) //ACIK
      {  
         sifre[36]='d';//ilk basamak acik kodu--yani pazartesi acik
         //*******************  baslangic saati  ***************
         if(carbas[0]<10)
         { 
            sifre[37]= 'c';
            c2= harf(carbas[0]%10);
            sifre[38]=c2;
         }
         if(carbas[0]>=10)
         {  
            c1= harf((carbas[0]-(carbas[0]%10))/10);
            sifre[37]=c1;
            c2= harf(carbas[0]%10);
            sifre[38]=c2;
         } 
         //*******************  baslangic dakikasi ***************
         if(carbas[1]<10)
         {
            sifre[39]='c';
            c1=harf(carbas[1]%10);
            sifre[40]=c1;
         }
         if(carbas[1]>=10)
         {  
            c1=harf((carbas[1]-(carbas[1]%10))/10);
            sifre[39]=c1;
            c2=harf(carbas[1]%10);
            sifre[40]=c2;
         }
         //***************  bitis saati  **************************
         
         if(carbit[0]<10)
         {
            sifre[41]='c';
            c1=harf(carbit[0]%10);
            sifre[42]=c1;
         }
         if(carbit[0]>=10)
         {
            c1=harf((carbit[0]-(carbit[0]%10))/10);
            sifre[41]=c1;
            c2=harf(carbit[0]%10);
            sifre[42]=c2;
         } 
         
         //*******************  bitis dakikasi   ***************
         if(carbit[1]<10)
         {
            sifre[43]='c';
            c1=harf(carbit[1]%10);
            sifre[44]=c1;
         }
         if(carbit[1]>=10)
         {
            c1=harf((carbit[1]-(carbit[1]%10))/10);
            sifre[43]=c1;
            c2=harf(carbit[1]%10);
            sifre[44]=c2;
         }  
      }
      
      if(z==0) //KAPALI
      {  
         for(int kap=36;kap<45;kap++)
         {
            sifre[kap]='c';
         }
      }
   }
   
   if(v==6)  //************************* CARSAMBA 2 **********************************************
   {     
      if(z==1) //ACIK
      {  
         sifre[45]='d';//ilk basamak acik kodu--yani pazartesi acik
         //*******************  baslangic saati  ***************
         if(carbas2[0]<10)
         { 
            sifre[46]= 'c';
            c2= harf(carbas2[0]%10);
            sifre[47]=c2;
         }
         if(carbas2[0]>=10)
         {  
            c1= harf((carbas2[0]-(carbas2[0]%10))/10);
            sifre[46]=c1;
            c2= harf(carbas2[0]%10);
            sifre[47]=c2;
         } 
         //*******************  baslangic dakikasi ***************
         if(carbas2[1]<10)
         {
            sifre[48]='c';
            c1=harf(carbas2[1]%10);
            sifre[49]=c1;
         }
         if(carbas2[1]>=10)
         {  
            c1=harf((carbas2[1]-(carbas2[1]%10))/10);
            sifre[48]=c1;
            c2=harf(carbas2[1]%10);
            sifre[49]=c2;
         }
         //***************  bitis saati  **************************
         
         if(carbit2[0]<10)
         {
            sifre[50]='c';
            c1=harf(carbit2[0]%10);
            sifre[51]=c1;
         }
         if(carbit2[0]>=10)
         {
            c1=harf((carbit2[0]-(carbit2[0]%10))/10);
            sifre[50]=c1;
            c2=harf(carbit2[0]%10);
            sifre[51]=c2;
         } 
         
         //*******************  bitis dakikasi   ***************
         if(carbit2[1]<10)
         {
            sifre[52]='c';
            c1=harf(carbit2[1]%10);
            sifre[53]=c1;
         }
         if(carbit2[1]>=10)
         {
            c1=harf((carbit2[1]-(carbit2[1]%10))/10);
            sifre[52]=c1;
            c2=harf(carbit2[1]%10);
            sifre[53]=c2;
         } 
      }
      
      if(z==0) //KAPALI
      {  
         for(int kap=45;kap<54;kap++)
         {
            sifre[kap]='c';
         }
      }
   }
   if(v==7)  //************************* PERSEMBE 1 **********************************************
   {     
      if(z==1) //ACIK
      {  
         sifre[54]='d';//ilk basamak acik kodu--yani pazartesi acik
         //*******************  baslangic saati  ***************
         if(perbas[0]<10)
         { 
            sifre[55]= 'c';
            c2= harf(perbas[0]%10);
            sifre[56]=c2;
         }
         if(perbas[0]>=10)
         {  
            c1= harf((perbas[0]-(perbas[0]%10))/10);
            sifre[55]=c1;
            c2= harf(perbas[0]%10);
            sifre[56]=c2;
         } 
         //*******************  baslangic dakikasi ***************
         if(perbas[1]<10)
         {
            sifre[57]='c';
            c1=harf(perbas[1]%10);
            sifre[58]=c1;
         }
         if(perbas[1]>=10)
         {  
            c1=harf((perbas[1]-(perbas[1]%10))/10);
            sifre[57]=c1;
            c2=harf(perbas[1]%10);
            sifre[58]=c2;
         }
         //***************  bitis saati  **************************
         
         if(perbit[0]<10)
         {
            sifre[59]='c';
            c1=harf(perbit[0]%10);
            sifre[60]=c1;
         }
         if(perbit[0]>=10)
         {
            c1=harf((perbit[0]-(perbit[0]%10))/10);
            sifre[59]=c1;
            c2=harf(perbit[0]%10);
            sifre[60]=c2;
         } 
         
         //*******************  bitis dakikasi   ***************
         if(perbit[1]<10)
         {
            sifre[61]='c';
            c1=harf(perbit[1]%10);
            sifre[62]=c1;
         }
         if(perbit[1]>=10)
         {
            c1=harf((perbit[1]-(perbit[1]%10))/10);
            sifre[61]=c1;
            c2=harf(perbit[1]%10);
            sifre[62]=c2;
         }
      }
      
      if(z==0) //KAPALI
      {  
         for(int kap=54;kap<63;kap++)
         {
            sifre[kap]='c';
         }
      }
   } 
   if(v==8)  //************************* PERSEMBE 2 **********************************************
   {     
      if(z==1) //ACIK
      {  
         sifre[63]='d';//ilk basamak acik kodu--yani pazartesi acik
         //*******************  baslangic saati  ***************
         if(perbas2[0]<10)
         { 
            sifre[64]= 'c';
            c2= harf(perbas2[0]%10);
            sifre[65]=c2;
         }
         if(perbas2[0]>=10)
         {  
            c1= harf((perbas2[0]-(perbas2[0]%10))/10);
            sifre[64]=c1;
            c2= harf(perbas2[0]%10);
            sifre[65]=c2;
         } 
         //*******************  baslangic dakikasi ***************
         if(perbas2[1]<10)
         {
            sifre[66]='c';
            c1=harf(perbas2[1]%10);
            sifre[67]=c1;
         }
         if(perbas2[1]>=10)
         {  
            c1=harf((perbas2[1]-(perbas2[1]%10))/10);
            sifre[66]=c1;
            c2=harf(perbas2[1]%10);
            sifre[67]=c2;
         }
         //***************  bitis saati  **************************
         
         if(perbit2[0]<10)
         {
            sifre[68]='c';
            c1=harf(perbit2[0]%10);
            sifre[69]=c1;
         }
         if(perbit2[0]>=10)
         {
            c1=harf((perbit2[0]-(perbit2[0]%10))/10);
            sifre[68]=c1;
            c2=harf(perbit2[0]%10);
            sifre[69]=c2;
         } 
         
         //*******************  bitis dakikasi   ***************
         if(perbit2[1]<10)
         {
            sifre[70]='c';
            c1=harf(perbit2[1]%10);
            sifre[71]=c1;
         }
         if(perbit2[1]>=10)
         {
            c1=harf((perbit2[1]-(perbit2[1]%10))/10);
            sifre[70]=c1;
            c2=harf(perbit2[1]%10);
            sifre[71]=c2;
         }
      }
      
      if(z==0) //KAPALI
      {  
         for(int kap=63;kap<72;kap++)
         {
            sifre[kap]='c';
         }
      }
   }  
       
  if(v==9)  //************************* CUMA 1 **********************************************
   {     
      if(z==1) //ACIK
      {  
         sifre[72]='d';//ilk basamak acik kodu--yani pazartesi acik
         //*******************  baslangic saati  ***************
         if(cumabas[0]<10)
         { 
            sifre[73]= 'c';
            c2= harf(cumabas[0]%10);
            sifre[74]=c2;
         }
         if(cumabas[0]>=10)
         {  
            c1= harf((cumabas[0]-(cumabas[0]%10))/10);
            sifre[73]=c1;
            c2= harf(cumabas[0]%10);
            sifre[74]=c2;
         } 
         //*******************  baslangic dakikasi ***************
         if(cumabas[1]<10)
         {
            sifre[75]='c';
            c1=harf(cumabas[1]%10);
            sifre[76]=c1;
         }
         if(cumabas[1]>=10)
         {  
            c1=harf((cumabas[1]-(cumabas[1]%10))/10);
            sifre[75]=c1;
            c2=harf(cumabas[1]%10);
            sifre[76]=c2;
         }
         //***************  bitis saati  **************************
         
         if(cumabit[0]<10)
         {
            sifre[77]='c';
            c1=harf(cumabit[0]%10);
            sifre[78]=c1;
         }
         if(cumabit[0]>=10)
         {
            c1=harf((cumabit[0]-(cumabit[0]%10))/10);
            sifre[77]=c1;
            c2=harf(cumabit[0]%10);
            sifre[78]=c2;
         } 
         
         //*******************  bitis dakikasi   ***************
         if(cumabit[1]<10)
         {
            sifre[79]='c';
            c1=harf(cumabit[1]%10);
            sifre[80]=c1;
         }
         if(perbit[1]>=10)
         {
            c1=harf((cumabit[1]-(cumabit[1]%10))/10);
            sifre[79]=c1;
            c2=harf(cumabit[1]%10);
            sifre[80]=c2;
         }
      }
      
      if(z==0) //KAPALI
      {  
         for(int kap=72;kap<81;kap++)
         {
            sifre[kap]='c';
         }
      }
   }
   
   if(v==10)  //************************* CUMA 2 **********************************************
   {     
      if(z==1) //ACIK
      {  
         sifre[81]='d';//ilk basamak acik kodu--yani pazartesi acik
         //*******************  baslangic saati  ***************
         if(cumabas2[0]<10)
         { 
            sifre[82]= 'c';
            c2= harf(cumabas2[0]%10);
            sifre[83]=c2;
         }
         if(cumabas2[0]>=10)
         {  
            c1= harf((cumabas2[0]-(cumabas2[0]%10))/10);
            sifre[82]=c1;
            c2= harf(cumabas2[0]%10);
            sifre[83]=c2;
         } 
         //*******************  baslangic dakikasi ***************
         if(cumabas2[1]<10)
         {
            sifre[84]='c';
            c1=harf(cumabas2[1]%10);
            sifre[85]=c1;
         }
         if(cumabas2[1]>=10)
         {  
            c1=harf((cumabas2[1]-(cumabas2[1]%10))/10);
            sifre[84]=c1;
            c2=harf(cumabas2[1]%10);
            sifre[85]=c2;
         }
         //***************  bitis saati  **************************
         
         if(cumabit2[0]<10)
         {
            sifre[86]='c';
            c1=harf(cumabit2[0]%10);
            sifre[87]=c1;
         }
         if(cumabit2[0]>=10)
         {
            c1=harf((cumabit2[0]-(cumabit2[0]%10))/10);
            sifre[86]=c1;
            c2=harf(cumabit2[0]%10);
            sifre[87]=c2;
         } 
         
         //*******************  bitis dakikasi   ***************
         if(cumabit2[1]<10)
         {
            sifre[88]='c';
            c1=harf(cumabit2[1]%10);
            sifre[89]=c1;
         }
         if(cumabit2[1]>=10)
         {
            c1=harf((cumabit2[1]-(cumabit2[1]%10))/10);
            sifre[88]=c1;
            c2=harf(cumabit2[1]%10);
            sifre[89]=c2;
         }
      }
      
      if(z==0) //KAPALI
      {  
         for(int kap=81;kap<90;kap++)
         {
            sifre[kap]='c';
         }
      }
   }
   
  if(v==11)  //************************* CUMARTESI 1 **********************************************
   {     
      if(z==1) //ACIK
      {  
         sifre[90]='d';//ilk basamak acik kodu--yani pazartesi acik
         //*******************  baslangic saati  ***************
         if(ctesibas[0]<10)
         { 
            sifre[91]= 'c';
            c2= harf(ctesibas[0]%10);
            sifre[92]=c2;
         }
         if(ctesibas[0]>=10)
         {  
            c1= harf((ctesibas[0]-(ctesibas[0]%10))/10);
            sifre[91]=c1;
            c2= harf(ctesibas[0]%10);
            sifre[92]=c2;
         } 
         //*******************  baslangic dakikasi ***************
         if(ctesibas[1]<10)
         {
            sifre[93]='c';
            c1=harf(ctesibas[1]%10);
            sifre[94]=c1;
         }
         if(ctesibas[1]>=10)
         {  
            c1=harf((ctesibas[1]-(ctesibas[1]%10))/10);
            sifre[94]=c1;
            c2=harf(ctesibas[1]%10);
            sifre[94]=c2;
         }
         //***************  bitis saati  **************************
         
         if(ctesibit[0]<10)
         {
            sifre[95]='c';
            c1=harf(ctesibit[0]%10);
            sifre[96]=c1;
         }
         if(ctesibit[0]>=10)
         {
            c1=harf((ctesibit[0]-(ctesibit[0]%10))/10);
            sifre[95]=c1;
            c2=harf(ctesibit[0]%10);
            sifre[96]=c2;
         } 
         
         //*******************  bitis dakikasi   ***************
         if(ctesibit[1]<10)
         {
            sifre[97]='c';
            c1=harf(ctesibit[1]%10);
            sifre[98]=c1;
         }
         if(ctesibit[1]>=10)
         {
            c1=harf((ctesibit[1]-(ctesibit[1]%10))/10);
            sifre[97]=c1;
            c2=harf(ctesibit[1]%10);
            sifre[98]=c2;
         }
      }
      
      if(z==0) //KAPALI
      {  
         for(int kap=90;kap<99;kap++)
         {
            sifre[kap]='c';
         }
      }
   } 
   
    if(v==12)  //************************* CUMARTESI 2 **********************************************
   {     
      if(z==1) //ACIK
      {  
         sifre[99]='d';//ilk basamak acik kodu--yani pazartesi acik
         //*******************  baslangic saati  ***************
         if(ctesibas2[0]<10)
         { 
            sifre[100]= 'c';
            c2= harf(ctesibas2[0]%10);
            sifre[101]=c2;
         }
         if(ctesibas2[0]>=10)
         {  
            c1= harf((ctesibas2[0]-(ctesibas2[0]%10))/10);
            sifre[100]=c1;
            c2= harf(ctesibas2[0]%10);
            sifre[101]=c2;
         } 
         //*******************  baslangic dakikasi ***************
         if(ctesibas2[1]<10)
         {
            sifre[102]='c';
            c1=harf(ctesibas2[1]%10);
            sifre[103]=c1;
         }
         if(ctesibas2[1]>=10)
         {  
            c1=harf((ctesibas2[1]-(ctesibas2[1]%10))/10);
            sifre[102]=c1;
            c2=harf(ctesibas2[1]%10);
            sifre[103]=c2;
         }
         //***************  bitis saati  **************************
         
         if(ctesibit2[0]<10)
         {
            sifre[104]='c';
            c1=harf(ctesibit2[0]%10);
            sifre[105]=c1;
         }
         if(ctesibit2[0]>=10)
         {
            c1=harf((ctesibit2[0]-(ctesibit2[0]%10))/10);
            sifre[104]=c1;
            c2=harf(ctesibit2[0]%10);
            sifre[105]=c2;
         } 
         
         //*******************  bitis dakikasi   ***************
         if(ctesibit2[1]<10)
         {
            sifre[106]='c';
            c1=harf(ctesibit2[1]%10);
            sifre[107]=c1;
         }
         if(ctesibit2[1]>=10)
         {
            c1=harf((ctesibit2[1]-(ctesibit2[1]%10))/10);
            sifre[106]=c1;
            c2=harf(ctesibit2[1]%10);
            sifre[107]=c2;
         } 
      }
      
      if(z==0) //KAPALI
      {  
         for(int kap=99;kap<108;kap++)
         {
            sifre[kap]='c';
         }
      }
   } 
   
   
   if(v==13)  //************************* PAZAR 1 **********************************************
   {     
      if(z==1) //ACIK
      {  
         sifre[108]='d';//ilk basamak acik kodu--yani pazartesi acik
         //*******************  baslangic saati  ***************
         if(pazarbas[0]<10)
         { 
            sifre[109]= 'c';
            c2= harf(pazarbas[0]%10);
            sifre[110]=c2;
         }
         if(pazarbas[0]>=10)
         {  
            c1= harf((pazarbas[0]-(pazarbas[0]%10))/10);
            sifre[109]=c1;
            c2= harf(pazarbas[0]%10);
            sifre[110]=c2;
         } 
         //*******************  baslangic dakikasi ***************
         if(pazarbas[1]<10)
         {
            sifre[111]='c';
            c1=harf(pazarbas[1]%10);
            sifre[112]=c1;
         }
         if(pazarbas[1]>=10)
         {  
            c1=harf((pazarbas[1]-(pazarbas[1]%10))/10);
            sifre[111]=c1;
            c2=harf(pazarbas[1]%10);
            sifre[112]=c2;
         }
         //***************  bitis saati  **************************
         
         if(pazarbit[0]<10)
         {
            sifre[113]='c';
            c1=harf(pazarbit[0]%10);
            sifre[114]=c1;
         }
         if(pazarbit[0]>=10)
         {
            c1=harf((pazarbit[0]-(pazarbit[0]%10))/10);
            sifre[113]=c1;
            c2=harf(pazarbit[0]%10);
            sifre[114]=c2;
         } 
         
         //*******************  bitis dakikasi   ***************
         if(pazarbit[1]<10)
         {
            sifre[115]='c';
            c1=harf(pazarbit[1]%10);
            sifre[116]=c1;
         }
         if(pazarbit[1]>=10)
         {
            c1=harf((pazarbit[1]-(pazarbit[1]%10))/10);
            sifre[115]=c1;
            c2=harf(pazarbit[1]%10);
            sifre[116]=c2;
         }
      }
      
      if(z==0) //KAPALI
      {  
         for(int kap=108;kap<117;kap++)
         {
            sifre[kap]='c';
         }
      }
   }
   
   
   if(v==14)  //************************* PAZAR 2 **********************************************
   {     
      if(z==1) //ACIK
      {  
         sifre[117]='d';//ilk basamak acik kodu--yani pazartesi acik
         //*******************  baslangic saati  ***************
         if(pazarbas2[0]<10)
         { 
            sifre[118]= 'c';
            c2= harf(pazarbas2[0]%10);
            sifre[119]=c2;
         }
         if(pazarbas2[0]>=10)
         {  
            c1= harf((pazarbas2[0]-(pazarbas2[0]%10))/10);
            sifre[118]=c1;
            c2= harf(pazarbas2[0]%10);
            sifre[119]=c2;
         } 
         //*******************  baslangic dakikasi ***************
         if(pazarbas2[1]<10)
         {
            sifre[120]='c';
            c1=harf(pazarbas2[1]%10);
            sifre[121]=c1;
         }
         if(pazarbas2[1]>=10)
         {  
            c1=harf((pazarbas2[1]-(pazarbas2[1]%10))/10);
            sifre[120]=c1;
            c2=harf(pazarbas2[1]%10);
            sifre[121]=c2;
         }
         //***************  bitis saati  **************************
         
         if(pazarbit2[0]<10)
         {
            sifre[122]='c';
            c1=harf(pazarbit2[0]%10);
            sifre[123]=c1;
         }
         if(pazarbit2[0]>=10)
         {
            c1=harf((pazarbit2[0]-(pazarbit2[0]%10))/10);
            sifre[122]=c1;
            c2=harf(pazarbit2[0]%10);
            sifre[123]=c2;
         } 
         
         //*******************  bitis dakikasi   ***************
         if(pazarbit2[1]<10)
         {
            sifre[124]='c';
            c1=harf(pazarbit2[1]%10);
            sifre[125]=c1;
         }
         if(pazarbit2[1]>=10)
         {
            c1=harf((pazarbit2[1]-(pazarbit2[1]%10))/10);
            sifre[124]=c1;
            c2=harf(pazarbit2[1]%10);
            sifre[125]=c2;
         } 
      }
      
      if(z==0) //KAPALI
      {  
         for(int kap=117;kap<126;kap++)
         {
            sifre[kap]='c';
         }
      }
   }
   
   if(v==15)  //************************* BUGUN ICIN GUN VE SAAT **********************************************
   {     
      if(z==1) //ACIK
      {  
         if(bugun[0]<10)
         { 
            sifre[127]='c';
            c2= harf(bugun[0]%10);
            sifre[128]=c2;
         }
         if(bugun[0]>=10)
         {  
            c1= harf((bugun[0]-(bugun[0]%10))/10);
            sifre[127]=c1;
            c2= harf(bugun[0]%10);
            sifre[128]=c2;
         } 
         //*******************   dakika ***************
         if(bugun[1]<10)
         {
            sifre[129]='c';
            c1=harf(bugun[1]%10);
            sifre[130]=c1;
         }
         if(bugun[1]>=10)
         {  
            c1=harf((bugun[1]-(bugun[1]%10))/10);
            sifre[129]=c1;
            c2=harf(bugun[1]%10);
            sifre[130]=c2;
         }
      }
   }
   
}//sifreleme fon bitis



void gun(int k)
{        
   while(k==0)
   {
      printf(lcd_putc,"\f");
      lcd_gotoxy(7,1);//LCD belirtilen satýr ve sütuna git komutu
      printf(lcd_putc,"BUGUN");
      delay_ms(100);  
        
      if(input(pin_b3)==0)//                    GUNLERI YUKARI SAY BUTONU
      {  
         delay_ms(20);
         while(input(pin_b3)==0);
         t++;
         if(t==8)
         {t=1;}
      }
      if(input(pin_b4)==0)//                    GUNLERI ASAGI SAY BUTONU
      {
         delay_ms(20);
         while(input(pin_b4)==0);
         t--;
         if(t==0)
         {t=7;}
      }

      if(t==1)
      {
         lcd_gotoxy(4,2);//LCD belirtilen satýr ve sütuna git komutu
         printf(lcd_putc,"PAZARTESI");
         delay_ms(200);
      }
      else if(t==2)
      {
         lcd_gotoxy(4,2);//LCD belirtilen satýr ve sütuna git komutu
         printf(lcd_putc,"SALI");
         delay_ms(100);
      }
      else if(t==3)
      {
         lcd_gotoxy(4,2);//LCD belirtilen satýr ve sütuna git komutu
         printf(lcd_putc,"CARSAMBA");
         delay_ms(100);
      }
      else if(t==4)
      {
         lcd_gotoxy(4,2);//LCD belirtilen satýr ve sütuna git komutu
         printf(lcd_putc,"PERSEMBE");
         delay_ms(100);
      }
      else if(t==5)
      {
         lcd_gotoxy(4,2);//LCD belirtilen satýr ve sütuna git komutu
         printf(lcd_putc," CUMA");
         delay_ms(100);
      }
      else if(t==6)
      {
         lcd_gotoxy(4,2);//LCD belirtilen satýr ve sütuna git komutu
         printf(lcd_putc,"CUMARTESI");
         delay_ms(100);
      }
      else if(t==7)
      {
         lcd_gotoxy(4,2);//LCD belirtilen satýr ve sütuna git komutu
         printf(lcd_putc,"PAZAR");
         delay_ms(100);
      }


      if(input(pin_b5)==0)//OKEY VERILIRSE GUNU AL
      {   
         delay_ms(20);
         while((input(pin_b5)==0));
         sifre[126]=harf(t);
         t=1;
         k=1;
         f=1;
      }
   }
}

void clock2 (int k)
{
   yan=1;
 
   while(k==0)
   { 
      lcd_gotoxy(8,2);//LCD belirtilen sütun ve satýra git komutu
      printf(lcd_putc,":");
      delay_ms(5);
      if(saat1<10)//Tek haneli rakamlarda ekranda basa 0 ATAR
      {
         lcd_gotoxy(6,2);//LCD belirtilen sütun ve satýra git komutu
         printf(lcd_putc,"%02d",saat1);     
         delay_ms(5);
         if(yan==1)// SAG TARAF  DAKIKA AYARI
         {
            lcd_gotoxy(7,2);
            lcd_send_byte(0x00,0x0F);
            delay_ms(40);
            lcd_send_byte(0x00,0x0C);
         }
      }
      if(saat1>=10)//Cift haneli rakamlarda ekranda basa 0 ATMAZ
      {
         lcd_gotoxy(6,2);//LCD belirtilen sütun ve satýra git komutu
         printf(lcd_putc,"%2d",saat1);
         delay_ms(5);
         if(yan==1)// SAG TARAF  DAKIKA AYARI
         {
            lcd_gotoxy(7,2);
            lcd_send_byte(0x00,0x0F);
            delay_ms(40);
            lcd_send_byte(0x00,0x0C);
         }
      }
      
      if(dakika1<10)//Tek haneli rakamlarda ekranda basa 0 ATAR
      {
         lcd_gotoxy(10,2);//LCD belirtilen sütun ve satýra git komutu
         printf(lcd_putc,"%02d",dakika1);    
         delay_ms(5);
         if(yan==2)// SAG TARAF  DAKIKA AYARI
         {
            lcd_gotoxy(11,2);
            lcd_send_byte(0x00,0x0F);
            delay_ms(40);
            lcd_send_byte(0x00,0x0C);
         }
      }
      if(dakika1>=10)//Cift haneli rakamlarda ekranda basa 0 ATMAZ
      {
         lcd_gotoxy(10,2);//LCD belirtilen sütun ve satýra git komutu
         printf(lcd_putc,"%2d",dakika1);    
         delay_ms(5);
         if(yan==2)// SAG TARAF  DAKIKA AYARI
         {
            lcd_gotoxy(11,2);
            lcd_send_byte(0x00,0x0F);
            delay_ms(40);
            lcd_send_byte(0x00,0x0C);
         }
      }
      
      if(input(pin_b1)==0)//SOL TARAFA GECIS saat tarafý------------------------------RB1
      {
         delay_ms(20);
         while(input(pin_b1)==0);
         yan--;
         if(yan==0)
         {yan=1;}
      }
   
      if(input(pin_b2)==0)//SAG TARAFA GECIS saat tarafý-----------------------------RB2
      {
         delay_ms(20);
         while(input(pin_b2)==0);
         yan++;
         if(yan==3)
         {yan=2;}
      }
     
      if(yan==1)// SAAT AYARI
      {
         if(input(pin_b3)==0)// SAATI YUKARI SAYMA
         {
            delay_ms(20);
            while(input(pin_b3)==0);
            saat1++;
            if(saat1==24)
            {saat1=0;}
         }
         if(input(pin_b4)==0)// SAATI ASAGI SAYMA
         {
            delay_ms(20);
            while(input(pin_b4)==0); 
            saat1--;
            if(saat1==-1)
            {saat1=23;}
         }
      }
  
      if(yan==2)// SAG TARAF  DAKIKA AYARI
      {
         if(input(pin_b3)==0)// DAKIKA YUKARI SAYMA
         {
            delay_ms(20);
            while(input(pin_b3)==0);
            dakika1++; 
            if(dakika1==60)
            {dakika1=0;}           
         }
         if(input(pin_b4)==0)// DAKIKA ASAGI SAYMA
         {
            delay_ms(20);
            while(input(pin_b4)==0);
            dakika1--;
            if(dakika1==-1)
            {dakika1=59;}
         }
      }

      if(input(pin_b5)==0)//OKEY BUTONUNA BASINCA FONKSIYONDAN CIKILIR ve GUN ICERISINDEKI CLOCK FONK. GERI DONER
      {
         delay_ms(20);
         while(input(pin_b5)==0);
         zaman[0]=saat1;
         zaman[1]=dakika1;  
         saat1=12;
         dakika1=0;
         k=1;// clock fonk. içindeki while() döngüsünden çýkaran deger
         f=1;
      }

   }
}



char harf(int e)
{  
   if(e==0)
    {  
      dene[0]='c';  
    } 
   else if(e==1)
    {   
      dene[0]='d'; 
    }   
     
    else if(e==2)
    {  
      dene[0]='e'; 
    }    
    
    else if(e==3)
    {  
      dene[0]='n'; 
    }    
   else  if(e==4)
    {    
      dene[0]='g'; 
    }   
    else if(e==5)
    {    
      dene[0]='h'; 
    }    
    else if(e==6)
    {    
      dene[0]='m'; 
    }   
    else if(e==7)
    {    
      dene[0]='p'; 
    }    
    else if(e==8)
    {   
      dene[0]='r'; 
    }    
    else if(e==9)
    {    
      dene[0]='s'; 
    }   

    return dene[0];  
}    


void kontrol(void)
{
   if((sifre[0]!='c') && (sifre[0]!='d'))
   {
      for(int knt=0;knt<9;knt++)
      {
         sifre[knt]='c';
      }
   }
   
   if((sifre[9]!='c') && (sifre[9]!='d'))
   {
      for(int knt=9;knt<18;knt++)
      {
         sifre[knt]='c';
      }
   }

   if((sifre[18]!='c') && (sifre[18]!='d'))
   {
      for(int knt=18;knt<27;knt++)
      {
         sifre[knt]='c';
      }
   }

   if((sifre[27]!='c') && (sifre[27]!='d'))
   {
      for(int knt=27;knt<36;knt++)
      {
         sifre[knt]='c';
      }
   }
   if((sifre[36]!='c') && (sifre[36]!='d'))
   {
      for(int knt=36;knt<45;knt++)
      {
         sifre[knt]='c';
      }
   }

   if((sifre[45]!='c') && (sifre[45]!='d'))
   {
      for(int knt=45;knt<54;knt++)
      {
         sifre[knt]='c';
      }
   }
   
   if((sifre[54]!='c') && (sifre[54]!='d'))
   {
      for(int knt=54;knt<63;knt++)
      {
         sifre[knt]='c';
      }
   }
   
   if((sifre[63]!='c') && (sifre[63]!='d'))
   {
      for(int knt=63;knt<72;knt++)
      {
         sifre[knt]='c';
      }
   }
   
   if((sifre[72]!='c') && (sifre[72]!='d'))
   {
      for(int knt=72;knt<81;knt++)
      {
         sifre[knt]='c';
      }
   }
   
   if((sifre[81]!='c') && (sifre[81]!='d'))
   {
      for(int knt=81;knt<90;knt++)
      {
         sifre[knt]='c';
      }
   }
   
   if((sifre[90]!='c') && (sifre[90]!='d'))
   {
      for(int knt=90;knt<99;knt++)
      {
         sifre[knt]='c';
      }
   }
   
   if((sifre[99]!='c') && (sifre[99]!='d'))
   {
      for(int knt=99;knt<108;knt++)
      {
         sifre[knt]='c';
      }
   }
   
   if((sifre[108]!='c') && (sifre[108]!='d'))
   {
      for(int knt=108;knt<117;knt++)
      {
         sifre[knt]='c';
      }
   }
   if((sifre[117]!='c') && (sifre[117]!='d'))
   {
      for(int knt=117;knt<126;knt++)
      {
         sifre[knt]='c';
      }
   }

}















