.data
array:  .word 7, 5, 3, 1, 2, 4, 6    // Mảng ban đầu cần sắp xếp

.text
.global _start

_start:
    LDR R0, =array           // R0: Địa chỉ cơ sở của mảng
    MOV R4, #7               // R4: Số phần tử trong mảng

outer_loop:
    SUB R5, R4, #1           // R5: Số phần tử cần kiểm tra (n - i)
    MOV R6, #0               // R6: Đặt bộ đếm vòng lặp trong

inner_loop:
    ADD R1, R0, R6, LSL #2   // R1: Địa chỉ phần tử thứ i
    LDR R2, [R1]             // R2: Giá trị phần tử thứ i
    LDR R3, [R1, #4]         // R3: Giá trị phần tử thứ i + 1

    CMP R2, R3               // So sánh R2 với R3
    BGT swap                 // Nếu R2 > R3, thực hiện hoán đổi

next_pair:
    ADD R6, R6, #1           // Tăng chỉ số phần tử tiếp theo
    CMP R6, R5               // Kiểm tra nếu đã so sánh hết các cặp trong vòng lặp
    BNE inner_loop           // Nếu chưa, quay lại vòng lặp trong

    SUB R4, R4, #1           // Giảm số phần tử cần kiểm tra trong vòng lặp ngoài
    CMP R4, #1               // Kiểm tra nếu chỉ còn 1 phần tử
    BNE outer_loop           // Nếu chưa, quay lại vòng lặp ngoài

    SVC #0                   // Kết thúc chương trình

swap:
    STR R3, [R1]             // Lưu R3 (phần tử lớn hơn) vào vị trí thứ i
    STR R2, [R1, #4]         // Lưu R2 (phần tử nhỏ hơn) vào vị trí thứ i + 1
    B next_pair              // Quay lại xử lý cặp phần tử tiếp theo
