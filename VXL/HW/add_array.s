.data
array: .word 1, 2, 3, 4, 5, 6, 7, 8, 9, 10

.text
.global sum
sum:
    LDR R0, =array        // R0: Địa chỉ cơ sở của mảng
    MOV R3, #0            // R3: Biến đếm (số phần tử trong mảng)
    MOV R2, #0            // R2: Tổng kết quả
    MOV R1, #0            // R1: Giá trị phần tử hiện tại

loop:
    LDR R1, [R0], #4      // Lấy giá trị của phần tử tại [R0] và tăng R0 thêm 4
    ADD R2, R2, R1        // Cộng giá trị của phần tử vào tổng (R2)
    ADD R3, R3, #1        // Tăng biến đêm R3 lên 1 và cập nhật trạng thái cờ (CPSR)
    CMP R3, #10           // So sánh R3 với 10, nếu bằng thì thoát khỏi vòng lặp
    BNE loop              // Nếu R3 != 0, quay lại đầu vòng lặp (loop)

    SVC #0                // Thoát 