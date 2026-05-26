# The Bathing Crocodile

## Mô Tả Bài Toán

Spampy là một chú cá sấu tò mò, thân thiện thích tắm sau một ngày làm việc vất vả. Spampy có $n$ điểm và $m$ ống nước (ống nước không có máy bơm nên chỉ có thể đi theo một hướng). Với $s$ là nguồn nước và $t$ là bồn tắm của Spampy.

Ống nước đã bị hao mòn qua thời gian sử dụng nên lượng nước Spampy nhận được sẽ bị thất thoát khi đi qua các ống nước này. May mắn thay, Spampy đã tìm được một ống nước có máy bơm để nước có thể đi qua từ cả hai hướng. Bạn gái của Spampy - Allie đã giúp cậu đánh dấu $k$ nơi mà ống nước có thể lắp đặt và tính toán lượng nước sẽ bị mất nếu ống nước được lắp đặt ở đó.

Nhưng vì có quá nhiều nơi, Spampy không biết đâu là nơi thích hợp để lắp ống nước sao cho số lượng nước bị mất là ít nhất. Bạn hãy giúp chú cá sấu Spampy nhé!

## Định Dạng Đầu Vào

- Dòng đầu tiên chứa 5 số nguyên dương $n \le 10000$, $m \le 100000$, $k < 300$, $1 \le s \le n$, $1 \le t \le n$.
- $m$ dòng tiếp theo, mỗi dòng chứa 3 số nguyên $u, v, c$ ($0 < c \le 1000$), trong đó $c$ là lượng nước mất đi của ống nước từ $u$ đến $v$ (một chiều).
- $k$ dòng tiếp theo, mỗi dòng chứa 3 số nguyên $x, y, q$ ($0 < q \le 1000$), trong đó $q$ là lượng nước mất đi nếu lắp ống nước có máy bơm nối hai điểm $x$ và $y$ (hai chiều).

## Định Dạng Đầu Ra

- In ra một số nguyên duy nhất là lượng nước mất đi ít nhất sau khi lắp ống nước có máy bơm (không in kèm ký tự xuống dòng).
- Trường hợp không có đường nước từ $s$ đến $t$ ngay cả sau khi lắp ống nước máy bơm, in ra `-1`.

## Ràng Buộc Hệ Thống

- $1 \le n \le 10000$
- $1 \le m \le 100000$
- $0 \le k < 300$
- $1 \le s, t \le n$
- $0 < c, q \le 1000$

## Ví Dụ Minh Họa

### Đầu vào mẫu

```text
4 5 3 1 4
1 2 13
2 3 19
3 1 25
3 4 17
4 1 18
1 3 23
2 3 5
2 4 25
```

### Đầu ra mẫu

```text
35
```

### Giải Thích Trực Quan

Ta có nguồn nước $s = 1$, bồn tắm $t = 4$, số ứng viên lắp ống máy bơm $k = 3$.
*   **Không dùng ống máy bơm**: Đường nước chỉ có thể chảy theo các ống một chiều: $1 \to 2 \to 3 \to 4$. Tổng chi phí thất thoát là $13 + 19 + 17 = 49$.
*   **Thử nghiệm lắp đặt các ứng viên**:
    *   Lắp ống $1 \leftrightarrow 3$ có chi phí $23$: Lộ trình tối ưu là $1 \to 3 \to 4$ (sử dụng ống máy bơm từ $1 \to 3$), tổng chi phí là $23 + 17 = 40$.
    *   Lắp ống $2 \leftrightarrow 3$ có chi phí $5$: Lộ trình tối ưu là $1 \to 2 \to 3 \to 4$ (sử dụng ống máy bơm từ $2 \to 3$ thay vì ống một chiều $2 \to 3$), tổng chi phí là $13 + 5 + 17 = 35$.
    *   Lắp ống $2 \leftrightarrow 4$ có chi phí $25$: Lộ trình tối ưu là $1 \to 2 \to 4$ (sử dụng ống máy bơm từ $2 \to 4$), tổng chi phí là $13 + 25 = 38$.
*   Kết quả lượng nước bị mất đi ít nhất thu được là $35$ (khi lắp ống $2 \leftrightarrow 3$).
