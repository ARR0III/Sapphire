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
  uint8_t data[BUFFER_SIZE + 1];
  uint8_t mix [BUFFER_SIZE * 4];
} CRYPT_CTX;

uint32_t gamma = 0;
uint32_t temp  = 0;
uint32_t n     = 0;

TForm1 *Form1;
CRYPT_CTX * ctx = NULL;

void init(uint8_t * key, size_t klen) {
  uint32_t i;

  for (i = 0; i < klen; ++i) {
    temp += ((uint32_t)key[i]) * (i + 1);
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

    if (true == format) {
      if (0 == (n % 6)) {
        out[j] = ' ';
        ++j;
      }

      if (54 == n) {
        out[j]     = 0x0D;
        out[j + 1] = 0x0A;
        j += 2;
        n = 0;
      }
    }
  }
  return j;
}

void crypt(uint8_t * data, uint8_t * key,
           uint32_t dlen, uint32_t klen, int tumbler) {
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

  uint8_t * memory = NULL;

  int ret_s           = 0;
  int memory_position = 0;
  int position        = 0;
  int real            = 0;

  int klen = strlen(Form1->Memo1->Text.c_str());
  int dlen = strlen(Form1->Memo2->Text.c_str());

  memory = (uint8_t *)malloc(dlen * 4);

  if (memory == NULL) {
    ShowMessage("Не удалось выделить память!");
    return -2;
  }

  short real_percent = 0;
  short past_percent = 0;
  
  float div = (float)(dlen) / 100.0;

  Form1->ProgressBar1->Min = 0;
  Form1->ProgressBar1->Max = 100;

  ctx->data[BUFFER_SIZE] = 0x00;
  ctx->mix [BUFFER_SIZE * 4] = 0x00;

  if (Form1->Memo1->Text == "") {
    ShowMessage("Ключ не введен!");
    free(memory);
    return -1;
  }

  if (Form1->Memo2->Text == "") {
    ShowMessage("Текст не введен!");
    free(memory);
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

    if (tumbler) {
      ret_s = enmix(ctx->data, ctx->mix, real, format);
    }

    crypt(tumbler ? ctx->mix : ctx->data, ctx->key,
          tumbler ? ret_s    : real, klen, tumbler);

    memcpy(memory + memory_position,
           tumbler ? ctx->mix : ctx->data,
           tumbler ? ret_s    : real);

    memory_position += (tumbler ? ret_s : real);

    memory[memory_position] = 0x00;

    position += real;
    dlen -= real;

    real_percent = (short)((float)position / div + 0.1);

    if (real_percent > past_percent) {
      Form1->ProgressBar1->Position = real_percent;
      past_percent = real_percent;
      Application->ProcessMessages();
    }
  }

  Form1->Memo3->Text = AnsiString((char *)memory);
  Application->ProcessMessages();

  memset(ctx, 0x00, sizeof(CRYPT_CTX));

  free(memory);

  temp  = 0;
  gamma = 0;
  n = 0;

  return 0;
}

void tumblers_init(void) {
  if (Form1->Edit1->Text != "") {
    gamma += atol(Form1->Edit1->Text.c_str());
  }

  if (Form1->Edit2->Text != "") {
    temp  += atol(Form1->Edit2->Text.c_str());
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



