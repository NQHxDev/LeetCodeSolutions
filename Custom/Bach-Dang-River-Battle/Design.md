# Tài Liệu Thiết Kế Thuật Toán: Trận Chiến Trên Sông Bạch Đằng

## Bản Chất Hình Học & Sự Liên Thông Đồ Thị

### Sự Liên Tưởng Trực Quan: "Hàng Rào Chắn Sông"
Trục dọc $y$ biểu diễn chiều rộng sông từ $y = 0$ (bờ nam) đến $y = W$ (bờ bắc).
*   Các cọc gỗ là các điểm $i$ với tọa độ $(X_i, Y_i)$ và độ cao $H_i$.
*   Thuyền địch có kích thước đường kính $D$.
*   Nếu khoảng cách giữa hai cọc nhô lên nhỏ hơn $D$, thuyền không thể đi qua khe hở giữa chúng. Ta coi như giữa hai cọc này tồn tại một **liên kết chặn** (an blocking edge).
*   Nếu khoảng cách từ một cọc nhô lên tới bờ sông nhỏ hơn $D$, ta coi như cọc này có **liên kết chặn** với bờ sông tương ứng.

Dòng sông bị chặn đứng hoàn toàn khi và chỉ khi: **Tồn tại một đường liên kết chặn liên tục kết nối bờ nam ($y = 0$) và bờ bắc ($y = W$)**.

Dưới đây là hình vẽ trực quan của đường liên kết chặn:
```text
Bờ Bắc y = W ----------------------------------------------------
                       / (Khoảng cách < D)
                    [Cọc 3]
                      | (Khoảng cách < D)
                    [Cọc 2]
                     / (Khoảng cách < D)
                  [Cọc 1]
                 / (Khoảng cách < D)
Bờ Nam y = 0 -----------------------------------------------------
```

---

## Giải Pháp: Thuật Toán Kích Hoạt Đỉnh Giảm Dần & DSU

Để tìm mực nước $L_{max}$ lớn nhất mà chuỗi chặn này tồn tại, ta có thể tiếp cận theo hai hướng:

### Hướng tiếp cận 1: Tìm kiếm nhị phân (Binary Search) kết hợp DFS/BFS
*   Tìm kiếm nhị phân giá trị $L$ trong tập hợp các độ cao $H_i$ khả dĩ (tối đa $N$ giá trị khác nhau).
*   Với mỗi giá trị $L$ thử nghiệm, ta dựng lại đồ thị chỉ gồm các cọc có $H_i \ge L$. Chạy DFS/BFS hoặc DSU để kiểm tra liên thông giữa bờ nam và bờ bắc.
*   Độ phức tạp: $O(N^2 \log N)$. 
*   *Đánh giá:* Mặc dù chạy tốt với $N \le 2500$, thuật toán này lặp đi lặp lại việc kiểm tra đồ thị từ đầu, chưa tối ưu hoàn toàn.

### Hướng tiếp cận 2: Thuật toán kích hoạt đỉnh giảm dần theo Kruskal (Tối ưu nhất)
Thay vì dựng lại đồ thị nhiều lần, ta có thể xây dựng đồ thị một cách lũy tiến (incremental graph):
1.  **Sắp xếp** các cọc gỗ theo thứ tự độ cao $H_i$ **giảm dần**.
2.  Khởi tạo cấu trúc **DSU** gồm $N + 2$ đỉnh:
    *   Đỉnh $0$: đại diện cho bờ nam ($y = 0$).
    *   Đỉnh $N + 1$: đại diện cho bờ bắc ($y = W$).
    *   Đỉnh $1$ đến $N$: đại diện cho các cọc gỗ.
3.  Ta duyệt qua từng cọc $i$ theo thứ tự độ cao giảm dần (tương đương với việc mực nước rút dần và kích hoạt cọc cao trước):
    *   Khi cọc $i$ nhô lên mặt nước:
        *   Nếu khoảng cách từ cọc $i$ tới bờ nam $Y_i < D$: Nối cọc $i$ với đỉnh $0$ (bờ nam) trong DSU.
        *   Nếu khoảng cách từ cọc $i$ tới bờ bắc $W - Y_i < D$: Nối cọc $i$ với đỉnh $N + 1$ (bờ bắc) trong DSU.
        *   Duyệt qua tất cả các cọc $j$ đã được kích hoạt trước đó (có $H_j \ge H_i$): nếu khoảng cách Euclid giữa chúng $dist(i, j) < D$, ta gộp nhóm $i$ và $j$ trong DSU.
    *   **Kiểm tra điều kiện dừng:** Sau khi xử lý xong cọc $i$, ta kiểm tra xem đỉnh $0$ và đỉnh $N + 1$ đã liên thông với nhau chưa. Nếu đã liên thông, mực nước hiện tại $L = H_i$ chính là giá trị $L_{max}$ cần tìm! Ta dừng và trả về $H_i$.
4.  Nếu duyệt hết toàn bộ các cọc mà bờ nam và bờ bắc vẫn không liên thông, trả về `-1`.

Độ phức tạp thời gian:
*   Sắp xếp: $O(N \log N)$.
*   Mỗi cọc $i$ được duyệt qua, ta kiểm tra khoảng cách với $i-1$ cọc trước đó và thực hiện thao tác gộp nhóm trên DSU. Tổng số thao tác gộp nhóm là $O(N^2)$, mỗi thao tác mất thời gian gần như hằng số $O(\alpha(N))$ nhờ kĩ thuật nén đường (path compression).
*   Độ phức tạp tổng thể: $O(N^2)$ — Cực kỳ tối ưu và nhanh chóng, chạy dưới 0.1s với $N = 2500$ trong C++.

---

## Các Trường Hợp Kiểm Thử Bổ Sung

### Trường hợp 1: Thuyền rất lớn so với sông
*   **Đầu vào:**
    ```text
    2 5 6
    1 2 10
    3 3 8
    ```
*   **Mô tả:** Chiều rộng sông $W = 5$, nhưng thuyền có đường kính $D = 6$. Thuyền mặc định bị chặn ngay cả khi không có cọc nào (ngay từ ban đầu bờ nam và bắc đã liên thông vì $W < D$, nhưng do ràng buộc hệ thống đảm bảo $W \ge D$ nên trường hợp này ta giả định kết quả trả về luôn là mức nước cực cao hoặc không xảy ra). Nếu sông rộng $W = 6$, thuyền rộng $D = 6$, bờ nam và bắc trực tiếp cách nhau $6$. Khoảng cách $= 6 \ge D = 6$ (chưa nối trực tiếp). Nếu có cọc cắm ở giữa, nó sẽ kích hoạt chặn.
*   **Đầu ra mong đợi:** `-1` (nếu không có cọc nào chắn, hoặc phụ thuộc vào tọa độ cọc).

### Trường hợp 2: Không có cọc nào nhô lên đủ để chặn sông
*   **Đầu vào:**
    ```text
    3 10 3
    1 2 10
    5 5 10
    9 8 10
    ```
*   **Mô tả:** Chiều rộng sông $W = 10$, thuyền đường kính $D = 3$. Các cọc cắm tại $Y = 2, 5, 8$. Khoảng cách từ cọc 1 $(1,2)$ tới bờ nam là $2 < 3$ (nối bờ nam). Khoảng cách từ cọc 3 $(9,8)$ tới bờ bắc là $2 < 3$ (nối bờ bắc). Khoảng cách giữa cọc 1 và cọc 2 là $\sqrt{(1-5)^2 + (2-5)^2} = \sqrt{16+9} = 5 \ge D = 3$ (không nối). Khoảng cách giữa cọc 2 và 3 là $\sqrt{16+9} = 5 \ge 3$ (không nối). Do đó các cọc đứng quá xa nhau, không tạo thành hàng rào chặn.
*   **Đầu ra mong đợi:** `-1`

### Trường hợp 3: Hàng rào chéo zic-zac dọc theo dòng sông
*   **Đầu vào:**
    ```text
    4 10 4
    1 3 100
    3 5 80
    5 7 90
    7 8 70
    ```
*   **Mô tả:** Các cọc tạo thành một chuỗi liên kết zic-zac kéo dài dọc theo sông:
    *   Cọc 1 $(1, 3)$ nối với bờ nam ($3 < 4$). Độ cao 100.
    *   Cọc 2 $(3, 5)$ nối với cọc 1 (khoảng cách $\sqrt{4+4} = \sqrt{8} \approx 2.82 < 4$). Độ cao 80.
    *   Cọc 3 $(5, 7)$ nối với cọc 2 (khoảng cách $\sqrt{8} < 4$). Độ cao 90.
    *   Cọc 4 $(7, 8)$ nối với cọc 3 (khoảng cách $\sqrt{4+1} = \sqrt{5} \approx 2.23 < 4$). Độ cao 70.
    *   Cọc 4 $(7, 8)$ nối với bờ bắc ($10 - 8 = 2 < 4$).
    Hàng rào liên thông khi cả 4 cọc đều nhô lên, tức là mực nước rút xuống mức nhỏ nhất trong chuỗi là $H_4 = 70$.
*   **Đầu ra mong đợi:** `70`

### Trường hợp 4: Một cọc duy nhất chặn đứng dòng sông hẹp
*   **Đầu vào:**
    ```text
    1 5 3
    2 2 50
    ```
*   **Mô tả:** Sông rộng 5, thuyền rộng 3. Có 1 cọc cắm ở tọa độ $(2, 2)$, độ cao 50.
    *   Khoảng cách tới bờ nam: $2 < 3$ (nối bờ nam).
    *   Khoảng cách tới bờ bắc: $5 - 2 = 3 \ge 3$ (chưa nối bờ bắc? Khoan, khoảng cách từ cọc tới bờ bắc là $W - Y_1 = 3 \ge D = 3$. Nên chưa nối bờ bắc. Thuyền vẫn có thể lách qua khoảng trống rộng 3 ở phía bờ bắc).
    *   Nếu cọc cắm ở $(2, 2.5)$, khoảng cách tới bờ nam là $2.5 < 3$ (nối bờ nam) và tới bờ bắc là $2.5 < 3$ (nối bờ bắc). Lúc này 1 cọc duy nhất ở giữa sẽ kết nối cả 2 bờ sông!
*   **Đầu ra mong đợi:** `-1` (với cọc ở $y=2$) hoặc `50` (nếu cọc ở $y=2.5$).

### Trường hợp 5: Các cọc nhô lên ở nhiều thời điểm khác nhau, hàng rào hình thành muộn
*   **Đầu vào:**
    ```text
    3 10 4
    1 3 50
    2 6 100
    3 8 20
    ```
*   **Mô tả:** Để chặn sông, ta cần nối `Bờ Nam` $\rightarrow$ `Cọc 1` $\rightarrow$ `Cọc 2` $\rightarrow$ `Cọc 3` $\rightarrow$ `Bờ Bắc`.
    *   Cọc 1 nối bờ nam ($3 < 4$), cọc 3 nối bờ bắc ($2 < 4$).
    *   Cọc 1 và cọc 2 nối nhau (khoảng cách $\sqrt{1+9} = \sqrt{10} < 4$).
    *   Cọc 2 và cọc 3 nối nhau (khoảng cách $\sqrt{1+4} = \sqrt{5} < 4$).
    Hàng rào hình thành khi cả ba cọc đều nhô lên. Cọc 3 nhô lên cuối cùng ở độ cao $20$.
*   **Đầu ra mong đợi:** `20`
