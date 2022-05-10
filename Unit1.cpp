#include <vcl.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#pragma hdrstop

#include "Unit1.h"

#pragma package(smart_init)
#pragma resource "*.dfm"

#define ENCRYPT 1
#define DECRYPT 0

#define BUFFER_SIZE 2048

typedef struct {
  uint8_t key [BUFFER_SIZE];
  uint8_t data[BUFFER_SIZE];
  uint8_t mix [BUFFER_SIZE * 3];
} CRYPT_CTX;

uint32_t gamma = 0;
uint32_t temp  = 0;
uint32_t n     = 0;

TForm1 *Form1;
CRYPT_CTX * ctx = NULL;

void init(uint8_t * key, size_t klen) {
  size_t i;

  for (i = 0; i < klen; ++i) {
    temp += key[i] * (i + 1);
  }
}

int enmix(uint8_t * in, uint8_t * out, size_t ilen, bool format) {
  size_t i, j;

  for (i = 0, j = 0; i < ilen; ++i) {
    if (in[i] >= 'A' && in[i] <= 'Z') {
      out[j] = in[i];
      ++j;
      ++n;
    }
    else
    if (in[i] >= 'a' && in[i] <= 'z') {
      out[j] = in[i] - 32;
      ++j;
      ++n;
    }
    else {
      continue;
    }

    if (format == true) {
      if (0 == (n % 5)) {
        out[j] = ' ';
        ++j;
      }

      if (50 == n) {
        out[j] = '\n';
        ++j;
        n = 0;
      }
    }
  }

  if (format == true)
    out[j] = '\n';
    
  return j;
}

void crypt(uint8_t * data, uint8_t * key, uint32_t dlen, uint32_t klen, int tumbler) {
  if (NULL == data || NULL == key || 0 == dlen || 0 == klen)
    return;

  uint32_t i;

  for (i = 0; i < dlen; ++i) {
    if (data[i] >= 'a' && data[i] <= 'z') {
      data[i] -= 32;
    }

    if (data[i] >= 'A' && data[i] <= 'Z') {

      temp  += key[gamma % klen];
      temp  += key[temp  % klen];

      temp  += gamma + 1;
      gamma += temp  - 1;

      temp  = (temp % 26) + 'A';

      if (ENCRYPT == tumbler)
        data[i] = ((data[i]  + temp) % 26) + 'A';
      else
        data[i] = (((data[i] - temp) + 26) % 26) + 'A';

    }
  }
}

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCreate(TObject *Sender)
{
  ctx = (CRYPT_CTX *)malloc(sizeof(CRYPT_CTX));

  if (NULL == ctx) {
    ShowMessage("Не удалось выделить память!");
    Form1->Close();
  }
}

int text_crypt(int tumbler, bool format) {
  int ret_s = 0;
  int position = 0;
  int real = 0;

  int klen = strlen(Form1->Memo1->Text.c_str());
  int dlen = strlen(Form1->Memo2->Text.c_str());

  if (Form1->Memo1->Text == "") {
    ShowMessage("Ключ не введен!");
    return -1;
  }

  if (Form1->Memo2->Text == "") {
    ShowMessage("Текст не введен!");
    return -1;
  }

  if (klen < 0 || klen > BUFFER_SIZE) {
    klen = BUFFER_SIZE;
  }

  memcpy(ctx->key, Form1->Memo1->Text.c_str(), klen);
  
  init(ctx->key, klen);

  Form1->Memo3->Clear();

  while(dlen > 0) {
    real = (dlen > BUFFER_SIZE ? BUFFER_SIZE : dlen);

    memcpy(ctx->data, Form1->Memo2->Text.c_str() + position, real);

    position += real;

    if (tumbler) {
      ret_s = enmix(ctx->data, ctx->mix, real, format);
    }

    crypt(tumbler ? ctx->mix : ctx->data, ctx->key,
          tumbler ? ret_s    : real, klen, tumbler);

    if (dlen < BUFFER_SIZE) {
      ctx->data[real]  = 0x00;
      ctx->mix [ret_s] = 0x00;
    }

    Form1->Memo3->Text =
      Form1->Memo3->Text + AnsiString((char *)(tumbler ? ctx->mix : ctx->data));

    dlen -= real;
  }

  memset(ctx, 0x00, sizeof(CRYPT_CTX));

  temp  = 0;
  gamma = 0;
  n = 0;

  return 0;
}

void tumblers_init(void) {
  if (Form1->Edit1->Text != "") {
    gamma = atol(Form1->Edit1->Text.c_str());
  }

  if (Form1->Edit2->Text != "") {
    temp = atol(Form1->Edit2->Text.c_str());
  }
}

//---------------------------------------------------------------------------
void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
  if (ctx != NULL)
    free(ctx);        
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormDestroy(TObject *Sender)
{
  if (ctx != NULL)
    free(ctx);          
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
  tumblers_init();

  if (Form1->XOR->Checked == True) {
    text_crypt(1, false);
  }
  else {
    text_crypt(1, true);
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender)
{
  tumblers_init();

  if (Form1->Sapphire->Checked == True) {
    text_crypt(0, true);
  }
  else {
    text_crypt(0, false);
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button3Click(TObject *Sender)
{
 Form1->Memo2->Clear();        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button4Click(TObject *Sender)
{
 Form1->Memo3->Clear();          
}
//---------------------------------------------------------------------------



