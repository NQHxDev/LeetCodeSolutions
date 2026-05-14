# Tư duy thiết kế: Bí mật của chiếc "Sổ tay ghi nhớ" (Two Sum)

Two Sum là một bài toán kinh điển để làm quen với một tư duy cực kỳ quan trọng trong lập trình: **Sử dụng bộ nhớ để tối ưu tốc độ.**

## Vấn đề: Cái giá của việc "Lười ghi nhớ"
Hãy tưởng tượng chúng ta đang đứng trước một hàng dài 1000 người và cần tìm ra 2 người có tổng số tuổi bằng 50.

Nếu dùng cách **Vét cạn (Brute Force)**:
- Ta chọn người thứ nhất, rồi chạy dọc cả hàng để hỏi từng người còn lại.
- Nếu không thấy, ta lại chọn người thứ hai, và lại... chạy dọc cả hàng một lần nữa.

=> **Hệ quả:** Chúng ta phải "chạy" rất nhiều lần ($O(n^2)$) vì mỗi lần kiểm tra, ta đều quên sạch những người mình đã từng gặp trước đó.

---

## Giải pháp: Chiếc "Sổ tay vạn năng" (Hash Map)
Thay vì lãng phí sức lực, chúng ta hãy mang theo một chiếc **Sổ tay**: Đi đến đâu, ghi lại tuổi và vị trí của người đó vào sổ đến đấy.

Khi đứng trước một người (gọi là `x`), thay vì chạy đi tìm người `y` khớp với mình (`y = 50 - x`), chúng ta chỉ cần đứng yên và lật sổ tay ra hỏi:
> **"Trong những người mình đã gặp trước đó, có ai `y` tuổi không?"**

- **Nếu có:** Chúng ta tìm thấy cặp đôi ngay lập tức!
- **Nếu chưa:** Ta ghi lại tuổi của người hiện tại vào sổ và bước sang người kế tiếp.

---

## Tại sao đây là cách tiếp cận tối ưu?
Trong lập trình, việc tra cứu trong "Sổ tay" (Hash Map) tốn thời gian gần như bằng không ($O(1)$).

- **Đánh đổi thông minh:** Chúng ta tốn thêm một ít bộ nhớ để giữ "Sổ tay" ($O(n)$), nhưng đổi lại chúng ta có tốc độ xử lý cực nhanh vì chỉ cần đi dọc hàng người đúng **1 lần duy nhất** ($O(n)$).
- **Nguyên tắc vàng:** Đừng bao giờ bắt máy tính làm đi làm lại một việc mà nó đã từng làm. Hãy ghi nhớ kết quả để sử dụng lại sau này.

---

## Mô phỏng luồng xử lý
Với `nums = [2, 7, 11, 15]` và `target = 9`:

1.  **Gặp số 2:**
    - Nhẩm: *"Cần tìm số 7"*.
    - Kiểm tra sổ: Chưa có số 7.
    - Hành động: Ghi `{2: vị trí 0}` vào sổ.
2.  **Gặp số 7:**
    - Nhẩm: *"Cần tìm số 2"*.
    - Kiểm tra sổ: **Đã có số 2 tại vị trí 0!**
    - **Kết luận:** Trả về `{0, 1}`.

---

**Tổng kết:** Tư duy Hash Map biến một bài toán "tìm kiếm" vất vả thành một bài toán "tra cứu" nhanh chóng. Đây là kỹ thuật nền tảng để giải quyết rất nhiều bài toán tối ưu phức tạp sau này.
