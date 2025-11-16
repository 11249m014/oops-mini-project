#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

struct Product {
    string name;
    int quantity;
    double price;
};

int main() {
    int n;
    cout << "Enter number of products: ";
    cin >> n;

    vector<Product> products(n);

    for (int i = 0; i < n; i++) {
        cout << "Enter product name: ";
        cin >> products[i].name;

        cout << "Enter quantity: ";
        cin >> products[i].quantity;

        cout << "Enter unit price: ";
        cin >> products[i].price;
    }

    ofstream file("invoice.html");
    if (!file) {
        cout << "Error creating invoice.html";
        return 1;
    }

    // HTML header
    file << R"(
<!DOCTYPE html>
<html>
<head>
<meta charset='UTF-8'>
<title>Invoice</title>
<style>
body { font-family: 'Poppins', Arial; background:#f5f7fa; padding:40px; }
.invoice-box { max-width:900px; margin:auto; background:#fff; padding:30px 40px; border-radius:12px;
               box-shadow:0 4px 30px rgba(0,0,0,0.1); }
h2 { text-align:center; margin-bottom:20px; color:#333; letter-spacing:1px; }
table { width:100%; border-collapse:collapse; margin-top:10px; }
th { background:#3742fa; color:white; padding:12px; font-size:16px; }
td { padding:12px; border-bottom:1px solid #ddd; text-align:center; }
.total-row { background:#f1f2f6; font-weight:bold; }
.footer { text-align:center; margin-top:25px; font-size:14px; color:#666; }
</style>
</head>
<body>
<div class='invoice-box'>
<h2>Invoice</h2>
<table>
<tr><th>Product</th><th>Qty</th><th>Price</th><th>Total</th></tr>
)";

    double grandTotal = 0;

    for (auto &p : products) {
        double total = p.quantity * p.price;
        grandTotal += total;

        file << "<tr>"
             << "<td>" << p.name << "</td>"
             << "<td>" << p.quantity << "</td>"
             << "<td>" << p.price << "</td>"
             << "<td>" << total << "</td>"
             << "</tr>\n";
    }

    file << "<tr class='total-row'><td colspan='3'>Grand Total</td><td>"
         << grandTotal << "</td></tr>";

    file << R"(
</table>
<div class='footer'>Thank you for your purchase!</div>
</div>
</body>
</html>
)";

    file.close();
    cout << "Beautiful Invoice Generated → invoice.html\n";
    return 0;
}
