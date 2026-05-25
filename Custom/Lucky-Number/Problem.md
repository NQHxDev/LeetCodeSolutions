# Lucky Number

## Mô Tả Bài Toán

Tại một cuộc thi, thí sinh được yêu cầu tìm các "số may mắn". Một số nguyên được coi là số may mắn nếu nó chỉ bao gồm các chữ số 4 và 7. Ví dụ: 4, 7, 44, 747, ...

Hãy giúp ban tổ chức đếm có bao nhiêu số may mắn nhỏ hơn hoặc bằng một số nguyên dương `n` được nhập vào.

## Định Dạng Đầu Vào

Một dòng chứa số nguyên `n`

## Định Dạng Đầu Ra

Một số nguyên duy nhất là số lượng số may mắn không vượt quá `n`

## Ràng Buộc Hệ Thống

$1 \le n \le 10^9$

## Ví Dụ Minh Họa

### Ví dụ 1:
**Đầu vào:**
```text
10
```
**Đầu ra:**
```text
2
```
**Giải thích:** Các số may mắn nhỏ hơn hoặc bằng 10 là `4` và `7`.

### Ví dụ 2:
**Đầu vào:**
```text
50
```
**Đầu ra:**
```text
4
```
**Giải thích:** Các số may mắn nhỏ hơn hoặc bằng 50 là `4`, `7`, `44`, và `47`. (Các số `74` và `77` lớn hơn 50 nên không được tính).

### Ví dụ 3:
**Đầu vào:**
```text
100
```
**Đầu ra:**
```text
6
```
**Giải thích:** Các số may mắn nhỏ hơn hoặc bằng 100 gồm:
- Có 1 chữ số: `4`, `7` (2 số)
- Có 2 chữ số: `44`, `47`, `74`, `77` (4 số)
Tổng cộng: 2 + 4 = 6 số.
