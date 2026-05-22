# Số Đẹp (Beautiful Numbers)

## Mô Tả Bài Toán

Một số nguyên không âm $x$ được gọi là **số đẹp** nếu như $x$ chia hết cho ít nhất một trong ba số: $4$, $7$, hoặc $11$.

Cho hai số nguyên không âm $L$ và $R$, nhiệm vụ của bạn là đếm số lượng số đẹp $x$ nằm trong đoạn $[L, R]$ (tức là thỏa mãn $L \le x \le R$).

---

## Định Dạng Đầu Vào

- **Dòng đầu tiên**: Chứa số nguyên dương $T$ tương ứng với số lượng bộ thử nghiệm (test cases).
- **$T$ dòng tiếp theo**: Mỗi dòng chứa hai số nguyên không âm $L$ và $R$ tương ứng với giới hạn dưới và giới hạn trên của đoạn cần truy vấn.

---

## Định Dạng Đầu Ra

- In ra $T$ dòng, mỗi dòng chứa một số nguyên duy nhất là số lượng số đẹp trong đoạn tương ứng.

---

## Ràng Buộc Hệ Thống

- $T \le 20$
- **Subtask 1 (60% số điểm)**: $0 \le L \le R \le 10^6$
- **Subtask 2 (40% số điểm)**: $0 \le L \le R \le 10^{12}$

---

## Ví Dụ Minh Họa

### Đầu vào mẫu

```text
2
1 10
0 28
```

### Đầu ra mẫu

```text
3
10
```

### Giải Thích

- **Test case 1**: Trong đoạn $[1, 10]$, các số đẹp là $\{4, 7, 8\}$ (chia hết cho 4 hoặc 7). Tổng cộng có 3 số.
- **Test case 2**: Trong đoạn $[0, 28]$, các số đẹp là:
    - Số 0 (chia hết cho tất cả).
    - Chia hết cho 4: $\{4, 8, 12, 16, 20, 24, 28\}$
    - Chia hết cho 7: $\{7, 14, 21, 28\}$
    - Chia hết cho 11: $\{11, 22\}$
    - Hợp của các tập trên (lưu ý số 28 bị lặp): $\{0, 4, 7, 8, 11, 14, 16, 20, 21, 22, 24, 28\}$. Tổng cộng có 12 số đẹp.
