# Ternary String

## Mô Tả Bài Toán

Một xâu ký tự được gọi là xâu tam phân nếu nó chỉ chứa các ký tự `0`, `1`, và `2`.

Hãy đếm số lượng xâu tam phân có độ dài `n` mà không chứa hai ký tự `1` đứng liền kề nhau.

## Định Dạng Đầu Vào

Duy nhất một số nguyên `n`

## Định Dạng Đầu Xuất

Một số nguyên duy nhất là số lượng xâu thỏa mãn điều kiện theo mô-đun $10^9 + 7$.

## Ràng Buộc Hệ Thống

$1 \le n \le 10^5$

## Ví Dụ Minh Họa

### Ví dụ 1:
**Đầu vào:**
```text
1
```
**Đầu ra:**
```text
3
```
**Giải thích:** Các xâu thỏa mãn là `0`, `1`, và `2`.

### Ví dụ 2:
**Đầu vào:**
```text
2
```
**Đầu ra:**
```text
8
```
**Giải thích:** Tổng số xâu tam phân độ dài 2 là $3^2 = 9$. Chỉ có xâu `11` chứa hai ký tự `1` liền kề nên bị loại. Số xâu thỏa mãn là $9 - 1 = 8$ xâu.

### Ví dụ 3:
**Đầu vào:**
```text
3
```
**Đầu ra:**
```text
22
```
**Giải thích:** Tổng số xâu tam phân độ dài 3 là $3^3 = 27$. Các xâu không thỏa mãn gồm: `110`, `111`, `112`, `011`, `211` (5 xâu). Số xâu thỏa mãn là $27 - 5 = 22$ xâu.
