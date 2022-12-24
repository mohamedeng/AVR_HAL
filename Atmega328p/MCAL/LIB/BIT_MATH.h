/*
 * bit_math.h
 *
 * Created: 3/26/2022 11:09:17 PM
 *  Author: mohamed mahmoud abdo
 */ 


#ifndef BIT_MATH_H_
#define BIT_MATH_H_




#define setbit(reg,bit) (reg |= (1<<bit))
#define resetbit(reg,bit) (reg &= ~(1<<bit))
#define togglebit(reg,bit) (reg ^= (1<<bit))

#define set(reg) (reg = 0xFF)
#define reset(reg) (reg = 0)
#define toggle(reg) (reg ^= 0xFF)

#define readbit(reg,bit) (1 & (reg>>bit))

#endif /* BIT_MATH_H_ */