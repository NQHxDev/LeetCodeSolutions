# Tài Liệu Thiết Kế Thuật Toán: Bulls and Cows

## Trò Chơi Sắp Đặt Khóa Và Ổ Khóa

Chúng ta có thể liên tưởng trò chơi đố số này với việc ghép đôi một chuỗi các ổ khóa và chìa khóa:
*   Mỗi vị trí trong chuỗi `secret` là một ổ khóa có hình dạng cụ thể (chữ số từ 0 đến 9).
*   Mỗi vị trí trong chuỗi `guess` là một chiếc chìa khóa tương ứng.

Quá trình phân loại diễn ra như sau:
*   **Bulls (A) - Đúng vị trí**: Chiếc chìa khóa đặt đúng ổ khóa cùng loại. Ta cắm chìa, mở khóa thành công và loại cặp này ra khỏi cuộc chơi.
*   **Cows (B) - Sai vị trí**: Chiếc chìa khóa không khớp với ổ khóa tại vị trí hiện tại của nó, nhưng có thể mở được một ổ khóa cùng loại nằm ở vị trí khác.
    *   Để đếm số Cows một cách chính xác mà không đếm lặp, ta thu gom tất cả các ổ khóa chưa được mở vào **Giỏ Ổ Khóa**, và tất cả các chìa khóa chưa dùng vào **Giỏ Chìa Khóa**.
    *   Với mỗi chữ số từ 0 đến 9, số lượng Cows tạo ra tối đa chính là phần giao (giá trị nhỏ nhất) giữa số lượng ổ khóa và số lượng chìa khóa của chữ số đó trong hai giỏ.

---

## Giải Pháp: Thuật Toán Đánh Dấu Tần Suất Một Lần Duyệt

Chúng ta sử dụng hai mảng lưu trữ tần suất kích thước 10 để đếm số lượng các chữ số không khớp:
1.  `secret_counts`: Đếm số lượng chữ số chưa khớp của `secret`.
2.  `guess_counts`: Đếm số lượng chữ số chưa khớp của `guess`.

Quy trình thực hiện:
1.  Khởi tạo `bulls = 0` và `cows = 0`.
2.  Duyệt qua từng chỉ số $i$ từ $0$ đến $N - 1$ ($N$ là độ dài của chuỗi):
    *   Nếu `secret[i] == guess[i]`: Tăng `bulls` lên 1.
    *   Nếu khác nhau:
        *   Tăng tần suất của chữ số `secret[i]` trong `secret_counts`.
        *   Tăng tần suất của chữ số `guess[i]` trong `guess_counts`.
3.  Sau khi duyệt hết chuỗi, duyệt qua các chữ số từ $0$ đến $9$:
    *   Cộng dồn vào `cows` giá trị nhỏ nhất giữa `secret_counts[d]` và `guess_counts[d]`.
4.  Ghép chuỗi kết quả dạng `"xAyB"` và trả về.

---

## Tại Sao Tối Ưu?

*   **Thời gian thực thi:** Thuật toán chỉ cần duyệt qua chuỗi ký tự đúng một lần. Vòng lặp thứ hai để tính Cows luôn có số lần lặp cố định là 10 (tương ứng với các chữ số từ 0 đến 9). Do đó, độ phức tạp thời gian là $O(N)$, chạy cực kỳ nhanh và tối ưu tuyệt đối.
*   **Không gian bộ nhớ:** Chỉ sử dụng hai mảng số nguyên có kích thước cố định bằng 10. Độ phức tạp không gian là $O(1)$, gần như không tiêu tốn tài nguyên bộ nhớ bổ sung.

---

## Minh Họa Từng Bước Chạy

Xét ví dụ: `secret = "1807"`, `guess = "7810"`

Bước 1: Khởi tạo các giỏ đếm tần suất chữ số từ 0 đến 9 bằng 0.

Bước 2: Duyệt qua chuỗi ký tự:
*   Chỉ số 0: `secret[0] = '1'`, `guess[0] = '7'`. Khác nhau $\to$ `secret_counts[1]++`, `guess_counts[7]++`.
*   Chỉ số 1: `secret[1] = '8'`, `guess[1] = '8'`. Giống nhau $\to$ `bulls = 1`.
*   Chỉ số 2: `secret[2] = '0'`, `guess[2] = '1'`. Khác nhau $\to$ `secret_counts[0]++`, `guess_counts[1]++`.
*   Chỉ số 3: `secret[3] = '7'`, `guess[3] = '0'`. Khác nhau $\to$ `secret_counts[7]++`, `guess_counts[0]++`.

Bước 3: Tính toán Cows dựa trên mảng đếm tần suất:
*   Chữ số 0: `secret_counts[0] = 1`, `guess_counts[0] = 1` $\to$ `cows += min(1, 1) = 1`.
*   Chữ số 1: `secret_counts[1] = 1`, `guess_counts[1] = 1` $\to$ `cows += min(1, 1) = 2`.
*   Chữ số 7: `secret_counts[7] = 1`, `guess_counts[7] = 1` $\to$ `cows += min(1, 1) = 3`.
*   Các chữ số khác có tần suất bằng 0.

Kết quả trả về: `"1A3B"`.

---

## Các Trường Hợp Kiểm Thử Bổ Sung

### Trường hợp 1: Tất cả đều là Bulls

*   **Đầu vào:**
    ```text
    1122
    1122
    ```
*   **Mô tả:** Mọi vị trí đều khớp hoàn toàn giữa secret và guess.
*   **Đầu ra mong đợi:** `"4A0B"`

### Trường hợp 2: Tất cả đều là Cows

*   **Đầu vào:**
    ```text
    1234
    4321
    ```
*   **Mô tả:** Các chữ số giống nhau nhưng toàn bộ đều đặt sai vị trí.
*   **Đầu ra mong đợi:** `"0A4B"`

### Trường hợp 3: Sự xuất hiện lặp lại của một chữ số duy nhất

*   **Đầu vào:**
    ```text
    1123
    0111
    ```
*   **Mô tả:** Chữ số '1' xuất hiện nhiều lần. 
    *   Vị trí thứ hai khớp: 1 Bull ('1' tại chỉ số 1).
    *   Các vị trí khác của '1' trong guess sẽ tạo thành 1 Cow khi ghép với '1' tại chỉ số 0 của secret.
*   **Đầu ra mong đợi:** `"1A1B"`
