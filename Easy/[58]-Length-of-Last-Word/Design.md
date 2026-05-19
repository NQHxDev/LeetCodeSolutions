# Tư duy thiết kế: Tìm độ dài của từ cuối cùng (Length of Last Word)

Bài toán yêu cầu tìm độ dài của từ cuối cùng trong một chuỗi `s` gồm các từ viết bằng tiếng Anh phân cách nhau bởi các khoảng trắng. Một từ được định nghĩa là một chuỗi con gồm các ký tự không phải khoảng trắng đứng liền kề nhau.

## Vấn đề: Sự lãng phí của việc duyệt xuôi và phân tách chuỗi

Thông thường, khi nghĩ đến việc xử lý từ trong một chuỗi, chúng ta hay sử dụng các hàm có sẵn của ngôn ngữ để cắt chuỗi (split) bằng ký tự khoảng trắng, sau đó lấy từ ở cuối danh sách.

Tuy nhiên, cách tiếp cận này gặp phải hai nhược điểm lớn:

- **Tốn bộ nhớ phụ:** Việc cắt chuỗi sẽ tạo ra một danh sách mới chứa tất cả các từ trong chuỗi ban đầu. Nếu chuỗi đầu vào dài hàng vạn ký tự, việc này sẽ tiêu tốn một lượng bộ nhớ đáng kể ($O(n)$ không gian).
- **Phép toán dư thừa:** Để tìm từ ở cuối cùng, việc duyệt từ đầu chuỗi và phân tách mọi từ phía trước là không cần thiết. Nếu chỉ muốn tìm từ cuối, chúng ta nên hướng sự tập trung trực tiếp vào phần đuôi của chuỗi.

---

## Giải pháp: Kỹ thuật "Đi ngược từ cuối đường" (Backward Traversal)

Tưởng tượng bạn đang đọc một cuốn sách từ góc dưới bên phải trang giấy ngược lên trên. Nhiệm vụ của bạn là tìm từ cuối cùng xuất hiện trên trang đó và đếm số chữ cái của nó.

Quy trình tự nhiên sẽ như sau:

- **Bước 1 (Dọn dẹp khoảng trắng thừa):** Đi ngược từ vị trí cuối cùng của chuỗi sang bên trái. Bỏ qua toàn bộ các khoảng trắng thừa ở đuôi cho đến khi gặp ký tự chữ cái đầu tiên. Ký tự này đánh dấu điểm kết thúc của từ cuối cùng cần tìm.
- **Bước 2 (Đếm độ dài):** Tiếp tục đi ngược sang bên trái và tăng biến đếm độ dài lên `1` cho mỗi ký tự chữ cái gặp được.
- **Bước 3 (Xác định ranh giới từ):** Ngay khi gặp khoảng trắng đầu tiên sau khi đã bắt đầu đếm, điều đó có nghĩa là chúng ta đã đi hết từ cuối cùng. Ta dừng lại và trả về kết quả đếm.

---

## Tại sao đây là cách tiếp cận tối ưu?

- **Tiết kiệm thời gian trong thực tế:** Trong trường hợp tốt nhất, nếu từ cuối cùng nằm sát đuôi chuỗi, thuật toán chỉ mất số bước bằng đúng độ dài của từ đó (thường rất nhỏ) chứ không cần quét qua toàn bộ chuỗi ban đầu. Độ phức tạp thời gian tối đa là $O(n)$ với $n$ là chiều dài chuỗi.
- **Bộ nhớ tối ưu tuyệt đối:** Chúng ta chỉ cần một biến đếm độ dài và một biến chạy chỉ số mà không sao chép hay tạo ra bất kỳ chuỗi con mới nào. Độ phức tạp không gian là $O(1)$.
- **Xử lý biên tự nhiên:** Logic này tự động xử lý chính xác các chuỗi có nhiều khoảng trắng ở cuối hoặc chuỗi chỉ có duy nhất một từ mà không cần viết thêm điều kiện kiểm tra phức tạp.

---

## Mô phỏng luồng xử lý chi tiết

Giả sử chuỗi đầu vào là: `s = "   Hello World  "`

- **Khởi tạo:**
    - Độ dài chuỗi `n = 16`. Chỉ số bắt đầu duyệt từ đuôi: `i = 15`.
    - Biến đếm độ dài: `length = 0`.

- **Quá trình duyệt:**
    - **Quét qua khoảng trắng ở cuối:**
        - `s[15] == ' '` -> Bỏ qua, giảm `i = 14`.
        - `s[14] == ' '` -> Bỏ qua, giảm `i = 13`.
    - **Bắt đầu đếm từ cuối cùng (World):**
        - `s[13] == 'd'` -> Hợp lệ, tăng `length = 1`, giảm `i = 12`.
        - `s[12] == 'l'` -> Hợp lệ, tăng `length = 2`, giảm `i = 11`.
        - `s[11] == 'r'` -> Hợp lệ, tăng `length = 3`, giảm `i = 10`.
        - `s[10] == 'o'` -> Hợp lệ, tăng `length = 4`, giảm `i = 9`.
        - `s[9] == 'W'` -> Hợp lệ, tăng `length = 5`, giảm `i = 8`.
    - **Chạm ranh giới từ:**
        - `s[8] == ' '` -> Gặp khoảng trắng và `length (5) > 0`.
        - Hành động: Dừng vòng lặp ngay lập tức.

- **Kết quả:** Trả về `5`.

---

## Test Case mở rộng

Dưới đây là các trường hợp kiểm thử để đảm bảo tính bao quát của thiết kế:

- **Case 1 (Chuỗi chỉ chứa duy nhất một từ, không có khoảng trắng):**
    - `s = "LeetCode"`
    - Kết quả trả về: `8`

- **Case 2 (Chuỗi chỉ có một từ duy nhất và nhiều khoảng trắng bao quanh):**
    - `s = "    A    "`
    - Kết quả trả về: `1`

- **Case 3 (Từ cuối cùng chỉ có 1 ký tự):**
    - `s = "Hello World a"`
    - Kết quả trả về: `1`

- **Case 4 (Có nhiều dấu cách liên tiếp giữa các từ):**
    - `s = "One   Two      Three"`
    - Kết quả trả về: `5`

- **Case 5 (Từ cuối cùng cực kỳ dài):**
    - `s = "ThisIsAVeryLongWordWithoutAnySpaces"`
    - Kết quả trả về: `35`

---

**Tổng kết:** Bằng việc đảo ngược hướng tiếp cận từ duyệt xuôi sang duyệt ngược, chúng ta biến một thao tác xử lý chuỗi phức tạp thành một phép đếm đơn giản. Tư duy này giúp máy tính tập trung chính xác vào vùng dữ liệu mục tiêu, tiết kiệm tối đa thời gian thực thi và tài nguyên bộ nhớ.
