#include <LiquidCrystal.h>


#define VITESSE_PAC 150
#define VITESSE_FANT 2000
#define MAXX 15
#define MAXY 1

#define btnRight     0
#define btnUp        1
#define btnDown      2
#define btnLeft      3
#define btnSelect    4
#define btnNone      5

void(* resetFunc) (void) = 0;
LiquidCrystal lcd(8, 9, 4, 5, 6, 7); 



byte pacman[8] = {
  B00000,
  B00000,
  B01110,
  B11011,
  B11100,
  B01110,
  B00000,
  B00000
};

byte fantome[8] = {
  B00000,
  B00000,
  B01110,
  B10101,
  B11111,
  B11111,
  B10101,
  B00000
};

byte point[8] = {
  B00000,
  B00000,
  B00000,
  B01110,
  B01110,
  B00000,
  B00000,
  B00000
};


byte points[MAXX+1][MAXY+1];

int xpac=2;
int ypac=1; 
int xfant=15;
int yfant=0;
byte light=true; 
long keystruck=0;
long tracking=0;
byte partieEnCours=true;
byte vide=false;

byte level=0;
int score=0;

void move(int x,int y) 
{
  int oldx=xpac;
  int oldy=ypac;
  if (((xpac+x)>=0)&((xpac+x)<=MAXX)) xpac=xpac+x; 
  if (((ypac+y)>=0)&((ypac+y)<=MAXY)) ypac=ypac+y;
  lcd.setCursor(xpac,ypac);
  lcd.write(byte(0)); 
  lcd.setCursor(oldx,oldy); 
  if ((xpac!=oldx)||(ypac!=oldy)) lcd.print(" "); 
  if(points[xpac][ypac]){
    points[xpac][ypac]=false; 
    score++;
  }
  vide=true;
  for (int i=0; i<=MAXX; i=i+1)
    for (int j=0; j<=MAXY; j=j+1)
      if (points[i][j])  vide=false;
  if ((vide)&&(partieEnCours)) win();
}

void gameOver(){
  lcd.setCursor(0, 0);
  lcd.print("***Game Over****");
  lcd.setCursor(0, 1);
  lcd.print("***");
  lcd.print(score);
  lcd.print("***"); 
  delay(2000);
  resetFunc();
}

void win()
{
  level++;
  lcd.setCursor(0, 0); 
  lcd.print("*** Next level ***");
  lcd.setCursor(0, 1); 
  lcd.print("*** ");
  lcd.print(level,DEC);
  lcd.print(" ***");
  delay(2000); 
  initLevel(); 
}

void pursuit() 
{
  int oldx=xfant;
  int oldy=yfant;
  if (yfant<ypac) yfant=yfant+1;
  else if (yfant>ypac) yfant=yfant-1;
  else if (xfant<xpac) xfant=xfant+1;
  else if (xfant>xpac) xfant=xfant-1;
  lcd.setCursor(xfant,yfant); 
  lcd.write(1);
  lcd.setCursor(oldx,oldy); 
  if ((oldx!=xfant)||(oldy!=yfant)) 
  {
    if (points[oldx][oldy]) lcd.write(2); 
    else lcd.print(" "); 
  }
}


void initLevel(){
  for (int i=0; i<=MAXX; i=i+1)
    for (int j=0; j<=MAXY; j=j+1){
      points[i][j]=true; 
      lcd.setCursor(i-1, j-1);
      lcd.write(2);
    }
  lcd.setCursor(xpac,ypac); 
  lcd.write(byte(0)); 
  lcd.setCursor(xfant,yfant);
  lcd.write(1); 
  tracking=millis();
  vide=false;
}

void setup() {
  Serial.begin(9600);

  lcd.begin(16, 2);
  lcd.createChar(0, pacman); 
  lcd.createChar(1, fantome); 
  lcd.createChar(2, point); 
  lcd.setCursor(0, 0);
  lcd.print("Pacman!"); 
  delay (5000);
  initLevel(); 
}

void loop() {
  int thisChar = Serial.read();
  switch (thisChar)
  {
  case 'r':
    lcd.scrollDisplayRight();
    break;
  case 'l':
    lcd.scrollDisplayLeft();
    break;
  }
  if ((thisChar>'a')&(thisChar<'z'))
  {
    lcd.setCursor(1,1);
    lcd.write(thisChar);
  }
  if (millis()-keystruck>VITESSE_PAC) 
  {
    int joy=getKey();
    switch (joy)
    {
    case btnNone:
      break;
    case btnLeft:
      Serial.print("Pacman move à gauche.\n"); 
      Serial.print(keystruck);
      move(-1,0);
      keystruck=millis();
      break;
    case btnRight:
      Serial.print("Pacman move à droite\n");
      move(1,0);
      keystruck=millis();
      break;
    case btnUp:
      Serial.print("Pacman move en haut\n");
      move(0,-1);
      keystruck=millis();
      break;
    case btnDown:
      Serial.print("Pacman move en bas\n");
      move(0,1);
      keystruck=millis();
      break;
    default:
      Serial.print(joy); 
      keystruck=millis(); 
    }; 
  };
  if (millis()-tracking>VITESSE_FANT/(level+1)+10)
  {
    pursuit();
    tracking=millis();
  }
  if ((xpac==xfant)&&(ypac==yfant)&&(partieEnCours)) 
  {
    gameOver();
  }
}


int getKey() {
  int b = analogRead(A0);
  if (b > 1000) return btnNone;
  delay(8);
  if (b < 50) return btnRight;
  if (b < 180) return btnUp;
  if (b < 330) return btnDown;
  if (b < 520) return btnLeft;
  if (b < 700) return btnSelect;
}
