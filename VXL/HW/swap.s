.data
array .word 1, 2, 3, 4, 5, 6, 7, 8, 9, 10

.text
.global _start

_start: 
	LDR R0, =array		  // Đưa địa chỉ array vào R0
	LDR R3, #10           // Số lần duyệt array

loop:
	LDR R1, [R0], #4	  // Đưa giá trị ở địa chỉ [R0] vào R1
	LDR R2, [R0]		  // Đưa giá trị của phần tử tiếp theo vào R0
    CMP R2, R1			  // So sánh giá trị của phần tử sau và phần tử trước, nếu > thì hoán đổi vị trí
	BGT exchange
    SUBS R3, R3, #1       // Giảm bộ đếm vòng lặp
    BNE loop              // Nếu R3 != 0, quay lại vòng lặp  
	
	SVC #0				  // Kết thúc chương trình
	
exchange:
	SUB R0, R0, #4           // Trở lại địa chỉ phần tử thứ nhất
    STR R2, [R0], #4         // Ghi giá trị R2 (phần tử lớn hơn) vào vị trí thứ nhất, tăng R0 lên 4
    STR R1, [R0]             // Ghi giá trị R1 (phần tử nhỏ hơn) vào vị trí thứ hai
    SUBS R3, R3, #1          // Giảm bộ đếm vòng lặp
    BNE loop                 // Nếu R3 != 0, quay lại vòng lặp
    B loop                   // Quay lại kiểm tra tiếp		  
	
