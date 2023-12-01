COMMON_C = common.c
COMMON = ${COMMON_C} common.h

all: day1

day1: ${.TARGET}.c ${COMMON}
	${LINK.c} -o ${.TARGET} ${.TARGET}.c ${COMMON_C}
