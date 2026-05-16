# Tư duy thiết kế: Zigzag Conversion

## Vấn đề

Bài toán yêu cầu chúng ta sắp xếp lại các ký tự của một chuỗi văn bản theo hình zigzag trên một số hàng nhất định, sau đó đọc lại theo từng hàng từ trên xuống dưới. Điều này tương tự như việc chúng ta đang viết chữ trên một dải ruy băng zắc-zắc, nhưng thay vì đọc theo đường đi của dải ruy băng, chúng ta lại trải phẳng nó ra và đọc theo từng dòng kẻ ngang.

Thách thức ở đây là xác định được vị trí hàng chính xác cho mỗi ký tự mà không cần phải thực sự xây dựng một ma trận hai chiều (vốn sẽ gây lãng phí bộ nhớ vì có nhiều khoảng trống).

---

## Giải pháp

Hãy tưởng tượng một **con thoi trên khung dệt** di chuyển lên xuống liên tục giữa các giới hạn hàng. 

1.  **Khởi tạo:** Chúng ta tạo ra các "ngăn chứa" (strings) tương ứng với số hàng (`numRows`).
2.  **Cơ chế di chuyển:** 
    -   Chúng ta bắt đầu từ hàng đầu tiên và di chuyển xuống dưới. 
    -   Khi chạm đến "sàn" (hàng cuối cùng), chúng ta đảo ngược hướng để đi lên.
    -   Khi chạm đến "trần" (hàng đầu tiên), chúng ta lại đảo hướng để đi xuống.
3.  **Thực thi:** Duyệt qua từng ký tự của chuỗi gốc, đặt ký tự đó vào ngăn chứa của hàng hiện tại, sau đó cập nhật vị trí hàng dựa trên hướng di chuyển hiện tại.
4.  **Kết hợp:** Sau khi đi qua toàn bộ chuỗi, chúng ta chỉ cần nối tất cả các ngăn chứa lại với nhau để có kết quả cuối cùng.

---

## Tại sao tối ưu?

Phương pháp này đạt được hiệu năng tối ưu về cả thời gian và không gian nhờ vào tính tinh giản trong cách tiếp cận:

-   **Thời gian O(n):** Chúng ta chỉ duyệt qua chuỗi đúng một lần. Mỗi thao tác chèn ký tự vào string có độ phức tạp trung bình là O(1).
-   **Không gian O(n):** Thay vì dùng một ma trận `numRows x n` đầy rẫy các ô trống, chúng ta chỉ sử dụng tổng cộng đúng `n` đơn vị bộ nhớ để lưu trữ các ký tự trong các string riêng lẻ. Điều này giúp loại bỏ hoàn toàn các vùng nhớ thừa không cần thiết.

---

## Mô phỏng thực tế

Giả sử chuỗi `s = "MOUNTAIN"`, `numRows = 3`.

1.  **Ký tự 'M':** Hàng 0. Hướng: Xuống. (Hàng tiếp theo: 1)
2.  **Ký tự 'O':** Hàng 1. Hướng: Xuống. (Hàng tiếp theo: 2)
3.  **Ký tự 'U':** Hàng 2. **Chạm sàn!** Đổi hướng sang Lên. (Hàng tiếp theo: 1)
4.  **Ký tự 'N':** Hàng 1. Hướng: Lên. (Hàng tiếp theo: 0)
5.  **Ký tự 'T':** Hàng 0. **Chạm trần!** Đổi hướng sang Xuống. (Hàng tiếp theo: 1)
6.  **Ký tự 'A':** Hàng 1. Hướng: Xuống. (Hàng tiếp theo: 2)
7.  **Ký tự 'I':** Hàng 2. **Chạm sàn!** Đổi hướng sang Lên. (Hàng tiếp theo: 1)
8.  **Ký tự 'N':** Hàng 1. Hướng: Lên. (Hàng tiếp theo: 0)

**Kết quả thu được theo từng ngăn:**
-   Ngăn 0: `MT`
-   Ngăn 1: `ONAI`
-   Ngăn 2: `UN`
=> Chuỗi kết quả: `MTONAIUN`

---

## Các trường hợp kiểm thử mở rộng

Dưới đây là một số kịch bản kiểm thử khác biệt để đảm bảo tính ổn định của giải thuật:

1.  **Chuỗi ngắn hơn số hàng:** 
    -   `s = "ABC"`, `numRows = 5`
    -   Kết quả: `"ABC"` (Chưa kịp chạm sàn đã hết chuỗi).
2.  **Số hàng chỉ bằng 1:** 
    -   `s = "LEETCODE"`, `numRows = 1`
    -   Kết quả: `"LEETCODE"` (Không có không gian để tạo zigzag).
3.  **Chuỗi đối xứng hoàn hảo:** 
    -   `s = "ABCCBA"`, `numRows = 2`
    -   Kết quả: `"ACBABC"` (Hàng 0: `ACB`, Hàng 1: `BCA`).
4.  **Chuỗi lặp lại:**
    -   `s = "AAAAAA"`, `numRows = 3`
    -   Kết quả: `"AAAAAA"` (Dù zigzag thế nào thì kết quả vẫn giữ nguyên do ký tự trùng lặp).
