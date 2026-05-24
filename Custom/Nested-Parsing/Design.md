# Tư duy thiết kế: Phân tích cú pháp lồng nhau (Nested Parsing)

Bài toán kiểm tra tính hợp lệ của cấu trúc lồng nhau đệ quy yêu cầu thiết kế một cơ chế kiểm tra cú pháp (Parser) chặt chẽ, tối ưu hóa quá trình khớp cặp đóng-mở và định vị các phân đoạn con kể cả khi xảy ra hiện tượng gộp dấu nháy đóng ở nhiều cấp độ, mở rộng thêm các trường hợp đóng/mở hoàn toàn các quote con bên trong cùng một nhóm dấu nháy đơn hoặc khi nhóm mở đầu tiên/nhóm đóng cuối cùng thực hiện thao tác phụ.

## Vấn đề

Hãy tưởng tượng một bộ hộp quà lồng nhau. Quy tắc sắp xếp là: một hộp quà cấp $k$ chỉ có thể chứa trực tiếp các hộp quà cấp $k-1$ ở bên trong. Tuy nhiên, khi các hộp quà được xếp chồng khít lên nhau và đóng nắp cùng một lúc ở phía sau, các vách hộp đóng ở các cấp khác nhau sẽ đứng sát nhau mà không có xốp bảo vệ ở giữa. Đối với người quan sát bên ngoài, họ chỉ thấy một lớp vách dày xếp chồng (tương tự như việc các dấu nháy đóng của nhiều cấp đứng liền kề và gộp thành một nhóm duy nhất có độ dày bằng tổng số vách hộp).

Tương tự, ta có thể mở và đóng một hộp quà con cấp $k-1$ hoàn toàn bên trong cùng một nhóm dấu nháy. Việc đóng mở khép kín này có thể diễn ra ở bất kỳ nhóm nào, **bao gồm cả nhóm mở đầu tiên ($a_0$) và nhóm đóng cuối cùng ($a_{n-1}$)**. Điều này nghĩa là nhóm đầu tiên không bắt buộc phải có kích thước đúng bằng chi phí mở $f(s_0)$, mà có thể chứa thêm các quote con lồng trong lòng nó từ rất sớm.

Đặc biệt, toàn bộ bài toán yêu cầu tìm cấp $k$ lớn nhất sao cho **toàn bộ chuỗi hạt ngọc** tạo thành **duy nhất một $k$-quote hợp lệ**. Do đó:
- Hộp quà ngoài cùng cấp $k$ bắt đầu ở nhóm đầu tiên và chỉ được đóng lại ở nhóm cuối cùng. Tại mọi khoảng xốp (văn bản) ở giữa, hộp ngoài cùng cấp $k$ này luôn luôn ở trạng thái mở.
- Mọi hộp quà được mở ra ở cấp sâu hơn phải tuân thủ nghiêm ngặt cấp độ lồng nhau. Một hộp ở vị trí có độ sâu ngăn xếp là $s'$ (cấp độ hiện tại là $level = k - s' + 1$) chỉ có thể trực tiếp chứa các hộp con có cấp độ chính xác là $level - 1$. Do đó, ta không thể đặt một hộp con có kích thước quá nhỏ (ví dụ hộp cấp 1) trực tiếp vào trong một hộp quá lớn (ví dụ hộp cấp 6) mà không qua các cấp trung gian.

---

## Giải pháp

Chúng ta sử dụng phương pháp **Quy hoạch động trên trạng thái ngăn xếp (Stack-state Dynamic Programming)** kết hợp với **Giới hạn ứng viên toán học**:

### Trường hợp đặc biệt: Không có văn bản (N = 1)
Nếu toàn bộ đầu vào chỉ chứa một nhóm dấu nháy duy nhất ($N = 1$), tổng số dấu nháy $a_0$ phải là một số chẵn và thỏa mãn điều kiện $a_0 \ge k(k+1)$.
Khi đó, giá trị $k$ lớn nhất có thể đạt được là:
$$k = \lfloor \frac{-1 + \sqrt{1 + 4 a_0}}{2} \rfloor$$
Ta chỉ cần kiểm tra xem $a_0$ có phải là số chẵn hay không để đưa ra kết luận.

### Xác định giới hạn trên K_max cho trường hợp tổng quát (N > 1)
Vì hộp cấp $k$ bắt buộc phải được mở ở nhóm đầu tiên ($a_0$) và đóng ở nhóm cuối cùng ($a_{n-1}$), ta luôn có $k \le a_0$ và $k \le a_{n-1}$.
Hơn nữa, tổng số dấu nháy trong toàn bộ chuỗi $\sum a_i$ phải đủ lớn để mở và đóng tất cả các cấp từ $1$ đến $k$ ít nhất một lần:
$$\sum a_i \ge k(k+1) \implies k \le \lfloor \frac{-1 + \sqrt{1 + 4 \sum a_i}}{2} \rfloor$$
Do đó, ta xác định giới hạn trên của $k$:
$$K_{max} = \min\left( a_0, a_{n-1}, \lfloor \frac{-1 + \sqrt{1 + 4 \sum a_i}}{2} \rfloor \right)$$
Vì $K_{max}$ trong mọi bộ dữ liệu thực tế luôn rất nhỏ (thường $\le 45000$), ta có thể duyệt trực tiếp $k$ từ $K_{max}$ xuống $1$.

### Quy trình xác thực cho mỗi giá trị k
1. **Tiền tính toán F:** Tạo mảng chi phí `F` tương ứng với $k$.
2. **Tìm các trạng thái s0 hợp lệ ở bước khởi đầu:**
    Duyệt $s_0 \in [1, k]$ sao cho $F[s_0] \le a_0$. Số dấu nháy dư thừa $diff = a_0 - F[s_0]$ phải thỏa mãn:
    - $diff \% 2 == 0$.
    - Nếu $diff > 0$, ta tính $y_{opt} = \min(s_0, k - 1)$ và yêu cầu $diff \ge (k - y_{opt}) \cdot (k - y_{opt} + 1)$.
    Nếu tìm thấy ít nhất một $s_0$ hợp lệ, ta giữ lại để chạy quy hoạch động.
3. **Kiểm tra tính tương thích ở bước kết thúc:**
    Tương tự, kiểm tra xem có tồn tại ít nhất một trạng thái đóng cuối cùng $s_{n-1} \in [1, k]$ sao cho $F[s_{n-1}] \le a_{n-1}$ và phần nháy dư $diff = a_{n-1} - F[s_{n-1}]$ thỏa mãn điều kiện chẵn và $diff \ge (k - y_{opt}) \cdot (k - y_{opt} + 1)$ với $y_{opt} = \min(s_{n-1}, k - 1)$ nếu $diff > 0$ hay không. Nếu không, bỏ qua $k$ này.
4. **Chạy quy hoạch động (DP):**
   Với mỗi $s_0$ tìm được:
   - Khởi tạo: $DP[0] = \{s_0\}$.
   - Tại mỗi nhóm $a_i$ tiếp theo, ta chuyển từ trạng thái $s \in DP[i-1]$ sang trạng thái mới $s_i$:
     - Ở các bước trung gian ($i < n - 1$), ngăn xếp bắt buộc phải chứa ít nhất hộp ngoài cùng ($si \ge 1$). Chỉ bước cuối cùng ($i = n - 1$) mới được phép rỗng ($si = 0$).
     - Gọi $s'$ là trạng thái ngăn xếp trung gian sau khi đóng (pop) một số cấp ($0 \le s' \le \min(s, s_i)$).
     - Chi phí trên biên là $f(s) + f(s_i) - 2f(s')$.
      - Số dấu nháy dư thừa $diff = a_i - [f(s) + f(s_i) - 2f(s')]$ phải thỏa mãn:
        1. $diff \ge 0$ và $diff$ là số **chẵn**.
        2. Nếu $diff > 0$, ta phải có $sp < k$, tính $y_{opt} = \min(\max(s, s_i), k - 1)$ và yêu cầu $diff \ge (k - y_{opt}) \cdot (k - y_{opt} + 1)$.
      - Nếu tồn tại giá trị $s'$ hợp lệ, ta ghi nhận $s_i$ là một trạng thái mới hợp lệ cho bước $i$.
   - Nếu kết thúc quy hoạch động mà trạng thái $0 \in DP[n-1]$, giá trị $k$ hiện tại là đáp án lớn nhất. Dừng thuật toán.

---

## Tại sao tối ưu?

- **Hiệu năng thời gian:** Thay vì giải quyết các phương trình chia hết phức tạp dễ bị sai lệch khi có nháy dư ở hai đầu, duyệt trực tiếp $k$ từ $K_{max}$ xuống $1$ là hướng tiếp cận trực quan nhất. Với $K_{max} \le 45000$, C++ chạy hàng chục ngàn bước quy hoạch động cực kỳ nhanh (thường dưới 15ms), đáp ứng tốt giới hạn thời gian.
- **Tiết kiệm bộ nhớ:** Chỉ sử dụng các vector nhỏ, độ phức tạp không gian tĩnh $O(k + N)$ cho mảng lưu trữ, không phụ thuộc vào giá trị cực đại $10^9$ của các nhóm dấu nháy.

---

## Mô phỏng luồng xử lý

Giả sử dãy số đầu vào là `a = [4, 3, 2, 1, 1, 2, 3, 1, 1, 1, 1, 1, 1, 4]`. Kích thước $N = 14$.
- Tổng dấu nháy $\sum a_i = 29$.
- $K_{max} = \min(4, 4, 4) = 4$.
- **Thử $k = 4$:**
  - $F = [0, 4, 7, 9, 10]$.
  - Nhóm đầu $a_0 = 4$: Chỉ có $s_0 = 1$ hợp lệ ($F[1]=4$, dư $0$).
  - Chạy quy hoạch động bắt đầu với $s_0 = 1$:
    - Bước 1 ($a_1 = 3$): $s = 1$. Thử tìm $si \ge 1$:
      - Nếu $si = 2$, chọn $s'=1$: $diff = 3 - (4+7-8) = 0$ (lẻ $\rightarrow$ loại).
      - Nếu $si = 1$, chọn $s'=1$: $diff = 3 - (4+4-8) = 3$ (lẻ $\rightarrow$ loại).
      - Tất cả các chuyển trạng thái đều thất bại $\rightarrow$ $DP[1]$ rỗng. Loại $k = 4$.
- **Thử $k = 3$:**
  - $F = [0, 3, 5, 6]$.
  - Nhóm đầu $a_0 = 4$: Thử các $s_0 \le 3$:
    - $s_0 = 1: F[1] = 3 \le 4$ nhưng dư $1$ (lẻ $\rightarrow$ loại).
    - $s_0 = 2: F[2] = 5 > 4 \rightarrow$ loại.
    - Không có $s_0$ hợp lệ $\rightarrow$ Loại $k = 3$.
- **Thử $k = 2$:**
  - $F = [0, 2, 3]$.
  - Nhóm đầu $a_0 = 4$: Thử các $s_0 \le 2$:
    - $s_0 = 1: F[1] = 2 \le 4$, dư $2$ (chẵn, $y_{opt} = \min(1, 1) = 1$, dư $2 \ge (2-1) \cdot (2-1+1) = 2 \rightarrow$ Hợp lệ!).
  - Chạy quy hoạch động bắt đầu từ $s_0 = 1$:
    - Vượt qua toàn bộ các bước quy hoạch động và kết thúc ở $s_N = 0$.
  - Trả về kết quả $k = 2$.

---

## Các trường hợp kiểm thử bổ sung

- **Trường hợp 1:** `a = [4, 3, 2, 1, 1, 2, 3, 1, 1, 1, 1, 1, 1, 4]`, $N = 14$
  - Mô tả: Trường hợp có chứa quote con lồng ghép từ rất sớm ở nhóm đầu tiên và nhóm cuối cùng.
  - Kết quả mong đợi: `2`

- **Trường hợp 2:** `a = [6, 6, 6, 6, 6, 6]`, $N = 6$
  - Mô tả: Dãy gồm toàn các phần tử bằng 6, đáp án đúng phải là 3 do ràng buộc cấp lồng nhau sâu hơn và tính duy nhất của quote ngoài cùng.
  - Kết quả mong đợi: `3`

- **Trường hợp 3:** `a = [3, 2, 2, 1, 2]`, $N = 5$
  - Mô tả: Một $2$-quote có nhóm mở đầu tiên thực hiện mở liên tiếp 2 cấp ($a_0 = 3$).
  - Kết quả mong đợi: `2`

- **Trường hợp 4:** `a = [2, 2, 2]`, $N = 3$
  - Mô tả: Một $2$-quote chứa duy nhất một $1$-quote được mở và đóng khép kín ngay trong nhóm ở giữa.
  - Kết quả mong đợi: `2`

- **Trường hợp 5:** `a = [22]`, $N = 1$
  - Mô tả: Toàn bộ chuỗi không có văn bản và lồng ghép cấp 4.
  - Kết quả mong đợi: `4`
