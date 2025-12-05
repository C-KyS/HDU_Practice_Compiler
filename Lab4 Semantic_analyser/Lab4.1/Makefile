CC = gcc
CFLAGS = -x c

# 默认目标，编译所有测试程序
all: test01 test02 test03 test04 test05

# 编译规则
test01: test1_basic.sy
	$(CC) $(CFLAGS) $< -o $@
test02: test2_control.sy
	$(CC) $(CFLAGS) $< -o $@

test03: test3_func.sy
	$(CC) $(CFLAGS) $< -o $@

test04: test4_array.sy
	$(CC) $(CFLAGS) $< -o $@

test05: test5_complex.sy
	$(CC) $(CFLAGS) $< -o $@

# 清理规则
.PHONY: clean
clean:
	rm -f test01 test02 test03 test04 test05