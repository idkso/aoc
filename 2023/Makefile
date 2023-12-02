COMMON_C = common.c
COMMON = ${COMMON_C} common.h

all: day1 day2p1 day2p2

day1: ${.TARGET}.c ${COMMON}
	${LINK.c} -o ${.TARGET} ${.TARGET}.c ${COMMON_C}

day2p1: ${.TARGET}.c ${COMMON}
	sed -E 's/Game ([[:digit:]]+):/\1/; s/([[:digit:]]+) ([a-z]+)/\2=\1/g' day2.input > day2.input.pp
	${LINK.c} -o ${.TARGET} ${.TARGET}.c ${COMMON_C}

day2p2: ${.TARGET}.c ${COMMON}
	sed -E 's/Game ([[:digit:]]+):/\1/; s/([[:digit:]]+) ([a-z]+)/\2=\1/g' day2.input > day2.input.pp
	${LINK.c} -o ${.TARGET} ${.TARGET}.c ${COMMON_C}
