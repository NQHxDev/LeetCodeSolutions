# Chợ Cá Tam Quan (Tam Quan Fish Market)

## Bối Cảnh Lịch Sử & Đề Bài

Mỗi buổi bình minh tại vùng biển Tam Quan, Quảng Nam, cảng biển lại trở nên nhộn nhịp khi các tàu đánh cá xa bờ lần lượt cập bến sau những ngày dài lênh đênh ngoài khơi. Hải sản tươi ngon sau khi đưa lên bờ cần được tiêu thụ nhanh chóng để giữ nguyên hương vị tinh túy của đại dương.

Mỗi tàu cá khi cập bến sẽ lập tức mở bán số cá đánh bắt được ngay tại mạn tàu. Lượng cá trên mỗi tàu được bán ra đều đặn theo thời gian cho đến khi hết hàng hoặc hết thời gian bảo quản.

Một đại thương lái muốn tận dụng cơ hội này để thu mua lượng cá lớn nhất có thể. Tuy nhiên, do giới hạn về nhân lực, sổ sách kiểm kho và phương tiện vận chuyển đông lạnh, người này chỉ có thể đứng tại bến trong **tối đa $K$ phút liên tục** để thu mua.

**Nhiệm vụ:** Hãy giúp thương lái tìm ra khoảng thời gian vàng dài $K$ phút để thu mua được tổng lượng cá lớn nhất từ tất cả các tàu đang neo đậu tại cảng Tam Quan.

---

## Chi Tiết Bài Toán

Cảng cá có $N$ tàu neo đậu được đánh số từ $1$ đến $N$. Đối với mỗi tàu thứ $i$:

- **Thời điểm bắt đầu bán cá**: $T_i$ (phút).
- **Thời gian mở bán kéo dài**: $D_i$ (phút), nghĩa là tàu sẽ bán cá từ thời điểm $T_i$ đến $T_i + D_i$.
- **Tổng lượng cá trên tàu**: $F_i$ (đơn vị khối lượng).
- **Đặc tính phân phối**: Cá được bán ra **đều đặn theo thời gian** với tốc độ không đổi là:
  $$R_i = \frac{F_i}{D_i} \quad (\text{đơn vị cá / phút})$$

Thương lái có thể chọn đứng ở bến trong khoảng thời gian $[L, L + K]$ liên tục (với mốc bắt đầu $L \ge 0$). Lượng cá thu mua được từ tàu $i$ sẽ tỷ lệ thuận với độ dài khoảng thời gian giao nhau giữa thời gian mở bán của tàu đó và khoảng thời gian đứng đợi của thương lái:
$$\text{Lượng cá mua được từ tàu } i = \text{Length}\Big([T_i, T_i + D_i] \cap [L, L + K]\Big) \times \frac{F_i}{D_i}$$

Hãy tìm thời điểm bắt đầu $L$ tối ưu sao cho tổng lượng cá thu mua được từ toàn bộ $N$ tàu cá là lớn nhất. Do kết quả tính toán có thể lẻ, kết quả cuối cùng cần được **làm tròn xuống số nguyên gần nhất** (lấy phần nguyên - floor).

---

## Định Dạng Đầu Vào

- **Dòng đầu tiên**: Chứa hai số nguyên dương $N$ và $K$ lần lượt là số lượng tàu cá và số phút tối đa thương lái có thể đứng tại bến.
- **$N$ dòng tiếp theo**: Mỗi dòng chứa ba số nguyên dương $T_i$, $F_i$, $D_i$ tương ứng với thời điểm bắt đầu bán, tổng lượng cá và thời gian mở bán của tàu thứ $i$.

---

## Định Dạng Đầu Ra

- **Một số nguyên duy nhất**: Tổng lượng cá tối đa có thể thu mua được sau khi đã làm tròn xuống số nguyên gần nhất.

---

## Ràng Buộc Hệ Thống

- $1 \le N \le 2 \times 10^5$ (Số lượng tàu cá rất lớn)
- $1 < K < 10^9$ (Thời gian đứng chờ có thể kéo dài)
- $1 \le D_i, F_i \le 10^9$ (Thời gian bán và lượng cá lớn)
- $0 \le T_i \le 10^9$ (Thời điểm cập bến bất kỳ trong ngày)

---

## Ví Dụ Minh Họa

### Đầu vào mẫu

```text
2 5
1 12 4
3 9 3
```

### Đầu ra mẫu

```text
21
```

### Giải Thích Trực Quan

- **Tàu 1**: Mở bán trong khoảng $[1, 1+4] = [1, 5]$. Tổng lượng cá là $12$, tốc độ bán là $\frac{12}{4} = 3$ đơn vị/phút.
- **Tàu 2**: Mở bán trong khoảng $[3, 3+3] = [3, 6]$. Tổng lượng cá là $9$, tốc độ bán là $\frac{9}{3} = 3$ đơn vị/phút.

Biểu đồ phân bố lượng cá bán ra theo thời gian:

```text
Thời gian (phút):   0   1   2   3   4   5   6   7
Tàu 1 [1, 5]:           |=======|=======|
                        (3 cá/phút)
Tàu 2 [3, 6]:                   |=======|===|
                                (3 cá/phút)
```

Nếu thương lái chọn khoảng thời gian trượt $[L, L + K] = [1, 1+5] = [1, 6]$:

- **Giao nhau với Tàu 1**: $[1, 5] \cap [1, 6] = [1, 5]$ (độ dài $4$ phút). Lượng cá mua được: $4 \times 3 = 12$.
- **Giao nhau với Tàu 2**: $[3, 6] \cap [1, 6] = [3, 6]$ (độ dài $3$ phút). Lượng cá mua được: $3 \times 3 = 9$.
- **Tổng thu mua**: $12 + 9 = 21$. Đây là phương án tối ưu nhất.
