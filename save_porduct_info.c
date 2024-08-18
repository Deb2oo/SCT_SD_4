#include <stdio.h>
#include <string.h>
void extract_product_info(const char *html, const char *csv_filename) {
    FILE *fp = fopen(csv_filename, "w");
    if (!fp) {
        printf("Unable to open file for writing\n");
        return;
    }
    fprintf(fp, "Product Name,Price,Rating\n");

    const char *pos = html;
    char name[100], price[20], rating[10];

    while ((pos = strstr(pos, "<div class=\"product\">")) != NULL) {
        if (sscanf(pos, "<div class=\"product\"><h2>%99[^<]</h2>", name) == 1) {
            pos = strstr(pos, "<span class=\"price\">");
            if (pos && sscanf(pos, "<span class=\"price\">%19[^<]</span>", price) == 1) {
                pos = strstr(pos, "<div class=\"rating\">");
                if (pos && sscanf(pos, "<div class=\"rating\">%9[^<]</div>", rating) == 1) {
                    fprintf(fp, "\"%s\",\"%s\",\"%s\"\n", name, price, rating);
                }
            }
        }
        pos += strlen("<div class=\"product\">");
    }

    fclose(fp);
}

int main(void) {
    const char *html =
        "<div class=\"product\"><h2>Product 1</h2><span class=\"price\">$19.99</span><div class=\"rating\">4.5</div></div>"
        "<div class=\"product\"><h2>Product 2</h2><span class=\"price\">$29.99</span><div class=\"rating\">4.0</div></div>"
        "<div class=\"product\"><h2>Product 3</h2><span class=\"price\">$39.99</span><div class=\"rating\">3.5</div></div>";
    const char *csv_filename = "products.csv";
    extract_product_info(html, csv_filename);

    printf("Product information has been saved to %s\n", csv_filename);
    return 0;
}
