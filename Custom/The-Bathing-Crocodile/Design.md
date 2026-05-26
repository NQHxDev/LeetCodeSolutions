# Tài Liệu Thiết Kế Thuật Toán: The Bathing Crocodile

## Bản Chất Đồ Thị Và Hệ Thống Phân Phối Nước

Chúng ta có thể hình dung mạng lưới các ống nước của chú cá sấu Spampy như một hệ thống cấp nước đô thị:
*   Các điểm nối ống nước là các đỉnh của đồ thị.
*   Các đường ống nước một chiều bình thường giống như các kênh dẫn nước tự chảy bằng trọng lực. Nước chỉ có thể chảy từ cao xuống thấp (một chiều từ nguồn $u$ đến đích $v$). Việc đi qua các kênh này làm tiêu hao năng lượng hoặc thất thoát một lượng nước nhất định.
*   Đường ống nước có gắn máy bơm đóng vai trò là một đường ống áp lực hai chiều đặc biệt. Do có máy bơm cưỡng bức, nước có thể được đẩy đi theo bất kỳ hướng nào ($x \to y$ hoặc $y \to x$) với cùng một mức độ thất thoát nước cố định.

Mục tiêu là tìm vị trí tối ưu để đặt duy nhất một đường ống hai chiều có máy bơm này vào hệ thống, sao cho hành trình của dòng nước từ nguồn $s$ tới bồn tắm $t$ của Spampy có tổng lượng thất thoát nước là nhỏ nhất.

---

## Giải Pháp: Thuật Toán Dijkstra Hai Chiều (Dual-Dijkstra)

Để tìm ra điểm lắp đặt ống máy bơm tốt nhất, ta có hai hướng tiếp cận:

### Hướng tiếp cận duyệt mọi khả năng

Ta lần lượt thử nghiệm lắp từng ống máy bơm trong số $k$ ứng viên vào đồ thị ban đầu. Với mỗi cấu hình đồ thị mới, ta chạy thuật toán Dijkstra để tìm khoảng cách ngắn nhất từ $s$ đến $t$.
*   Độ phức tạp thời gian: $O(k \cdot (m + n) \log n)$.
*   *Đánh giá:* Mặc dù chạy được với các giới hạn nhỏ, việc xây dựng lại đồ thị và chạy lại Dijkstra hàng trăm lần là cực kỳ lãng phí tài nguyên và không thể tối ưu khi $n, m$ tăng lên.

### Hướng tiếp cận Dijkstra hai chiều tối ưu

Thay vì tìm đường đi sau khi lắp ống, ta có thể đảo ngược tư duy. Một đường đi từ $s$ đến $t$ có sử dụng ống máy bơm nối giữa $x$ và $y$ với chi phí $q$ sẽ có cấu trúc gồm ba phần:
1.  Đường đi từ nguồn $s$ đến một đầu của ống máy bơm (ví dụ là $x$).
2.  Đi qua ống máy bơm từ $x$ sang $y$ với chi phí $q$.
3.  Đường đi từ đầu kia $y$ của ống máy bơm đến bồn tắm $t$.

Như vậy, chi phí tối thiểu của đường đi này là:
$$D = dist\_s[x] + q + dist\_t[y]$$
Trong đó $dist\_s[x]$ là đường đi ngắn nhất từ nguồn $s$ đến $x$ trên đồ thị gốc, và $dist\_t[y]$ là đường đi ngắn nhất từ $y$ đến bồn tắm $t$ trên đồ thị gốc. Do ống máy bơm là hai chiều, ta cũng phải xét hướng ngược lại từ $y$ sang $x$:
$$D' = dist\_s[y] + q + dist\_t[x]$$

Để tính toán nhanh chóng các giá trị này cho tất cả $k$ cặp ứng viên mà không cần duyệt lại đồ thị, ta thực hiện:
1.  **Chạy Dijkstra lần 1** từ nguồn $s$ trên đồ thị gốc để tìm mảng khoảng cách ngắn nhất $dist\_s$ từ $s$ tới mọi nút.
2.  **Dựng đồ thị đảo ngược (reversed graph)** bằng cách đảo chiều tất cả $m$ cạnh một chiều của đồ thị gốc.
3.  **Chạy Dijkstra lần 2** từ bồn tắm $t$ trên đồ thị đảo ngược này để thu được mảng khoảng cách ngắn nhất $dist\_t$ từ mọi nút đến $t$.
4.  Duyệt qua danh sách $k$ ống máy bơm ứng viên. Với mỗi ống nối $(x, y)$ có chi phí $q$, chi phí tối ưu khi sử dụng ống này là:
    $$ans\_pump = \min(dist\_s[x] + q + dist\_t[y], \ dist\_s[y] + q + dist\_t[x])$$
5.  Kết quả tối ưu cuối cùng là giá trị nhỏ nhất trong số tất cả các phương án lắp đặt ống máy bơm, đồng thời so sánh với phương án đi trực tiếp không cần máy bơm ($dist\_s[t]$).

---

## Tại Sao Tối Ưu?

*   **Thời gian thực thi:** Việc chỉ chạy Dijkstra đúng hai lần giúp giảm độ phức tạp thời gian tổng thể xuống còn $O((m + n) \log n)$, sau đó chỉ mất $O(k)$ để duyệt qua danh sách các máy bơm. Điều này giúp chương trình chạy nhanh hơn gấp hàng trăm lần so với cách tiếp cận thông thường và hoạt động mượt mà ngay cả khi $n = 10000, m = 100000$.
*   **Không gian bộ nhớ:** Chỉ cần lưu trữ thêm một đồ thị đảo ngược dạng danh sách kề, độ phức tạp không gian là $O(n + m)$, hoàn toàn nằm trong giới hạn cho phép.

---

## Minh Họa Từng Bước Chạy

Xét đồ thị với $s = 1$ (nguồn nước), $t = 4$ (bồn tắm), $k = 3$ (ứng viên máy bơm). Các cạnh một chiều:
*   $1 \to 2$ (13)
*   $2 \to 3$ (19)
*   $3 \to 1$ (25)
*   $3 \to 4$ (17)
*   $4 \to 1$ (18)

Bước 1: Chạy Dijkstra từ nguồn $1$ trên đồ thị gốc:
*   $dist\_s[1] = 0$
*   $dist\_s[2] = 13$
*   $dist\_s[3] = 32$
*   $dist\_s[4] = 49$

Bước 2: Xây dựng đồ thị đảo ngược:
*   $2 \to 1$ (13)
*   $3 \to 2$ (19)
*   $1 \to 3$ (25)
*   $4 \to 3$ (17)
*   $1 \to 4$ (18)

Bước 3: Chạy Dijkstra từ đích $4$ trên đồ thị đảo ngược:
*   $dist\_t[4] = 0$
*   $dist\_t[3] = 17$
*   $dist\_t[2] = 36$
*   $dist\_t[1] = 42$

Bước 4: Thử nghiệm lắp ống máy bơm:
*   Với ống nối $1 \leftrightarrow 3$ có chi phí $23$:
    *   $dist\_s[1] + 23 + dist\_t[3] = 0 + 23 + 17 = 40$.
    *   $dist\_s[3] + 23 + dist\_t[1] = 32 + 23 + 42 = 97$.
    *   Chi phí tốt nhất: $40$.
*   Với ống nối $2 \leftrightarrow 3$ có chi phí $5$:
    *   $dist\_s[2] + 5 + dist\_t[3] = 13 + 5 + 17 = 35$.
    *   $dist\_s[3] + 5 + dist\_t[2] = 32 + 5 + 36 = 73$.
    *   Chi phí tốt nhất: $35$.
*   Với ống nối $2 \leftrightarrow 4$ có chi phí $25$:
    *   $dist\_s[2] + 25 + dist\_t[4] = 13 + 25 + 0 = 38$.
    *   $dist\_s[4] + 25 + dist\_t[2] = 49 + 25 + 36 = 110$.
    *   Chi phí tốt nhất: $38$.

Kết quả tối ưu cuối cùng thu được là $\min(dist\_s[4], 40, 35, 38) = \min(49, 40, 35, 38) = 35$ (lắp đặt ống $2 \leftrightarrow 3$).

---

## Các Trường Hợp Kiểm Thử Bổ Sung

### Trường hợp 1: Đồ thị gốc không liên thông nhưng lắp bơm giải quyết được

*   **Đầu vào:**
    ```text
    3 1 1 1 3
    1 2 10
    2 3 5
    ```
*   **Mô tả:** Đồ thị gốc chỉ có duy nhất cạnh $1 \to 2$, không có đường đi từ nguồn $1$ đến đích $3$. Ta có $k = 1$ ống bơm ứng viên nối $2 \leftrightarrow 3$ với chi phí $5$.
*   **Đầu ra mong đợi:** `15` (Đi qua đường $1 \to 2 \to 3$ nhờ ống máy bơm $2 \leftrightarrow 3$, tổng chi phí $10 + 5 = 15$).

### Trường hợp 2: Đồ thị hoàn toàn bị cô lập

*   **Đầu vào:**
    ```text
    4 2 1 1 4
    1 2 5
    3 4 5
    1 2 2
    ```
*   **Mô tả:** Đồ thị gốc gồm hai thành phần biệt lập: $\{1, 2\}$ và $\{3, 4\}$. Ống bơm duy nhất nối $1 \leftrightarrow 2$ là hai đỉnh đã liên thông sẵn, không giúp đưa dòng nước sang bồn tắm tại $4$.
*   **Đầu ra mong đợi:** `-1`

### Trường hợp 3: Ống máy bơm tối ưu hơn nhiều đường đi trực tiếp ngắn nhất

*   **Đầu vào:**
    ```text
    5 5 2 1 5
    1 2 10
    2 5 20
    1 3 2
    4 5 2
    3 4 50
    3 4 5
    2 4 10
    ```
*   **Mô tả:**
    *   Đường đi trực tiếp ngắn nhất từ $1 \to 5$ ban đầu là $1 \to 2 \to 5$ với chi phí $10 + 20 = 30$.
    *   Có hai ống máy bơm ứng viên:
        *   Ống 1: $3 \leftrightarrow 4$ chi phí $5$.
        *   Ống 2: $2 \leftrightarrow 4$ chi phí $10$.
    *   Nếu chọn ống 1 ($3 \leftrightarrow 4$ chi phí 5), ta đi đường $1 \to 3 \to 4 \to 5$ với tổng chi phí: $2$ (từ $1 \to 3$) + $5$ (bơm $3 \leftrightarrow 4$) + $2$ (từ $4 \to 5$) = $9$.
*   **Đầu ra mong đợi:** `9` (Tối ưu hơn rất nhiều so với chi phí trực tiếp $30$).
