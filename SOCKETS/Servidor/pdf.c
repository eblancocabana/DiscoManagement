#include "pdfgen.h"

int main(void) {
  struct pdf_info info = {
    .creator = "My software",
    .producer = "My software",
    .title = "Entrada de discoteca",
    .author = "My name",
    .subject = "Entrada de discoteca",
    .date = "Hoy"
  };
  
  struct pdf_doc * pdf = pdf_create(PDF_A4_WIDTH, PDF_A4_HEIGHT, & info);
  pdf_set_font(pdf, "Helvetica-Bold");
  pdf_append_page(pdf);
  pdf_add_text(pdf, NULL, "Entrada de discoteca", 24, 50, 750, PDF_BLACK);
  pdf_add_text(pdf, NULL, "Nombre:", 16, 70, 700, PDF_BLACK);
  pdf_add_text(pdf, NULL, "Fecha:", 16, 70, 650, PDF_BLACK);
  pdf_add_text(pdf, NULL, "Hora:", 16, 70, 600, PDF_BLACK);
  pdf_save(pdf, "entrada.pdf");
  pdf_destroy(pdf);
  return 0;
}
