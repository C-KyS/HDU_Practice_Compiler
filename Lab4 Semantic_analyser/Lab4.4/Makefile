# 目标：ss (编译词法、语法和语义分析器)
ss: ss.l ss.y ast.h semantic.cc
#	@echo "--- 编译词法/语法/语义分析器 (ss) ---"
	bison -d ss.y -o ss.tab.c
	flex -o ss.c ss.l
	g++ ss.c ss.tab.c semantic.cc -o ss 

# 目标：sss (自动运行所有测试文件)
# 依赖于 ss 可执行文件
sss: ss
	@echo "\n--- 运行测试文件 (test0*.sy) ---"
	@if [ -f ss ]; then \
		for file in test0*.sy; do \
			if [ -f "$$file" ]; then \
				echo "\n========================================"; \
				echo "执行: ./ss $$file"; \
				echo "----------------------------------------"; \
				./ss "$$file"; \
				echo "========================================"; \
			else \
				echo "未找到测试文件 (test0*.sy)!"; \
				break; \
			fi; \
		done; \
	else \
		echo "错误: 缺少可执行文件 ss。请先运行 'make' 或 'make ss'。"; \
	fi

# 目标：clean (清理生成的文件)
clean : 
# 	@echo "--- 清理生成文件 ---"
	rm -f ss.c ss.tab.c ss.tab.h ss

.PHONY: ss sss clean