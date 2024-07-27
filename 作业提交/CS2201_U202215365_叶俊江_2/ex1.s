.section .data
buf1: .byte 0, 1, 2, 3, 4, 5, 6, 7, 8, 9
buf2: .fill 10, 1, 0
buf3: .fill 10, 1, 0
buf4: .fill 10, 1, 0

# 添加提示信息
string: .asciz "Press any key to begin!\n"
string_len = . - string
  
# 定义一个字符缓冲区来读取用户按键输入
input_char: .byte 1

.section .text
.global  main
main:
mov  $buf1, %esi
mov  $buf2, %edi
mov  $buf3, %ebx
mov  $buf4, %edx
mov  $10, %ecx

# 保存数据
push %eax
push %ebx
push %ecx
push %edx

# 显示提示信息
mov $4, %eax           # 系统调用号 (sys_write)
mov $1, %ebx           # 文件描述符 (stdout)
mov $string, %ecx      # 消息的地址
mov $string_len, %edx # 消息的长度
int $0x80             # 调用内核
  
# 等待按键输入
mov $3, %eax          # 系统调用号 (sys_read)
mov $0, %ebx          # 文件描述符 (stdin)
mov $input_char, %ecx # 输入缓冲区地址
mov $1, %edx          # 读取的字节数
int $0x80             # 调用内核

# 恢复数据
pop %edx
pop %ecx
pop %ebx
pop %eax

lopa:  mov  (%esi), %al
mov  %al, (%edi)
inc  %al
mov  %al, (%ebx)
add  $3,  %al
mov  %al, (%edx)
inc  %esi
inc  %edi
inc  %ebx
inc  %edx
dec  %ecx
jnz  lopa
mov  $1, %eax
movl $0, %ebx
int  $0x80
