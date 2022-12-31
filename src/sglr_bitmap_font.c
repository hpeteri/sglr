#include "sglr_bitmap_font.h"
#include "sglr_texture.h"

sglr_BitmapFont sglr_make_bitmap_font_builtin(){

  static sglr_BitmapFont font;
  
  if(font.texture.id)
    return font;



  // === 0 - 127 ===
  //
  //
  //    ! " / $ % & ' ( ) * + , - . /
  //  0 1 2 3 4 5 6 7 8 9 : ; < = > ?
  //  @ A B C D E F G H I J K L M N O
  //  P Q R S T U V W X Y Z [ \ ] ^ _
  //  ` a b c d e f g h i j k l m n o
  //  p q r s t u v w x y z { | } ~ 
  //  === 128 - 255 ===
  //  utf-8 extension
  //  
  //  
  //    ¡ ¢ £ ¤ ¥ ¦ § ¨ © ª « ¬   ® ¯
  //  ° ± ² ³ ´ µ ¶ · ¸ ¹ º » ¼ ½ ¾ ¿
  //  À Á Â Ã Ä Å Æ Ç È É Ê Ë Ì Í Î Ï
  //  Ð Ñ Ò Ó Ô Õ Ö × Ø Ù Ú Û Ü Ý Þ ß
  //  à á â ã ä å æ ç è é ê ë ì í î ï
  //  ð ñ ò ó ô õ ö ø ù ú û ü ý þ ÿ  



  char atlas_bits[8 * 16][16] = {
    // null
    0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,
    0b01111110, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,
    0b01100110, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,
    0b01011010, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,
    0b01011010, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,
    0b01100110, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,
    0b01111110, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,
    0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,
      
    0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,
    0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,
    0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,
    0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,
    0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,
    0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,
    0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,
    0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,

    //          !           "           #           $          %            &           '           (           )           *           +           ,           -           .           /
    0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00001000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,
    0b00000000, 0b00010000, 0b01101100, 0b00100100, 0b00111100, 0b00100000, 0b00111100, 0b00100000, 0b00010000, 0b01000000, 0b00000000, 0b00010000, 0b00000000, 0b00000000, 0b00000000, 0b00000010,
    0b00000000, 0b00010000, 0b01101100, 0b01111110, 0b01001010, 0b01010100, 0b01000000, 0b01000000, 0b00100000, 0b00100000, 0b00101000, 0b00010000, 0b00000000, 0b00000000, 0b00000000, 0b00000100,
    0b00000000, 0b00010000, 0b01001000, 0b00100100, 0b00101000, 0b00101000, 0b00111100, 0b00000000, 0b01000000, 0b00010000, 0b01010100, 0b01111100, 0b00000000, 0b01111100, 0b00000000, 0b00001000,
    0b00000000, 0b00010000, 0b00000000, 0b00100100, 0b00001100, 0b00010100, 0b01000010, 0b00000000, 0b01000000, 0b00010000, 0b00101000, 0b00010000, 0b00000000, 0b00000000, 0b00000000, 0b00010000,
    0b00000000, 0b00000000, 0b00000000, 0b01111110, 0b01001010, 0b00101010, 0b01000010, 0b00000000, 0b01000000, 0b00010000, 0b00000000, 0b00010000, 0b00010000, 0b00000000, 0b00010000, 0b00100000,
    0b00000000, 0b00010000, 0b00000000, 0b00100100, 0b00111100, 0b00000100, 0b00111100, 0b00000000, 0b00100000, 0b00100000, 0b00000000, 0b00000000, 0b00010000, 0b00000000, 0b00010000, 0b01000000,
    0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00001000, 0b00000000, 0b00000000, 0b00000000, 0b00010000, 0b01000000, 0b00000000, 0b00000000, 0b01100000, 0b00000000, 0b00000000, 0b00000000,
    
    //0         1           2           3           4           5           6           7           8           9           :           ;            <           =          >           ?
    0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,
    0b00111100, 0b00110000, 0b00111100, 0b00111110, 0b00001100, 0b01111110, 0b01111110, 0b01111110, 0b00111100, 0b01111100, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00111100,
    0b01000110, 0b00010000, 0b01000010, 0b00000010, 0b00010100, 0b01000000, 0b10000000, 0b00000100, 0b01000010, 0b10000010, 0b00100000, 0b00100000, 0b00001000, 0b00000000, 0b00010000, 0b01000010,
    0b01001010, 0b00010000, 0b00000010, 0b00011100, 0b00100100, 0b01111100, 0b10111100, 0b00111100, 0b00111100, 0b10000010, 0b00000000, 0b00000000, 0b00010000, 0b01111110, 0b00001000, 0b00001100,
    0b01010010, 0b00010000, 0b00111000, 0b00000010, 0b01111110, 0b00000010, 0b11000010, 0b00010000, 0b01000010, 0b01111110, 0b00000000, 0b00000000, 0b00100000, 0b00000000, 0b00000100, 0b00010000,
    0b01100010, 0b00010000, 0b01000000, 0b01000010, 0b00000100, 0b01000010, 0b10000010, 0b00100000, 0b01000010, 0b00000010, 0b00100000, 0b00100000, 0b00010000, 0b01111110, 0b00001000, 0b00000000,
    0b00111100, 0b01111100, 0b01111110, 0b00111100, 0b00000100, 0b00111100, 0b01111100, 0b01000000, 0b00111100, 0b01111100, 0b00000000, 0b00100000, 0b00001000, 0b00000000, 0b00010000, 0b00010000,
    0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b01000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,
                                                                                                                  
    //@         A           B           C           D           E           F           G           H           I           J           K           L           M           N           O
    0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,
    0b00111110, 0b00111100, 0b01111110, 0b00111100, 0b01111100, 0b01111110, 0b01111110, 0b00111110, 0b01000010, 0b01111100, 0b00111000, 0b01000100, 0b01000000, 0b01100110, 0b01000010, 0b00111100,
    0b01000010, 0b01000010, 0b01000001, 0b01000010, 0b01000010, 0b01000000, 0b01000000, 0b01000000, 0b01000010, 0b00010000, 0b00001000, 0b01001000, 0b01000000, 0b01011010, 0b01100010, 0b01000010,
    0b01011110, 0b01111110, 0b01111110, 0b01000000, 0b01000010, 0b01111110, 0b01111110, 0b01000110, 0b01111110, 0b00010000, 0b00001000, 0b01110000, 0b01000000, 0b01011010, 0b01010010, 0b01000010,
    0b01010010, 0b01000010, 0b01000001, 0b01000000, 0b01000010, 0b01000000, 0b01000000, 0b01000010, 0b01000010, 0b00010000, 0b00001000, 0b01010000, 0b01000000, 0b01000010, 0b01001010, 0b01000010,
    0b01011110, 0b01000010, 0b01000001, 0b01000010, 0b01000010, 0b01000000, 0b01000000, 0b01000010, 0b01000010, 0b00010000, 0b01001000, 0b01001000, 0b01000000, 0b01000010, 0b01000110, 0b01000010,
    0b01000000, 0b01000010, 0b01111110, 0b00111100, 0b01111100, 0b01111110, 0b01000000, 0b00111100, 0b01000010, 0b01111100, 0b00110000, 0b01000100, 0b01111110, 0b01000010, 0b01000010, 0b00111100,
    0b00111110, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,

    //P         Q           R           S           T           U           V           W           X           Y           Z           [           \           ]           ^           
    0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,
    0b01111100, 0b00111100, 0b01111100, 0b00111100, 0b01111110, 0b01000010, 0b01000010, 0b01000010, 0b01000010, 0b01000100, 0b01111110, 0b01111000, 0b01000000, 0b01111000, 0b00010000, 0b00000000,
    0b01000010, 0b01000010, 0b01000010, 0b01000010, 0b00010000, 0b01000010, 0b01000010, 0b01000010, 0b01000010, 0b01000100, 0b00000100, 0b01000000, 0b00100000, 0b00001000, 0b00101000, 0b00000000,
    0b01111100, 0b01000010, 0b01111100, 0b00110000, 0b00010000, 0b01000010, 0b01000010, 0b01000010, 0b00100100, 0b00101000, 0b00001000, 0b01000000, 0b00010000, 0b00001000, 0b01000100, 0b00000000,
    0b01000000, 0b01001010, 0b01001000, 0b00001100, 0b00010000, 0b01000010, 0b01000010, 0b01000010, 0b00011000, 0b00010000, 0b00010000, 0b01000000, 0b00001000, 0b00001000, 0b00000000, 0b00000000,
    0b01000000, 0b01001010, 0b01000100, 0b01000010, 0b00010000, 0b01000010, 0b00100100, 0b01011010, 0b00100100, 0b00010000, 0b00100000, 0b01000000, 0b00000100, 0b00001000, 0b00000000, 0b00000000,
    0b01000000, 0b00111100, 0b01000010, 0b00111100, 0b00010000, 0b00111100, 0b00011000, 0b00100100, 0b01000010, 0b00010000, 0b01111110, 0b01000000, 0b00000010, 0b00001000, 0b00000000, 0b00000000,
    0b00000000, 0b00000010, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b01111000, 0b00000000, 0b01111000, 0b00000000, 0b11111111,

    //`         a           b           c           d           e           f           g           h           i           j           k           l           m           n           o
    0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,
    0b01100000, 0b00000000, 0b01000000, 0b00000000, 0b00000010, 0b00000000, 0b00001100, 0b00111100, 0b01000000, 0b00001000, 0b00001000, 0b01001000, 0b01100000, 0b00000000, 0b01000000, 0b00000000,
    0b00010000, 0b00111000, 0b01000000, 0b00000000, 0b00000010, 0b00111100, 0b00010000, 0b01000100, 0b01000000, 0b00000000, 0b00000000, 0b01010000, 0b00100000, 0b00100100, 0b01111100, 0b00111100,
    0b00000000, 0b00000100, 0b01000000, 0b01111000, 0b00000010, 0b01000010, 0b01111100, 0b01000100, 0b01111000, 0b00011000, 0b00011000, 0b01100000, 0b00100000, 0b01011010, 0b01000010, 0b01000010,
    0b00000000, 0b00111100, 0b01111100, 0b10000000, 0b00111110, 0b01111110, 0b00010000, 0b00111100, 0b01000100, 0b00001000, 0b00001000, 0b01010000, 0b00100000, 0b01011010, 0b01000010, 0b01000010,
    0b00000000, 0b01000100, 0b01000010, 0b10000000, 0b01000010, 0b01000000, 0b00010000, 0b00000100, 0b01000100, 0b00001000, 0b00001000, 0b01001000, 0b00100000, 0b01000010, 0b01000010, 0b01000010,
    0b00000000, 0b00111100, 0b01111100, 0b01111000, 0b00111110, 0b00111110, 0b00010000, 0b00000100, 0b01000100, 0b00111100, 0b00001000, 0b01000100, 0b00110000, 0b01000010, 0b01000010, 0b00111100,
    0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00111000, 0b00000000, 0b00000000, 0b00111000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,

    //p         q           r           s           t           u           v           w           x           y           z           {           |           }           ~          
    0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,
    0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00010000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00011100, 0b00010000, 0b00111000, 0b00000010, 0b00000000,
    0b01111100, 0b00111110, 0b01011100, 0b00111110, 0b01111100, 0b01000010, 0b01000010, 0b01000010, 0b01000010, 0b01000010, 0b01111110, 0b00100000, 0b00010000, 0b00000100, 0b00111100, 0b00000000,
    0b01000010, 0b01000010, 0b01100010, 0b01000000, 0b00010000, 0b01000010, 0b01000010, 0b01000010, 0b00100100, 0b01000010, 0b00000100, 0b00100000, 0b00010000, 0b00000100, 0b01000000, 0b00000000,
    0b01111100, 0b00111110, 0b01000000, 0b00111100, 0b00010000, 0b01000010, 0b01000010, 0b01000010, 0b00011000, 0b01000010, 0b00011000, 0b01000000, 0b00010000, 0b00000010, 0b00000000, 0b00000000,
    0b01000000, 0b00000010, 0b01000000, 0b00000010, 0b00010000, 0b01000110, 0b00100100, 0b01011010, 0b00100100, 0b00111110, 0b00100000, 0b00100000, 0b00010000, 0b00000100, 0b00000000, 0b00000000,
    0b01000000, 0b00000010, 0b01000000, 0b01111100, 0b00001100, 0b00111010, 0b00011000, 0b00100100, 0b01000010, 0b00000010, 0b01111110, 0b00100000, 0b00010000, 0b00000100, 0b00000000, 0b00000000,
    0b01000000, 0b00000010, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00011100, 0b00000000, 0b00011100, 0b00010000, 0b00111000, 0b00000000, 0b00000000,

    0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,
    0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,
    0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,
    0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,
    0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,
    0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,
    0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,
    0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,

    0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,
    0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,
    0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,
    0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,
    0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,
    0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,
    0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,
    0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,

    //          ¡           ¢           £           ¤           ¥           ¦           §           ¨           ©           ª           «           ¬                       ®           ¯
    0b00000000, 0b00000000, 0b00001000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,
    0b00000000, 0b00100000, 0b00111100, 0b00011100, 0b00000000, 0b00000000, 0b00000000, 0b01111100, 0b01010000, 0b01111110, 0b01011100, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,
    0b00000000, 0b00000000, 0b01001000, 0b00100000, 0b01000100, 0b01000100, 0b00010000, 0b01000000, 0b01010000, 0b01001110, 0b00000100, 0b00000000, 0b01111100, 0b00000000, 0b00110000, 0b01110000,
    0b00000000, 0b00100000, 0b01001000, 0b00100000, 0b00111000, 0b00101000, 0b00010000, 0b01010000, 0b00000000, 0b01010010, 0b00011100, 0b00100100, 0b00000100, 0b00000000, 0b00101000, 0b00000000,
    0b00000000, 0b00100000, 0b01001000, 0b01111000, 0b00101000, 0b00010000, 0b00000000, 0b01111100, 0b00000000, 0b01001110, 0b01100100, 0b01001000, 0b00000100, 0b00000000, 0b00100100, 0b00000000,
    0b00000000, 0b00100000, 0b00011100, 0b00100000, 0b00111000, 0b00111000, 0b00010000, 0b00010100, 0b00000000, 0b01000010, 0b00000000, 0b00100100, 0b00000000, 0b00000000, 0b00000000, 0b00000000,
    0b00000000, 0b00100000, 0b00001000, 0b01111110, 0b01000100, 0b00010000, 0b00010000, 0b01111000, 0b00000000, 0b01111110, 0b01111100, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,
    0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,

    //°         ±           ²           ³           ´           µ           ¶           ·           ¸           ¹           º           »           ¼           ½           ¾           ¿
    0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,
    0b00010000, 0b00010000, 0b00110000, 0b01100000, 0b00000100, 0b00000000, 0b00110100, 0b01000000, 0b00000000, 0b01000000, 0b00100000, 0b00000000, 0b01000000, 0b01000000, 0b01100000, 0b00100000,
    0b00101000, 0b00111000, 0b00001000, 0b00010000, 0b00001000, 0b01000010, 0b01110100, 0b00000000, 0b00000000, 0b01000000, 0b01010000, 0b01000100, 0b01000000, 0b01000000, 0b00010000, 0b00000000,
    0b00010000, 0b00010000, 0b00010000, 0b01100000, 0b00000000, 0b01000010, 0b00110100, 0b00000000, 0b00000000, 0b00000000, 0b00100000, 0b00100010, 0b00000000, 0b00001000, 0b01100000, 0b00100000,
    0b00000000, 0b00000000, 0b00111100, 0b00010000, 0b00000000, 0b01000010, 0b00010100, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b01000100, 0b00010100, 0b00010100, 0b00010100, 0b00100000,
    0b00000000, 0b01111100, 0b00000000, 0b01100000, 0b00000000, 0b01000110, 0b00010100, 0b00000000, 0b00100000, 0b00000000, 0b01110000, 0b00000000, 0b00011100, 0b00001000, 0b00011100, 0b01000100,
    0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b01111010, 0b00010100, 0b00000000, 0b01000000, 0b00000000, 0b00000000, 0b00000000, 0b00000100, 0b00011110, 0b00000100, 0b00111000,
    0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b01000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,

    //À         Á           Â           Ã           Ä           Å           Æ           Ç           È           É           Ê           Ë           Ì           Í           Î           Ï
    0b00001000, 0b00010000, 0b00111100, 0b00111100, 0b00100100, 0b00111100, 0b00000000, 0b00000000, 0b00010000, 0b00001000, 0b00011000, 0b00100100, 0b00010000, 0b00010000, 0b00111000, 0b00101000,
    0b00000100, 0b00100000, 0b01000010, 0b00000000, 0b00000000, 0b00100100, 0b00111110, 0b00111100, 0b00001000, 0b00010000, 0b00100100, 0b00000000, 0b00001000, 0b00100000, 0b01000100, 0b00000000,
    0b00111100, 0b00111100, 0b00111100, 0b00111100, 0b00111100, 0b00111100, 0b01001000, 0b01000010, 0b01111110, 0b01111110, 0b01111110, 0b01111110, 0b01111100, 0b01111100, 0b01111100, 0b01111100,
    0b01000010, 0b01000010, 0b01000010, 0b01000010, 0b01000010, 0b01000010, 0b01001000, 0b01000000, 0b01000000, 0b01000000, 0b01000000, 0b01000000, 0b00010000, 0b00010000, 0b00010000, 0b00010000,
    0b01111110, 0b01111110, 0b01111110, 0b01111110, 0b01111110, 0b01111110, 0b01111110, 0b01000000, 0b01111110, 0b01111110, 0b01111110, 0b01111110, 0b00010000, 0b00010000, 0b00010000, 0b00010000,
    0b01000010, 0b01000010, 0b01000010, 0b01000010, 0b01000010, 0b01000010, 0b01001000, 0b01000010, 0b01000000, 0b01000000, 0b01000000, 0b01000000, 0b00010000, 0b00010000, 0b00010000, 0b00010000,
    0b01000010, 0b01000010, 0b01000010, 0b01000010, 0b01000010, 0b01000010, 0b01001110, 0b00111100, 0b01111110, 0b01111110, 0b01111110, 0b01111110, 0b01111100, 0b01111100, 0b01111100, 0b01111100,
    0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00001000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,

    //Ð         Ñ           Ò           Ó           Ô           Õ           Ö           ×           Ø           Ù           Ú           Û           Ü           Ý           Þ           ß
    0b00000000, 0b01111100, 0b00010000, 0b00001000, 0b00010000, 0b00111100, 0b00100100, 0b00000000, 0b00000000, 0b00010000, 0b00010000, 0b00011000, 0b00100100, 0b00000000, 0b00000000, 0b00000000,
    0b01111100, 0b00000000, 0b00001000, 0b00010000, 0b00101000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00001000, 0b00100000, 0b00100100, 0b00000000, 0b01010100, 0b01000000, 0b00110000,
    0b01000010, 0b01100010, 0b00111100, 0b00111100, 0b00111100, 0b00111100, 0b00111100, 0b00000000, 0b00111100, 0b00000000, 0b00000000, 0b00000000, 0b01000010, 0b01000100, 0b01111000, 0b01001000,
    0b11110010, 0b01010010, 0b01000010, 0b01000010, 0b01000010, 0b01000010, 0b01000010, 0b00101000, 0b01001010, 0b01000010, 0b01000010, 0b01000010, 0b01000010, 0b00101000, 0b01000100, 0b01110000,
    0b01000010, 0b01001010, 0b01000010, 0b01000010, 0b01000010, 0b01000010, 0b01000010, 0b00010000, 0b01010010, 0b01000010, 0b01000010, 0b01000010, 0b01000010, 0b00010000, 0b01000100, 0b01001000,
    0b01000010, 0b01000110, 0b01000010, 0b01000010, 0b01000010, 0b01000010, 0b01000010, 0b00101000, 0b01100010, 0b01000010, 0b01000010, 0b01000010, 0b01000010, 0b00010000, 0b01111000, 0b01000100,
    0b01111100, 0b01000010, 0b00111100, 0b00111100, 0b00111100, 0b00111100, 0b00111100, 0b00000000, 0b00111100, 0b00111100, 0b00111100, 0b00111100, 0b00111100, 0b00010000, 0b01000000, 0b01111100,
    0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,

    //à         á           â           ã           ä           å           æ           ç           è           é           ê           ë           ì           í           î           ï
    0b00010000, 0b00001000, 0b00111100, 0b00111100, 0b00100100, 0b00011000, 0b00000000, 0b00000000, 0b00010000, 0b00001000, 0b00111100, 0b00100100, 0b00010000, 0b00000100, 0b00001000, 0b00000000,
    0b00001000, 0b00010000, 0b01000010, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00001000, 0b00010000, 0b01000010, 0b00000000, 0b00001000, 0b00001000, 0b00010100, 0b00010100,
    0b00111000, 0b00111000, 0b00111000, 0b00111000, 0b00111000, 0b00111000, 0b00111110, 0b00000000, 0b00111100, 0b00111100, 0b00111100, 0b00111100, 0b00000000, 0b00000000, 0b00000000, 0b00000000,
    0b00000100, 0b00000100, 0b00000100, 0b00000100, 0b00000100, 0b00000100, 0b00001010, 0b01111000, 0b01000010, 0b01000010, 0b01000010, 0b01000010, 0b00011000, 0b00011000, 0b00011000, 0b00011000,
    0b00111100, 0b00111100, 0b00111100, 0b00111100, 0b00111100, 0b00111100, 0b00111110, 0b10000000, 0b01111110, 0b01111110, 0b01111110, 0b01111110, 0b00001000, 0b00001000, 0b00001000, 0b00001000,
    0b01000100, 0b01000100, 0b01000100, 0b01000100, 0b01000100, 0b01000100, 0b01001000, 0b10000000, 0b01000000, 0b01000000, 0b01000000, 0b01000000, 0b00001000, 0b00001000, 0b00001000, 0b00001000,
    0b00111100, 0b00111100, 0b00111100, 0b00111100, 0b00111100, 0b00111100, 0b00111110, 0b01111000, 0b00111110, 0b00111110, 0b00111110, 0b00111110, 0b00111100, 0b00111100, 0b00111100, 0b00111100,
    0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00100000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,

    //ð         ñ           ò           ó           ô           õ           ö           ø           ù           ú           û           ü           ý           þ           ÿ  
    0b01101100, 0b01100000, 0b00010000, 0b00001000, 0b00011000, 0b00010010, 0b00100100, 0b00000000, 0b00000000, 0b00000000, 0b00011000, 0b00100100, 0b00000000, 0b00000000, 0b00000000, 0b00000000,
    0b00010010, 0b00011000, 0b00001000, 0b00010000, 0b00100100, 0b01101100, 0b00000000, 0b00000000, 0b00010000, 0b00001000, 0b00100100, 0b00000000, 0b00001000, 0b01000000, 0b00100100, 0b00000000,
    0b00000000, 0b01000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00001000, 0b00010000, 0b00000000, 0b01000010, 0b00010000, 0b01110000, 0b00000000, 0b00000000,
    0b00111100, 0b01111100, 0b00111100, 0b00111100, 0b00111100, 0b00111100, 0b00111100, 0b00111100, 0b01000010, 0b01000010, 0b01000010, 0b01000010, 0b01000010, 0b01001000, 0b01000010, 0b00000000,
    0b01000010, 0b01000010, 0b01000010, 0b01000010, 0b01000010, 0b01000010, 0b01000010, 0b01001010, 0b01000010, 0b01000010, 0b01000010, 0b01000010, 0b01000010, 0b01001000, 0b01000010, 0b00000000,
    0b01000010, 0b01000010, 0b01000010, 0b01000010, 0b01000010, 0b01000010, 0b01000010, 0b01010010, 0b01000110, 0b01000110, 0b01000110, 0b01000110, 0b00111110, 0b01110000, 0b00111110, 0b00000000,
    0b00111100, 0b01000010, 0b00111100, 0b00111100, 0b00111100, 0b00111100, 0b00111100, 0b00111100, 0b00111010, 0b00111010, 0b00111010, 0b00111010, 0b00000010, 0b01000000, 0b00000010, 0b00000000,
    0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00011100, 0b00000000, 0b00011100, 0b00000000,
    

  };
  
  uint8_t font_pixels[256][128];
  int pad = 2;
  memset(font_pixels, 0, sizeof(font_pixels));
  
  for(int row = 0; row < 16; row++){
    for(int i = 0; i < 8; i++){
      for(int column = 0; column < 16; column++){
        uint8_t c = atlas_bits[row * 8 + i][column];
        
        for(int b = 0; b < 8; b++){

          if(c & (1 << (7 - b))){
            font_pixels[row * (8 + pad) + i][column * 8 + b] = 0xff;
            //printf("#");
          }
          //else{ printf(" "); }

        }
        //printf("|");
      }
      //printf("\n");
    }
    

    //printf("================");
    //printf("================"); 
    //printf("================");
    //printf("================"); 
    //printf("================"); 
    //printf("================"); 
    //printf("================"); 
    //printf("================"); 
    //printf("================");  
    //printf("\n");  
    
  }
  
  font.texture = sglr_make_texture_2d_red(128, 256, font_pixels);
  sglr_set_texture_debug_name(font.texture, "bitmap_font");

  sglr_set_texture(font.texture);
  
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_A, GL_RED);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_R, GL_ONE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_G, GL_ONE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_B, GL_ONE);
  
  sglr_check_error();
  sglr_unset_texture(font.texture.type);

  return font;
}

