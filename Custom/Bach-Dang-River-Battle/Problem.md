# Trận Chiến Trên Sông Bạch Đằng (Bach Dang River Battle)

## Bối Cảnh Lịch Sử & Đề Bài

Vào mùa đông năm 938, vùng cửa sông Bạch Đằng dậy sóng trước cuộc tiến công xâm lược của quân Nam Hán do thái tử Hoằng Tháo chỉ huy. Để đập tan dã tâm xâm lược, Ngô Quyền đã bày ra một trận địa vô cùng độc đáo: cắm hàng ngàn cây cọc gỗ đầu nhọn bịt sắt xuống lòng sông Bạch Đằng.

Dòng sông Bạch Đằng có chiều rộng cố định là $W$. Bờ sông phía nam nằm ở tọa độ $y = 0$, bờ sông phía bắc nằm ở tọa độ $y = W$. Lòng sông có $N$ chiếc cọc gỗ được cắm tại các tọa độ $(X_i, Y_i)$ với độ cao của cọc là $H_i$. 

Khi thủy triều dâng cao, toàn bộ các cọc gỗ bị ngập sâu dưới nước, giúp các chiến thuyền lớn của quân địch dễ dàng đi qua. Tuy nhiên, khi thủy triều rút xuống mức mực nước $L$, các cọc gỗ có độ cao lớn hơn hoặc bằng mực nước ($H_i \ge L$) sẽ nhô lên khỏi mặt nước và trở thành các chướng ngại vật vững chắc.

Chiến thuyền của Hoằng Tháo có dạng hình tròn đường kính $D$. Chiến thuyền xuất phát từ vùng biển phía tây ($x = -\infty$) và muốn hành quân sâu vào nội địa nước ta ở phía đông ($x = +\infty$). Thuyền không được chạm vào hai bờ sông ($y = 0$ và $y = W$) cũng như các cọc gỗ đang nhô lên trên mặt nước. 

Theo nguyên lý hình học, chiến thuyền đường kính $D$ không thể đi qua khe hở giữa hai chướng ngại vật nếu khoảng cách Euclid giữa chúng **nhỏ hơn $D$**. Dòng sông sẽ bị chặn đứng hoàn toàn nếu các chướng ngại vật (bao gồm bờ sông phía nam, bờ sông phía bắc và các cọc gỗ nhô lên) liên kết với nhau tạo thành một hàng rào chắn ngang sông từ nam lên bắc.

**Nhiệm vụ:** Hãy giúp Ngô Quyền xác định mực nước cao nhất $L_{max}$ sao cho chiến thuyền của quân địch **hoàn toàn không thể vượt qua** trận địa cọc (bị chặn đứng). Nếu ngay cả khi mực nước rút cạn trơ đáy (toàn bộ cọc đều nhô lên) mà chiến thuyền địch vẫn có thể lách qua trận địa cọc, hãy in ra `-1`.

---

## Chi Tiết Bài Toán

Cho chiều rộng sông $W$, đường kính chiến thuyền $D$, và danh sách $N$ chiếc cọc với tọa độ $(X_i, Y_i)$ và độ cao $H_i$.

*   Bờ sông phía nam được coi là đường thẳng $y = 0$.
*   Bờ sông phía bắc được coi là đường thẳng $y = W$.
*   Các cọc gỗ nhô lên khi mực nước sông $L \le H_i$.
*   Khoảng cách Euclid giữa hai cọc $i$ và $j$ là:
    $$dist(i, j) = \sqrt{(X_i - X_j)^2 + (Y_i - Y_j)^2}$$
    Nếu $dist(i, j) < D$, thuyền đường kính $D$ không thể lách qua giữa hai cọc này.
*   Khoảng cách từ cọc $i$ tới bờ sông phía nam là $Y_i$. Nếu $Y_i < D$, thuyền không thể lách qua giữa cọc và bờ nam.
*   Khoảng cách từ cọc $i$ tới bờ sông phía bắc là $W - Y_i$. Nếu $W - Y_i < D$, thuyền không thể lách qua giữa cọc và bờ bắc.

Tìm số nguyên $L_{max}$ lớn nhất sao cho tồn tại ít nhất một đường liên kết chặn từ bờ nam ($y = 0$) sang bờ bắc ($y = W$).

---

## Định Dạng Đầu Vào

*   **Dòng đầu tiên:** Chứa ba số nguyên dương $N$, $W$, và $D$ lần lượt là số lượng cọc gỗ, chiều rộng sông và đường kính chiến thuyền.
*   **$N$ dòng tiếp theo:** Mỗi dòng chứa ba số nguyên $X_i$, $Y_i$ và $H_i$ tương ứng là tọa độ $x$, tọa độ $y$ và độ cao của cọc thứ $i$.

---

## Định Dạng Đầu Xuất

*   **Một số nguyên duy nhất:** Giá trị mực nước lớn nhất $L_{max}$ để thuyền địch bị chặn hoàn toàn, hoặc `-1` nếu thuyền địch luôn có thể vượt qua.

---

## Ràng Buộc Hệ Thống

*   $1 \le N \le 2500$ (Số lượng cọc gỗ trên sông)
*   $1 \le W, D \le 10^9$ (Chiều rộng sông và kích thước thuyền có thể rất lớn)
*   $-10^9 \le X_i \le 10^9$ (Tọa độ dọc bờ sông)
*   $0 < Y_i < W$ (Cọc chỉ nằm trong lòng sông)
*   $1 \le H_i \le 10^9$ (Độ cao cọc gỗ)
*   Dữ liệu luôn đảm bảo $W \ge D$ (nếu sông hẹp hơn kích thước thuyền thì thuyền mặc định luôn bị chặn ngay từ đầu).

---

## Ví Dụ Minh Họa

### Đầu vào mẫu 1

```text
3 10 4
2 3 6
2 6 8
5 7 6
```

### Đầu ra mẫu 1

```text
6
```

### Giải Thích Trực Quan 1

*   Chiều rộng sông $W = 10$, đường kính thuyền $D = 4$.
*   Có 3 cọc gỗ:
    *   Cọc 1: tọa độ $(2, 3)$, độ cao $6$.
    *   Cọc 2: tọa độ $(2, 6)$, độ cao $8$.
    *   Cọc 3: tọa độ $(5, 7)$, độ cao $6$.

Nếu mực nước $L \le 6$, các cọc nhô lên bao gồm:
*   Cọc 1 (độ cao $6 \ge 6$)
*   Cọc 2 (độ cao $8 \ge 6$)
*   Cọc 3 (độ cao $6 \ge 6$)

Kiểm tra sự kết nối của các cọc nhô lên này với bờ sông:
*   Khoảng cách từ Cọc 1 tới bờ nam: $Y_1 = 3 < D = 4$ (Cọc 1 nối với bờ nam).
*   Khoảng cách từ Cọc 3 tới bờ bắc: $10 - Y_3 = 3 < D = 4$ (Cọc 3 nối với bờ bắc).
*   Khoảng cách giữa Cọc 1 và Cọc 2: $\sqrt{(2-2)^2 + (3-6)^2} = \sqrt{9} = 3 < D = 4$ (Cọc 1 nối với Cọc 2).
*   Khoảng cách giữa Cọc 2 và Cọc 3: $\sqrt{(2-5)^2 + (6-7)^2} = \sqrt{9 + 1} = \sqrt{10} \approx 3.16 < D = 4$ (Cọc 2 và Cọc 3 nối với nhau).

Như vậy, ta có chuỗi liên kết chặn hoàn chỉnh từ bờ nam sang bờ bắc:
`Bờ Nam` $\rightarrow$ `Cọc 1` $\rightarrow$ `Cọc 2` $\rightarrow$ `Cọc 3` $\rightarrow$ `Bờ Bắc`.
Mực nước tối đa để chuỗi này tồn tại là mực nước bé nhất trong các cọc thuộc chuỗi, tức là $\min(H_1, H_2, H_3) = \min(6, 8, 6) = 6$.
Do đó, kết quả là `6`.
