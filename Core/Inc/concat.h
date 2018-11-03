/*
 * concat.h
 *
 *  Created on: Oct 20, 2018
 *      Author: wuyua
 */

#ifndef INC_CONCAT_H_
#define INC_CONCAT_H_

#define CONCAT2_(x,y) x##y
#define CONCAT2(x,y) CONCAT2_(x,y)

#define CONCAT3_(x,y) x##y##z
#define CONCAT3(x,y) CONCAT3_(x,y,z)


#endif /* INC_CONCAT_H_ */
