# Tư duy thiết kế: Longest Substring Without Repeating Characters

Tìm chuỗi con dài nhất không chứa ký tự lặp lại là bài toán yêu cầu sự khéo léo trong việc quản lý phạm vi tìm kiếm. Mục tiêu là tìm ra độ dài lớn nhất mà không cần phải duyệt đi duyệt lại cùng một đoạn chuỗi nhiều lần.

## Vấn đề: Sự lãng phí của việc "Làm lại từ đầu"
Cách tiếp cận cơ bản là thử mọi chuỗi con có thể có và kiểm tra xem chúng có chứa ký tự lặp lại hay không.

- **Hệ quả:** Việc kiểm tra từng cặp vị trí tốn thời gian lên đến $O(n^2)$ hoặc $O(n^3)$. Khi gặp một ký tự lặp lại, nếu chúng ta vứt bỏ toàn bộ kết quả hiện tại và bắt đầu lại từ ký tự tiếp theo, chúng ta đang lãng phí những thông tin quý giá đã thu thập được.
- **Thách thức:** Làm sao để "trượt" qua chuỗi một cách liên tục mà vẫn đảm bảo tính duy nhất của các ký tự?

---

## Giải pháp: Chiếc "Khung ảnh linh hoạt" (Sliding Window)
Hãy tưởng tượng chúng ta có một chiếc khung ảnh có thể co giãn. Ta đặt cạnh phải của khung vào đầu chuỗi và bắt đầu kéo nó về bên phải để thu thêm ký tự.

**Bước ngoặt tư duy:**
Thay vì nhấc cả chiếc khung lên và đặt lại từ đầu khi thấy một ký tự đã tồn tại trong khung, chúng ta chỉ cần **co cạnh trái** của khung lại cho đến khi ký tự lặp lại đó bị loại ra ngoài.

Để biết một ký tự đã xuất hiện hay chưa và vị trí của nó ở đâu mà không mất công tìm kiếm, chúng ta sử dụng một chiếc "Sổ tay ghi chép" (Hash Map) lưu trữ `{ký_tự: vị_trí_cuối_cùng_xuất_hiện}`.

---

## Tại sao đây là cách tiếp cận tối ưu?
Kỹ thuật này biến việc tìm kiếm thành một hành trình "một chiều" duy nhất từ đầu đến cuối chuỗi.

- **Độ phức tạp thời gian:** $O(n)$. Cả cạnh trái và cạnh phải của khung chỉ đi từ trái sang phải đúng một lần.
- **Hiệu năng:** Chúng ta không bao giờ phải quay đầu lại. Mỗi khi mở rộng khung, ta chỉ mất $O(1)$ để kiểm tra sổ tay và cập nhật kết quả.

---

## Mô phỏng luồng xử lý
Giả sử chuỗi là: `abcabcbb`

1.  **Bắt đầu:** Khung rỗng, độ dài max = 0.
2.  **Mở rộng khung (a, b, c):** Khung chứa `abc`, độ dài hiện tại = 3. Sổ tay ghi: `{a:0, b:1, c:2}`.
3.  **Gặp ký tự 'a' lặp lại:**
    - Tra sổ tay thấy 'a' đã ở vị trí 0.
    - Nhảy cạnh trái của khung đến vị trí `0 + 1 = 1`.
    - Khung bây giờ chứa `bca`.
4.  **Tiếp tục:** Cạnh phải cứ thế tiến lên, cạnh trái chỉ nhảy khi gặp "vật cản" (ký tự lặp lại).
5.  **Kết thúc:** Độ dài lớn nhất ghi nhận được trong suốt quá trình là 3.

---

**Tổng kết:** Bí mật của Sliding Window là khả năng **tận dụng lại kết quả cũ**. Thay vì phá bỏ tất cả, chúng ta chỉ loại bỏ những phần không còn hợp lệ ở bên trái và tiếp tục khám phá những khả năng mới ở bên phải. Đây là tư duy cốt lõi để đưa các bài toán từ độ phức tạp bình phương về độ phức tạp tuyến tính.
