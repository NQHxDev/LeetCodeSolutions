# Tư Duy Thiết Kế: Beautiful Numbers (Số Đẹp)

## 1. Bản Chất Toán Học: Nguyên Lý Bù Trừ (Inclusion-Exclusion Principle)

Bài toán yêu cầu chúng ta đếm số lượng số nguyên $x \in [L, R]$ chia hết cho $4$, $7$, hoặc $11$.
Thay vì đếm trực tiếp trên đoạn $[L, R]$, ta có thể đưa về bài toán đếm trên khoảng $[1, N]$:
$$\text{Số lượng số đẹp trong } [L, R] = \text{Count}(R) - \text{Count}(L-1)$$
*(Nếu $L = 0$, do $0$ là số đẹp, ta chỉ cần tính $\text{Count}(R) + 1$)*.

### Đếm số lượng chia hết cho $a$, $b$, hoặc $c$ trong khoảng $[1, N]$
Gọi:
* $A$ là tập hợp các số chia hết cho $4$ trong $[1, N]$.
* $B$ là tập hợp các số chia hết cho $7$ trong $[1, N]$.
* $C$ là tập hợp các số chia hết cho $11$ trong $[1, N]$.

Theo nguyên lý bù trừ, kích thước của tập hợp hợp $A \cup B \cup C$ được tính bằng công thức:
$$|A \cup B \cup C| = (|A| + |B| + |C|) - (|A \cap B| + |A \cap C| + |B \cap C|) + |A \cap B \cap C|$$

Trong đó:
* $|A| = \lfloor N/4 \rfloor$
* $|B| = \lfloor N/7 \rfloor$
* $|C| = \lfloor N/11 \rfloor$
* $|A \cap B|$ là các số chia hết cho cả $4$ và $7$. Do $4$ và $7$ nguyên tố cùng nhau, bội chung nhỏ nhất là $\text{LCM}(4, 7) = 28$. Vậy $|A \cap B| = \lfloor N/28 \rfloor$.
* Tương tự, $\text{LCM}(4, 11) = 44 \Rightarrow |A \cap C| = \lfloor N/44 \rfloor$.
* $\text{LCM}(7, 11) = 77 \Rightarrow |B \cap C| = \lfloor N/77 \rfloor$.
* $|A \cap B \cap C|$ là các số chia hết cho cả $4, 7, 11$. Bội chung nhỏ nhất là $\text{LCM}(4, 7, 11) = 308$. Vậy $|A \cap B \cap C| = \lfloor N/308 \rfloor$.

Như vậy, hàm đếm tối ưu đạt độ phức tạp $O(1)$:
$$\text{Count}(N) = \lfloor N/4 \rfloor + \lfloor N/7 \rfloor + \lfloor N/11 \rfloor - \lfloor N/28 \rfloor - \lfloor N/44 \rfloor - \lfloor N/77 \rfloor + \lfloor N/308 \rfloor$$

---

## 2. So Sánh Với Các Bài Toán LeetCode

Đây là phiên bản trực diện và đơn giản hơn của bài toán LeetCode:
* **[LeetCode 1201 - Ugly Number III](https://leetcode.com/problems/ugly-number-iii/)**: Yêu cầu tìm số đẹp thứ $n$ chia hết cho $a$, $b$, hoặc $c$. 
  * Để giải quyết LeetCode 1201, chúng ta phải sử dụng **Binary Search (Tìm kiếm nhị phân)** trên khoảng kết quả, và ở mỗi bước kiểm tra, ta dùng chính **Nguyên lý bù trừ** này để đếm số lượng số đẹp $\le M$.
* **[LeetCode 878 - N-th Magical Number](https://leetcode.com/problems/n-th-magical-number/)**: Tương tự nhưng chỉ xét 2 số chia $a$ và $b$.

---

## 3. Độ Phức Tạp Thuật Toán

* **Thời gian (Time Complexity)**: $O(1)$ cho mỗi test case. Tổng thời gian cho $T$ test cases là $O(T)$, chạy cực kỳ nhanh và vượt qua subtask 2 với $R \le 10^{12}$ chỉ trong chưa đầy $1$ miligiây.
* **Không gian (Space Complexity)**: $O(1)$ bộ nhớ phụ trợ.
